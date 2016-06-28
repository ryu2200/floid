#pragma once 
#include<iostream>
#include<vector>
#include<string>
#include <algorithm>
#include"network.h"
#include"dijkstra.h"
#include<chrono>
using namespace std;
typedef vector<string> line;
typedef vector<vector<int> > Matrix;
//�ǂݍ��ލs�f�[�^�̍ő�l.�����ɗ]�T�������Ȃ��Ƃ�΂�
#define MAX_LINE_NUM 10000
//��s�ɂ͉��s�R�[�h�������}������Ă���
const char empty_line = '\n';
//��؂蕶���Q(�n�C�t��,��,�C�R�[��,�J���},�^�u,���s����)
const char delimiter[] = "- =,	:\n";

//��������g�[�N���ɕ�������.���̉��s�R�[�h����������
void readData(char* readline, vector<line>& line_data, FILE* fp, const char* delimiter, int& data_size){
	//��s���̃f�[�^
	vector<string> splited_line;
	//strtok�p�̓����ϐ�
	char* next;
	char* cfx;
	while (feof(fp) == 0){
		splited_line.clear();
		std::fgets(readline, MAX_LINE_NUM, fp);
		//�󔒍s�͖�������
		if ((*readline == empty_line)){
			continue;
		}
		//��؂蕶���Ɏ���܂ł��ꕶ���Ƃ��Ċi�[
		next = strtok_s(readline, delimiter, &cfx);
		splited_line.push_back(next);
		while (next != NULL){
			next = strtok_s(NULL, delimiter, &cfx);
			if (next != NULL){
				splited_line.push_back(next);
			}
		}
		//�s�P�ʂŃf�[�^���i�[
		line_data.push_back(splited_line);
		data_size++;
	}
	//eof�̕��T�C�Y���ꌸ�炷
	data_size--;
}
//�t���C�h�@
void warshall_floyd(int n,Matrix d) { // n�͒��_��
	for (int i = 0; i < n; i++)      // �o�R���钸�_
		for (int j = 0; j < n; j++)    // �J�n���_
			for (int k = 0; k < n; k++)  // �I�[
				d[j][k] = min(d[j][k], d[j][i] + d[i][k]);			
}

void washall_floyd(int stId,Network<Node_dij*, Link_dij*> net,int& net_size){
	//�n�_�m�[�h�̃|�C���^���擾
	getNode_ptr(net, stId)->ncost = 0;
	for (;;){
		int minID = -1;
		Node_dij* minNode = getNode_ptr(net, calcMinCost(net,minID));
		//�ŏ���p�����m�[�h��������Ȃ���ΑS�Ẵm�[�h��T�����Ă���̂ŏI��
		if (minNode ==NULL){
			break;
		}
		//��p���m��
		minNode->isDet = true;
		net_size++;
		//�אڃm�[�h�܂ł̔�p���v�Z����.�L�[��������΂��̃m�[�h���烊���N�͐L�тĂ��Ȃ�
		if (net.outLinks.count(minNode->id) != NULL){
			vector<Link_dij*> next = net.outLinks.find(minNode->id)->second;
			for (auto itr = next.begin(); itr != next.end(); ++itr){
				auto newCost = minNode->ncost + (*itr)->getLinkCost();
				//�אڃm�[�h�̔�p������Ȃ��
				auto NextNodePtr = getNode_ptr(net, (*itr)->en);
				if (NextNodePtr->isDet == false){
					//�אڃm�[�h��p������p���傫����Δ�p���X�V����s�|�C���^���L�^����
					if (NextNodePtr->ncost > newCost){
						NextNodePtr->ncost = newCost;
						NextNodePtr->preNode = minNode;
					}
				}
			}
		}
	}
	

}
