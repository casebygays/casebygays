#pragma once
#include "StructPack.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class File {
	File* parentFile = nullptr;
	int id;
	string icon;
	string name;
	string securityType;
	string pass;
public:
	static vector<File*> files;
	static int fileId;

	File(int id, string icon, string s, string n) : id(id), icon(icon), securityType(s), name(n), pass("") {}
	virtual void add(File* child) {}
	virtual void erase(int id) {}
	virtual void setParent(File* f) { parentFile = f; }
	void setSecurity(string security) { securityType = security; }
	void setPass(string p) { pass = p; }
	virtual File* getParent() { return parentFile; }
	virtual int getId() { return id; }
	virtual string getName() { return name; }
	virtual int getFileCount() { return NULL; }
	virtual File* getFile(int num) { return nullptr; }
	string getSecurity() { return securityType; }
	string getPass() { return pass; }
	string getIcon() { return icon; }
};

class txt : public File {
	string desc;
public:
	txt(int i, string s, string n, string d) : File(i, "[T]", s, n), desc(d) {}
	txtS save();
	void load() {}
	string getDesc() {
		return desc;
	}
};

class exe : public File {
public:
	exe(int i, string s, string n) : File(i, "[>]", s, n) {}
	exeS save();
	void load();
};

class Folder : public File {
	vector<File*> childFile;
public:
	Folder(char i, string s, string n) : File(i, "[_]", s, n) {}
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