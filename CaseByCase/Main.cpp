#pragma once
#include "Canvas.h"
#include "Computer.h"
#include "File.h"
#include "Command.h"
#include "StructPack.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

#define COMMAX 80
void setPass(string p);
void addtxt(int cNum, File* parent, string security, string name, string desc, bool cR = true);
void addexe(int cNum, File* parent, string security, string name, bool cR = true);
void addFol(int cNum, File* parent, string security, string name, bool cR = true);
void remove(int cNum, int id);

Canvas canvas;
Computer* com = new Computer[COMMAX];
Command command(&canvas, com, COMMAX);

vector<File*> File::files;
int File::fileId = 0;

int Canvas::alertLevel = 0;
Computer* Canvas::targetCom = nullptr; //타겟팅 컴퓨터
Computer* Canvas::connectCom = nullptr; // 접속한 컴퓨터
File* Canvas::currentFile = nullptr; // 현재 파일

int main() {
	ifstream file("Description.txt");
	string line;
	while (getline(file, line)) {
		size_t sep = line.find('=');
		if (sep == string::npos) continue;

		string key = line.substr(0, sep);
		string value = line.substr(sep + 1);

		//if (key == "name") name = value;
		//else if (key == "level") level = stoi(value);
		//else if (key == "health") health = stod(value);
	}

	file.close();

	canvas.input("전체화면으로 진행해주세요.");
	canvas.input("/help 입력시 명령어 리스트를 호출합니다.");

	com[0].setPlayer();
	// 플레이어 컴퓨터 파일
	addFol(0, nullptr, "public", "도움말", false);

	addFol(0, nullptr, "public", "Diary", false);
	addtxt(0, com[0].getFile(1), "public", "dlfrl1", "해킹의 기본은 무엇일까\n오늘 해킹을 하기 위해서는 scan을 하면 내가 해킹할수있는 iq를 찾을수있다\ntarget 특정 iq를 지정할수있음\ncarck 지정iq의 포트를 열수있음\nnuke 포트를 전부 열면 iq를 해킹할수있음\nconnet 접속\ndisconnet 내 iq로 재접속", false);

	addFol(0, nullptr, "public", "Diary_123", false);

	addtxt(0, com[0].getFile(1), "public", "Diary_1", "일기내용 1", false);
	addtxt(0, com[0].getFile(1), "public", "Diary_2", "일기내용 2", false);
	addexe(0, nullptr, "private", "help", true); setPass("1234");

	//addtxt(0, com[0].getFile(1), "public", "textfile", "내용 내용", false);
	// 그외 컴퓨터 파일
	addFol(1, nullptr, "public", "1번_컴퓨터", true);
	addtxt(1, com[1].getFile(0), "public", "news_1", "오늘 아침 뉴스를 보았다. 뉴스에서는 여객기 사고를 보여주고있엇다. 어제 형이 외국으로 간다는 얘기를 들었다.", true);
	addtxt(1, com[1].getFile(0), "private", "news_2", "오늘 경찰에게서 전화가 왔다. 형이 죽었다고 한다. 어제 뉴스로 보았던 여객기에 형이 타고 있었다고 한다. 여러가지 생각이 들었다. 형은 착한 사람이었다.", true); setPass("1125");
	addtxt(1, com[1].getFile(0), "private", "news_3", "", true); setPass("비밀번호 정해야함");
	addtxt(1, com[1].getFile(0), "private", "news_4", "형의 유품에서 수상한 USB가 발견 되었다.그날 이후로 나는 아무것도 할 수 없다. 티비를 보아도 그 사건만 나오고 있다. 언제쯤 괜찮아 질까\n\"내가 사건을 해결해볼까?\"", true); setPass("1125");

	addFol(0, nullptr, "public", "USB", true);	// 나중에 숨김파일 처리하고 소식4번을 확인하면 나타나게 할 예정

	addtxt(0, com[0].getFile(4), "public", "Detail_1", "[보안 점검 기록 - 2025.04.20 | 작성자: 김석현 (보안 관리자)]\n \n비행기 자동 운항 시스템 내부에서 알 수 없는 우회 루틴 발견.\n정상 인증 과정을 우회하여 외부 명령이 삽입 가능한 구조.\n로그 분석 결과, 아래 명령이 비정상적으로 실행됨:\nCMD: override_autopilot(true)\nCMD: set_altitude(0)\n \n공식 매뉴얼 및 코드베이스에는 존재하지 않는 방식.\n본 루틴이 악용될 경우 비행기 통제가 불가능해질 수 있음.\n \n이미 시스템이 침해당했을 가능성또한 존재.\n해당 루틴은 의도적으로 삽입된 것으로 보임. 빠른 조치가 필요함.", true);
	addtxt(0, com[0].getFile(4), "public", "전송되지않은메일초안", "[전송되지 않은 메일 초안]\n \nTo: 본사 보안총괄부\nSubject: 시스템 침해 의심건\n이 루틴은 단순한 버그가 아니라, 누군가가 만든 우회 경로로 보입니다.\n침입 흔적이 있으며, 접근은 최소 두 차례 이상 감지되었습니다.\n어떤 목적이었는지는 모르겠지만, 이걸 무시하면 사고로 이어질 수 있습니다.\n하지만 내부 경로를 따라온 흔적도 있어, 내부 인물이 연루되었을 가능성도 배제할 수 없습니다.\n내가 이 사실을 알았다는 것 자체가 위험할 수도 있습니다.\n정보는 백업해 두었습니다. 내가 끝까지 보고하지 못하더라도, 누군가는 이걸 봐야합니다. 내가 보고를 못할 경우 친구A에게 연락 바랍니다. \n전송 보류 중...", true);
	addtxt(0, com[0].getFile(4), "public", "Record.wav","\n\n[녹음 파일 자동 복구 기록 | 일부 손상됨]\n \n형: 여기 접근 좌표 확인해봤어. 포트6077에서 외부 요청이 감지됐어.\n형: 로그엔 '인증 우회' 명령이 두 번... 누군가 시스템 안으로 들어왔다는 거야.\n형: ...기록을 남겨야겠어. 더 이상 이걸 혼자 감당할 순 없어...\n \n* (통화 끊김 / 정적 발생) *",true);

	
	
	addFol(0, nullptr, "public", "스마트폰", true); setPass("김석현");	// 마찬가지로 나중에 숨김파일 처리하고 USB를 확인하면 나타나게 할 예정 패드워드는 다른곳에서 찾을수 있게 설정

	addFol(0, com[0].getFile(5), "public", "Message", true);
	addFol(0, com[0].getFile(5), "public", "Call_Log", true);

	addtxt(0, com[0].getFile(5)->getFile(0), "public", "[보안팀장]", "[4/21 09:44]\n \n석현 씨, 그건 그냥 테스트 루틴이야. 작년에도 나왔던 거잖아. 오버좀 하지마.\n우리 지금 연차도 없고, 민감한 시기인 거 알잖아.\n조용히 묻고 지나가자. 시스템 바꾸는 건 본사 허락 없인 안 돼 알잖아 우리 귀찮게 하지말자", true);
	addtxt(0, com[0].getFile(5)->getFile(0), "public", "[알수없는번호]", "[4/19 20:32]\n \n그 루틴 너만 본 거 아니야. 다른 사람들도 다 봤어. 하지만 입 다물었지.\n왜 아직도 그걸 파냐고 하더라. 조심해.\n모든 게 기록되고 있어. 네 위치도 마찬가지야.", true);
	addtxt(0, com[0].getFile(5)->getFile(0), "public", "[엄마]", "[4/19 20:32]\n \n석현아 이번 주말에 집에 올 수 있니?", true);


	addtxt(0, com[0].getFile(5)->getFile(1), "public", "[엄마]", "[4/19 20:32]\n \n석현아 이번 주말에 집에 올 수 있니?", true); // 여기서부터 진행해야함

	command.cmd_connect("127.0.0.1");

	//remove(0, 1);

	while (!command.getShutdown()) {
		canvas.draw();
		command.checkCommand(canvas.input());
	}
	for (File* f : File::files) { cout << f->getId(); delete f; }
	delete[] com;
	return 0;
}
void setPass(string p) { File::files[File::files.size()-1]->setPass(p); }
void addtxt(int cNum, File* parent, string security, string name, string desc, bool cR) {
	File* f = new txt(File::fileId, security, name, desc, cR);
	if (parent) { com[cNum].add(parent, f); }
	else { com[cNum].add(f); }
	File::files.push_back(f);
	File::fileId++;
}
void addexe(int cNum, File* parent, string security, string name, bool cR) {
	File* f = new exe(File::fileId, security, name, cR);
	if (parent) { com[cNum].add(parent, f); }
	else { com[cNum].add(f); }
	File::files.push_back(f);
	File::fileId++;
}
void addFol(int cNum, File* parent, string security, string name, bool cR) {
	File* f = new Folder(File::fileId, security, name, cR);
	if (parent) { com[cNum].add(parent, f); }
	else { com[cNum].add(f); }
	File::files.push_back(f);
	File::fileId++;
}
void remove(int cNum, int id) {
	com[cNum].remove(id);
	for (int i = 0; i < File::files.size(); i++) {
		if (File::files[i]->getId() == id) {
			delete File::files[i];
			File::files.erase(File::files.begin() + i);
		}
	}
}