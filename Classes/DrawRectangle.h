#pragma once
#include"DrawObject.h"

USING_NS_CC;

#define RECT_MARK 1
#define RECT_MATERIAL PhysicsMaterial(1.0, 1.0, 0.1)

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
	virtual void InitPhysics();
	virtual void InitDisplay();
	virtual void SetVelocity(Vec2 velocity);
	virtual int GetMark();

	CREATE_FUNC(DrawRectangle);
};