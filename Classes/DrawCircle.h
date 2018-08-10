#pragma once
#include"cocos2d.h"
#include"DrawObject.h"

USING_NS_CC;

class DrawCircle :public DrawObject {
public:
	float m_fRadius, m_Angle;

public:
	static DrawObject *createObject(Vec2 m_InitialPosition, float m_fMass, 
		Vec2 m_Velocity, Color4F m_Color, float m_fRadius, float m_Angle);
	virtual bool init();
	virtual void Render();
	virtual void InitDisplay();
	virtual void SetVelocity(Vec2 velocity);

	CREATE_FUNC(DrawCircle);
};