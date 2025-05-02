#pragma once
#include "Canvas.h"
#include "Computer.h"
#include "File.h"
#include "Command.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

#define COMMAX 80


int main() {
	// cmd창 전체화면 권장 메시지

	Canvas canvas;
	Computer* com = new Computer[COMMAX];
	Command command(&canvas, com, COMMAX);
	com[0].setPlayer();
	com[0].add(new Folder(0, "public", "도움말"));
	com[0].add(new txt(1, "public", "/help.txt", "/help", { "/help" }));
	com[1].add(new Folder(3, "public", "folder"));
	com[1].add(0, new txt(4, "public", "textfile.txt", "textfile", { "hello world!" }));

	command.cmd_connect("127.0.0.1");
	while (!command.getShutdown()) {
		canvas.draw();
		command.checkCommand(canvas.input());
	}
	
	delete[] com;
	return 0;
}