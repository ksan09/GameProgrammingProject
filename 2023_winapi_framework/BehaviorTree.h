#pragma once
#include "Node.h"

class BehaviorTree
{
public:
	BehaviorTree(Node* rootNode);
	~BehaviorTree();
public:
	NODE_STATE Update();
private:
	Node* m_pRootNode;
	NODE_STATE m_eState;
};

