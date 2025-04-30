#pragma once

using namespace std;
class File {
	string type;
};
class Folder : File {
	File* childFiles;
public:
	Folder(int cfNum) 
	{
		childFiles = new File[cfNum];
	}
	~Folder()
	{
		delete[] childFiles;
	}
};