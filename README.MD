# Soshiant 33 Game Engine

![](https://cdn.rawgit.com/sajjad-shirazy/Soshiant-33-Game-Engine-/f661e8e3/MSVS2008/ClassDiagram1.png)

## Dependencies
- Pei (https://github.com/sajjad-shirazy/Pei)
- Box2D
- Lua

## Usage
```c++
#include "../Soshiant33.h"
using namespace Soshiant33;

int main() {
	SPLoopManager loopman;
	loopman.AllowSleep(true);

	S33Engine engine;
	SPColor color;

	S33ScenePattern scenePattern(0,0,0,true,0);
	S33SpritePattern* spp = (S33SpritePattern*)scenePattern.library.AddLibMember("ScenePattern 001",S33LibMember::Type_SpritePattern);
	S33SpriteState* sps = (S33SpriteState*)spp->AddNewState("State 01");
	sps->AddNewKeyFrame("e:\\1.jpg");
	sps->AddNewKeyFrame("e:\\2.jpg");
	sps = spp->AddNewState("State 02");
	sps->AddNewKeyFrame("e:\\1.png");
	sps->AddNewKeyFrame("e:\\2.png");

	//scenePattern.LoadFromFile("ScenePattern.bin");

	S33Scene* scene = (S33Scene*)engine.AddChild(&scenePattern,0);
	S33Sprite* sprite = (S33Sprite*)scene->AddChild((S33SpritePattern*)scenePattern.library.GetLibMember(0),0);


	S33EntityParameters ep;
	ep.transform.position.x = 400;
	ep.transform.position.y = 300;
	float d = 0;

	while(!engine._window->IsWindowClosed())
	{
		loopman.BeginLoop();
		SPWindow::ProcessMessages();
		engine.Update();
		scene->backColor.Set(Math::Random()*255,0,0);
		if(sprite->currentState)
			sprite->currentState = 0;
		else
			sprite->currentState = 1;		
		loopman.EndLoop();
	}

	scenePattern.SaveToFile("ScenePattern.bin");
	return 0;
}
```
## Classes
- Soshiant33::S33ComplexEntity
- Soshiant33::S33DebugDraw
- Soshiant33::S33Engine
- Soshiant33::S33Entity
- Soshiant33::S33Entity::Types
- Soshiant33::S33Library
- Soshiant33::S33Scene
- Soshiant33::S33Sprite
- Soshiant33::S33JointPattern
- Soshiant33::S33ComplexEntityPatternChilds
- Soshiant33::S33ComplexEntityPattern
- Soshiant33::S33EntityPattern
- Soshiant33::S33EntityPattern::Types
- Soshiant33::S33EntityParameters
- Soshiant33::S33KeyFrame
- Soshiant33::S33ScenePattern
- Soshiant33::S33SpritePattern
- Soshiant33::S33SpriteState
