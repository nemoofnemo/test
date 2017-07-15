#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <list>
#include <map>
#include <string>

using namespace std;

class ss {
public:
	map<string, string> data;

	const string & operator[](const string & key) {
		return data[key];
	}
};

int lowbit(int x) {
	return x&(-x);
}

class test1 {
private:
	int a;

public:
	test1() {
		a = 100;
	}
};

void show(int * arr, int len) {
	for (int i = 0; i < len; ++i) {
		cout << arr[i] << ' ';
	}
	cout << endl;
}

void func(int * arr, int len) {
	show(arr, len);
	int begin = 0;
	int tail = len - 1;
	while (begin < tail) {
		while (arr[begin] % 2 != 0 && begin <= tail) {
			begin++;
		}
		while (arr[tail] % 2 == 0 && tail >= 0) {
			tail--;
		}
		cout << begin << ' ' << tail << endl;
		int temp = arr[begin];
		arr[begin] = arr[tail];
		arr[tail] = temp;
		begin++;
		tail--;
	}
	show(arr, len);
}

void m_sort(int *arr, int begin, int end) {
	if (begin >= end) {
		return;
	}
	
	int cmp = arr[begin];
	int i = begin;
	int d = end;
	while (i < d) {
		while ( i < d && arr[i] < cmp) {
			++i;
		}
		while ( i < d && arr[d] >= cmp) {
			--d;
		}

		if (i < d) {
			int temp = arr[i];
			arr[i] = arr[d];
			arr[d] = temp;
		}
	}

	m_sort(arr, begin, i);
	m_sort(arr, i + 1 , end);

	return;
}

int main(void) {
	int arr[] = {4,11,16,20,40,15,13,2,3,1,8,4,13};
	show(arr, 13);
	m_sort(arr, 0, 12);
	show(arr, 13);
	return 0;
}
