#include <iostream>
using namespace std;
#define CMDSIZE 15

string str[CMDSIZE];
int strIndex = 0;

void draw();

int main() {
	while (1) {
		draw();
	}
	

	return 0;
}

void draw() {
	system("cls");
	cout << ">나의 IP : 00x. xx.xx\n";
	cout << ">접속 IP :00. xx.xx\n";
	cout << "==================================================================================\n";
	cout << "	> ※ AAAAA\n";
	cout << "	> ☆ BBBBBB\n";
	cout << "==================================================================================\n";
	for (int i = 0; i < CMDSIZE; i++) {
		if (str[i] == "") break;
		cout << str[i] << "\n";
	}
	cin >> str[strIndex];
	strIndex = (strIndex + 1) % CMDSIZE;
}
