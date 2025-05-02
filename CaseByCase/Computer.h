#pragma once
#include "File.h"
#include "StructPack.h"
using namespace std;

class Computer {
	string IP;
	bool ssh, ftp, smt, http; // ��Ʈ
	bool is_nuke; // ��ŷ��
	vector<File*> childFile;
public:
	Computer(bool player = false) {
		IP = addRandomIP();
		ssh = true;
		ftp = false;
		smt = false;
		http = false;
		is_nuke = false;
	}
	~Computer() {
		for (File* f : childFile)
			delete f;
	}
	// ����
	ComputerS save() {}
	void load() {}

	void setPlayer() {
		IP = "127.0.0.1";
		is_nuke = true;
	}
	string addRandomIP(int lvl = rand() % 3) {
		int min[4];
		int max[4];
		int octet[4];
		if (lvl == 2) {  // ��Ը� ���
			min[0] = 10; min[1] = 0; min[2] = 0; min[3] = 0;
			max[0] = 1; max[1] = 256; max[2] = 256; max[3] = 256;
		}
		else if (lvl == 1) {  // �߼ұ��
			min[0] = 172; min[1] = 16; min[2] = 0; min[3] = 0;
			max[0] = 1; max[1] = 16; max[2] = 256; max[3] = 256;
		}
		else {  // ����
			min[0] = 192; min[1] = 168; min[2] = 0; min[3] = 0;
			max[0] = 1; max[1] = 1; max[2] = 256; max[3] = 256;
		}
		
		for (int i = 0; i < 4; i++)
			octet[i] = min[i] + rand() % max[i];
		return to_string(octet[0]) + "." + to_string(octet[1]) + "." + to_string(octet[2]) + "." + to_string(octet[3]);
	}
	void add(File* child) {
		childFile.push_back(child);
	}
	void add(int index, File* child) {
		if (index < 0 || index >= childFile.size()) return;

		Folder* folder = dynamic_cast<Folder*>(childFile[index]);
		if (folder) {
			folder->add(child, childFile[index]);
		}
	}
	void remove(int index) {
		childFile.erase(childFile.begin() + index);
	}

	// ����
	bool portCrack(string p, bool b) {
		if (p == "ssh" and ssh != b) ssh = b;
		else if (p == "ftp" and ftp != b) ftp = b;
		else if (p == "smt" and smt != b) smt = b;
		else if (p == "http" and http != b) http = b;
		else return false;
		return true;
	}
	void nuke() { is_nuke = true; }
	string getIP() { return IP; }
	File* getFile(int num) { return childFile[num]; }
	int getFileCount() { return childFile.size(); }
	bool getIsNuke() { return is_nuke; }
	bool getCanNuke() { return !ssh and !ftp and !smt and !http or is_nuke; }
};

/*
�ּ�

�ڽ� : 127.0.0.1
��ε�ĳ��Ʈ : 255.255.255.255
�ƹ� IP�� ���� �ȵ�(��� ��Ʈ��ũ) : 0.0.0.0

10.0.0.0 ~ 10.255.255.255			��Ը� �����
172.16.0.0 ~ 172.31.255.255	 		�߼ұ����
192.168.0.0 ~ 192.168.255.255	 	������ ����� ��
*/