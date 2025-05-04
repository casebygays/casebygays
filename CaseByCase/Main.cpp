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
void addtxt(int cNum, File* parent, string security, string name, string desc, bool cR = true);
void addexe(int cNum, File* parent, string security, string name, bool cR = true);
void addFol(int cNum, File* parent, string security, string name, bool cR = true);
void remove(int cNum, int id);

Canvas canvas;
Computer* com = new Computer[COMMAX];
Command command(&canvas, com, COMMAX);

vector<File*> File::files;
int File::fileId = 0;

int main() {
	canvas.input("전체화면으로 진행해주세요.");
	canvas.input("/help 입력시 명령어 리스트를 호출합니다.");

	com[0].setPlayer();
	// 플레이어 컴퓨터 파일
	addFol(0, nullptr, "public", "도움말", false);
	addFol(0, nullptr, "public", "일기", false);
	addtxt(0, com[0].getFile(1), "public", "일기_0", "일기내용 0", false);
	addtxt(0, com[0].getFile(1), "public", "일기_1", "일기내용 1", false);
	addtxt(0, com[0].getFile(1), "public", "일기_2", "일기내용 2", false);
	addexe(0, nullptr, "private", "help", true); setPass("1234");
	// 그외 컴퓨터 파일
	addFol(1, nullptr, "public", "1번_컴퓨터", true);
	addtxt(1, nullptr, "public", "textfile", "내용 내용", true);
	addtxt(1, com[1].getFile(0), "public", "textfile", "내용 내용", true);

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
void addexe(int cNum, File* parent, string security, string name, bool cR) {
	File* f = new exe(File::fileId, security, name, cR);
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