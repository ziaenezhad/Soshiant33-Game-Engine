#include "S33Scene.h"
#include "S33Sprite.h"
#include "S33ComplexEntity.h"

namespace Soshiant33
{
	extern S33ScenePattern* lastScenePattern;
	extern S33SpritePattern* lastSpritePattern;
	extern S33ComplexEntityPattern* lastComplexEntityPattern;
	//----------------------------------------------------
	//Entity Pattern :
	S33EntityPattern::S33EntityPattern(const char* name,Types type)
	{
		//MessageBox(0,"after load",0,0);
		this->type = type;
		std::string path = "";
		if(name)
			this->name = name;	
		this->itemGroupID = S33Library::itemsGroupID;
		switch(type)
		{
		case Type_SpritePattern :
			if(lastSpritePattern)
				lastSpritePattern->next = (S33SpritePattern*)this;
			this->prev = lastSpritePattern;
			lastSpritePattern = (S33SpritePattern*)this;
			this->next = 0;
			break;
		case Type_ComplexEntityPattern :
			if(lastComplexEntityPattern)
				lastComplexEntityPattern->next = (S33ComplexEntityPattern*)this;
			this->prev = lastComplexEntityPattern;
			lastComplexEntityPattern = (S33ComplexEntityPattern*)this;
			this->next = 0;
			break;
		case Type_ScenePattern :				
			if(lastScenePattern)
				lastScenePattern->next = (S33ScenePattern*)this;
			this->prev = lastScenePattern;
			lastScenePattern = (S33ScenePattern*)this;
			this->next = 0;
			break;
		}
		this->script.clear();
	}
	void S33EntityPattern::serializeBase_S33EntityPattern(SPArchive& archive)
	{
		archive & this->name;
		archive & this->script;
		SERIALIZE_ENUM(archive,S33EntityPattern::Types,this->type);
	}
	//----------------------------------------------------
	//Entity Parameters
	S33EntityParameters::S33EntityParameters()
	{
		this->name = "who.am.i[Entity]";
	}
	void S33EntityParameters::serialize(SPArchive& archive)
	{
		this->serializeBase_SPRenderingParameters(archive);
		archive & this->name;
	}
	//----------------------------------------------------
	//Entity
	S33Entity::S33Entity(S33EntityPattern* entityPattern,S33EntityParameters* ep,S33ComplexEntity* parent)
	{
		this->isAlive = true;
		this->parent  = parent;
		if(!parent)
			this->scene = (S33Scene*)this;
		else
			this->scene = parent->scene;
		this->pattern = entityPattern;
		if(ep)
			this->ep = (*ep);
		if(parent)
			this->ep.Transform(&parent->ep);
		else
			this->ep.Transform();
		this->script.owner = this;
		if(entityPattern)
			this->script.Set(&entityPattern->script);
	}
	S33Entity::~S33Entity()
	{
	}

}