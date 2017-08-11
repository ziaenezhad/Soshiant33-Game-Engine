#include "S33Sprite.h"
#include "S33Scene.h"
#include "S33Engine.h"
#include "S33ComplexEntity.h"
using namespace std;
namespace Soshiant33
{
	//----------------------------------------------------
	//Joint Pettern
	void S33JointPattern::serialize(SPArchive& archive)
	{
		archive & this->body1Name;
		archive & this->body2Name;
		archive & this->joint1Name;
		archive & this->joint2Name;
	}
	//----------------------------------------------------
	//Complex Entity Pattern
	void S33ComplexEntityPatternChilds::serialize(SPArchive& archive)
	{
		archive & this->ep;
		archive & this->patternName;
		archive & ((unsigned char&)this->patternType);
	}
	S33ComplexEntityPattern::S33ComplexEntityPattern(const char* name,S33EntityPattern::Types type):S33EntityPattern(name,type)
	{
		if(name && this->type == S33EntityPattern::Type_ComplexEntityPattern)
		{	
			std::string path = S33Library::basePath + name;
			this->Load(path.c_str());
		}
	}
	S33ComplexEntityPattern::~S33ComplexEntityPattern()
	{		
		std::vector<S33JointPattern*>::iterator jiter = this->joints.begin();
		while(jiter != this->joints.end())
			delete (*jiter++);
		std::vector<S33ComplexEntityPatternChilds*>::iterator  citer = this->childs.begin();
		while(citer != this->childs.end())
			delete (*citer++);
	}
	void S33ComplexEntityPattern::serializeBase_S33ComplexEntityPattern(SPArchive& archive)
	{
		this->serializeBase_S33EntityPattern(archive);
		archive & this->childs;
		archive & this->joints;
	}
	void S33ComplexEntityPattern::serialize(SPArchive& archive)
	{
		serializeBase_S33ComplexEntityPattern(archive);
	}
	void S33ComplexEntityPattern::Save(const char *name)
	{
		this->name = Pei::Utility::File::Path::GetName(name);
		SPArchive archive(name,SPArchive::IO_Output);
		this->serialize(archive);
	}
	void S33ComplexEntityPattern::Load(const char* name)
	{
		SPArchive archive(name,SPArchive::IO_Input);
		this->serialize(archive);
	}
	//----------------------------------------------------
	//Complex Entity
	S33ComplexEntity::S33ComplexEntity(S33ComplexEntityPattern* complexEntityDef,S33EntityParameters* ep,S33ComplexEntity* parent):S33Entity(complexEntityDef,ep,parent)
	{
		this->type = S33Entity::Type_ComplexEntity;
		if(complexEntityDef)
		{
			if(complexEntityDef->type == S33EntityPattern::Type_ComplexEntityPattern)
				this->init(complexEntityDef);
		}
	}

	S33ComplexEntity::~S33ComplexEntity()
	{
		this->childsIterator = this->childs.begin();
		while(this->childsIterator != this->childs.end())
		{
			S33Entity* entity = (*this->childsIterator);
			if(entity)
			{
				switch(entity->type)
				{
				case S33Entity::Type_Sprite:
					delete (S33Sprite*)(*this->childsIterator);
					break;
				case S33Entity::Type_ComplexEntity:
					delete (S33ComplexEntity*)(*this->childsIterator);
					break;
				case S33Entity::Type_Scene:
					delete (S33Scene*)(*this->childsIterator);
					break;
				}
			}
			this->childsIterator++;
		}
	}

