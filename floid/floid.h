#pragma once 
#include"myHeader.h"
#include"types.h"
#define UNLIMITED 1e+10

#ifndef SEQUENCE
//最小費用を持つノードを計算する
inline int calcMinCost(Network<Node_floyd*, Link_dij*> net){
	//エラーなら-1を返す。それ以外は最短のーどID返す
	int minID = -1;
	double minCost = UNLIMITED;
	map<NodeID, Node_floyd*>::iterator it = net.nodes.begin();
	map<NodeID, Node_floyd*>::iterator itE = net.nodes.end();
	for (; it != itE; it++){
		if (it->second->isDet == false){
			//小さい費用を持つノードが来たら更新する
			if (minCost > it->second->ncost){
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
inline Node_floyd* getNode_ptr(Network<Node_floyd*, Link_dij*> net, int id){
	//キーが存在すればポインタ返す
	if (net.nodes.count(id) == 1){
		return (net.nodes.find(id)->second);
	}
	//キーが存在しなければNULLポインタを返す
	else if (net.nodes.count(id) == 0){
		return nullptr;
	}

}
//フロイド法でネットワークを全探索する
inline void washall_floyd(int stId, Network<Node_floyd*, Link_dij*> net, int& net_size){
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
		//キーが無ければそのノードからリンク出ていない(outlinks参照)
		if (net.outLinks.count(minNode->id) != NULL){
			vector<Link_dij*> next = net.outLinks.find(minNode->id)->second;
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
