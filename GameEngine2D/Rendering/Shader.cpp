#include "Shader.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <glew\glew.h>
#include <cstdlib>
#include <cstring>
#include <sstream>

#include "..\Core\Utility.h"

//--------------------------------------------------------------------------------
// Variable Initializations
//--------------------------------------------------------------------------------
std::map<std::string, ShaderData*> Shader::s_resourceMap;
int ShaderData::s_supportedOpenGLLevel = 0;

//--------------------------------------------------------------------------------
// Forward declarations
//--------------------------------------------------------------------------------
static void checkShaderError(int shader, int flag, bool isProgram, const std::string& errorMessage);
static std::vector<UniformStruct> findUniformStructs(const std::string& shaderText);
static std::string findUniformStructName(const std::string& structStartToOpeningBrace);
static std::vector<TypedData> findUniformStructComponents(const std::string& openingBraceToClosingBrace);
static std::string loadShader(const std::string& fileName);
static void string_ReplaceKey(std::string* replaceIn, size_t replacementStart, const std::string& replacementValue, const std::string& endKey, int startLocation);
static void string_FindAndReplace(std::string* replaceIn, const std::string& replacementKey, const std::string& replacementValue, const std::string& endKey = "", int startLocation = 0);
static void string_ReplaceAll(std::string* replaceIn, const std::string& replacementKey, const std::string& replacementValue, const std::string& endKey = "", int startLocation = 0, bool insertCounter = false);

//--------------------------------------------------------------------------------
// Constructors/Destructors
//--------------------------------------------------------------------------------
ShaderData::ShaderData(const std::string& fileName)
{
	m_program = glCreateProgram();

	if (m_program == 0)
	{
		fprintf(stderr, "Error creating shader program\n");
		assert(false);
	}

	if (s_supportedOpenGLLevel == 0)
	{
		int majorVersion;
		int minorVersion;

		glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
		glGetIntegerv(GL_MINOR_VERSION, &minorVersion);

		s_supportedOpenGLLevel = majorVersion * 100 + minorVersion * 10;
	}

	std::string vertexShaderText = loadShader(fileName + ".vs");
	std::string fragmentShaderText = loadShader(fileName + ".fs");

	if (s_supportedOpenGLLevel >= 320)
	{
		convertVertexShaderToGLSL150(&vertexShaderText);
		convertFragmentShaderToGLSL150(&fragmentShaderText);
	}

	addVertexShader(vertexShaderText);
	addFragmentShader(fragmentShaderText);

	std::string attributeKeyword = s_supportedOpenGLLevel  < 320 ? "attribute" : "in";
	addAllAttributes(vertexShaderText, attributeKeyword);

	compileShader();

	addShaderUniforms(vertexShaderText);
	addShaderUniforms(fragmentShaderText);
}

ShaderData::~ShaderData()
{
	for (std::vector<int>::iterator it = m_shaders.begin(); it != m_shaders.end(); ++it)
	{
		glDetachShader(m_program, *it);
		glDeleteShader(*it);
	}
	glDeleteProgram(m_program);
}

Shader::Shader(const std::string& fileName)
{
	m_fileName = fileName;

	std::map<std::string, ShaderData*>::const_iterator it = s_resourceMap.find(fileName);
	if (it != s_resourceMap.end())
	{
		m_shaderData = it->second;
		m_shaderData->addReference();
	}
	else
	{
		m_shaderData = new ShaderData(fileName);
		s_resourceMap.insert(std::pair<std::string, ShaderData*>(fileName, m_shaderData));
	}
}

Shader::Shader(const Shader& other) :
m_shaderData(other.m_shaderData),
m_fileName(other.m_fileName)
{
	m_shaderData->addReference();
}

Shader::~Shader()
{
	if (m_shaderData && m_shaderData->removeReference())
	{
		if (m_fileName.length() > 0)
			s_resourceMap.erase(m_fileName);

		delete m_shaderData;
	}
}

//--------------------------------------------------------------------------------
// Member Function Implementation
//--------------------------------------------------------------------------------
void Shader::bind() const
{
	glUseProgram(m_shaderData->getProgram());
}

