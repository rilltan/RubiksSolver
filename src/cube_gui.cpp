#include "cube.h"
#include <array>
#include <glad.h>
#include <iostream>
#include "cube_gui.h"

//void generate2DVertexData(std::array<float, 3 * 9>& vertices, Cube& cube) {
//	vertices[0] = -1.0f;
//	vertices[1] = -1.0f;
//	vertices[2] = 0.0f;
//
//	vertices[1*9 + 0] = -1.0f;
//	vertices[1*9 + 1] = 1.0f;
//	vertices[1*9 + 2] = 0.0f;
//
//	vertices[2*9 + 0] = 1.0f;
//	vertices[2*9 + 1] = -1.0f;
//	vertices[2*9 + 2] = 0.0f;
//
//	for (int i = 0; i < 3; i++) {
//		vertices[i * 9 + 3] = 0.0f;
//		vertices[i * 9 + 4] = 0.0f;
//		vertices[i * 9 + 5] = 1.0f;
//
//		vertices[i * 9 + 6] = 1.0f;
//		vertices[i * 9 + 7] = 1.0f;
//		vertices[i * 9 + 8] = 1.0f;
//	}
//}

CubeRenderer::CubeRenderer() {
	currentSize = 1080;

	float squareVertices[] = {
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f
	}; // x, y, z, normal x, normal y, normal z

	// TEMPORARY setting up shaders
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x/2, aPos.y/2, aPos.z, 1.0);\n"
		"}\0";
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\0";
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// setting up vao
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// setting up vbo
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(squareVertices), squareVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// setting up output texture
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, currentSize, currentSize, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	// setting up output framebuffer
	glGenFramebuffers(1, &tex_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, tex_fbo);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	std::cout << "CubeRenderer initialized" << std::endl;
}
void CubeRenderer::Draw() {
	glUseProgram(shaderProgram);
	glBindVertexArray(vao);
	glBindFramebuffer(GL_FRAMEBUFFER, tex_fbo);
	glViewport(0, 0, currentSize, currentSize);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
unsigned int CubeRenderer::getTextureID() const {
	return tex;
}