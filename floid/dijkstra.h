#include"Network.h"
#include"Node_dij.h"
#include"Link_dij.h"


using namespace std;

//�_�C�N�X�g���@�ōŒZ�o�H���o�͂���
void dijkstra(Network<Node_dij*, Link_dij*> net, NodeID startNode, NodeID endId);

//�o�H���o�͂���
void printParh(Network<Node_dij*, Link_dij*> net, NodeID startNode, NodeID endId);
//�ŏ���p�����m�[�h���v�Z����
int calcMinCost(Network<Node_dij*, Link_dij*> net,int& minID);
//�m�[�hID�����̃|�C���^�Q�b�g
Node_dij* getNode_ptr(Network<Node_dij*, Link_dij*> net, int Id);