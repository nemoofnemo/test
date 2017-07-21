#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <list>

using namespace std;

const int BLOCK_COUNT = 4;		//amount of blocks. 

//运行过程中创建的临时文件与可执行文件在同一目录下

struct Node {
	unsigned id;
	unsigned next_id;
	int value;

	Node() {
		id = 0;
		next_id = 0;
		value = 0;
	}
};

class QueueEx {
private:
	list<Node> headList;
	list<Node> tailList;
	unsigned index;	//overflow warning
	int count;

	void writeToFile(list<Node> & l) {
		auto it = l.begin();
		auto end = l.end();
		while (it != end) {
			char name[256] = { 0 };	//warning
			itoa(it->id, name, 10);		//type convert: unsigned to int
			fstream fs;
			fs.open(name, fstream::out | fstream::trunc);
			fs << it->value << endl << it->next_id << endl;	
			fs.close();
			it++;
		}
		cout << "write 4 blocks to file" << endl;
	}

	void deleteFile(unsigned id) {
		char path[256] = { 0 };
		itoa(id, path, 10);
		remove(path);
	}

	bool readOneFromFile(unsigned id, Node * ptr) {
		char name[256] = { 0 };	//warnning
		itoa(id, name, 10);			//type convert: unsigned to int
		ptr->id = id;
		ifstream fs;
		fs.open(name, fstream::in);
		string str;
		fs >> str;
		ptr->value = atoi(str.c_str());
		str = "";
		fs >> str;
		ptr->next_id = atoi(str.c_str());
		fs.close();
		deleteFile(id);
		cout << "read 1 file" << endl;
		return true;
	}

	void readFromFile(unsigned id, list<Node> & l) {
		unsigned target = id;
		l.clear();
		while (l.size() < BLOCK_COUNT)
		{
			Node temp;
			temp.id = target;
			readOneFromFile(target, &temp);
			l.push_back(temp);
			target = temp.next_id;
		}
	}

public:
	QueueEx() {
		count = 0;
		index = 1;
	}

	virtual ~QueueEx() {
		//clear ..
		//....
	}
	
	bool push_back(int val) {
		//new queue node
		cout << "push 1 block to queue, val:" <<val << endl;
		Node temp;
		temp.id = index++;
		temp.value = val;

		if (count < BLOCK_COUNT) { // elements in queue's head
			if (count != 0) {
				headList.back().next_id = temp.id;
			}
			headList.push_back(temp);
			count++;
			return true;
		}

		if (count >= BLOCK_COUNT && count < BLOCK_COUNT + BLOCK_COUNT) { // fill two block in memory : head and tail
			if (tailList.size() == 0) {
				headList.back().next_id = temp.id;
			}
			else {
				tailList.back().next_id = temp.id;
			}
			tailList.push_back(temp);
			count++;
			return true;
		}

		//write memory to file and push back new node.
		tailList.back().next_id = temp.id;

		if (tailList.size() == BLOCK_COUNT) {
			writeToFile(tailList);
			tailList.clear();
		}

		tailList.push_back(temp);
		count++;
		return true;
	}

	bool pop_front(int * val) {
		if ( val == nullptr ) {
			return false;
		}

		if ( count == 0 ) {
			return false;
		}

		*val = headList.front().value;
		cout << "pop 1 block ,val:" << *val << endl;

		if (count <= BLOCK_COUNT) {
			headList.pop_front();
			count--;
			return true;
		}

		if (count <= BLOCK_COUNT + BLOCK_COUNT) {
			headList.pop_front();
			headList.push_back(tailList.front());
			tailList.pop_front();
			count--;
			return true;
		}

		unsigned next = headList.front().next_id;
		headList.pop_front();
		count--;

		if (count == BLOCK_COUNT + BLOCK_COUNT) {	//adjust memory .
			Node temp;
			unsigned target = (headList.size() == 0) ? next: headList.back().next_id;
			while (headList.size() < BLOCK_COUNT) {
				if (!readOneFromFile(target, &temp)) {
					cout << "error 1" << endl;
					exit(-1);
				}
				headList.push_back(temp);
				target = temp.next_id;
			}
			while (tailList.size() < BLOCK_COUNT)
			{
				if (!readOneFromFile(target, &temp)) {
					cout << "error 2" << endl;
					exit(-1);
				}
				tailList.push_front(temp);
				target = temp.next_id;
			}
			return true;
		}
		
		if (headList.size() == 0) {
			readFromFile(next, headList);
		}
		
		return true;
	}
};

int main(void) {
	QueueEx q;
	for (int i = 1; i <= 10; ++i) {
		q.push_back(i);
	}


	for (int i = 1; i <= 10; ++i) {
		int val;
		q.pop_front(&val);
	}

	return 0;
}