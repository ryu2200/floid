#include "Node_dij.h"
#define UNLIMITED 1e+10

Node_dij::Node_dij(NodeID id_) : Node(id_)
{//èâä˙ílÇ±ÇÍÇ≈ÇÊÇ©Ç¡ÇΩÇ¡ÇØ
	ncost = UNLIMITED;
	isDet = false;
}


Node_dij::~Node_dij()
{
}
