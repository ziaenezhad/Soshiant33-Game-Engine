#include "Box2DSerialization.h"

namespace Pei
{
	namespace Utility
	{
		//-----------------------------------------------------------------------------------------
		void Serialize(SPArchive & ar,b2Vec2 & vec)
		{
			ar & vec.x;
			ar & vec.y;
		}
		//-----------------------------------------------------------------------------------------
		void Serialize(SPArchive & ar,b2Filter & filter)
		{
			ar & filter.categoryBits;
			ar & filter.groupIndex;
			ar & filter.maskBits;
		}
		//-----------------------------------------------------------------------------------------
		void Serialize(SPArchive & ar,b2BodyDef & body)
		{
			ar & body.active;
			ar & body.allowSleep;
			ar & body.angle;
			ar & body.angularDamping;
			ar & body.angularVelocity;
			ar & body.awake;
			ar & body.bullet;
			ar & body.fixedRotation;
			ar & body.inertiaScale;
			ar & body.linearDamping;
			ar & body.linearVelocity;
			ar & body.position;
			SERIALIZE_ENUM(ar,b2BodyType,body.type);
		}
		//-----------------------------------------------------------------------------------------
        void Serialize(SPArchive & ar,b2FixtureDef & fixture)
        {			
			ar & fixture.density;
			ar & fixture.filter;
			ar & fixture.friction;
			ar & fixture.isSensor;
			ar & fixture.restitution;
			ar & fixture.density;

			bool hasShape = false;
			if(fixture.shape)
				hasShape = true;
			ar & hasShape;
			if(hasShape)
			{
				switch(ar.ioType)
				{
				case SPArchive::IO_Output:
					{
						SERIALIZE_ENUM(ar,b2Shape::Type,(b2Shape::Type)fixture.shape->m_type);
						switch(fixture.shape->m_type)
						{
						case b2Shape::e_circle:
							ar.SaveBinary((void*)fixture.shape,sizeof(b2CircleShape));
							break;
						case b2Shape::e_polygon:
							ar.SaveBinary((void*)fixture.shape,sizeof(b2PolygonShape));
							break;
						}
					}
				case SPArchive::IO_Input:
					{
						b2Shape::Type type = b2Shape::e_unknown;
						SERIALIZE_ENUM(ar,b2Shape::Type,type);
						switch(type)
						{
						case b2Shape::e_circle:
							{
								b2CircleShape* shape = new b2CircleShape();
								ar.LoadBinary(shape,sizeof(b2CircleShape));
								fixture.shape = shape;
								break;
							}
						case b2Shape::e_polygon:
							{
								b2PolygonShape* shape = new b2PolygonShape();
								ar.LoadBinary(shape,sizeof(b2PolygonShape));
								fixture.shape = shape;
								break;
							}
						}
					}
				}
			}
		}
	}
}