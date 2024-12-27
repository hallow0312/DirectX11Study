#include "pch.h"
#include "GeometryHelper.h"

void GeometryHelper::CreateRectangle(shared_ptr<Geometry<VertexColorData>> geometry, Color color)
{
	vector <VertexColorData> _vertices;
	_vertices.resize(4);
	//13
	//02
	_vertices[0].position = Vec3(-0.5f, -0.5f, 0.f);
	_vertices[0].color = color;
	
	_vertices[1].position = Vec3(-0.5f, 0.5f, 0.f);
	_vertices[1].color = color;
	
	_vertices[2].position = Vec3(0.5f, -0.5f, 0.f);
	_vertices[2].color = color;
	
	_vertices[3].position = Vec3(0.5f, 0.5f, 0.f);
	_vertices[3].color = color;
	
	geometry->SetVertices(_vertices);
	vector<uint32> indices = { 0,1,2,2,1,3 };
	geometry->SetIndices(indices);
}



void GeometryHelper::CreateRectangle(shared_ptr<Geometry<VertexTextureData>> geometry)
{
	vector <VertexTextureData> _vertices;
	
	_vertices.resize(4);
	//13
	//02
	_vertices[0].position = Vec3(-0.5f, -0.5f, 0.f);
	_vertices[0].uv = { 0.f,1.f };
	//_vertices[0].color = Color(1.f, 0.f, 0.f, 1.f);

	_vertices[1].position = Vec3(-0.5f, 0.5f, 0.f);
	_vertices[1].uv = { 0.f,0.f };

	//_vertices[1].color = Color(1.f, 0.f, 0.f, 1.f);

	_vertices[2].position = Vec3(0.5f, -0.5f, 0.f);
	_vertices[2].uv = { 1.f,1.f };

	//_vertices[2].color = Color(1.f, 0.f, 0.f, 1.f);

	_vertices[3].position = Vec3(0.5f, 0.5f, 0.f);
	_vertices[3].uv = { 1.f,0.f };


	geometry->SetVertices(_vertices);
	vector<uint32> indices = { 0,1,2,2,1,3 };
	geometry->SetIndices(indices);
}
