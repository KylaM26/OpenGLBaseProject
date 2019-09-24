#pragma once

namespace IncredibleMath {
	bool Multiply(float* out, const float* matA, int aRows, int aCols, const float* matB, int bRows, int bCols);

	// MATRIX 2X2
	typedef struct Matrix2x2 {
		union {
			struct {
				float _11, _12, _21, _22;
			};

			float arr[4];
		};

		Matrix2x2 operator*(float scaler);

		inline float* operator[](const int index) {
			return &(arr[index * 2]);
		}

	} Matrix2x2, Mat2x2, M2x2;

	Matrix2x2 Matrix2x2::operator*(float scaler) {
		Matrix2x2 m;
		for (int i = 0; i < 2; i++)
			m.arr[i] = this->arr[i] * scaler;

		return m;
	}

	Matrix2x2 operator*(const Matrix2x2& a, const Matrix2x2& b) {
		Matrix2x2 r;
		if (!Multiply(r.arr, a.arr, 2, 2, b.arr, 2, 2))
			return Matrix2x2();
		return r;
	}

	// MATRIX 3X3
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

	Matrix3x3 operator*(const Matrix3x3& a, const Matrix3x3& b) {
		Matrix3x3 r;
		if (!Multiply(r.arr, a.arr, 3, 3, b.arr, 3, 3))
			return Matrix3x3();
		return r;
	}

	// MATRIX 4X4
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

	Matrix4x4 operator*(const Matrix4x4& a, const Matrix4x4& b) {
		Matrix4x4 r;
		if (!Multiply(r.arr, a.arr, 4, 4, b.arr, 4, 4))
			return Matrix4x4();
		return r;
	}

	// MATRIX MATH OPERATIONS
	void Transpose(const float* sourceMat, float* destinationMat, const int sourceRows, const int sourceColums) {
		for (int i = 0; i < sourceRows * sourceColums; i++) {
			int row = i / sourceRows;
			int col = i % sourceRows;
			destinationMat[i] = sourceMat[sourceColums * col + row];
		}
	}

	Matrix2x2 Transpose(const Matrix2x2& m) {
		Matrix2x2 r;
		Transpose(m.arr, r.arr, 2, 2);
		return r;
	}

	Matrix3x3 Transpose(const Matrix3x3& m) {
		Matrix3x3 r;
		Transpose(m.arr, r.arr, 3, 3);
		return r;
	}

	Matrix4x4 Transpose(const Matrix4x4& m) {
		Matrix4x4 r;
		Transpose(m.arr, r.arr, 4, 4);
		return r;
	}

	bool Multiply(float* out, const float* matA, int aRows, int aCols, const float* matB, int bRows, int bCols) {
		if (aCols != bRows)
			return false;

		for (int i = 0; i < aRows; ++i) {
			for (int j = 0; j < bCols; ++j) {
				out[bCols * i + j] = 0.0f;
				for (int k = 0; k < bRows; ++k) {
					int a = aCols * i + k;
					int b = bCols * k + j;
					out[bCols * i + j] += matA[a] * matB[b];
				}
			}
		}

		return true;
	}

	//Matrix2x2 Matrix2x2::operator*(const Matrix2x2& a, const Matrix2x2& b) {
	//	Matrix2x2 r;
	//	if (!Multiply(r.arr, a.arr, 2, 2, b.arr, 2, 2))
	//		return;
	//	return r;
	//}

	//Matrix2x2 MultiplyMaxtrix(const Matrix2x2& a, const Matrix2x2& b) {

	//}

	//Matrix3x3 MultiplyMaxtrix(const Matrix3x3& a, const Matrix3x3& b) {
	//	Matrix3x3 r;
	//	if (!Multiply(r.arr, a.arr, 3, 3, b.arr, 3, 3))
	//		return;
	//	return r;
	//}

	//Matrix4x4 MultiplyMaxtrix(const Matrix4x4& a, const Matrix4x4& b) {
	//	Matrix4x4 r;
	//	if (!Multiply(r.arr, a.arr, 4, 4, b.arr, 4, 4))
	//		return;
	//	return r;
	//}
}

