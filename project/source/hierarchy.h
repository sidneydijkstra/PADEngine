#ifndef HIERARCHY_CLASS
#define HIERARCHY_CLASS

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct node {
	int data;
	struct node* left;
	struct node* right;
};

class Hierarchy
{
public:
	Hierarchy();
	~Hierarchy();

	void addChild(Hierarchy* child);
	void removeChild(Hierarchy* child);

	Hierarchy* getParent() { return _parent; };
	std::vector<Hierarchy*> getChildren() { return _children; }

	int guid;

private:
	std::vector<Hierarchy*> _children;
	Hierarchy* _parent;

	int _nextGuid;
};

#endif