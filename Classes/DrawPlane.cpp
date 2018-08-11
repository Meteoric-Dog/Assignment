#include "DrawPlane.h"

DrawObject * DrawPlane::createObject(Vec2 m_InitialPosition, float m_fMass, Vec2 m_Velocity, Color4F m_Color, Vec2 m_OtherPoint)
{
	auto plane = DrawPlane::create();
	plane->SetValues(m_InitialPosition, m_fMass, m_Velocity, m_Color);
	plane->m_OtherPoint.x = m_OtherPoint.x;
	plane->m_OtherPoint.y = m_OtherPoint.y;
	return plane;
}

bool DrawPlane::init()
{
	if (!DrawObject::init()) {
		return false;
	}
	return true;
}

void DrawPlane::Render()
{
	Vec2 root(0, 0);
	Vec2 otherPoint(this->m_OtherPoint.x - this->m_InitialPosition.x, 
		this->m_OtherPoint.y - this->m_InitialPosition.y);
	this->drawLine(root, otherPoint, this->m_Color);
	this->setContentSize(Size(otherPoint.x, otherPoint.y));
}

void DrawPlane::InitDisplay()
{
	this->Render();
	
	Vec2 anchorRoot(0.5, 0.5);
	this->setAnchorPoint(anchorRoot);
	this->ignoreAnchorPointForPosition(false);
	this->setPosition(this->m_InitialPosition);
}

void DrawPlane::SetVelocity(Vec2 velocity)
{
	this->m_Velocity.x = velocity.x;
	this->m_Velocity.y = velocity.y;
}

int DrawPlane::GetTag()
{
	return PLANE_TAG;
}
