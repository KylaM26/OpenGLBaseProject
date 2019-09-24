#pragma once

#include "Mesh.h"
#include "Shader.h"

class Game {
private:

public:
	Game() {}
	Triangle triangle;
	Shader shader;
	V3 playerPos = V3(0, 0, 0);
	float scale;
	M4x4 trans, rot, size, mat, perspective;
};