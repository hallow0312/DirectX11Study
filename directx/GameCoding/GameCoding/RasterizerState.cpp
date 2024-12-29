#include "pch.h"
#include "RasterizerState.h"

RasterizerState::RasterizerState(ComPtr<ID3D11Device> device):_device(device)
{
}

RasterizerState::~RasterizerState()
{
}

void RasterizerState::Create()
{
	D3D11_RASTERIZER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.FillMode = D3D11_FILL_SOLID;
	desc.CullMode = D3D11_CULL_BACK; //카메라영역 벗어나면 컬링 등 
	desc.FrontCounterClockwise = false; //성능  향상을 위함 앞면 :시계방향 뒷면 : 반시계방향 

	HRESULT hr = _device->CreateRasterizerState(&desc, _rasterizerState.GetAddressOf());
	CHECK(hr);
}
