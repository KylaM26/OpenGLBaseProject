#pragma once

#include <cmath>
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

#define PI 3.14159265
#define RAD_TO_DEG(f) (f * (180/PI)) 
#define DEG_TO_RAD(f) (f * (PI/180)) 

namespace IncredibleMath {
	// DOT
	float Dot(const Vector2& a, const Vector2& b) { // This function does not normalize the vector.
		return ((a.x * b.x) + (a.y * b.y));
	}

	float Dot(const Vector3& a, const Vector3& b) { // This function does not normalize the vector.
		return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
	}

	float Dot(const Vector4& a, const Vector4& b) {
		return ((a.x * b.x) + (a.y * b.y));
	}

	// MAGNITUTDE
	float Magnitude(const Vector2& v) {
		return sqrtf(Dot(v, v));
	}

	float Magnitude(const Vector3& v) {
		return sqrtf(Dot(v, v));
	}

	float Magnitude(const Vector4& v) {
		return sqrtf(Dot(v,v));
	}

	float MagnitudeSq(const Vector2& v) { // Instead of using the normal Magnitutde function just used this and multiply the value it is being checked against twice. To avoid using the sqrt() function
		return Dot(v, v);
	}

	float MagnitudeSq(const Vector3& v) { // Instead of using the normal Magnitutde function just used this and multiply the value it is being checked against twice. To avoid using the sqrt() function
		return Dot(v, v);
	}

	float MagnitudeSq(const Vector4& v) {
		return Dot(v, v);
	}

	// NORMALIZE (Const issue)

	Vector2 Normalize(Vector2& v) {
		return (v * (1.f / Magnitude(v)));
	}

	Vector3 Normalize(Vector3& v) { 
		return (v * (1.f / Magnitude(v)));
	}

	Vector4 Normalize(Vector4& v) {
		return (v * (1.f / Magnitude(v)));
	}

	// Angle
	float GetAngleBetweenVectors(const Vector2& a, const Vector2& b) {
		return acosf(Dot(a, b));
	}

	float GetAngleBetweenVectors(const Vector3& a, const Vector3& b) {
		return acosf(Dot(a, b));
	}

	//float GetAngleBetweenVectors(const Vector4& a, const Vector4& b) {
	//	return (acosf(Dot(a, b)));
	//}

	// CROSS
	Vector3 Cross(const Vector3& a, const Vector3& b) {
		Vector3 result = Vector3();
		result.x = a.y * b.z - a.z * b.y;
		result.y = a.z * b.x - a.x * b.z;
		result.z = a.x * b.y - a.y * b.x;
		return result;
	}

	// PROJECT (Const issue)
	Vector2 Project(Vector2& length, Vector2& direction) { // B will be projected onto A
		float dP = Dot(length, direction);
		float magSq = MagnitudeSq(direction);
		return direction * (dP / magSq);
	}

	Vector3 Project(Vector3& length, Vector3& direction) { // B will be projected onto A
		float dP = Dot(length, direction);
		float magSq = MagnitudeSq(direction);
		return direction * (dP / magSq);
	}

	//Vector4 Project(Vector4& length, Vector4& direction) {
	//	float dP = Dot(length, direction);
	//	float magSq = MagnitudeSq(direction);
	//	return direction * (dP / magSq);
	//}

	// PERPENDICULAR (Const issue)
	Vector2 Perpendicular(Vector2& length, Vector2& direction) {
		return length - Project(length, direction);
	}

	Vector3 Perpendicular(Vector3& length, Vector3& direction) {
		return length - Project(length, direction);
	}

	//Vector4 Perpendicular(Vector4& length, Vector4& direction) {
	//	return length - Project(length, direction);
	//}

	// REFLECTION
	Vector2 Reflect(Vector2& v, Vector2& normal) {
		float dot = Dot(v, normal);
		return (v - normal * (dot * 2.f));
	}

	Vector3 Reflect(Vector3& v, Vector3& normal) {
		float dot = Dot(v, normal);
		return (v - normal * (dot * 2.f));
	}

	//Vector4 Reflect(Vector4& v, Vector4& normal) {
	//	float dot = Dot(v, normal);
	//	return (v - normal * (dot * 2.f));
	//}

}	 
