#include"dijkstra.h"
#include"Network.h"
#include"Node_dij.h"
#include"Link_dij.h"
#include<iostream>
#define UNLIMITED 1e+10

using namespace std;

void dijkstra(Network<Node_dij*, Link_dij*> net, NodeID startId, NodeID endId){
	//�O�̗��N�̃R�[�h�ڐA�B���Ԃ�䗿�搶�Ƃ��Ƃ��荇�킹�ς݂��낤�{�y������B
	//StartNode,endId�͂悭�킩��Ȃ��B��L�h�~���Ӑ}�ł������������B���ꂵ�����B
	//Network�ɓn���^�́i���R�j�|�C���^�ɂ����Bmain()�Ƃ��Ɛ�������邽�߁Bnetwork�̒�`�Ń|�C���^�ɂ��������y�ȋC������B�ς��Ȃ������B
	getNode_ptr(net, startId)->ncost = 0;
	for (;;){
		//1.a���m��m�[�h�̂����ŏ���p�����m�[�h����������
		Node_dij* minNode = NULL;//getNode_ptr(net, calcMinCost(net));
		
		//cout << minNode->id<<"ll"<< endl;
		//��p�m��t���O�𗧂Ă�
		minNode->isDet = true;
		//�I�_�m�[�h�ɓ��B������I��
		if (endId == minNode->id){
			break;
		}
		//1.b�אڃm�[�h�܂ł̔�p���v�Z����
		//�אڃm�[�h�̃C�e���[�^���`����
		//�L�[���������outlinks�͑��݂��Ȃ�
		if (net.outLinks.count(minNode->id) != NULL){
			vector<Link_dij*> next = net.outLinks.find(minNode->id)->second;
			//�אڃm�[�h�̒������Ԕ�p�̏������m�[�h��T��
			for (auto itr = next.begin(); itr != next.end(); ++itr){
				//����p���v�Z
				auto newCost = minNode->ncost + (*itr)->getLinkCost();
				//�אڃm�[�h�̔�p������Ȃ��
				auto NextNodePtr = getNode_ptr(net, (*itr)->en);
				if (NextNodePtr->isDet == false){//����if������Ӗ����悭�킩���
					//�אڃm�[�h��p������p���傫�����
					//��p���X�V����s�|�C���^��ݒ肷��
					if (NextNodePtr->ncost > newCost){
						NextNodePtr->ncost = newCost;
						NextNodePtr->preNode = minNode;
					}
				}
			}
		}
	}

}

//�o�H���o�͂���
void printParh(Network<Node_dij*, Link_dij*> net, NodeID startId, NodeID endId){
	//�ŒZ�o�H�L���p
	Node_dij* root = getNode_ptr(net, endId);
	Node_dij* origin = getNode_ptr(net, startId);
	cout << "�ŒZ�o�H��" << endl;
	for (;;){
		//���݃m�[�h��ݒ肷��
		Node_dij* node_c = root;
		//Id, Cost ���o�͂���
		cout << "id :" << root->id << ", cost =" << node_c->ncost << endl;
		if (node_c == origin){
			break;
		}
		//��s�m�[�h�Ɉړ�
		root = node_c->preNode;
	}
}




//�ŏ���p�����m�[�h���v�Z����
int calcMinCost(Network<Node_dij*, Link_dij*> net,int& minID){
	//�قڗ��N�̈ڐA
	//�G���[�Ȃ�0��Ԃ��B����ȊO�͍ŒZ�́[��ID�Ԃ�
	double minCost = UNLIMITED;
	
	map<NodeID, Node_dij*>::iterator it = net.nodes.begin();
	map<NodeID, Node_dij*>::iterator itE = net.nodes.end();

	for (;it!=itE; it++){
		if (it->second->isDet == false){
			//��������p�����m�[�h��������X�V����
			if (minCost > it->second->ncost){
				//cout << it->second->id << endl;
				//�ŏ���p���X�V����
				minCost = it->second->ncost;
				//�ŏ���p�����m�[�h��Id
				minID = it->second->id;
				//cout << minID << endl;
			}
		}
	}
	return minID;

	
	//�l�b�g���[�N��̃m�[�h�̒�����ŏ���p�����m�[�h��T������
	//�A�Ԃ�O��Ƃ����l�b�g���[�N�\���Ȃ炱��ł�����
#ifdef DEBUG
	for (unsigned int i = 1; i <= net.nodes.size(); i++){
		if ((net.nodes[i]->isDet == false)){
			//��������p�����m�[�h��������X�V����
			if (minCost > net.nodes[i]->ncost){
				//�ŏ���p���X�V����
				minCost = net.nodes[i]->ncost;
				//�ŏ���p�����m�[�h��Id
				minId = net.nodes[i]->id;
			}
		}
	}
#endif
	
}

Node_dij* getNode_ptr(Network<Node_dij*, Link_dij*> net, int id){
	return (net.nodes.find(id)->second);
}