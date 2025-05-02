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
	File(int i, string s, string n) : id(i), securityLevel(s), name(n) {}
	virtual void add(File* child) {}
	virtual void erase(int id) {}
	virtual void setParent(File* f) { parentFile = f; }
	virtual File* getParent() { return parentFile; }
	virtual int getId() { return id; }
	virtual string getName() { return name; }
	virtual int getFileCount() { return NULL; }
	virtual File* getFile(int num) { return nullptr; }
};

class txt : public File {
	string descName;
	string desc;
public:
	txt(int i, string s, string n, string dn, string d) : File(i, s, n), descName(dn), desc(d) {}
	txtS save();
	void load() {}
	string getDescName() { return descName; }
	string getDesc() {
		return desc;
	}
};

class exe : public File {
	string url;
public:
	exe(int i, string s, string n, string u) : File(i, s, n), url(u) {}
	exeS save();
	void load();
	string getURL() {
		return url;
	}
};

class Folder : public File {
	vector<File*> childFile;
public:
	Folder(char i, string s, string n) : File(i, s, n) {}
	~Folder() {
		for (File* f : childFile) {
			f->setParent(nullptr);
		}
	}
	FolderS save();
	FolderS load();
	void add(File* parent, File* child) {
		childFile.push_back(child);
		child->setParent(parent);
	}
	void erase(int id) {
		for (int i = 0; i < childFile.size(); i++) {
			if (childFile[i]->getId() == id) {
				childFile[i]->setParent(nullptr);
				childFile.erase(childFile.begin() + i);
			}
		}
	}
	int getFileCount() { return childFile.size(); }
	File* getFile(int num) { return childFile[num]; }
};