#pragma once
#include "Canvas.h"
#include "Computer.h"
#include "StructPack.h"
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

class Command {
	Canvas* canvas;

	Computer* computer;
	int comMax;
	Computer* targetCom; //타겟팅 컴퓨터
	Computer* connectCom; // 접속한 컴퓨터
	File* currentFile; // 현재 파일

	bool shutdown; // 게임 종료
public:
	Command(Canvas* c, Computer* com, int cM)
	{
		canvas = c;
		computer = com;
		comMax = cM;
		targetCom = nullptr;
		connectCom = nullptr;
		currentFile = nullptr;
		shutdown = false;
	}
	CommandS save() {}
	void load() {}
	void checkCommand(const string& s)
	{
		istringstream iss(s);
		string token;
		vector<string> tokens;

		while (iss >> token) { tokens.push_back(token); }

		if (tokens.empty()) { return; }
		else if (tokens[0] == "/shutdown") cmd_shutdown();
		else if (tokens[0] == "/save") cmd_savegame();
		else if (tokens[0] == "/load") cmd_loadgame();
		else if (tokens[0] == "/help") cmd_help();
		else if (tokens[0] == "/clear") cmd_clear();
		else if (tokens[0] == "/addtxt" and tokens.size() > 2) cmd_addtxt(tokens[1], tokens[2]);
		else if (tokens[0] == "/addexe") cmd_addexe(tokens[1]);
		else if (tokens[0] == "/addfolder") cmd_addfolder(tokens[1]);
		else if (tokens[0] == "/remove") cmd_remove(tokens[1]);

		else if (tokens[0] == "/scan") cmd_scan();
		else if (tokens[0] == "/portscan") cmd_portscan();
		else if (tokens[0] == "/target" and tokens.size() > 1) cmd_target(tokens[1]);
		else if (tokens[0] == "/crack" and tokens.size() > 1) cmd_crack(tokens[1]);
		else if (tokens[0] == "/nuke" and tokens.size() > 1) cmd_nuke(tokens[1]); // IP 적었을때
		else if (tokens[0] == "/nuke") cmd_nuke(); // IP 안적었을때
		else if (tokens[0] == "/unlock" and tokens.size() > 2) cmd_unlock(tokens[1], tokens[2]);

		else if (tokens[0] == "/connect" and tokens.size() > 1) cmd_connect(tokens[1]); // IP 적었을때
		else if (tokens[0] == "/connect") cmd_connect(); // IP 안적었을때
		else if (tokens[0] == "/disconnect") cmd_disconnect();
		else if (tokens[0] == "/in" and tokens.size() > 1) cmd_in(tokens[1]);
		else if (tokens[0] == "/out") cmd_out();
	}
	File* getCurrentFile() { return currentFile; }
	bool getShutdown() { return shutdown; }

	
	void cmd_shutdown() { shutdown = true; }
	void cmd_savegame() {
		ofstream file("Save.txt");
		if (file.is_open()) {
			//file << "name=" << name << '\n';
			//file << "level=" << level << '\n';
			//file << "health=" << health << '\n';
			file.close();
			cout << "저장 완료!" << endl;
		}
	}
	void cmd_loadgame() {
		ifstream file("Save.txt");
		string line;
		while (getline(file, line)) {
			size_t sep = line.find('=');
			if (sep == string::npos) continue;

			string key = line.substr(0, sep);
			string value = line.substr(sep + 1);

			//if (key == "name") name = value;
			//else if (key == "level") level = stoi(value);
			//else if (key == "health") health = stod(value);
		}

		file.close();
	}
	void cmd_help()
	{
		canvas->input("/shutdown				게임 종료");
		canvas->input("/in [파일]				파일 열기");
		canvas->input("/out				이전으로 돌아감 (사이트 나가기, 상위폴더로 나가기 등)");
		canvas->input("/scan				주변 IP 스캔");
		canvas->input("/clear				드르륵 탁 clear");

		canvas->input("/unlock [파일] [비밀번호]		비밀번호 해제");
		canvas->input("/decoding [파일]			대상 파일 복호화");
		canvas->input("/portscan [IP]			포트 정보 확인");
		canvas->input("/crack ssh				22번 포트 열기");
		canvas->input("/crack ftp				21번 포트 열기");
		canvas->input("/crack smtp			25번 포트 열기");
		canvas->input("/crack http			80번 포트 열기");
		canvas->input("/nuke [IP]				PC 해킹");
		canvas->input("/connect [IP]			해당 컴퓨터 접속");
		canvas->input("/disconnect			접속 종료");
		canvas->input("removelog				로그 삭제");
	}
	void cmd_clear() { canvas->cmdClear(); }
	void cmd_addtxt(string name, string desc) {
		if (currentFile == nullptr or dynamic_cast<Folder*>(currentFile)) {
			File* f = new txt(File::fileId, "public", name, desc, true);
			if (currentFile != nullptr) { connectCom->add(currentFile, f); }
			else if (connectCom != nullptr) { connectCom->add(f); }
			File::files.push_back(f);
			File::fileId++;
			canvas->input("txt를 생성함");
		}
		else {
			canvas->input("파일을 생성할 수 없는 경로임");
		}
	}
	void cmd_addexe(string name) {
		if (currentFile == nullptr or dynamic_cast<Folder*>(currentFile)) {
			File* f = new exe(File::fileId, "public", name, true);
			if (currentFile != nullptr) { connectCom->add(currentFile, f); }
			else if (connectCom != nullptr) { connectCom->add(f); }
			File::files.push_back(f);
			File::fileId++;
			canvas->input("exe를 생성함");
		}
		else {
			canvas->input("파일을 생성할 수 없는 경로임");
		}
	}
	void cmd_addfolder(string name) {
		if (currentFile == nullptr or dynamic_cast<Folder*>(currentFile)) {
			File* f = new Folder(File::fileId, "public", name, true);
			if (currentFile != nullptr) { connectCom->add(currentFile, f); }
			else if (connectCom != nullptr) { connectCom->add(f); }
			File::files.push_back(f);
			File::fileId++;
			canvas->input("폴더를 생성함");
		}
		else {
			canvas->input("파일을 생성할 수 없는 경로임");
		}
	}
	void cmd_remove(string name) {
		if (currentFile != nullptr) { 
			for (int i = 0; i < currentFile->getFileCount(); i++) { // 현재폴더 내에 모든 파일 검사
				if (currentFile->getFile(i)->getName() == name) { // 현재폴더의 파일중 입력받은 이름과 같은 파일이 있으면,
					if (currentFile->getFile(i)->getCanRemove()) {
						int id = currentFile->getFile(i)->getId();
						connectCom->remove(id); // 접속중인 컴퓨터의 remove함수를 호출
						for (int j = 0; j < File::files.size(); j++) {						// files의 모든 파일을 검사
							if (File::files[j]->getId() == id) { // 파일의 id와 같으면
								delete File::files[j];											// 제거
								File::files.erase(File::files.begin() + j);						// files안에서도 제거
							}
						}
						canvas->input("지정한 파일 삭제됨");
					}
					else {
						canvas->input("삭제 불가능한 파일입니다.");
					}
				}
			}
		}
		else if (connectCom != nullptr) {
			for (int i = 0; i < connectCom->getFileCount(); i++) {
				if (connectCom->getFile(i)->getName() == name) {
					if (connectCom->getFile(i)->getCanRemove()) {
						int id = connectCom->getFile(i)->getId();
						connectCom->remove(id);
						for (int j = 0; j < File::files.size(); j++) {
							if (File::files[j]->getId() == id) {
								delete File::files[j];
								File::files.erase(File::files.begin() + j);
							}
						}
					}
					else {
						canvas->input("삭제 불가능한 파일입니다.");
					}
				}
			}
		}
	}
	// 해킹
	void cmd_scan()
	{
		canvas->input(computer[1].getIP()); // 임시
		for (int i = 0; i < 3; i++) {
			int com = 1 + rand() % (comMax - 1);
			canvas->input(computer[com].getIP());
		}
	}
	void cmd_portscan() {
		if (targetCom) {
			string s = "포트 정보|";
			if (targetCom->getPort("ssh")) s += "ssh : O|";
			else s += "ssh : X|";
			if (targetCom->getPort("ftp")) s += "ftp : O|";
			else s += "ftp : X|";
			if (targetCom->getPort("smt")) s += "smt : O|";
			else s += "smt : X|";
			if (targetCom->getPort("http")) s += "http : O|";
			else s += "http : X|";
			if (targetCom->getPort("proxy")) s += "proxy : O|";
			else s += "proxy : X|";
			if (targetCom->getPort("firewall")) s += "firewall : O|";
			else s += "firewall : X|";
			
			canvas->input(s);
		}
		else {
			canvas->input("대상 IP가 지정되지 않음");
		}
	}
	void cmd_target(string ip) {
		for (int i = 0; i < comMax; i++) {
			if (computer[i].getIP() == ip) {
				canvas->input(ip + " : 목표로 지정함");
				targetCom = &computer[i];
				break;
			}
		}
	}
	void cmd_crack(string target) { 
		if (targetCom != nullptr)
		{
			if (targetCom->portCrack(target, false)) canvas->input(target + " : 성공적으로 포트를 엶");
			else canvas->input(target + " : 포트가 열려있거나, 대상을 찾지못함");
		}
	}
	void cmd_nuke(string ip = "") {
		if (ip == "" and targetCom != nullptr) {
			if (targetCom->getCanNuke()) {
				targetCom->nuke();
				canvas->input(targetCom->getIP() + " : 해킹 성공");
			}
			else {
				canvas->input(targetCom->getIP() + " : 해킹 실패");
			}
		}
		else {
			for (int i = 0; i < comMax; i++) {
				if (computer[i].getIP() == ip) {
					if (computer[i].getCanNuke()) {
						canvas->input(ip + " : 해킹 성공");
						computer[i].nuke();
					}
					else canvas->input(ip + " : 해킹 실패");
					break;
				}
			}
		}
	}
	void cmd_unlock(string name, string pass = "") {
		if (currentFile == nullptr) { // 컴퓨터에서 in
			for (int i = 0; i < connectCom->getFileCount(); i++) {
				File* f = connectCom->getFile(i);
				if (f->getName() == name and f->getSecurity() == "private" and f->getPass() == pass) {
					f->setSecurity("public");
					canvas->input("잠금해제 완료");
				}
				else {
					canvas->input("비밀번호 틀림");
				}
			}
		}
		else { // 폴더에서 in
			for (int i = 0; i < currentFile->getFileCount(); i++) {
				File* f = currentFile->getFile(i);
				if (f->getName() == name and f->getSecurity() == "private" and f->getPass() == pass) {
					f->setSecurity("public");
					canvas->input("잠금해제 완료");
				}
				else {
					canvas->input("비밀번호 틀림");
				}
			}
		}
	}

