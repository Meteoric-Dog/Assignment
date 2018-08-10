#include "DrawObject.h"

DrawObject::DrawObject()
{
	DrawNode::DrawNode();
	this->m_InitialPosition = *(new Vec2(0, 0));
	m_fMass = 0;
	this->m_Velocity = *(new Vec2(0, 0));
	this->m_Color = Color4F::WHITE;
}

DrawObject::DrawObject(const DrawObject & object)
{
	//this->m_InitialPosition = object.m_InitialPosition;
	this->m_InitialPosition.x = object.m_InitialPosition.x;
	this->m_InitialPosition.y = object.m_InitialPosition.y;
	this->m_fMass = object.m_fMass;
	//this->m_Velocity = object.m_Velocity;
	this->m_Velocity.x = object.m_Velocity.x;
	this->m_Velocity.y = object.m_Velocity.y;
	//this->m_Color = object.m_Color;
	this->m_Color.r = object.m_Color.r;
	this->m_Color.g = object.m_Color.g;
	this->m_Color.b = object.m_Color.b;
	this->m_Color.a = object.m_Color.a;
}

bool DrawObject::init()
{
	if (!DrawNode::init()) {
		return false;
	}
	return true;
}

void DrawObject::Render()
{
}

void DrawObject::InitDisplay()
{
}

void DrawObject::SetVelocity(Vec2 velocity)
{
}

int DrawObject::GetMark()
{
	return OBJECT_MARK;
}

void DrawObject::ChangeColor(const Color4F & color)
{
	this->m_Color = color;
	this->Render();
}

void DrawObject::SetValues(Vec2 m_InitialPosition, float m_fMass, Vec2 m_Velocity, Color4F m_Color)
{
	this->m_InitialPosition.x = m_InitialPosition.x;
	this->m_InitialPosition.y = m_InitialPosition.y;

	this->m_fMass = m_fMass;

	this->m_Velocity.x = m_Velocity.x;
	this->m_Velocity.y = m_Velocity.y;

	this->m_Color.r = m_Color.r;
	this->m_Color.g = m_Color.g;
	this->m_Color.b = m_Color.b;
	this->m_Color.a = m_Color.a;
}

