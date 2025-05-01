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

	com[0].add(new Folder("public", "폴더 1"));
	com[0].add(0, new txt("public", "텍스트파일 1", "hello world!"));

	while (!command.getShutdown()) {
		canvas.draw(&command);
		command.checkCommand(canvas.input());
	}
	
	delete[] com;
	return 0;
}
