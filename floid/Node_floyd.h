#pragma once
#include "Node.h"
class Node_floyd :public Node{
public:
	//ノードコスト
	double ncost;
	//確定フラグ
	bool isDet;
	//無限大フラグ
	bool isInf;
	//先行ノードのポインタ
	Node_floyd* preNode;
	//デフォルトコンストラクタ
	Node_floyd();
	//ノード情報を初期化
	Node_floyd(NodeID id_,int x_,int y_);
	~Node_floyd();
};
