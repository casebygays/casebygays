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
	Computer* connectCom; // ������ ��ǻ��
	File* currentFile; // ���� ����
	File* prevFile; // ���� ����

	bool shutdown; // ���� ����
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
		canvas->input(computer[0].getIP()); // �ӽ�
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
		if (currentFile == nullptr) { // ��ǻ�Ϳ��� in
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
		else { // �������� in
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
