#include "Canvas.h"
#include "Command.h"
#include "Computer.h"
#include "File.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

int main() {
	Canvas game;
	Command command(&game);

	while (!command.getShutdown()) {
		game.draw();
		command.checkCommand(game.input());
	}
	

	return 0;
}
