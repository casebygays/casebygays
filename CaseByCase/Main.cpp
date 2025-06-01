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
void addtxt(int cNum, File* parent, string security, string name, string desc, bool v = true, bool cR = true, bool oneshot = false);
void addexe(int cNum, File* parent, string security, string name, string code, bool v = true, bool cR = true, bool oneshot = false);
void addFol(int cNum, File* parent, string security, string name, bool v = true, bool cR = true, bool oneshot = false);
void remove(int cNum, int id);

Canvas canvas;
Computer* com = new Computer[COMMAX];
Command command(&canvas, com, COMMAX);

vector<File*> File::files;
int File::fileId = 0;

Computer* Canvas::targetCom = nullptr; //타겟팅 컴퓨터
Computer* Canvas::connectCom = nullptr; // 접속한 컴퓨터
File* Canvas::currentFile = nullptr; // 현재 파일
int Canvas::alertLevel = 0;

File* autoParent; // main에서 가장 마지막에 생성된 폴더를 가르킴

int main() {
	/* cmd창 조절, 전체화면 변경, 빌드할때 활성화해야됨
	system("mode con: cols=300 lines=100"); 
	system("title Case By Case");
	HWND consoleWindow = GetConsoleWindow();
	ShowWindow(consoleWindow, SW_MAXIMIZE);
	*/
	canvas.input("/help 입력시 명령어 리스트를 호출합니다.");
	// 플레이어 컴퓨터 파일
	com[0].setPlayer();
	addFol(0, nullptr, "public", "Diary", true, false);
	addtxt(0, autoParent, "public", "2018.04.03", "해킹의 기본.\n\n /scan : 무작위 컴퓨터의 IP를 스캔한다.\n /target [IP] : 해킹하고싶은 컴퓨터의 IP를 지정한다.\n /crack : 지정된 컴퓨터의 포트를 해킹한다.\n포트 종류 : ssh, ftp, smtp, http, proxy, firewall\n\n /nuke : 포트를 전부 열면 해킹가능\n /connet : 해킹을 완료한 컴퓨터에 접속, IP 안적으면 지정된 컴퓨터에 연결 시도\n /disconnet : 컴퓨터 접속 해제", true, false);
	addtxt(0, autoParent, "public", "2025.05.10", "오늘은 나의 생일이다. 매 년 저녁쯤에 형이 케이크를 사들고 왔었다. 하지만 오늘은 조용히 혼자서 생일을 보냈다. \n혼자 보내는게 익숙한 것도, 편한 것도 아니다.이제는 혼자가 익숙해져야 한다. 처음 느낀 조용함. 그 속에 있는 불편함...\n어쩌면, 난 생일을 축하받을 자격이 없을지도 모른다. 앞으로의 생일은 축하할 일이 없을 것 같다.", true,false);
	addFol(0, nullptr, "public", "Memo", true, false);
	addtxt(0, autoParent, "public", "메모1", "메모 내용", true, false);
	addtxt(0, nullptr, "private", "/help", "살려줘...", true, true); setPass("1234");
	addexe(0, nullptr, "public", "파일생성", "/addtxt 생성된_텍스트 응 이제 뛰어쓰기 가능하죠? ㅋ | /addfolder 생성된_폴더 | /in 생성된_폴더 | /addtxt 텍스트1 ㅎㅇ | /addtxt 텍스트2 ㅂㅇ | /out", true, true);
	//USB


	/*addFol(0, nullptr, "public", "USB", false, true);	// 나중에 숨김파일 처리하고 소식4번을 확인하면 나타나게 할 예정
	addtxt(0, autoParent, "public", "Detail_1", "[보안 점검 기록 - 2025.04.20 | 작성자: 김석현 (보안 관리자)]\n \n비행기 자동 운항 시스템 내부에서 알 수 없는 우회 루틴 발견.\n정상 인증 과정을 우회하여 외부 명령이 삽입 가능한 구조.\n로그 분석 결과, 아래 명령이 비정상적으로 실행됨:\nCMD: override_autopilot(true)\nCMD: set_altitude(0)\n \n공식 매뉴얼 및 코드베이스에는 존재하지 않는 방식.\n본 루틴이 악용될 경우 비행기 통제가 불가능해질 수 있음.\n \n이미 시스템이 침해당했을 가능성또한 존재.\n해당 루틴은 의도적으로 삽입된 것으로 보임. 빠른 조치가 필요함.", true);
	addtxt(0, autoParent, "public", "전송되지않은메일초안", "[전송되지 않은 메일 초안]\n \nTo: 본사 보안총괄부\nSubject: 시스템 침해 의심건\n이 루틴은 단순한 버그가 아니라, 누군가가 만든 우회 경로로 보입니다.\n192.168.00.16 에서 침입 흔적이 있으며, 접근은 최소 두 차례 이상 감지되었습니다.\n어떤 목적이었는지는 모르겠지만, 이걸 무시하면 사고로 이어질 수 있습니다.\n하지만 내부 경로를 따라온 흔적도 있어, 내부 인물이 연루되었을 가능성도 배제할 수 없습니다.\n내가 이 사실을 알았다는 것 자체가 위험할 수도 있습니다.\n정보는 백업해 두었습니다. 내가 끝까지 보고하지 못하더라도\n누군가는 이걸 봐야합니다. 내가 보고를 못할 경우.. \n전송 보류 중...", true);
	addtxt(0, autoParent, "public", "Record.wav", "\n\n[녹음 파일 자동 복구 기록 | 일부 손상됨]\n \n형: 여기 접근 좌표 확인해봤어. 포트6077에서 외부 요청이 감지됐어.\n형: 로그엔 '인증 우회' 명령이 두 번... 누군가 시스템 안으로 들어왔다는 거야.\n형: ...기록을 남겨야겠어. 더 이상 이걸 혼자 감당할 순 없어...\n \n* (통화 끊김 / 정적 발생) *", true);
	addtxt(0, autoParent, "private", "동생을 위한 서프라이즈 계획","\n1.주문제작한 케이크 들고오기\n2.생일 선물 구매하기(미정)\n노트북? 핸드폰? 애매함", true, false); setPass("0510");
	*/
	//스마트폰 
	
	// 그외 컴퓨터 파일
	// 
	// 
	// 튜토리얼 컴퓨터
	com[1].setComputer(1, "00.000.000.000", 0,0,1,0,1,1); // 컴퓨터 정보 사용자 지정
	addFol(1, nullptr, "public", "News_Collection", true);
	addtxt(1, autoParent, "public", "[속보]여객기_추락", "[속보] 하늘항공 여객기 추락... 탑승자 전원 사망\n\n2025년 5월 7일 새벽, 하늘항공 소속 여객기가 추락해 탑승자 전원이 사망하는 참사가 발생했습니다.\n사고기는 지면과 충돌한 직후 폭발했으며, 기체는 완전히 소실된 것으로 알려졌습니다.\n현재 정확한 사고 원인은 조사 중에 있으며, 관계 당국은 사고 현장을 통제하고 수습 작업에 착수했습니다.", true);
	//addtxt(1, autoParent, "private", "news_3", "", true); setPass("비밀번호 정해야함");
	addtxt(1, autoParent, "private", "news_4", "형의 유품에서 수상한 USB가 발견 되었다. 그날 이후로 나는 아무것도 할 수 없다. 티비를 보아도 그 사건만 나오고 있다. 언제쯤 괜찮아 질까\n\"내가 사건을 끝내야겠다.\"", true); setPass("1125");
	addexe(1, autoParent, "public", "USB연결하기", "/addfolder USB | /in USB | /addtxt Detail_1 [보안 점검 기록 - 2025.04.20 작성자: 김석현 (보안 관리자)]\n \n비행기 자동 운항 시스템 내부에서 알 수 없는 우회 루틴 발견.\n정상 인증 과정을 우회하여 외부 명령이 삽입 가능한 구조.\n로그 분석 결과, 아래 명령이 비정상적으로 실행됨:\nCMD: override_autopilot(true)\nCMD: set_altitude(0)\n \n공식 매뉴얼 및 코드베이스에는 존재하지 않는 방식.\n본 루틴이 악용될 경우 비행기 통제가 불가능해질 수 있음.\n \n이미 시스템이 침해당했을 가능성또한 존재.\n해당 루틴은 의도적으로 삽입된 것으로 보임. 빠른 조치가 필요함. | /addtxt 전송되지않은메일초안 [전송되지 않은 메일 초안]\n \nTo: 본사 보안총괄부\nSubject: 시스템 침해 의심건\n이 루틴은 단순한 버그가 아니라, 누군가가 만든 우회 경로로 보입니다.\n침입 흔적이 있으며, 접근은 최소 두 차례 이상 감지되었습니다.\n어떤 목적이었는지는 모르겠지만, 이걸 무시하면 사고로 이어질 수 있습니다.\n하지만 내부 경로를 따라온 흔적도 있어, 내부 인물이 연루되었을 가능성도 배제할 수 없습니다.\n내가 이 사실을 알았다는 것 자체가 위험할 수도 있습니다.\n정보는 백업해 두었습니다. 내가 끝까지 보고하지 못하더라도\n누군가는 이걸 봐야합니다. 내가 보고를 못할 경우.. \n전송 보류 중... | /addtxt Record.wav \n\n[녹음 파일 자동 복구 기록 일부 손상됨]\n \n형: 192.168.00.16 여기 접근 좌표 확인해봤어. 포트6077에서 외부 요청이 감지됐어.\n형: 로그엔 '인증 우회' 명령이 두 번... 누군가 시스템 안으로 들어왔다는 거야.\n형: ...기록을 남겨야겠어. 더 이상 이걸 혼자 감당할 순 없어...\n \n* (통화 끊김 / 정적 발생) * | /addtxt 동생을위한서프라이즈계획 \n1.주문제작한 케이크 들고오기\n2.생일 선물 구매하기(미정)\n노트북? 핸드폰? 애매함", true);
	// | /in USB | /addtxt Detail_1 [보안 점검 기록 - 2025.04.20 작성자: 김석현 (보안 관리자)]\n \n비행기 자동 운항 시스템 내부에서 알 수 없는 우회 루틴 발견.\n정상 인증 과정을 우회하여 외부 명령이 삽입 가능한 구조.\n로그 분석 결과, 아래 명령이 비정상적으로 실행됨:\nCMD: override_autopilot(true)\nCMD: set_altitude(0)\n \n공식 매뉴얼 및 코드베이스에는 존재하지 않는 방식.\n본 루틴이 악용될 경우 비행기 통제가 불가능해질 수 있음.\n \n이미 시스템이 침해당했을 가능성또한 존재.\n해당 루틴은 의도적으로 삽입된 것으로 보임. 빠른 조치가 필요함.
	// | /out | /addtxt 전송되지않은메일초안 [전송되지 않은 메일 초안]\n \nTo: 본사 보안총괄부\nSubject: 시스템 침해 의심건\n이 루틴은 단순한 버그가 아니라, 누군가가 만든 우회 경로로 보입니다.\n침입 흔적이 있으며, 접근은 최소 두 차례 이상 감지되었습니다.\n어떤 목적이었는지는 모르겠지만, 이걸 무시하면 사고로 이어질 수 있습니다.\n하지만 내부 경로를 따라온 흔적도 있어, 내부 인물이 연루되었을 가능성도 배제할 수 없습니다.\n내가 이 사실을 알았다는 것 자체가 위험할 수도 있습니다.\n정보는 백업해 두었습니다. 내가 끝까지 보고하지 못하더라도\n누군가는 이걸 봐야합니다. 내가 보고를 못할 경우.. \n전송 보류 중... | /out | /addtxt Record.wav \n\n[녹음 파일 자동 복구 기록 | 일부 손상됨]\n \n형: 192.168.00.16 여기 접근 좌표 확인해봤어. 포트6077에서 외부 요청이 감지됐어.\n형: 로그엔 '인증 우회' 명령이 두 번... 누군가 시스템 안으로 들어왔다는 거야.\n형: ...기록을 남겨야겠어. 더 이상 이걸 혼자 감당할 순 없어...\n \n* (통화 끊김 / 정적 발생) * | /out | /addtxt 동생을 위한 서프라이즈 계획 \n1.주문제작한 케이크 들고오기\n2.생일 선물 구매하기(미정)\n노트북? 핸드폰? 애매함 | /out | /out | /out | /out
	//| /addtxt 동생을 위한 서프라이즈 계획 \n1.주문제작한 케이크 들고오기\n2.생일 선물 구매하기(미정)\n노트북? 핸드폰? 애매함 | /out | /out
	//addtxt(1, autoParent, "public", "2025.05.07", "오늘 새벽, 너를 하늘로 보냈다.\n텔레비전에서 전원 사망이라는 자막이 떴을 때,\n나는 그 말을 믿을 수 없었다.믿고 싶지 않았다.\n하지만 결국, 그 안에 네 이름이 있다는 걸 받아들여야 했다.\n\n아직도 네 방은 그대로다.\n너는 아무 말 없이 떠났고, 나는 아무 말도 해줄 수 없었다.\n\n딸아, 아빠가 미안해.\n그날 아침, 너를 껴안아주지 못한 게 너무 후회돼.\n다음 생엔... 꼭 더 많이 웃게 해줄게.", true); setPass("1125");

	// 형의 스마트폰
	com[2].setComputer(2, "스마트폰", 0, 0, 1, 0, 1, 1); // 컴퓨터 정보 사용자 지정
	//com[2].setComputer(2, "123.456.789", 0, 1, 0, 1, 0, 0);
	//addFol(2, nullptr, "public", "스마트폰", true); setPass("김석현");	// 마찬가지로 나중에 숨김파일 처리하고 USB를 확인하면 나타나게 할 예정 패드워드는 다른곳에서 찾을수 있게 설정

	addFol(2, nullptr, "public", "Message", true);

	addtxt(2, autoParent, "public", "[보안팀장]", "[4/21 09:44]\n \n석현 씨, 그건 그냥 테스트 루틴이야. 작년에도 나왔던 거잖아. 오버좀 하지마.\n우리 지금 연차도 없고, 민감한 시기인 거 알잖아.\n조용히 묻고 지나가자. 시스템 바꾸는 건 본사 허락 없인 안 돼 알잖아\n우리 귀찮게 하지말자", true);
	addtxt(2, autoParent, "public", "[알수없는번호]", "[4/19 20:32]\n \n그 루틴 너만 본 거 아니야. 다른 사람들도 다 봤어. 하지만 입 다물었지.\n왜 아직도 그걸 파냐고 하더라. 조심해.\n모든 게 기록되고 있어. 네 위치도 마찬가지야.", true);
	addtxt(2, autoParent, "public", "[엄마]", "[4/19 20:32]\n \n석현아 이번 주말에 집에 올 수 있니?", true);

	addFol(2, nullptr, "public", "Call_Log", true);

	addtxt(2, autoParent, "public", "[조현철교수님]", "[5/7 01:55]", true);
	addtxt(2, autoParent, "public", "[차재승]", "[5/3 16:08]\n \n따흐!!!!!!!!", true);
	addtxt(2, autoParent, "public", "[버락오바마]", "[5/2 04:32]", true);
	addtxt(2, autoParent, "public", "[이상혁]", "[13/12 25:32]", true);
	addtxt(2, autoParent, "public", "[도날드트럼프]", "[2/22 22:22]", true);
	addtxt(2, autoParent, "public", "[트랄랄레로트랄랄라라]", "[2/17 12:32]", true);
	addtxt(2, autoParent, "public", "[노드현]", "[1/26 17:08]", true);
	addtxt(2, autoParent, "public", "[노드현]", "[1/26 17:08]", true);
	addtxt(2, autoParent, "public", "[노드현]", "[1/26 17:08]", true);
	addtxt(2, autoParent, "public", "[노드현]", "[1/26 17:08]", true);
	addtxt(2, autoParent, "public", "[노드현]", "[1/26 17:08]", true);
	addtxt(2, autoParent, "public", "[노드현]", "[1/26 17:08]", true);
	addtxt(2, autoParent, "public", "[노드현]", "[1/26 17:08]", true);
	addtxt(2, autoParent, "public", "[노드현]", "[1/26 17:08]", true);


	// 가정집

	// 강현은 아들이고 강석은 아빠임
	com[3].setComputer(3, "192.168.00.16", 1, 0, 1, 0, 0, 0); // 컴퓨터 정보 사용자 지정

	addFol(3, nullptr, "public", "내PC", true);
		addFol(3, autoParent, "public", "다운로드", true);

	addFol(3, nullptr, "public", "카카오톡", true);
		addFol(3, autoParent, "private", "강현", true, false);setPass("0126");
			addtxt(3, autoParent, "public", "아빠", "                .\n                .\n                .\n          -2025.03.25-\n \n아들 잘 지내지? 밥 잘 챙겨먹고 잘지내\n \n                           응 잘지내고 있어\n \n          -2025.4.28-\n \n                           아빠 생일 축하해\n \n고마워 아들",true);

		addFol(3, com[3].getFile(1), "private", "강석", true);setPass("0428");
			addtxt(3, autoParent, "public", "K", "                .\n                .\n                .\n          -2011.11.11-\n \n실제적용은 그쪽 항공이 먼저야\n \n                           알겠어.\n \n", true);
	
	addFol(3, nullptr, "public", "Chrome", true);
		addFol(3, autoParent, "public", "naver.com", true);
			addFol(3, autoParent, "private", "jung5004", true);setPass("0428");
				addFol(3, autoParent, "public", "메일", true);
					addexe(3, autoParent, "public", "카카오톡으로_인증", "/out | /out | /out | /out | /in 카카오톡 | /in 종호 | /addtxt 카카오톡인증 5687 | /out | /out | /out | /in Chrome | /in naver.com | /in jung5004 | /in 메일 | /addtxt jlee@kflsys.net 보낸 사람:jung5004\n받는 사람: jlee@kflsys.net\n제목: deployment memo\n \nTX217에서 확실히 반응이 있었다. 예외 입력은 무시되었고\n목표 궤도에 정확히 진입했다. 남은 건 본 운용뿐이다.\n | /addexe Download.browserhistory.json /out | /out / out /out /out /in 다운로드 /addtxt browserhistory.json {\n  tx_id: TX217,\n  route:[VXNlckFsdGF8MTcyLjIyLjkuNDE=, cmVsYXk4OA==]\n} | /out | /out | /in Chrome | /in naver.com | /in jung5004 | /in 메일 | /in jlee@kflsys.net", true);

			addFol(3, com[3].getFile(2)->getFile(0), "public", "검색목록", true); //9
				addtxt(3, autoParent, "public", "비행기사건", "비행기가 추락했다 사람이 죽었다", true);

		addFol(3, com[3].getFile(2), "public", "youtube.com", true);
			addtxt(3, autoParent, "public", "건전한사람", "브르르브르르파타핌브르르르르파타핌침판지니바나니니퉁퉁퉁사후르", true);
		addFol(3, com[3].getFile(2), "public", "edward.kmu.ac.kr", true);
			addtxt(3, autoParent, "public", "뜨아이이이", "학점이 이상해!!", true);
		addFol(3, com[3].getFile(2), "public", "ctl.kmu.ac.kr", true);
			addtxt(3, autoParent, "public", "뜨아이이이", "과제가 너무 많아..", true);
		
	addFol(3, nullptr, "public", "휴지통", true);
		addtxt(3, autoParent, "public", "browserhistory.html", "forum.darknexus.io/post/7495\nkflsys.net / internal / TRG - control.html\nTRG actuator not responding?", true);

	addFol(3, nullptr, "public", "CCTV", true);
		addFol(3, autoParent, "public", "거실", true);
			addtxt(3, autoParent, "public", "가족사진", "중호의 탄생일 2003.01.26", true);
		addFol(3, com[3].getFile(4), "public", "주방", true);
			addtxt(3, autoParent, "public", "주방_사진", "주방 사진", true);
		addFol(3, com[3].getFile(4), "public", "중호방", true);
			addtxt(3, autoParent, "public", "중호의_방_사진", "중호의 방 사진", true);
	

	

	com[4].setComputer(4, "172.22.9.41", 1, 1, 1, 1, 1, 1); // 컴퓨터 정보 사용자 지정
	addFol(4, nullptr, "public", "src", true);
		addFol(4, autoParent, "public", "logs", true);
			addtxt(4, autoParent, "public", "observer", "[04:11:05] 외부 접속 탐지: 192.168.88.94\n[04:11 : 09] 사용자: jlee_localtest 권한 요청\n[04:11 : 10] 로그 접근 : test_results / TRG17 - LOCKED.enc\n[04:11 : 12] 경고 : 암호화된 테스트 결과 파일 접근 시도(잠금 상태)", true);
			addFol(4, com[4].getFile(0)->getFile(0), "public", "test_results", true);
				addtxt(4, autoParent, "private", "TRG17-LOCKED.enc", "[해제 완료]\n[TRG 실험 보고서 #17]\n기체 ID : TX217\nOverride 반응 : 수신 후 1.1초 내 조종 입력 무시됨\n접속 계정 : iqlogin_0921\n비고 : override 키, relay88 통해 전송됨", true, false, true); setPass("enotniopeno");

			addFol(4, com[4].getFile(0)->getFile(0), "public", "TRG17-LOCKED.enc", true);
				addtxt(4, autoParent, "public", "sys_routemap.xml", "sys_routemap.xml\n< routes >\n<nexthop>\n<name>SEIA 메인 서버< / name>\n<ip>c2VpYS5jb3JwOjQyMDA = < / ip> <!--base64-->\n< / nexthop>\n< / routes> 복호화하면 -> 이거 보이게 seia.corp:4200", true);

		addFol(4, com[4].getFile(0), "public", "notes", true);
			addtxt(4, autoParent, "public", "key_hint.txt", "테스트 결과 파일은 실험 반응 시간 기반으로 암호화됨.\n기억하라, 그 수치는 1.1초였다.\n힌트: 뒤집어 생각해보면, 답이 보일지도 ? ", true);//정답 1.1초를 1.1one -> enotniopeno
			addtxt(4, autoParent, "public", "engineer_chat.log", "[03:44] han_lee: relay 노드에 비밀번호 또 안 바꿨냐?\n??? : 난 이 조합이 좋아.커피 + 비행기 + 내 번호.\n[03:47] han_lee: 또 그 얘기야? 테스트 #35 성공했다고 몇 년째 우려먹냐.\n[03:48] han_lee: 그리고 진짜 바꿔라. 누가 봐도 유추되겠다.", true);


		addFol(4, com[4].getFile(0), "public", "src", true);
			addFol(4, com[4].getFile(0)->getFile(0), "public", "TRG", true);
			addtxt(4, autoParent, "pubilc", "codesheet.jpg","[TRG 시스템 접근 정보 - 사내 테스트용]\n \n인증 계정 : seia - corp / iqlogin_0921\n필요 키 : ******", true);

		addFol(4, com[4].getFile(0), "public", "mail", true);

			

	com[5].setComputer(5, "seia.corp:4200", 1, 1, 1, 1, 1, 1);
	addFol(5, nullptr, "public", "logs", true);
		addFol(5, com[5].getFile(0), "public", "access", true);
			addtxt(5, com[5].getFile(0)->getFile(0), "public", "2025-04-17.log", "[23:19:42] 사용자 접속: iqlogin_0921 from 192.168.88.94\n[23:19:47] relay88_route.cfg 접근\n[23:19:50] a0417.gz.enc 파일 다운로드 요청\n[23:19:52] 로그 백업 전환 시작 : archive_A0417.lgz 로 이관", true);
		addFol(5, com[5].getFile(0), "public", "netstat_report.md", true);
		addFol(5, com[5].getFile(0), "public", "backup", true);
			addtxt(5, com[5].getFile(0)->getFile(2), "public", "archive_A0417.lgz", "[12:01:10] 테스트 시작: relay88 latency test \n[12:01:13] 결과: 평균 응답 속도 22ms\n[12:05:22] 디버그 로그 : guest88 권한 오류\n[12:11:12] config.ini 포맷 충돌 감지 → 기본값으로 복원됨", true);
	addFol(5, nullptr, "public", "devtools", true);
		addFol(5, com[5].getFile(1), "public", "decoder", true);
			addtxt(5, com[5].getFile(1)->getFile(0), "public", "decompress.keyhint", "압축 해제 키는 '경고 메일'의 base값에 있음.\n첫 문장의 글자 수를 2진수로 바꿔라(8자리).", true);
		addFol(5, com[5].getFile(1), "public", "keygen", true);
			addtxt(5, com[5].getFile(1)->getFile(1), "public", "authmap.png", "User Map:\n- seia_root\n- relay_test\n- iqlogin_0921\n- atcproxy", true);
		addFol(5, com[5].getFile(1), "public", "relay_debug", true);
			addtxt(5, com[5].getFile(1)->getFile(2), "public", "autyo_transfer.c", "", true);
			addtxt(5, com[5].getFile(1)->getFile(2), "public", "precompile.json", "", true);

	addFol(5, nullptr, "public", "mail", true);
		addFol(5, autoParent, "public", "admin", true);
			addtxt(5, autoParent, "public", "warn.txt", "[관리자 경고]\n \nCheck relay routing immediately.", true);
			addtxt(5, autoParent, "public", "enc_req.dat", "", true);

	addFol(5, nullptr, "public", "testdata", true);
		addFol(5, autoParent, "public", "fightctrl", true);
			addtxt(5, autoParent, "public", "relay88_route.cfg", "[RELAY88_CONFIGURATION]\nsecure_id = TX217\nrelay_chain = proxy - khan42 → atcproxy\nauth_required = true",true);
	addFol(5, nullptr, "public", "tmp", true);
		addtxt(5, autoParent, "public", "a0417.gz.enc", "[EXFIL TRACE LOG - INTERNAL USE ONLY]\n \n파일: relay88_route.cfg\n조작 시도 : iqlogin_0921\n원격 포트 : 8022\n전송 위치 : atc - nexus.aircorp : 8022\n→ 타깃 시스템 : 관제탑 연계 서버(NEXUS GATEWAY)\n로그 제거 시도 감지됨.추적 ID : YJ1029(삭제 성공 여부 : Unknown)", true);
	
	


	com[6].setComputer(1, "44.444.444.444", 0, 0, 0, 0, 0, 0);

	// 개인폴더도 넣을까 생각중

	addFol(6, nullptr, "public", "업무용", true); 
	addFol(6, autoParent, "public", "운항일지");
	addtxt(6, autoParent, "public", "04-01", "\n \n [운항일지 - 정기 노선 점검 보고서]\n \n -노선명: ICN-NRT (도쿄 노선)\n \n -기체번호: HL8271\n \n -운항일자: 2025.04.01\n \n -기장: 이재훈\n \n -부기장: 박수연\n \n 비행 요약\n \n -출발 시간: 08시 10분\n \n -도착 시간: 11시 25분\n \n -총 비행시간: 3시간 15분\n \n -기상 조건: 맑음, 시정 10km 이상\n \n 점검 사항\n \n -APU 상태 양호\n \n -연료 주입량: 0421리터\n \n -랜딩기어 작동 정상\n \n -조종석 계기판 리셋 후 자동 복원 완료\n \n 비고\n \n -승객 탑승률 84.2퍼센트\n \n -4번 좌석 구역에서 이물질 발견되어 청소 강화 요청\n \n -착륙 전 추가 감속 시행\n \n -담당자 서명: LJH", true);
	addtxt(6, autoParent, "public", "04-03", "\n \n [운항일지 - 정기 노선 점검 보고서]\n \n -노선명: ICN-KIX (오사카 노선)\n \n -기체번호: HL8237\n \n -운항일자: 2025.04.03\n \n -기장: 김석현\n \n -부기장: 조예린\n \n 비행 요약\n \n -출발 시간: 09시 30분\n \n -도착 시간: 12시 10분\n \n -총 비행시간: 2시간 40분\n \n -기상 조건: 구름 많음, 풍속 15노트\n \n 점검 사항\n \n -자동 조종 장치 정상 작동\n \n -연료 주입량: 0510리터\n \n -엔진 진동 수치 초과 기록 있음, 정비팀 분석 요청\n \n 비고\n \n -관제 통신 지연 발생\n \n -이착륙 절차 이상 없음\n \n -부기장 조작 지원 적절\n \n -담당자 서명: KSH",true);
	addtxt(6, autoParent, "public", "04-05","\n \n [운항일지 - 정기 노선 점검 보고서]\n \n -노선명: ICN-TPE (타이베이 노선)\n \n -기체번호: HL8201\n \n -운항일자: 2025.04.05\n \n -기장: 박소영\n \n -부기장: 정우성\n \n 비행 요약\n \n -출발 시간: 07시 45분\n \n -도착 시간: 10시 25분\n \n -총 비행시간: 2시간 40분\n \n -기상 조건: 흐림, 약한 비\n \n 점검 사항\n \n -착륙 시 하중 초과 경고\n \n -연료 주입량: 0488리터\n \n -프랩 작동 시험 완료\n \n 비고\n \n -수하물 재분배 지연 7분\n \n -관제 통신 정확도 양호\n \n -비상 매뉴얼 오염으로 교체 요청 접수\n \n -담당자 서명: PSY", true);
	addtxt(6, autoParent, "public", "04-07","\n \n [운항일지 - 정기 노선 점검 보고서]\n \n -노선명: ICN-BKK (방콕 노선)\n \n -기체번호: HL8244\n \n -운항일자: 2025.04.07\n \n -기장: 송지훈\n \n -부기장: 이다현\n \n 비행 요약\n \n -출발 시간: 10시 15분\n \n -도착 시간: 13시 55분\n \n -총 비행시간: 3시간 40분\n \n -기상 조건: 흐림, 적란운 경보\n \n 점검 사항\n \n -연료 주입량: 0510리터\n \n -엔진 진동 센서 오차 2퍼센트\n \n -접지 마찰음 강함\n \n 비고\n \n -응급 키트 사용 사례 1건\n \n -게이트 연결 지연 3분\n \n -관제 협조 양호\n \n -담당자 서명: SJH", true);
	addtxt(6, autoParent, "public", "04-09","\n \n [운항일지 - 정기 노선 점검 보고서]\n \n -노선명: ICN-SGN (호치민 노선)\n \n -기체번호: HL8250\n \n -운항일자: 2025.04.09\n \n -기장: 유다연\n \n -부기장: 김태윤\n \n 비행 요약\n \n -출발 시간: 06시 20분\n \n -도착 시간: 09시 40분\n \n -총 비행시간: 3시간 20분\n \n -기상 조건: 맑음, 온도 28도\n \n 점검 사항\n \n -기내기압 급변 경고 -> 자동 보정 작동\n \n -연료 주입량: 0510리터\n \n -APU 착륙 후 재시동 1회\n \n 비고\n \n -탑승 서류 지연 발생\n \n -기내 안내방송 미출력\n \n -민원 접수 없음\n \n -담당자 서명: YDY", true);
	addFol(6, autoParent->getParent(), "public", "회의록");
	addtxt(6, autoParent, "public", "04-20", "\n \n [정기 업무 회의록]\n \n -일시: 2025년 4월 20일 오전 9시\n \n -장소: 3층 전략기획실 회의실\n \n -참석자: 김석현, 박정우, 이다현, 조민아\n \n -기록자: 이다현\n \n 회의 안건\n \n -상반기 노선 운영 전략 검토\n \n -신규 시스템 교육 일정 조율\n \n -사내 테스트 서버 접근 암호 통일 여부\n \n 주요 발언\n \n -박정우: 사내 교육용 장비는 다 암호를 다르게 쓰니까 헷갈려요\n \n -김석현: 테스트용이니까 그냥 0510으로 통일해\n \n -조민아: 숫자 익숙하긴 하네요. 외우기 쉬워요\n \n 결론\n \n -다음 분기부터 테스트 장비 접근 암호는 0510으로 임시 고정\n \n -신규 시스템 교육은 4월 말부터 2주 간 실시 예정", true);
	addtxt(6, autoParent, "public", "04-22", "\n \n [기술부 장비관리 회의록]\n \n -일시: 2025년 4월 22일 오후 3시\n \n -장소: 기술지원실 회의실 B\n \n -참석자: 강대리, 정과장, 김차장\n \n -기록자: 정과장\n \n 회의 안건\n \n -장비 점검 결과 공유\n \n -예비 비상코드 재정비\n \n -장비 교체 우선순위 논의\n \n 주요 내용\n \n -2번 장비에서 반복 오류 발생, 재부팅 시에도 해제 불가\n \n -장비별 초기화 시나리오 정리 필요\n \n -긴급 수리 대상 2건 지정됨\n \n 조치 사항\n \n -오류 장비는 즉시 수리 의뢰\n \n -예비코드 방안은 추후 논의로 이월", true);
	addtxt(6, autoParent, "public", "04-24", "\n \n [보안정책 수립 사내 간담회]\n \n -일시: 2025년 4월 24일 오전 10시\n \n -참석자: 김팀장, 이대리, 박정우, 임수빈\n \n -장소: 2층 회의실 A\n \n -기록자: 임수빈\n \n 안건\n \n -비상상황 시 데이터 접근 권한\n \n -패스코드 관리 방식 개선\n \n -암호화 장비 배치 순서\n \n 발언 요약\n \n -각 부서별 접근 권한 차등 설정 검토\n \n -테스트 장비 보안 강화 요청\n \n -정책 개정 시 타 부서 공지 필수\n \n 결론\n \n -신규 정책 초안 다음 회의 전까지 작성", true);
	addtxt(6, autoParent, "public", "04-26", "\n \n [운항안전실 주간회의록]\n \n -일시: 2025년 4월 26일 오후 4시\n \n -장소: 비행운영실 회의실\n \n -참석자: 송지훈, 정예슬, 유다연, 강현우\n \n -기록자: 유다연\n \n 안건\n \n -전주 운항 중 이상사항 점검\n \n -기내 방송 장비 점검 결과\n \n -지상 대응 매뉴얼 재검토\n \n 회의 결과\n \n -기내 방송 관련 오류 없음\n \n -매뉴얼 인쇄물 일부 누락 확인 -> 재배포 요청\n \n -긴급 대응 체크리스트 항목 보완 필요", true);
	addtxt(6, autoParent, "public", "04-28", "\n \n [시스템 유지관리 전략 회의록]\n \n -일시: 2025년 4월 28일 오전 8시 30분\n \n -장소: 1층 정보보안실\n \n -참석자: 김진수, 박정우, 이다현\n \n -기록자: 김진수\n \n 의제\n \n -서버 재시작 인증 프로세스 검토\n \n -장비별 기본 설정 초기화 범위\n \n -시스템 연동 체크 절차 정리\n \n 논의 내용\n \n -서버 로그인 동기화 오류 보고됨\n \n -장비별 관리 포맷 일원화 필요\n \n -초기화 순서표 재작성 후 배포 예정", true);
	addFol(6, autoParent->getParent(), "public", "출장비정산내역서");
	addtxt(6, autoParent, "public", "김석현", "\n \n [출장비 정산서]\n \n -성명: 김석현\n \n -소속 부서: 전략기획팀\n \n -출장 기간: 2025년 5월 9일 ~ 2025년 5월 10일\n \n -출장지: 부산 (BEXCO 박람회 참석)\n \n 경비 내역\n \n -교통비: 83,000원\n \n -숙박비: 97,000원\n \n -식비: 54,000원\n \n -총합계: 234,000원\n \n 비고\n \n -숙소 입실 시 전자 도어락 암호 입력 필요\n \n -테스트용 임시 비밀번호로 0510 사용됨\n \n 확인: 경리팀 김하늘\n \n 승인: 전략기획실장 최용진", true);
	addtxt(6, autoParent, "public", "이다현", "\n \n [출장비 정산서]\n \n -성명: 이다현\n \n -소속 부서: 고객지원실\n \n -출장 기간: 2025년 4월 2일 ~ 2025년 4월 4일\n \n -출장지: 제주도 본사 연수\n \n 경비 내역\n \n -항공료: 112,000원\n \n -숙박비: 2박 180,000원\n \n -식비: 45,000원\n \n -렌트비: 88,000원\n \n -총합계: 425,000원\n \n 비고\n \n -식대는 전일정 동일 업체 이용\n \n -렌트카 기름은 법인카드 사용 처리\n \n -확인: 총무 이정훈\n \n -승인: 고객지원팀장 박선영", true);
	addtxt(6, autoParent, "public", "박정우", "\n \n [출장비 정산서]\n \n -성명: 박정우\n \n -소속 부서: 운영본부\n \n -출장 기간: 2025년 3월 15일 ~ 2025년 3월 17일\n \n -출장지: 대전 지사 시스템 점검\n \n 경비 내역\n \n -교통비: 67,500원\n \n -숙박비: 120,000원\n \n -식비: 52,000원\n \n -총합계: 239,500원\n \n 비고\n \n -지사 서버 점검 중 야간근무 수당 별도 지급 예정\n \n -영수증 분실로 일부 금액 총괄 정산\n \n -확인: 재무팀 이승철\n \n -승인: 운영실장 김태호", true);
	addtxt(6, autoParent, "public", "조민아", "\n \n [출장비 정산서]\n \n -성명: 조민아\n \n -소속 부서: 품질관리팀\n \n -출장 기간: 2025년 5월 5일 ~ 2025년 5월 6일\n \n -출장지: 청주 공장 샘플 검사\n \n 경비 내역\n \n -교통비: 58,000원\n \n -숙박비: 1박 82,000원\n \n -식비: 41,000원\n \n -총합계: 181,000원\n \n 비고\n \n -검사 진행 중 일부 시료 반송됨\n \n -택배비는 현장 부서에서 직접 청구 처리 예정\n \n -확인: 총무 권상우\n \n -승인: 품질팀장 윤소정", true);
	addtxt(6, autoParent, "public", "정기표", "\n \n [출장비 정산서]\n \n -성명: 정기표\n \n -소속 부서: 기술연구소\n \n -출장 기간: 2025년 4월 12일 ~ 2025년 4월 14일\n \n -출장지: 광주 공장 유지보수 회의\n \n 경비 내역\n \n -KTX 왕복: 92,000원\n \n -숙박비: 89,000원\n \n -식비: 37,000원\n \n -기타비용: 12,000원 (회의 자료 출력 등)\n \n -총합계: 230,000원\n \n 비고\n \n -회의 일정 조정으로 귀사 하루 연기됨\n \n -기술 문서 인쇄비 별도 증빙 제출함\n \n -확인: 경리 최나영\n \n -승인: 연구소장 문태성", true);
	addFol(6, autoParent->getParent(), "public", "장비점검기록서");
	addtxt(6, autoParent, "public", "04-15", "\n \n [장비점검기록서]\n \n -점검일자: 2025년 4월 15일\n \n -점검자: 정예슬\n \n -장비명: HN-LASER측정기 (모델: HL5000X)\n \n -설치 위치: 본관 3층 계측실\n \n 점검 항목\n \n -전원 상태: 정상\n \n -교정 오차 범위: +-0.02mm (허용 범위 이내)\n \n -장비 응답 속도: 표준값 대비 98% 수준\n \n -센서 정렬 상태: 양호\n \n 특이사항\n \n -레이저 발진 지연 약 1초 발생 -> 사용 지장 없음\n \n -다음 교정 일정: 2025년 10월 예정\n \n -서명: 정예슬", true);
	addtxt(6, autoParent, "public", "04-18", "\n \n [장비점검기록서]\n \n -점검일자: 2025년 4월 18일\n \n -점검자: 김태윤\n \n -장비명: 자동 토크 측정기 (모델: ATQ-2200)\n \n -설치 위치: 청주 제2공장 QC실\n \n 점검 항목\n \n -전원 상태: 정상\n \n -측정값 반복오차: +-0.1Nm (기준값 이내)\n \n -디지털 화면 반응속도: 정상\n \n -내부 모듈 이상 없음\n \n 특이사항\n \n -터치패널 교체 이력 있음, 반응 속도 안정화 완료\n \n -수기 테스트 로그 백업 완료\n \n -서명: 김태윤", true);
	addtxt(6, autoParent, "public", "04-22", "\n \n [장비점검기록서]\n \n -점검일자: 2025년 4월 22일\n \n -점검자: 박정우\n \n -장비명: 전자식 압력계 (모델: PVM-88)\n \n -설치 위치: 1공장 배관 테스트룸\n \n 점검 항목\n \n -전원 상태: 정상\n \n -유압 반응 속도: 0.8초 이내\n \n -오차율: 0.15% (기준값 0.3% 이하)\n \n -배터리 상태: 충전량 85%\n \n 특이사항\n \n -벽면 고정 브래킷 느슨함 발견 -> 현장 조치 완료\n \n -관리자용 초기화 암호 0510 입력하여 설정 복구\n \n -서명: 박정우", true);
	addtxt(6, autoParent, "public", "04-24", "\n \n [장비점검기록서]\n \n -점검일자: 2025년 4월 24일\n \n -점검자: 이다현\n \n -장비명: 고속 이미지 판독기 (모델: VIS-9000)\n \n -설치 위치: 본사 연구동 2층\n \n 점검 항목\n \n -판독 정확도: 99.3%\n \n -전원 상태: 정상\n \n -소프트웨어 버전: v1.12.3 (최신)\n \n -점등 센서 응답률: 정상\n \n 특이사항\n \n -저장용량 경고 발생 -> 이미지 로그 3일치 삭제 후 정상 복귀\n \n -권장 유지보수 주기 도래 -> 5월 초 요청 예정\n \n -서명: 이다현", true);
	addtxt(6, autoParent, "public", "04-26", "\n \n [장비점검기록서]\n \n -점검일자: 2025년 4월 26일\n \n -점검자: 유다연\n \n -장비명: 휴대용 가스 감지기 (모델: GAS-Guard)\n \n -설치 위치: 소방안전보관소\n \n 점검 항목\n \n -센서 반응시간: 1.3초\n \n -경고음 작동 여부: 정상\n \n -내장 배터리 상태: 충전 필요\n \n -외관 파손 여부: 이상 없음\n \n 특이사항\n \n -지난달 센서 보강 이후 감지 민감도 향상됨\n \n -2일 간격으로 자동 자가점검 진행 설정됨\n \n -서명: 유다연", true);
	addFol(6, autoParent->getParent(), "public", "공지사항");
	addtxt(6, autoParent, "public", "공지사항01", "\n \n [보안 시스템 임시 점검 안내]\n \n -일시: 2025년 5월 2일\n \n -부서: 정보보안실\n \n 내용\n \n -전 사내망 보안 시스템 점검이 아래 일정으로 진행될 예정입니다.\n \n -점검 일시: 2025년 5월 5일(월) 21시 ~ 23시\n \n -점검 내용: 서버 방화벽 정책 갱신 및 백업 장비 리부트\n \n -영향 범위: 사내 공유폴더 접근 제한 가능성 있음\n \n -일부 테스트 장비는 임시 접근 코드로 설정됩니다.\n \n -기본 접근 비밀번호는 0510으로 통일되며, 점검 완료 후 재설정 바랍니다.\n \n -문의: 보안담당 정지호 (내선 321)", true);
	addtxt(6, autoParent, "public", "공지사항02", "\n \n [복사기 교체 및 재등록 안내]\n \n -일시: 2025년 5월 1일\n \n -부서: 총무팀\n \n 내용\n \n -1층, 2층, 4층 사무실 복사기 기종이 아래 일정에 따라 교체됩니다.\n \n -교체 일시: 5월 3일(금) 오전 9시~11시\n \n -신규 기종: RICOH MP3054\n \n -설정: 개별 사용자 ID 등록 필요\n \n -기존에 등록된 출력 설정은 유지되지 않으며, 교체 후 재등록 바랍니다.\n \n -설치 후 매뉴얼은 메일로 공지 예정입니다.\n \n -문의: 총무과 김하늘 (내선 216)", true);
	addtxt(6, autoParent, "public", "공지사항03", "\n \n [사내 식당 식자재 납품 일정 변경 안내]\n \n -일시: 2025년 4월 30일\n \n -부서: 복지후생팀\n \n 내용\n \n -5월 초 황금연휴로 인해 식자재 공급 일정이 아래와 같이 조정됩니다.\n \n -기존 납품일: 매주 화요일\n \n -변경 납품일: 5월 한정으로 매주 수요일\n \n -이에 따라 메뉴 편성에도 일부 변동이 있을 수 있습니다.\n \n -불편을 최소화하기 위해 품목 변경 없이 공급 예정입니다.\n \n -문의: 후생팀 김다은 (내선 143)", true);
	addtxt(6, autoParent, "public", "공지사항04", "\n \n [휴가 신청 시스템 업데이트 공지]\n \n -일시: 2025년 4월 29일\n \n -부서: 인사팀\n \n 내용\n \n -휴가 신청 웹 시스템이 5월부터 새로운 인터페이스로 전환됩니다.\n \n -변경 일자: 5월 6일\n \n -주요 변경사항: 모바일 최적화, 전자결재 연동, 캘린더 표시 개선\n \n -기존 신청 내역은 자동 이관됩니다\n \n -시연회는 5월 2일 오전 11시에 1층 소회의실에서 진행됩니다.\n \n -문의: 인사팀 박수연 (내선 208)", true);
	addtxt(6, autoParent, "public", "공지사항05", "\n \n [사내 금연 구역 확대 시행 안내]\n \n -일시: 2025년 4월 27일\n \n -부서: 안전보건실\n \n 내용\n \n -사내 금연 구역 확대에 따라 아래 구역은 전면 금연으로 지정됩니다.\n \n -확대 시행일: 5월 1일부\n \n -추가 지정 구역: 주차장 연결통로, 2층 로비 앞, 구내식당 입구\n \n -흡연은 지정된 외부 흡연구역에서만 가능합니다.\n \n -위반 시 인사 규정 제18조에 따라 조치됩니다.\n \n -문의: 안전관리 담당 조민아 (내선 155)", true);



	addFol(6, nullptr, "private", "비밀문서", true);setPass("0510"); // #0510, 업무용폴더에 비번힌트 각 폴더 마다 한개 텍스트사이에 넣어놨음 힌트
	addFol(6, autoParent, "public", "경영");
	addtxt(6, autoParent, "public", "비용처리관련문서", "\n \n [내부회계감사보고서 발췌 - 2023.11.07]\n \n - 감사팀은 하늘항공 본사의 2022~2023년 회계자료 중 유류비 계정을 정밀 분석함.\n - 총 4억 7천만 원에 해당하는 유류비가 실제 운항기록과 불일치하는 것으로 확인됨.\n - 출장비 청구 건 중, 임원 김OO 외 3인이 동일 날짜에 중복된 지역으로 각각 출장비를 청구함.\n \n [비고]\n \n - 항공유류비, 차량 렌트, 숙박비, 식비 등 항목 중 일부는 실제 법인카드 사용 내역과 불일치.\n - '출장대행업체' 명목의 개인 계좌 입금 내역 존재.\n \n - 해당 보고서는 외부 감사인에게 전달되지 않음. 내부 참고용.\n", true);
	addtxt(6, autoParent, "public", "페이퍼컴퍼니관련문서", "\n \n [비밀 문건 - 재무부 사내 보고용]\n \n - 2021년 4월 설립된 오로라글로벌물류 는 법적으로 독립된 외주사이나, 실제로는 정OO 부사장 친인척이 대표로 등록됨.\n - 동사는 1년 간 약 32건의 물류 계약을 단독 수주하였으며, 단가가 시장가 대비 평균 180% 이상으로 책정됨.\n \n - 자금 흐름 분석 결과:\n  하늘항공 - 오로라글로벌 (정기 송금) - 개인 계좌 (차명 명의)로 분산 입금\n  총액: 약 12.6억 원\n \n [내부 대화 녹취 요약]\n 감사팀은 손 안 댑니다. 우리가 미리 손 써놨어요. - 재무부 이팀장", true);
	addtxt(6, autoParent, "public", "노선배정로비관련문서", "\n \n [기획실 문건 - '노선전략 추진 내역']\n \n - 2022년 3월: 동남아 직항 신규 노선 확보를 위해 교통부 고위 관료 2명 접촉\n - 사외이사 명단에 교통부 출신 AOO 전 국장을 영입\n - 2022.05.17: '자문료' 명목으로 3,200만원 지급\n \n [이후 진행사항]\n - 경쟁사 J항공이 동남아 노선 심사 탈락\n - 하늘항공, '전략노선 안정성 확보' 사유로 단독 배정 성공\n \n 비고: 외부 언론 노출 우려 있음. 전략기획실 내 공유 금지.", true);
	addtxt(6, autoParent, "public", "법안관련문서", "\n \n [정치권 네트워크 메모 - 비공식 문건]\n \n - 현직 국회의원 2인과 정기 간담회 (2023년 2분기 기준)\n - 2022.09~2023.03: 항공안전법 개정안 저지 로비 진행\n  - 주요 내용: 정비 내역 공개 의무화 조항 삭제 추진\n \n - 정치자금법 우회 대응\n  - A재단 후원금 명목으로 1억 2천만 원 기부\n  - 대표자: 전략실 B이사의 배우자\n \n [주의]\n - 국정감사 대비해 관련 파일 암호화 필요\n - 대응 문건은 대외 협력팀에서 일괄 작성 예정", true);
	addFol(6, autoParent->getParent(), "public", "인사");
	addtxt(6, autoParent, "public", "채용평가표분석보고서", "\n \n [채용 평가표 분석 보고서 - HR기획팀 (비공개)]\n \n 공채 18기 객실승무원 면접 평가표 확인 결과:\n - A지원자 (기준 미달): 서류전형 탈락 대상 -> 실제 최종 합격\n - B지원자 (면접 점수: 73점) -> 시스템에는 91점으로 수정 반영됨\n \n [내부 대화 기록]\n 면접관 C: 'B는 사장님 조카야. 1차에서라도 좀 걸러줘야 했는데.'\n 인사팀 D: '점수는 내가 맞춰놨어. 시스템 들어가서 확인해봐.'\n \n 비고:\n - 채용 시스템 접속 기록: 2024.03.21 17:42\n - 수정자: ID_HR_Admin\n - 실제 서명된 평가표와 데이터 불일치 발견", true);
	addtxt(6, autoParent, "public", "승무원채용관련", "\n \n [특별 감사 요청서 요약 - 비공식 메모]\n \n 2023년 채용된 신입 승무원 67명 중, 다음 5명이 '고위층 인맥 지원자'로 의심됨:\n \n 1. 김OO - 당시 국토부 국장 딸\n 2. 최OO - 회장 비서실장 조카\n 3. 윤OO - 자회사 대표 지인\n \n [이메일 발췌]\n 인사실장 -> HR매니저:\n '걔네는 점수 상관말고 무조건 올려. 어차피 결과는 우리가 쥐고 있어.'\n \n [비고]\n - HR DB상에는 '추천 없음'으로 표시되어 있으나, 실제 메일 내부 전달 내역 존재\n - 공정채용 인증 관련 외부 감사 직전 삭제됨", true);
	addFol(6, autoParent->getParent(), "public", "정비");
	addtxt(6, autoParent, "public", "안전점검관련문서", "\n \n [항공기 안전점검 기록 위조 - 감찰반 분석 문건]\n \n 기체: HL8237 (B737-800)\n 점검일자: 2023.02.23\n 담당자: 기체정비부 강OO\n \n [문제점]\n - 실물 검사 없이 점검서류만 작성\n - 기체 좌측 플랩 작동 이상 오류 경고 발생 이력 존재\n - 그러나 기록지엔 \"이상 없음\" 으로 체크\n \n - 항공기 해당 일자 실제 운항함 (ICN -> FUK)\n - 민간 항공기록원에 보고되지 않음", true);
	addtxt(6, autoParent, "public", "정비결함기체운항관련문서", "\n \n [정비이력 - 감춰진 운항 내역 요약 (2022~2023)]\n \n 기체: HL9823\n 결함: 엔진오일 누유 (3회 반복 발생)\n \n [운항 강행 사례]\n 1) 2022.11.17 - 김포->제주 (운항 강행)\n  - 출발 30분 전 경고등 점등 -> 리셋 후 출발\n \n 2) 2023.01.09 - 제주->김포\n  - 체크리스트 미작성, 기장 승인 누락\n \n 3) 2023.02.01 - 결함 코드를 타 기체 코드로 변경 후 운항 등록\n \n - 해당 기체는 2023.04.02 고장으로 비상착륙 이력 존재", true);
	addFol(6, autoParent->getParent(), "public", "운항");
	addFol(6, autoParent, "public", "보도대응관련자료");
	addtxt(6, autoParent, "public", "엔딩고장착륙건극비문", "\n \n [하늘항공 본사 - 언론 대응 지침서 (극비)]\n \n 문서번호: PR-C093-V3\n 작성자: 전략기획실 대응총괄팀\n 작성일: 2025.05.07\n 보안등급: INTERNAL – LEVEL 4\n 사건명: HL7882 엔진고장 착륙사건\n \n [상황 요약]\n - 2023.03.18 발생한 HL7882 기체의 비상착륙 건에 대해,\n   현재 FDR 및 CVR 데이터를 분석한 결과 엔진계통 정비 누락에 의한 결함 발생으로 판단됨.\n - 해당 기체는 3월 14일자 내부 정비 요청을 무시하고 운항에 투입되었으며,\n   사고 당시 엔진오일 압력 급락 및 오토스러틀 해제, 엔진 셧다운 발생 기록이 있음.\n - 내부 보고에 따르면, 비상 착륙 후 기수 바퀴 붕괴 및 승객 경상 5명 발생 확인.\n \n [지시사항]\n  공식 입장 및 언론 대응 방향\n 1. 악천후로 인한 예방적 비상착륙 으로 보도자료 일괄 통일\n    - 엔진결함, 정비누락, 내부경고 등은 절대 언급 금지\n    - 기체 상태는 즉각적 대응으로 안정적 착륙으로 기술\n 2. 주요 표현 문구 예시:\n    -  기장의 신속한 판단으로 승객 모두 안전하게 하선\n    -  기상 변화에 따른 예방적 조치\n 3. 사고 장면 CCTV 및 기체 접근 사진은 외부 유출 시 즉시 법무 대응\n \n 내부 입단속\n - 정비부, 운항관리, 탑승승무원 전원에게 보도 전 내부 공유 금지 서약서 제출 요청\n - 사고 당시 FDR 원본 데이터는 서버 백업 포함 완전 삭제 지시\n - 복사본 존재 시, USB/이메일 등 전수조사 진행\n \n 기타 조치\n - 피해 승객에 대한 위로금은 익명 계약 형태로 처리\n - 유가족 혹은 민원 제기 시, 정상 대응 중이라는 입장 고수\n \n [주의]\n 해당 사건은 하늘항공 이미지에 직접적 타격이 우려되므로\n 지침 위반자는 인사상 불이익 및 민형사상 책임을 질 수 있음.", true);
	addtxt(6, autoParent, "public", "기체통신오류미착륙건극비문", "\n \n [하늘항공 전략기획실 - 기체 통신오류 관련 대응 지침 (극비)]\n \n 문서번호: PR-D477-V1\n 작성일: 2025.05.07\n 작성자: 전략대응 총괄팀\n 보안등급: INTERNAL - LEVEL 5\n 사건명: HL9987 기체 항법통신 오류 건 (FDR 통제 이탈)\n \n [상황 요약]\n - 2025.05.07 HL9987 항공편(SVO->ICN) 중,\n   FDR 로그상 외부 IP 접속 및 자동 항법 시스템 변경 정황 존재.\n - 자동조종장치(A/P)가 이탈하고, 항로가 수동 개입 없이 변경됨\n   -> 로그상 `REMOTE_CMD`, `nav.dll` 무단 수정 기록 존재\n   -> 시스템 내 암호화된 문자열: `/root` 라는 외부 서명 감지됨\n - CAPT 및 FO 모두 통제 불능 상태 기록 존재\n   -> CVR 대화 중 조종 안 했는데 방향 바뀌었다 등 포함\n - 현 시스템 보안상 취약 지점 확인되었으며,\n   조종 시스템이 외부 해킹을 통해 탈취된 첫 사례일 가능성 높음\n \n [지시사항]\n 공식 입장 및 언론 대응 방안\n 1. 사건 원인은 비행 중 항법장비 일시적 오류로 일괄 통일\n    - 외부 개입, 시스템 침투, 해킹 등 단어는 금지\n    - 보조 통신 장치 간 간섭 오류 혹은 백업 채널 충돌 등 기술적 설명 활용\n 2. 표현 문구 예시:\n    - 일시적인 항법 데이터 불일치가 발생했으나 즉시 복구\n    - 보조 시스템이 즉각 작동하여 기체 안전 유지됨\n 3. 기술자료 제출 시, `nav.dll` 수정 내용은 원상 복원 후 제출\n    - 로그상 `REMOTE_CMD`는 코드 내 주석 처리 및 삭제 후 재작성\n \n 내부 통제 조치\n - 운항기록 원본은 보안데이터 조정본으로 대체 저장\n - CVR/FDR 분석 파일은 별도 외장 디스크 이동 후 봉인\n - 기술팀 내 암호화 키 접근 권한은 임원 전용으로 한정\n \n 직원 통제\n - 운항본부, 정비본부, 기술보안실 소속 전 인원 대상\n   비정상 항법 로그 언급 금지 서약서 회람\n - 개발팀 이력 중 `REMOTE_CMD` 키워드 검색 결과 즉시 파기\n \n [주의 및 요청]\n - 이 사건은 자사 항공 보안 신뢰도 및 국제운항 라이선스 심사에 영향을 줄 수 있으므로,\n   사고의 존재는 인정하되, 원인은 철저히 내부 기술적 문제로 위장해야 함\n - 항공기 해킹이라는 표현이 외부에 유출될 경우,\n   PR팀·법무팀·기술보안팀 합동 비상체제로 전환됨", true);
	addtxt(6, autoParent->getParent(), "public", "비행시간기록", "\n \n [비행운항기록 조작 정황 보고 - 2023.03.15]\n \n 기장: 이OO\n 기체: HL9023\n 노선: 인천(ICN) – 시드니(SYD) – 인천(ICN)\n \n [규정]\n - 연속 운항 최대 근무시간: 10시간 (국토부 고시 기준)\n \n [실제 기록]\n - 운항 시작: 2023.03.11 20:15\n - 운항 종료: 2023.03.12 09:10\n - 총 운항 시간: 12시간 55분\n \n [제출된 보고서]\n - 운항 시간: 9시간 48분 (비행 전 지연시간 삭제)\n - 휴게시간 1시간 허위 기재\n \n - 이 기록은 국토부 정기 보고에 포함되지 않음.\n - 보고서 조작자는 운항관리팀 송OO 주임 (로그인 기록 확보)", true);
	addtxt(6, autoParent->getParent(), "public", "운항관리및보고서류", "\n \n [감사 요청서 - '운항일지 허위작성 건' 분석]\n \n - 점검 기체: HL8851\n - 대상일: 2023.04.08\n - 기장: 김OO\n \n [문제 내용]\n - 비행 전 점검 항목 중 기체 우측 랜딩기어 이상 진동 있음\n - 해당 정비소 기록엔 정비 요청 있음 -> 이력 추적 결과: 작업 미실시\n - 운항일지에는 '정상 작동 확인됨' 으로 표기", true);
	addtxt(6, autoParent->getParent(), "public", "위험운항강행기록", "\n \n [내부 특별 보고서 - '기상악화 속 운항 강행 사례']\n \n 기체: HL9176\n 일시: 2023.01.29\n 노선: 인천(ICN) -> 오사카(KIX)\n \n [기상정보]\n - 출발 40분 전, 관제탑 기상 경보 발령 (강풍+우박)\n - 타 항공사 3편: 전편 결항\n \n [운항 결정 주체]\n - 운항본부장 직결 지시: 'VIP 예약 있음. 시간 맞춰라.'\n \n [결과]\n - 기체 착륙 시 1차 시도 실패 -> 2차 시도 착륙\n - 승객 4명 경미한 부상, 수하물 파손 2건\n \n - 해당 사고는 기체 착륙 실패 항목에서 제외 보고됨", true);






		
		//[NEWS] KST 통신사에서 고객 정보 유출...\n \n|[NEWS] 통신사 KST 대처가 시급하지 않아\n \n최근 KST 통신사에서 대규모 고객 정보 유출 사건이 발생해 고객들의 불안이 커지고 있다.\n이번 사건은 해킹 공격으로 인해 수십만 명의 개인 정보가 외부로 유출된 것으로 확인됐다.\n유출된 데이터에는 고객의 이름, 전화번호, 주소, 이메일뿐만 아닌 일부 고객의 신용카드 정보와 결제 이력도 포함 되있는\n것으로 알려졌다.\nKST 통신사는 오늘 오전 긴급 기자회견을 열고 사건의 경위를 설명했다.\n회사 측은 유출을 막기위한 대응을 하기 위해 노력하고 있다고 고객을 안심시키고 있음.\n 하지만 이미 잃어버린 민심을 잠재울 수 있을지 계속 지켜봐야 할 것으로 판단되어...

	command.cmd_connect("127.0.0.1");
	
	while (!command.getShutdown()) {
		canvas.draw();
		command.checkCommand(canvas.input());
	}
	
	for (File* f : File::files) { cout << f->getId(); delete f; }
	delete[] com;
	return 0;
}
void setPass(string p) { File::files[File::files.size()-1]->setPass(p); }
void addtxt(int cNum, File* parent, string security, string name, string desc, bool v, bool cR, bool oneshot) {
	File* f = new txt(File::fileId, security, name, desc, v, cR, oneshot);
	if (parent) { com[cNum].add(parent, f); }
	else { com[cNum].add(f); }
	File::files.push_back(f);
	File::fileId++;
}
void addexe(int cNum, File* parent, string security, string name, string code, bool v, bool cR, bool oneshot) {
	File* f = new exe(File::fileId, security, name, code, v, cR, oneshot);
	if (parent) { com[cNum].add(parent, f); }
	else { com[cNum].add(f); }
	File::files.push_back(f);
	File::fileId++;
}
void addFol(int cNum, File* parent, string security, string name, bool v, bool cR, bool oneshot) {
	File* f = new Folder(File::fileId, security, name, v, cR, oneshot);
	if (parent) { com[cNum].add(parent, f); }
	else { com[cNum].add(f); }
	autoParent = f;
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