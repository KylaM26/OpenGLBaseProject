#pragma once


#include <stdio.h>

namespace IncredibleMath {
	typedef struct Vector3 {
		union {
			struct {
				float x, y, z;
			};

			struct {
				float r, g, b;
			};

			float arr[3];
		};

		Vector3();
		Vector3(float x, float y, float z);

		Vector3 operator+(const Vector3& v);
		Vector3 operator-(const Vector3& v);
		Vector3 operator*(const Vector3& v);
		Vector3 operator+(const float& f);
		Vector3 operator-(const float& f);
		Vector3 operator*(const float& f);

		float& operator[](const int index);

		void operator=(const Vector3& v);
		void operator+=(const Vector3& v);
		void operator-=(const Vector3& v);
		void operator*=(const Vector3& v);
		void operator+=(const float& f);
		void operator-=(const float& f);
		void operator*=(const float& f);
		void operator++();
		void operator--();



		void Print();
	} Vector3, Vec3, V3;


	// CONSTRUCTORS
	Vector3::Vector3() {
		this->x = 0, this->y = 0, this->z = 0;
	}

	Vector3::Vector3(float x, float y, float z) {
		this->x = x, this->y = y, this->z = z;
	}



	// VECTOR RETURN OVERLOADS
	Vector3 Vector3::operator+(const Vector3& v) {
		return Vector3(this->x + v.x, this->y + v.y, this->z + v.z);
	}

	Vector3 Vector3::operator-(const Vector3& v) {
		return Vector3(this->x - v.x, this->y - v.y, this->z - v.z);
	}

	Vector3 Vector3::operator*(const Vector3& v) {
		return Vector3(this->x * v.x, this->y * v.y, this->z * v.z);
	}

	Vector3 Vector3::operator+(const float& f) {
		return Vector3(this->x + f, this->y + f, this->z + f);
	}

	Vector3 Vector3::operator-(const float& f) {
		return Vector3(this->x - f, this->y - f, this->z - f);
	}

	Vector3 Vector3::operator*(const float& f) {
		return Vector3(this->x * f, this->y * f, this->z * f);
	}


	// VOID OVERLOADS
	void Vector3::operator+=(const Vector3& v) {
		this->x += v.x, this->y += v.y, this->z += v.z;
	}

	void Vector3::operator-=(const Vector3& v) {
		this->x -= v.x, this->y -= v.y, this->z -= v.z;
	}

	void Vector3::operator*=(const Vector3& v) {
		this->x *= v.x, this->y *= v.y, this->z *= v.z;
	}

	void Vector3::operator=(const Vector3& v) {
		this->x = v.x;
		this->y = v.y;
		this->z = v.z;
	}

	void Vector3::operator+=(const float& f) {
		this->x += f, this->y += f, this->z += f;
	}

	void Vector3::operator-=(const float& f) {
		this->x -= f, this->y -= f, this->z -= f;
	}

	void Vector3::operator*=(const float& f) {
		this->x *= f, this->y *= f, this->z *= f;
	}

	void Vector3::operator++() {
		this->x++, this->y++, this->z++;
	}
	void Vector3::operator--() {
		this->x--; this->y--, this->z--;
	}

	// FLOATING POINT RETURNS

	float& Vector3::operator[](const int index) {
		if (index < 3) return arr[index]; else printf("Index of: %d, is out of range!", index); return arr[0];
	}

	// MISC
	void Vector3::Print() {
		printf("x: %f, y: %f, z: %f\n", this->x, this->y, this->z);
	}
}