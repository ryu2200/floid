#pragma once
#include "Link.h"
#include"types.h"
class Link_dij :public Link{
private:
	int  lcost;
public:
	int getLinkCost();
	Link_dij(LinkID id_, NodeID st_, NodeID en_, int lc_);
	~Link_dij();
};