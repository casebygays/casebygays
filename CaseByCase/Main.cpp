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
void addtxt(int cNum, File* parent, string security, string name, string desc, bool v = true, bool cR = true);
void addexe(int cNum, File* parent, string security, string name, string code, bool v = true, bool cR = true);
void addFol(int cNum, File* parent, string security, string name, bool v = true, bool cR = true);
void remove(int cNum, int id);

Canvas canvas;
Computer* com = new Computer[COMMAX];
Command command(&canvas, com, COMMAX);

vector<File*> File::files;
int File::fileId = 0;

Computer* Canvas::targetCom = nullptr; //Ÿ���� ��ǻ��
Computer* Canvas::connectCom = nullptr; // ������ ��ǻ��
File* Canvas::currentFile = nullptr; // ���� ����
int Canvas::alertLevel = 0;

int main() {
	canvas.input("��üȭ������ �������ּ���.");
	canvas.input("/help �Է½� ��ɾ� ����Ʈ�� ȣ���մϴ�.");

	com[0].setPlayer();
	

	// �÷��̾� ��ǻ�� ����
	addFol(0, nullptr, "public", "Diary", true, false);
	addtxt(0, com[0].getFile(0), "public", "2018.04.03", "��ŷ�� �⺻.\n\n /scan : ������ ��ǻ���� IP�� ��ĵ�Ѵ�.\n /target [IP] : ��ŷ�ϰ���� ��ǻ���� IP�� �����Ѵ�.\n /crack : ������ ��ǻ���� ��Ʈ�� ��ŷ�Ѵ�.\n��Ʈ ���� : ssh, ftp, smtp, http, proxy, firewall\n\n /nuke : ��Ʈ�� ���� ���� ��ŷ����\n /connet : ��ŷ�� �Ϸ��� ��ǻ�Ϳ� ����, IP �������� ������ ��ǻ�Ϳ� ���� �õ�\n /disconnet : ��ǻ�� ���� ����", true, false);
	addFol(0, nullptr, "public", "Memo", true, false);
	addtxt(0, com[0].getFile(1), "public", "�޸�1", "�޸� ����", true, false);
	addtxt(0, nullptr, "private", "/help", "�����...", true, true); setPass("�������� �˷���");
	addexe(0, nullptr, "public", "saveload", "/addtxt a a | /addfolder b", true, true);
	addtxt(0, nullptr, "public", "AAAAA", "������ ������", false, true);
	addexe(0, nullptr, "private", "scan.exe", "/scan", true); setPass("1234");
	addFol(0, nullptr, "public", "USB", true);	// ���߿� �������� ó���ϰ� �ҽ�4���� Ȯ���ϸ� ��Ÿ���� �� ����
	//USB
	addtxt(0, com[0].getFile(6), "public", "Detail_1", "[���� ���� ��� - 2025.04.20 | �ۼ���: �輮�� (���� ������)]\n \n����� �ڵ� ���� �ý��� ���ο��� �� �� ���� ��ȸ ��ƾ �߰�.\n���� ���� ������ ��ȸ�Ͽ� �ܺ� ����� ���� ������ ����.\n�α� �м� ���, �Ʒ� ����� ������������ �����:\nCMD: override_autopilot(true)\nCMD: set_altitude(0)\n \n���� �Ŵ��� �� �ڵ庣�̽����� �������� �ʴ� ���.\n�� ��ƾ�� �ǿ�� ��� ����� ������ �Ұ������� �� ����.\n \n�̹� �ý����� ħ�ش����� ���ɼ����� ����.\n�ش� ��ƾ�� �ǵ������� ���Ե� ������ ����. ���� ��ġ�� �ʿ���.", true);
	addtxt(0, com[0].getFile(6), "public", "���۵������������ʾ�", "[���۵��� ���� ���� �ʾ�]\n \nTo: ���� �����Ѱ���\nSubject: �ý��� ħ�� �ǽɰ�\n�� ��ƾ�� �ܼ��� ���װ� �ƴ϶�, �������� ���� ��ȸ ��η� ���Դϴ�.\nħ�� ������ ������, ������ �ּ� �� ���� �̻� �����Ǿ����ϴ�.\n� �����̾������� �𸣰�����, �̰� �����ϸ� ���� �̾��� �� �ֽ��ϴ�.\n������ ���� ��θ� ����� ������ �־�, ���� �ι��� ����Ǿ��� ���ɼ��� ������ �� �����ϴ�.\n���� �� ����� �˾Ҵٴ� �� ��ü�� ������ ���� �ֽ��ϴ�.\n������ ����� �ξ����ϴ�. ���� ������ �������� ���ϴ���\n�������� �̰� �����մϴ�. ���� ���� ���� ��� ģ��A���� ���� �ٶ��ϴ�. \n���� ���� ��...", true);
	addtxt(0, com[0].getFile(6), "public", "Record.wav","\n\n[���� ���� �ڵ� ���� ��� | �Ϻ� �ջ��]\n \n��: ���� ���� ��ǥ Ȯ���غþ�. ��Ʈ6077���� �ܺ� ��û�� �����ƾ�.\n��: �α׿� '���� ��ȸ' ����� �� ��... ������ �ý��� ������ ���Դٴ� �ž�.\n��: ...����� ���ܾ߰ھ�. �� �̻� �̰� ȥ�� ������ �� ����...\n \n* (��ȭ ���� / ���� �߻�) *",true);
	
	
	//����Ʈ��
	addFol(0, nullptr, "public", "����Ʈ��", true); setPass("�輮��");	// ���������� ���߿� �������� ó���ϰ� USB�� Ȯ���ϸ� ��Ÿ���� �� ���� �е����� �ٸ������� ã���� �ְ� ����

	addFol(0, com[0].getFile(7), "public", "Message", true);
	addFol(0, com[0].getFile(7), "public", "Call_Log", true);

	addtxt(0, com[0].getFile(7)->getFile(0), "public", "[��������]", "[4/21 09:44]\n \n���� ��, �װ� �׳� �׽�Ʈ ��ƾ�̾�. �۳⿡�� ���Դ� ���ݾ�. ������ ������.\n�츮 ���� ������ ����, �ΰ��� �ñ��� �� ���ݾ�.\n������ ���� ��������. �ý��� �ٲٴ� �� ���� ��� ���� �� �� ���ݾ�\n�츮 ������ ��������", true);
	addtxt(0, com[0].getFile(7)->getFile(0), "public", "[�˼����¹�ȣ]", "[4/19 20:32]\n \n�� ��ƾ �ʸ� �� �� �ƴϾ�. �ٸ� ����鵵 �� �þ�. ������ �� �ٹ�����.\n�� ������ �װ� �ĳİ� �ϴ���. ������.\n��� �� ��ϵǰ� �־�. �� ��ġ�� ����������.", true);
	addtxt(0, com[0].getFile(7)->getFile(0), "public", "[����]", "[4/19 20:32]\n \n������ �̹� �ָ��� ���� �� �� �ִ�?", true);

	addtxt(0, com[0].getFile(7)->getFile(1), "public", "[����ö������]", "[5/7 01:55]", true);
	addtxt(0, com[0].getFile(7)->getFile(1), "public", "[�����]", "[5/3 16:08]", true);
	addtxt(0, com[0].getFile(7)->getFile(1), "public", "[�������ٸ�]", "[5/2 04:32]", true);
	addtxt(0, com[0].getFile(7)->getFile(1), "public", "[�̻���]", "[13/12 25:32]", true);
	addtxt(0, com[0].getFile(7)->getFile(1), "public", "[������Ʈ����]", "[2/22 22:22]", true);
	addtxt(0, com[0].getFile(7)->getFile(1), "public", "[Ʈ��������Ʈ�������]", "[2/17 12:32]", true);
	addtxt(0, com[0].getFile(7)->getFile(1), "public", "[�����]", "[1/26 17:08]", true);
	addtxt(0, com[0].getFile(7)->getFile(1), "public", "[�����]", "[1/26 17:08]", true);
	addtxt(0, com[0].getFile(7)->getFile(1), "public", "[�����]", "[1/26 17:08]", true);
	addtxt(0, com[0].getFile(7)->getFile(1), "public", "[�����]", "[1/26 17:08]", true);
	addtxt(0, com[0].getFile(7)->getFile(1), "public", "[�����]", "[1/26 17:08]", true);
	addtxt(0, com[0].getFile(7)->getFile(1), "public", "[�����]", "[1/26 17:08]", true);
	addtxt(0, com[0].getFile(7)->getFile(1), "public", "[�����]", "[1/26 17:08]", true);
	addtxt(0, com[0].getFile(7)->getFile(1), "public", "[�����]", "[1/26 17:08]", true);

	// �׿� ��ǻ�� ����
	addFol(1, nullptr, "public", "1��_��ǻ��", true);
	addtxt(1, com[1].getFile(0), "public", "news_1", "���� ��ħ ������ ���Ҵ�. ���������� ������ ��� �����ְ��־���. ���� ���� �ܱ����� ���ٴ� ��⸦ �����.", true);
	addtxt(1, com[1].getFile(0), "private", "news_2", "���� �������Լ� ��ȭ�� �Դ�. ���� �׾��ٰ� �Ѵ�. ���� ������ ���Ҵ� �����⿡ ���� Ÿ�� �־��ٰ� �Ѵ�. �������� ������ �����. ���� ���� ����̾���.", true); setPass("1125");
	addtxt(1, com[1].getFile(0), "private", "news_3", "", true); setPass("��й�ȣ ���ؾ���");
	addtxt(1, com[1].getFile(0), "private", "news_4", "���� ��ǰ���� ������ USB�� �߰� �Ǿ���.�׳� ���ķ� ���� �ƹ��͵� �� �� ����. Ƽ�� ���Ƶ� �� ��Ǹ� ������ �ִ�. ������ ������ ����\n\"���� ����� �ذ��غ���?\"", true); setPass("1125");

	
	addFol(1, nullptr, "public", "News_Collection", true);
	addtxt(1, com[1].getFile(0), "public", "�ҽ�1", "2025�� 5�� 7�� ���� ���� ���� �׾���..\n����� ������ �������Ż�� ����Ѵ�\n���� ������ �ʹ� ��Ÿ����.", true);
	addtxt(1, com[1].getFile(0), "private", "�ҽ�2", "���� ����� ������� ���� A�� ��� �Ѵ�. ������ ��� ��� �Ͼ���ϱ�?", true); setPass("1125");
	addtxt(1, com[1].getFile(0), "private", "�ҽ�3", "���� ���� ������ �̻��� ���� ���� �� �������� �־���\n ���� ��ǰ���� ��ȣȭ�� USB�� �߰ߵǾ���. �̰��� ��ŷ�غ���", true); setPass("��й�ȣ ���ؾ���");
	addtxt(1, com[1].getFile(0), "private", "�ҽ�4", "", true); setPass("1125");

	addFol(2, nullptr, "public", "����_��ǻ��", true);
	
	addtxt(2, com[1].getFile(1), "public", "�R���o��2", "1", true);
	addtxt(2, com[1].getFile(1), "public", "�R���o��3", "1", true);     // 2�� ��ǻ�Ϳ� �R���o�� �̶�� ������ ���� \ �״����� ���Ͼȿ��� ��й�ȣ
	addtxt(2, com[1].getFile(1), "public", "�R���o��4", "2", true);
	addtxt(2, com[1].getFile(1), "public", "�R���o��5", "5", true);

	
	addFol(3, nullptr, "public", "����_usb", true); setPass("���� ����");
	addtxt(3, com[3].getFile(0), "private", "����_usb1", "USB ��ȣȭ �õ� -> Project Aegis Red Line ��� �������� 3�ܰ� �鵵�� ���� �� �ұ��� �� �����ִ�.", true); setPass("���� ����");
	addtxt(3, com[3].getFile(0), "private", "����_usb2", "���� A���� ��� ���� �ý��� �����ڿ�����, ���� ��� �ý��ۿ� �ǵ��� ���� ������� �����Ѵٰ� ���� ���������� �����Ѵٰ� �����ִ�.", false); setPass("���� ����");
	
	



	//addtxt(0, com[0].getFile(5)->getFile(1), "public", "[����]", "[4/19 20:32]\n \n������ �̹� �ָ��� ���� �� �� �ִ�?", true); // ���⼭���� �����ؾ���

	//command.cmd_connect("127.0.0.1");

	
	//remove(0, 1);

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
void addtxt(int cNum, File* parent, string security, string name, string desc, bool v, bool cR) {
	File* f = new txt(File::fileId, security, name, desc, v, cR);
	if (parent) { com[cNum].add(parent, f); }
	else { com[cNum].add(f); }
	File::files.push_back(f);
	File::fileId++;
}
void addexe(int cNum, File* parent, string security, string name, string code, bool v, bool cR) {
	File* f = new exe(File::fileId, security, name, code, v, cR);
	if (parent) { com[cNum].add(parent, f); }
	else { com[cNum].add(f); }
	File::files.push_back(f);
	File::fileId++;
}
void addFol(int cNum, File* parent, string security, string name, bool v, bool cR) {
	File* f = new Folder(File::fileId, security, name, v, cR);
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