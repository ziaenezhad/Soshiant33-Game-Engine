#ifndef _Box2DSerialization_H
#define _Box2DSerialization_H

#include "../ExternalLibs.h"

namespace Pei
{
	namespace Utility
	{
		void Serialize(SPArchive & ar,b2Vec2 & vec);
		void Serialize(SPArchive & ar,b2Filter & filter);
		void Serialize(SPArchive & ar,b2BodyDef & body);
        void Serialize(SPArchive & ar,b2FixtureDef & fixture);
	}
}
#endif