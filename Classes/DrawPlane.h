#pragma once
#include"DrawObject.h"

#define PLANE_TAG 250
#define PLANE_MATERIAL PhysicsMaterial(1.0, 1.0, 0.1)

class DrawPlane :public DrawObject {
public:
	Vec2 m_OtherPoint;

public:
	static DrawObject * createObject(Vec2 m_InitialPosition,
		float m_fMass, Vec2 m_Velocity, Color4F m_Color, Vec2 m_OtherPoint);
	virtual bool init();
	virtual void Render();	
	virtual void InitDisplay();
	virtual void SetVelocity(Vec2 velocity);
	virtual int GetTag();

	CREATE_FUNC(DrawPlane);
};