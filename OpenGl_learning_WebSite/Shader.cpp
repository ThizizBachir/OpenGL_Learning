#include "Shader.hpp"

Shader::Shader(const char* vertexPath,const char* fragmentPath) {

	std::string vertexCode=ReadFile(GL_VERTEX_SHADER,vertexPath);
	std::string fragmentCode= ReadFile(GL_FRAGMENT_SHADER, fragmentPath);
	
	unsigned int vID = CompileShader(GL_VERTEX_SHADER, vertexCode);
	unsigned int fID = CompileShader(GL_FRAGMENT_SHADER, fragmentCode);

	ID = glCreateProgram();
	glAttachShader(ID, vID);
	glAttachShader(ID, fID);
	glLinkProgram(ID);

	int success;
	char infolog[512];

	// print linking errors if any
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infolog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infolog << std::endl;
	}

	// delete the shaders as they're linked into our program now and no longer necessary
	glDeleteShader(vID);
	glDeleteShader(fID);



};
unsigned int Shader::CompileShader(GLuint type, const std::string& source) {
	unsigned int id;
	id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, NULL);
	glCompileShader(id);

	int sucess;
	char infolog[512];

	glGetShaderiv(id, GL_COMPILE_STATUS, &sucess);
	if (!sucess) {
		glGetShaderInfoLog(id, 512, NULL, infolog);
		std::cout << "ERROR::SHADER::" << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << "::COMPILATION_FAILED\n" << infolog << std::endl;
	}
	return id;

};

std::string Shader::ReadFile(GLuint type, const char* FilePath) {
	//source code variables
	std::string Code;
	//input file variales
	std::ifstream ShaderFile;
	// make sure files can throw exceptions
	ShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		//open fail
		ShaderFile.open(FilePath);
		//Checking if file is opened or not
		/*if (!ShaderFile.is_open()) {
			std::cout << "ERROR::SHADER::" << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << "::FILE_NOT_OPENED" << std::endl;
		}
		else
		{
			std::cout << "SUCCESS::SHADER::" << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << "::FILE_OPENED" << std::endl;
		};*/
		std::stringstream ShaderStream;
		//read file buffer contents into streams
		ShaderStream << ShaderFile.rdbuf();
		//close the file handlers
		ShaderFile.close();
		//convert Stream to Strings
		Code = ShaderStream.str();
	}
	catch (std::fstream::failure e) {
		std::cout << "ERROR::SHADER::"<<(type == GL_VERTEX_SHADER ? "Vertex" : "Fragment")<<"::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	return Code;
};
void Shader::use() {
	glUseProgram(ID);
}
void Shader::setBool(const std::string& name, bool value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
