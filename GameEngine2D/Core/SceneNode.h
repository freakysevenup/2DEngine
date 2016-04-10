#pragma once
#include <vector>
#include <string>
#include "Camera.h"
#include <glm\glm.hpp>
using namespace glm;

class SceneNode
{
public:
	SceneNode(const std::string& name, const std::string& tag = "", const vec2& position = vec2(0.0f), const vec2& scale = vec2(1.0f)) :
		m_name(name),
		m_tag(tag),
		m_position(position),
		m_scale(scale)	{ }
	~SceneNode();

	void UpdateAll();
	void RenderAll();

	void AddChild(SceneNode * node);
	void RemoveChild(SceneNode * node);

	void SetTag(std::string tag) { m_tag = tag; }

	inline std::string GetName() { return m_name; }
	inline std::string GetTag() { return m_tag; }

private:

	std::string m_name;
	std::string m_tag;
	std::vector<SceneNode*> m_children;
	vec2 m_position;
	vec2 m_scale;

};

