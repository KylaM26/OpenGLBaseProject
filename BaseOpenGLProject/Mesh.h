#pragma once

#include <glew.h>

class Mesh {
protected:
	GLuint VAO, VBO, IBO;
	int vCount, iCount;
public:
	Mesh(): VAO(0), VBO(0), IBO(0), vCount(0), iCount(0) {}

	virtual void CreateMesh(GLfloat* vertecies, const int vertexCount) = 0;
	virtual void CreateMesh(GLfloat* vertecies, GLuint* indecies, const int vertexCount, const int indexCount) = 0;
	virtual void BindMesh(GLenum type) = 0;
	virtual void UnbindMesh() = 0;
	virtual ~Mesh() {}
};

class Triangle : public Mesh {
private:
	GLenum bufferType;
public:
	void CreateMesh(GLfloat* vertecies, const int vertexCount) override {
		vCount = vertexCount;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertecies[0]) * vertexCount, vertecies, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void CreateMesh(GLfloat* vertecies, GLuint* indecies, const int vertexCount, const int indexCount) override {
		vCount = vertexCount, iCount = indexCount;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &IBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertecies[0]) * vertexCount, vertecies, GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indecies[0]) * indexCount, indecies, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void BindMesh(GLenum type) override {
	
		glBindVertexArray(VAO);
		
		switch (bufferType) {
		case GL_ARRAY_BUFFER:
			glDrawArrays(GL_TRIANGLES, 0, 3);
			break;
		case GL_ELEMENT_ARRAY_BUFFER:
			glDrawElements(GL_TRIANGLES, iCount, GL_UNSIGNED_INT, 0);
			break;
		default:
			glDrawArrays(GL_TRIANGLES, 0, 3);
			break;
		}
	}

	void UnbindMesh() override {
		glBindVertexArray(0);
	}

	~Triangle() {
		if (VAO != 0) {
			glDeleteVertexArrays(1, &VAO);
			VAO = 0;
		}
	}
};