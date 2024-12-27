#pragma once


class Game
{
public:
	Game();
	~Game();
public:
	void Init(HWND hwnd);
	void Update();
	void Render();
private:
	HWND _hwnd;
	shared_ptr<Graphics> _graphics; 
private:

	void CreateRasterizerState();
	void CreateSamplerState();
	void CreateBlendState();
	
private:
	//Geometry
	//vector<Vertex> _vertices;
	//기하학적인 도형 제작 한번만 만들면 됨 
	//resource로 빼줄 필요가 있음 
	shared_ptr<Geometry<VertexTextureData>>_geometry;
	shared_ptr<VertexBuffer> _vertexBuffer;
	shared_ptr<IndexBuffer> _indexBuffer;
	shared_ptr<InputLayout> _inputLayout;
	
	shared_ptr<VertexShader> _vertexShader;
	
	ComPtr<ID3D11RasterizerState> _rasterizerState = nullptr;

	shared_ptr<PixelShader> _pixelShader;
	
	shared_ptr<Texture> _texture1;
	shared_ptr<Texture> _texture2;


	ComPtr<ID3D11SamplerState> _samplerState = nullptr;
	ComPtr<ID3D11BlendState> _blendState = nullptr;
	//[CPU<->RAM] [GPU<->RAM]};
private:
	TransformData _transformData;
	shared_ptr<ConstantBuffer<TransformData>> _constantBuffer;
	//ComPtr<ID3D11Buffer> _constantBuffer;

	Vec3 _localPosition = { 0.f,0.f,0.f };
	Vec3 _localRotation = { 0.f,0.f,0.f };
	Vec3 _localScale = { 1.f,1.f,1.f };
};


