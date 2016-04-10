#include "Utility.h"
#include <SDL2\SDL_timer.h>
#include <random>
#include <ctime>
#include <fstream>

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

template<typename T> 
inline T Utility::clamp(const T &a, const T &min, const T &max)
{
	if (a < min) return min;
	else if (a > max) return max;
	else return a;
}

bool Utility::readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer)
{
	std::ifstream file(filePath, std::ios::binary);
	if (file.fail())
	{
		perror(filePath.c_str());
		return false;
	}

	//To figure out the size of a file we want to use a method to find the 
	//end of the file. this will tell us how many bytes the file is

	//Seek to the end of the file
	file.seekg(0, std::ios::end);

	//Get the file size
	int fileSize = file.tellg();
	file.seekg(0, std::ios::beg);

	//at the top of every file is a file header it is information about a file, like
	//when it was last edited for example. You will not normally see this information
	//so if we don't want to read those bytes we can stop that from happening
	//This is not necessary however it is better safe than sorry.

	fileSize -= file.tellg();

	//resize the buffer to the size of the file we are reading
	buffer.resize(fileSize);

	//&(buffer[0]) is like saying what is the address of the first element of the buffer array, 
	//that is where we want to start reading from.
	file.read((char *)&(buffer[0]), fileSize);
	file.close();

	//The file was successfully opened and stored in the buffer
	return true;

}

bool Utility::readFileToBuffer(std::string filePath, std::string & buffer)
{
	std::ifstream file(filePath, std::ios::binary);
	if (file.fail())
	{
		perror(filePath.c_str());
		return false;
	}

	//To figure out the size of a file we want to use a method to find the 
	//end of the file. this will tell us how many bytes the file is

	//Seek to the end of the file
	file.seekg(0, std::ios::end);

	//Get the file size
	int fileSize = file.tellg();
	file.seekg(0, std::ios::beg);

	//at the top of every file is a file header it is information about a file, like
	//when it was last edited for example. You will not normally see this information
	//so if we don't want to read those bytes we can stop that from happening
	//This is not necessary however it is better safe than sorry.

	fileSize -= file.tellg();

	//resize the buffer to the size of the file we are reading
	buffer.resize(fileSize);

	//&(buffer[0]) is like saying what is the address of the first element of the buffer array, 
	//that is where we want to start reading from.
	file.read((char *)&(buffer[0]), fileSize);
	file.close();

	//The file was successfully opened and stored in the buffer
	return true;
}