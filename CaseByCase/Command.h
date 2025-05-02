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

		else if (tokens[0] == "/scan") cmd_scan();
		else if (tokens[0] == "/portscan") cmd_portscan();
		else if (tokens[0] == "/target" and tokens.size() > 1) cmd_target(tokens[1]);
		else if (tokens[0] == "/crack" and tokens.size() > 1) cmd_crack(tokens[1]);
		else if (tokens[0] == "/nuke" and tokens.size() > 1) cmd_nuke(tokens[1]); // IP 적었을때
		else if (tokens[0] == "/nuke") cmd_nuke(); // IP 안적었을때

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
		canvas->input("/help		명령어 리스트 출력");
		canvas->input("/shutdown		게임 종료");
		canvas->input("/in File		파일 열기");
		canvas->input("/out			이전으로 돌아감 (사이트 나가기, 상위폴더로 나가기 등)");
		canvas->input("/scan		주변 IP 스캔");
		canvas->input("/clear		드르륵 탁 clear");

		canvas->input("/decoding File	대상 파일 복호화");
		canvas->input("/portscan IP		포트 정보 확인");
		canvas->input("/crack ssh		22번 포트 열기");
		canvas->input("/crack ftp		21번 포트 열기");
		canvas->input("/crack smtp		25번 포트 열기");
		canvas->input("/crack http		80번 포트 열기");
		canvas->input("/nuke IP		PC 해킹");
		canvas->input("/connect IP		해당 컴퓨터 접속");
		canvas->input("/disconnect		접속 종료");
		canvas->input("removelog		로그 삭제");
	}
	void cmd_clear() { canvas->cmdClear(); }

	// 해킹
	void cmd_scan()
	{
		canvas->input(computer[1].getIP()); // 임시
		for (int i = 0; i < 3; i++) {
			int com = 1 + rand() % comMax - 1;
			canvas->input(computer[com].getIP());
		}
	}
	void cmd_portscan() {
		if (targetCom) {
			string s = "포트 정보|";
			if (targetCom->getPort("ssh")) s = s + "ssh : O|";
			else s = s + "ssh : X|";
			if (targetCom->getPort("ftp")) s = s + "ftp : O|";
			else s = s + "ftp : X|";
			if (targetCom->getPort("smt")) s = s + "smt : O|";
			else s = s + "smt : X|";
			if (targetCom->getPort("http")) s = s + "http : O|";
			else s = s + "http : X|";
			
			canvas->input(s);
		}
		else {

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
				if (name == f->getName()) {
					currentFile = f;
					canvas->currentFile = f;
					if (dynamic_cast<Folder*>(f)) canvas->currentFileType = "Folder";
					else if (dynamic_cast<txt*>(f)) canvas->currentFileType = "txt";
					else if (dynamic_cast<exe*>(f)) canvas->currentFileType = "exe";
				}
			}
		}
		else { // 폴더에서 in
			for (int i = 0; i < currentFile->getFileCount(); i++) {
				File* f = currentFile->getFile(i);
				if (name == f->getName()) {
					canvas->input(name + " " + f->getName());
					currentFile = f;
					canvas->currentFile = f;
					if (dynamic_cast<Folder*>(f)) canvas->currentFileType = "Folder";
					else if (dynamic_cast<txt*>(f)) canvas->currentFileType = "txt";
					else if (dynamic_cast<exe*>(f)) canvas->currentFileType = "exe";
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