void Shader::updateUniforms(const Transform & transform, const Texture & texture, const Renderer & renderer, const Camera & camera) const
{
	//for (unsigned int i = 0; i < m_shaderData->getUniformNames().size(); i++)
	//{
	//	std::string uniformName = m_shaderData->getUniformNames()[i];
	//	std::string uniformType = m_shaderData->getUniformTypes()[i];

	//	if (uniformType == "sampler2D")
	//	{
	//		int samplerSlot = renderer.getSamplerSlot(uniformName);


	//		material.getTexture(uniformName).bind(samplerSlot);
	//		setUniformi(uniformName, samplerSlot);
	//	}
	//	else if (uniformName.substr(0, 2) == "C_")
	//	{
	//		if (uniformName == "C_eyePos")
	//			setUniformVec2(uniformName, camera.getTransform());
	//		else
	//			throw "Invalid Camera Uniform: " + uniformName;
	//	}
	//}
}

void Shader::setUniformi(const std::string& uniformName, int value) const
{
	glUniform1i(m_shaderData->getUniformMap().at(uniformName), value);
}

void Shader::setUniformf(const std::string& uniformName, float value) const
{
	glUniform1f(m_shaderData->getUniformMap().at(uniformName), value);
}

void Shader::setUniformVec2(const std::string& uniformName, const vec2& value) const
{
	glUniform2f(m_shaderData->getUniformMap().at(uniformName), value.x, value.y);
}

static void replaceShaderVersionWith(std::string* shaderText, const std::string& newVersion)
{
	static const std::string VERSION_KEY = "#version ";

	size_t versionLocation = shaderText->find(VERSION_KEY);
	size_t versionNumberStart = versionLocation + VERSION_KEY.length();
	size_t versionNumberEnd = shaderText->find("\n", versionNumberStart) - versionNumberStart;
	shaderText->replace(versionNumberStart, versionNumberEnd, newVersion);
}

void ShaderData::convertVertexShaderToGLSL150(std::string* shaderText)
{
	replaceShaderVersionWith(shaderText, "150");

	string_ReplaceAll(shaderText, "varying", "out");
	string_ReplaceAll(shaderText, "attribute", "in");
}

void ShaderData::convertFragmentShaderToGLSL150(std::string* shaderText)
{
	replaceShaderVersionWith(shaderText, "150");

	string_ReplaceAll(shaderText, "varying", "in");
	string_ReplaceAll(shaderText, "texture2D", "texture");
	string_ReplaceAll(shaderText, "gl_FragColor", "OUT_Fragment_Color");

	std::string newFragout = "out vec4 OUT_Fragment_Color;\n";
	size_t start = shaderText->find("\n");
	shaderText->replace(start + 1, 0, newFragout);
}

void ShaderData::addVertexShader(const std::string& text)
{
	addProgram(text, GL_VERTEX_SHADER);
}

void ShaderData::addGeometryShader(const std::string& text)
{
	addProgram(text, GL_GEOMETRY_SHADER);
}

void ShaderData::addFragmentShader(const std::string& text)
{
	addProgram(text, GL_FRAGMENT_SHADER);
}

void ShaderData::addProgram(const std::string& text, int type)
{
	int shader = glCreateShader(type);

	if (shader == 0)
	{
		fprintf(stderr, "Error creating shader type %d\n", type);
		assert(false);
	}

	const GLchar* p[1];
	p[0] = text.c_str();
	GLint lengths[1];
	lengths[0] = text.length();

	glShaderSource(shader, 1, p, lengths);
	glCompileShader(shader);

	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar InfoLog[1024];

		glGetShaderInfoLog(shader, 1024, NULL, InfoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", shader, InfoLog);

		assert(false);
	}

	glAttachShader(m_program, shader);
	m_shaders.push_back(shader);
}

