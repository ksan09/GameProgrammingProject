#include "pch.h"
#include "BehaviorTree.h"

BehaviorTree::BehaviorTree(Node* rootNode)
	: m_pRootNode(rootNode)
	, m_eState(NODE_STATE::RUNNING)
{
}

BehaviorTree::~BehaviorTree()
{
	if (m_pRootNode != nullptr)
		delete m_pRootNode;
}

NODE_STATE BehaviorTree::Update()
{
	if (m_pRootNode == nullptr)
		return NODE_STATE::FAILURE;

	if (m_eState == NODE_STATE::RUNNING)
		m_eState = m_pRootNode->Update();
	return m_eState;
}
