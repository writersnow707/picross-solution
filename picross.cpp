#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <Windows.h>
using namespace std;

void init_map(int** map) {
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			map[i][j] = 0;
		}
	}
}

void printmap(int** map) {
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++)
			cout << ((map[i][j] == 0) ? "□" : "■") << "";
		cout << endl;
	}
}

int main (void) {
	vector<int> numbers;
	ifstream readFile; // input file stream
	int** map;
	int sum = 0;
	int dif = 0;
	int line = 0;

	map = new int*[15];

	for (int i = 0; i < 15; i++)
		map[i] = new int[15];

	init_map(map);

	readFile.open("picross.txt");

	if (readFile.is_open())	{
		while (!readFile.eof()) {
			sum = 0;
			dif = 15;
			string str;
			getline(readFile, str);

			stringstream ss(str);

			while (getline(ss, str, ' '))
				numbers.push_back(stoi(str));
			

			for (auto iter : numbers) 
				sum += iter;

			sum += numbers.size() - 1;
			//cout << sum << endl;
			dif -= sum;

			sum = 0;
			for (auto iter : numbers) {
				if (iter > dif) {
					for (int paint = dif; paint < iter; paint++) {
						if (line < 15) map[line%15][sum + paint] = 1;
						else map[sum + paint][line%15] = 1;
					}
				}
				sum += iter + 1;
			}

			while (!numbers.empty())
				numbers.pop_back();

			system("cls");
			printmap(map);
			Sleep(300);
			line++;
		}
		readFile.close();

		for (int i = 0; i < 15; i++)
			delete[] map[i];
	}
	return 0;
}
