#pragma once
#include"DrawObject.h"

USING_NS_CC;

class DrawRectangle :public DrawObject {
public:
	Size m_Size;

public:
	DrawRectangle();
	DrawRectangle(const DrawRectangle &rectangle);

public:
	static DrawObject* createObject(Vec2 m_InitialPosition, float m_fMass, Vec2 m_Velocity, Color4F m_Color, Size m_Size);
	virtual bool init();
	virtual void Render();
	virtual void InitDisplay();
	virtual void SetVelocity(Vec2 velocity);

	CREATE_FUNC(DrawRectangle);
};