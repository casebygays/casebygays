#pragma once
#include "StructPack.h"
#include <iostream>
#include <sstream>
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

	bool visible;
	bool canRemove;
	bool oneshot;
public:
	static vector<File*> files;
	static int fileId;

	File(int id, string icon, string s, string n, bool v, bool cR, bool oneshot) : id(id), icon(icon), securityType(s), name(n), pass(""), visible(v), canRemove(cR), oneshot(oneshot) {}
	void setSecurity(string security) { securityType = security; }
	void setPass(string p) { pass = p; }
	void setVisible(bool v) { visible = v; }
	string getSecurity() { return securityType; }
	string getPass() { return pass; }
	string getIcon() { return icon; }
	bool getVisible() { return visible; }
	bool getCanRemove() { return canRemove; }
	bool getOneshot() { return oneshot; }

	virtual void add(File* child) {}
	virtual void erase(int id) {}
	virtual void setParent(File* f) { parentFile = f; }
	virtual File* getParent() { return parentFile; }
	virtual int getId() { return id; }
	virtual string getName() { return name; }
	virtual int getFileCount() { return NULL; }
	virtual File* getFile(int num) { return nullptr; }

	static string getRoot(File* file) {
		int stop = 30;
		string s = "/" + file->getName();
		File* pfile = file->getParent();

		while (pfile != nullptr and stop > 0) {
			s = "/" + pfile->getName() + s;
			pfile = pfile->getParent();
			stop--;
		}
		return s;
	}
};

class txt : public File {
	string desc;
public:
	txt(int i, string s, string n, string d, bool v, bool cR, bool oneshot) : File(i, "[T]", s, n, v, cR, oneshot), desc(d) {}
	txt(S_File file) : File(file.id, file.icon, file.securityType, file.name, file.visible, file.canRemove, file.oneshot) {

	}
	string getDesc() {
		return desc;
	}
};

class exe : public File {
	string code;
public:
	exe(int i, string s, string n, string c, bool v, bool cR, bool oneshot) : File(i, "[>]", s, n, v, cR, oneshot), code(c) {}
	exe(S_File file) : File(file.id, file.icon, file.securityType, file.name, file.visible, file.canRemove, file.oneshot) {
		code = file.code;
	}
	vector<string> runCode() { // 코드 실행시 '|' 기준으로 잘라서 리턴
		vector<string> commands;
		istringstream iss(code);
		string segment;

		while (getline(iss, segment, '|')) {
			commands.push_back(trim(segment));
		}

		return commands;
	}
	string trim(const string& str) { // 문자열 양쪽 공백 제거 함수
		size_t first = str.find_first_not_of(" \t\n\r");
		if (first == string::npos) return "";
		size_t last = str.find_last_not_of(" \t\n\r");
		return str.substr(first, last - first + 1);
	}
	string getCode() { return code; }
};

class Folder : public File {
	vector<File*> childFile;
public:
	Folder(int id, string security, string name, bool v, bool cR, bool oneshot) : File(id, "[_]", security, name, v, cR, oneshot) {}
	Folder(S_File file) : File(file.id, file.icon, file.securityType, file.name, file.visible, file.canRemove, file.oneshot) {
		if (file.parentID == -1) return;
		for (int i = 0; i < File::getFileCount(); i++) {
			if (File::files[i]->getId() == file.parentID) {
				setParent(File::files[i]);
				File::files[i]->add(this);
			}
		} // 부모 설정
	}

	~Folder() {
		for (File* f : childFile) {
			f->setParent(nullptr);
		}
	}
	int* getChildId() {
		int* r = new int[childFile.size()];
		for (int i = 0; i < childFile.size(); i++) {
			r[i] = childFile[i]->getId();
		}
		return r;
	}
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