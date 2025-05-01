#pragma once
#include "File.h"
#include "Computer.h"
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

#define CMDSIZE 30 // cmd 최대 출력 줄 수
#define SCREENSIZE 15

class Canvas {
	vector<string> cmd;
	string lastText;
public:
	Computer* connectCom; // 접속한 컴퓨터
	File* currentFile; // 현재 폴더
	string currentFileType; // 현재 폴더 타입
	//Canvas() : {}
	string input() //cmd창에 입력, 입력된 텍스트를 반환함
	{
		getline(cin, lastText);
		cmd.push_back(lastText);
		if (cmd.size() > CMDSIZE) cmd.erase(cmd.begin()); // cmd 출력 제한유지
		return lastText;
	}
	void input(string s) //cmd창에 입력, 입력된 텍스트를 반환함
	{
		cmd.push_back(s);
		if (cmd.size() > CMDSIZE) cmd.erase(cmd.begin()); // cmd 출력 제한유지
	}
	void cmdClear() 
	{
		cmd.clear();
	}
	void draw() // 그래픽 출력
	{
		if (currentFile != nullptr and currentFileType == "Folder") drawFolder(dynamic_cast<Folder*>(currentFile));
		else if (currentFile != nullptr and currentFileType == "txt") drawtxt(dynamic_cast<txt*>(currentFile));
		else if (connectCom != nullptr) drawComputer(connectCom);
		else {
			system("cls");
			cout << ">나의 IP : 00x. xx.xx\n";
			cout << ">접속 IP : 00X. xx.xx\n";
			cout << "==================================================================================\n";
			printEmpty(SCREENSIZE);
			cout << "==================================================================================\n";
			printCMD();
		}
			
	}
	void drawComputer(Computer* com)
	{
		system("cls");
		cout << ">나의 IP : 00x. xx.xx\n";
		cout << ">접속 IP : 00X. xx.xx\n";
		cout << "==================================================================================\n";
		for (int i = 0; i < com->getFileCount(); i++) {
			cout << com->getFile(i)->getName() + "\n";
		}
		printEmpty(SCREENSIZE - com->getFileCount());
		cout << "==================================================================================\n";
		printCMD();
	}
	void drawFolder(Folder* folder)
	{

		system("cls");
		cout << ">나의 IP : 00x. xx.xx\n";
		cout << ">접속 IP : 00X. xx.xx\n";
		cout << "==================================================================================\n";
		for (int i = 0; i < folder->getFileCount(); i++) {
			cout << folder->getFile(i)->getName() + "\n";
		}
		printEmpty(SCREENSIZE - folder->getFileCount());
		cout << "==================================================================================\n";
		printCMD();
	}
	void drawtxt(txt* text)
	{
		system("cls");
		cout << ">나의 IP : 00x. xx.xx\n";
		cout << ">접속 IP : 00X. xx.xx\n";
		cout << "==================================================================================\n";
		cout << text->getName() + "\n";
		for (int i = 0 ; i < 10; i++) cout << text->getDesc(i) + "\n";
		printEmpty(4);
		cout << "==================================================================================\n";
		printCMD();
	}
	void drawexe()
	{

	}

	void printCMD() {
		for (int i = 0; i < cmd.size(); i++) {
			cout << cmd[i] << "\n";
		}
	}
	void printEmpty(int n) {
		while (n-- > 0) { cout << "\n"; }
	}
};