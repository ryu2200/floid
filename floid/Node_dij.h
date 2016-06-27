#pragma once
#include "Node.h"
class Node_dij :public Node{
public:
	//ノードコスト
	double ncost;
	//確定フラグ
	bool isDet;
	//先行ノードのポインタ
	Node_dij* preNode;
	//デフォルトコンストラクタ
	Node_dij();
	//ノード情報を初期化
	Node_dij(NodeID id_);
	~Node_dij();
};
