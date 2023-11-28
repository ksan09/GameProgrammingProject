#pragma once

class Node
{
public:
	Node();
	virtual ~Node();
public:
	NODE_STATE Update();
protected:
	virtual void OnStart() abstract;
	virtual NODE_STATE OnUpdate() abstract;
	virtual void OnStop() abstract;
public:
	NODE_STATE GetNodeState() { return m_eNodeState; }
protected:
	NODE_STATE m_eNodeState;
	bool m_bStarted;
};

class CompositeNode
	: public Node
{
public:
	CompositeNode();
	virtual ~CompositeNode();
public:
	void RegisterChild(Node* child);
protected:
	std::vector<Node*> m_pChildren;
};

class SequenceNode
	: public CompositeNode
{
public:
	SequenceNode();
	~SequenceNode();
public:
	virtual void OnStart() override;
	virtual NODE_STATE OnUpdate() override;
	virtual void OnStop() override;
private:
	int m_iCurrent;
};

class SelectorNode
	: public CompositeNode
{
public:
	SelectorNode();
	~SelectorNode();
public:
	virtual void OnStart() override;
	virtual NODE_STATE OnUpdate() override;
	virtual void OnStop() override;
};

class DecoratorNode
	: public Node
{
public:
	DecoratorNode(Node* child);
	virtual ~DecoratorNode();
protected:
	Node* m_pChildNode;
};

class InverterNode
	: public DecoratorNode
{
public:
	InverterNode(Node* child);
	~InverterNode();
public:
	virtual void OnStart() override;
	virtual NODE_STATE OnUpdate() override;
	virtual void OnStop() override;
};

class RepeatNode
	: public DecoratorNode
{
public:
	RepeatNode(Node* child);
	~RepeatNode();
public:
	virtual void OnStart() override;
	virtual NODE_STATE OnUpdate() override;
	virtual void OnStop() override;
};

class ActionNode
	: public Node
{
public:
	ActionNode();
	virtual ~ActionNode();
};

