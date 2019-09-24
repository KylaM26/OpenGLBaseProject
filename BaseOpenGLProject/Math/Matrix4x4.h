#pragma once

#include <stdio.h>

namespace IncredibleMath {
	typedef struct Matrix4x4 {
		union {
			struct {
				float _11, _12, _13, _14,
					_21, _22, _23, _24,
					_31, _32, _33, _34,
					_41, _42, _43, _44;
			};

			float arr[16];
		};

		Matrix4x4();
		Matrix4x4(float xPos, float yPos, float zPos);

		Matrix4x4 operator*(float scaler);

		inline float* operator[](const int index) {
			return &(arr[index * 4]);
		}

	} Matrix4x4, Mat4x4, M4x4;

	inline Matrix4x4::Matrix4x4() {
		this->_11 = 1.0f; this->_12 = 0.0f; this->_13 = 0.0f; this->_14 = 0.0f;
		this->_21 = 0.0f; this->_22 = 1.0f; this->_23 = 0.0f; this->_24 = 0.0f;
		this->_31 = 0.0f; this->_32 = 0.0f; this->_33 = 1.0f; this->_34 = 0.0f;
		this->_11 = 0.0f; this->_42 = 0.0f; this->_43 = 0.0f; this->_44 = 1.0f;
	}

	inline Matrix4x4::Matrix4x4(float xPos, float yPos, float zPos) {
		this->_11 = 1.0f; this->_12 = 0.0f; this->_13 = 0.0f; this->_14 = xPos;
		this->_21 = 0.0f; this->_22 = 1.0f; this->_23 = 0.0f; this->_24 = yPos;
		this->_31 = 0.0f; this->_32 = 0.0f; this->_33 = 1.0f; this->_34 = zPos;
		this->_11 = 0.0f; this->_42 = 0.0f; this->_43 = 0.0f; this->_44 = 1.0f;
	}

	Matrix4x4 Matrix4x4::operator*(float scaler) {
		Matrix4x4 m;
		for (int i = 0; i < 4; i++)
			m.arr[i] = this->arr[i] * scaler;

		return m;
	}
}