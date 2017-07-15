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
		while (i < d && arr[d] > cmp) {
			--d;
		}
		if (i < d) {
			arr[i] = arr[d];
			i++;
		}
		while (i < d && arr[i] <= cmp){
			++i;
		}
		if (i < d) {
			arr[d] = arr[i];
			d--;
		}
	}
	arr[i] = cmp;
	m_sort(arr, begin, i - 1);
	m_sort(arr, i + 1 , end);

	return;
}

void func1(int arr[3]) {
	cout << arr[4] << endl;
}

class A {
public:
	A() {
		cout << "AC" << endl;
	}
	virtual ~A() {
		cout << "AD" << endl;
	}
};

class B {
public:
	B() {
		cout << "BC" << endl;
	}
	virtual ~B() {
		cout << "BD" << endl;
	}
};

class C : public A, virtual public B {
public:
	C() {
		cout << "CC" << endl;
	}
	virtual ~C() {
		cout << "CD" << endl;
	}
};

class Empty {

};

class A1 {
public:
	virtual void func(int a) {
		cout << "A1" << endl;
	}
	void func(float a) {
		cout << "A2" << endl;
	}
};

class B1 : public A1 {
public:
	void func(int a) {
		cout << "B1" << endl;
	}
};


int main(void) {
	/*int arr[] = {4,11,16,20,40,15,13,2,3,1,8,4,13};
	show(arr, 13);
	func1(arr);*/
	
	

	return 0;
}
