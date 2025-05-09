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

	bool canRemove;
public:
	static vector<File*> files;
	static int fileId;

	File(int id, string icon, string s, string n, bool cR) : id(id), icon(icon), securityType(s), name(n), pass(""), canRemove(cR) {}
	void setSecurity(string security) { securityType = security; }
	void setPass(string p) { pass = p; }
	string getSecurity() { return securityType; }
	string getPass() { return pass; }
	string getIcon() { return icon; }
	bool getCanRemove() { return canRemove; }

	virtual void add(File* child) {}
	virtual void erase(int id) {}
	virtual void setParent(File* f) { 
		parentFile = f;
	}
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
	txt(int i, string s, string n, string d, bool cR) : File(i, "[T]", s, n, cR), desc(d) {}
	txt(S_File file) : File(file.id, file.icon, file.securityType, file.name, file.canRemove) {

	}
	string getDesc() {
		return desc;
	}
};

class exe : public File {
public:
	exe(int i, string s, string n, bool cR) : File(i, "[>]", s, n, cR) {}
	exe(S_File file) : File(file.id, file.icon, file.securityType, file.name, file.canRemove) {

	}
};

class Folder : public File {
	vector<File*> childFile;
public:
	Folder(int id, string security, string name, bool cR) : File(id, "[_]", security, name, cR) {}
	Folder(S_File file) : File(file.id, file.icon, file.securityType, file.name, file.canRemove) {
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