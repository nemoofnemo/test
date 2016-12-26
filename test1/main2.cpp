#include <cstdio>
#include <cstdlib>
#include <list>

using namespace std;

int main(void) {
	int count;
	list<char> ls;
	scanf("%d", &count);
	getchar();

	for (int k = 0; k < count; ++k) {
		char ch;
		bool flag = false;
		while ((ch = getchar()) != '\n') {
			flag = true;
			switch (ch) {
			case '[':
			case '(':
				ls.push_back(ch);
				break;
			case ']':
				if (ls.rbegin() != ls.rend()) {
					if (*ls.rbegin() == '[') {
						ls.pop_back();
					}
					else {
						puts("No");
						goto cl;
					}
				}
				else {
					puts("No");
					goto cl;
				}
				break;
			case ')':
				if (ls.rbegin() != ls.rend()) {
					if (*ls.rbegin() == '(') {
						ls.pop_back();
					}
					else {
						puts("No");
						goto cl;
					}
				}
				else {
					puts("No");
					goto cl;
				}
				break;
			default:
				puts("No");
				goto cl;
				break;
			}
		}

		if (ls.size()) {
			puts("No");
		}
		else {
			if (flag)
				puts("Yes");
			else
				puts("No");
		}

		cl:
		ls.clear();
		flag = false;
	}

	return 0;
}
