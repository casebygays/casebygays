#pragma once
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

#define CMDSIZE 15 // cmd �ִ� ��� �� ��

class Canvas {
	vector<string> cmd;
	string lastText;
public:
	//Canvas() : {}
	string input() //cmdâ�� �Է�, �Էµ� �ؽ�Ʈ�� ��ȯ��
	{
		getline(cin, lastText);
		cmd.push_back(lastText);
		if (cmd.size() > CMDSIZE) cmd.erase(cmd.begin()); // cmd ��� ��������
		return lastText;
	}
	void input(string s) //cmdâ�� �Է�, �Էµ� �ؽ�Ʈ�� ��ȯ��
	{
		cmd.push_back(s);
		if (cmd.size() > CMDSIZE) cmd.erase(cmd.begin()); // cmd ��� ��������
	}
	void draw() // �׷��� ���
	{
		system("cls");
		cout << ">���� IP : 00x. xx.xx\n";
		cout << ">���� IP : 00. xx.xx\n";
		cout << "==================================================================================\n";
		cout << "	> �� AAAAA\n";
		cout << "	> �� BBBBBB\n";
		cout << "==================================================================================\n";
		for (int i = 0; i < cmd.size(); i++) {
			if (cmd[i] == "") break;
			cout << cmd[i] << "\n";
		}
	}
};