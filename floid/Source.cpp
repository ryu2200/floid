#include<iostream>
#include<vector>
#include<map>
#include<chrono>
#include<fstream>
#include"readData.h"
#include"Network.h"
#include"Node_dij.h"
#include"Link_dij.h"
#include"floid.h"

using namespace std;

int main(int argc,char** argv){
	//計測開始
	const auto startTime = std::chrono::system_clock::now();
	//パラメータ確認
	if (argc != 3){
		cerr << "Invalid parameter num" << endl;
		return EXIT_FAILURE;
	}
	//1.ファイルの存在確認
	FILE* fp_node;
	FILE* fp_link;
	errno_t error_node = fopen_s(&fp_node, argv[1], "r");
	errno_t error_link = fopen_s(&fp_link, argv[2], "r");
	if (error_node != NULL){
		cerr << "Can't open node_file" << endl;
		return EXIT_FAILURE;
	}
	if (error_link != NULL){
		cerr << "Can't open link_file" << endl;
		return EXIT_FAILURE;
	}
	//2.ノードのデータとリンクのデータを格納する
	char readline[MAX_LINE_NUM];
	//ノードデータの格納
	int node_num = NULL;
	vector<line>node_data;
	readData(readline, node_data, fp_node, delimiter,node_num);
	cerr << "ノードファイルの読み込み成功" << endl;
	cout<<"ノード数=" << node_num << endl;
	fclose(fp_node);
	//リンクデータの格納
	int link_num = NULL;
	vector<line>link_data;
	readData(readline, link_data, fp_link, delimiter,link_num);
	cerr << "リンクファイルの読み込み成功" << endl;
	cout<< "リンク数=" << link_num << endl;
	fclose(fp_link);
	//delete readline;

	//3.ネットワークを生成する
	Network<Node_dij*, Link_dij*> net;
	for (int i = 0; i < node_num;i++){
		net.addNode(new Node_dij(stoi(node_data[i][0])));
	}
	node_data.clear();
	for (int i = 0; i < link_num;i++){
		net.addLink(new Link_dij(stoi(link_data[i][0]), 
			stoi(link_data[i][1]),
			stoi(link_data[i][2]), 
			stoi(link_data[i][3])));
	}
	link_data.clear();
	//フロイド法で全探索する
	int stId = net.nodes.begin()->first;
	int net_size = NULL;
	washall_floyd(stId,net,net_size);
	cout << "ネットワークサイズ="<<net_size << endl;

#ifdef _DEBUG
	//未確定ノードを確認(デバック用)
	ofstream unfixed_node("./unfixed_node.csv");
	map<NodeID, Node_dij*>::iterator it = net.nodes.begin();
	map<NodeID, Node_dij*>::iterator itE = net.nodes.end();

	for (; it != itE; it++){
		//確定フラグが未確定のノードをファイルに出力
		if (it->second->isDet == false){
			unfixed_node << it->second->id << ","<<endl;
		}
	}
#endif 
	//終了時刻
	const auto endTime = std::chrono::system_clock::now();
	const auto timeSpan = endTime - startTime;
	std::cout << "処理時間:" << std::chrono::duration_cast<std::chrono::milliseconds>(timeSpan).count() << "[ms]" << std::endl;


	/*
	node_num = 4000;
	
	d = Matrix(node_num, vector<int>(node_num, INF));
	for (int i = 0; i < node_num; i++) d[i][i] = 0;
	//リンクコストを設定する
	//この時ヘッダが挿入されているとエラー
	for (int i = 0; i < link_num; i++) {
		int  stNode = NULL;
		int  enNode = NULL;;
		int freespd = NULL;
		stNode = stoi(link_data[i][1]);
		enNode = stoi(link_data[i][2]);
		freespd = stoi(link_data[i][3]);
		d[stNode][enNode] = freespd;
	}
	cerr << "リンクコストの設定終了"<<endl;
	warshall_floyd(node_num,d);
	cerr << "最短経路の計算終了" << endl;
	//計算結果を出力
	for (int i = 0; i < node_num; i++) {
		for (int j = 0; j < node_num; j++) {
			if (i != j && d[i][j] != INF){
				cout << i << "から" << j << "へのコスト: " << d[i][j] << endl;
			}
				
		}
	}
*/
} 