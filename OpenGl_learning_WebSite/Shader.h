#pragma once
#ifndef Shader_H
#define Shader_H


#include "glad\glad.h"
#include "string"
#include "iostream"
#include "fstream"
#include "sstream"


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

};
#endif

