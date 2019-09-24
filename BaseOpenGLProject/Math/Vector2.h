#pragma once

#include <stdio.h>

namespace IncredibleMath {
	typedef struct Vector2 {
		union {
			struct {
				float x, y;
			};

			float arr[2];
		};

		Vector2();
		Vector2(float x, float y);

		Vector2 operator+(const Vector2& v);
		Vector2 operator-(const Vector2& v);
		Vector2 operator*(const Vector2& v);
		Vector2 operator+(const float& f);
		Vector2 operator-(const float& f);
		Vector2 operator*(const float& f);

		float& operator[](const int index);

		void operator=(const Vector2& v);
		void operator+=(const Vector2& v);
		void operator-=(const Vector2& v);
		void operator*=(const Vector2& v);
		void operator+=(const float& f);
		void operator-=(const float& f);
		void operator*=(const float& f);
		void operator++();
		void operator--();

		void Print();
	} Vector2, Vec2, V2;


	// CONSTRUCTORS
	Vector2::Vector2() {
		this->x = 0, this->y = 0;
	}

	Vector2::Vector2(float x, float y) {
		this->x = x, this->y = y;
	}



	// VECTOR RETURN OVERLOADS
	Vector2 Vector2::operator+(const Vector2& v) {
		return Vector2(this->x + v.x, this->y + v.y);
	}

	Vector2 Vector2::operator-(const Vector2& v) {
		return Vector2(this->x - v.x, this->y - v.y);
	}

	Vector2 Vector2::operator*(const Vector2& v) {
		return Vector2(this->x * v.x, this->y * v.y);
	}

	Vector2 Vector2::operator+(const float& f) {
		return Vector2(this->x + f, this->y + f);
	}

	Vector2 Vector2::operator-(const float& f) {
		return Vector2(this->x - f, this->y - f);
	}

	Vector2 Vector2::operator*(const float& f) {
		return Vector2(this->x * f, this->y * f);
	}



	// VOID OVERLOADS
	void Vector2::operator+=(const Vector2& v) {
		this->x += v.x, this->y += v.y;
	}

	void Vector2::operator-=(const Vector2& v) {
		this->x -= v.x, this->y -= v.y;
	}

	void Vector2::operator*=(const Vector2& v) {
		this->x *= v.x, this->y *= v.y;
	}

	void Vector2::operator=(const Vector2& v) {
		this->x = v.x;
		this->y = v.y;
	}

	void Vector2::operator+=(const float& f) {
		this->x += f, this->y += f;
	}

	void Vector2::operator-=(const float& f) {
		this->x -= f, this->y -= f;
	}

	void Vector2::operator*=(const float& f) {
		this->x *= f, this->y *= f;
	}

	void Vector2::operator++() {
		this->x++, this->y++;
	}
	void Vector2::operator--() {
		this->x--; this->y--;
	}

	// FLOATING POINT RETURNS

	float& Vector2::operator[](const int index) {
		if (index < 2) return arr[index]; else printf("Index of: %d, is out of range!", index); return arr[0];
	}

	// MISC
	void Vector2::Print() {
		printf("x: %f, y: %f\n", this->x, this->y);
	}
}