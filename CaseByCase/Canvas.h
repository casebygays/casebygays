#pragma once
#include "File.h"
#include "Computer.h"
#include "StructPack.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <windows.h>
using namespace std;

#define CMDSIZE 41 // cmd �ִ� ��� �� ��
#define SCREENWIDTH 120 // ��ũ�� ���α���
#define SCREENHEIGH 25 // ��ũ�� ���α���

class Canvas {
private:
	vector<string> cmd;
	string lastText;
	int index; // ���� �� ��ȣ
public:
	bool in_proxy;
	int proxyAnswer;
	int proxyChance;

	static int alertLevel; // �߰���

	static Computer* targetCom; //Ÿ���� ��ǻ��
	static Computer* connectCom; // ������ ��ǻ��
	static File* currentFile; // ���� ����
	static bool getFileType(File* f, string type) {
		if (dynamic_cast<exe*>(f) and type == "exe") return true;
		else if (dynamic_cast<txt*>(f) and type == "txt") return true;
		else if (dynamic_cast<Folder*>(f) and type == "Folder") return true;
		return false;
	}

	Canvas() {
		index = 0;
		in_proxy = false;
		proxyChance = 0;

		targetCom = nullptr;
		connectCom = nullptr;
		currentFile = nullptr;
	}
	void save() {}
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
	void draw() {
		if (in_proxy) drawProxyGame();
		else if (currentFile != nullptr and getFileType(currentFile, "Folder")) drawFolder(dynamic_cast<Folder*>(currentFile));
		else if (currentFile != nullptr and getFileType(currentFile, "txt")) drawtxt(dynamic_cast<txt*>(currentFile));
		else if (currentFile != nullptr and getFileType(currentFile, "exe")) drawexe(dynamic_cast<exe*>(currentFile));
		else if (connectCom != nullptr) drawComputer(connectCom);
		else drawMain();
	}
	void drawMain() //  ����ȭ��(�����ȭ��)
	{
		system("cls");
		print("> ���� IP : ???.?.?.?");
		print("[????]");
		print("========================================================================================================================");
		print("?????????????????????????");
		for (int i = 0; i < SCREENHEIGH - 1; i++) 
			print("");
		print("========================================================================================================================");
		for (int i = index; i < CMDSIZE; i++) 
			print("");
		index = 0;
	}
	void drawComputer(Computer* com)
	{
		system("cls");
		print("> ���� IP : " + connectCom->getIP());
		if (alertLevel != 0) print("�߰��� : " + to_string(alertLevel), "Red");
		else print("");
		print("/����ȭ��");
		print("========================================================================================================================");
		for (int i = 0; i < com->getFileCount(); i++) 
			if (com->getFile(i)->getVisible())
				if (com->getFile(i)->getSecurity() == "private")
					print(com->getFile(i)->getIcon() + " " + com->getFile(i)->getName() + " (���)");
				else print(com->getFile(i)->getIcon() + " " + com->getFile(i)->getName());
		for (int i = 0; i < SCREENHEIGH - com->getFileCount() - 1; i++) 
			print("");
		print("========================================================================================================================");
		for (int i = index; i < CMDSIZE; i++) print("");
		printInput();
		index = 0;
	}
	void drawFolder(Folder* folder)
	{
		system("cls");
		print("> ���� IP : " + connectCom->getIP());
		print("/����ȭ��" + File::getRoot(currentFile));
		print("========================================================================================================================");
		if (folder->getFileCount() == 0) print("�������");
		for (int i = 0; i < folder->getFileCount(); i++) {
			if (folder->getFile(i)->getVisible())
				print(folder->getFile(i)->getIcon()+ " " + folder->getFile(i)->getName());
		}
		for (int i = 0; i < SCREENHEIGH - folder->getFileCount() - 1; i++)
			print("");
		print("========================================================================================================================");
		for (int i = index; i < CMDSIZE; i++) print("");
		printInput();
		index = 0;
	}
	void drawtxt(txt* text)
	{
		system("cls");
		print("> ���� IP : " + connectCom->getIP());
		print("/����ȭ��" + File::getRoot(currentFile));
		print("========================================================================================================================");
		string s = text->getDesc();
		istringstream iss(s);
		string line;
		int count = 0;

		while (getline(iss, line)) {
			for (size_t i = 0; i < line.length(); i += SCREENWIDTH) {
				print(line.substr(i, SCREENWIDTH));
				count++;
			}
		}

		for (int i = 0; i < SCREENHEIGH - count; i++) {
			print("");
		}
		print("========================================================================================================================");
		for (int i = index; i < CMDSIZE; i++) print("");
		printInput();
		index = 0;
	}
	void drawexe(exe* exe)
	{
		system("cls");
		print("> ���� IP : " + connectCom->getIP());
		print("/����ȭ��" + File::getRoot(currentFile));
		print("========================================================================================================================");
		printInput();
		index = 0;
	}
	void drawProxyGame() {
		system("cls");
		print("> ���� IP : " + connectCom->getIP());
		print("[���Ͻ� ��ŷ - ���� ����]");
		print("========================================================================================================================");
		print("										+-----------------------------+");
		print("										|     PROXY SECURITY TEST     |");
		print("										+-----------------------------+");
		print("										| 1~5 ���� �� ������ ���߼��� |");
		print("										|     ��ȸ�� �� 2���Դϴ�.    |");
		print("										+-----------------------------+");
		print("========================================================================================================================");
		for (int i = index; i < CMDSIZE; i++) print("");
		printInput();
		index = 0;
	}
	void print(string s) {
		cout << s;
		if (index < CMDSIZE) printCMD(SCREENWIDTH - s.size(), index);
		index++;
		cout << "\n";
	}
	void print(string text, string col) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
		WORD saved_attributes;
		GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
		saved_attributes = consoleInfo.wAttributes;

		if (col == "Red") SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
		else if (col == "Green") SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		else if (col == "Blue") SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);

		cout << text;

		SetConsoleTextAttribute(hConsole, saved_attributes);

		if (index < CMDSIZE) printCMD(SCREENWIDTH - text.size(), index);
		index++;
		cout << "\n";
	}
	void printCMD(int space, int index) {
		for (int i = 0; i < space; i++) cout << " ";
		if (index < cmd.size())
			cout << " |" << setw(2) << setfill('0') << index << " " << cmd[index].substr(0,100);
		else
			cout << " |" << setw(2) << setfill('0') << index;
	}
	void printInput() {
		for (int i = 0; i < SCREENWIDTH; i++) cout << " ";
		cout << " | > ";
	}
	int getCMDSize() { return cmd.size(); }
	string getCMDText(int num) { return cmd[num]; }
	string getLastText() { return lastText; }
};