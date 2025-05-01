#pragma once
#include "Canvas.h"
#include "Computer.h"
#include <string>
#include <sstream>
#include <vector>
using namespace std;

class Command {
	Canvas* canvas;

	Computer* computer;
	int comMax;
	Computer* connectCom; // 접속한 컴퓨터
	File* currentFile; // 현재 파일
	File* prevFile; // 이전 파일

	bool shutdown; // 게임 종료
public:
	Command(Canvas* c, Computer* com, int cM)
	{
		canvas = c;
		computer = com;
		comMax = cM;
		connectCom = nullptr;
		currentFile = nullptr;
		prevFile = nullptr;
		shutdown = false;
	}
	void checkCommand(const string& s)
	{
		istringstream iss(s);
		string token;
		vector<string> tokens;

		while (iss >> token) { tokens.push_back(token); }

		if (tokens.empty()) { return; }
		else if (tokens[0] == "/shutdown") cmd_shutdown();
		else if (tokens[0] == "/help") cmd_help();
		else if (tokens[0] == "/connect") cmd_connect(tokens[1]);
		else if (tokens[0] == "/scan") cmd_scan();
		else if (tokens[0] == "/clear") cmd_clear();
		else if (tokens[0] == "/in") cmd_in(tokens[1]);
		else if (tokens[0] == "/out") cmd_out();
	}
	File* getCurrentFile() { return currentFile; }
	bool getShutdown() { return shutdown; }

	void cmd_help()
	{
		canvas->input("/help : 명령어 리스트 출력");
		canvas->input("/shutdown : 게임 종료");
		canvas->input("/in");
		canvas->input("/out : 이전으로 돌아감 (사이트 나가기, 상위폴더로 나가기 등)");
		canvas->input("/decoding 파일이름: 대상 파일 복호화");
		canvas->input("/scan : 주변 IP 스캔");
		canvas->input("/portscan IP : 포트 정보 확인");
		canvas->input("/sshcrack : 22번 포트 열기");
		canvas->input("/ftpcrack : 21번 포트 열기");
		canvas->input("/smtpcrack : 25번 포트 열기");
		canvas->input("/httpworm : 80번 포트 열기");
		canvas->input("/connect IP : 해당 컴퓨터 접속");
		canvas->input("/disconnect : 접속 종료");
		canvas->input("/nuke IP : 완전 해킹");
		canvas->input("rmlog : 로그 삭제");
		canvas->input("/clear : drrrr tak clear");
	}
	void cmd_shutdown()
	{
		shutdown = true;
	}
	void cmd_scan()
	{
		canvas->input(computer[0].getIP()); // 임시
		for (int i = 0; i < 3; i++) {
			int com = rand() % comMax;
			canvas->input(computer[com].getIP());
		}
	}
	void cmd_connect(string ip)
	{
		for (int i = 0; i < comMax; i++) {
			if (computer[i].getIP() == ip) {
				canvas->input(ip + " connected");
				connectCom = &computer[i];
				canvas->connectCom = &computer[i];
				break;
			}
		}
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
		if (currentFile->getParent() != nullptr) {
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
	void cmd_clear() {
		canvas->cmdClear();
	}
};
