#define ToRadians(x) (float)(((x) * 3.1415926536f / 180.0f))
#define ToDegree(x) (float)(((x) * 180.0f / 3.1415926536f))
#define ZERO_MEM(a) memset(a,0,sizeof(a))
#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))
#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))
#define SAFE_DELETE(p) if(p) {delete p; p = NULL;}
#define INVALID_VALUE 0xFFFFFFFF

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