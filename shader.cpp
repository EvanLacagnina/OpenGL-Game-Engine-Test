#include "shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
	std::string vertexCode; // Strings to contain vertex and frag shader code
	std::string fragmentCode;

	std::ifstream vShaderFile; // objects containing vert and frag shader files
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit); // Make sure these will cause an exception w/ exception mask
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit); // Make sure these will cause an exception w/ exception mask

	try {
		// Open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream; // Creating a stringstream - allows us to read a stringas is it were a stream (like cin)

		// Read file's buffer contents into streams (input)
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		// Close file objects/handlers
		vShaderFile.close();
		fShaderFile.close();

		// Convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();

	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR: shader file not read" << std::endl;
	}
	const char* vShaderCode = vertexCode.c_str(); // Casting to a const char*
	const char* fShaderCode = fragmentCode.c_str();


	// COMPILING SHADERS

	unsigned int vertex, fragment; // Vertex & frag shader IDs
	int success;
	char infoLog[512];

	vertex = glCreateShader(GL_VERTEX_SHADER); // Creating vertex shader
	glShaderSource(vertex, 1, &vShaderCode, NULL); // Sets source code of shader object
	glCompileShader(vertex); // Bet you can't guess what this one does!
	
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success); // Returns requested parameter (compile status) as 'success'
	if (!success) {
		glGetShaderInfoLog(vertex, 512, NULL, infoLog); // Sets 'infoLog' to the infolog
		std::cout << "ERROR: vertex shader compilation failed\n" << infoLog << std::endl;
	}
	


	// Fragment
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	// Print compilation errors if any
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR: fragment shader compilation failed\n" << infoLog << std::endl;
	}


	// LINKING SHADERS
	
	ID = glCreateProgram(); // Set instance variable 'ID' to the returned ID from the created program
	glAttachShader(ID, vertex); // Attaches vertex shader
	glAttachShader(ID, fragment); // Attaches fragment shader
	glLinkProgram(ID); // Links the program

	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR: shader program linking failed\n" << infoLog << std::endl;
	}

	// Delete shaders
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}


void Shader::use() {
	glUseProgram(ID);
}


void Shader::setBool(const std::string& name, bool value) const { // We can input uniforms into our shader
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void Shader::setInt(const std::string& name, int value) const { // We can input uniforms into our shader
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setFloat(const std::string& name, float value) const { // We can input uniforms into our shader
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setMat4(const std::string& name, glm::mat4 value) const { // We can input uniforms into our shader
	glUniformMatrix4fv(glGetUniformLocation(this->ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
void Shader::setVec3(const std::string& name, glm::vec3 value) const { // We can input uniforms into our shader
	glUniform3fv(glGetUniformLocation(this->ID, name.c_str()), 1, glm::value_ptr(value));
}
