#pragma once
#include"cocos2d.h"
#include"DrawObject.h"

USING_NS_CC;

#define CIRCLE_MARK 2
#define CIRCLE_MATERIAL PhysicsMaterial(1.0, 1.0, 0.1)

class DrawCircle :public DrawObject {
public:
	float m_fRadius, m_Angle;

public:
	static DrawObject *createObject(Vec2 m_InitialPosition, float m_fMass, 
		Vec2 m_Velocity, Color4F m_Color, float m_fRadius, float m_Angle);
	virtual bool init();
	virtual void Render();
	virtual void InitPhysics();
	virtual void InitDisplay();
	virtual void SetVelocity(Vec2 velocity);
	virtual int GetMark();

	CREATE_FUNC(DrawCircle);
};