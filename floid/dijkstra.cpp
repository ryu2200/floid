#include"dijkstra.h"
#include"Network.h"
#include"Node_dij.h"
#include"Link_dij.h"
#include<iostream>
#define UNLIMITED 1e+10

using namespace std;

void dijkstra(Network<Node_dij*, Link_dij*> net, NodeID startId, NodeID endId){
	//前の龍君のコード移植。たぶん井料先生とかとすり合わせ済みだろう＋楽だから。
	//StartNode,endIdはよくわからない。誤記防止が意図でも混乱しそう。統一したい。
	//Networkに渡す型は（当然）ポインタにした。main()とかと整合性取るため。networkの定義でポインタにした方が楽な気もする。変わらないかも。
	getNode_ptr(net, startId)->ncost = 0;
	for (;;){
		//1.a未確定ノードのうち最小費用を持つノードを検索する
		Node_dij* minNode = NULL;//getNode_ptr(net, calcMinCost(net));
		
		//cout << minNode->id<<"ll"<< endl;
		//費用確定フラグを立てる
		minNode->isDet = true;
		//終点ノードに到達したら終了
		if (endId == minNode->id){
			break;
		}
		//1.b隣接ノードまでの費用を計算する
		//隣接ノードのイテレータを定義する
		//キーが無ければoutlinksは存在しない
		if (net.outLinks.count(minNode->id) != NULL){
			vector<Link_dij*> next = net.outLinks.find(minNode->id)->second;
			//隣接ノードの中から一番費用の小さいノードを探す
			for (auto itr = next.begin(); itr != next.end(); ++itr){
				//仮費用を計算
				auto newCost = minNode->ncost + (*itr)->getLinkCost();
				//隣接ノードの費用が未定ならば
				auto NextNodePtr = getNode_ptr(net, (*itr)->en);
				if (NextNodePtr->isDet == false){//次とif分ける意味がよくわからん
					//隣接ノード費用が仮費用より大きければ
					//費用を更新し先行ポインタを設定する
					if (NextNodePtr->ncost > newCost){
						NextNodePtr->ncost = newCost;
						NextNodePtr->preNode = minNode;
					}
				}
			}
		}
	}

}

//経路を出力する
void printParh(Network<Node_dij*, Link_dij*> net, NodeID startId, NodeID endId){
	//最短経路記憶用
	Node_dij* root = getNode_ptr(net, endId);
	Node_dij* origin = getNode_ptr(net, startId);
	cout << "最短経路は" << endl;
	for (;;){
		//現在ノードを設定する
		Node_dij* node_c = root;
		//Id, Cost を出力する
		cout << "id :" << root->id << ", cost =" << node_c->ncost << endl;
		if (node_c == origin){
			break;
		}
		//先行ノードに移動
		root = node_c->preNode;
	}
}




//最小費用を持つノードを計算する
int calcMinCost(Network<Node_dij*, Link_dij*> net,int& minID){
	//ほぼ龍君の移植
	//エラーなら0を返す。それ以外は最短のーどID返す
	double minCost = UNLIMITED;
	
	map<NodeID, Node_dij*>::iterator it = net.nodes.begin();
	map<NodeID, Node_dij*>::iterator itE = net.nodes.end();

	for (;it!=itE; it++){
		if (it->second->isDet == false){
			//小さい費用を持つノードが来たら更新する
			if (minCost > it->second->ncost){
				//cout << it->second->id << endl;
				//最小費用を更新する
				minCost = it->second->ncost;
				//最小費用を持つノードのId
				minID = it->second->id;
				//cout << minID << endl;
			}
		}
	}
	return minID;

	
	//ネットワーク上のノードの中から最小費用を持つノードを探索する
	//連番を前提としたネットワーク構造ならこれでいける
#ifdef DEBUG
	for (unsigned int i = 1; i <= net.nodes.size(); i++){
		if ((net.nodes[i]->isDet == false)){
			//小さい費用を持つノードが来たら更新する
			if (minCost > net.nodes[i]->ncost){
				//最小費用を更新する
				minCost = net.nodes[i]->ncost;
				//最小費用を持つノードのId
				minId = net.nodes[i]->id;
			}
		}
	}
#endif
	
}

Node_dij* getNode_ptr(Network<Node_dij*, Link_dij*> net, int id){
	return (net.nodes.find(id)->second);
}