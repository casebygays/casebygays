#pragma once
#include "File.h"

using namespace std;

class Port {
	bool enabled;
	int level;
public:
	Port(bool on = false, int lvl = 0) : enabled(on), level(lvl) {}
};
class Computer {
	string IP = "000.000.0.0";
	Port ssh, ftp, smt, http;
	vector<File*> childFile;
public:
	Computer() {
		IP = addRandomIP();
	}
	~Computer() {
		//delete[] file;
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
	void add(int index, File* child) {
		if (index < 0 || index >= childFile.size()) return; // index 유효성 검사

		childFile[index]->add(child);
	}
	void remove(int index) {
		childFile.erase(childFile.begin() + index);
	}
	
	string getIP() { return IP; }
	int getFileCount() { return childFile.size(); }
	File* getFile(int num) { return childFile[num]; }
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