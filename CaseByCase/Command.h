#pragma once
#include "Canvas.h"
#include "Computer.h"
#include "StructPack.h"
#include "Firewall.h"
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;
// 디버그용 bugconnect 나중에 지우면 이 문구도 지워
class Command {
	Canvas* canvas;
	Computer* computer;
	int comMax;
	bool shutdown; // 게임 종료
	Firewall firewallGame;
public:
	Command(Canvas* c, Computer* com, int cM)
	{
		canvas = c;
		computer = com;
		comMax = cM;
		shutdown = false;
	}
	void save() {}
	void load() {}
	void checkCommand(const string& s)
	{
		istringstream iss(s);
		string token;
		vector<string> tokens;
		while (iss >> token) { tokens.push_back(token); }

		if (tokens.empty()) { return; }
		else if (canvas->in_proxy) { // 프록시 미니게임
			canvas->proxyChance -= 1;
			if (tokens[0] == to_string(canvas->proxyAnswer)) {
				canvas->in_proxy = false;
				Canvas::targetCom->portCrack("proxy", false);
				canvas->input("프록시 해킹 성공");
			}
			else if (canvas->proxyChance > 0) {
				string s = "프록시 해킹 실패 / 남은 기회 : " + to_string(canvas->proxyChance);
				canvas->input(s);
				addAlertLevel(1);
			}
			else if (canvas->proxyChance == 0) {
				canvas->in_proxy = false;
				string s = "프록시 해킹 실패 / 정답 : ";
				s = s + to_string(canvas->proxyAnswer);
				canvas->input(s);
				addAlertLevel(6);
			}
		}
		else if (canvas->in_firewall) {//파이어월 야구게이
			if (tokens.size() != firewallGame.computerBall.size()) return;
			for (int i = 0; i < tokens.size(); i++) {
				cout << firewallGame.strike;
				if (stoi(tokens[i]) == firewallGame.computerBall[i]) {
					firewallGame.strike += 1;

				}
				else if (firewallGame.contains(firewallGame.computerBall, stoi(tokens[i]))) {
					firewallGame.ball += 1;
				}
				else
					firewallGame.out += 1;
			}
			if (firewallGame.strike == tokens.size()) {
				Canvas::targetCom->portCrack("firewall", false);
				canvas->input("파이어월 해킹 야호");
				canvas->in_firewall = false;
			}
			else if (firewallGame.count != 9) {
				firewallGame.count += 1;
				addAlertLevel(1);
				canvas->input(to_string(firewallGame.strike) + "S " + to_string(firewallGame.ball) + "B " + to_string(firewallGame.out) + "O  / 남은 횟수 : " + to_string(10- firewallGame.count));
			}
			else {
				canvas->input("실패 ㅠㅠ");
				addAlertLevel(6);
				canvas->in_firewall = false;
			}
		}
		else if (canvas->in_login){
			if (tokens.size() >= 2) {
				if (tokens[0] == "atcproxy" and tokens[1] == "00100000") { // 로그인 성공
					canvas->in_login = false;
					canvas->input("로그인 성공");
				}
				else if (tokens[0] == "iqlogin_0921" and tokens[1] == "coffeeflight35") { // 로그인 성공
					canvas->in_login = false;
					canvas->input("로그인 성공");
				}
				else {
					canvas->input("로그인 실패");
					canvas->in_login = false;
				}
			}
			else {
				canvas->input("알맞은 값을 입력해주세요");
				canvas->in_login = false;
			}
		}
		else if (tokens[0] == "/show" && tokens.size() > 1) {
			bool found = false;
			for (int i = 0; i < Canvas::connectCom->getFileCount(); i++) {
				File* f = Canvas::connectCom->getFile(i);
				if (!f->getVisible() && f->getName() == tokens[1]) {
					f->setVisible(true);
					canvas->input("숨겨진 파일을 표시했습니다: " + f->getName());
					found = true;
					break;
				}
			}
			if (!found) {
				canvas->input("해당 이름의 숨겨진 파일을 찾을 수 없습니다.");
			}
		}

		else if (tokens[0] == "/shutdown") cmd_shutdown();
		else if (tokens[0] == "/save") cmd_savegame();
		else if (tokens[0] == "/load") cmd_loadgame();
		else if (tokens[0] == "/help") cmd_help();
		else if (tokens[0] == "/clear") cmd_clear();
		else if (tokens[0] == "/addtxt" and tokens.size() > 2) cmd_addtxt(tokens[1], tokens[2]);
		else if (tokens[0] == "/addexe" and tokens.size() > 3) cmd_addexe(tokens[1], tokens[2]);
		else if (tokens[0] == "/addfolder") cmd_addfolder(tokens[1]);
		else if (tokens[0] == "/remove") cmd_remove(tokens[1]);

		else if (tokens[0] == "/scan") cmd_scan();
		else if (tokens[0] == "/portscan") cmd_portscan();
		else if (tokens[0] == "/target" and tokens.size() > 1) cmd_target(tokens[1]);
		else if (tokens[0] == "/crack" and tokens.size() > 1) cmd_crack(tokens[1]);
		else if (tokens[0] == "/nuke" and tokens.size() > 1) cmd_nuke(tokens[1]); // IP 적었을때
		else if (tokens[0] == "/nuke") cmd_nuke(); // IP 안적었을때

		else if (tokens[0] == "/debugconnect" and tokens.size() > 1) cmd_debugconnect(tokens[1]);
		else if (tokens[0] == "/connect" and tokens.size() > 1) cmd_connect(tokens[1]); // IP 적었을때
		else if (tokens[0] == "/connect") cmd_connect(); // IP 안적었을때
		else if (tokens[0] == "/disconnect") cmd_disconnect();
		else if (tokens[0] == "/in" and tokens.size() > 2) cmd_in(tokens[1], tokens[2]);
		else if (tokens[0] == "/in" and tokens.size() > 1) cmd_in(tokens[1]);
		else if (tokens[0] == "/out") cmd_out();
	}
	File* getCurrentFile() { return Canvas::currentFile; }
	bool getShutdown() { return shutdown; }
	void addAlertLevel(int value) {
		if (Canvas::connectCom->getIP() != "127.0.0.1" or Canvas::targetCom != nullptr)
			Canvas::alertLevel += value;
		if (Canvas::alertLevel >= 100) {
			// 발각도가 100이 되면 접속중인 컴퓨터에서 튕김, +보안이 강화되는거 넣어도 좋을듯
		}
	}
	void cmd_shutdown() { shutdown = true; }
	void cmd_savegame() {
		ofstream file("Save.txt");
		if (file.is_open()) {
			for (int i = 0; i < File::files.size(); i++) {
				file << "id=" << File::files[i]->getId() << '\n';
				if (File::files[i]->getParent() == nullptr) 
					file << "parentID=" << -1 << '\n';
				else 
					file << "parentID=" << File::files[i]->getParent()->getId() << '\n';
				file << "icon=" << File::files[i]->getIcon() << '\n';
				file << "name=" << File::files[i]->getName() << '\n';
				file << "securityType=" << File::files[i]->getSecurity() << '\n';
				file << "pass=" << File::files[i]->getPass() << '\n';
				file << "visible=" << File::files[i]->getVisible() << '\n';
				file << "canRemove=" << File::files[i]->getCanRemove() << '\n';
				file << "oneshot=" << File::files[i]->getOneshot() << '\n';
				if (dynamic_cast<txt*>(File::files[i])) {
					file << "desc=" << dynamic_cast<txt*>(File::files[i])->getDesc() << '\n';
					file << "fileType=" << "txt" << '\n';
				}
				else if (dynamic_cast<exe*>(File::files[i])) {
					file << "code=" << dynamic_cast<exe*>(File::files[i])->getCode() << '\n';
					file << "fileType=" << "exe" << '\n';
				}
				else if (dynamic_cast<Folder*>(File::files[i])) {
					file << "fileType=" << "Folder" << '\n';
				}
			}
			for (int i = 0; i < 80; i++) {
				file << "IP=" << computer[i].getIP() << '\n';
				file << "level=" << computer[i].getLevel() << '\n';
				file << "ssh=" << computer[i].getPort("ssh") << '\n';
				file << "ftp=" << computer[i].getPort("ftp") << '\n';
				file << "smtp=" << computer[i].getPort("smtp") << '\n';
				file << "http=" << computer[i].getPort("http") << '\n';
				file << "proxy=" << computer[i].getPort("proxy") << '\n';
				file << "firewall=" << computer[i].getPort("firwall") << '\n';
				file << "isNuke=" << computer[i].getIsNuke() << '\n';
				file << "childFiles=[";
				for (int j = 0; j < computer[i].getFileCount(); j++) {
					file << computer[i].getFile(j)->getId();
					if (j < computer[i].getFileCount() - 1)
						file << ",";
				}
				file << "]\n";
			}
			for (int i = 0; i < canvas->getCMDSize(); i++) {
				file << "cmd=" << canvas->getCMDText(i) << '\n';
			}
			file << "lastText=" << canvas->getLastText() << '\n';
			file << "connectComIP=" << Canvas::connectCom->getIP() << '\n';
			if (Canvas::currentFile != nullptr) file << "currentFileID=" << Canvas::currentFile->getId() << '\n';
			file.close();
		}
		
		canvas->input(to_string(computer[0].getFileCount()));
	}
	void cmd_loadgame() {
		ifstream file("Save.txt");
		string line;

		S_Computer comData;
		S_File fileData;
		int comIndex = 0; // com의 index
		for (File* f : File::files) { delete f; } // 모든 파일 삭제
		File::files.clear();

		while (getline(file, line)) {
			size_t sep = line.find('=');
			if (sep == string::npos) continue;

			string key = line.substr(0, sep);
			string value = line.substr(sep + 1);
			// 파일
			if (key == "id") { fileData.id = stoi(value); }
			else if (key == "parentID") { fileData.parentID = stoi(value); }
			else if (key == "icon") { fileData.icon = value; }
			else if (key == "name") { fileData.name = value; }
			else if (key == "securityType") { fileData.securityType = value; }
			else if (key == "pass") { fileData.pass = value; }
			else if (key == "visible") { fileData.visible = stoi(value); }
			else if (key == "canRemove") { fileData.canRemove = stoi(value); }
			else if (key == "oneshot") { fileData.canRemove = stoi(value); }
			else if (key == "desc") { fileData.desc = value; }
			else if (key == "code") { fileData.code = value; }
			else if (key == "fileType") { 
				if (value == "txt") File::files.push_back(new txt(fileData));
				else if (value == "exe") File::files.push_back(new exe(fileData));
				else if (value == "Folder") File::files.push_back(new Folder(fileData)); 
			}

			else if (key == "IP") {
				comData.IP = value;
			}
			else if (key == "level") { comData.level = stoi(value); }
			else if (key == "ssh") { comData.ssh = stoi(value); }
			else if (key == "ftp") { comData.ftp = stoi(value); }
			else if (key == "smtp") { comData.smtp = stoi(value); }
			else if (key == "http") { comData.http = stoi(value); }
			else if (key == "is_nuke") { comData.is_nuke = stoi(value); }
			else if (key == "childFiles") {
				computer[comIndex].childFileClear();

				size_t start = value.find('[');
				size_t end = value.find(']');

				if (start != string::npos && end != string::npos && end > start) {
					string numbers = value.substr(start + 1, end - start - 1);
					stringstream ss(numbers);
					string token;
					while (getline(ss, token, ',')) {
						for (File* f : File::files) {
							if (f->getId() == stoi(token)) computer[comIndex].add(f);
						}
					}
				}
				comIndex++;
			}
			if (key == "connectComIP") { 
				for (int i = 0; i < comMax; i++)
					if (computer[i].getIP() == value)
						Canvas::connectCom = &computer[i];
			}
			else if (key == "currentFileID") {
				for (int i = 0; i < File::files.size(); i++) {
					if (File::files[i]->getId() == stoi(value))
						Canvas::currentFile = File::files[i];
					canvas->input(to_string(Canvas::currentFile->getId()));
				}
			}
		}
		canvas->input(Canvas::connectCom->getIP());
		if (Canvas::currentFile != nullptr) canvas->input(Canvas::currentFile->getName());
		file.close();
		//canvas->input(to_string(computer[0].getFileCount()));
	}
	void cmd_help()
	{
		canvas->input("--------------------------------------------------------");
		canvas->input("비고 : () = 선택,	[] = 필수");
		canvas->input("/shutdown				게임 종료");
		canvas->input("/in [파일] (비밀번호)		파일 열기");
		canvas->input("/out				상위폴더로 나가기");
		canvas->input("/clear				드르륵 탁 clear");
		canvas->input("/scan				주변 IP 스캔");
		canvas->input("/target [IP]			주변 IP 스캔");
		//canvas->input("/decoding [파일]			대상 파일 복호화");
		canvas->input("/portscan				포트 정보 확인");
		canvas->input("/crack ssh				22번 포트 열기");
		canvas->input("/crack ftp				21번 포트 열기");
		canvas->input("/crack smtp			25번 포트 열기");
		canvas->input("/crack http			80번 포트 열기");
		canvas->input("/crack proxy			proxy 비활성화");
		canvas->input("/crack firewall			friewall 비활성화");
		canvas->input("/nuke (IP)				PC 해킹");
		canvas->input("/connect	(IP)			해당 컴퓨터 접속");
		canvas->input("/disconnect			접속 종료");
		canvas->input("--------------------------------------------------------");
		//canvas->input("/removelog				로그 삭제");
	}
	void cmd_clear() { canvas->cmdClear(); }
	void cmd_addtxt(string name, string desc) {
		if (Canvas::currentFile == nullptr or dynamic_cast<Folder*>(Canvas::currentFile)) {
			File* f = new txt(File::fileId, "public", name, desc, true, true, false);
			if (Canvas::currentFile != nullptr) { Canvas::connectCom->add(Canvas::currentFile, f); }
			else if (Canvas::connectCom != nullptr) { Canvas::connectCom->add(f); }
			File::files.push_back(f);
			File::fileId++;
			canvas->input("txt를 생성함");
		}
		else {
			canvas->input("파일을 생성할 수 없는 경로임");
		}
	}
	void cmd_addexe(string name, string code) {
		if (Canvas::currentFile == nullptr or dynamic_cast<Folder*>(Canvas::currentFile)) {
			File* f = new exe(File::fileId, "public", name, code, true, true, false);
			if (Canvas::currentFile != nullptr) { Canvas::connectCom->add(Canvas::currentFile, f); }
			else if (Canvas::connectCom != nullptr) { Canvas::connectCom->add(f); }
			File::files.push_back(f);
			File::fileId++;
			canvas->input("exe를 생성함");
		}
		else {
			canvas->input("파일을 생성할 수 없는 경로임");
		}
	}
	void cmd_addfolder(string name) {
		if (Canvas::currentFile == nullptr or dynamic_cast<Folder*>(Canvas::currentFile)) {
			File* f = new Folder(File::fileId, "public", name, true, true, false);
			if (Canvas::currentFile != nullptr) { Canvas::connectCom->add(Canvas::currentFile, f); }
			else if (Canvas::connectCom != nullptr) { Canvas::connectCom->add(f); }
			File::files.push_back(f);
			File::fileId++;
			canvas->input("폴더를 생성함");
		}
		else {
			canvas->input("파일을 생성할 수 없는 경로임");
		}
	}
	void cmd_remove(string name) {
		if (Canvas::currentFile != nullptr) { 
			for (int i = 0; i < Canvas::currentFile->getFileCount(); i++) { // 현재폴더 내에 모든 파일 검사
				if (Canvas::currentFile->getFile(i)->getName() == name) { // 현재폴더의 파일중 입력받은 이름과 같은 파일이 있으면,
					if (Canvas::currentFile->getFile(i)->getCanRemove()) {
						int id = Canvas::currentFile->getFile(i)->getId();
						Canvas::connectCom->remove(id); // 접속중인 컴퓨터의 remove함수를 호출
						for (int j = 0; j < File::files.size(); j++) {						// files의 모든 파일을 검사
							if (File::files[j]->getId() == id) { // 파일의 id와 같으면
								delete File::files[j];											// 제거
								File::files.erase(File::files.begin() + j);						// files안에서도 제거
							}
						}
						canvas->input("지정한 파일 삭제됨");
					}
					else {
						canvas->input("삭제 불가능한 파일입니다.");
					}
				}
			}
		}
		else if (Canvas::connectCom != nullptr) {
			for (int i = 0; i < Canvas::connectCom->getFileCount(); i++) {
				if (Canvas::connectCom->getFile(i)->getName() == name) {
					if (Canvas::connectCom->getFile(i)->getCanRemove()) {
						int id = Canvas::connectCom->getFile(i)->getId();
						Canvas::connectCom->remove(id);
						for (int j = 0; j < File::files.size(); j++) {
							if (File::files[j]->getId() == id) {
								delete File::files[j];
								File::files.erase(File::files.begin() + j);
							}
						}
					}
					else {
						canvas->input("삭제 불가능한 파일입니다.");
					}
				}
			}
		}
	}
	// 해킹
	void cmd_scan()
	{
		canvas->input(computer[1].getIP()); // 임시
		for (int i = 0; i < 3; i++) {
			int com = 1 + rand() % (comMax - 1);
			canvas->input(computer[com].getIP());
		}
	}
	void cmd_portscan() {
		if (Canvas::targetCom) {
			string s = "포트 정보|";
			if (Canvas::targetCom->getPort("ssh")) s += "ssh : 잠김|";
			else s += "ssh : 열림|";
			if (Canvas::targetCom->getPort("ftp")) s += "ftp : 잠김|";
			else s += "ftp : 열림|";
			if (Canvas::targetCom->getPort("smtp")) s += "smtp : 잠김|";
			else s += "smtp : 열림|";
			if (Canvas::targetCom->getPort("http")) s += "http : 잠김|";
			else s += "http : 열림|";
			if (Canvas::targetCom->getPort("proxy")) s += "proxy : 잠김|";
			else s += "proxy : 열림|";
			if (Canvas::targetCom->getPort("firewall")) s += "firewall : 잠김|";
			else s += "firewall : 열림|";
			canvas->input(s);
		}
		else {
			canvas->input("대상 IP가 지정되지 않음");
		}
	}
	void cmd_target(string ip) {
		if (ip == "atc-nexus.aircorp:8022") {
			canvas->in_login = true;
			for (int i = 0; i < comMax; i++) {
				if (computer[i].getIP() == ip) {
					canvas->input(ip + " : 목표로 지정함");
					Canvas::targetCom = &computer[i];
					break;
				}
			}
			addAlertLevel(1);
		}
		else if (ip == "seia.corp:4200") {
			canvas->in_login = true;
			for (int i = 0; i < comMax; i++) {
				if (computer[i].getIP() == ip) {
					canvas->input(ip + " : 목표로 지정함");
					Canvas::targetCom = &computer[i];
					break;
				}
			}
			addAlertLevel(1);
		}

		for (int i = 0; i < comMax; i++) {
			if (computer[i].getIP() == ip) {
				canvas->input(ip + " : 목표로 지정함");
				Canvas::targetCom = &computer[i];
				break;
			}
		}
		addAlertLevel(1);
	}
	void cmd_crack(string target) { 
		if (target == "proxy" and Canvas::targetCom->getPort("proxy")) {
			canvas->in_proxy = true;
			canvas->proxyAnswer = rand() % 5 + 1;
			canvas->proxyChance = 2;
			addAlertLevel(3);
		}
		else if (target == "firewall" and Canvas::targetCom->getPort("firewall")) {
			canvas->in_firewall = true;
			firewallGame.setGame(Canvas::targetCom->getLevel());
			addAlertLevel(1);
		}
		else if (Canvas::targetCom->portCrack(target, false)) {
			canvas->input(target + " : 성공적으로 포트를 엶");
			addAlertLevel(4);
		}
		else if (Canvas::targetCom == nullptr) {
			canvas->input("해킹 대상이 없습니다.");
		}
		else {
			canvas->input(target + " : 포트가 열려있거나, 대상을 찾지 못함");
			addAlertLevel(2);
		}
	}
	void cmd_nuke(string ip = "") {
		if (ip == "" and Canvas::targetCom != nullptr) {

			if (Canvas::targetCom->getCanNuke()) {
				Canvas::targetCom->nuke();
				canvas->input(Canvas::targetCom->getIP() + " : 해킹 성공");
			}
			else {
				canvas->input(Canvas::targetCom->getIP() + " : 해킹 실패");
			}
		}
		else {
			for (int i = 0; i < comMax; i++) {
				if (computer[i].getIP() == ip) {
					if (computer[i].getCanNuke()) {
						canvas->input(ip + " : 해킹 성공");
						computer[i].nuke();
					}
					else canvas->input(ip + " : 해킹 실패");
					break;
				}
			}
		}
	}

