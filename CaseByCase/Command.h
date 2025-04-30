#pragma once

class Command {
	Canvas* canvas;

	bool shutdown; // ���� ����
public:
	Command(Canvas* c)
	{
		canvas = c;
		shutdown = false;
	}
	void checkCommand(const string& s)
	{
		istringstream iss(s);
		string token;
		vector<string> tokens;

		while (iss >> token) { tokens.push_back(token); }

			 if (tokens[0] == "/shutdown") cmd_shutdown();
		else if (tokens[0] == "/help") cmd_help();
	}
	bool getShutdown() { return shutdown; }

	void cmd_help()
	{
		canvas->input("/shutdown : ���� ����");
		canvas->input("/help : ��ɾ� ����Ʈ ���");
		canvas->input("/exit : �������� ���ư� (����Ʈ ������, ���������� ������ ��)");
		canvas->input("/decoding �����̸�: ��� ���� ��ȣȭ");
		canvas->input("/scan : �ֺ� IP ��ĵ");
		canvas->input("/portscan IP : ��Ʈ ���� Ȯ��");
		canvas->input("/sshcrack : 22�� ��Ʈ ����");
		canvas->input("/ftpcrack : 21�� ��Ʈ ����");
		canvas->input("/smtpcrack : 25�� ��Ʈ ����");
		canvas->input("/httpworm : 80�� ��Ʈ ����");
		canvas->input("/connect IP : �ش� ��ǻ�� ����");
		canvas->input("/disconnect : ���� ����");
		canvas->input("/nuke IP : ���� ��ŷ");
		canvas->input("rmlog : �α� ����");
	}
	void cmd_shutdown()
	{
		shutdown = true;
	}
};