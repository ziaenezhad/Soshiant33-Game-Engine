#include "S33Script.h"

namespace Soshiant33
{
	S33Script::S33Script()
	{
		this->owner = 0;
		this->luaScript = 0;
	}
	S33Script::~S33Script()
	{
		if(this->luaScript)			
			lua_close(this->luaScript);
	}
	void S33Script::Set(std::string *text)
	{
		if(text)
		{
			if(this->luaScript)
				lua_close(this->luaScript);
			if(text->length() > 0)
			{
				this->luaScript = lua_open();
				luaL_dostring(this->luaScript,text->c_str());
			}
			else
				this->luaScript = 0;
		}
		else
			this->luaScript = 0;
	}
}