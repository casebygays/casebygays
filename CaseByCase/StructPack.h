#pragma once
#include <string>
using namespace std;

typedef struct {
	int parentFileID;
	int id;
	string securityLevel;
	string name;

	string descName;
	string desc;
} txtS;

typedef struct {
	int parentFileID;
	int id;
	string securityLevel;
	string name;

	string url;
} exeS;

typedef struct {
	int parentFileID;
	int id;
	string securityLevel;
	string name;

} FolderS;

typedef struct {
	string IP;
	bool ssh, ftp, smt, http;

	txtS t;
	exeS e;
	FolderS f;
} ComputerS;

typedef struct {
	string cmd[30];
	string lastText;
	string connectComIP;
	int currentFileID;
	string currentFileType;
} CanvasS;

typedef struct {
	string connectComIP; // 접속한 컴퓨터
	int currentFileID; // 현재 파일
	int prevFileID; // 이전 파일
} CommandS;