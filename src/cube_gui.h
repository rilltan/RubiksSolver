#pragma once

class CubeRenderer {
	unsigned int vao;
	unsigned int tex_fbo;
	unsigned int tex;
	unsigned int vertexShader;
	unsigned int fragmentShader;
	unsigned int shaderProgram;
	unsigned int currentSize;

public:
	CubeRenderer();
	void Draw();
	unsigned int getTextureID() const;
};