#pragma once
#include "StructPack.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class File {
	File* parentFile = nullptr;
	int id;
	string name;
	string securityLevel;
public:
	File(char i, string s, string n) : id(i), securityLevel(s), name(n) {}
	virtual ~File() {}
	virtual void add(File* child) {}
	virtual void remove(int index) {}
	virtual void setParent(File* f) { parentFile = f; }
	virtual File* getParent() { return parentFile; }
	virtual int getIcon() { return id; }
	virtual string getName() { return name; }
	virtual int getFileCount() { return NULL; }
	virtual File* getFile(int num) { return nullptr; }
};

class txt : public File {
	string descName;
	string desc[10];
public:
	txt(char i, string s, string n, string dn, const vector<string>& descs = {}) : File(i, s, n), descName(dn) {
		for (size_t j = 0; j < descs.size() && j < 10; ++j) { desc[j] = descs[j]; }
	}
	txtS save();
	void load() {}
	string getDescName() { return descName; }
	string getDesc(int num) {
		return desc[num];
	}
};

class exe : public File {
	string url;
public:
	exe(char i, string s, string n, string u) : File(i, s, n), url(u) {}
	exeS save();
	exeS load();
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
	FolderS save();
	FolderS load();
	void add(File* child, File* parent) { 
		childFile.push_back(child);
		child->setParent(parent);
	}
	void remove(int index) { childFile.erase(childFile.begin() + index); }
	int getFileCount() { return childFile.size(); }
	File* getFile(int num) { return childFile[num]; }
};