#pragma once
#include "Link_floyd.h"

int Link_dij::getLinkCost(){
	return this->lcost;
}
Link_dij::Link_dij(LinkID id_, NodeID st_, NodeID en_, int lc_) :Link(id_, st_, en_)
{
	lcost = lc_;
}


Link_dij::~Link_dij()
{
}