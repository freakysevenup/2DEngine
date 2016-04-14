#include "SceneNode.h"


SceneNode::~SceneNode()
{
	for (size_t i = 0; i < m_children.size(); i++)
	{
		delete m_children[i];
	}
	m_children.clear();
}

void SceneNode::UpdateAll()
{
	for (size_t go = 0; go < m_children.size(); go++)
	{
		m_children[go]->UpdateAll();
	}
}

void SceneNode::RenderAll()
{
	for (size_t go = 0; go < m_children.size(); go++)
	{
		m_children[go]->RenderAll();
	}
}
