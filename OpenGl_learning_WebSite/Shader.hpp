#pragma once
#ifndef Shader_H
#define Shader_H


#include "glad\glad.h"
#include "string"
#include "iostream"
#include "fstream"
#include "sstream"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>     


class Shader {

public :
	unsigned int ID;

	Shader(const char* vertexpath,const char* fragmentPath);
private:
	unsigned int CompileShader(GLuint type, const std::string& source);
	std::string ReadFile(GLuint type, const char* FilePath);
public:

	void use();

	void setBool(const std::string& name, const bool value) const;
	void setInt(const std::string& name,const int value) const;
	void setFloat(const std::string& name, const float value) const;
	void setMat4(const std::string& name, const glm::mat4) const;
	void setVec3(const std::string& name, const glm::vec3) const;
	void setVec4(const std::string& name, const glm::vec4) const;

};
#endif

