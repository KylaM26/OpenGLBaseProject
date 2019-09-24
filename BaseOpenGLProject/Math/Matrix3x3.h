#pragma once

#include <stdio.h>

namespace IncredibleMath {
	typedef struct Matrix3x3 {
		union {
			struct {
				float _11, _12, _13,
					  _21, _22, _23,
					  _31, _32, _33;
			};

			float arr[9];
		};

		Matrix3x3 operator*(float scaler);

		inline float* operator[](const int index) {
			return &(arr[index * 3]);
		}

	} Matrix3x3, Mat3x3, M3x3;


	Matrix3x3 Matrix3x3::operator*(float scaler) {
		Matrix3x3 m;
		for (int i = 0; i < 3; i++)
			m.arr[i] = this->arr[i] * scaler;

		return m;
	}

}