	// 접속
	void cmd_connect(string ip = "")
	{
		for (int i = 0; i < comMax; i++) {
			if ((ip == "" or ip == "target") and computer[i].getIP() == targetCom->getIP()) { // IP를 안적었을때, target을 바로 적었을때
				if (!computer[i].getIsNuke()) canvas->input(targetCom->getIP() + " : 접속 실패");
				else {
					canvas->input(targetCom->getIP() + " : 접속 성공");
					connectCom = &computer[i];
					canvas->connectCom = &computer[i];
					break;
				}
			}
			else if (computer[i].getIP() == ip) {
				if (!computer[i].getIsNuke()) canvas->input(ip + " : 접속 실패");
				else {
					canvas->input(ip + " : 접속 성공");
					connectCom = &computer[i];
					canvas->connectCom = &computer[i];
					break;
				}
			}
		}
	}
	void cmd_disconnect()
	{
		connectCom = &computer[0];
		canvas->connectCom = &computer[0];
		canvas->currentFile = nullptr;
		canvas->currentFileType = "";
	}
	void cmd_in(string name) {
		if (currentFile == nullptr) { // 컴퓨터에서 in
			for (int i = 0; i < connectCom->getFileCount(); i++) {
				File* f = connectCom->getFile(i);
				if (f->getName() == name and f->getSecurity() == "public") {
					currentFile = f;
					canvas->currentFile = f;
					if (dynamic_cast<Folder*>(f)) canvas->currentFileType = "Folder";
					else if (dynamic_cast<txt*>(f)) canvas->currentFileType = "txt";
					else if (dynamic_cast<exe*>(f)) canvas->currentFileType = "exe";
				}
				else if (f->getName() == name and f->getSecurity() == "private") {
					canvas->input("파일이 잠겨있음");
				}
			}
		}
		else { // 폴더에서 in
			for (int i = 0; i < currentFile->getFileCount(); i++) {
				File* f = currentFile->getFile(i);
				if (f->getName() == name and f->getSecurity() == "public") {
					canvas->input(name + " " + f->getName());
					currentFile = f;
					canvas->currentFile = f;
					if (dynamic_cast<Folder*>(f)) canvas->currentFileType = "Folder";
					else if (dynamic_cast<txt*>(f)) canvas->currentFileType = "txt";
					else if (dynamic_cast<exe*>(f)) canvas->currentFileType = "exe";
				}
				else if (f->getName() == name and f->getSecurity() == "private") {
					canvas->input("파일이 잠겨있음");
				}
			}
		} 
		
	}
	void cmd_out() {
		if (currentFile != nullptr and currentFile->getParent() != nullptr) {
			currentFile = currentFile->getParent();
			canvas->currentFile = currentFile;
			if (dynamic_cast<Folder*>(currentFile)) canvas->currentFileType = "Folder";
			else if (dynamic_cast<txt*>(currentFile)) canvas->currentFileType = "txt";
			else if (dynamic_cast<exe*>(currentFile)) canvas->currentFileType = "exe";
		}
		else {
			currentFile = nullptr;
			canvas->currentFile = nullptr;
			canvas->currentFileType = "";
		}
	}
};
