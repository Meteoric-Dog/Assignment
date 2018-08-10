#pragma once
#include"cocos2d.h"

USING_NS_CC;

#define OBJECT_MARK 0

class DrawObject :public DrawNode {
public:
	Vec2 m_InitialPosition;
	float m_fMass;
	Vec2 m_Velocity;
	Color4F m_Color;

public:
	DrawObject();
	DrawObject(const DrawObject &object);

public:
	virtual bool init();
	virtual void Render();
	virtual void InitDisplay();
	virtual void SetVelocity(Vec2 velocity);
	virtual int GetMark();

	void ChangeColor(const Color4F &color);
	void SetValues(Vec2 m_InitialPosition, float m_fMass, Vec2 m_Velocity, Color4F m_Color);

	CREATE_FUNC(DrawObject);
};