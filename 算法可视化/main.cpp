#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

// 预定义BGR颜色
#define WHITE Scalar(255, 255, 255)
#define BLACK Scalar(0, 0, 0)
#define BLUE Scalar(255, 0, 0)
#define GREEN Scalar(0, 255, 0)
#define RED Scalar(0, 0, 255)
#define YELLOW Scalar(0, 255, 255)
#define ORANGE Scalar(0, 165, 255)

using namespace cv;
using namespace std;

const int MAXTREELEN = 32;
const int MAXLEN = 100;
int DELAY = 150;

struct Element
{
	int value;
	int height;
	Scalar color;
};
class Array
{
private:
	char* window;
	int window_height;
	int window_width;
	Element** a, * temp1;
	int len;
	bool isContinuity;
	int delay; // 延时（ms）
	void QuickSort(int l, int r);
	int  partition(int l, int r);		//快排辅助
	Array(const Array& x);				//拷贝构造函数
	void Mergesort(int begin, int end);	//归并辅助
	int getmaxbit();
public:
	Array();
	Array(string& select);
	void insert();
	void random_initialization();
	void show();
	void setElementColor(int i, Scalar color);
	void drawArray();
	void insertionSort();				//插入排序
	void selectionSort();				//选择排序
	void bubbleSort();					//冒泡排序
	void quickSort();					//快速排序
	void shellSort();					//希尔排序
	void mergesort();					//归并排序
	void radixsort();					//基数排序
};

struct TreeElement
{
	int value;
	string* text;
	Point pos;
	Scalar color;
};

class Tree
{
private:
	char* window;
	int window_height;
	int window_width;
	TreeElement* tArr;
	int len;
	int unordered_len;
	int dataRange;
	int radius;
	bool isContinuity;
	int delay; // 延时（ms)
public:
	Tree();
	Tree(string& select);
	void insert();
	void show();
	void random_initialization();
	void setElementColor(int i, Scalar color);
	void drawTree(int size);
	void drawResult();
	void down(int u);
	void heapSwap(TreeElement& a, TreeElement& b);
	void heapSort();	//堆排序
};

int main()
{
	printf("**********************\n");
	printf("***** 1.插入排序 *****\n");
	printf("***** 2.选择排序 *****\n");
	printf("***** 3.冒泡排序 *****\n");
	printf("***** 4.快速排序 *****\n");
	printf("***** 5.希尔排序 *****\n");
	printf("***** 6.归并排序 *****\n");
	printf("***** 7.基数排序 *****\n");
	printf("***** 8.堆  排序 *****\n");
	printf("**********************\n");
	string selectSort;
	while (true)
	{
		printf("请输入您的选择：");
		cin >> selectSort;
		if (selectSort.size() == 1 && selectSort[0] >= '1' && selectSort[0] <= '8') break;
		printf("输入有误请重新输入！\n");
	}

	printf("****************************\n");
	printf("*****     默认参数     *****\n");
	printf("***** 1.连续播放       *****\n");
	printf("***** 2.随机初始化数组 *****\n");
	printf("****************************\n");
	string selectParameter;
	while (true)
	{
		printf("是否采用默认参数（y/n）：");
		cin >> selectParameter;
		if (selectParameter.size() == 1 && (selectParameter[0] == 'y' || selectParameter[0] == 'n')) break;
		printf("输入有误请重新输入！\n");
	}

	string select[2];
	if (selectParameter[0] == 'y')
	{
		select[0] = 'y';
		select[1] = 'y';
	}
	else
	{
		while (true)
		{
			printf("是否连续播放（y/n）：");
			cin >> select[0];
			if (select[0].size() == 1 && (select[0][0] == 'y' || select[0][0] == 'n')) break;
			printf("输入有误请重新输入！\n");
		}

		if (select[0][0] == 'y')
		{
			string selectDelay;
			do
			{
				printf("请输入延时（ms）：");
				scanf("%d", &DELAY);
				while (true)
				{
					printf("是否设定延时为%d ms（y/n）:", DELAY);
					cin >> selectDelay;
					if (selectDelay.size() == 1 && (selectDelay[0] == 'y' || selectDelay[0] == 'n')) break;
					printf("输入有误请重新输入！\n");
				}
			} while (selectDelay[0] == 'n');
		}

		while (true)
		{
			printf("是否随机初始化数组（y/n）：");
			cin >> select[1];
			if (select[1].size() == 1 && (select[1][0] == 'y' || select[1][0] == 'n')) break;
			printf("输入有误请重新输入！\n");
		}
	}

	if (selectSort[0] >= '1' && selectSort[0] <= '7')
	{
		Array a(select[0]);

		if (select[1][0] == 'y') a.random_initialization();
		else a.insert();

		if (selectSort[0] == '1') a.insertionSort();
		if (selectSort[0] == '2') a.selectionSort();
		if (selectSort[0] == '3') a.bubbleSort();
		if (selectSort[0] == '4') a.quickSort();
		if (selectSort[0] == '5') a.shellSort();
		if (selectSort[0] == '6')a.mergesort();
		if (selectSort[0] == '7')a.radixsort();

		system("cls");
		a.show();
	}
	else
	{
		Tree a(select[0]);

		if (select[1][0] == 'y') a.random_initialization();
		else a.insert();

		a.heapSort();

		system("cls");
		a.show();
	}

	waitKey(0);

	return 0;
}

