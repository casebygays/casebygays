#pragma once
#include "Computer.h"

class Command {
	Canvas* canvas;

	Computer* computer;
	int comMax;
	Computer* connectCom;
	Folder* currentFolder;

	bool shutdown; // ���� ����
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
		canvas->input("/help : ��ɾ� ����Ʈ ���");
		canvas->input("/shutdown : ���� ����");
		canvas->input("/in");
		canvas->input("/out : �������� ���ư� (����Ʈ ������, ���������� ������ ��)");
		canvas->input("/decoding �����̸�: ��� ���� ��ȣȭ");
		canvas->input("/scan : �ֺ� IP ��ĵ");
		canvas->input("/portscan IP : ��Ʈ ���� Ȯ��");
		canvas->input("/sshcrack : 22�� ��Ʈ ����");
		canvas->input("/ftpcrack : 21�� ��Ʈ ����");
		canvas->input("/smtpcrack : 25�� ��Ʈ ����");
		canvas->input("/httpworm : 80�� ��Ʈ ����");
		canvas->input("/connect IP : �ش� ��ǻ�� ����");
		canvas->input("/disconnect : ���� ����");
		canvas->input("/nuke IP : ���� ��ŷ");
		canvas->input("rmlog : �α� ����");
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