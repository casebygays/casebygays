#pragma once
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

#define CMDSIZE 15 // cmd 최대 출력 줄 수

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
	void draw() // 그래픽 출력
	{
		system("cls");
		cout << ">나의 IP : 00x. xx.xx\n";
		cout << ">접속 IP : 00. xx.xx\n";
		cout << "==================================================================================\n";
		cout << "	> ※ AAAAA\n";
		cout << "	> ☆ BBBBBB\n";
		cout << "==================================================================================\n";
		for (int i = 0; i < cmd.size(); i++) {
			if (cmd[i] == "") break;
			cout << cmd[i] << "\n";
		}
	}
};