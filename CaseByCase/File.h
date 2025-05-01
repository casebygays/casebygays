#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class File {
	File* parentFile = nullptr;
	char icon;
	string securityLevel;
	string name;
public:
	File(char i, string s, string n) : icon(i), securityLevel(s), name(n) {}
	virtual ~File() {}
	virtual void add(File* child) {}
	virtual void remove(int index) {}
	virtual void setParent(File* f) { parentFile = f; }
	virtual File* getParent() { return parentFile; }
	virtual char getIcon() { return icon; }
	virtual string getName() { return name; }
	virtual int getFileCount() { return NULL; }
	virtual File* getFile(int num) { return nullptr; }
};

class txt : public File {
	string descName;
	string desc[10];
public:
	txt(char i, string s, string n, string dn, string d1, string d2 = "", string d3 = "", string d4 = "", string d5 = "", string d6 = "", string d7 = "", string d8 = "", string d9 = "", string d10 = "") : File(i, s, n), descName(dn) {
		desc[0] = d1;
		desc[1] = d2;
		desc[2] = d3;
		desc[3] = d4;
		desc[4] = d5;
		desc[5] = d6;
		desc[6] = d7;
		desc[7] = d8;
		desc[8] = d9;
		desc[9] = d10;
	}
	string getDesc(int num) {
		return desc[num];
	}
};

class exe : public File {
	string url;
public:
	exe(char i, string s, string n, string u) : File(i, s, n), url(u) {}
	string getURL() {
		return url;
	}
};

class Folder : public File {
	vector<File*> childFile;
public:
	Folder(char i, string s, string n) : File(i, s, n) {}
	~Folder() {
		for (File* f : childFile)
			delete f;
	}
	void add(File* child, File* parent) { 
		childFile.push_back(child);
		child->setParent(parent);
	}
	void remove(int index) { childFile.erase(childFile.begin() + index); }
	int getFileCount() { return childFile.size(); }
	File* getFile(int num) { return childFile[num]; }
};