#pragma once
#include "File.h"
#include "Computer.h"
#include "StructPack.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
using namespace std;

#define CMDSIZE 31 // cmd 최대 출력 줄 수
#define SCREENWIDTH 80 // 스크린 가로길이
#define SCREENHEIGH 15 // 스크린 세로길이

class Canvas {
private:
	vector<string> cmd;
	string lastText;
	int index; // 현재 줄 번호
public:
	bool in_proxy;
	int proxyAnswer;
	int proxyChance;
	vector<int> proxyInput;

	static Computer* targetCom; //타겟팅 컴퓨터
	static Computer* connectCom; // 접속한 컴퓨터
	static File* currentFile; // 현재 파일
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
	void draw() {
		if (in_proxy) drawProxyGame();
		else if (currentFile != nullptr and getFileType(currentFile, "Folder")) drawFolder(dynamic_cast<Folder*>(currentFile));
		else if (currentFile != nullptr and getFileType(currentFile, "txt")) drawtxt(dynamic_cast<txt*>(currentFile));
		else if (currentFile != nullptr and getFileType(currentFile, "exe")) drawexe(dynamic_cast<exe*>(currentFile));
		else if (connectCom != nullptr) drawComputer(connectCom);
		else drawMain();
	}
	void drawMain() //  메인화면(디버그화면)
	{
		system("cls");
		print("> 접속 IP : ???.?.?.?");
		print("[????]");
		print("================================================================================");
		print("이 화면은 의도적으로 띄운거아니면 뭔가 잘못된거다.");
		for (int i = 0; i < SCREENHEIGH - 1; i++) 
			print("");
		print("================================================================================");
		for (int i = index; i < CMDSIZE; i++) 
			print("");
		index = 0;
	}
	void drawComputer(Computer* com)
	{
		system("cls");
		print("> 접속 IP : " + connectCom->getIP());
		print("/바탕화면");
		print("================================================================================");
		for (int i = 0; i < com->getFileCount(); i++) 
			print(com->getFile(i)->getIcon() + " " + com->getFile(i)->getName());
		for (int i = 0; i < SCREENHEIGH - com->getFileCount() - 1; i++) 
			print("");
		print("================================================================================");
		for (int i = index; i < CMDSIZE; i++) print("");
		printInput();
		index = 0;
	}
	void drawFolder(Folder* folder)
	{
		system("cls");
		print("> 접속 IP : " + connectCom->getIP());
		print("/바탕화면" + File::getRoot(currentFile));
		print("================================================================================");
		if (folder->getFileCount() == 0) print("비어있음");
		for (int i = 0; i < folder->getFileCount(); i++) {
			print(folder->getFile(i)->getIcon()+ " " + folder->getFile(i)->getName());
		}
		for (int i = 0; i < SCREENHEIGH - folder->getFileCount() - 1; i++)
			print("");
		print("================================================================================");
		for (int i = index; i < CMDSIZE; i++) print("");
		printInput();
		index = 0;
	}
	void drawtxt(txt* text)
	{
		system("cls");
		print("> 접속 IP : " + connectCom->getIP());
		print("/바탕화면" + File::getRoot(currentFile));
		print("================================================================================");
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
		print("================================================================================");
		for (int i = index; i < CMDSIZE; i++) print("");
		printInput();
		index = 0;
	}
	void drawexe(exe* exe)
	{
		system("cls");
		print("> 접속 IP : " + connectCom->getIP());
		print("/바탕화면" + File::getRoot(currentFile));
		print("================================================================================");
		printInput();
		index = 0;
	}
	void drawProxyGame() {
		system("cls");
		print("> 접속 IP : " + connectCom->getIP());
		print("[프록시 해킹 - 스도쿠]");
		print("================================================================================");
		print("                       +-----------------------------+");
		print("                       |     PROXY SECURITY TEST     |");
		print("                       +-----------------------------+");
		print("                       | 0~9 숫자 중 정답을 맞추세요 |");
		print("                       |     기회는 총 3번입니다.    |");
		print("                       +-----------------------------+");
		print("================================================================================");
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