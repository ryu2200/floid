#include"myHeader.h"
using namespace std;

int main(int argc,char** argv){
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
	char readline[MAX_LINE_NUM];
	//�m�[�h�f�[�^�̊i�[
	int node_num = NULL;
	vector<line>node_data;
	readData(readline, node_data, fp_node, delimiter,node_num);
	cerr << "�m�[�h�t�@�C���̓ǂݍ��ݐ���" << endl;
	cout<<"�m�[�h��=" << node_num << endl;
	fclose(fp_node);
	//�����N�f�[�^�̊i�[
	int link_num = NULL;
	vector<line>link_data;
	readData(readline, link_data, fp_link, delimiter,link_num);
	cerr << "�����N�t�@�C���̓ǂݍ��ݐ���" << endl;
	cout<< "�����N��=" << link_num << endl;
	fclose(fp_link);
	//delete readline;

	//3.�l�b�g���[�N�𐶐�����
	Network<Node_floyd*, Link_dij*> net;
	for (int i = 0; i < node_num;i++){
		net.addNode(new Node_floyd(stoi(node_data[i][0])));
	}
	node_data.clear();
	for (int i = 0; i < link_num;i++){
		net.addLink(new Link_dij(stoi(link_data[i][0]), 
			stoi(link_data[i][1]),
			stoi(link_data[i][2]), 
			stoi(link_data[i][3])));
	}
	link_data.clear();
	//�t���C�h�@�őS�T������
	int stId = net.nodes.begin()->first;
	int net_size = NULL;
	washall_floyd(stId,net,net_size);
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

} 