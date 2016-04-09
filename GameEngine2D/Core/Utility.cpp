#include "Utility.h"
#include <SDL2\SDL_timer.h>
#include <random>
#include <ctime>

void Utility::sleep(int milliseconds)
{
	SDL_Delay(milliseconds);
}

std::vector<std::string> Utility::split(const std::string& s, char delim)
{
	std::vector<std::string> elems;

	const char* cstr = s.c_str();
	unsigned int strLength = (unsigned int)s.length();
	unsigned int start = 0;
	unsigned int end = 0;

	while (end <= strLength)
	{
		while (end <= strLength)
		{
			if (cstr[end] == delim)
				break;
			end++;
		}

		elems.push_back(s.substr(start, end - start));
		start = end + 1;
		end = start;
	}

	return elems;
}

float Utility::getMax(const vec2 & vec)
{
	float Max = vec[0];

	for (int i = 0; i < 3; i++)
		if (vec[i] > Max)
			Max = vec[i];

	return Max;
}

float Utility::getDistance(const vec2& point1, const vec2& point2)
{
	return sqrt(((point2.x - point1.x) * (point2.x - point1.x)) + ((point2.y - point1.y) * (point2.y - point1.y)));
}

float Utility::getRandomNumber(float min/* = 0.0f */, float max/* = 1.0f */)
{
	static std::mt19937 randomEngine((unsigned int)time(nullptr));

	std::uniform_real_distribution<float> randDir(min, max);

	return randDir(randomEngine);
}