int getHeight(int n)
{
	int height = 0;
	while (n) ++height, n /= 2;
	return height;
}

Array::Array(const Array& x) {
	*this = x;
	a = new Element * [len];//这一行代码的bug，找了足足一个小时！
	for (int i = 0; i < len; i++) {
		a[i] = new Element;
		a[i]->color = x.a[i]->color;
		a[i]->value = x.a[i]->value;
		a[i]->height = x.a[i]->height;
	}
	window = new char[7];
}

Array::Array()
{
	window = new char[7];
	strcpy(window, "window");
	window_height = 400;
	window_width = 400;

	a = NULL;
	len = 0;
	isContinuity = true;
	delay = 100;
}

Array::Array(string& select)
{
	window = new char[7];
	strcpy(window, "window");
	window_height = 400;
	window_width = 400;

	a = NULL;
	len = 0;
	isContinuity = (select[0] == 'y');
	delay = DELAY;
}

void Array::QuickSort(int l, int r)
{
	if (l < len) setElementColor(l, BLUE);
	if (r >= 0) setElementColor(r, BLUE);
	drawArray();
	if (l >= r)
	{
		if (l < len) setElementColor(l, GREEN);
		if (r >= 0) setElementColor(r, GREEN);
		drawArray();
		return;
	}
	int i = l - 1, j = r + 1, x = a[l + r >> 1]->value;
	setElementColor(l + r >> 1, ORANGE);
	drawArray();
	while (i < j)
	{
		do
		{
			++i;
			setElementColor(i, BLUE);
			drawArray();
			setElementColor(i, YELLOW);
		} while (a[i]->value < x);
		setElementColor(i, RED);
		drawArray();
		do
		{
			--j;
			setElementColor(j, BLUE);
			drawArray();
			setElementColor(j, RED);
		} while (a[j]->value > x);
		setElementColor(j, YELLOW);
		drawArray();

		if (i < j)
		{
			swap(a[i], a[j]);
			setElementColor(i, YELLOW);
			setElementColor(j, RED);
		}
		drawArray();
	}
	for (int k = l; k <= r; ++k)
		setElementColor(k, WHITE);
	if (i == j) setElementColor(i, GREEN);
	QuickSort(l, i - 1);
	QuickSort(j + 1, r);
}

void Array::insert()
{
	while (true)
	{
		printf("请输入数组的长度(0,%d]：", MAXLEN);
		scanf("%d", &len);
		if (len > 0 && len <= MAXLEN) break;
		printf("输入有误请重新输入！\n");
	}

	a = new Element * [len];
	printf("请输入数组的各元素：\n");
	for (int i = 0; i < len; ++i)
	{
		int x = 0;
		scanf("%d", &x);

		a[i] = new Element;
		a[i]->value = x;
		a[i]->color = WHITE;
	}

	// 计算各数组元素对应高度
	int max = 0x80000000, min = 0x7fffffff;
	for (int i = 0; i < len; ++i)
	{
		if (a[i]->value > max) max = a[i]->value;
		if (a[i]->value < min) min = a[i]->value;
	}

	if (min <= 0) min = -min + 1;
	else min = 0;
	max += min;
	for (int i = 0; i < len; ++i)
	{
		a[i]->height = (a[i]->value + min) * window_height / max;
	}
}

