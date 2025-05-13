#pragma once
#include <vector>
#include <string>
using namespace std;

typedef struct {
	int id;
	int parentID;
	string icon;
	string name;
	string securityType;
	string pass;
	bool canRemove;
	bool visible;
	string desc; // txt
	string code; // exe
	// Folder�� �ε忡�� �ٷ� ������

} S_File;

typedef struct {
	string IP;
	int level;
	bool ssh, ftp, smtp, http;
	bool is_nuke;
	vector<int> childID;
} S_Computer;

typedef struct {
	string cmd[31];
	string lastText;
	string connectComIP;
	int currentFileID;
	string currentFileType;
} S_Canvas;

typedef struct {
	string connectComIP; // ������ ��ǻ��
	int currentFileID; // ���� ����
	int prevFileID; // ���� ����
} S_Command;