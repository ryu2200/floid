#pragma once
#include "Link.h"
#include"types.h"
class Link_floyd :public Link{
private:
	int  lcost;
	int headway;
	int left_sfr_headway;
	int straight_sfr_headway;
	int right_sfr_headway;
	int length;
	int jamdens;

public:
	int getLinkCost();
	Link_floyd(LinkID id_, NodeID st_, NodeID en_, int lcost_,
	int headway_,int left_sfr_headway_,int straight_sfr_headway_,
	int right_sfr_headway_,int length_,int jamdens_);
	~Link_floyd();
};