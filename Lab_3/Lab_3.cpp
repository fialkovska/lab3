#include <conio.h>
#include <iostream>
#include <fstream>

using namespace std;

#define N 6

int read_matrix(int matr[N][N]) {
	ifstream in("l3-1.txt");
	if (in.is_open())
	{
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				in >> matr[i][j];

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
				cout << matr[i][j] << "\t";
			cout << "\n";
		}

		in.close();
		return **matr;
	}
	else
	{
		cout << "Файл не знайдено.";
		return 0;
	}
}

int connectivity_matrix(int con_matr[N][N], int matr[N][N]) {
	cout << "\nМатриця зв'язностi: " << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (matr[i][j] > 0) {
				con_matr[i][j] = 1;
			}
			else {
				con_matr[i][j] = matr[i][j];
			}
			cout << con_matr[i][j] << "\t";
		}
		cout << endl;
	}

	return **con_matr;
}

int gamilton(int k, int con_matr[N][N], int c[N], int path[N], int v0)
{
	int v, q1 = 0, k1;
	for (v = 0; v < N && !q1; v++)
	{
		if (con_matr[v][path[k - 1]] || con_matr[path[k - 1]][v])
		{
			if (k == N && v == v0) {
				q1 = 1;
			}
			else if (c[v] == -1)
			{
				c[v] = k; path[k] = v;
				k1 = k + 1;
				q1 = gamilton(k1, con_matr, c, path, v0);
				if (!q1) c[v] = -1;
			}
			else continue;
		}
	}   return q1;
}

int if_gamilton(int con_matr[N][N], int c[N], int path[N], int v0) {
	cout << "\nГамiльтонiв цикл:\n";
	for (int j = 0; j < N; j++) {
		c[j] = -1;
	}
	path[0] = v0;
	c[v0] = v0;

	if (gamilton(1, con_matr, c, path, v0)) {}
	else {
		cout << "Немає рiшень\n";
	}
	return *path;
}

int output(int matr[N][N], int path[N]) {
	int weight = 0;
	cout << " Ребро : Вага \n";
	for (int i = 0; i < N; i++) {
		if (i == N - 1) {
			cout << " " << path[i] + 1 << " - " << path[0] + 1 << " : " << matr[path[i]][path[0]] << endl;
			weight += matr[path[i]][path[0]];
		}
		else {
			cout << " " << path[i] + 1 << " - " << path[i + 1] + 1 << " : " << matr[path[i]][path[i + 1]] << endl;
			weight += matr[path[i]][path[i + 1]];
		}
	}
	cout << "\n Загальна вага шляху: " << weight << endl << endl;
	return  0;
}



void main()
{
	setlocale(LC_ALL, "Ukrainian");
	int matr[N][N];
	int con_matr[N][N];

	int c[N];
	int path[N];
	int v0 = 0;    

	cout << "Кiлькiсть вершин: " << N << endl;
	cout << "Матриця ваг: " << endl;
	read_matrix(matr);
	connectivity_matrix(con_matr, matr);

	if_gamilton(con_matr, c, path, v0);
	output(matr, path);

	system("pause");
}