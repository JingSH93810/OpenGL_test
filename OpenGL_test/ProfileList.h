#pragma once
#include <string.h>
#include <math.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
using namespace std;

struct Node
{
	GLdouble* vertexArray;
	Node* next;
	Node() {
		vertexArray = NULL;
		next = NULL;
	}
	Node(GLdouble* item, Node *ptr = NULL)
		//函数参数表中的形参允许有默认值，但是带默认值的参数需要放后面
	{
		next = ptr;
		vertexArray = item;
	}
};
class ProfileList
{
public:
	ProfileList() { head = NULL; nodeCount = 0; };
	ProfileList(GLdouble* item) { head = new Node(item); nodeCount = 1; };
	Node* GetHead() const;
	void SetHead(Node* p);
	Node* Locate(int pos);
	bool Insert(GLdouble* item, int pos);
	GLdouble* GetData(int pos);
	int GetNodeNumber();

	~ProfileList();

private:
	Node* head;
	int nodeCount;
	
};

