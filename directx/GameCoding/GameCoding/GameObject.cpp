#include "pch.h"
#include "GameObject.h"
#include"MonoBehaviour.h"
#include"Transform.h"

GameObject::GameObject(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext):_device(device)
{
	//객체마다 들고있어야할부분 

	_geometry = make_shared<Geometry<VertexTextureData>>();
	GeometryHelper::CreateRectangle(_geometry); //기하학적인 도형 

	_vertexBuffer = make_shared<VertexBuffer>(_device); 
	_vertexBuffer->Create(_geometry->GetVertices());

	_indexBuffer = make_shared<IndexBuffer>(_device);
	_indexBuffer->Create(_geometry->GetIndices());

	_vertexShader = make_shared<VertexShader>(_device);
	_vertexShader->Create(L"Default.hlsl", "VS", "vs_5_0");

	_inputLayout = make_shared<InputLayout>(_device);
	_inputLayout->Create(VertexTextureData::descs, _vertexShader->GetBlob());
	
	_pixelShader = make_shared<PixelShader>(_device);
	_pixelShader->Create(L"Default.hlsl", "PS", "ps_5_0");

	_rasterizerState = make_shared<RasterizerState>(_device);
	_rasterizerState->Create();
	
	_blendState = make_shared<BlendState>(_device);
	_blendState->Create();

	_constantBuffer = make_shared<ConstantBuffer<TransformData>>(_device, deviceContext);
	_constantBuffer->Create();
	
	_texture1 = make_shared<Texture>(_device);
	_texture1->Create(L"Skeleton.png");

	_samplerState = make_shared<SamplerState>(_device);
	_samplerState->Create();


}

GameObject::~GameObject()
{
}

void GameObject::Awake()
{
	for (shared_ptr<Component>& component : _components)
	{
		if (component)
		component->Awake();
	}
	for (shared_ptr<MonoBehaviour>& script : _scripts)
	{
		script->Awake();
	}
}

void GameObject::Start()
{
	for (shared_ptr<Component>& component : _components)
	{
		if (component)
		component->Start();
	}
	for (shared_ptr<MonoBehaviour>& script : _scripts)
	{
		script->Start();
	}
}

void GameObject::Update()
{
	for (shared_ptr<Component>& component : _components)
	{
		if (component)
			component->Update();
		
		
	}
	for (shared_ptr<MonoBehaviour>& script : _scripts)
	{
		script->Update();
	}

	_transformData.matWorld = GetorAddTransform()->GetWorldMatrix();
	_constantBuffer->CopyData(_transformData);
}

void GameObject::LateUpdate()
{
	for (shared_ptr<Component>& component : _components)
	{
		if(component)
		component->LateUpdate();
	}
	for (shared_ptr<MonoBehaviour>& script : _scripts)
	{
		script->LateUpdate();
	}
}

void GameObject::FixedUpdate()
{
	for (shared_ptr<Component>& component : _components)
	{
		if (component)
		component->FixedUpdate();
	}
	for (shared_ptr<MonoBehaviour>& script : _scripts)
	{
		script->FixedUpdate();
	}
}

shared_ptr<Component> GameObject::GetFixedComponent(ComponentType type)
{
	uint8 index = static_cast<uint8>(type);
	assert(index < FIXED_COMPONENT_COUNT);
	return _components[index];
}

shared_ptr<Transform> GameObject::GetTransform()
{
	shared_ptr<Component> component = GetFixedComponent(ComponentType::Transform);
	return static_pointer_cast<Transform>(component);
}

shared_ptr<Transform> GameObject::GetorAddTransform()
{
	if (GetTransform() == nullptr)
	{
		shared_ptr<Transform>transform = make_shared<Transform>();
		AddComponent(transform);
	}
	return GetTransform();
}

void GameObject::AddComponent(shared_ptr<Component> component)
{
	component->SetGameObject(shared_from_this());
	uint8 index = static_cast<uint8>(component->GetType());
	if (index < FIXED_COMPONENT_COUNT)
	{
		_components[index] = component;
	}
	else
	{
		_scripts.push_back(dynamic_pointer_cast<MonoBehaviour>(component));
	}
	

}

void GameObject::Render(shared_ptr<Pipeline> pipeline)
{
	PipelineInfo  info;
	info.inputLayout = _inputLayout;
	info.vertexShader = _vertexShader;
	info.pixelShader = _pixelShader;
	info.rasterizerState = _rasterizerState;
	info.blendState = _blendState;

	pipeline->UpdatePipeline(info); 

	// IA
	pipeline->SetVertexBuffer(_vertexBuffer);  
	pipeline->SetIndexBuffer(_indexBuffer); 
	pipeline->SetConstantBuffer(0, SS_VertexShader, _constantBuffer); 
	pipeline->SetTexture(0, SS_PixelShader, _texture1); 
	pipeline->SetSamplerState(0, SS_PixelShader, _samplerState); 
	pipeline->DrawIndexed(_geometry->GetIndexCount(), 0, 0);
} 
