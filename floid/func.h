#pragma once 
#include<iostream>
#include<vector>
#include<string>
#include <algorithm>
#include"network.h"
#include"dijkstra.h"
#include<chrono>
using namespace std;
typedef vector<string> line;
typedef vector<vector<int> > Matrix;
//読み込む行データの最大値.こいつに余裕もたせないとやばい
#define MAX_LINE_NUM 10000
//空行には改行コードだけが挿入されている
const char empty_line = '\n';
//区切り文字群(ハイフン,空白,イコール,カンマ,タブ,改行文字)
const char delimiter[] = "- =,	:\n";

//文字列をトークンに分解する.この改行コードも消去する
void readData(char* readline, vector<line>& line_data, FILE* fp, const char* delimiter, int& data_size){
	//一行分のデータ
	vector<string> splited_line;
	//strtok用の内生変数
	char* next;
	char* cfx;
	while (feof(fp) == 0){
		splited_line.clear();
		std::fgets(readline, MAX_LINE_NUM, fp);
		//空白行は無視する
		if ((*readline == empty_line)){
			continue;
		}
		//区切り文字に至るまでを一文字として格納
		next = strtok_s(readline, delimiter, &cfx);
		splited_line.push_back(next);
		while (next != NULL){
			next = strtok_s(NULL, delimiter, &cfx);
			if (next != NULL){
				splited_line.push_back(next);
			}
		}
		//行単位でデータを格納
		line_data.push_back(splited_line);
		data_size++;
	}
	//eofの分サイズを一減らす
	data_size--;
}
//フロイド法
void warshall_floyd(int n,Matrix d) { // nは頂点数
	for (int i = 0; i < n; i++)      // 経由する頂点
		for (int j = 0; j < n; j++)    // 開始頂点
			for (int k = 0; k < n; k++)  // 終端
				d[j][k] = min(d[j][k], d[j][i] + d[i][k]);			
}

void washall_floyd(int stId,Network<Node_dij*, Link_dij*> net,int& net_size){
	//始点ノードのポインタを取得
	getNode_ptr(net, stId)->ncost = 0;
	for (;;){
		int minID = -1;
		Node_dij* minNode = getNode_ptr(net, calcMinCost(net,minID));
		//最小費用を持つノードが見つからなければ全てのノードを探索しているので終了
		if (minNode ==NULL){
			break;
		}
		//費用を確定
		minNode->isDet = true;
		net_size++;
		//隣接ノードまでの費用を計算する.キーが無ければそのノードからリンクは伸びていない
		if (net.outLinks.count(minNode->id) != NULL){
			vector<Link_dij*> next = net.outLinks.find(minNode->id)->second;
			for (auto itr = next.begin(); itr != next.end(); ++itr){
				auto newCost = minNode->ncost + (*itr)->getLinkCost();
				//隣接ノードの費用が未定ならば
				auto NextNodePtr = getNode_ptr(net, (*itr)->en);
				if (NextNodePtr->isDet == false){
					//隣接ノード費用が仮費用より大きければ費用を更新し先行ポインタを記録する
					if (NextNodePtr->ncost > newCost){
						NextNodePtr->ncost = newCost;
						NextNodePtr->preNode = minNode;
					}
				}
			}
		}
	}
	

}
