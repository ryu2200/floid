#include "Node_dij.h"
#define UNLIMITED 1e+10

Node_dij::Node_dij(NodeID id_) : Node(id_)
{//�����l����ł悩��������
	ncost = UNLIMITED;
	isDet = false;
}


Node_dij::~Node_dij()
{
}
