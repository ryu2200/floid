#include"Network.h"
#include"Node_dij.h"
#include"Link_dij.h"


using namespace std;

//ダイクストラ法で最短経路を出力する
void dijkstra(Network<Node_dij*, Link_dij*> net, NodeID startNode, NodeID endId);

//経路を出力する
void printParh(Network<Node_dij*, Link_dij*> net, NodeID startNode, NodeID endId);
//最小費用を持つノードを計算する
int calcMinCost(Network<Node_dij*, Link_dij*> net,int& minID);
//ノードID→そのポインタゲット
Node_dij* getNode_ptr(Network<Node_dij*, Link_dij*> net, int Id);