#pragma once
#include "Node.h"
class Node_floyd :public Node{
public:
	//�m�[�h�R�X�g
	double ncost;
	//�m��t���O
	bool isDet;
	//��s�m�[�h�̃|�C���^
	Node_floyd* preNode;
	//�f�t�H���g�R���X�g���N�^
	Node_floyd();
	//�m�[�h����������
	Node_floyd(NodeID id_);
	~Node_floyd();
};
