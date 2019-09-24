#pragma once

#include <stdio.h>

namespace IncredibleMath {
	typedef struct Vector4 {
		union {
			struct {
				float x, y, z, w;
			};

			struct {
				float r, g, b, a;
			};

			float arr[4];
		};

		Vector4();
		Vector4(float x, float y, float z, float w);

		Vector4 operator+(const Vector4& v);
		Vector4 operator-(const Vector4& v);
		Vector4 operator*(const Vector4& v);
		Vector4 operator+(const float& f);
		Vector4 operator-(const float& f);
		Vector4 operator*(const float& f);

		float& operator[](const int index);

		void operator=(const Vector4& v);
		void operator+=(const Vector4& v);
		void operator-=(const Vector4& v);
		void operator*=(const Vector4& v);
		void operator+=(const float& f);
		void operator-=(const float& f);
		void operator*=(const float& f);
		void operator++();
		void operator--();



		void Print();
	} Vector4, Vec4, V4;

	// CONSTRUCTORS
	Vector4::Vector4() {
		this->x = 0, this->y = 0, this->z = 0, this->w = 0;
	}

	Vector4::Vector4(float x, float y, float z, float w) {
		this->x = x, this->y = y, this->z = z, this->w = w;
	}



	// VECTOR RETURN OVERLOADS
	Vector4 Vector4::operator+(const Vector4& v) {
		return Vector4(this->x + v.x, this->y + v.y, this->z + v.z, this->w + v.w);
	}

	Vector4 Vector4::operator-(const Vector4& v) {
		return Vector4(this->x - v.x, this->y - v.y, this->z - v.z, this->w - v.w);
	}

	Vector4 Vector4::operator*(const Vector4& v) {
		return Vector4(this->x * v.x, this->y * v.y, this->z * v.z, this->w * v.w);
	}

	Vector4 Vector4::operator+(const float& f) {
		return Vector4(this->x + f, this->y + f, this->z + f, this->w + f);
	}

	Vector4 Vector4::operator-(const float& f) {
		return Vector4(this->x - f, this->y - f, this->z - f, this->w - f);
	}

	Vector4 Vector4::operator*(const float& f) {
		return Vector4(this->x * f, this->y * f, this->z * f, this->w * f);
	}



	// VOID OVERLOADS
	void Vector4::operator+=(const Vector4& v) {
		this->x += v.x, this->y += v.y, this->z += v.z, this->w += v.w;
	}

	void Vector4::operator-=(const Vector4& v) {
		this->x -= v.x, this->y -= v.y, this->z -= v.z, this->w -= v.w;
	}

	void Vector4::operator*=(const Vector4& v) {
		this->x *= v.x, this->y *= v.y, this->z *= v.z, this->w *= v.w;
	}

	void Vector4::operator=(const Vector4& v) {
		this->x = v.x;
		this->y = v.y;
		this->z = v.z;
		this->w = v.w;
	}

	void Vector4::operator+=(const float& f) {
		this->x += f, this->y += f, this->z += f, this->w += f;
	}

	void Vector4::operator-=(const float& f) {
		this->x -= f, this->y -= f, this->z -= f, this->w -= f;
	}

	void Vector4::operator*=(const float& f) {
		this->x *= f, this->y *= f, this->z *= f, this->w *= f;
	}

	void Vector4::operator++() {
		this->x++, this->y++, this->z++, this->w++;
	}
	void Vector4::operator--() {
		this->x--; this->y--, this->z--, this->w--;
	}

	// FLOATING POINT RETURNS

	float& Vector4::operator[](const int index) {
		if (index < 4) return arr[index]; else printf("Index of: %d, is out of range!", index); return arr[0];
	}

	// MISC
	void Vector4::Print() {
		printf("x: %f, y: %f, z: %f, w: %f\n", this->x, this->y, this->z, this->w);
	}
}
