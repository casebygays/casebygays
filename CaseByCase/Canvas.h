#pragma once
#include "File.h"
#include "Computer.h"
#include "StructPack.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
using namespace std;

#define CMDSIZE 31 // cmd �ִ� ��� �� ��
#define SCREENSIZE 15

class Canvas {
	vector<string> cmd;
	string lastText;
public:
	Computer* connectCom; // ������ ��ǻ��
	File* currentFile; // ���� ����
	string currentFileType; // ���� ���� Ÿ��
	CanvasS save() {}
	void load() {}
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
	void cmdClear() 
	{
		cmd.clear();
	}
	void draw() // �׷��� ���
	{
		if (currentFile != nullptr and currentFileType == "Folder") drawFolder(dynamic_cast<Folder*>(currentFile));
		else if (currentFile != nullptr and currentFileType == "txt") drawtxt(dynamic_cast<txt*>(currentFile));
		else if (connectCom != nullptr) drawComputer(connectCom);
		else {
			system("cls");
			cout << "> ���� IP : 127.0.0.1\n";
			cout << "================================================================================\n";
			printEmpty(SCREENSIZE);
			cout << "================================================================================\n";
			printCMD();
		}
			
	}
	void drawComputer(Computer* com)
	{
		system("cls");
		cout << "> ���� IP : " << connectCom->getIP() << "\n\n";
		cout << "����ȭ��\n";
		cout << "================================================================================\n";
		for (int i = 0; i < com->getFileCount(); i++) {
			cout << com->getFile(i)->getName() + "\n";
		}
		printEmpty(SCREENSIZE - com->getFileCount()-1);
		cout << "================================================================================\n";
		printCMD();
	}
	void drawFolder(Folder* folder)
	{

		system("cls");
		cout << "> ���� IP : " << connectCom->getIP() << "\n\n";
		cout << folder->getName() << "\n";
		cout << "================================================================================\n";
		if (folder->getFileCount() == 0) cout << "�������\n";
		for (int i = 0; i < folder->getFileCount(); i++) {
			cout << folder->getFile(i)->getName() + "\n";
		}
		printEmpty(SCREENSIZE - folder->getFileCount()-1);
		cout << "================================================================================\n";
		printCMD();
	}
	void drawtxt(txt* text)
	{
		system("cls");
		cout << "> ���� IP : " << connectCom->getIP() << "\n\n";
		cout << text->getDescName() << "\n";
		cout << "================================================================================\n";
		string s = text->getDesc();
		int count = 1;
		for (size_t i = 0; i < s.length(); i += 80) {
			cout << s.substr(i, 80) << std::endl;
			count++;
		}
		printEmpty(SCREENSIZE - count);
		cout << "================================================================================\n";
		printCMD();
	}
	void drawexe()
	{

	}

	void printCMD() {
		cout << "----------------------------------------------------------------------------------\n";
		for (int i = 0; i < cmd.size(); i++) {
			cout << setw(2) << setfill('0') << i << " " << cmd[i] << "\n";
		}
		printEmpty(CMDSIZE - cmd.size());
		cout <<"> ";
	}
	void printEmpty(int n) {
		while (n-- > 0) { cout << "\n"; }
	}
};