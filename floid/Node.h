#pragma once
#include"types.h"
class Node {
public:
	NodeID id;
	Node(){}
	Node(NodeID id_) {
		id = id_;
	}
};