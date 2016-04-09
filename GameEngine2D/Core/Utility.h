#include <vector>
#include <string>
#include <glm\glm.hpp>
using namespace glm;

namespace Utility
{
	void sleep(int milliseconds);
	std::vector<std::string> split(const std::string& s, char delim);
	float getDistance(const vec2& point1, const vec2& point2);
	float getMax(const vec2& vec);
	float getRandomNumber(float min = 0.0f, float max = 1.0f);
}