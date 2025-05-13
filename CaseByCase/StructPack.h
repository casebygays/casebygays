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
	// Folder는 로드에서 바로 가져옴

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
	string connectComIP; // 접속한 컴퓨터
	int currentFileID; // 현재 파일
	int prevFileID; // 이전 파일
} S_Command;