void Array::show()
{
	printf("排序后的结果为：\n");
	for (int i = 0; i < len; ++i)
		printf("%d ", a[i]->value);
	printf("\n");
}

void Array::random_initialization()
{
	srand((unsigned int)time(0));
	len = rand() % MAXLEN + 1;

	a = new Element * [len];
	for (int i = 0; i < len; ++i)
	{
		a[i] = new Element;
		a[i]->value = i + 1;
		a[i]->height = window_height * (i + 1) / len;
		a[i]->color = WHITE;
	}

	random_shuffle(&a[0], &a[len]);
}

void Array::setElementColor(int i, Scalar color)
{
	a[i]->color = color;
}

void Array::drawArray()
{
	Mat img = Mat::zeros(window_height, window_width, CV_8UC3);
	for (int i = 0; i < len; ++i)
	{
		rectangle(img, Point(i * window_width / len, window_height),
			Point((i + 1) * window_width / len, window_height - a[i]->height),
			a[i]->color, FILLED, LINE_8);
	}
	imshow(window, img);
	if (isContinuity) waitKey(delay);
	else waitKey(0);
}

void Array::insertionSort()
{
	drawArray();

	waitKey(0);
	for (int i = 1; i < len; ++i)
	{
		setElementColor(i, BLUE);

		for (int j = i; j > 0; --j)
		{
			setElementColor(j - 1, BLUE);
			drawArray();
			if (a[j]->value >= a[j - 1]->value)
			{
				setElementColor(j, GREEN);
				setElementColor(j - 1, GREEN);
				break;
			}

			swap(a[j], a[j - 1]);
			drawArray();

			setElementColor(j, GREEN);
			if (j - 1 == 0) setElementColor(j - 1, GREEN);
		}
		drawArray();
	}
}

void Array::selectionSort()
{
	drawArray();

	waitKey(0);
	int minindex, temp, old = -1;
	for (int i = 0; i < len - 1; i++)
	{
		minindex = i;
		setElementColor(i, RED);
		drawArray();
		for (int j = i + 1; j < len; j++)
		{
			if (a[j - 1]->color != RED)
				setElementColor(j - 1, WHITE);
			setElementColor(j, BLUE);
			drawArray();
			if (a[j]->value < a[minindex]->value)
			{
				old = minindex;
				minindex = j;
				setElementColor(old, WHITE);
				setElementColor(minindex, RED);
				drawArray();
			}
		}
		if (a[len - 1]->color != RED && a[len - 1]->color == BLUE)
			setElementColor(len - 1, WHITE);
		swap(a[i], a[minindex]);
		setElementColor(i, GREEN);
		drawArray();
	}
	setElementColor(len - 1, GREEN);
	drawArray();
}

void Array::bubbleSort()
{
	drawArray();

	waitKey(0);
	for (int i = 0; i < len; ++i)
	{
		setElementColor(0, BLUE);
		for (int j = 0; j < len - i - 1; ++j)
		{
			setElementColor(j + 1, BLUE);
			drawArray();
			if (a[j]->value > a[j + 1]->value)
			{
				swap(a[j], a[j + 1]);
				drawArray();

			}setElementColor(j, WHITE);
		}
		setElementColor(len - 1 - i, GREEN);
		drawArray();
	}
}

void Array::quickSort()
{
	drawArray();
	waitKey(0);
	QuickSort(0, len - 1);
}

void Array::shellSort()
{
	drawArray();
	waitKey(0);
	int d = len;
	temp1 = new Element;
	while (true)
	{
		d = d / 2;
		for (int x = 0; x < d; x++)
		{
			for (int i = x; i < len; i += d)
				setElementColor(i, YELLOW);
			drawArray();
			int k;
			for (k = x + d; k < len; k = k + d)
			{
				setElementColor(k, BLUE);
				temp1->color = GREEN;
				temp1->height = a[k]->height;
				temp1->value = a[k]->value;
				int j;
				for (j = k - d; j >= 0; j = j - d)
				{
					setElementColor(j, BLUE);
					setElementColor(j + d, BLUE);
					drawArray();
					if (a[j]->value > temp1->value)
					{
						swap(a[j + d], a[j]);
						setElementColor(j + d, GREEN);
						setElementColor(j, GREEN);
					}
					else
					{
						setElementColor(j + d, GREEN);
						setElementColor(j, GREEN);
						break;
					}
					drawArray();
				}
				swap(a[j + d], temp1);
				drawArray();
			}
			setElementColor(k - d, GREEN);
			drawArray();
			for (int i = x; i < len; i += d)
				setElementColor(i, WHITE);
		}if (d == 1)break;
	}
}

