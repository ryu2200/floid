/*
* Network.h
*
*  Created on: 2015/09/24
*      Author: iryo
*/

#ifndef NETWORK_H_
#define NETWORK_H_

#include "types.h"
#include <map>
#include <vector>

using namespace std;

// ポイント：テンプレートクラスには，メンバの実装を要求してもよいが，メソッドの実装は，それが
// 不可欠で単純なものでないかぎり要求しないほうがよい（たとえば，不等号のオーバーロードとか）
// アルゴリズムの実態はNetwork側で極力実装すべき．
template <class NODE, class LINK>
class Network {
public:
	map<NodeID, NODE> nodes;
	map<NodeID, vector<LINK> > outLinks;
	map<NodeID, vector<LINK> > inLinks;
	Network() {
		nodes.clear();
		inLinks.clear();
		outLinks.clear();
	}
	~Network() {}
	int addNode(NODE node) {
		// すでに同じIDのノードが存在すればエラー（１）を返す
		if (nodes.count(node->id) > 0) return 1;
		nodes[node->id] = node;
		return 0;
	}
	int addLink(LINK link) {
		NodeID st = link->st;
		NodeID en = link->en;
		// 以降，なんかしらの問題があってリンクを追加できなければ1を返す
		if (nodes.count(st) == 0) return 1;
		if (nodes.count(en) == 0) return 1;
		// 重複リンクは許容されるとし，ここではチェックはしない
		outLinks[st].push_back(link);
		inLinks[en].push_back(link);
		return 0;
	}
};


#endif /* NETWORK_H_ */
