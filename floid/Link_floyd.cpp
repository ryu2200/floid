#pragma once
#include "Link_floyd.h"

int Link_floyd::getLinkCost(){
	return this->lcost;
}
Link_floyd::Link_floyd(LinkID id_, NodeID st_, NodeID en_, int lc_,
	int headway_, int left_sfr_headway_, int straight_sfr_headway_,
	int right_sfr_headway_, int length_, int jamdens_) :Link(id_, st_, en_)
{
	lcost = lc_;
	headway = headway_;
	left_sfr_headway = left_sfr_headway_;
	straight_sfr_headway = straight_sfr_headway_;
	right_sfr_headway = right_sfr_headway_;
	length = length_;
	jamdens = jamdens_;
}


Link_floyd::~Link_floyd()
{
}