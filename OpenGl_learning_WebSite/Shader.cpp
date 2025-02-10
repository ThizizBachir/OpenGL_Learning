#include "Shader.hpp"

unsigned int TextureFromFile(const char* filename) {
	unsigned int id;
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//texture loading
	int width, height, nrchannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(filename, &width, &height, &nrchannels, 0);

	if (data) {

		GLenum format;
		if (nrchannels == 1)
			format = GL_RED;
		else if (nrchannels == 3)
			format = GL_RGB;
		else if (nrchannels == 4)
			format = GL_RGBA;
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "ERROR::Texture::Failed to load texture" << "\n";
	}

	stbi_image_free(data);

	return id;
}


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


GLint Shader::getUniformLocation(const std::string &name) const 
{
	GLint location = glGetUniformLocation(ID, name.c_str());
	if (location == -1)
	{
		std::cout << "ERROR::SHADER::PROGRAM::cannot locate uniform named: " << name << std::endl;
	}
	return location;
}
void Shader::setBool(const std::string& name, bool value) const {
	glUniform1i(getUniformLocation(name), (int)value);
}

void Shader::setInt(const std::string& name, int value) const {

	glUniform1i(getUniformLocation(name), value);
}

void Shader::setFloat(const std::string& name, float value) const {
	glUniform1f(getUniformLocation(name), value);
}

void Shader::setVec3(const std::string& name, glm::vec3 value) const {
	glUniform3fv(getUniformLocation(name),1,glm::value_ptr(value));
}

void Shader::setVec4(const std::string& name, glm::vec4 value) const {
	glUniform3fv(getUniformLocation(name), 1, glm::value_ptr(value));
}

void Shader::setMat4(const std::string& name, glm::mat4 value) const {
	glUniformMatrix4fv(getUniformLocation(name), 1,GL_FALSE, glm::value_ptr(value));
}