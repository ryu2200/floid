#pragma once 
#include"myHeader.h"
#include"types.h"
#define UNLIMITED 1e+16

#ifndef SEQUENCE
//�ŏ���p�����m�[�h���v�Z����
inline NodeID calcMinCost(Network<Node_floyd*, Link_floyd*> net){
	//�G���[�Ȃ�-1��Ԃ��B����ȊO�͍ŒZ�́[��ID�Ԃ�
	NodeID minID = -1;
	double minCost = UNLIMITED;
	map<NodeID, Node_floyd*>::iterator it = net.nodes.begin();
	map<NodeID, Node_floyd*>::iterator itE = net.nodes.end();
	for (; it != itE; it++){
		if (it->second->isDet == false){
			//��p��������ł͂Ȃ��A������p����������p�����m�[�h��������X�V����
			if (minCost >it->second->ncost){
				minCost = it->second->ncost;
				minID = it->second->id;
			}
		}
	}
	return minID;

#elif SEQUENCE
	//�l�b�g���[�N��̃m�[�h�̒�����ŏ���p�����m�[�h��T������
	//�A�Ԃ�O��Ƃ����l�b�g���[�N�\���Ȃ炱��ł�����
	int minID = -1;
	double minCost = UNLIMITED;
	for (unsigned int i = 1; i <= net.nodes.size(); i++){
		if ((net.nodes[i]->isDet == false)){
			//��������p�����m�[�h��������X�V����
			if (minCost > net.nodes[i]->ncost){
				minCost = net.nodes[i]->ncost;
				minId = net.nodes[i]->id;
			}
		}
	}
	return minID;
#endif

}
inline Node_floyd* getNode_ptr(Network<Node_floyd*, Link_floyd*> net, int id){
	//�L�[�����݂���΃|�C���^�Ԃ�
	if (net.nodes.count(id) == 1){
		return (net.nodes.find(id)->second);
	}
	//�L�[�����݂��Ȃ����NULL�|�C���^��Ԃ�
	else if (net.nodes.count(id) == 0){
		return nullptr;
	}

}
//�t���C�h�@�Ńl�b�g���[�N��S�T������(�R)
inline void washall_floyd(int stId, Network<Node_floyd*, Link_floyd*> net, int& net_size){
	getNode_ptr(net, stId)->ncost = 0;
	for (;;){
		Node_floyd* minNode = getNode_ptr(net, calcMinCost(net));
		//�ŏ���p�����m�[�h��������Ȃ���ΑS�Ẵm�[�h��T�����Ă���̂ŏI��
		if (minNode == NULL){
			break;
		}
		
		minNode->isDet = true;
		//�m�肵���m�[�h�̐������l�b�g���[�N�̃m�[�h�����C���N�������g
		net_size++;
		//�L�[��������΂��̃m�[�h���烊���N�o�Ă��Ȃ�(outlinks�Q��)//������������������
		if (net.outLinks.count(minNode->id) != NULL){
			vector<Link_floyd*> next = net.outLinks.find(minNode->id)->second;
			for (auto itr = next.begin(); itr != next.end(); ++itr){
				auto newCost = minNode->ncost + (*itr)->getLinkCost();
				auto NextNodePtr = getNode_ptr(net, (*itr)->en);
				//�אڃm�[�h��p������p���傫����Δ�p���X�V����s�|�C���^���L�^����
				if (NextNodePtr->isDet == false){
					if (NextNodePtr->ncost > newCost){
						NextNodePtr->ncost = newCost;
						NextNodePtr->preNode = minNode;
					}
				}
				
			}
			
		}
	}
}
//�[���D��T���ŃO���t�̘A��������s��
inline void floyd(int stId, Network<Node_floyd*, Link_floyd*> net, int& net_size){
	//�n�_�m�[�h�̃|�C���^���擾
	Node_floyd* Node_c = getNode_ptr(net, stId);
	Node_c->isTraced = true;
	for (;;){
		//����ȏ�i�߂Ȃ���ΑS�Ẵm�[�h��T�����Ă���̂ŏI��
		if (Node_c == NULL){
			break;
		}
		//�s�悪�����
		if (net.outLinks.count(Node_c->id) != NULL){
			vector < Link_floyd* > ::iterator  next_it = net.outLinks.find(Node_c->id)->second.begin();
			vector < Link_floyd* > ::iterator  next_itE = net.outLinks.find(Node_c->id)->second.end();
			//�s��̃m�[�h���擾
			Node_floyd* NextNodePtr = getNode_ptr(net, (*next_it)->en);
			//�T���O�̗אڃm�[�h��T��
			for (; next_it != next_itE;next_it++){
				//���T���̃m�[�h���������
				if (NextNodePtr->isTraced == false){
					NextNodePtr = getNode_ptr(net, (*next_it)->en);
				}
			}
			//���T���̃m�[�h������Έړ�
			if (NextNodePtr->isTraced == false){
				//�אڃm�[�h�Ɉړ�
				NextNodePtr->isTraced = true;
				NextNodePtr->preNode = Node_c;
				Node_c = NextNodePtr;
			}
			//���T���̃m�[�h��������Ȃ���΃��[�v���ʂ߂�
			if (NextNodePtr->isTraced == true){
				break;
			}
			
		}
		//�s�悪�Ȃ��������͗אڃm�[�h���T���ς݂Ȃ��߂�
		if (net.outLinks.count(Node_c->id) != NULL&&){
			//Node_c = NextNodePtr->preNode
		}
	}
}