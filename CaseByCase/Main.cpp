#include "Canvas.h"
#include "Command.h"
#include "Computer.h"
#include "File.h"
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

	com[0].add(new Folder("public", "���� 1"));
	com[0].add(0, new txt("public", "�ؽ�Ʈ���� 1", "hello world!"));

	while (!command.getShutdown()) {
		canvas.draw(&command);
		command.checkCommand(canvas.input());
	}
	
	delete[] com;
	return 0;
}
