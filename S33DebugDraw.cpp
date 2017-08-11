#include "S33Scene.h"
#include "S33DebugDraw.h"

namespace Soshiant33
{
	SPVector3 B2Vec22SPVector3(const b2Vec2* vector)
	{
		return SPVector3(vector->x*S33Scene::meterPixelRatio,vector->y*S33Scene::meterPixelRatio,0);
	}
	SPColor   B2Color2SPColor(const b2Color* color)
	{
		return SPColor((unsigned char)(color->r*255),(unsigned char)(color->g*255),(unsigned char)(color->b*255));
	}
	void S33DebugDraw::DrawPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color)
	{
		SPVector3 moveTo = B2Vec22SPVector3((b2Vec2*)&vertices[0]);
		SPColor   lineColor = B2Color2SPColor((b2Color*)&color);
		SPVector3 lineTo ;

		for(int i=1; i < vertexCount;i++)
		{
			lineTo = B2Vec22SPVector3((b2Vec2*)&vertices[i]);
			this->gfxProvider->DrawLine(&moveTo,&lineTo,&lineColor);
			moveTo = lineTo ;
		}
		this->gfxProvider->DrawLine(&moveTo,&B2Vec22SPVector3((b2Vec2*)&vertices[0]),&lineColor);

	}
	void S33DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
	{
		this->DrawPolygon(vertices,vertexCount,color);
	}
	void S33DebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
	{
		this->DrawCircle(center,radius,color);
	}
	void S33DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
	{
		this->gfxProvider->DrawLine(&B2Vec22SPVector3(&p1),&B2Vec22SPVector3(&p2),&B2Color2SPColor((b2Color*)&color));
	}
	void S33DebugDraw::DrawTransform(const b2Transform& xf)
	{
		
	}
	void S33DebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
	{
		this->gfxProvider->DrawRegularPolygon(&B2Vec22SPVector3(&center),radius*S33Scene::meterPixelRatio,0,12,&B2Color2SPColor((b2Color*)&color));
	}
}