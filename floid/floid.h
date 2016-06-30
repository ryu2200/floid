#pragma once 
#include"myHeader.h"
#include"types.h"
#define UNLIMITED 1e+16

#ifndef SEQUENCE
//最小費用を持つノードを計算する
inline NodeID calcMinCost(Network<Node_floyd*, Link_floyd*> net){
	//エラーなら-1を返す。それ以外は最短のーどID返す
	NodeID minID = -1;
	double minCost = UNLIMITED;
	map<NodeID, Node_floyd*>::iterator it = net.nodes.begin();
	map<NodeID, Node_floyd*>::iterator itE = net.nodes.end();
	for (; it != itE; it++){
		if (it->second->isDet == false){
			//費用が無限大ではなく、同じ費用か小さい費用を持つノードが来たら更新する
			if (minCost >it->second->ncost){
				minCost = it->second->ncost;
				minID = it->second->id;
			}
		}
	}
	return minID;

#elif SEQUENCE
	//ネットワーク上のノードの中から最小費用を持つノードを探索する
	//連番を前提としたネットワーク構造ならこれでいける
	int minID = -1;
	double minCost = UNLIMITED;
	for (unsigned int i = 1; i <= net.nodes.size(); i++){
		if ((net.nodes[i]->isDet == false)){
			//小さい費用を持つノードが来たら更新する
			if (minCost > net.nodes[i]->ncost){
				minCost = net.nodes[i]->ncost;
				minId = net.nodes[i]->id;
			}
		}
	}
	return minID;
#endif

}
inline Node_floyd* getNode_ptr(Network<Node_floyd*, Link_floyd*> net, int id){
	//キーが存在すればポインタ返す
	if (net.nodes.count(id) == 1){
		return (net.nodes.find(id)->second);
	}
	//キーが存在しなければNULLポインタを返す
	else if (net.nodes.count(id) == 0){
		return nullptr;
	}

}
//フロイド法でネットワークを全探索する(嘘)
inline void washall_floyd(int stId, Network<Node_floyd*, Link_floyd*> net, int& net_size){
	getNode_ptr(net, stId)->ncost = 0;
	for (;;){
		Node_floyd* minNode = getNode_ptr(net, calcMinCost(net));
		//最小費用を持つノードが見つからなければ全てのノードを探索しているので終了
		if (minNode == NULL){
			break;
		}
		
		minNode->isDet = true;
		//確定したノードの数だけネットワークのノード数をインクリメント
		net_size++;
		//キーが無ければそのノードからリンク出ていない(outlinks参照)//ここが少しおかしい
		if (net.outLinks.count(minNode->id) != NULL){
			vector<Link_floyd*> next = net.outLinks.find(minNode->id)->second;
			for (auto itr = next.begin(); itr != next.end(); ++itr){
				auto newCost = minNode->ncost + (*itr)->getLinkCost();
				auto NextNodePtr = getNode_ptr(net, (*itr)->en);
				//隣接ノード費用が仮費用より大きければ費用を更新し先行ポインタを記録する
				if (NextNodePtr->isDet == false){
					if (NextNodePtr->ncost > newCost){
						NextNodePtr->ncost = newCost;
						NextNodePtr->preNode = minNode;
					}
				}
				
			}
			
		}
	}
}
//深さ優先探索でグラフの連結判定を行う
inline void floyd(int stId, Network<Node_floyd*, Link_floyd*> net, int& net_size){
	//始点ノードのポインタを取得
	Node_floyd* Node_c = getNode_ptr(net, stId);
	Node_c->isTraced = true;
	for (;;){
		//これ以上進めなければ全てのノードを探索しているので終了
		if (Node_c == NULL){
			break;
		}
		//行先があれば
		if (net.outLinks.count(Node_c->id) != NULL){
			vector < Link_floyd* > ::iterator  next_it = net.outLinks.find(Node_c->id)->second.begin();
			vector < Link_floyd* > ::iterator  next_itE = net.outLinks.find(Node_c->id)->second.end();
			//行先のノードを取得
			Node_floyd* NextNodePtr = getNode_ptr(net, (*next_it)->en);
			//探索前の隣接ノードを探す
			for (; next_it != next_itE;next_it++){
				//未探索のノードが見つかれば
				if (NextNodePtr->isTraced == false){
					NextNodePtr = getNode_ptr(net, (*next_it)->en);
				}
			}
			//未探索のノードがあれば移動
			if (NextNodePtr->isTraced == false){
				//隣接ノードに移動
				NextNodePtr->isTraced = true;
				NextNodePtr->preNode = Node_c;
				Node_c = NextNodePtr;
			}
			//未探索のノードが見つからなければループをぬめる
			if (NextNodePtr->isTraced == true){
				break;
			}
			
		}
		//行先がないもしくは隣接ノードが探索済みなら一つ戻る
		if (net.outLinks.count(Node_c->id) != NULL&&){
			//Node_c = NextNodePtr->preNode
		}
	}
}