#ifndef _S33Script_H
#define _S33Script_H

#include "ExternalLibs.h"

namespace Soshiant33
{
	class S33Entity;
	struct S33Script
	{
		lua_State* luaScript;
		S33Entity* owner;
		S33Script();
		~S33Script();
		void Set(std::string* text);
	};
}
#endif