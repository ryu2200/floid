#pragma once 
#include<vector>
#include"Node_dij.h"
#include"network.h"
#include"Link_dij.h"
#define UNLIMITED 1e+10

#ifndef SEQUENCE
//�ŏ���p�����m�[�h���v�Z����
int calcMinCost(Network<Node_dij*, Link_dij*> net){
	//�G���[�Ȃ�-1��Ԃ��B����ȊO�͍ŒZ�́[��ID�Ԃ�
	int minID = -1;
	double minCost = UNLIMITED;
	map<NodeID, Node_dij*>::iterator it = net.nodes.begin();
	map<NodeID, Node_dij*>::iterator itE = net.nodes.end();
	for (; it != itE; it++){
		if (it->second->isDet == false){
			//��������p�����m�[�h��������X�V����
			if (minCost > it->second->ncost){
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
Node_dij* getNode_ptr(Network<Node_dij*, Link_dij*> net, int id){
	//�L�[�����݂���΃|�C���^�Ԃ�
	if (net.nodes.count(id) == 1){
		return (net.nodes.find(id)->second);
	}
	//�L�[�����݂��Ȃ����NULL�|�C���^��Ԃ�
	else if (net.nodes.count(id) == 0){
		return nullptr;
	}

}
//�t���C�h�@�Ńl�b�g���[�N��S�T������
void washall_floyd(int stId, Network<Node_dij*, Link_dij*> net, int& net_size){
	getNode_ptr(net, stId)->ncost = 0;
	for (;;){
		Node_dij* minNode = getNode_ptr(net, calcMinCost(net));
		//�ŏ���p�����m�[�h��������Ȃ���ΑS�Ẵm�[�h��T�����Ă���̂ŏI��
		if (minNode == NULL){
			break;
		}
		minNode->isDet = true;
		//�m�肵���m�[�h�̐������l�b�g���[�N�̃m�[�h�����C���N�������g
		net_size++;
		//�L�[��������΂��̃m�[�h���烊���N�o�Ă��Ȃ�(outlinks�Q��)
		if (net.outLinks.count(minNode->id) != NULL){
			vector<Link_dij*> next = net.outLinks.find(minNode->id)->second;
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
