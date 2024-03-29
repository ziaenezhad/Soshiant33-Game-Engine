#ifndef _S33Sprite_H
#define _S33Sprite_H

#include "S33Entity.h"
#include "S33SpriteState.h"
#include "Box2D/Box2DSerialization.h"

namespace Soshiant33
{
	//----------------------------------------------------
	//Sprite Pattern
	class  S33Sprite;
	struct S33SpritePattern : public S33EntityPattern
	{
		friend class S33Library;
	protected:
		void serialize(SPArchive& archive);
	public:
		void Save(const char* name);
		void Load(const char* name);
		b2BodyDef                     bodyDef;
		unsigned short                totalStates;
		std::vector<b2FixtureDef*>    fixtures;
		std::vector<S33SpriteState*>  states;

		S33SpritePattern(const char* name = 0);

		void             Render(S33Sprite* instance);
		void             RemoveState(unsigned short index);
		S33SpriteState*  AddNewState(const char* name);
	private:
		~S33SpritePattern();

	};
	//----------------------------------------------------
	//Sprite
	/// موجودیت نهایی قابل ترسیم در صحنه
	/// هرموجودیت از چند وضعیت تشکیل شده که در هرلحظه توسط وضعیت جاری بروزرسانی و ترسیم می شود
	class S33Sprite : public S33Entity
	{	
		friend class S33Scene;
		friend struct S33SpriteState;
		void init(S33SpritePattern* spriteDef);		
	public:
		bool           isPhysical;
		b2Body*        body;
		unsigned short currentState;

		S33Sprite(S33SpritePattern* spritePattern,S33EntityParameters* ep,S33ComplexEntity* parent);
		~S33Sprite();

		void Render();
		void Update();
		S33Entity* Pick(POINT* point);
		/// تغییر به وضعیت جدید
		void SwitchState(unsigned short stateIndex);
		void SwitchState(const char* name);
	};
}
#endif