void ShaderData::addAllAttributes(const std::string& vertexShaderText, const std::string& attributeKeyword)
{
	int currentAttribLocation = 0;
	size_t attributeLocation = vertexShaderText.find(attributeKeyword);
	while (attributeLocation != std::string::npos)
	{
		bool isCommented = false;
		size_t lastLineEnd = vertexShaderText.rfind(";", attributeLocation);

		if (lastLineEnd != std::string::npos)
		{
			std::string potentialCommentSection = vertexShaderText.substr(lastLineEnd, attributeLocation - lastLineEnd);
			isCommented = potentialCommentSection.find("//") != std::string::npos;
		}

		if (!isCommented)
		{
			size_t begin = attributeLocation + attributeKeyword.length();
			size_t end = vertexShaderText.find(";", begin);

			std::string attributeLine = vertexShaderText.substr(begin + 1, end - begin - 1);

			begin = attributeLine.find(" ");
			std::string attributeName = attributeLine.substr(begin + 1);

			glBindAttribLocation(m_program, currentAttribLocation, attributeName.c_str());//SetAttribLocation(attributeName, currentAttribLocation);
			currentAttribLocation++;
		}
		attributeLocation = vertexShaderText.find(attributeKeyword, attributeLocation + attributeKeyword.length());
	}
}

void ShaderData::addShaderUniforms(const std::string& shaderText)
{
	static const std::string UNIFORM_KEY = "uniform";

	std::vector<UniformStruct> structs = findUniformStructs(shaderText);

	size_t uniformLocation = shaderText.find(UNIFORM_KEY);
	while (uniformLocation != std::string::npos)
	{
		bool isCommented = false;
		size_t lastLineEnd = shaderText.rfind(";", uniformLocation);

		if (lastLineEnd != std::string::npos)
		{
			std::string potentialCommentSection = shaderText.substr(lastLineEnd, uniformLocation - lastLineEnd);
			isCommented = potentialCommentSection.find("//") != std::string::npos;
		}

		if (!isCommented)
		{
			size_t begin = uniformLocation + UNIFORM_KEY.length();
			size_t end = shaderText.find(";", begin);

			std::string uniformLine = shaderText.substr(begin + 1, end - begin - 1);

			begin = uniformLine.find(" ");
			std::string uniformName = uniformLine.substr(begin + 1);
			std::string uniformType = uniformLine.substr(0, begin);

			m_uniformNames.push_back(uniformName);
			m_uniformTypes.push_back(uniformType);
			addUniform(uniformName, uniformType, structs);
		}
		uniformLocation = shaderText.find(UNIFORM_KEY, uniformLocation + UNIFORM_KEY.length());
	}
}

void ShaderData::addUniform(const std::string& uniformName, const std::string& uniformType, const std::vector<UniformStruct>& structs)
{
	bool addThis = true;

	for (unsigned int i = 0; i < structs.size(); i++)
	{
		if (structs[i].getName().compare(uniformType) == 0)
		{
			addThis = false;
			for (unsigned int j = 0; j < structs[i].getMemberNames().size(); j++)
			{
				addUniform(uniformName + "." + structs[i].getMemberNames()[j].getName(), structs[i].getMemberNames()[j].getType(), structs);
			}
		}
	}

	if (!addThis)
		return;

	unsigned int location = glGetUniformLocation(m_program, uniformName.c_str());

	assert(location != INVALID_VALUE);

	m_uniformMap.insert(std::pair<std::string, unsigned int>(uniformName, location));
}

void ShaderData::compileShader() const
{
	glLinkProgram(m_program);
	checkShaderError(m_program, GL_LINK_STATUS, true, "Error linking shader program");

	glValidateProgram(m_program);
	checkShaderError(m_program, GL_VALIDATE_STATUS, true, "Invalid shader program");
}

//--------------------------------------------------------------------------------
// Static Function Implementations
//--------------------------------------------------------------------------------
static void checkShaderError(int shader, int flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (!success)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		fprintf(stderr, "%s: '%s'\n", errorMessage.c_str(), error);
	}
}

static std::string loadShader(const std::string& fileName)
{
	std::ifstream file;
	file.open(("Assets/Shaders/" + fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);

			if (line.find("#include") == std::string::npos)
				output.append(line + "\n");
			else
			{
				std::string includeFileName = Utility::split(line, ' ')[1];
				includeFileName = includeFileName.substr(1, includeFileName.length() - 2);

				std::string toAppend = loadShader(includeFileName);
				output.append(toAppend + "\n");
			}
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}

	return output;
};

