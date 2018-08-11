#include "DrawRectangle.h"


DrawRectangle::DrawRectangle()
{
}

DrawRectangle::DrawRectangle(const DrawRectangle & rectangle) :DrawObject(rectangle), m_Size(m_Size)
{
}

DrawObject * DrawRectangle::createObject(Vec2 m_InitialPosition, float m_fMass, Vec2 m_Velocity, Color4F m_Color, Size m_Size)
{
	auto retangle = DrawRectangle::create();
	retangle->SetValues(m_InitialPosition, m_fMass, m_Velocity, m_Color);
	retangle->m_Size = *(new Size(m_Size));
	return retangle;
}

bool DrawRectangle::init()
{
	if (!DrawObject::init()) {
		return false;
	}
	return true;
}

void DrawRectangle::Render()
{
	Vec2 root(0, 0);
	this->drawRect(root, this->m_Size, this->m_Color);
	this->setContentSize(this->m_Size);
}

void DrawRectangle::InitPhysics()
{
	auto physicsBody = PhysicsBody::createBox(this->m_Size, RECT_MATERIAL);
	//physicsBody->setMass(this->m_fMass);
	physicsBody->setGravityEnable(true);
	physicsBody->setDynamic(true);
	physicsBody->setCollisionBitmask(COLLISION_MASK);
	physicsBody->setContactTestBitmask(COLLISION_MASK);
	this->setPhysicsBody(physicsBody);
}

void DrawRectangle::InitDisplay()
{
	this->Render();
	
	Vec2 anchorRoot(0.5, 0.5);
	this->setAnchorPoint(anchorRoot);
	this->ignoreAnchorPointForPosition(false);
	this->setPosition(this->m_InitialPosition.x + this->m_Size.width / 2, 
		this->m_InitialPosition.y + this->m_Size.height / 2);

	this->InitPhysics();
}

void DrawRectangle::SetVelocity(Vec2 velocity)
{
	this->m_Velocity.x = velocity.x;
	this->m_Velocity.y = velocity.y;
}

int DrawRectangle::GetTag()
{
	return RECT_TAG;
}

