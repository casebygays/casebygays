#pragma once
#include "Canvas.h"
#include "Computer.h"
#include "StructPack.h"
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;
// ����׿� bugconnect ���߿� ����� �� ������ ����
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
		else if (canvas->in_proxy) { // ���Ͻ� �̴ϰ���
			canvas->proxyChance -= 1;
			if (tokens[0] == to_string(canvas->proxyAnswer)) {
				canvas->in_proxy = false;
				Canvas::targetCom->portCrack("proxy", false);
				canvas->input("���Ͻ� ��ŷ ����");
			}
			else if (canvas->proxyChance == 0) {
				canvas->in_proxy = false;
				string s = "���Ͻ� ��ŷ ���� / ���� : ";
				s = s + to_string(canvas->proxyAnswer);
				canvas->input(s);
			}
		}
		else if (tokens[0] == "/shutdown") cmd_shutdown();
		else if (tokens[0] == "/save") cmd_savegame();
		else if (tokens[0] == "/load") cmd_loadgame();
		else if (tokens[0] == "/help") cmd_help();
		else if (tokens[0] == "/clear") cmd_clear();
		else if (tokens[0] == "/addtxt" and tokens.size() > 2) cmd_addtxt(tokens[1], tokens[2]);
		else if (tokens[0] == "/addexe" and tokens.size() > 3) cmd_addexe(tokens[1], tokens[2]);
		else if (tokens[0] == "/addfolder") cmd_addfolder(tokens[1]);
		else if (tokens[0] == "/remove") cmd_remove(tokens[1]);

		else if (tokens[0] == "/scan") cmd_scan();
		else if (tokens[0] == "/portscan") cmd_portscan();
		else if (tokens[0] == "/target" and tokens.size() > 1) cmd_target(tokens[1]);
		else if (tokens[0] == "/crack" and tokens.size() > 1) cmd_crack(tokens[1]);
		else if (tokens[0] == "/nuke" and tokens.size() > 1) cmd_nuke(tokens[1]); // IP ��������
		else if (tokens[0] == "/nuke") cmd_nuke(); // IP ����������
		else if (tokens[0] == "/unlock" and tokens.size() > 2) cmd_unlock(tokens[1], tokens[2]);

		else if (tokens[0] == "/debugconnect" and tokens.size() > 1) cmd_debugconnect(tokens[1]);
		else if (tokens[0] == "/connect" and tokens.size() > 1) cmd_connect(tokens[1]); // IP ��������
		else if (tokens[0] == "/connect") cmd_connect(); // IP ����������
		else if (tokens[0] == "/disconnect") cmd_disconnect();
		else if (tokens[0] == "/in" and tokens.size() > 1) cmd_in(tokens[1]);
		else if (tokens[0] == "/out") cmd_out();
	}
	File* getCurrentFile() { return Canvas::currentFile; }
	bool getShutdown() { return shutdown; }
	void addAlertLevel(int value) {
		if (Canvas::connectCom->getIP() != "127.0.0.1" or Canvas::targetCom != nullptr)
			Canvas::alertLevel += value;
		if (Canvas::alertLevel >= 100) {
			// �߰����� 100�� �Ǹ� �������� ��ǻ�Ϳ��� ƨ��, +������ ��ȭ�Ǵ°� �־ ������
		}
	}
	void cmd_shutdown() { shutdown = true; }
	void cmd_savegame() {
		ofstream file("Save.txt");
		if (file.is_open()) {
			for (int i = 0; i < File::files.size(); i++) {
				file << "id=" << File::files[i]->getId() << '\n';
				if (File::files[i]->getParent() == nullptr) 
					file << "parentID=" << -1 << '\n';
				else 
					file << "parentID=" << File::files[i]->getParent()->getId() << '\n';
				file << "icon=" << File::files[i]->getIcon() << '\n';
				file << "name=" << File::files[i]->getName() << '\n';
				file << "securityType=" << File::files[i]->getSecurity() << '\n';
				file << "pass=" << File::files[i]->getPass() << '\n';
				file << "visible=" << File::files[i]->getVisible() << '\n';
				file << "canRemove=" << File::files[i]->getCanRemove() << '\n';
				file << "oneshot=" << File::files[i]->getOneshot() << '\n';
				if (dynamic_cast<txt*>(File::files[i])) {
					file << "desc=" << dynamic_cast<txt*>(File::files[i])->getDesc() << '\n';
					file << "fileType=" << "txt" << '\n';
				}
				else if (dynamic_cast<exe*>(File::files[i])) {
					file << "code=" << dynamic_cast<exe*>(File::files[i])->getCode() << '\n';
					file << "fileType=" << "exe" << '\n';
				}
				else if (dynamic_cast<Folder*>(File::files[i])) {
					file << "fileType=" << "Folder" << '\n';
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
		}
		
		canvas->input(to_string(computer[0].getFileCount()));
	}
	void cmd_loadgame() {
		ifstream file("Save.txt");
		string line;

		S_Computer comData;
		S_File fileData;
		int comIndex = 0; // com�� index
		for (File* f : File::files) { delete f; } // ��� ���� ����
		File::files.clear();

		while (getline(file, line)) {
			size_t sep = line.find('=');
			if (sep == string::npos) continue;

			string key = line.substr(0, sep);
			string value = line.substr(sep + 1);
			// ����
			if (key == "id") { fileData.id = stoi(value); }
			else if (key == "parentID") { fileData.parentID = stoi(value); }
			else if (key == "icon") { fileData.icon = value; }
			else if (key == "name") { fileData.name = value; }
			else if (key == "securityType") { fileData.securityType = value; }
			else if (key == "pass") { fileData.pass = value; }
			else if (key == "visible") { fileData.visible = stoi(value); }
			else if (key == "canRemove") { fileData.canRemove = stoi(value); }
			else if (key == "oneshot") { fileData.canRemove = stoi(value); }
			else if (key == "desc") { fileData.desc = value; }
			else if (key == "code") { fileData.code = value; }
			else if (key == "fileType") { 
				if (value == "txt") File::files.push_back(new txt(fileData));
				else if (value == "exe") File::files.push_back(new exe(fileData));
				else if (value == "Folder") File::files.push_back(new Folder(fileData)); 
			}

			else if (key == "IP") {
				comData.IP = value;
			}
			else if (key == "level") { comData.level = stoi(value); }
			else if (key == "ssh") { comData.ssh = stoi(value); }
			else if (key == "ftp") { comData.ftp = stoi(value); }
			else if (key == "smtp") { comData.smtp = stoi(value); }
			else if (key == "http") { comData.http = stoi(value); }
			else if (key == "is_nuke") { comData.is_nuke = stoi(value); }
			else if (key == "childFiles") {
				computer[comIndex].childFileClear();

				size_t start = value.find('[');
				size_t end = value.find(']');

				if (start != string::npos && end != string::npos && end > start) {
					string numbers = value.substr(start + 1, end - start - 1);
					stringstream ss(numbers);
					string token;
					while (getline(ss, token, ',')) {
						for (File* f : File::files) {
							if (f->getId() == stoi(token)) computer[comIndex].add(f);
						}
					}
				}
				comIndex++;
			}
			if (key == "connectComIP") { 
				for (int i = 0; i < comMax; i++)
					if (computer[i].getIP() == value)
						Canvas::connectCom = &computer[i];
			}
			else if (key == "currentFileID") {
				for (int i = 0; i < File::files.size(); i++) {
					if (File::files[i]->getId() == stoi(value))
						Canvas::currentFile = File::files[i];
					canvas->input(to_string(Canvas::currentFile->getId()));
				}
			}
		}
		canvas->input(Canvas::connectCom->getIP());
		canvas->input(Canvas::currentFile->getName());
		file.close();
		//canvas->input(to_string(computer[0].getFileCount()));
	}
	void cmd_help()
	{
		canvas->input("--------------------------------------------------------");
		canvas->input("��� : () = ����,	[] = �ʼ�");
		canvas->input("/shutdown				���� ����");
		canvas->input("/in [����]				���� ����");
		canvas->input("/out				�������� ���ư� (���������� ������)");
		canvas->input("/clear				�帣�� Ź clear");
		canvas->input("/unlock [����] [��й�ȣ]		��й�ȣ ����");
		canvas->input("/scan				�ֺ� IP ��ĵ");
		canvas->input("/target [IP]				�ֺ� IP ��ĵ");
		//canvas->input("/decoding [����]			��� ���� ��ȣȭ");
		canvas->input("/portscan				��Ʈ ���� Ȯ��");
		canvas->input("/crack ssh				22�� ��Ʈ ����");
		canvas->input("/crack ftp				21�� ��Ʈ ����");
		canvas->input("/crack smtp			25�� ��Ʈ ����");
		canvas->input("/crack http			80�� ��Ʈ ����");
		canvas->input("/crack proxy			proxy ��Ȱ��ȭ");
		canvas->input("/crack firewall			friewall ��Ȱ��ȭ");
		canvas->input("/nuke (IP)					PC ��ŷ");
		canvas->input("/connect	(IP)			�ش� ��ǻ�� ����");
		canvas->input("/disconnect			���� ����");
		canvas->input("--------------------------------------------------------");
		//canvas->input("/removelog				�α� ����");
	}
	void cmd_clear() { canvas->cmdClear(); }
	void cmd_addtxt(string name, string desc) {
		if (Canvas::currentFile == nullptr or dynamic_cast<Folder*>(Canvas::currentFile)) {
			File* f = new txt(File::fileId, "public", name, desc, true, true, false);
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
	void cmd_addexe(string name, string code) {
		if (Canvas::currentFile == nullptr or dynamic_cast<Folder*>(Canvas::currentFile)) {
			File* f = new exe(File::fileId, "public", name, code, true, true, false);
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
			File* f = new Folder(File::fileId, "public", name, true, true, false);
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
			if (Canvas::targetCom->getPort("ssh")) s += "ssh : ���|";
			else s += "ssh : ����|";
			if (Canvas::targetCom->getPort("ftp")) s += "ftp : ���|";
			else s += "ftp : ����|";
			if (Canvas::targetCom->getPort("smtp")) s += "smtp : ���|";
			else s += "smtp : ����|";
			if (Canvas::targetCom->getPort("http")) s += "http : ���|";
			else s += "http : ����|";
			if (Canvas::targetCom->getPort("proxy")) s += "proxy : ���|";
			else s += "proxy : ����|";
			if (Canvas::targetCom->getPort("firewall")) s += "firewall : ���|";
			else s += "firewall : ����|";
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
		if (target == "proxy" and Canvas::targetCom->getPort("proxy")) {
			canvas->in_proxy = true;
			canvas->proxyAnswer = rand() % 5 + 1;
			canvas->proxyChance = 2;
			addAlertLevel(3);
		}
		else if (Canvas::targetCom->portCrack(target, false)) {
			canvas->input(target + " : ���������� ��Ʈ�� ��");
			addAlertLevel(4);
		}
		else if (Canvas::targetCom == nullptr) {
			canvas->input("��ŷ ����� �����ϴ�.");
		}
		else {
			canvas->input(target + " : ��Ʈ�� �����ְų�, ����� ã�� ����");
			addAlertLevel(2);
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
	void cmd_debugconnect(string id = "") { // ����׿�
		int a = stoi(id);
		Canvas::connectCom = &computer[a];
		Canvas::currentFile = nullptr;
		canvas->input(Canvas::connectCom->getIP() + " : ���� ����");
	}
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
			for (int i = 0; i < Canvas::connectCom->getFileCount(); i++) {  //���� ã��
				File* f = Canvas::connectCom->getFile(i);
				if (f->getName() == name and f->getSecurity() == "public") {
					if (dynamic_cast<Folder*>(f)) {
						Canvas::currentFile = f;
						Canvas::getFileType(f, "Folder");
					}
					else if (dynamic_cast<txt*>(f)) {
						Canvas::currentFile = f;
						Canvas::getFileType(f, "txt");
					}
					else if (dynamic_cast<exe*>(f)) {
						exe* e = dynamic_cast<exe*>(f);
						vector<string> code = e->runCode();
						for (int i = 0; i < code.size(); i++)
							checkCommand(code[i]);
						if (e->getOneshot()) { checkCommand("/remove " + e->getName()); }
					}
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
					if (dynamic_cast<Folder*>(f)) {
						Canvas::currentFile = f;
						Canvas::getFileType(f, "Folder");
					}
					else if (dynamic_cast<txt*>(f)) {
						Canvas::currentFile = f;
						Canvas::getFileType(f, "txt");
					}
					else if (dynamic_cast<exe*>(f)) {
						exe* e = dynamic_cast<exe*>(f);
						vector<string> code = e->runCode();
						for (int i = 0; i < code.size(); i++)
							checkCommand(code[i]);
						if (e->getOneshot()) { checkCommand("/remove " + e->getName()); }
					}
				}
				else if (f->getName() == name and f->getSecurity() == "private") {
					canvas->input("������ �������");
				}
			}
		} 
		
	}
	void cmd_out() {
		if (Canvas::currentFile != nullptr and Canvas::currentFile->getParent() != nullptr) {
			string fileName = "@#$&*()#";
			if (Canvas::currentFile->getOneshot()) fileName = Canvas::currentFile->getName();
			Canvas::currentFile = Canvas::currentFile->getParent();
			if (dynamic_cast<Folder*>(Canvas::currentFile)) Canvas::getFileType(Canvas::currentFile, "Folder");
			else if (dynamic_cast<txt*>(Canvas::currentFile)) Canvas::getFileType(Canvas::currentFile, "txt");
			else if (dynamic_cast<exe*>(Canvas::currentFile)) Canvas::getFileType(Canvas::currentFile, "exe");
			checkCommand("/remove " + fileName);
		}
		else {
			string fileName = "@#&$(*@#&()";
			if (Canvas::currentFile->getOneshot()) fileName = Canvas::currentFile->getName();
			Canvas::currentFile = nullptr;
			checkCommand("/remove " + fileName);
		}
	}
};
