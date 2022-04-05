// append 에서 고려할 요소 : empty() 일때
// insert에서 고려할 것 : tail삽입, head삽입
// delete 에서 고려할 것 : head 삭제(1.원소가 하나 남았을 때 2.그냥 삭제하는거일때) tail 삭제 

#include <iostream>
#include <string>
using namespace std;

struct node {
	int data;
	node* next;
	node* prev;
};

class doublyLinkedlist {
private:
	int listSize;
	node* head;
	node* tail;
public:
	doublyLinkedlist();
	bool empty();
	void append(int data);
	void insertion(int idx, int data);
	void delection(int idx);
	void print();
};

doublyLinkedlist::doublyLinkedlist()
{
	head = NULL;
	tail = NULL;
	listSize = 0;
}

bool doublyLinkedlist::empty()
{
	return (listSize == 0);
}

// append 에서 고려할 요소 : empty() 일때
void doublyLinkedlist::append(int data) // tail에 노드 추가 => O(1)
{
	node* newNode = new node;
	newNode->data = data;
	newNode->next = NULL;
	newNode->prev = NULL;

	if (empty())
	{
		head = newNode;
		tail = newNode;
		listSize++;
	}

	else {
		tail->next = newNode;
		newNode->prev = tail;
		tail = newNode;
		listSize++;
	}
}

// insert에서 고려할 것 : tail삽입, head삽입. 중간삽입은 삽입할 인덱스의 노드 직전의 노드를 구하므로, for문을 "조금" 돌린다.(i=1 일때 부터시작)
// tail에 insert를 진행하는 것은 idx == listSize 일때이다. (tail 노드 삭제연산의 경우는 idx == listSize-1 일떄이다)
// if (idx < 0 || idx > listSize) return; 에서 delete 연산과 다르게 idx ">" listSize 인것도 주의하자.
void doublyLinkedlist::insertion(int idx, int data) 
{
	if (idx < 0 || idx > listSize)
		return;

	else if (idx == listSize) // tail에 삽입이므로 append 호출 => O(1)
	{
		append(data);
		listSize++;
		cout << "insertion에서 appeend 호출" << endl;
	}

	else if (idx == 0) // head 에 삽입 => O(1)
	{
		node* newNode = new node;
		newNode->data = data;
		newNode->next = head;
		head->prev = newNode;
		newNode->next= head;
		head = newNode;
		listSize++;
	}

	else // 중간에 어딘가에 삽입 => O(n)
	{
		node* newNode = new node;
		newNode->data = data;
		node* curNode = head;
		for (int i = 1; i < idx; i++)
		{
			curNode = curNode->next;
		}
		newNode->next = curNode->next;
		curNode->next->prev = newNode;

		newNode->prev = curNode;
		curNode->next = newNode;
		listSize++;
	}
}

// delete 에서 고려할 것 : head 삭제(1.원소가 하나 남았을 때 2.그냥 삭제하는거일때) tail 삭제 3.중간 삽입에서 for문은 i=0부터 돌리고, 삭제할 노드와 그전노드인 curNode,preNode를 구한다.
// tail 노드 삭제시 insert 연산의 경우엔 idx == listSize 일때 진행했지만, delete 연산은 idx == listSize-1 일 떄이다.
// (idx < 0 || idx >= listSize || empty()) return; 에서 idx ">=" listSize 인것도 주의하자. (insert연산은 idx ">" listSize 이다.)
void doublyLinkedlist::delection(int idx)
{
	if (idx < 0 || idx >= listSize || empty())
		return;

	node* curNode = head;
	if (idx == 0) // head 삭제 => O(1)
	{
		if (listSize == 1)
		{
			head = tail = NULL;
		}
		else
		{
			head = head->next;
		}
	}

	
	else if (idx == listSize-1) // tail 삭제 => O(1)
	{
		node* tmp = tail;
		tail = tmp->prev;
		tail->next = NULL;
		delete tmp;
		listSize--;
	}
	
	else // 중간 노드 삭제 => O(n)
	{
		node* preNode = head;
		for (int i = 0; i < idx; i++)
		{
			preNode = curNode;
			curNode = curNode->next;
		}
		preNode->next = curNode->next;
		curNode->next->prev = preNode;
		delete curNode;
		listSize--;
	}
}

void doublyLinkedlist::print()
{
	if (empty())
		cout << "empty";

	node* curNode = head;
	while (curNode != NULL)
	{
		cout << curNode->data << " ";
		curNode = curNode->next;
	}
	cout << endl;
}

int main(void)
{
	doublyLinkedlist d;

	int testCase;
	cin >> testCase;
	while (testCase--)
	{
		string command;
		cin >> command;
		if (command == "empty")
		{
			if (d.empty())
				cout << "EMPTY" << endl;
			else
				cout << "NOT EMPTY" << endl;
		}
		else if (command == "append")
		{
			int data;
			cin >> data;
			d.append(data);
		}
		else if (command == "insert")
		{
			int idx, data;
			cin >> idx >> data;
			d.insertion(idx, data);
		}
		else if (command == "delete")
		{
			int idx;
			cin >> idx;
			d.delection(idx);
		}
		else if (command == "print")
		{
			d.print();
		}
	}
}
