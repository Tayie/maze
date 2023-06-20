#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <easyx.h>
#include <stack>
#include <windows.h>
#define maxsize 100
using namespace std;
int maze[maxsize][maxsize];
static int y;
struct point {
	int x; //��-1
	int y; //��-1
};
//i ������ j ������
typedef struct {
	int i; //��-1
	int j; //��-1
	int di; //��һ�����鷽λ
}box;

bool path(int yi, int xi, int yo, int xo) {
	stack<box>s;
	box path[maxsize];
	box b;//���õ�ǰ��
	bool find;
	int i, j, di, i1, j1;
	b.i = yi;
	b.j = xi;
	b.di = -1; //b����ǰ�Ŀ�
	s.push(b);
	maze[b.i][b.j] = -1; //�߹���·���-1
	while (!s.empty())
	{
		b = s.top();
		i = b.i;
		j = b.j;
		di = b.di;
		if (j == xo && i == yo)
		{
			cout << "·������:" << endl;
			int k = 0;
			while (!s.empty())
			{
				box b1;
				b1 = s.top();
				s.pop();
				path[k++] = b1;//��ջ������path����
			}
			while (k >= 1)
			{
				k--; //����k++ �����һ��
				cout << "(" << path[k].i << "," << path[k].j << "," << path[k].di << ")";
				if ((k + 2) % 5 == 0) {
					cout << endl;
				}

			}
			cout << endl;
			return true;
		}
		find = false; //find ��ʼΪFalse
		while (di < 4 && !find) //�������ĸ���
		{
			di++;
			switch (di)
			{
			case 0: {i1 = i - 1; j1 = j; break; }//����
			case 1: {i1 = i; j1 = j + 1; break; }//��
			case 2: {i1 = i + 1; j1 = j; break; }//��
			case 3: {i1 = i; j1 = j - 1; break; }//��
			}
			if (maze[i1][j1] == 0) find = true;
		}
		if (find) {
			s.top().di = di;
			b.i = i1;
			b.j = j1;
			b.di = -1;
			s.push(b);
			maze[b.i][b.j] = -1; //�ҵ���ջ�ұ��
		}
		else
		{
			s.pop();
			maze[b.i][b.j] = 0;
		}

	}
	return false;
}
void CreateMaze(int m, int n) {

	for (int i = 0; i < m + 2; i++)
	{
		for (int j = 0; j < n + 2; j++)
		{
			maze[i][j] = 1;
		}
	} //��ʼ��ȫ��ǽ
	for (int i = 0; i < m + 2; i++) {
		for (int j = 0; j < n + 2; j++)
		{
			maze[i][0] = 0;
			maze[0][j] = 0;
			maze[m + 2 - 1][j] = 0;
			maze[i][n + 2 - 1] = 0;
		}//���������һ����Ϊ· �����ڲ�һȦǽ
	}
	vector<point> maze_p; //����һ���洢ǽ������
	point p;
	p.x = 2; //��-1
	p.y = 2; //��-1
	maze_p.push_back(p); //����ʼ�����
	while (maze_p.size()) {
		int count = 0;//���� �������������ܵ��м���·

		int num = rand() % maze_p.size();
		point p1;
		p1 = maze_p[num];

		for (int j = (p1.x) - 1; j < (p1.x) + 2; j++) //��
		{
			for (int i = (p1.y) - 1; i < (p1.y) + 2; i++) {
				if (maze[i][j] == 0 && abs(p1.x - j) + abs(p1.y - i) == 1) {
					count++;
				}
			}
		}

		if (count <= 1) {
			maze[p1.y][p1.x] = 0;
			for (int j = (p1.x) - 1; j < (p1.x) + 2; j++)
			{
				for (int i = (p1.y) - 1; i < (p1.y) + 2; i++) {
					if (maze[i][j] == 1 && abs(p1.x - j) + abs(p1.y - i) == 1) {
						point temp;
						temp.x = j;
						temp.y = i;
						maze_p.push_back(temp);
					}
				}
			}
		}

		maze_p.erase(maze_p.begin());
	}

	maze[2][1] = 0;

	for (int i = m + 2 - 3; i >= 0; i--)
	{
		if (maze[i][n + 2 - 3] == 0) {
			maze[i][n + 2 - 2] = 0;
			y = i;
			break;
		}

	}
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << maze[i + 1][j + 1];
		}
		cout << endl;
	}//��ʾ
	cout << "--------------------------------" << endl;


}


int main() {
	int m, n;
	cout << "����������";
	cin >> m;
	cout << "����������";
	cin >> n;
	CreateMaze(m, n);
	if (!path(2, 1, y, n))
	{
		cout << "���Թ��޽�" << endl;
	}
	const int width = 40;
	{
		auto ret = _getwch();
		initgraph(1920, 1080);
		setlinecolor(YELLOW);
		setfillcolor(RED);
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++) {
				if (maze[i + 1][j + 1] == 1)
				{
					fillrectangle(j * width, i * width, j * width + width - 1, i * width + width - 1); //����ǽ���η���
				}
			}
		}

		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++) {
				if (maze[i + 1][j + 1] == -1)
				{
					setfillcolor(GREEN);
					fillrectangle(j * width, i * width, j * width + width - 1, i * width + width - 1); //����ǽ���η���
					Sleep(500);
				}
			}
		}
		ret = _getwch();
		closegraph();
	}//easyx


}
