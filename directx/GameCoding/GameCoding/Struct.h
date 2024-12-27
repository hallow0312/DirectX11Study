#pragma once
#include "Types.h"

//struct Vertex
//{
//	Vec3 position;//12BYTE
//	//Color color;
//	Vec2 uv; 
//};
struct TransformData
{
	Matrix matWorld= Matrix::Identity;
	Matrix matView= Matrix::Identity;
	Matrix matProjection = Matrix::Identity;
};