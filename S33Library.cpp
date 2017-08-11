#include "S33Library.h"
#include "S33Scene.h"
#include "S33Sprite.h"

using namespace Pei::Utility;

namespace Soshiant33
{
	S33ScenePattern* lastScenePattern = 0;
	S33SpritePattern* lastSpritePattern = 0;
	S33ComplexEntityPattern* lastComplexEntityPattern = 0;
	std::string S33Library::basePath = "Ptrn\\";
	unsigned char S33Library::itemsGroupID = 0;

	S33ScenePattern* S33Library::GetScenePattern(const char *name)
	{
		if(name)
		{			
			S33ScenePattern* current = lastScenePattern;
			while(current)
			{
				if(current->name.compare(name) == 0)
					return current;
				current = (S33ScenePattern*)current->prev;
			}
			return new S33ScenePattern(name);
		}
		return 0;
	}

	S33SpritePattern* S33Library::GetSpritePattern(const char *name)
	{
		if(name)
		{				
			S33SpritePattern* current = lastSpritePattern;
			while(current)
			{
				if(current->name.compare(name) == 0)
					return current;
				current = (S33SpritePattern*)current->prev;
			}
			return new S33SpritePattern(name);
		}
		return 0;
	}

	S33ComplexEntityPattern* S33Library::GetComplexEntityPattern(const char *name)
	{
		if(name)
		{			
			S33ComplexEntityPattern* current = lastComplexEntityPattern;
			while(current)
			{
				if(current->name.compare(name) == 0)
					return current;
				current = (S33ComplexEntityPattern*)current->prev;
			}
			return new S33ComplexEntityPattern(name);
		}
		return 0;
	}

	void S33Library::RemoveItems(unsigned char itemsGroupID)
	{
		
		S33EntityPattern* current = lastScenePattern;
		while(current)
		{
			if(current->itemGroupID == itemsGroupID)
			{
				if(current->next)
					current->next->prev = current->prev;
				if(current->prev)
					current->prev->next = current->next;
				S33ScenePattern* temp = (S33ScenePattern*)current;
				current = current->prev;
				delete temp;
				continue;
			}
			current = current->prev;
		}
		
		current = lastSpritePattern;
		while(current)
		{
			if(current->itemGroupID == itemsGroupID)
			{
				if(current->next)
					current->next->prev = current->prev;
				if(current->prev)
					current->prev->next = current->next;
				S33SpritePattern* temp = (S33SpritePattern*)current;
				current = current->prev;
				delete temp;
				continue;
			}
			current = current->prev;
		}
		
		current = lastComplexEntityPattern;
		while(current)
		{
			if(current->itemGroupID == itemsGroupID)
			{
				if(current->next)
					current->next->prev = current->prev;
				if(current->prev)
					current->prev->next = current->next;
				S33ComplexEntityPattern* temp = (S33ComplexEntityPattern*)current;
				current = current->prev;
				delete temp;
				continue;
			}
			current = current->prev;
		}
	}
	
}