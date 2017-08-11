#include <Soshiant33.h>
#include <boost/tuple/tuple.hpp>

using namespace Soshiant33;
//using namespace Pei::Graphic;
//using namespace Pei::Utility;


int main() {
	SPLoopManager loopman;
	loopman.AllowSleep(true);
	S33ScenePattern* scenePattern = S33Library::GetScenePattern("01.sen");//new S33ScenePattern();
	S33Engine engine;//(1366,768,true);
	//scenePattern->name = "01.sen";
	S33Scene* scene = (S33Scene*)engine.AddChild(scenePattern,0);
	//S33SpritePattern* spritePattern = new S33SpritePattern();//S33Library::GetSpritePattern("test.sprt");
	//S33SpriteState* spriteState = spritePattern->AddNewState("State0");
	//spriteState->SetGraphic("SpriteSheet_06.x");
	//for(unsigned int i =0;i< spriteState->GetGraphic()->subsetsCount;i++)
	//	spriteState->AddKeyFrame(i);
	//spriteState->frameTimeLenght = 1000/150;
	//spritePattern->Save("Ptrn\\test.sprt");
	//spritePattern->states[0]->frameTimeLenght = 1000/1;
	//S33EntityParameters ep;
	//ep.position.z = 0;
	//for(int i=0;i<100;i++)
	//{
	//	ep.position.x = rand()%8600 - 300;
	//	ep.position.z = rand()%1860 - 600;
	//	ep.material.Set(1,Math::Random(),1,1);
	//	S33Sprite* sprite = (S33Sprite*)scene->AddChild(spritePattern,&ep);
	//}
	//scene->SortChildsByDepth();
	//scene->SaveAsScenePattern("Ptrn\\01.sen");


	float r = 0;
	while(!engine.GetWindow()->IsWindowClosed())
	{	
		loopman.BeginLoop();
		SPWindow::ProcessMessages();
		scene->Update();
		engine.Render();
		//scene->backColor.value ++;
		//sprite->ep.position.z-=sinf(r+=0.07f)*5;
		//sprite->ep.rotation.y=sinf(r)*1;
		engine.GetRenderer()->GetCamera()->Strafe(0.7f);
		engine.GetRenderer()->GetCamera()->Fly(sinf(r+=0.07f)*4);
		scene->ep.scale.x  = scene->ep.scale.y = sinf(r)/4+1.2f;
		loopman.EndLoop();
	}
	S33Library::RemoveItems(0);
	return 0;
}