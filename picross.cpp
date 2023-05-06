#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <Windows.h>
using namespace std;

/*
class picross {
private:
public:
}; */
int cnt = 0;

int** init_map() {
	int** arr = new int* [15];

	for (int i = 0; i < 15; i++)
		arr[i] = new int[15];

	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			arr[i][j] = 0;
		}
	}
	return arr;
}
vector<vector<int>> init_list(string fileName) {
	vector<vector<int>> list(15);
	ifstream readFile;
	string str;
	int line = 0;

	readFile.open(fileName);
	if (readFile.is_open()) {
		while (!readFile.eof()) {
			string str;
			getline(readFile, str);

			stringstream ss(str);

			while (getline(ss, str, ' '))
				list[line].push_back(stoi(str));

			line++;
		}
		readFile.close();
	}
	readFile.close();

	return list;
}
void printmap(int** map) {
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++)
			cout << ((map[i][j] == 0) ? "□" : "■") << "";
		cout << endl;
	}
}
void start_print(int** map, vector<vector<int>> v, int count) {
	int sum = 0;
	int dif = 15;
	int line = 0;

	for (auto iter : v) {
		sum = iter.size() - 1;
		for (int i = 0; i < iter.size(); i++)
			sum += iter[i];
		dif = 15 - sum;
		sum = 0;
		for (int i = 0; i < iter.size(); i++) {
			if (iter[i] > dif) {
				for (int paint = dif; paint < iter[i]; paint++) {
					(count == 0)
						? (map[sum + paint][line % 15] = 1)
						: (map[line % 15][sum + paint] = 1);
				}
				//cnt += iter[i] - dif;
			}
			sum += iter[i] + 1;
		}
		system("cls");
		printmap(map);
		//cout << line << ((count == 0) ? "열 진행중..." : "행 진행중...") 
		//	<< ", cnt = " << cnt << endl;
		Sleep(300);
		line++;
	}
}
void solution(int** map, vector<vector<int>> c, vector<vector<int>> r) {
	start_print(map, r, 0);
	start_print(map, c, 1);
}

int main(void) {
	vector<vector<int>> column_list;
	vector<vector<int>> row_list;
	int** map;

	map = init_map();
	column_list = init_list("picross_column.txt");
	row_list = init_list("picross_row.txt");

	solution(map, column_list, row_list);

	for (int i = 0; i < 15; i++)
		delete[] map[i];
	return 0;
}