int Array::getmaxbit() {
	int max_value = a[0]->value;
	for (int i = 1; i < len; i++) {
		if (a[i]->value > max_value) {
			max_value = a[i]->value;
		}
	}
	int d = 1;
	while (max_value >= 10) {
		d++;
		max_value /= 10;
	}
	return d;
}

void Array::radixsort() {
	int d = getmaxbit(), radix = 1;
	int* cnt = new int[10];
	Array temp(*this);
	strcpy(temp.window, "result");
	for (int i = 0; i < len; i++) {
		temp.a[i]->color = BLACK;
	}
	temp.drawArray();
	moveWindow("result", window_width + 50, 0);
	for (int i = 1; i <= d; i++) {
		for (int j = 0; j < len; j++) {
			a[j]->color = WHITE;
		}
		for (int j = 0; j < 10; j++)cnt[j] = 0;
		for (int j = 0; j < len; j++) {
			int k = (a[j]->value / radix) % 10;
			cnt[k]++;
		}
		for (int j = 1; j < 10; j++) {
			cnt[j] += cnt[j - 1];
		}
		for (int j = len - 1; j >= 0; j--) {
			int k = (a[j]->value / radix) % 10;
			a[j]->color = BLUE;//正要移动
			drawArray();
			a[j]->color = BLACK;
			drawArray();
			temp.a[cnt[k] - 1]->value = a[j]->value;
			temp.a[cnt[k] - 1]->height = a[j]->height;
			temp.a[cnt[k] - 1]->color = GREEN;
			temp.drawArray();
			cnt[k]--;
		}
		for (int j = 0; j < len; j++) {
			a[j]->value = temp.a[j]->value;
			a[j]->color = temp.a[j]->color;
			a[j]->height = temp.a[j]->height;
			drawArray();
			temp.a[j]->color = BLACK;
			temp.drawArray();
		}
		radix *= 10;
	}
}

Tree::Tree()
{
	window = new char[7];
	strcpy(window, "window");
	window_height = 750;
	window_width = 1500;
	tArr = NULL;
	len = 0;
	unordered_len = 0;
	dataRange = 100;
	radius = 0;
	isContinuity = true;
	delay = DELAY;
}

Tree::Tree(string& select)
{
	window = new char[7];
	strcpy(window, "window");
	window_height = 750;
	window_width = 1500;
	tArr = NULL;
	len = 0;
	unordered_len = 0;
	dataRange = 100;
	radius = 0;
	isContinuity = (select[0] == 'y');
	delay = DELAY;
}

void Tree::insert()
{
	while (true)
	{
		printf("请输入数组的长度(0,%d]：", MAXTREELEN);
		scanf("%d", &len);
		if (len > 0 && len <= MAXTREELEN) break;
		printf("输入有误请重新输入！\n");
	}
	unordered_len = len;

	//获得树的高度
	int height = getHeight(len);
	//满二叉树结点数
	int n = pow(2, height) - 1;

	tArr = new TreeElement[n + 1];
	printf("请输入数组的各元素：\n");
	for (int i = 1; i <= len; ++i)
	{
		int x = 0;
		scanf("%d", &x);

		tArr[i].value = x;
		tArr[i].text = new string(to_string(tArr[i].value));
		tArr[i].color = WHITE;
	}

	//层与层之间的距离
	int yDist = window_height / height;
	//最后一层结点之间的距离
	int xDist = window_width * 2 / (n + 1);

	//计算结点圆半径
	radius = min(xDist / 4, yDist / 4);

	//计算最后一层结点的坐标

	int x = xDist / 2, y = window_height - yDist / 2;
	for (int i = (n + 1) / 2; i <= n; ++i)
		tArr[i].pos = Point(x, y), x += xDist;
	//计算剩余结点的坐标
	for (int i = n / 2; i; --i)
		tArr[i].pos = (tArr[i * 2].pos + tArr[i * 2 + 1].pos) / 2 - Point(0, yDist);

	drawTree(len);
}

