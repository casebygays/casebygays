#pragma once

class Command {
	Canvas* canvas;

	bool shutdown; // 게임 종료
public:
	Command(Canvas* c)
	{
		canvas = c;
		shutdown = false;
	}
	void checkCommand(const string& s)
	{
		istringstream iss(s);
		string token;
		vector<string> tokens;

		while (iss >> token) { tokens.push_back(token); }

			 if (tokens[0] == "/shutdown") cmd_shutdown();
		else if (tokens[0] == "/help") cmd_help();
	}
	bool getShutdown() { return shutdown; }

	void cmd_help()
	{
		canvas->input("/shutdown : 게임 종료");
		canvas->input("/help : 명령어 리스트 출력");
		canvas->input("/exit : 이전으로 돌아감 (사이트 나가기, 상위폴더로 나가기 등)");
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
	}
	void cmd_shutdown()
	{
		shutdown = true;
	}
};