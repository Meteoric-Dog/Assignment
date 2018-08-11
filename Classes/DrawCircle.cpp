#include "DrawCircle.h"

DrawObject * DrawCircle::createObject(Vec2 m_InitialPosition, float m_fMass, 
	Vec2 m_Velocity, Color4F m_Color, float m_fRadius, float m_Angle)
{
	auto circle = DrawCircle::create();
	circle->SetValues(m_InitialPosition, m_fMass, m_Velocity, m_Color);
	circle->m_Angle = m_Angle;
	circle->m_fRadius = m_fRadius;
	return circle;
}

bool DrawCircle::init()
{
	if (!DrawObject::init()) {
		return false;
	}
	return true;
}

void DrawCircle::Render()
{
	int segment = 1000;
	Vec2 initialCenter(this->m_fRadius, this->m_fRadius);
	this->drawCircle(initialCenter, this->m_fRadius, this->m_Angle, segment, false, this->m_Color);
	this->setContentSize(Size(this->m_fRadius * 2, this->m_fRadius * 2));
	//char *value = new char[100];
	//sprintf(value, "%f %f", this->getBoundingBox().size.width, this->getBoundingBox().size.height);
	//CCLOG(value);
	//delete[] value;
}

void DrawCircle::InitPhysics()
{
	auto physicsBody = PhysicsBody::createCircle(this->m_fRadius, CIRCLE_MATERIAL);
	physicsBody->setGravityEnable(true);
	physicsBody->setDynamic(true);	
	physicsBody->setCollisionBitmask(COLLISION_MASK);        
	physicsBody->setContactTestBitmask(COLLISION_MASK);
	this->setPhysicsBody(physicsBody);
}

void DrawCircle::InitDisplay()
{
	this->Render();
	
	Vec2 anchorRoot(0.5, 0.5);
	this->setAnchorPoint(anchorRoot);
	this->ignoreAnchorPointForPosition(false);
	this->setPosition(this->m_InitialPosition.x + this->m_fRadius,
		this->m_InitialPosition.y + this->m_fRadius);

	this->InitPhysics();
}

void DrawCircle::SetVelocity(Vec2 velocity)
{
	this->m_Velocity.x = velocity.x;
	this->m_Velocity.y = velocity.y;
}

int DrawCircle::GetTag()
{
	return CIRCLE_TAG;
}
