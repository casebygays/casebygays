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
	Canvas canvas;
	Computer* com = new Computer[COMMAX];
	Command command(&canvas, com, COMMAX);

	com[0].add(new Folder('¡á', "public", "folder"));
	com[0].add(0, new txt('££', "public", "textfile.txt", "textfile", "hello world!"));

	while (!command.getShutdown()) {
		canvas.draw();
		command.checkCommand(canvas.input());
	}
	
	delete[] com;
	return 0;
}