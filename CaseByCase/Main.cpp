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
void addexe(int cNum, File* parent, string security, string name, bool cR = true);
void addFol(int cNum, File* parent, string security, string name, bool cR = true);
void remove(int cNum, int id);

Canvas canvas;
Computer* com = new Computer[COMMAX];
Command command(&canvas, com, COMMAX);

vector<File*> File::files;
int File::fileId = 0;

int Canvas::alertLevel = 0;
Computer* Canvas::targetCom = nullptr; //타겟팅 컴퓨터
Computer* Canvas::connectCom = nullptr; // 접속한 컴퓨터
File* Canvas::currentFile = nullptr; // 현재 파일

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

	canvas.input("전체화면으로 진행해주세요.");
	canvas.input("/help 입력시 명령어 리스트를 호출합니다.");

	com[0].setPlayer();
	// 플레이어 컴퓨터 파일
	addFol(0, nullptr, "public", "도움말", false);
<<<<<<< HEAD
	addFol(0, nullptr, "public", "dlfrl", false);
	addtxt(0, com[0].getFile(1), "public", "dlfrl1", "해킹의 기본은 무엇일까\n오늘 해킹을 하기 위해서는 scan을 하면 내가 해킹할수있는 iq를 찾을수있다\ntarget 특정 iq를 지정할수있음\ncarck 지정iq의 포트를 열수있음\nnuke 포트를 전부 열면 iq를 해킹할수있음\nconnet 접속\ndisconnet 내 iq로 재접속", false);
=======
	addFol(0, nullptr, "public", "일기", false);
	addtxt(0, com[0].getFile(1), "public", "일기_0", "가나다라마바사가나다라마바사 가나다라마바사가나다라마 바사가나다라마바사가나다라마바\n사가나다라마바사가나다라마바사가나다라마 바사가나다라마바사가나다라마바사가나다라\n마바사가나다라마바사가나다라마바사가나다라마바사가나다라마바사가나다라마바사", false);
>>>>>>> fdf4ca19b7453d85f1bb9586d102420ef8e15a16
	addtxt(0, com[0].getFile(1), "public", "일기_1", "일기내용 1", false);
	addtxt(0, com[0].getFile(1), "public", "일기_2", "일기내용 2", false);
	addexe(0, nullptr, "private", "help", true); setPass("1234");

	//addtxt(0, com[0].getFile(1), "public", "textfile", "내용 내용", false);
	// 그외 컴퓨터 파일
	addFol(1, nullptr, "public", "1번_컴퓨터", true);
	//addtxt(1, nullptr, "public", "textfile", "내용 내용", true);
	addtxt(1, com[1].getFile(0), "public", "소식1", "2025년 5월 7일 오늘 형이 사고로 죽었다..\n사고의 원인은 비행기통신사고 라고한다\n요즘도 이런 통신사고가 일어나는가? 누군가 의도적으로 사고를 일으킨것이 아닐까?\n형의 억울한 죽음을 위해서라도 사건의 진실을 찾아보겠어", true);
	addtxt(1, com[1].getFile(0), "private", "소식2", "형이 골랐던 여행기는 대기업 A사 라고 한다. 대기업에 어떠한 사고가 일어난것일까?", true); setPass("1125");
	addtxt(1, com[1].getFile(0), "private", "소식3", "형은 생전 나에게 이상한 점이 많다 고 말한적이 있었다\n 형의 유품에서 암호화된 USB가 발견되었다. 이것을 해킹해보자", true); setPass("비밀번호 정해야함");
	addtxt(1, com[1].getFile(0), "private", "소식4", "", true); setPass("1125");

	addFol(2, nullptr, "public", "2번_컴퓨터", true);
	//addFol(2, nullptr, "public", "딹뛀꼘뿔", true);
	
	addtxt(2, com[0].getFile(0), "public", "딹뛀꼘뿔2", "1", true);
	addtxt(2, com[0].getFile(0), "public", "딹뛀꼘뿔3", "1", true);     // 2번 컴퓨터에 딹뛀꼘뿔 이라는 폴더을 생성 \ 그다음에 파일안에서 비밀번호
	addtxt(2, com[0].getFile(0), "public", "딹뛀꼘뿔4", "2", true);
	addtxt(2, com[0].getFile(0), "public", "딹뛀꼘뿔5", "5", true);


	addFol(3, nullptr, "public", "형의 usb", true); setPass("나의 생일");
	addtxt(3, com[1].getFile(0), "private", "형의 usb1", "USB 복호화 시도 -> Project Aegis Red Line 통신 프로토콜 3단계 백도어 설계 등 불길한 용어가 적혀있다.", true); setPass("나의 생일");

	addtxt(3, com[1].getFile(0), "private", "형은 A사의 통신 보안 시스템 연구자였으며, 신형 통신 시스템에 의도된 보안 취약점이 존재한다고 말한 녹취파일이 존재한다고 쓰여있다.", false); setPass("나의 생일");


	

	addFol(3, nullptr, "public", "형의 스마트폰", true); setPass("나의 생일");
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