#pragma once
#include "Link.h"
#include"types.h"
class Link_dij :public Link{
private:
	//�����N�R�X�g
	int  lcost;
public:
	//�����N�R�X�g���擾����
	int getLinkCost();
	Link_dij(LinkID id_, NodeID st_, NodeID en_, int lc_);
	~Link_dij();
};

