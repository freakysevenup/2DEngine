#include "SpriteAnimation.h"
#include "ErrorLog.h"
#include "ColourRGB8.h"
#include "Rectangle.h"

std::map<std::string, AnimationSet> Animation::m_animationSets = { std::make_pair(" ", std::make_pair(SpriteAtlas(), std::vector<int>())) };

void Animation::CreateAnimationSet(const SpriteAtlas& spriteAtlas, const std::vector<int>& indices, const std::string& animationName)
{
	m_animationSet.first = spriteAtlas;
	m_animationSet.second = indices;

	auto it = m_animationSets.find(animationName);
	if (it != m_animationSets.end())
	{
		addReference();
	}
	else
	{
		m_animationSets.insert(std::make_pair(animationName, m_animationSet));
	}
}

AnimationSet Animation::GetAnimationSet(const std::string& animationName)
{
	auto it = m_animationSets.find(animationName);
	if (it != m_animationSets.end())
	{
		return it->second;
	}

	ErrorLog::GetInstance()->Log(ErrorLog::SeverityLevel::JADE_ERROR, animationName + " not found, null AnimationSet returned");
	return AnimationSet();
}

SpriteAnimation::SpriteAnimation(Rectangle * dimensions, const std::string& animationName)
{
	m_dims = dimensions;
	m_animationSet = m_animation.GetAnimationSet(animationName);
}

void SpriteAnimation::Play(int index)
{
	for (size_t i = 0; i < m_animationSet.second.size(); i++)
	{
		if (m_animationSet.second[i] == index)
		{
			m_spritebatch.Draw(*m_dims, m_animationSet.first.GetTexCoords(index), m_animationSet.first.GetTexture().m_id, 0.0f, glm::vec4(1.0f));
		}
	}
}
