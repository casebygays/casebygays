#pragma once
#include "File.h"
#include "StructPack.h"
using namespace std;

class Computer {
	string IP;
	int level;
	bool ssh, ftp, smtp, http, proxy, firewall; // 포트
	bool is_nuke; // 해킹됨
	vector<File*> childFile;
public:
	Computer() {
		level = rand() % 3;
		IP = addRandomIP(level);
		ssh = rand() % 2;
		ftp = rand() % 2;
		smtp = rand() % 2;
		http = rand() % 2;
		proxy = rand() % 2 -1 + level;
		firewall = rand() % 2 - 1 + level;
		is_nuke = false;
	}
	
	~Computer() {
	}
	// 세팅
	void setPlayer() {
		IP = "127.0.0.1";
		is_nuke = true;
	}
	void setComputer(int lvl, string ip, int ssh, int ftp, int smtp, int http, int proxy, int firewall) {
		level = lvl;
		IP = ip;
		this->ssh = ssh;
		this->ftp = ftp;
		this->smtp = smtp;
		this->http = http;
		this->proxy = proxy;
		this->firewall = firewall;
		is_nuke = false;
	}
	string addRandomIP(int lvl) {
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
	void remove(int id) {
		for (File* f : File::files) {
			if (f->getId() == id) {
				for (int i = 0; i < childFile.size(); i++) {
					if (childFile[i]->getId() == id) { childFile.erase(childFile.begin() + i); }
				}
				if(f->getParent() != nullptr) f->getParent()->erase(id);
			}
		}
	}
	void childFileClear() {
		childFile.clear();
	}

	// 진행
	bool portCrack(string p, bool b) {
		if (p == "ssh" and ssh != b) ssh = b;
		else if (p == "ftp" and ftp != b) ftp = b;
		else if (p == "smtp" and smtp != b) smtp = b;
		else if (p == "http" and http != b) http = b;
		else if (p == "proxy" and proxy != b) proxy = b;
		else if (p == "firewall" and firewall != b) firewall = b;
		else return false; // 실패하면 false
		return true; // 성공적으로 열면 true
	}
	void nuke() { is_nuke = true; }
	int getLevel() { return level; }
	string getIP() { return IP; }
	File* getFile(int num) { return childFile[num]; }
	int getFileCount() { return childFile.size(); }
	bool getPort(string p) {
		if (p == "ssh") return ssh;
		else if (p == "ftp") return ftp;
		else if (p == "smtp") return smtp;
		else if (p == "http") return http;
		else if (p == "proxy") return proxy;
		else if (p == "firewall") return firewall;
		else return false;
	}
	bool getIsNuke() { return is_nuke; }
	bool getCanNuke() { return !ssh and !ftp and !smtp and !http and !proxy and !firewall or is_nuke; }
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