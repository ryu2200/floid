#include"Node_floyd.h"
#define UNLIMITED 1e+16//これじゃ値が小さすぎるかも

Node_floyd::Node_floyd(NodeID id_,int x_,int y_) : Node(id_,x_,y_)
{
	ncost = UNLIMITED;
	isDet = false;
	isInf = true;
}


Node_floyd::~Node_floyd()
{
}
