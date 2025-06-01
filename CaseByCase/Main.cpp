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