#include"Node_floyd.h"
#define UNLIMITED 1e+10

Node_floyd::Node_floyd(NodeID id_) : Node(id_)
{
	ncost = UNLIMITED;
	isDet = false;
}


Node_floyd::~Node_floyd()
{
}