void Tree::random_initialization()
{
	srand((unsigned int)time(0));
	unordered_len = len = rand() % MAXTREELEN + 1;

	//获得树的高度
	int height = getHeight(len);
	//满二叉树结点数
	int n = pow(2, height) - 1;

	tArr = new TreeElement[n + 1];

	for (int i = 1; i <= len; ++i)
	{
		tArr[i].value = (rand() % dataRange);
		tArr[i].text = new string(to_string(tArr[i].value));
		tArr[i].color = WHITE;
	}

	//层与层之间的距离
	int yDist = window_height / height;
	//最后一层结点之间的距离
	int xDist = window_width * 2 / (n + 1);

	//计算结点圆半径
	radius = min(xDist / 4, yDist / 4);

	//计算最后一层结点的坐标
	int x = xDist / 2, y = window_height - yDist / 2;
	for (int i = (n + 1) / 2; i <= n; ++i)
		tArr[i].pos = Point(x, y), x += xDist;
	//计算剩余结点的坐标
	for (int i = n / 2; i; --i)
		tArr[i].pos = (tArr[i * 2].pos + tArr[i * 2 + 1].pos) / 2 - Point(0, yDist);

	drawTree(len);
}

void Tree::show()
{
	printf("排序后的结果为：\n");
	for (int i = 1; i <= len; ++i)
		printf("%d ", tArr[i].value);
	printf("\n");
}

void Tree::setElementColor(int i, Scalar color)
{
	tArr[i].color = color;
}

void Tree::drawTree(int size)
{
	Mat img = Mat::zeros(window_height, window_width, CV_8UC3);
	//画线
	for (int i = size; i > 1; --i)
		line(img, tArr[i].pos, tArr[i / 2].pos, WHITE, 2, LINE_AA);

	//画圆
	for (int i = 1; i <= len; ++i)
		circle(img, tArr[i].pos, radius, tArr[i].color, FILLED, LINE_AA);

	//画数值
	double fontScale = radius / 25.0;
	Point deviation[3];
	deviation[1] = Point(int(-9 * fontScale), int(10 * fontScale));
	deviation[2] = Point(int(-18 * fontScale), int(10 * fontScale));
	for (int i = 1; i <= len; ++i)
		putText(img, *tArr[i].text, tArr[i].pos + deviation[tArr[i].text->size()], FONT_HERSHEY_SIMPLEX, fontScale, BLACK, 1, LINE_AA, false);

	imshow(window, img);
	if (isContinuity) waitKey(delay);
	else waitKey(0);
}

void Tree::drawResult()
{
	Mat img = Mat::zeros(window_height, window_width, CV_8UC3);

	//画线
	for (int i = 1; i < len; ++i)
		line(img, tArr[i].pos, tArr[i + 1].pos, WHITE, 2, LINE_AA);

	//画圆
	for (int i = 1; i <= len; ++i)
		circle(img, tArr[i].pos, radius, tArr[i].color, FILLED, LINE_AA);

	//画数值
	double fontScale = radius / 25.0;
	Point deviation[3];
	deviation[1] = Point(int(-9 * fontScale), 10 * fontScale);
	deviation[2] = Point(-18 * fontScale, 10 * fontScale);
	for (int i = 1; i <= len; ++i)
		putText(img, *tArr[i].text, tArr[i].pos + deviation[tArr[i].text->size()], FONT_HERSHEY_SIMPLEX, fontScale, BLACK, 1, LINE_AA, false);

	imshow(window, img);
	if (isContinuity) waitKey(delay);
	else waitKey(0);
}

void Tree::down(int u)
{
	drawTree(unordered_len);

	int t = u;
	if (u * 2 <= unordered_len && tArr[u * 2].value > tArr[t].value) t = u * 2;
	if (u * 2 + 1 <= unordered_len && tArr[u * 2 + 1].value > tArr[t].value) t = u * 2 + 1;

	if (u != t)
	{
		setElementColor(t, BLUE);
		drawTree(unordered_len);
		heapSwap(tArr[u], tArr[t]);
		drawTree(unordered_len);
		setElementColor(u, WHITE);

		down(t);
	}
	setElementColor(u, WHITE);
}

