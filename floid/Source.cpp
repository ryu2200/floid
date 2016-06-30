#include"myHeader.h"
#include"types.h"
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
	Network<Node_floyd*, Link_floyd*> net;
	for (int i = 0; i < node_num;i++){
		net.addNode(new Node_floyd(stoi(node_data[i][0]), 
			stoi(node_data[i][1]),
			stoi(node_data[i][2])
			)
			);
	}
	node_data.clear();
	for (int i = 0; i < link_num;i++){
		net.addLink(new Link_floyd(stoi(link_data[i][0]), 
			stoi(link_data[i][1]),
			stoi(link_data[i][2]), 
			stoi(link_data[i][3]),
			stoi(link_data[i][4]),
			stoi(link_data[i][5]),
			stoi(link_data[i][6]),
			stoi(link_data[i][7]),
			stoi(link_data[i][8]),
			stoi(link_data[i][9])
			));
	}
	link_data.clear();
	cout << "ネットワークの生成終了" << endl;
	
	//探索は適当にnodesの先頭から開始
	int netId = NULL;
	NodeID stId = net.nodes.begin()->first;
	stId = 110;
	cout << "stId=" << stId << endl;
	//フロイド法で全探索する
	int net_size = NULL;
	washall_floyd(stId, net, net_size);
	cout << "NetworkId ="<<netId<<","<<"NetworkSize =" << net_size << endl;
#ifdef _DUBUG
	//4.ネットワークを分割する
	//分割後のネットワークを格納する配列
	vector<Network<Node_floyd*, Link_floyd*>> separated_net(1000);
	vector<Network<Node_floyd*, Link_floyd*>>::iterator separated_net_it = separated_net.begin();
	int netId = 0;

	for (;;){
		//nodesが空なら探索終了
		if (net.nodes.size()==NULL){
			break;
		}
		//探索は適当にnodesの先頭から開始
		NodeID stId = net.nodes.begin()->first;
		cout << "stId=" << stId << endl;
		//フロイド法で全探索する
		int net_size = NULL;
		washall_floyd(stId, net, net_size);//
		cout << "NetworkId ="<<netId<<","<<"NetworkSize =" << net_size << endl;
		cout << endl;
		netId++;
		//確定ノードと確定ノードから伸びるリンク(outlinksとinlinks)を格納
		map<NodeID,Node_floyd*>::iterator nodes_it = net.nodes.begin();
		map<NodeID, Node_floyd*>::iterator nodes_itE = net.nodes.end();
		for (; nodes_it != nodes_itE; nodes_it++){
			Node_floyd* nf = nodes_it->second;
			if (nf->isDet==true){
				//ノードを追加
				separated_net_it->addNode(new Node_floyd(nf->id,nf->x,nf->y));
				//リンクを追加

				//確定したノードをnodesから削除
				net.nodes.erase(nf->id);

			}
			
		}
		separated_net_it++;


	}
#endif
#ifdef _TEST
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

} 