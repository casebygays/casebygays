#pragma once
#include "Computer.h"

class Command {
	Canvas* canvas;

	Computer* computer;
	int comMax;
	Computer* connectCom;
	Folder* currentFolder;

	bool shutdown; // 게임 종료
public:
	Command(Canvas* c, Computer* com, int cM)
	{
		canvas = c;
		computer = com;
		comMax = cM;
		connectCom = nullptr;
		currentFolder = nullptr;
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
	}
	Folder* getCurrentFolder() { return currentFolder; }
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
				break;
			}
		}
	}
	void cmd_in(string name) {
		if (currentFolder != nullptr) {

		}
		else {
			for (int i = 0; i < connectCom->getFileCount(); i++) {
				if (name == connectCom->getFile(i)->getName()) {
					currentFolder = connectCom->getFile(i);
					break;
				}
			}
		}
	}
	void cmd_clear()
	{
		canvas->cmdClear();
	}
};