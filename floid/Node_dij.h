#pragma once
#include "Node.h"
class Node_dij :public Node{
public:
	//�m�[�h�R�X�g
	double ncost;
	//�m��t���O
	bool isDet;
	//��s�m�[�h�̃|�C���^
	Node_dij* preNode;
	//�f�t�H���g�R���X�g���N�^
	Node_dij();
	//�m�[�h����������
	Node_dij(NodeID id_);
	~Node_dij();
};
