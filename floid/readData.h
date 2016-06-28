#pragma once 
#include<iostream>
#include<vector>
#include<string>
using namespace std;
typedef vector<string> line;
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





