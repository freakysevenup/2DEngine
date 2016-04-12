#pragma once
#include "SpriteAtlas.h"
#include "SpriteBatch.h"
#include <vector>
#include <map>
#include <string>
#include "Reference.h"

typedef std::pair<SpriteAtlas, std::vector<int>> AnimationSet;

class Animation : public Reference
{
public:
	void CreateAnimationSet(const SpriteAtlas& spriteAtlas, const std::vector<int>& indices, const std::string& animationName);
	AnimationSet GetAnimationSet(const std::string& animationName);

private:
	AnimationSet m_animationSet;
	static std::map<std::string, AnimationSet> m_animationSets;
};

class SpriteAnimation
{
public:
	SpriteAnimation(Rectangle * dimensions, const std::string& animationName);

	void Play(int index);

private:

	bool m_isLooped;
	bool m_isPlaying;
	bool m_isStopped;
	int m_currentFrame;
	Animation m_animation;
	AnimationSet m_animationSet;
	SpriteBatch m_spritebatch;
	Rectangle * m_dims;
};

