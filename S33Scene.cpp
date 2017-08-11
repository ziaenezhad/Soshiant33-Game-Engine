#include "S33Scene.h"
#include "S33Engine.h"
#include "S33Sprite.h"
using namespace Pei::Utility;

namespace Soshiant33
{
	//----------------------------------------------------
	//Scene Pattern
	S33ScenePattern::S33ScenePattern(const char* name):S33ComplexEntityPattern(name,S33EntityPattern::Type_ScenePattern)
	{
		this->gravity.Set(0,-9.8f);
		this->backColor.Set(111,111,111);
		if(name)
		{	
			std::string path = S33Library::basePath + name;
			this->Load(path.c_str());
		}
		//this->library = new S33Library();
		//this->archive = 0;
	}
	/*void S33ScenePattern::SaveToFile(const char* filename)
	{
		archive = new SPArchive(filename,SPArchive::IO_Output);
		(*archive) & (*this);
		delete archive;
	}*/
	/*void S33ScenePattern::LoadFromFile(const char* filename)
	{
		archive = new SPArchive(filename,SPArchive::IO_Input);
		(*archive) & (*this);
		delete archive;
	}*/
	void S33ScenePattern::serialize(SPArchive& archive)
	{
		this->serializeBase_S33ComplexEntityPattern(archive);
		archive & this->backColor;
		archive & this->gravity;
		archive & this->doSleep;
	}
	void S33ScenePattern::Save(const char *name)
	{
		this->name = Pei::Utility::File::Path::GetName(name);
		SPArchive archive(name,SPArchive::IO_Output);
		this->serialize(archive);
	}
	void S33ScenePattern::Load(const char* name)
	{
		SPArchive archive(name,SPArchive::IO_Input);
		this->serialize(archive);
	}

	//---------------------------------------------------
	//Scene
	unsigned char    S33Scene::meterPixelRatio = 40;
	S33Scene::S33Scene(S33ScenePattern* scenePattern,S33EntityParameters* ep,S33Engine* parent)
		: S33ComplexEntity(scenePattern,ep,0)
		,debugDraw(((S33Engine*)parent)->GetRenderer())
	{		
		this->type = S33Entity::Type_Scene;
		//Phisics Initing

		/*b2BodyDef groundBodyDef;
		groundBodyDef.position.Set(0.0f, -10.0f);
		b2Body* groundBody = this->world->CreateBody(&groundBodyDef);
		b2PolygonShape groundBox;
		groundBox.SetAsBox(50.0f, 10.0f);
		groundBody->CreateFixture(&groundBox,0);*/
		//----------------------------------------------
		this->parent = parent;
		this->type = S33Entity::Type_Scene;
		this->timer.Start();
		this->timeStep = timeGetTime();	
		this->velocityIteration = 6;
		this->positionIteration = 2;
		this->backColor = scenePattern->backColor;
		this->paused = false;
		this->ep.name = "sajjad";
		this->world = new b2World(scenePattern->gravity,scenePattern->doSleep);
		this->world->SetDebugDraw(&this->debugDraw);
		uint32 flags = 0;
		flags += b2DebugDraw::e_shapeBit;
		flags += b2DebugDraw::e_jointBit;
		//flags += b2DebugDraw::e_aabbBit;
		flags += b2DebugDraw::e_pairBit;
		flags += b2DebugDraw::e_centerOfMassBit;
		this->debugDraw.SetFlags(flags);
		this->ep.Transform(&parent->ep);

		
		if(scenePattern)
			this->init(scenePattern);
	}
	S33Scene::~S33Scene()
	{
		SAFE_DELETE(this->world);
	}
	void S33Scene::Render()
	{
		if(this->paused)
			this->timeStep = 0;
		else
			this->timeStep = timeGetTime() - this->timeStep;//this->timer.GetTimePassedFromMemory();
		((S33Engine*)this->parent)->GetRenderer()->ClearBackBuffer(&this->backColor);

		this->world->Step(this->timeStep/1000.0f,this->velocityIteration,this->positionIteration);
		this->renderChilds();
		this->world->DrawDebugData();
		this->timeStep = timeGetTime();
	}
	void S33Scene::SaveAsScenePattern(const char* name)
	{
		S33ScenePattern* pattern = new S33ScenePattern();
		pattern->name = this->ep.name + "_Pattern";
		this->childsIterator = this->childs.begin();
		while(this->childsIterator != this->childs.end())
		{
			S33ComplexEntityPatternChilds* child = new S33ComplexEntityPatternChilds();
			child->ep = (*this->childsIterator)->ep;
			child->patternName = (*this->childsIterator)->pattern->name;
			child->patternType = (*this->childsIterator)->pattern->type;
			pattern->childs.push_back(child);
			this->childsIterator++;
		}

		// Filling Joints
		pattern->script = this->pattern->script;
		pattern->type = this->pattern->type;

		pattern->backColor = this->backColor;
		pattern->doSleep = ((S33ScenePattern*)this->pattern)->doSleep;
		pattern->gravity = ((S33ScenePattern*)this->pattern)->gravity;

		SPArchive ar(name,SPArchive::IO_Output);
		pattern->serialize(ar);
	}
	
}