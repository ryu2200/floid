#pragma once 
#include<iostream>
#include<vector>
#include<string>
using namespace std;
typedef vector<string> line;
//読み込む行データの最大値.こいつに余裕もたせないとやばい
#define MAX_LINE_NUM 10000
//空行には改行コードだけが挿入されている
const char empty_line = '\n';
//区切り文字群(ハイフン,空白,イコール,カンマ,タブ,改行文字)
const char delimiter[] = "- =,	:\n";

//文字列をトークンに分解する.この改行コードも消去する
void readData(char* readline, vector<line>& line_data, FILE* fp, const char* delimiter, int& data_size){
	//一行分のデータ
	vector<string> splited_line;
	//strtok用の内生変数
	char* next;
	char* cfx;
	while (feof(fp) == 0){
		splited_line.clear();
		std::fgets(readline, MAX_LINE_NUM, fp);
		//空白行は無視する
		if ((*readline == empty_line)){
			continue;
		}
		//区切り文字に至るまでを一文字として格納
		next = strtok_s(readline, delimiter, &cfx);
		splited_line.push_back(next);
		while (next != NULL){
			next = strtok_s(NULL, delimiter, &cfx);
			if (next != NULL){
				splited_line.push_back(next);
			}
		}
		//行単位でデータを格納
		line_data.push_back(splited_line);
		data_size++;
	}
	//eofの分サイズを一減らす
	data_size--;
}





