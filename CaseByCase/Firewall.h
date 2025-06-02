#pragma once
#include <vector>
using namespace std;
class Firewall {
private:




public:
	int size;//레벨당 자릿수
	vector<int> computerBall; //동적 할당 배열 답
	//vector<int> userBall; //사용자 제시 자릿수
	int count = 0; //답 제시 횟수
	int strike = 0;
	int ball= 0;
	int out= 0;
	void setGame(int level) {
		resetGame();
		for (int i = 0; i < 1 + level; i++) {
			int random;
			while (true){
				random = rand() % 9 + 1;
				if (!contains(computerBall, random)) {
					break;
				}
			}
			computerBall.push_back(random);
		}
	}
	void resetGame() {
		computerBall.clear();
		count = 0;
		strike = 0;
		ball = 0;
		out = 0;
	}
	template<typename T>
	bool contains(const std::vector<T>& vec, const T& value) {
		return std::find(vec.begin(), vec.end(), value) != vec.end();
	}



};