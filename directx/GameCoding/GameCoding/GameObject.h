#pragma once
class MonoBehaviour;

class GameObject:public enable_shared_from_this<GameObject>
{
public:
	GameObject(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext);
	~GameObject();
#pragma region LifeCycle
	void Awake();
	void Start();
	void Update();
	void LateUpdate();
	void FixedUpdate();
#pragma endregion

	shared_ptr<Component>GetFixedComponent(ComponentType type);

	shared_ptr<Transform>GetTransform();
	shared_ptr<Transform>GetorAddTransform();

	void AddComponent(shared_ptr<Component>component);
	void  Render(shared_ptr<Pipeline> pipeline);

private:
	ComPtr<ID3D11Device> _device;
	shared_ptr<Geometry<VertexTextureData>>_geometry;
	shared_ptr<VertexBuffer> _vertexBuffer;
	shared_ptr<IndexBuffer> _indexBuffer;
	shared_ptr<InputLayout> _inputLayout;

	shared_ptr<VertexShader> _vertexShader;
	shared_ptr<RasterizerState> _rasterizerState;
	shared_ptr<PixelShader> _pixelShader;

	shared_ptr<Texture> _texture1;

	shared_ptr<SamplerState>_samplerState;
	shared_ptr<BlendState> _blendState;
	//[CPU<->RAM] [GPU<->RAM]};
private:
	TransformData _transformData;
	shared_ptr<ConstantBuffer<TransformData>> _constantBuffer;


	shared_ptr<Transform> _transform = make_shared<Transform>();

protected:
	//고정크기(각각 하나씩)
	array<shared_ptr<Component>, FIXED_COMPONENT_COUNT> _components;   
	//여러개들어갈수있는  scripts
	vector<shared_ptr<MonoBehaviour>> _scripts;
	
};

