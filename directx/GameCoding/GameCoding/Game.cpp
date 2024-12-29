#include "pch.h"
#include "Game.h"
#include"Camera.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init(HWND hwnd)
{
	_hwnd = hwnd;

	_graphics = make_shared<Graphics>(hwnd);
	_pipeline = make_shared<Pipeline>(_graphics->GetDeviceContext());
	
	//GameObject
	_monster = make_shared<GameObject>(_graphics->GetDevice(), _graphics->GetDeviceContext());
	_monster->GetorAddTransform();
	
	_camera= make_shared<GameObject>(_graphics->GetDevice(), _graphics->GetDeviceContext());
	_camera->GetorAddTransform();
	_camera->AddComponent(make_shared<Camera>());
	
}

void Game::Update()
{
	//scale Rotation Transtaition;
	_monster->Update();
}

void Game::Render()
{
	_graphics->RenderBegin();
	//IA-VS-RS-PS-OW
	{
		_monster->Render(_pipeline);
	}
	_graphics->RenderEnd();
}

