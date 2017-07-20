#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <list>

using namespace std;

const int BLOCK_SIZE = 32;
const int BLOCK_COUNT = 4;

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

	void readFromFile(list<Node> & l) {

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

		headList.pop_front();
		count--;

		if (headList.size() == 0) {

		}
		
		return true;
	}
};