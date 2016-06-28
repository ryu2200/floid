/*
* Network.h
*
*  Created on: 2015/09/24
*      Author: iryo
*/

#ifndef NETWORK_H_
#define NETWORK_H_

#include "types.h"
#include <map>
#include <vector>

using namespace std;

// �|�C���g�F�e���v���[�g�N���X�ɂ́C�����o�̎�����v�����Ă��悢���C���\�b�h�̎����́C���ꂪ
// �s���ŒP���Ȃ��̂łȂ�������v�����Ȃ��ق����悢�i���Ƃ��΁C�s�����̃I�[�o�[���[�h�Ƃ��j
// �A���S���Y���̎��Ԃ�Network���ŋɗ͎������ׂ��D
template <class NODE, class LINK>
class Network {
public:
	map<NodeID, NODE> nodes;
	map<NodeID, vector<LINK> > outLinks;
	map<NodeID, vector<LINK> > inLinks;
	Network() {
		nodes.clear();
		inLinks.clear();
		outLinks.clear();
	}
	~Network() {}
	int addNode(NODE node) {
		// ���łɓ���ID�̃m�[�h�����݂���΃G���[�i�P�j��Ԃ�
		if (nodes.count(node->id) > 0) return 1;
		nodes[node->id] = node;
		return 0;
	}
	int addLink(LINK link) {
		NodeID st = link->st;
		NodeID en = link->en;
		// �ȍ~�C�Ȃ񂩂���̖�肪�����ă����N��ǉ��ł��Ȃ����1��Ԃ�
		if (nodes.count(st) == 0) return 1;
		if (nodes.count(en) == 0) return 1;
		// �d�������N�͋��e�����Ƃ��C�����ł̓`�F�b�N�͂��Ȃ�
		outLinks[st].push_back(link);
		inLinks[en].push_back(link);
		return 0;
	}
};


#endif /* NETWORK_H_ */
