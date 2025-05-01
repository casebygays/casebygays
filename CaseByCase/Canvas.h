#pragma once
#include "File.h"
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

#define CMDSIZE 30 // cmd 최대 출력 줄 수

class Canvas {
	vector<string> cmd;
	string lastText;
public:
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
	void draw(Command* command) // 그래픽 출력
	{
		if (command->getCurrentFolder() != nullptr) drawFolder(command->getCurrentFolder());
		system("cls");
		cout << ">나의 IP : 00x. xx.xx\n";
		cout << ">접속 IP : 00X. xx.xx\n";
		cout << "==================================================================================\n";
		cout << "==================================================================================\n";
		for (int i = 0; i < cmd.size(); i++) {
			cout << cmd[i] << "\n";
		}
	}
	void drawFolder(Folder* folder) // 폴더 내부 파일 출력
	{
		system("cls");
		cout << ">나의 IP : 00x. xx.xx\n";
		cout << ">접속 IP : 00X. xx.xx\n";
		cout << "==================================================================================\n";
		cout << "	> ※ AAAAA\n";
		cout << "	> ☆ BBBBBB\n";
		cout << "==================================================================================\n";
		for (int i = 0; i < cmd.size(); i++) {
			cout << cmd[i] << "\n";
		}
	}
};