	void S33ComplexEntity::init(S33ComplexEntityPattern *complexEntityDef)
	{
		//--------------------------------------------------------------------------------------
		//addin childs
		std::vector<S33ComplexEntityPatternChilds*>::iterator cIterator = complexEntityDef->childs.begin();
		while(cIterator != complexEntityDef->childs.end())
		{
			switch((*cIterator)->patternType)
			{
			case S33EntityPattern::Type_ScenePattern :
				this->childs.push_back(new S33Scene(S33Library::GetScenePattern((*cIterator)->patternName.c_str()),&(*cIterator)->ep,(S33Engine*)this));
				break;
			case S33EntityPattern::Type_SpritePattern :
				this->childs.push_back(new S33Sprite(S33Library::GetSpritePattern((*cIterator)->patternName.c_str()),&(*cIterator)->ep,this));
				break;
			case S33EntityPattern::Type_ComplexEntityPattern :
				this->childs.push_back(new S33ComplexEntity(S33Library::GetComplexEntityPattern((*cIterator)->patternName.c_str()),&(*cIterator)->ep,this));
				break;
			}
			cIterator++;
		}
		//------------------------------------------------------------------------------------
		//adding Joints
		std::vector<S33JointPattern*>::iterator jIterator = complexEntityDef->joints.begin();
		while(jIterator != complexEntityDef->joints.end())
		{
			//
			jIterator++;
		}
	}

	void S33ComplexEntity::Update()
	{
		if(parent)
			this->ep.Transform(&parent->ep) ;
		this->childsIterator = this->childs.begin();
		while(this->childsIterator != this->childs.end())
			(*this->childsIterator++)->Update();
	}
	void S33ComplexEntity::Render()
	{
		this->renderChilds();
	}

	void S33ComplexEntity::renderChilds()
	{
		this->childsIterator = this->childs.begin();
		while(this->childsIterator != this->childs.end())
		{
			S33Entity* entity = (*this->childsIterator);
			if(entity->isAlive)
			{
				if(entity->ep.visible)
					entity->Render();
			}
			else
			{
				this->childsIterator = this->childs.erase(this->childsIterator);
				switch(entity->type)
				{
				case S33Entity::Type_Sprite:
					delete (S33Sprite*)entity;
					break;
				case S33Entity::Type_ComplexEntity:
					delete (S33ComplexEntity*)entity;
					break;
				}
				if(this->childsIterator == this->childs.end())
					break;
				continue;
			}
			this->childsIterator++;
		}
	}

	S33Entity* S33ComplexEntity::AddChild(S33EntityPattern* pattern,S33EntityParameters* ep)
	{
		//MessageBox(0,"S33ComplexEntity::AddChild",0,0);
		S33Entity* child = 0;
		if(!ep)
			ep = new S33EntityParameters();
		switch(pattern->type)
		{
		case S33EntityPattern::Type_SpritePattern:
			child = new S33Sprite((S33SpritePattern*)pattern,ep,this);
			break;
		case S33EntityPattern::Type_ComplexEntityPattern:
			child = new S33ComplexEntity((S33ComplexEntityPattern*)pattern,ep,this);
			break;
		case S33EntityPattern::Type_ScenePattern:
			child = new S33Scene((S33ScenePattern*)pattern,ep,(S33Engine*)this);
			break;
		}
		if(child)
			this->childs.push_back(child);
		return child;
	}
	float S33ComplexEntity::GetDepth()
	{
		if(this->childs.size())
			return (*this->childs.begin())->ep.global_position.z;
		else
			return 0;
	}

	bool sortFunction (S33Entity* i,S33Entity* j) 
	{ 
		return (i->GetDepth() > j->GetDepth()); 
	}

	void S33ComplexEntity::SortChildsByDepth()
	{
		this->childs.sort(sortFunction);
	}
	S33Entity* S33ComplexEntity::Pick(POINT* point)
	{
		S33Entity* result = 0;
		this->childsIterator = this->childs.begin();
		while(this->childsIterator != this->childs.end())
		{
			S33Entity* temp = (*this->childsIterator)->Pick(point);
			if(temp)
				if(result)
				{
					if(temp->ep.global_position.z < result->ep.global_position.z)
						result = temp;
				}
				else
					result = temp;
			this->childsIterator++;
		}
		return result;
	}
	void S33ComplexEntity::SaveAsComplexEntityPattern(const char* name)
	{
		S33ComplexEntityPattern* pattern = new S33ComplexEntityPattern();
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

		SPArchive ar(name,SPArchive::IO_Output);
		pattern->serialize(ar);
	}
}