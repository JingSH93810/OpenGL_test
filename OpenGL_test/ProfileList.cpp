#include "ProfileList.h"


Node * ProfileList::GetHead() const
{
	return head;
}

void ProfileList::SetHead(Node * p)
{
	head = p;
	nodeCount = 1;
}

Node * ProfileList::Locate(int pos)
{
	int i = 0;
	Node *p = head;

	if (pos < 0)
		return NULL;

	while (NULL != p && i < pos)
	{
		p = p->next;
		i++;
	}

	return p;
}

bool ProfileList::Insert(Profile* item, int pos)
{
	Node* p = Locate(pos);
	if (NULL == p)
		return false;

	Node* node = new Node(item);
	if (NULL == node)
	{
		cout << "·ÖÅäÄÚ´æÊ§°Ü!" << endl;
		exit(1);
	}
	node->next = p->next;
	p->next = node;
	nodeCount++;
	return true;
}

Profile* ProfileList::GetData(int pos)
{
	Node* p = Locate(pos);
	if (NULL == p)
		return NULL;

	return p->profile;
}

int ProfileList::GetNodeNumber()
{
	return nodeCount;
}

ProfileList::~ProfileList()
{
	Node *p;
	while( head != NULL)
	{
		p = head;
		head = head->next;
		delete(p);
	}
	nodeCount = 0;
}
