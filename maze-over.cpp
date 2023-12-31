#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <easyx.h>
#include <stack>
#include <windows.h>
#define maxsize 1000
using namespace std;
int maze[maxsize][maxsize];
static int y;
struct point {
	int x; //列-1
	int y; //行-1
};
//i 代表行 j 代表列
typedef struct {
	int i; //行-1
	int j; //列-1
	int di; //下一个方块方位
}box;
typedef struct linkstack {
	box pathnode;
	struct linkstack* next;
	int top;
}ls;

ls* push(ls* stack, box b) {
	//创建新元素节点
	ls* n = (ls*)malloc(sizeof(ls));
	n->pathnode = b;
	n->next = stack;
	stack = n; //头指针指向更新
	return stack;
}//头插法插入

ls* pop(ls* stack) {
	if (stack) {
		ls* n = stack;         //声明一个新指针指向栈顶节点
		stack = stack->next;
		free(n);
	}
	return stack;
}
bool isempty(ls* stack) {

	return stack->next == NULL;

}//是否空
box top(ls* stack) {
	return stack->pathnode;
}
ls * inits(ls*& s) {
	s = (ls*)malloc(sizeof(ls));
	s->next = NULL;
	return s;
}
bool path(int yi, int xi, int yo, int xo) {
	ls* p;
	inits(p);
	box path[maxsize];
	box b;//设置当前点
	bool find;
    int i, j, di, i1, j1;
	b.i = yi;
	b.j = xi;
	b.di = -1; //b代表当前的块
	p = push(p,b);
	maze[b.i][b.j] = -1; //走过的路标记-1
	while (!isempty(p))
	{
		b = top(p);
		i = b.i;
		j = b.j;
		di = b.di;
		if (j == xo && i == yo)
		{
			cout << "路径如下:" << endl;
			int k = 0;
			while (!isempty(p))
			{
				box b1;
				b1 = top(p);
				p=pop(p);
				path[k++] = b1;//将栈顶放入path数组
			}
			while (k >= 1)
			{
				k--; //上面k++ 多加了一个
				cout << "(" << path[k].i << "," << path[k].j << "," << path[k].di << ")";
				if (k % 5 == 0) {
					cout << endl;
				}//5个一组输出

			}
			cout << endl;
			return true;
		}
		find = false; //find 初始为False
		while (di < 4 && !find) //找其他四个点
		{
			di++;
			switch (di)
			{
			case 0: {i1 = i - 1; j1 = j; break; }//上面
			case 1: {i1 = i; j1 = j + 1; break; }//右
			case 2: {i1 = i + 1; j1 = j; break; }//下
			case 3: {i1 = i; j1 = j - 1; break; }//左
			}
			if (maze[i1][j1] == 0) find = true;
		}
		if (find) {

			p->pathnode.di= di;
			b.i = i1;
			b.j = j1;
			b.di = -1;
			p = push(p,b);
			maze[b.i][b.j] = -1; //找到进栈且标记
		}
		else
		{
			p = pop(p);
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
	} //初始化全是墙
	for (int i = 0; i < m + 2; i++) {
		for (int j = 0; j < n + 2; j++)
		{
			maze[i][0] = 0;
			maze[0][j] = 0;
			maze[m + 2 - 1][j] = 0;
			maze[i][n + 2 - 1] = 0;
		}//将最外面的一层设为路 保护内部一圈墙
	}
	vector<point> maze_p; //定义一个存储墙的容器
	point p;
	p.x = 2; //列-1
	p.y = 2; //行-1
	maze_p.push_back(p); //将初始点进队
	while (maze_p.size()) {
		int count = 0;//计数 用来计数点四周点有几个路

		int num = rand() % maze_p.size();
		point p1;
		p1 = maze_p[num];

		for (int j = (p1.x) - 1; j < (p1.x) + 2; j++) //列
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

		maze_p.erase(maze_p.begin()+num); //把队列当前墙删除
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
	}//显示
	cout << "--------------------------------------------------------" << endl;


}


int main() {
	int m, n;
	cout << "输入行数：";
	cin >> m;
	cout << "输入列数：";
	cin >> n;
	CreateMaze(m, n);
	if (!path(2, 1, y, n))
	{
		cout << "该迷宫无解" << endl;
	}
	const int width = 20;
	{
		auto ret = _getwch();
		initgraph(1920, 1920);
		setlinecolor(YELLOW);
		setfillcolor(RED);
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++) {
				if (maze[i + 1][j + 1] == 1)
				{
					fillrectangle(j * width, i * width, j * width + width - 1, i * width + width - 1); //绘制墙矩形方块
					Sleep(5);
				}
			}
		}
    
		for (int j = 0; j < n; j++)
		{
			for (int i = 0; i < m; i++) {
				if (maze[i + 1][j + 1] == -1)
				{
					setfillcolor(GREEN);
					fillrectangle(j * width, i * width, j * width + width - 1, i * width + width - 1); //绘制路径方块
					Sleep(0);
				}
			}
		}
		ret = _getwch();
		closegraph();
	}//easyx


}
