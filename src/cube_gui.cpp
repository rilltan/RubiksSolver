#include "cube.h"
#include <array>
#include <glad.h>
#include <iostream>
#include "cube_gui.h"
#include <fstream>
#include <sstream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

CubeRenderer::CubeRenderer(const char* vertexShaderPath, const char* fragmentShaderPath) {
	currentWidth = 1080;
	currentHeight = 1080;
	maxTextureSize = 2048;

	float squareVertices[] = {
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	}; // x, y, z, normal x, normal y, normal z

	std::string vertexShaderCode =
#include "vertex_shader.glsl"
	const char* vertexShaderSource = vertexShaderCode.c_str();
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	std::string fragmentShaderCode =
#include "fragment_shader.glsl"
	const char* fragmentShaderSource = fragmentShaderCode.c_str();
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
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, maxTextureSize, maxTextureSize, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
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
float positions[] = {
	-0.25f, 0.5f, 0.0f,
	-0.25f, -0.5f, 0.0f,
	-0.75f, 0.0f, 0.0f,
	0.25f, 0.0f, 0.0f,
	-0.25f, 0.0f, 0.0f,
	0.75f, 0.0f, 0.0f
};
float colours[] = {
	1.0f,1.0f,1.0f,
	1.0f,1.0f,0.0f,
	1.0f,0.5f,0.0f,
	1.0f,0.0f,0.0f,
	0.0f,1.0f,0.0f,
	0.0f,0.0f,1.0f
};
int indices[] = { 0,1,2,7,8,3,6,5,4 };
void CubeRenderer::Draw2D(Cube& cube) {
	glUseProgram(shaderProgram);
	glBindVertexArray(vao);
	glBindFramebuffer(GL_FRAMEBUFFER, tex_fbo);
	float aspectRatio = 4.0f / 3.0f;
	int size = fmin(currentWidth, currentHeight*aspectRatio);
	glViewport((currentWidth - size) / 2, (currentHeight - size) / 2, size, size);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);



	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 9; j++) {
			glm::mat4 pvm = glm::translate(glm::mat4(1.0f), glm::vec3(positions[i * 3], positions[i * 3 + 1], positions[i * 3 + 2]));
			pvm = glm::scale(pvm, glm::vec3(0.25f));
			pvm = glm::translate(pvm, glm::vec3(-2.0f/3.0f + (float)(j%3)*2.0f/3.0f, 2.0f / 3.0f - (float)(j / 3) * 2.0f / 3.0f,0.0f));
			pvm = glm::scale(pvm, glm::vec3(0.3f));
			glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "pvm"), 1, GL_FALSE, glm::value_ptr(pvm));
			if (indices[j] == 8) {
				glUniform3f(glGetUniformLocation(shaderProgram, "objectColor"), colours[i * 3], colours[i * 3 + 1], colours[i * 3 + 2]);
			}
			else {
				int index = getSticker(cube, (Face)i, indices[j]);// cube[i] >> ((7 - indices[j]) * 4) & 0xF;
				if (index >= 0 && index <= 5) {
					glUniform3f(glGetUniformLocation(shaderProgram, "objectColor"), colours[index * 3], colours[index * 3 + 1], colours[index * 3 + 2]);
				}
				else {
					throw std::runtime_error("Invalid cube");
				}
			}
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void CubeRenderer::Draw3D() {

}
unsigned int CubeRenderer::getTextureID() const {
	return tex;
}
unsigned int CubeRenderer::getMaxTextureSize() const {
	return maxTextureSize;
}
void CubeRenderer::Resize(int width, int height) {
	currentWidth = width;
	currentHeight = height;
}