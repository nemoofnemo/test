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
		while (arr[begin] % 2 == 0 && begin < tail) {
			begin++;
		}
		while (arr[tail--] % 2 != 0 && tail >= 0) {
			tail--;
		}
		int temp = arr[begin];
		arr[begin] = arr[tail];
		arr[tail] = temp;
	}
	show(arr, len);
}

int main(void) {
	int arr[] = {4,11,16,20,40,15,13,2,3,1,8,4};
	func(arr, 12);

	return 0;
}
