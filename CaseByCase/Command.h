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
	Computer* targetCom; //Ÿ���� ��ǻ��
	Computer* connectCom; // ������ ��ǻ��
	File* currentFile; // ���� ����

	bool shutdown; // ���� ����
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
		else if (tokens[0] == "/nuke" and tokens.size() > 1) cmd_nuke(tokens[1]); // IP ��������
		else if (tokens[0] == "/nuke") cmd_nuke(); // IP ����������

		else if (tokens[0] == "/connect" and tokens.size() > 1) cmd_connect(tokens[1]); // IP ��������
		else if (tokens[0] == "/connect") cmd_connect(); // IP ����������
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
			cout << "���� �Ϸ�!" << endl;
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
		canvas->input("/help		��ɾ� ����Ʈ ���");
		canvas->input("/shutdown		���� ����");
		canvas->input("/in File		���� ����");
		canvas->input("/out			�������� ���ư� (����Ʈ ������, ���������� ������ ��)");
		canvas->input("/scan		�ֺ� IP ��ĵ");
		canvas->input("/clear		�帣�� Ź clear");

		canvas->input("/decoding File	��� ���� ��ȣȭ");
		canvas->input("/portscan IP		��Ʈ ���� Ȯ��");
		canvas->input("/crack ssh		22�� ��Ʈ ����");
		canvas->input("/crack ftp		21�� ��Ʈ ����");
		canvas->input("/crack smtp		25�� ��Ʈ ����");
		canvas->input("/crack http		80�� ��Ʈ ����");
		canvas->input("/nuke IP		PC ��ŷ");
		canvas->input("/connect IP		�ش� ��ǻ�� ����");
		canvas->input("/disconnect		���� ����");
		canvas->input("removelog		�α� ����");
	}
	void cmd_clear() { canvas->cmdClear(); }

	// ��ŷ
	void cmd_scan()
	{
		canvas->input(computer[1].getIP()); // �ӽ�
		for (int i = 0; i < 3; i++) {
			int com = 1 + rand() % comMax - 1;
			canvas->input(computer[com].getIP());
		}
	}
	void cmd_portscan() {
		if (targetCom) {
			string s = "��Ʈ ����|";
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
				canvas->input(ip + " : ��ǥ�� ������");
				targetCom = &computer[i];
				break;
			}
		}
	}
	void cmd_crack(string target) { 
		if (targetCom != nullptr)
		{
			if (targetCom->portCrack(target, false)) canvas->input(target + " : ���������� ��Ʈ�� ��");
			else canvas->input(target + " : ��Ʈ�� �����ְų�, ����� ã������");
		}
	}
	void cmd_nuke(string ip = "") {
		if (ip == "" and targetCom != nullptr) {
			if (targetCom->getCanNuke()) {
				targetCom->nuke();
				canvas->input(targetCom->getIP() + " : ��ŷ ����");
			}
			else {
				canvas->input(targetCom->getIP() + " : ��ŷ ����");
			}
		}
		else {
			for (int i = 0; i < comMax; i++) {
				if (computer[i].getIP() == ip) {
					if (computer[i].getCanNuke()) {
						canvas->input(ip + " : ��ŷ ����");
						computer[i].nuke();
					}
					else canvas->input(ip + " : ��ŷ ����");
					break;
				}
			}
		}
	}

	// ����
	void cmd_connect(string ip = "")
	{
		for (int i = 0; i < comMax; i++) {
			if ((ip == "" or ip == "target") and computer[i].getIP() == targetCom->getIP()) { // IP�� ����������, target�� �ٷ� ��������
				if (!computer[i].getIsNuke()) canvas->input(targetCom->getIP() + " : ���� ����");
				else {
					canvas->input(targetCom->getIP() + " : ���� ����");
					connectCom = &computer[i];
					canvas->connectCom = &computer[i];
					break;
				}
			}
			else if (computer[i].getIP() == ip) {
				if (!computer[i].getIsNuke()) canvas->input(ip + " : ���� ����");
				else {
					canvas->input(ip + " : ���� ����");
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
