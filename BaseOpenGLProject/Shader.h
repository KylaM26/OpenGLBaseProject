#pragma once

#include <glew.h>
#include <iostream>
#include <string>
#include <fstream>
#include "Math/Vector3.h"
#include "Math/MatrixMath.h"

using namespace IncredibleMath;

class Shader {
private:
	GLuint program;
	GLuint uniformPosition, uniformScale, uniformMat4x4;

	void LoadShaderFromFile(const char* path, std::string& code) {
		std::ifstream file;

		file.open(path, std::ios::in);
		if (file.is_open()) {
			std::string lineOfCode = "";
			while (!file.eof()) {
				std::getline(file, lineOfCode);
				code.append(lineOfCode + '\n');
			}
			file.close();
		} else {
		//	std::cout << "Failed to open file: " << path << std::endl;
		}
	}

public:
	 void CreateProgram() {
		program = glCreateProgram();
	};

	GLuint CreateShader(const char* path, GLenum type) {
		GLuint shader = glCreateShader(type);

		if (!shader) {
			std::cout << "Failed to create shader " << path << std::endl;
			return 0;
		}

		std::string code = "";
		LoadShaderFromFile(path, code);
		
		GLint length = strlen(code.c_str());
		const char* codeCStr = code.c_str();

		glShaderSource(shader, 1, &codeCStr, &length);
		glCompileShader(shader);

		int success = 0;
		GLchar buf[1024];

		glGetShaderiv(program, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(program, sizeof(buf), 0, buf);
			std::cout << buf << std::endl;
		}

		return shader;
	}

	void AddShaderToProgram(GLuint& shader) {
		glAttachShader(program, shader);
	}

	void CompileProgram() {
		glLinkProgram(program);

		int success = 0;
		GLchar buf[1024];

		glGetProgramiv(program, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(program, sizeof(buf), 0, buf);
			std::cout << buf << std::endl;
		}

		uniformPosition = glGetUniformLocation(program, "uPosition");
		uniformScale = glGetUniformLocation(program, "uScale");
		uniformMat4x4 = glGetUniformLocation(program, "uMat4x4");
	}

	GLuint& GetProgram() { return program; }
public:
	void SetUniformPosition(V3& position) {
		glUniform4f(uniformPosition, position.x, position.y, position.z, 1.f);
	}

	void SetUniformScale(float scale) {
		glUniform1f(uniformScale, scale);
	}
	
	void SetUniformMat4x4(IncredibleMath::M4x4& m) {
		glUniformMatrix4fv(uniformMat4x4, 1, GL_TRUE, &m[0][0]);
	}

	GLuint& GetUniformMat4x4() { return uniformMat4x4;  }
};