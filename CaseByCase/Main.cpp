#pragma once
#include "Canvas.h"
#include "Computer.h"
#include "File.h"
#include "Command.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

#define COMMAX 80
void setPass(string p);
void addtxt(int cNum, File* parent, string security, string name, string desc);
void addexe(int cNum, File* parent, string security, string name);
void addFol(int cNum, File* parent, string security, string name);
void remove(int cNum, int id);

Canvas canvas;
Computer* com = new Computer[COMMAX];
Command command(&canvas, com, COMMAX);
vector<File*> files;
int fileId = 0;

int main() {
	canvas.input("��üȭ������ �������ּ���.");
	canvas.input("/help �Է½� ��ɾ� ����Ʈ�� ȣ���մϴ�.");

	com[0].setPlayer();
	// �÷��̾� ��ǻ�� ����
	addFol(0, nullptr, "public", "����");
	addFol(0, nullptr, "public", "�ϱ�");
	addtxt(0, com[0].getFile(0), "public", "�ϱ�_0", "�ϱ⳻�� 0");
	addtxt(0, com[0].getFile(0), "public", "�ϱ�_1", "�ϱ⳻�� 1");
	addtxt(0, com[0].getFile(0), "public", "�ϱ�_2", "�ϱ⳻�� 2");
	addexe(0, nullptr, "private", "help"); setPass("1234");
	// �׿� ��ǻ�� ����
	addFol(1, nullptr, "public", "1��_��ǻ��");
	addtxt(1, nullptr, "public", "textfile", "���� ����");
	addtxt(1, com[1].getFile(0), "public", "textfile", "���� ����");

	command.cmd_connect("127.0.0.1");

	//remove(0, 1);

	while (!command.getShutdown()) {
		canvas.draw();
		command.checkCommand(canvas.input());
	}
	for (File* f : files) { cout << f->getId(); delete f; }
	delete[] com;
	return 0;
}
void setPass(string p) { files[files.size()-1]->setPass(p); }
void addtxt(int cNum, File* parent, string security, string name, string desc) {
	File* f = new txt(fileId, security, name, desc);
	if (parent) { com[cNum].add(parent, f); }
	else { com[cNum].add(f); }
	files.push_back(f);
	fileId++;
}
void addexe(int cNum, File* parent, string security, string name) {
	File* f = new exe(fileId, security, name);
	if (parent) { com[cNum].add(parent, f); }
	else { com[cNum].add(f); }
	files.push_back(f);
	fileId++;
}
void addFol(int cNum, File* parent, string security, string name) {
	File* f = new Folder(fileId, security, name);
	if (parent) { com[cNum].add(parent, f); }
	else { com[cNum].add(f); }
	files.push_back(f);
	fileId++;
}
void remove(int cNum, int id) {
	com[cNum].remove(files ,id);
	for (int i = 0; i < files.size(); i++) {
		if (files[i]->getId() == id) {
			delete files[i];
			files.erase(files.begin() + i);
		}
	}
}