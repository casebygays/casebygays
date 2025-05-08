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
	bool shutdown; // ���� ����
public:
	Command(Canvas* c, Computer* com, int cM)
	{
		canvas = c;
		computer = com;
		comMax = cM;
		shutdown = false;
	}
	void save() {}
	void load() {}
	void checkCommand(const string& s)
	{
		istringstream iss(s);
		string token;
		vector<string> tokens;
		while (iss >> token) { tokens.push_back(token); }

		if (tokens.empty()) { return; }
		else if (canvas->in_proxy) {
			canvas->proxyChance -= 1;
			canvas->proxyInput.push_back(stoi(tokens[0]));

			if (canvas->proxyChance == 0) {
				canvas->in_proxy = false;
				canvas->proxyInput.clear();
				string s = "���Ͻ� ��ŷ ���� / ���� : ";
				s = s + to_string(canvas->proxyAnswer);
				canvas->input(s);
				return;
			}
		}
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
	File* getCurrentFile() { return Canvas::currentFile; }
	bool getShutdown() { return shutdown; }
	
	
	void cmd_shutdown() { shutdown = true; }
	void cmd_savegame() {
		ofstream file("Save.txt");
		if (file.is_open()) {
			for (int i = 0; i < File::files.size(); i++) {
				file << "id=" << File::files[i]->getId() << '\n';
				file << "icon=" << File::files[i]->getIcon() << '\n';
				file << "name=" << File::files[i]->getName() << '\n';
				file << "securityType=" << File::files[i]->getSecurity() << '\n';
				file << "pass=" << File::files[i]->getPass() << '\n';
				file << "canRemove=" << File::files[i]->getCanRemove() << '\n';
				if (dynamic_cast<txt*>(File::files[i])) {
					file << "desc=" << dynamic_cast<txt*>(File::files[i])->getDesc() << '\n';;
				}
				else if (dynamic_cast<exe*>(File::files[i])) {
				}
				else if (dynamic_cast<Folder*>(File::files[i])) {
					Folder* f = dynamic_cast<Folder*>(File::files[i]);
					int* p = f->getChildId();
					file << "childFiles=[";
					for (int j = 0; j < f->getFileCount(); j++) {
						file << p[j];
						if (j < f->getFileCount() - 1)
							file << ",";
					}
					file << "]\n";
					delete p;
				}
			}
			for (int i = 0; i < 80; i++) {
				file << "IP=" << computer[i].getIP() << '\n';
				file << "level=" << computer[i].getLevel() << '\n';
				file << "ssh=" << computer[i].getPort("ssh") << '\n';
				file << "ftp=" << computer[i].getPort("ftp") << '\n';
				file << "smtp=" << computer[i].getPort("smtp") << '\n';
				file << "http=" << computer[i].getPort("http") << '\n';
				file << "proxy=" << computer[i].getPort("proxy") << '\n';
				file << "firewall=" << computer[i].getPort("firwall") << '\n';
				file << "isNuke=" << computer[i].getIsNuke() << '\n';
				file << "childFiles=[";
				for (int j = 0; j < computer[i].getFileCount(); j++) {
					file << computer[i].getFile(j)->getId();
					if (j < computer[i].getFileCount() - 1)
						file << ",";
				}
				file << "]\n";
			}
			for (int i = 0; i < canvas->getCMDSize(); i++) {
				file << "cmd=" << canvas->getCMDText(i) << '\n';
			}
			file << "lastText=" << canvas->getLastText() << '\n';
			file << "connectComIP=" << Canvas::connectCom->getIP() << '\n';
			if (Canvas::currentFile != nullptr) file << "currentFileID=" << Canvas::currentFile->getId() << '\n';

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
		if (Canvas::currentFile == nullptr or dynamic_cast<Folder*>(Canvas::currentFile)) {
			File* f = new txt(File::fileId, "public", name, desc, true);
			if (Canvas::currentFile != nullptr) { Canvas::connectCom->add(Canvas::currentFile, f); }
			else if (Canvas::connectCom != nullptr) { Canvas::connectCom->add(f); }
			File::files.push_back(f);
			File::fileId++;
			canvas->input("txt�� ������");
		}
		else {
			canvas->input("������ ������ �� ���� �����");
		}
	}
	void cmd_addexe(string name) {
		if (Canvas::currentFile == nullptr or dynamic_cast<Folder*>(Canvas::currentFile)) {
			File* f = new exe(File::fileId, "public", name, true);
			if (Canvas::currentFile != nullptr) { Canvas::connectCom->add(Canvas::currentFile, f); }
			else if (Canvas::connectCom != nullptr) { Canvas::connectCom->add(f); }
			File::files.push_back(f);
			File::fileId++;
			canvas->input("exe�� ������");
		}
		else {
			canvas->input("������ ������ �� ���� �����");
		}
	}
	void cmd_addfolder(string name) {
		if (Canvas::currentFile == nullptr or dynamic_cast<Folder*>(Canvas::currentFile)) {
			File* f = new Folder(File::fileId, "public", name, true);
			if (Canvas::currentFile != nullptr) { Canvas::connectCom->add(Canvas::currentFile, f); }
			else if (Canvas::connectCom != nullptr) { Canvas::connectCom->add(f); }
			File::files.push_back(f);
			File::fileId++;
			canvas->input("������ ������");
		}
		else {
			canvas->input("������ ������ �� ���� �����");
		}
	}
	void cmd_remove(string name) {
		if (Canvas::currentFile != nullptr) { 
			for (int i = 0; i < Canvas::currentFile->getFileCount(); i++) { // �������� ���� ��� ���� �˻�
				if (Canvas::currentFile->getFile(i)->getName() == name) { // ���������� ������ �Է¹��� �̸��� ���� ������ ������,
					if (Canvas::currentFile->getFile(i)->getCanRemove()) {
						int id = Canvas::currentFile->getFile(i)->getId();
						Canvas::connectCom->remove(id); // �������� ��ǻ���� remove�Լ��� ȣ��
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
		else if (Canvas::connectCom != nullptr) {
			for (int i = 0; i < Canvas::connectCom->getFileCount(); i++) {
				if (Canvas::connectCom->getFile(i)->getName() == name) {
					if (Canvas::connectCom->getFile(i)->getCanRemove()) {
						int id = Canvas::connectCom->getFile(i)->getId();
						Canvas::connectCom->remove(id);
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
		if (Canvas::targetCom) {
			string s = "��Ʈ ����|";
			if (Canvas::targetCom->getPort("ssh")) s += "ssh : O|";
			else s += "ssh : X|";
			if (Canvas::targetCom->getPort("ftp")) s += "ftp : O|";
			else s += "ftp : X|";
			if (Canvas::targetCom->getPort("smtp")) s += "smt : O|";
			else s += "smt : X|";
			if (Canvas::targetCom->getPort("http")) s += "http : O|";
			else s += "http : X|";
			if (Canvas::targetCom->getPort("proxy")) s += "proxy : O|";
			else s += "proxy : X|";
			if (Canvas::targetCom->getPort("firewall")) s += "firewall : O|";
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
				Canvas::targetCom = &computer[i];
				break;
			}
		}
	}
	void cmd_crack(string target) { 
		if (Canvas::targetCom == nullptr) { canvas->input("��ŷ ����� �����ϴ�."); }
		else {
			if (target == "proxy") {
				canvas->in_proxy = true;
				canvas->proxyAnswer = rand() % 10;
				canvas->proxyChance = 3;
			}
			else if (Canvas::targetCom->portCrack(target, false)) 
				canvas->input(target + " : ���������� ��Ʈ�� ��");
			else 
				canvas->input(target + " : ��Ʈ�� �����ְų�, ����� ã������");
		}

		
	}
	void cmd_nuke(string ip = "") {
		if (ip == "" and Canvas::targetCom != nullptr) {
			if (Canvas::targetCom->getCanNuke()) {
				Canvas::targetCom->nuke();
				canvas->input(Canvas::targetCom->getIP() + " : ��ŷ ����");
			}
			else {
				canvas->input(Canvas::targetCom->getIP() + " : ��ŷ ����");
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
		if (Canvas::currentFile == nullptr) { // ��ǻ�Ϳ��� in
			for (int i = 0; i < Canvas::connectCom->getFileCount(); i++) {
				File* f = Canvas::connectCom->getFile(i);
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
			for (int i = 0; i < Canvas::currentFile->getFileCount(); i++) {
				File* f = Canvas::currentFile->getFile(i);
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
			if ((ip == "" or ip == "target") and computer[i].getIP() == Canvas::targetCom->getIP()) { // IP�� ����������, target�� �ٷ� ��������
				if (!computer[i].getIsNuke()) canvas->input(Canvas::targetCom->getIP() + " : ���� ����");
				else {
					canvas->input(Canvas::targetCom->getIP() + " : ���� ����");
					Canvas::connectCom = &computer[i];
					Canvas::currentFile = nullptr;
					break;
				}
			}
			else if (computer[i].getIP() == ip) {
				if (!computer[i].getIsNuke()) canvas->input(ip + " : ���� ����");
				else {
					canvas->input(ip + " : ���� ����");
					Canvas::connectCom = &computer[i];
					Canvas::currentFile = nullptr;
					break;
				}
			}
		}
	}
	void cmd_disconnect()
	{
		Canvas::connectCom = &computer[0];
		Canvas::currentFile = nullptr;
	}
	void cmd_in(string name) {
		if (Canvas::currentFile == nullptr) { // ��ǻ�Ϳ��� in
			for (int i = 0; i < Canvas::connectCom->getFileCount(); i++) {
				File* f = Canvas::connectCom->getFile(i);
				if (f->getName() == name and f->getSecurity() == "public") {
					Canvas::currentFile = f;
					if (dynamic_cast<Folder*>(f)) Canvas::getFileType(f, "Folder");
					else if (dynamic_cast<txt*>(f)) Canvas::getFileType(f, "txt");
					else if (dynamic_cast<exe*>(f)) Canvas::getFileType(f, "exe");
				}
				else if (f->getName() == name and f->getSecurity() == "private") {
					canvas->input("������ �������");
				}
			}
		}
		else { // �������� in
			for (int i = 0; i < Canvas::currentFile->getFileCount(); i++) {
				File* f = Canvas::currentFile->getFile(i);
				if (f->getName() == name and f->getSecurity() == "public") {
					canvas->input(name + " " + f->getName());
					Canvas::currentFile = f;
					if (dynamic_cast<Folder*>(f)) Canvas::getFileType(f, "Folder");
					else if (dynamic_cast<txt*>(f)) Canvas::getFileType(f, "txt");
					else if (dynamic_cast<exe*>(f)) Canvas::getFileType(f, "exe");
				}
				else if (f->getName() == name and f->getSecurity() == "private") {
					canvas->input("������ �������");
				}
			}
		} 
		
	}
	void cmd_out() {
		if (Canvas::currentFile != nullptr and Canvas::currentFile->getParent() != nullptr) {
			Canvas::currentFile = Canvas::currentFile->getParent();
			if (dynamic_cast<Folder*>(Canvas::currentFile)) Canvas::getFileType(Canvas::currentFile, "Folder");
			else if (dynamic_cast<txt*>(Canvas::currentFile)) Canvas::getFileType(Canvas::currentFile, "txt");
			else if (dynamic_cast<exe*>(Canvas::currentFile)) Canvas::getFileType(Canvas::currentFile, "exe");
		}
		else {
			Canvas::currentFile = nullptr;
		}
	}
};
