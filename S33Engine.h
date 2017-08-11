#ifndef _S33Engine_H
#define _S33Engine_H

#include "S33Library.h"
#include "S33ComplexEntity.h"

using namespace Pei::Graphic;
using namespace Pei::Utility;

namespace Soshiant33
{
	extern HINSTANCE appHandle;
	class S33Engine : public S33ComplexEntity
	{
		//-------------------------------------------------
		//Resource Related
		SPRenderer*                   renderer;
		SPLoopManager                 loopMan;
		unsigned int                  width;
		unsigned int                  height;
		SPWindow *                    window;
		SPTimer                       timer;
		HWND                          windowHandle;
		bool                          fullscreen;
		bool                          alive;
		
		//SPRenderingParameters basePlane_rp;
		//SPMesh* basePlane;

	public:
		static S33Library* shareLibrary;

		S33Engine(unsigned int width = 800,unsigned int height = 600,bool fullscreen = false,HWND windowHandle = 0);
		~S33Engine();

		void        Render();
		void        ReSize(unsigned int width,unsigned int height,bool resetBackbufferSize = false);
		void        Fullscreen(bool value);
		bool        IsAlive(){return this->alive;}
		double      GetFPS(){return this->loopMan.GetPPS();}
		void        SetMaxFPS(unsigned short value){this->loopMan.AllowSleep(true,value);}
		void        SetWindowHandle(HWND handle);
		inline SPWindow*   GetWindow(){return this->window;}
		inline SPRenderer* GetRenderer(){return this->renderer;}

	};
}
#endif