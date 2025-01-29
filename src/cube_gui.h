#pragma once
#include "cube.h"

class CubeRenderer {
	unsigned int vao;
	unsigned int tex_fbo;
	unsigned int tex;
	unsigned int vertexShader;
	unsigned int fragmentShader;
	unsigned int shaderProgram;
	int currentWidth;
	int currentHeight;
	int maxTextureSize;

public:
	CubeRenderer(const char* vertexShaderPath, const char* fragmentShaderPath);
	void Draw2D(Cube& cube);
	void Draw3D();
	unsigned int getTextureID() const;
	unsigned int getMaxTextureSize() const;
	void Resize(int width, int height);
};