#pragma once
#include"types.h"
class Link {
public:
	LinkID id;
	NodeID st, en;
	Link(LinkID id_, NodeID st_, NodeID en_) {
		id = id_;
		st = st_;
		en = en_;
	}
	//�f�t�H���g�R���X�g���N�^
	Link(){};
};

