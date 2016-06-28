#include<iostream>
#include<vector>
#include<map>
#include"func.h"
#include"Network.h"
#include"Node_dij.h"
#include"Link_dij.h"
#include<random>
#include<sstream>
#include<chrono>
#include<fstream>
using namespace std;
char readline[MAX_LINE_NUM];
//������R�X�g
#define INF 100000
//�m�[�h�f�[�^�̊i�[
vector<line>node_data ;
vector<line>link_data;
Matrix d;//�O���t�̋���(���R�����s���Ԃ��i�[�����񎟌��z��)
//���C�����[�`��
int main(int argc,char** argv){
#if NDEBUG
	//�v���J�n
	const auto startTime = std::chrono::system_clock::now();
	//�p�����[�^�m�F
	if (argc != 3){
		cerr << "Invalid parameter num" << endl;
		return EXIT_FAILURE;
	}
	//1.�t�@�C���̑��݊m�F
	FILE* fp_node;
	FILE* fp_link;
	errno_t error_node = fopen_s(&fp_node, argv[1], "r");
	errno_t error_link = fopen_s(&fp_link, argv[2], "r");
	if (error_node != NULL){
		cerr << "Can't open node_file" << endl;
		return EXIT_FAILURE;
	}
	if (error_link != NULL){
		cerr << "Can't open link_file" << endl;
		return EXIT_FAILURE;
	}
	//2.�m�[�h�̃f�[�^�ƃ����N�̃f�[�^���i�[����
	int node_num = NULL;
	readData(readline, node_data, fp_node, delimiter,node_num);
	cerr << "�m�[�h�t�@�C���̓ǂݍ��ݐ���" << endl;
	cout<<"�m�[�h��=" << node_num << endl;
	fclose(fp_node);
	int link_num = NULL;
	readData(readline, link_data, fp_link, delimiter,link_num);
	cerr << "�����N�t�@�C���̓ǂݍ��ݐ���" << endl;
	cout<< "�����N��=" << link_num << endl;
	fclose(fp_link);

	//3.�l�b�g���[�N�𐶐�����
	Network<Node_dij*, Link_dij*> net;
	//��p���m��A�m�[�h�R�X�g������̃m�[�h�𐶐�����
	for (int i = 0; i < node_num;i++){
		// cout << stoi(node_data[i][0]) << endl;
		net.addNode(new Node_dij(stoi(node_data[i][0])));
	}
	//�����N���i�[����
	for (int i = 0; i < link_num;i++){
		net.addLink(new Link_dij(stoi(link_data[i][0]), 
			stoi(link_data[i][1]),
			stoi(link_data[i][2]), 
			stoi(link_data[i][3])));
	}
	//�t���C�h�@�őS�T������
	int stNode = net.nodes.begin()->first;
	cout << "�n�_�m�[�h��" << stNode << endl;
	int net_size = NULL;
	washall_floyd(stNode,net,net_size);
	cout << "�l�b�g���[�N�T�C�Y="<<net_size << endl;

#ifdef _DEBUG
	//���m��m�[�h���m�F(�f�o�b�N�p)
	ofstream unfixed_node("./unfixed_node.csv");
	map<NodeID, Node_dij*>::iterator it = net.nodes.begin();
	map<NodeID, Node_dij*>::iterator itE = net.nodes.end();

	for (; it != itE; it++){
		//�m��t���O�����m��̃m�[�h���t�@�C���ɏo��
		if (it->second->isDet == false){
			unfixed_node << it->second->id << ","<<endl;
		}
	}
#endif 
	//�I������
	const auto endTime = std::chrono::system_clock::now();
	const auto timeSpan = endTime - startTime;
	std::cout << "��������:" << std::chrono::duration_cast<std::chrono::milliseconds>(timeSpan).count() << "[ms]" << std::endl;
	int hoge = NULL;
	cout << "�����L�[����͂��Ă�������" << endl;
	cin >> hoge;
#endif

	/*
	node_num = 4000;
	
	d = Matrix(node_num, vector<int>(node_num, INF));
	for (int i = 0; i < node_num; i++) d[i][i] = 0;
	//�����N�R�X�g��ݒ肷��
	//���̎��w�b�_���}������Ă���ƃG���[
	for (int i = 0; i < link_num; i++) {
		int  stNode = NULL;
		int  enNode = NULL;;
		int freespd = NULL;
		stNode = stoi(link_data[i][1]);
		enNode = stoi(link_data[i][2]);
		freespd = stoi(link_data[i][3]);
		d[stNode][enNode] = freespd;
	}
	cerr << "�����N�R�X�g�̐ݒ�I��"<<endl;
	warshall_floyd(node_num,d);
	cerr << "�ŒZ�o�H�̌v�Z�I��" << endl;
	//�v�Z���ʂ��o��
	for (int i = 0; i < node_num; i++) {
		for (int j = 0; j < node_num; j++) {
			if (i != j && d[i][j] != INF){
				cout << i << "����" << j << "�ւ̃R�X�g: " << d[i][j] << endl;
			}
				
		}
	}
*/
} 