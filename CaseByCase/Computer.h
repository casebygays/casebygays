#pragma once
#include "File.h"
#include "StructPack.h"
using namespace std;

class Computer {
	string IP;
	bool ssh, ftp, smt, http; // 포트
	bool is_nuke; // 해킹됨
	vector<File*> childFile;
public:
	Computer() {
		IP = addRandomIP();
		ssh = rand() % 2;
		ftp = rand() % 2;
		smt = rand() % 2;
		http = rand() % 2;
		is_nuke = false;
	}
	~Computer() {
	}
	// 세팅
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
		if (lvl == 2) {  // 대규모 기업
			min[0] = 10; min[1] = 0; min[2] = 0; min[3] = 0;
			max[0] = 1; max[1] = 256; max[2] = 256; max[3] = 256;
		}
		else if (lvl == 1) {  // 중소기업
			min[0] = 172; min[1] = 16; min[2] = 0; min[3] = 0;
			max[0] = 1; max[1] = 16; max[2] = 256; max[3] = 256;
		}
		else {  // 가정
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
	void add(File* parent, File* child) {

		Folder* folder = dynamic_cast<Folder*>(parent);
		if (folder) {
			folder->add(parent, child);
		}
	}
	void remove(vector<File*> files, int id) {
		for (File* f : files) {
			if (f->getId() == id) {
				for (int i = 0; i < childFile.size(); i++) {
					if (childFile[i]->getId() == id) { childFile.erase(childFile.begin() + i); }
				}
				f->getParent()->erase(id);
			}
		}
	}

	// 진행
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
	bool getPort(string p) {
		if (p == "ssh") return ssh;
		else if (p == "ftp") return ftp;
		else if (p == "smt") return smt;
		else if (p == "http") return http;
		else return false;
	}
	bool getIsNuke() { return is_nuke; }
	bool getCanNuke() { return !ssh and !ftp and !smt and !http or is_nuke; }
};

/*
주소

자신 : 127.0.0.1
브로드캐스트 : 255.255.255.255
아무 IP도 지정 안됨(모든 네트워크) : 0.0.0.0

10.0.0.0 ~ 10.255.255.255			대규모 기업용
172.16.0.0 ~ 172.31.255.255	 		중소기업용
192.168.0.0 ~ 192.168.255.255	 	가정용 라우터 등
*/