#include <Soshiant33.h>

#pragma comment(lib, "Pei_d.lib")
#pragma comment(lib, "Soshiant33_d.lib")
#pragma comment(lib, "lua5.1.lib")
#pragma comment(lib, "Box2d_d.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")

using namespace Soshiant33;

int main() {
	SPLoopManager loopman;
	loopman.AllowSleep(true);
	S33Engine engine;//(1366,768,true);

	//با استفاده از یک الگوی صحنه می توانیم به تعداد از آن نمونه سازی سازی کنیم
	// یک الگوی صخنه می تواند از روی فایل بارگزاری شود
	S33ScenePattern* scenePattern = new S33ScenePattern();
	scenePattern->name = "01.sen";
	//این صحنه نمونه ای است که الگوی صحنه بالا ساخته شده.
	//و به موتور اضافه شده و بعد از این توسط موتور به روز رسانی خواهد شد.
	S33Scene* scene = (S33Scene*)engine.AddChild(scenePattern,0);

	// با استفاده از یک الگوی اسپرایت می توانیم به تعداد از روی آن نمونه سازی کنیم.
	// یک الگوی اسپرایت می تواند از روی فایل بارگزاری شود
	S33SpritePattern* spritePattern = new S33SpritePattern();//S33Library::GetSpritePattern("test.sprt");
	// هر اسپرایت می تواند چند وضعیت داشته باشد که توسط وضعیت جاری به روز رسانی و ترسیم می شود
	S33SpriteState* spriteState = spritePattern->AddNewState("State0");
	// هر وضعیت اسپرایت یک گرافیک دارد که می تواند انیمیشن دو بعدی یا پارتیکل یا مش یه بعدی باشد
	spriteState->SetGraphic("SpriteSheet_06.x");
	// هر وضعیت اسپرایت یک تایم لاین دارد. تایم لاین آرایه ای از فریم هاست
	for(unsigned int i =0;i< spriteState->GetGraphic()->subsetsCount;i++)
		spriteState->AddKeyFrame(i);
	spriteState->frameTimeLenght = 1000/150;
	//می شود یک الگوی اسپرایت را ذخیره کرد
	spritePattern->Save("Ptrn\\test.sprt");
	spritePattern->states[0]->frameTimeLenght = 1000/1;
	//مولفه های یک موجودیت : موقعیت ، چرخش ، مد ترکیب ، شفافیت ، رنگ و...
	S33EntityParameters ep;
	ep.position.z = 0;
	for(int i=0;i<50;i++)
	{
		ep.position.x = rand()%8600 - 300;
		ep.position.z = rand()%1860 - 600;
		ep.material.Set(1,Math::Random(),1,1);
		S33Sprite* sprite = (S33Sprite*)scene->AddChild(spritePattern,&ep);
	}
	// بار گزاری یک الگوی اسپرایت جدید از فایل و نمونه یازس از آن
	spritePattern = S33Library::GetSpritePattern("SpritePatern2.sprt");
	spritePattern->states[0]->frameTimeLenght = 200;
	for(int i=0;i<50;i++)
	{
		ep.position.x = rand()%8600 - 300;
		ep.position.z = rand()%1860 - 600;
		ep.material.Set(1,Math::Random(),1,1);
		S33Sprite* sprite = (S33Sprite*)scene->AddChild(spritePattern,&ep);
	}
	// برای ترکیب کانال آلفا باید موجودیت ها به ترتیب عمق ترسیم شوند
	scene->SortChildsByDepth();
	// می شود یک الگوی صحنه را ذخیره کرد
	// مشکل : نرخ فریم مشکل دارد
	scene->SaveAsScenePattern("Ptrn\\01.sen");
	float r = 0;
	while(!engine.GetWindow()->IsWindowClosed())
	{
		loopman.BeginLoop();
		SPWindow::ProcessMessages();
		engine.Update();
		engine.Render();

		engine.GetRenderer()->GetCamera()->Strafe(0.7f);
		engine.GetRenderer()->GetCamera()->Fly(sinf(r+=0.07f)*4);
		//scene->ep.scale.x = scene->ep.scale.y = sinf(r)/4+1.2f;

		loopman.EndLoop();
	}
	//حذف پایین ترین سطح منابع کتابخانه
	//سطح رزرو شده برای موتور
	S33Library::RemoveItems(0);
	return 0;
}