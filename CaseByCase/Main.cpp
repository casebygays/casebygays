#pragma once
#include "Canvas.h"
#include "Computer.h"
#include "File.h"
#include "Command.h"
#include "StructPack.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

#define COMMAX 80
void setPass(string p);
void addtxt(int cNum, File* parent, string security, string name, string desc, bool cR = true);
void addexe(int cNum, File* parent, string security, string name, string code, bool cR = true);
void addFol(int cNum, File* parent, string security, string name, bool cR = true);
void remove(int cNum, int id);

Canvas canvas;
Computer* com = new Computer[COMMAX];
Command command(&canvas, com, COMMAX);

vector<File*> File::files;
int File::fileId = 0;

Computer* Canvas::targetCom = nullptr; //Ÿ���� ��ǻ��
Computer* Canvas::connectCom = nullptr; // ������ ��ǻ��
File* Canvas::currentFile = nullptr; // ���� ����

int main() {
	ifstream file("Description.txt");
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

	canvas.input("��üȭ������ �������ּ���.");
	canvas.input("/help �Է½� ��ɾ� ����Ʈ�� ȣ���մϴ�.");

	com[0].setPlayer();

	// �÷��̾� ��ǻ�� ����
	addFol(0, nullptr, "public", "Diary", false);
	addtxt(0, com[0].getFile(0), "public", "2018.04.03", "��ŷ�� �⺻.\n\n /scan : ������ ��ǻ���� IP�� ��ĵ�Ѵ�.\n /target [IP] : ��ŷ�ϰ���� ��ǻ���� IP�� �����Ѵ�.\n /crack : ������ ��ǻ���� ��Ʈ�� ��ŷ�Ѵ�.\n��Ʈ ���� : ssh, ftp, smtp, http, proxy, firewall\n\n /nuke : ��Ʈ�� ���� ���� ��ŷ����\n /connet : ��ŷ�� �Ϸ��� ��ǻ�Ϳ� ����, IP �������� ������ ��ǻ�Ϳ� ���� �õ�\n /disconnet : ��ǻ�� ���� ����", false);
	addFol(0, nullptr, "public", "Memo", false);
	addtxt(0, com[0].getFile(1), "public", "�޸�1", "�޸� ����", false);
	addtxt(0, nullptr, "private", "/help", "�����...", true); setPass("�������� �˷���");
	addexe(0, nullptr, "public", "saveload", "/scan | /debugconnect 1", true);

	// �׿� ��ǻ�� ����
	addFol(1, nullptr, "public", "News_Collection", true); // �ٸ���� ��ǻ�� �ȿ� �� ���ΰ� ������ �޸�����?
	addtxt(1, com[1].getFile(0), "public", "�ҽ�1", "2025�� 5�� 7�� ���� ���� ���� �׾���..\n����� ������ �������Ż�� ����Ѵ�\n���� ������ �ʹ� ��Ÿ����.", true);
	addtxt(1, com[1].getFile(0), "private", "�ҽ�2", "���� ����� ������� ���� A�� ��� �Ѵ�. ������ ��� ��� �Ͼ���ϱ�?", true); setPass("1125");
	addtxt(1, com[1].getFile(0), "private", "�ҽ�3", "���� ���� ������ �̻��� ���� ���� �� �������� �־���\n ���� ��ǰ���� ��ȣȭ�� USB�� �߰ߵǾ���. �̰��� ��ŷ�غ���", true); setPass("��й�ȣ ���ؾ���");
	addtxt(1, com[1].getFile(0), "private", "�ҽ�4", "", true); setPass("1125");

	addFol(1, nullptr, "public", "2��_��ǻ��", true);
	addFol(1, nullptr, "public", "�R���o��", true);
	
	addtxt(1, com[1].getFile(0), "public", "�R���o��2", "1", true);
	addtxt(1, com[1].getFile(0), "public", "�R���o��3", "1", true);     // 2�� ��ǻ�Ϳ� �R���o�� �̶�� ������ ���� \ �״����� ���Ͼȿ��� ��й�ȣ
	addtxt(1, com[1].getFile(0), "public", "�R���o��4", "2", true);
	addtxt(1, com[1].getFile(0), "public", "�R���o��5", "5", true);


	addFol(3, nullptr, "public", "����_usb", true); setPass("���� ����");
	addtxt(3, com[3].getFile(0), "private", "����_usb1", "USB ��ȣȭ �õ� -> Project Aegis Red Line ��� �������� 3�ܰ� �鵵�� ���� �� �ұ��� �� �����ִ�.", true); setPass("���� ����");
	addtxt(3, com[3].getFile(0), "private", "����_usb2", "���� A���� ��� ���� �ý��� �����ڿ�����, ���� ��� �ý��ۿ� �ǵ��� ���� ������� �����Ѵٰ� ���� ���������� �����Ѵٰ� �����ִ�.", false); setPass("���� ����");


	

	addFol(3, nullptr, "public", "���� ����Ʈ��", true); setPass("���� ����");

	command.cmd_connect("127.0.0.1");

	//remove(0, 1);

	while (!command.getShutdown()) {
		canvas.draw();
		command.checkCommand(canvas.input());
	}
	for (File* f : File::files) { cout << f->getId(); delete f; }
	delete[] com;
	return 0;
}
void setPass(string p) { File::files[File::files.size()-1]->setPass(p); }
void addtxt(int cNum, File* parent, string security, string name, string desc, bool cR) {
	File* f = new txt(File::fileId, security, name, desc, cR);
	if (parent) { com[cNum].add(parent, f); }
	else { com[cNum].add(f); }
	File::files.push_back(f);
	File::fileId++;
}
void addexe(int cNum, File* parent, string security, string name, string code, bool cR) {
	File* f = new exe(File::fileId, security, name, code, cR);
	if (parent) { com[cNum].add(parent, f); }
	else { com[cNum].add(f); }
	File::files.push_back(f);
	File::fileId++;
}
void addFol(int cNum, File* parent, string security, string name, bool cR) {
	File* f = new Folder(File::fileId, security, name, cR);
	if (parent) { com[cNum].add(parent, f); }
	else { com[cNum].add(f); }
	File::files.push_back(f);
	File::fileId++;
}
void remove(int cNum, int id) {
	com[cNum].remove(id);
	for (int i = 0; i < File::files.size(); i++) {
		if (File::files[i]->getId() == id) {
			delete File::files[i];
			File::files.erase(File::files.begin() + i);
		}
	}
}