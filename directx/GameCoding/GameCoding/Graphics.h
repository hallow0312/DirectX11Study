#pragma once
class Graphics
{
public:
	Graphics(HWND hwnd);
	~Graphics();
	void RenderBegin();
	void RenderEnd();

	ComPtr<ID3D11Device>GetDevice() { return _device; }
	ComPtr<ID3D11DeviceContext>GetDeviceContext() { return _deviceContext; }

private:
	void CreateDeviceAndSwapChain();
	void CreateRenderTargetView(); //
	void SetViewPort();
private:
	HWND  _hwnd;
	uint32 _width = 0;
	uint32 _height = 0;

private:

	//Device &SwapChain
	ComPtr<ID3D11Device> _device = nullptr; //unit ����
	ComPtr <ID3D11DeviceContext> _deviceContext = nullptr;  //unit ���� ���϶�� �ϴ� ��  

	ComPtr<IDXGISwapChain>_swapChain = nullptr;

	//RtV
	ComPtr<ID3D11RenderTargetView> _renderTargetView;

	//Misc //ȭ���� �����ϴ� ����ü 
	D3D11_VIEWPORT _viewPort = { 0 };
	float _clearColor[4] = { 0.f,0.f,0.f,0.f };

};

