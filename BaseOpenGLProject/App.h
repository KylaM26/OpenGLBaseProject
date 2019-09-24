#pragma once

#include <glew.h>
#include "Game.h"
#include "Platform.h"
#include "Pipeline.h"
#include "Math/VectorMath.h"

struct Camera {
	Vector3 pos, target, up;
	Matrix4x4 view, rot;

	void InitializeCameraTransform() {
		pos = Vector3(1.0f, 1.0f, -3.0f);
		target = Vector3(0.45f, 0.0f, 1.0f);
		up = Vector3(0.0f, 1.0f, 0.0f);

		Vector3 normalTarget = Normalize(target);
		Vector3 normalUp = Normalize(up);
		Vector3 right = Cross(target, up);
		right = Normalize(right);

		rot[0][0] = 0.0f;		rot[0][1] = 0.0f;	rot[0][2] = 0.0f;
		rot[1][0] = right.x;	rot[1][1] = up.y;   rot[1][2] = target.z;
		rot[2][0] = 0.0f;		rot[2][1] = 0.0f;	rot[2][2] = 0.0f;
		rot[3][0] = 0.0f;		rot[3][1] = 0.0f;	rot[2][3] = 0.0f;

		view[0][0] = normalUp.x;		view[0][1] = normalUp.y;		view[0][2] = normalUp.z;		view[0][3] = 0.0f;
		view[1][0] = right.x;			view[1][1] = right.y;			view[1][2] = right.z;			view[1][3] = 0.0f;
		view[2][0] = normalTarget.x;	view[2][1] = normalTarget.y;	view[2][2] = normalTarget.z;	view[2][3] = 0.0f;
		view[3][0] = 0.0f;				view[3][1] = 0.0f;				view[3][2] = 0.0f;				view[3][3] = 1.0f;

	}

};

Camera cam;

class App {
private:
	Platform* platform;
	Game game;

	void HandleKeys() {
		if (platform->keypad[KEY_A]) {
		//	game.game.scale -= 1.f * platform->clock->deltaTime;
		}
		
		if (platform->keypad[KEY_D]) {
	//		game.game.scale += 1.f * platform->clock->deltaTime;
		}
	}

	void InitializeGlew() {
		if (glewInit() != GLEW_OK) {
			ERROR_BOX("Failed to Initialize glew");
			return;
		}
	}

public:
	bool quit;
	App(Platform* p) { 
		platform = p; 
		quit = platform->quit;
		game = Game();
	}

	void Initialize() {
		InitializeGlew();

		const int VERTEX_COUNT = 9;
		GLfloat vertecies[VERTEX_COUNT] = {
			-1.0f, -1.0f, 0.0f,
			 0.0f, 1.0f, 0.0f,
			 1.0f, -1.0f, 0.0f
		};

		const int INDEX_COUNT = 12;
		GLuint indicies[INDEX_COUNT] = {
			0, 3, 1,
			1, 3, 2,
			2, 3, 0,
			0, 1, 2 
		};

		game.triangle.CreateMesh(vertecies, indicies, VERTEX_COUNT, INDEX_COUNT);

		GLuint vertexShader = game.shader.CreateShader("Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		GLuint fragmentShader = game.shader.CreateShader("Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);

		game.shader.CreateProgram();

		game.shader.AddShaderToProgram(vertexShader);
		game.shader.AddShaderToProgram(fragmentShader);

		game.shader.CompileProgram();
		game.scale = 1.f;
		game.playerPos = V3(0, -0, 0);


		const float ar = platform->GetWindowWidth() / platform->GetWindowHeight();
		const float zNear = 1.0f;
		const float zFar = 1000.f;
		const float zRange = zNear - zFar;

		const float tanHalfFOV = tanf(DEG_TO_RAD(130.0f/ 2.0));

		game.perspective[0][0] = 1.0f / (tanHalfFOV * ar);
		game.perspective[0][1] = 0.0f;
		game.perspective[0][2] = 0.0f;
		game.perspective[0][3] = 0.0f;

		game.perspective[1][0] = 0.0f;
		game.perspective[1][1] = 1.0f / tanHalfFOV;
		game.perspective[1][2] = 0.0f;
		game.perspective[1][3] = 0.0f;

		game.perspective[2][0] = 0.0f;
		game.perspective[2][1] = 0.0f;
		game.perspective[2][2] = (-zNear - zFar) / zRange;
		game.perspective[2][3] = 2.0f * zFar * zNear / zRange;

		game.perspective[3][0] = 0.0f;
		game.perspective[3][1] = 0.0f;
		game.perspective[3][2] = 0.0f;
		game.perspective[3][3] = 1.0f;

		cam.InitializeCameraTransform();
	}

	void Update() {
		HandleKeys();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(game.shader.GetProgram());

		game.shader.SetUniformPosition(game.playerPos);
		game.shader.SetUniformScale(game.scale);
		game.shader.SetUniformMat4x4(game.mat);
	

		game.triangle.BindMesh(GL_ELEMENT_ARRAY_BUFFER);
		game.triangle.UnbindMesh();
	
		float x = 0.2f, y = 0.2f, z = 0.2f,  w = 0.2f;
		game.trans._11 = 1.0f; game.trans[0][1] = 0.0f; game.trans[0][2] = 0.0f; game.trans[0][3] = 0.0f;
		game.trans[1][0] = 0.0f; game.trans._22 = 1.0f; game.trans[1][2] = 0.0f; game.trans[1][3] = 0.0f;
		game.trans[2][0] = 0.0f; game.trans[2][1] = 0.0f; game.trans._33 = 1.0f; game.trans[2][3] = 0.0f;
		game.trans[3][0] = 0.0f; game.trans[3][1] = 0.0f; game.trans[3][2] = 0.0f; game.trans._44 = 1.0f;

		game.size._11 = 2.0f; game.size[0][1] = 0.0f; game.size[0][2] = 0.0f; game.size[0][3] = 0.0f;
		game.size[1][0] = 0.0f; game.size._22 = 2.0f; game.size[1][2] = 0.0f; game.size[1][3] = 0.0f;
		game.size[2][0] = 0.0f; game.size[2][1] = 0.0f; game.size._33 = 2.0f; game.size[2][3] = 0.0f;
		game.size[3][0] = 0.0f; game.size[3][1] = 0.0f; game.size[3][2] = 0.0f; game.size._44 = 1.0f;

		game.rot._11 = cosf(game.scale); game.rot[0][1] = 0.0f; game.rot[0][2] = sinf(game.scale); game.rot[0][3] = 0.0f;
		game.rot[1][0] = 0.0f; game.rot._22 = 1.0f; game.rot[1][2] = 0.0f; game.rot[1][3] = 0.0f;
		game.rot[2][0] = -sinf(game.scale); game.rot[2][1] = 0.0f; game.rot._33 = cosf(game.scale); game.rot[2][3] = 0.0f;
		game.rot[3][0] = 0.0f; game.rot[3][1] = 0.0f; game.rot[3][2] = 0.0f; game.rot._44 = 1.0f;

	
		game.mat = game.perspective * game.trans * game.rot * game.size;

		game.scale += 1.f * platform->clock->deltaTime;

		glUseProgram(0);
	}

	~App() { }
};

