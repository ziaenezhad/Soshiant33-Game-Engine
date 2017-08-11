#include "S33Engine.h"
#include "S33Event.h"

using namespace Pei::Utility;
using namespace Pei::Graphic;

namespace Soshiant33
{
	HINSTANCE appHandle = 0;
	S33Library* S33Engine::shareLibrary = new S33Library();
	
	S33Engine::S33Engine(unsigned int width,unsigned int height,bool fullscreen,HWND windowHandle ):S33ComplexEntity(0,0,0)
	{
		this->type = S33Entity::Type_Engine;
		this->window = 0;
		this->windowHandle = 0;
		this->ep.name = "Soshiant33Engine";
		this->timer.Start();
		this->width = width;
		this->height = height;
		this->fullscreen  = fullscreen;
		//---------------------------------------------------------------
		//Creating Window
		if(!windowHandle)
		{
			this->window = new SPWindow(appHandle,"Soshiant 33 v 0.0.1",-1,-1,width,height);
			this->windowHandle = this->window->GetHandle();
			if(fullscreen)
				this->window->FullScreen();
		}
		else		
			this->windowHandle = windowHandle ;

		this->renderer = new SPRenderer(this->windowHandle,width,height);
		if(fullscreen)
			this->renderer->Fullscreen();

		this->renderer->SetLightEnable(true);
		this->renderer->SetAlphaTestEnable(true);
		this->renderer->SetAlphaBlendEnable(true);
		this->renderer->SetTextureSamplerEnabled(true);
		//this->renderer->SetFillMode(SPRenderer::FillMode_Wireframe);
		this->renderer->GetCamera()->Walk(-800);
		this->renderer->GetCamera()->Fly(10);
		//this->renderer->GetCamera()->Pitch(0.5f);

		//basePlane = SPResourceManager::GetMesh("basePlane.x");
	}	
	S33Engine::~S33Engine()
	{
		SAFE_DELETE(this->renderer);
		SAFE_DELETE(this->window);
	}
	void S33Engine::ReSize(unsigned int width,unsigned int height,bool resetBackbufferSize)
	{
		this->width = width;
		this->height = height;
		if(resetBackbufferSize)
			this->renderer->ResetBackBufferSize(width,height);
		else
			this->renderer->GetCamera()->SetCameraSize(width,height);		
	}	
	void S33Engine::Fullscreen(bool value)
	{
		this->fullscreen = value;
		if(this->window)
			this->window->FullScreen(value);
		this->renderer->Fullscreen(value);
	}
	void S33Engine::Render()
	{
		this->renderer->StartRendering();
		this->renderChilds();
		this->renderer->StopRendering();
	}	
	void S33Engine::SetWindowHandle(HWND handle)
	{
		this->windowHandle = handle;
		if(this->window)
			delete this->window;
		this->renderer->SetWindowHandle(handle);
	}
}