	// 접속
	void cmd_debugconnect(string id = "") { // 디버그용
		int a = stoi(id);
		Canvas::connectCom = &computer[a];
		Canvas::currentFile = nullptr;
		canvas->input(Canvas::connectCom->getIP() + " : 접속 성공");
	}
	void cmd_connect(string ip = "")
	{
		for (int i = 0; i < comMax; i++) {
			if ((ip == "" or ip == "target") and computer[i].getIP() == Canvas::targetCom->getIP()) { // IP를 안적었을때, target을 바로 적었을때
				if (!computer[i].getIsNuke()) canvas->input(Canvas::targetCom->getIP() + " : 접속 실패");
				else {
					canvas->input(Canvas::targetCom->getIP() + " : 접속 성공");
					Canvas::connectCom = &computer[i];
					Canvas::currentFile = nullptr;
					break;
				}
			}
			else if (computer[i].getIP() == ip) {
				if (!computer[i].getIsNuke()) canvas->input(ip + " : 접속 실패");
				else {
					canvas->input(ip + " : 접속 성공");
					Canvas::connectCom = &computer[i];
					Canvas::currentFile = nullptr;
					break;
				}
			}
		}
	}
	void cmd_disconnect()
	{
		Canvas::connectCom = &computer[0];
		Canvas::currentFile = nullptr;
	}
	void cmd_in(string name) {
		if (Canvas::currentFile == nullptr) { // 컴퓨터에서 in
			for (int i = 0; i < Canvas::connectCom->getFileCount(); i++) {  //파일 찾기
				File* f = Canvas::connectCom->getFile(i);
				if (f->getName() == name and f->getSecurity() == "public") {
					if (dynamic_cast<Folder*>(f)) {
						Canvas::currentFile = f;
						Canvas::getFileType(f, "Folder");
					}
					else if (dynamic_cast<txt*>(f)) {
						Canvas::currentFile = f;
						Canvas::getFileType(f, "txt");
					}
					else if (dynamic_cast<exe*>(f)) {
						exe* e = dynamic_cast<exe*>(f);
						vector<string> code = e->runCode();
						for (int i = 0; i < code.size(); i++)
							checkCommand(code[i]);
						if (e->getOneshot()) { checkCommand("/remove " + e->getName()); }
					}
					addAlertLevel(2);
				}
				else if (f->getName() == name and f->getSecurity() == "private") {
					canvas->input("파일이 잠겨있음");
					addAlertLevel(4);
				}
			}
		}
		else { // 폴더에서 in
			for (int i = 0; i < Canvas::currentFile->getFileCount(); i++) {
				File* f = Canvas::currentFile->getFile(i);
				if (f->getName() == name and f->getSecurity() == "public") {
					if (dynamic_cast<Folder*>(f)) {
						Canvas::currentFile = f;
						Canvas::getFileType(f, "Folder");
					}
					else if (dynamic_cast<txt*>(f)) {
						Canvas::currentFile = f;
						Canvas::getFileType(f, "txt");
					}
					else if (dynamic_cast<exe*>(f)) {
						exe* e = dynamic_cast<exe*>(f);
						vector<string> code = e->runCode();
						for (int i = 0; i < code.size(); i++)
							checkCommand(code[i]);
						if (e->getOneshot()) { checkCommand("/remove " + e->getName()); }
					}
					addAlertLevel(2);
				}
				else if (f->getName() == name and f->getSecurity() == "private") {
					canvas->input("파일이 잠겨있음");
					addAlertLevel(4);
				}
			}
		} 
		
	}
	void cmd_in(string name, string pass) {
		bool success = false;
		if (Canvas::currentFile == nullptr) {
			for (int i = 0; i < Canvas::connectCom->getFileCount(); i++) {
				File* f = Canvas::connectCom->getFile(i);
				if (f->getName() == name && f->getSecurity() == "private" && f->getPass() == pass) {
					f->setSecurity("public");
					canvas->input("잠금해제 완료");
					if (dynamic_cast<Folder*>(f)) {
						Canvas::currentFile = f;
						Canvas::getFileType(f, "Folder");
					}
					else if (dynamic_cast<txt*>(f)) {
						Canvas::currentFile = f;
						Canvas::getFileType(f, "txt");
					}
					else if (dynamic_cast<exe*>(f)) {
						exe* e = dynamic_cast<exe*>(f);
						vector<string> code = e->runCode();
						for (int i = 0; i < code.size(); i++)
							checkCommand(code[i]);
						if (e->getOneshot()) { checkCommand("/remove " + e->getName()); }
					}
					addAlertLevel(2);
					success = true;
					break;
				}
			}
			if (!success) {
				canvas->input("비밀번호 틀림");
				addAlertLevel(6);
			}
		}
		else {
			bool success = false;
			for (int i = 0; i < Canvas::currentFile->getFileCount(); i++) {
				File* f = Canvas::currentFile->getFile(i);
				if (f->getName() == name && f->getSecurity() == "private" && f->getPass() == pass) {
					f->setSecurity("public");
					canvas->input("잠금해제 완료");
					if (dynamic_cast<Folder*>(f)) {
						Canvas::currentFile = f;
						Canvas::getFileType(f, "Folder");
					}
					else if (dynamic_cast<txt*>(f)) {
						Canvas::currentFile = f;
						Canvas::getFileType(f, "txt");
					}
					else if (dynamic_cast<exe*>(f)) {
						exe* e = dynamic_cast<exe*>(f);
						vector<string> code = e->runCode();
						for (int i = 0; i < code.size(); i++)
							checkCommand(code[i]);
						if (e->getOneshot()) { checkCommand("/remove " + e->getName()); }
					}
					addAlertLevel(2);
					success = true;
					break;
				}
			}
			if (!success) {
				canvas->input("비밀번호 틀림");
				addAlertLevel(6);
			}
		}
	}

	void cmd_out() {
		File* cf = Canvas::currentFile;
		if (Canvas::currentFile != nullptr and Canvas::currentFile->getParent() != nullptr) {
			//string fileName = "@#$&*()#";
			//if (Canvas::currentFile->getOneshot()) fileName = Canvas::currentFile->getName();
			Canvas::currentFile = Canvas::currentFile->getParent();
			if (dynamic_cast<Folder*>(Canvas::currentFile)) Canvas::getFileType(Canvas::currentFile, "Folder");
			else if (dynamic_cast<txt*>(Canvas::currentFile)) Canvas::getFileType(Canvas::currentFile, "txt");
			else if (dynamic_cast<exe*>(Canvas::currentFile)) Canvas::getFileType(Canvas::currentFile, "exe");
			//checkCommand("/remove " + fileName);
			addAlertLevel(1);
		}
		else {
			//string fileName = "@#&$(*@#&()";
			//if (Canvas::currentFile->getOneshot()) fileName = Canvas::currentFile->getName();
			Canvas::currentFile = nullptr;
			//checkCommand("/remove " + fileName);
			addAlertLevel(1);
		}
	}
};
