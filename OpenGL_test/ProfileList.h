#pragma once
#include <iostream>
#include "Profile.h"
using namespace std;

struct Node
{
	Profile* profile;
	Node* next;
	Node() {
		profile = NULL;
		next = NULL;
	}
	Node(Profile* item, Node *ptr = NULL)
		//函数参数表中的形参允许有默认值，但是带默认值的参数需要放后面
	{
		next = ptr;
		profile = item;
	}
};
class ProfileList
{
public:
	ProfileList() { head = NULL; nodeCount = 0; };
	ProfileList(Profile* item) { head = new Node(item); nodeCount = 1; };
	Node* GetHead() const;
	void SetHead(Node* p);
	Node* Locate(int pos);
	bool Insert(Profile* item, int pos);
	Profile* GetData(int pos);
	int GetNodeNumber();

	~ProfileList();

private:
	Node* head;
	int nodeCount;
	
};

