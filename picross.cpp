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
	int line = 0;
	int dif = 0;
	int center = 7;
	int x = 0;

	for (auto iter : v) {
		if (iter.size() == 1) {
			if (iter.front() <= center) {
				line++;
				continue;
			}
			else {
				dif = iter.front() - center - 1;
				if (count == 0) {
					map[center][line % 15] = 1;
					for (int i = 1; i <= dif; i++)
						map[center - i][line % 15] = map[center + i][line % 15] = 1;
				}
				else {
					map[line % 15][center] = 1;
					for (int i = 1; i <= dif; i++)
						map[line % 15][center - i] = map[line % 15][center + i] = 1;
				}
			}
		}
		else {
			sum = 0;
			dif = 15;
			for (int i = 0; i < iter.size(); i++)
				sum += iter[i];
			sum += iter.size() - 1;
			dif -= sum;
			sum = 0;
			x = 0;

			for (int i = 0; i < iter.size(); i++) {
				sum += iter[i];
				for (int j = dif+x; j < sum; j++) {
					(count == 0)
						? (map[j][line % 15] = 1)
						: (map[line % 15][j] = 1);
				}
				sum += 1;
				x = sum;
			}
		}
		system("cls");
		printmap(map);
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
