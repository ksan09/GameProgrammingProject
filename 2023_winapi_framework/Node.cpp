#include "pch.h"
#include "Node.h"

Node::Node()
	: m_eNodeState(NODE_STATE::RUNNING)
	, m_bStarted(false)
{
}

Node::~Node()
{
}

NODE_STATE Node::Update()
{
	if (m_bStarted == false)
	{
		OnStart();
		m_bStarted = true;
	}

	m_eNodeState = OnUpdate();

	if (m_eNodeState == NODE_STATE::SUCCESS
		|| m_eNodeState == NODE_STATE::FAILURE)
	{
		OnStop();
		m_bStarted = false;
	}

	return m_eNodeState;
}

DecoratorNode::DecoratorNode(Node* child)
	: m_pChildNode (child)
{
}

DecoratorNode::~DecoratorNode()
{
	if (m_pChildNode != nullptr)
		delete m_pChildNode;
}

InverterNode::InverterNode(Node* child)
	: DecoratorNode(child)
{
}

InverterNode::~InverterNode()
{
}

void InverterNode::OnStart()
{
}

NODE_STATE InverterNode::OnUpdate()
{
	switch (m_pChildNode->Update())
	{
	case NODE_STATE::RUNNING:
		m_eNodeState = NODE_STATE::RUNNING;
		break;
	case NODE_STATE::SUCCESS:
		m_eNodeState = NODE_STATE::FAILURE;
		break;
	case NODE_STATE::FAILURE:
		m_eNodeState = NODE_STATE::SUCCESS;
		break;
	default:
		break;
	}

	return m_eNodeState;
}

void InverterNode::OnStop()
{
}

RepeatNode::RepeatNode(Node* child)
	: DecoratorNode(child)
{
}

RepeatNode::~RepeatNode()
{
}

void RepeatNode::OnStart()
{
}

NODE_STATE RepeatNode::OnUpdate()
{
	if(m_pChildNode != nullptr)
		m_eNodeState = m_pChildNode->Update();
	return NODE_STATE::RUNNING;
}

void RepeatNode::OnStop()
{
}

CompositeNode::CompositeNode()
{
}

CompositeNode::~CompositeNode()
{
	std::vector<Node*>::iterator iter = m_pChildren.begin();
	for (iter; iter == m_pChildren.end(); ++iter)
		iter = m_pChildren.erase(iter);
}

void CompositeNode::RegisterChild(Node* child)
{
	m_pChildren.push_back(child);
}

ActionNode::ActionNode()
{
}

ActionNode::~ActionNode()
{
}

SequenceNode::SequenceNode()
	: m_iCurrent(0)
{
}

SequenceNode::~SequenceNode()
{
}

void SequenceNode::OnStart()
{
	m_iCurrent = 0;
}

NODE_STATE SequenceNode::OnUpdate()
{
	if (m_pChildren.empty())
		return NODE_STATE::FAILURE;

	auto child = m_pChildren[m_iCurrent];

	switch (child->Update())
	{
	case NODE_STATE::RUNNING:
		m_eNodeState = NODE_STATE::RUNNING;
		break;
	case NODE_STATE::FAILURE:
		return NODE_STATE::FAILURE;
		break;
	case NODE_STATE::SUCCESS:
		m_iCurrent++;
		break;
	default:
		break;
	}

	if (m_iCurrent == m_pChildren.size())
		m_eNodeState = NODE_STATE::SUCCESS;
	else
		m_eNodeState = NODE_STATE::RUNNING;

	return m_eNodeState;
}

void SequenceNode::OnStop()
{
}

SelectorNode::SelectorNode()
{
}

SelectorNode::~SelectorNode()
{
}

void SelectorNode::OnStart()
{
}

NODE_STATE SelectorNode::OnUpdate()
{
	if (m_pChildren.empty())
		return NODE_STATE::FAILURE;

	for (auto node : m_pChildren)
	{
		switch (node->Update())
		{
		case NODE_STATE::RUNNING:
			return NODE_STATE::RUNNING;
		case NODE_STATE::SUCCESS:
			return NODE_STATE::SUCCESS;
		case NODE_STATE::FAILURE:
			break;
		default:
			break;
		}
	}

	return NODE_STATE::FAILURE;
}

void SelectorNode::OnStop()
{
}
