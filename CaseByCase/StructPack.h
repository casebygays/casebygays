#pragma once
#include <vector>
#include <string>
using namespace std;

typedef struct {
	int id;
	string icon;
	string name;
	string securityType;
	string pass;
	bool canRemove;
} S_File;

typedef struct {
	S_File file;
	string desc;
} S_txt;

typedef struct {
	S_File file;
} S_exe;

typedef struct {
	S_File file;
	vector<int> childID;
} S_Folder;

typedef struct {
	int level;
	string IP;
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