static std::vector<TypedData> findUniformStructComponents(const std::string& openingBraceToClosingBrace)
{
	static const char charsToIgnore[] = { ' ', '\n', '\t', '{' };
	static const size_t UNSIGNED_NEG_ONE = (size_t)-1;

	std::vector<TypedData> result;
	std::vector<std::string> structLines = Utility::split(openingBraceToClosingBrace, ';');

	for (unsigned int i = 0; i < structLines.size(); i++)
	{
		size_t nameBegin = UNSIGNED_NEG_ONE;
		size_t nameEnd = UNSIGNED_NEG_ONE;

		for (unsigned int j = 0; j < structLines[i].length(); j++)
		{
			bool isIgnoreableCharacter = false;

			for (unsigned int k = 0; k < sizeof(charsToIgnore) / sizeof(char); k++)
			{
				if (structLines[i][j] == charsToIgnore[k])
				{
					isIgnoreableCharacter = true;
					break;
				}
			}

			if (nameBegin == UNSIGNED_NEG_ONE && isIgnoreableCharacter == false)
			{
				nameBegin = j;
			}
			else if (nameBegin != UNSIGNED_NEG_ONE && isIgnoreableCharacter)
			{
				nameEnd = j;
				break;
			}
		}

		if (nameBegin == UNSIGNED_NEG_ONE || nameEnd == UNSIGNED_NEG_ONE)
			continue;

		TypedData newData(
			structLines[i].substr(nameEnd + 1),
			structLines[i].substr(nameBegin, nameEnd - nameBegin));

		result.push_back(newData);
	}

	return result;
}

static std::string findUniformStructName(const std::string& structStartToOpeningBrace)
{
	return Utility::split(Utility::split(structStartToOpeningBrace, ' ')[0], '\n')[0];
}

static std::vector<UniformStruct> findUniformStructs(const std::string& shaderText)
{
	static const std::string STRUCT_KEY = "struct";
	std::vector<UniformStruct> result;

	size_t structLocation = shaderText.find(STRUCT_KEY);
	while (structLocation != std::string::npos)
	{
		structLocation += STRUCT_KEY.length() + 1; //Ignore the struct keyword and space

		size_t braceOpening = shaderText.find("{", structLocation);
		size_t braceClosing = shaderText.find("}", braceOpening);

		UniformStruct newStruct(
			findUniformStructName(shaderText.substr(structLocation, braceOpening - structLocation)),
			findUniformStructComponents(shaderText.substr(braceOpening, braceClosing - braceOpening)));

		result.push_back(newStruct);
		structLocation = shaderText.find(STRUCT_KEY, structLocation);
	}

	return result;
}

static void string_ReplaceKey(std::string* replaceIn, size_t replacementStart, const std::string& replacementValue, const std::string& endKey, int startLocation)
{
	size_t replacementEnd = replaceIn->find(endKey, startLocation) - replacementStart;

	replaceIn->replace(replacementStart, replacementEnd, replacementValue);
}

static void string_FindAndReplace(std::string* replaceIn, const std::string& replacementKey, const std::string& replacementValue, const std::string& endKey, int startLocation)
{
	size_t replacementStart = replaceIn->find(replacementKey, startLocation);
	string_ReplaceKey(replaceIn, replaceIn->find(replacementKey, startLocation), replacementValue, endKey, replacementStart + replacementKey.length());
}

static void string_ReplaceAll(std::string* replaceIn, const std::string& replacementKey, const std::string& replacementValue, const std::string& endKey, int startLocation, bool insertCounter)
{
	static std::string COUNTER_KEY = "%d";

	int numReplaced = 0;
	size_t replacementLocation = replaceIn->find(replacementKey, startLocation);

	size_t counterLocation = 0;
	std::string newReplacementStart = "";
	std::string newReplacementEnd = "";

	if (insertCounter)
	{
		counterLocation = replacementValue.find(COUNTER_KEY);
		newReplacementStart = replacementValue.substr(0, counterLocation);
		newReplacementEnd = replacementValue.substr(counterLocation + COUNTER_KEY.length());
	}

	while (replacementLocation != std::string::npos)
	{
		if (insertCounter)
		{
			std::stringstream newReplacement;

			newReplacement << newReplacementStart << numReplaced << newReplacementEnd;

			replaceIn->replace(replacementLocation, replacementKey.length(), newReplacement.str());
		}
		else
			string_ReplaceKey(replaceIn, replacementLocation, replacementValue, endKey, replacementLocation + replacementKey.length());

		replacementLocation = replaceIn->find(replacementKey, replacementLocation + replacementValue.length());
		numReplaced++;
	}
}
