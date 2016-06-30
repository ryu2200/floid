#pragma once
#include"types.h"
class Node {
public:
	NodeID id;
	int x;
	int y;

	Node(){}
	Node(NodeID id_,int x_,int y_) {
		id = id_;
		x = x_;
		y = y_;
	}
};