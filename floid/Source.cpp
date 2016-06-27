#include<iostream>
#include<vector>
#include<map>
#include"func.h"
#include"Network.h"
#include"Node_dij.h"
#include"Link_dij.h"
#include<random>
using namespace std;
char readline[MAX_LINE_NUM];
//無限大コスト
#define INF 100000
#define DEBUG 0
//ノードデータの格納
vector<line>node_data ;
vector<line>link_data;
Matrix d;//グラフの距離(自由流旅行時間を格納した二次元配列)
//メインルーチン
int main(int argc,char** argv){
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
	int node_num = NULL;
	readData(readline, node_data, fp_node, delimiter,node_num);
	cerr << "ノードファイルの読み込み成功" << endl;
	cout<<"ノード数=" << node_num << endl;
	fclose(fp_node);
	int link_num = NULL;
	readData(readline, link_data, fp_link, delimiter,link_num);
	cerr << "リンクファイルの読み込み成功" << endl;
	cout<< "リンク数=" << link_num << endl;
	fclose(fp_link);

	//3.ネットワークを生成する
	Network<Node_dij*, Link_dij*> net;
	//費用未確定、ノードコスト無限大のノードを生成する
	for (int i = 0; i < node_num;i++){
		// cout << stoi(node_data[i][0]) << endl;
		net.addNode(new Node_dij(stoi(node_data[i][0])));
	}
	//リンクを格納する
	for (int i = 0; i < link_num;i++){
		net.addLink(new Link_dij(stoi(link_data[i][0]), 
			stoi(link_data[i][1]),
			stoi(link_data[i][2]), 
			stoi(link_data[i][3])));
	}
	//フロイド法で全探索する
	int stNode = 110;
	int net_size = NULL;
	cout << net.nodes.size();
	washall_floyd(stNode,net,net_size);
	cout << "ネットワークサイズ="<<net_size << endl;
	
	

#if DEBUG
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
#endif
} 