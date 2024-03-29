#include <Soshiant33.h>

#pragma comment(lib, "Pei_d.lib")
#pragma comment(lib, "lua5.1.lib")
#pragma comment(lib, "Box2d_d.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")

using namespace Soshiant33;

int main()
{
	S33Engine engine;//(1366,768,true);
	engine.GetRenderer()->GetCamera()->Walk(-1000);
	S33ScenePattern* scenePattern = new S33ScenePattern();
	scenePattern->name = "01.sen";
	S33Scene* scene = (S33Scene*)engine.AddChild(scenePattern,0);
	S33SpritePattern* spritePattern = new S33SpritePattern();

	//----------------
	//تعریف تنه فیزیکی
	//----------------
	spritePattern->bodyDef.position.Set(0,0);// موقعیت اولیه
	spritePattern->bodyDef.type = b2_dynamicBody;// نوع تنه : به داکیومنت باکس تو دی مراجعه کنید
	spritePattern->bodyDef.angle = 0;// زاویه چرخش اولیه
	//----------------------------------------------------------------------

	S33SpriteState* spriteState = spritePattern->AddNewState("State0");
	spriteState->SetGraphic("SpriteSheet_06.x");
	for(unsigned int i =0;i< spriteState->GetGraphic()->subsetsCount;i++)
		spriteState->AddKeyFrame(i);
	spriteState->frameTimeLenght = 1000/45;

	S33EntityParameters ep;
	ep.position.z = 0;
	S33Sprite* sprite = (S33Sprite*)scene->AddChild(spritePattern,&ep);

	//----------------------------------
	//تعریف شکل و سایر جزئیات تنه فیزیکی
	//----------------------------------
	sprite->isPhysical = true;//اگر فالس باشد مشخصات تنه با اسپرایت در صدا ردن متد آپدیت تنظیم نمی شود
	sprite->body->SetTransform(b2Vec2(0,15),(float)Math::PI /5.0f);
	b2PolygonShape box;
	box.SetAsBox(144.0f/S33Scene::meterPixelRatio/2,138.0f/S33Scene::meterPixelRatio/2);
	//b2CircleShape circle;
	//circle.m_radius = 144.0f/S33Scene::meterPixelRatio/2;
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &box;
	fixtureDef.density = 100.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.1f;
	sprite->body->CreateFixture(&fixtureDef);
	//-------------------------------------

	while(!engine.GetWindow()->IsWindowClosed())
	{
		SPWindow::ProcessMessages();
		engine.Update();
		engine.Render();
	}
	S33Library::RemoveItems(0);
	return 0;
}
