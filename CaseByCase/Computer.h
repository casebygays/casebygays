#pragma once

using namespace std;
class Port {
	bool enabled;
	int level;
public:
	Port(bool on = false, int lvl = 0) : enabled(on), level(lvl) {}
};
class Computer {
	string ip = "000.000.0.0";
	Port ssh, ftp, smt, http;

};