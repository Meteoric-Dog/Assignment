#pragma once
#include"cocos2d.h"

USING_NS_CC;

#define OBJECT_TAG 100
#define COLLISION_MASK 0x1001

class DrawObject :public DrawNode {
public:
	Vec2 m_InitialPosition;
	float m_fMass;
	Vec2 m_Velocity;
	Color4F m_Color;
	ParticleSystem *particle;
	int m_iContactCount;

public:
	DrawObject();
	DrawObject(const DrawObject &object);

public:
	virtual bool init();
	virtual int getTag();

	virtual void Render();
	virtual void InitPhysics();
	virtual void InitDisplay();
	virtual void SetVelocity(Vec2 velocity);
	virtual void startParticle();
	virtual void stopParticle();

	void ChangeColor(const Color4F &color);
	void SetValues(Vec2 m_InitialPosition, float m_fMass, Vec2 m_Velocity, Color4F m_Color);

	CREATE_FUNC(DrawObject);
};