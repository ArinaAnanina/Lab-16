#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <windows.h>
using namespace std;
void PrintArray(vector<int> list)
{
	for (int i = 0; i < list.size(); i++)
	{
		cout << list[i] << "\t";
	}
	cout << endl;
}
void CreatArray(vector<int>& list)
{
	for (int i = 0; i < list.size(); i++)
	{
		list[i] = rand() % 1000;
	}
}


vector<int> Merger(vector<int> list1, vector<int> list2)
{
	int l1 = 0;
	int l2 = 0;
	vector<int>tmp;
	while (l1 < list1.size() && l2 < list2.size())
	{
		if (list1[l1] <= list2[l2])
		{
			tmp.push_back(list1[l1]);
			l1++;
		}
		else
		{
			tmp.push_back(list2[l2]);
			l2++;
		}
	}
	while (l1 < list1.size())
	{
		tmp.push_back(list1[l1]);
		l1++;
	}
	while (l2 < list2.size())
	{
		tmp.push_back(list2[l2]);
		l2++;
	}

	return tmp;
}
void balanced_sort(vector<int>& list)
{
	if (list.size() < 2)
	{
		return;
	}
	else if (list.size() == 2)
	{
		if (list[0] > list[1])
		{
			int tmp = list[0];
			list[0] = list[1];
			list[1] = tmp;
		}
		return;
	}
	vector<int> left;
	vector<int> right;
	int mid = list.size() / 2;
	for (int i = 0; i < mid; i++)
	{
		left.push_back(list[i]);
	}
	for (int i = mid; i < list.size(); i++)
	{
		right.push_back(list[i]);
	}
	balanced_sort(left);
	balanced_sort(right);
	list = Merger(left, right);
}


void Split_series(vector<vector<int>>& list_of_series, vector<int> list)
{
	int i = 0;
	while (i < list.size())
	{
		vector<int> line;
		line.push_back(list[i]);
		i++;

		while (i < list.size() && list[i - 1] < list[i])
		{
			line.push_back(list[i]);
			i++;
		}

		list_of_series.push_back(line);
	}
}
vector<int> Merge_series(vector<int> list1, vector<int> list2) 
{
	int l1 = 0, l2 = 0;
	vector <int> tmp;
	while (l1 < list1.size() && l2 < list2.size())
	{
		if (list1[l1] <= list2[l2])
		{
			tmp.push_back(list1[l1]);
			l1++;
		}
		else
		{
			tmp.push_back(list2[l2]);
			l2++;
		}
	}
	while (l1 < list1.size())
	{
		tmp.push_back(list1[l1]);
		l1++;
	}
	while (l2 < list2.size())
	{
		tmp.push_back(list2[l2]);
		l2++;
	}
	return tmp;
}
vector<int> natural_sort(vector<int> list)
{
	vector<vector<int>> list_of_series;
	Split_series(list_of_series, list); 

	while (list_of_series.size() >= 2)
	{
		vector<int> Merged = Merge_series(list_of_series[0], list_of_series[1]);
		list_of_series.push_back(Merged); 
		list_of_series.erase(list_of_series.begin());
		list_of_series.erase(list_of_series.begin());
	}
	return list_of_series[0];
}

void fib(int length, int& size1, int& size2)
{
	int t;
	size1 = 0;
	size2 = 1;
	do {
		t = size2;
		size2 = size1 + size2;
		size1 = t;
	} while (size1 + size2 < length);
}

vector<vector<int>> split_to_series(vector<int> list, int& seriesSize)
{
	vector<vector<int>> result;
	int length = 8;
	if (list.size() >= length) {
		while (list.size() % length != 0) {
			length++;
		}
	}
	else {
		length = list.size();
	}

	seriesSize = list.size() / length;
	for (int i = 0; i < length; i++) {
		vector<int> series;
		for (int j = 0; j < seriesSize; j++) {
			series.push_back(list[i * seriesSize + j]);
		}
		result.push_back(series);
	}

	return result;
}

vector<int> get_empty(int size)
{
	vector<int> result;
	for (int i = 0; i < size; i++) {
		result.push_back(NULL);
	}
	return result;
}

vector<vector<int>> merge_lines(vector<vector<int>>& series1, vector<vector<int>>& series2)
{
	vector<vector<int>> result;
	int size = series2.size();
	for (int i = 0; i < size; i++) {
		result.push_back(Merge_series(series1[i], series2[i]));
	}

	series1.erase(series1.begin(), series1.begin() + size);
	series2.clear();

	return result;
}

vector<int> phase_sort(vector<int> list)
{
	if (!list.size()) {
		return list;
	}

	vector<vector<vector<int>>> lines;
	int seriesSize;
	vector<vector<int>> series = split_to_series(list, seriesSize);

	// Находим размеры линий
	int size1, size2;
	fib(series.size(), size1, size2);

	// Сортируем серии
	for (int i = 0; i < series.size(); i++) {
		sort(series[i].begin(), series[i].end());
	}

	// Заполняем линии
	vector<vector<int>> line1;
	for (int i = 0; i < size2; i++) {
		line1.push_back(series[i]);
	}
	lines.push_back(line1);

	vector<vector<int>> line2;
	for (int i = size2; i < size2 + size1; i++) {
		line2.push_back((i < series.size()) ? series[i] : get_empty(seriesSize));
	}
	lines.push_back(line2);

	vector<vector<int>> line3;
	lines.push_back(line3);

	// Проходы
	while (!lines[1].empty()) {
		lines[2] = merge_lines(lines[0], lines[1]);
		lines.insert(lines.begin(), lines[2]);
		lines.pop_back();
	}

	int lastEmptyIndex = 0;
	while (lines[0][0][lastEmptyIndex] == NULL) {
		lastEmptyIndex++;
	}
	lines[0][0].erase(lines[0][0].begin(), lines[0][0].begin() + lastEmptyIndex);

	return lines[0][0];
}



int main()
{
	system("color F0");
	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int size;
	do
	{
		cout << "Введите кол-во чисел в списке: ";
		cin >> size;
	} while (size <= 0);
	vector <int> list(size);
	CreatArray(list);
	PrintArray(list);

	int vvod;
	cout << "1 - Сортировка методом сбалансированного слияния " << endl;
	cout << "2 - Сортировка методом естественного слияния " << endl;
	cout << "3 - Сортировка методом многофазного слияния " << endl;
	cin >> vvod;
	if (vvod == 1)
	{
		cout << "Отсортированный список: " << endl;
		balanced_sort(list);
		PrintArray(list);
	}
	else if (vvod == 2)
	{
		cout << "Отсортированный список: " << endl;
		list = natural_sort(list);
		PrintArray(list);
	}
	else if (vvod == 3)
	{
		cout << "Отсортированный список: " << endl;
		list = phase_sort(list);
		PrintArray(list);
	}
	else 
	{
		cout << "Введено некорректное значение:(" << endl;
	}

	return 0;
}