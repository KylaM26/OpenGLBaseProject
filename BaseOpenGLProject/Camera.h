#pragma once

#include <glew.h>
#include "Math/Matrix4x4.h"
#include "Math/Vector3.h"
#include "Math/VectorMath.h"

using namespace IncredibleMath;

class Camera {
public:
	V3 position, direction;
	V3 up, right;
	IncredibleMath::M4x4 matrix;
	float pitch, yaw, roll;

	Camera() {}

	Camera(V3 position, V3 target, V3 up) {
		 this->direction = Normalize(target);
		 this->up = Cross(up, direction);
		 this->up = Normalize(up);
		 this->right = Cross(direction, up);

		 //maxtrix[0][0] = up.x;			maxtrix[0][1] = up.y;
		 //maxtrix[1][0] = right.x;		maxtrix[1][1] = right.y;
		 //maxtrix[2][0] = direction.x;	maxtrix[2][1] direction.y;
		 //maxtrix[3][0] = 0.0f;

		 matrix[0][0] = up.x; matrix[0][1] = up.y; matrix[0][2] = up.z; matrix[0][3] = 0.0f;
		 matrix[1][0] = right.x; matrix[1][1] = right.y; matrix[1][2] = right.z; matrix[1][3] = 0.0f;
		 matrix[2][0] = direction.x; matrix[2][1] = direction.y; matrix[2][2] = direction.z; matrix[2][3] = 0.0f;
		 matrix[3][0] = 0.0f; matrix[3][1] = 0.0f; matrix[3][2] = 0.0f; matrix[3][3] = 1.0f;
	}


};