void Tree::heapSwap(TreeElement& a, TreeElement& b)
{
	swap(a.value, b.value);
	swap(a.text, b.text);
}

void Tree::heapSort()
{
	drawTree(unordered_len);
	waitKey(0);

	for (int i = unordered_len / 2; i; --i) setElementColor(i, BLUE), down(i);
	drawTree(unordered_len);

	while (unordered_len > 1)
	{
		setElementColor(1, BLUE);
		setElementColor(unordered_len, BLUE);
		drawTree(unordered_len);
		heapSwap(tArr[1], tArr[unordered_len]);
		drawTree(unordered_len);
		setElementColor(1, WHITE);
		setElementColor(unordered_len, WHITE);
		drawTree(unordered_len);
		setElementColor(unordered_len, GREEN);
		unordered_len--;
		drawTree(unordered_len);

		setElementColor(1, BLUE);
		down(1);
		drawTree(unordered_len);
	}
	setElementColor(unordered_len, GREEN);
	unordered_len = 0;
	drawTree(unordered_len);

	drawResult();
	waitKey(0);
}

void Array::mergesort() {
	Mergesort(0, len - 1);
}

void Array::Mergesort(int begin, int end) {
	if (begin < end) {
		int mid = (begin + end) / 2;
		Mergesort(begin, mid);
		Mergesort(mid + 1, end);
		Array temp(*this);
		temp.window = new char[7];
		strcpy(temp.window, "result");
		temp.drawArray();
		moveWindow("result", window_height + 50, 0);
		setElementColor(begin, RED), setElementColor(mid, RED), setElementColor(end, RED);
		drawArray();//红框说明边界begin,middle,end
		setElementColor(begin, WHITE), setElementColor(mid, WHITE), setElementColor(end, WHITE);
		int i = 0, j = 0;
		while (begin + i <= mid && mid + 1 + j <= end) {
			setElementColor(begin + i, BLUE), setElementColor(mid + j + 1, BLUE);
			drawArray();//蓝框说明这两个正在作比较
			setElementColor(begin + i, WHITE), setElementColor(mid + j + 1, WHITE);
			if (a[begin + i]->value < a[mid + 1 + j]->value) {
				temp.a[begin + i + j]->height = a[begin + i]->height;
				temp.a[begin + i + j]->value = a[begin + i]->value;
				setElementColor(begin + i, BLACK);
				drawArray();
				temp.setElementColor(begin + i + j, GREEN);
				temp.drawArray();
				i++;
			}//绿表示比较完成
			else {
				temp.a[begin + i + j]->height = a[mid + 1 + j]->height;
				temp.a[begin + i + j]->value = a[mid + 1 + j]->value;
				setElementColor(mid + j + 1, BLACK);
				drawArray();
				temp.setElementColor(begin + i + j, GREEN);
				temp.drawArray();
				j++;
			}
		}
		while (begin + i <= mid) {
			setElementColor(begin + i, BLUE);
			drawArray();
			setElementColor(begin + i, BLACK);
			drawArray();
			temp.a[begin + i + j]->value = a[begin + i]->value;
			temp.a[begin + i + j]->height = a[begin + i]->height;
			temp.setElementColor(begin + i + j, BLUE);
			temp.drawArray();
			temp.setElementColor(begin + i + j, GREEN);
			temp.drawArray();
			i++;
		}
		while (mid + j + 1 <= end) {
			setElementColor(mid + j + 1, BLUE);
			drawArray();
			setElementColor(mid + j + 1, WHITE);
			temp.a[begin + i + j]->value = a[mid + 1 + j]->value;
			temp.a[begin + i + j]->height = a[mid + 1 + j]->height;
			temp.setElementColor(begin + i + j, BLUE);
			temp.drawArray();
			temp.setElementColor(begin + i + j, GREEN);
			temp.drawArray();
			j++;
		}
		for (i = begin; i <= end; i++) {
			a[i]->height = temp.a[i]->height;
			a[i]->value = temp.a[i]->value;
			a[i]->color = GREEN;
		}
		drawArray();
		for (i = begin; i <= end; i++) {
			a[i]->color = WHITE;
		}
		drawArray();
		destroyWindow("result");
	}
}