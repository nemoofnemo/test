#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <list>

using namespace std;

const int BLOCK_SIZE = 32;		//bytes in memory block
const int BLOCK_COUNT = 4;		//amount of blocks. 

struct Node {
	unsigned id;
	unsigned next_id;
	char * data;
	int length;

	Node() {
		id = 0;
		next_id = 0;
		data = nullptr;
		length = 0;
	}

	//operator=(){}

	//Node(const Node&){}
};

class QueueEx {
private:
	list<Node> headList;
	list<Node> tailList;
	unsigned index;	//overflow warning
	int count;

	void writeToFile(list<Node> & l) {

	}

	bool readOneFromFile(unsigned id, Node * ptr) {

	}

	void deleteFile(unsigned id) {
		char path[256] = { 0 };
		itoa(id, path, 10);
		remove(path);
	}

	void readFromFile(unsigned id, list<Node> & l) {

	}

public:
	QueueEx() {
		count = 0;
		index = 1;
	}

	virtual ~QueueEx() {

	}
	
	bool push_back(char * data, int length) {
		if (!data || length <= 0) {
			return false;
		}

		//new queue node
		Node temp;
		temp.data = data;
		temp.id = index++;
		temp.length = length;

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

	bool pop_front(char ** data, int * length) {
		if ( !data || length == nullptr ) {
			return false;
		}

		if ( count == 0 ) {
			return false;
		}

		*data = headList.front().data;
		*length = headList.front().length;

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


	return 0;
}