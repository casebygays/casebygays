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
		else if (tokens[0] == "/nuke" and tokens.size() > 1) cmd_nuke(tokens[1]); // IP ��������
		else if (tokens[0] == "/nuke") cmd_nuke(); // IP ����������
		else if (tokens[0] == "/unlock" and tokens.size() > 2) cmd_unlock(tokens[1], tokens[2]);

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
		canvas->input("/shutdown				���� ����");
		canvas->input("/in [����]				���� ����");
		canvas->input("/out				�������� ���ư� (����Ʈ ������, ���������� ������ ��)");
		canvas->input("/scan				�ֺ� IP ��ĵ");
		canvas->input("/clear				�帣�� Ź clear");

		canvas->input("/unlock [����] [��й�ȣ]		��й�ȣ ����");
		canvas->input("/decoding [����]			��� ���� ��ȣȭ");
		canvas->input("/portscan [IP]			��Ʈ ���� Ȯ��");
		canvas->input("/crack ssh				22�� ��Ʈ ����");
		canvas->input("/crack ftp				21�� ��Ʈ ����");
		canvas->input("/crack smtp			25�� ��Ʈ ����");
		canvas->input("/crack http			80�� ��Ʈ ����");
		canvas->input("/nuke [IP]				PC ��ŷ");
		canvas->input("/connect [IP]			�ش� ��ǻ�� ����");
		canvas->input("/disconnect			���� ����");
		canvas->input("removelog				�α� ����");
	}
	void cmd_clear() { canvas->cmdClear(); }
	void cmd_addtxt(string name, string desc) {
		if (currentFile == nullptr or dynamic_cast<Folder*>(currentFile)) {
			File* f = new txt(File::fileId, "public", name, desc, true);
			if (currentFile != nullptr) { connectCom->add(currentFile, f); }
			else if (connectCom != nullptr) { connectCom->add(f); }
			File::files.push_back(f);
			File::fileId++;
			canvas->input("txt�� ������");
		}
		else {
			canvas->input("������ ������ �� ���� �����");
		}
	}
	void cmd_addexe(string name) {
		if (currentFile == nullptr or dynamic_cast<Folder*>(currentFile)) {
			File* f = new exe(File::fileId, "public", name, true);
			if (currentFile != nullptr) { connectCom->add(currentFile, f); }
			else if (connectCom != nullptr) { connectCom->add(f); }
			File::files.push_back(f);
			File::fileId++;
			canvas->input("exe�� ������");
		}
		else {
			canvas->input("������ ������ �� ���� �����");
		}
	}
	void cmd_addfolder(string name) {
		if (currentFile == nullptr or dynamic_cast<Folder*>(currentFile)) {
			File* f = new Folder(File::fileId, "public", name, true);
			if (currentFile != nullptr) { connectCom->add(currentFile, f); }
			else if (connectCom != nullptr) { connectCom->add(f); }
			File::files.push_back(f);
			File::fileId++;
			canvas->input("������ ������");
		}
		else {
			canvas->input("������ ������ �� ���� �����");
		}
	}
	void cmd_remove(string name) {
		if (currentFile != nullptr) { 
			for (int i = 0; i < currentFile->getFileCount(); i++) { // �������� ���� ��� ���� �˻�
				if (currentFile->getFile(i)->getName() == name) { // ���������� ������ �Է¹��� �̸��� ���� ������ ������,
					if (currentFile->getFile(i)->getCanRemove()) {
						int id = currentFile->getFile(i)->getId();
						connectCom->remove(id); // �������� ��ǻ���� remove�Լ��� ȣ��
						for (int j = 0; j < File::files.size(); j++) {						// files�� ��� ������ �˻�
							if (File::files[j]->getId() == id) { // ������ id�� ������
								delete File::files[j];											// ����
								File::files.erase(File::files.begin() + j);						// files�ȿ����� ����
							}
						}
						canvas->input("������ ���� ������");
					}
					else {
						canvas->input("���� �Ұ����� �����Դϴ�.");
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
						canvas->input("���� �Ұ����� �����Դϴ�.");
					}
				}
			}
		}
	}
	// ��ŷ
	void cmd_scan()
	{
		canvas->input(computer[1].getIP()); // �ӽ�
		for (int i = 0; i < 3; i++) {
			int com = 1 + rand() % (comMax - 1);
			canvas->input(computer[com].getIP());
		}
	}
	void cmd_portscan() {
		if (targetCom) {
			string s = "��Ʈ ����|";
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
			canvas->input("��� IP�� �������� ����");
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
	void cmd_unlock(string name, string pass = "") {
		if (currentFile == nullptr) { // ��ǻ�Ϳ��� in
			for (int i = 0; i < connectCom->getFileCount(); i++) {
				File* f = connectCom->getFile(i);
				if (f->getName() == name and f->getSecurity() == "private" and f->getPass() == pass) {
					f->setSecurity("public");
					canvas->input("������� �Ϸ�");
				}
				else {
					canvas->input("��й�ȣ Ʋ��");
				}
			}
		}
		else { // �������� in
			for (int i = 0; i < currentFile->getFileCount(); i++) {
				File* f = currentFile->getFile(i);
				if (f->getName() == name and f->getSecurity() == "private" and f->getPass() == pass) {
					f->setSecurity("public");
					canvas->input("������� �Ϸ�");
				}
				else {
					canvas->input("��й�ȣ Ʋ��");
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
				if (f->getName() == name and f->getSecurity() == "public") {
					currentFile = f;
					canvas->currentFile = f;
					if (dynamic_cast<Folder*>(f)) canvas->currentFileType = "Folder";
					else if (dynamic_cast<txt*>(f)) canvas->currentFileType = "txt";
					else if (dynamic_cast<exe*>(f)) canvas->currentFileType = "exe";
				}
				else if (f->getName() == name and f->getSecurity() == "private") {
					canvas->input("������ �������");
				}
			}
		}
		else { // �������� in
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
					canvas->input("������ �������");
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
