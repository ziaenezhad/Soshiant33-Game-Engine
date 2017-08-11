#include "S33Sprite.h"
#include "S33Engine.h"
#include "S33Scene.h"
#include "S33ComplexEntity.h"

using namespace Pei::Utility;

namespace Soshiant33
{
	//----------------------------------------------------
	//Sprite Pattern
	S33SpritePattern::S33SpritePattern(const char* name)
		:S33EntityPattern(name,S33EntityPattern::Type_SpritePattern)
	{
		this->totalStates = 0;
		if(name)
		{	
			std::string path = S33Library::basePath + name;
			this->Load(path.c_str());
		}
		this->bodyDef.position.Set(0,0);
		this->bodyDef.type = b2_staticBody;
		this->bodyDef.angle = 0;
	}
	S33SpritePattern::~S33SpritePattern()
	{
		std::vector<b2FixtureDef*>::iterator fIter = this->fixtures.begin();
		while(fIter != this->fixtures.end())
			delete (*fIter++);
		std::vector<S33SpriteState*>::iterator sIter = this->states.begin();
		while(sIter != this->states.end())
			delete (*sIter++);	
	}
	S33SpriteState* S33SpritePattern::AddNewState(const char* name)
	{
		S33SpriteState* spriteState = new S33SpriteState(name);
		this->states.push_back(spriteState);
		this->totalStates ++;
		return spriteState;
	}	
	void S33SpritePattern::RemoveState(unsigned short index)
	{
		delete this->states[index];
		this->states.erase(this->states.begin()+index);
		this->totalStates --;
	}
	void S33SpritePattern::Render(S33Sprite* instance)
	{
		if(this->totalStates > instance->currentState)
		{
			this->states[instance->currentState]->Render(instance);
		}
		else
			instance->currentState--;//Error
	}
	void  S33SpritePattern::serialize(SPArchive& archive)
	{
		this->serializeBase_S33EntityPattern(archive);
		archive & this->bodyDef;
		archive & this->fixtures;		
		archive & this->totalStates;
		switch(archive.ioType)
		{
		case SPArchive::IO_Output:
			{
				std::vector<S33SpriteState*>::iterator iter = this->states.begin();
				while(iter != this->states.end())
					archive & (**iter++);
				break;
			}
		case SPArchive::IO_Input:
			{				
				for(int i = 0 ; i<this->totalStates ; i++)
				{
					S33SpriteState* state = new S33SpriteState(0);
					archive & (*state);
					this->states.push_back(state);
				}
				break;
			}
		}
		//MessageBox(0,String::ToString(this->states[0]->timeline[0]->subsetIndex).c_str(),"S33SpritePattern::serialize",0);
	}
	void S33SpritePattern::Save(const char *name)
	{
		this->name = Pei::Utility::File::Path::GetName(name);
		SPArchive archive(name,SPArchive::IO_Output);
		this->serialize(archive);
	}
	void S33SpritePattern::Load(const char* name)
	{
		SPArchive archive(name,SPArchive::IO_Input);
		this->serialize(archive);
	}
	//----------------------------------------------------
	//Sprite
	S33Sprite::S33Sprite(S33SpritePattern* spritePattern,S33EntityParameters* ep,S33ComplexEntity* parent)
		:S33Entity(spritePattern,ep,parent)
	{
		this->type = S33Entity::Type_Sprite;
		this->isPhysical = false;
		this->currentState = 0;
		if(spritePattern)
			this->init(spritePattern);
		else
			//Error
			errorHandler.PushError("S33Sprite::S33Sprite",this->ep.name.c_str(),"Creating a Sprite without Pattern !");
		
		this->body = this->scene->world->CreateBody(&spritePattern->bodyDef);
		this->body->SetUserData(this);


		/*b2PolygonShape dynamicBox;
		dynamicBox.SetAsBox(144.0f/S33Scene::meterPixelRatio/2,138.0f/S33Scene::meterPixelRatio/2);
		b2CircleShape circ;
		circ.m_radius = 144.0f/S33Scene::meterPixelRatio/2;
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;
		fixtureDef.density = 100.0f;
		fixtureDef.friction = 0.3f;
		fixtureDef.restitution = 0.1f;
		this->body->CreateFixture(&fixtureDef);*/
	}
	S33Sprite::~S33Sprite()
	{
		if(this->scene->world)
			this->scene->world->DestroyBody(this->body);
	}
	void S33Sprite::init(S33SpritePattern *spritePattern)
	{
		std::vector<b2FixtureDef*>::iterator iterator = spritePattern->fixtures.begin();
		while(iterator != spritePattern->fixtures.end())
		{
			this->body->CreateFixture((*iterator));
		}
	}

	void S33Sprite::Update()
	{
		if(this->isPhysical)
		{
			this->ep.position.x = this->body->GetPosition().x * S33Scene::meterPixelRatio;
			this->ep.position.y = this->body->GetPosition().y * S33Scene::meterPixelRatio;
			this->ep.rotation.z = this->body->GetAngle();
			//static float wh = 1;
			//((b2CircleShape*)this->m_fixtureList[0].GetShape())->m_radius +=0.01f;
		}
		this->ep.Transform(&parent->ep);
	}
	void S33Sprite::Render()
	{
		if(this->isPhysical)
			this->Update();
		((S33SpritePattern*)this->pattern)->Render(this);
	}
	S33Entity* S33Sprite::Pick(POINT* point)
	{
		if(((S33SpritePattern*)this->pattern)->states[this->currentState]->GetGraphic()->Pick(point,&this->ep))
			return this;
		else
			return 0;
	}
	
	void S33Sprite::SwitchState(unsigned short stateIndex)
	{
		this->currentState = stateIndex;
	}

	void S33Sprite::SwitchState(const char* name)
	{
		unsigned short size = ((S33SpritePattern*)this->pattern)->states.size();
		for(unsigned short i=0;i<size;i++)
		{
			if(!((S33SpritePattern*)this->pattern)->states[i]->name.compare(name))
			{
				this->SwitchState(i);
				break;
			}
		}
	}
}