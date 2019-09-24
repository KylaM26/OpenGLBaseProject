#pragma once

#include "Math/Vector3.h"
#include "Math/MatrixMath.h"

using namespace IncredibleMath;

class Pipeline {
private:
	Vector3 m_scale;
	Vector3 m_worldPos;
	Vector3 m_rotateInfo;
	Matrix4x4 m_transformation;
public:
	Pipeline() {}
	void Scale(float ScaleX, float ScaleY, float ScaleZ) {
	
}
	void WorldPos(float x, float y, float z) {}
	void Rotate(float RotateX, float RotateY, float RotateZ) {}
	const Matrix4x4* GetTrans() {
		Matrix4x4 ScaleTrans, RotateTrans, TranslationTrans;
		m_transformation = TranslationTrans * RotateTrans * ScaleTrans;
		return &m_transformation;
	}

};
