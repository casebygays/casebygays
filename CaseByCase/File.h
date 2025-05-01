#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class File {
	string type;
	string name;
public:
	File(string t, string n) : type(t), name(n) {}
	virtual ~File() {}
	virtual void add(File* child) {}
	virtual void remove(int index) {}
	virtual string getName() {
		return name;
	}
};

class txt : public File {
	string desc;
public:
	txt(string t, string n, string d) : File(t,n), desc(d) {}
	string getDesc() {
		return desc;
	}
};

class exe : public File {
	string url;
public:
	exe(string t, string n, string u) : File(t, n), url(u) {}
	string getURL() {
		return url;
	}
};

class Folder : public File {
	vector<File*> childFile;
public:
	Folder(string t, string n) : File(t, n) {}
	~Folder() {
		for (File* f : childFile)
			delete f;
	}
	void add(File* child) {
		childFile.push_back(child);
	}
	void remove(int index) {
		childFile.erase(childFile.begin() + index);
	}
	int getChildCount() { return childFile.size(); }
};