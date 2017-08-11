#ifndef _S33Scene_H
#define _S33Scene_H

#include "S33DebugDraw.h"
#include "S33ComplexEntity.h"
#include "Box2D/Box2DSerialization.h"

namespace Soshiant33
{
	//----------------------------------------------------
	//Scene Pattern
	class S33Scene ;
	class S33Engine;
	struct S33ScenePattern : S33ComplexEntityPattern 
	{
		friend class S33Scene;
		friend class S33Library;
		//S33Library*   library;
		//SPArchive*    archive;
		SPColor       backColor;
		b2Vec2        gravity;
		bool          doSleep;

		//void          SaveToFile(const char* filename);		
		//void          LoadFromFile(const char* filename);
		S33ScenePattern(const char* name = 0);
		void Save(const char* name);
		void Load(const char* name);
	protected:
		void serialize(SPArchive& archive);
	private:
		~S33ScenePattern(){}
	};
	//---------------------------------------------------
	//Scene
	class  S33Sprite;
	struct S33SpritePattern;
	class  S33DebugDraw;
	class S33Scene : public S33ComplexEntity 
	{		
		bool             paused ;
		SPTimer          timer;	
		S33DebugDraw     debugDraw;
	public:
		static unsigned char meterPixelRatio;
		unsigned int    velocityIteration;
		unsigned int    positionIteration;	
		unsigned int    timeStep;	
		SPColor         backColor;
		b2World*        world;

		S33Scene(S33ScenePattern* scenePattern,S33EntityParameters* ep,S33Engine* parent);
		~S33Scene();

		void        Render();
		void        Paly(){this->paused = false ; this->timer.Start();}
		void        Pause(){this->paused = true; this->timer.Pause();}
		
		void SaveAsScenePattern(const char* name);
	};
}
#endif