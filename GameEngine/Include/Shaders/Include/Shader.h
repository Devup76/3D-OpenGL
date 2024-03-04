#pragma once
#include <iostream>
#include <glm/ext/matrix_float4x4.hpp>

class Shader
{

public:

	Shader(const std::string vertexFilePath, const std::string fragmentFilePath);
	~Shader();

	std::string readFile(const std::string& filename);

	std::string vertexShaderSource;
	std::string fragmentShaderSource;

	unsigned int ID;

	unsigned int use();

	unsigned int getID();

	void setMat4(const std::string& name, const glm::mat4& mat) const;

};

