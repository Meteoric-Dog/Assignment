#pragma once
#include"cocos2d.h"
#include"DrawObject.h"

USING_NS_CC;

#define CIRCLE_TAG 200
#define CIRCLE_MATERIAL PhysicsMaterial(1.0, 1.0, 0.1)
#define CIRCLE_PARTICLE_SPEED 4.0
#define CIRCLE_PARTICLE_SCALE 2.0

class DrawCircle :public DrawObject {
public:
	float m_fRadius, m_Angle;

public:
	static DrawObject *createObject(Vec2 m_InitialPosition, float m_fMass, 
		Vec2 m_Velocity, Color4F m_Color, float m_fRadius, float m_Angle);
	virtual bool init();
	virtual int getTag();

	virtual void Render();
	virtual void InitParticle();
	virtual void InitPhysics();
	virtual void InitDisplay();
	virtual void SetVelocity(Vec2 velocity);
	virtual void startParticle();
	virtual void stopParticle();

	CREATE_FUNC(DrawCircle);
};