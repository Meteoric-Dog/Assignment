#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<list>
#include<fstream>
#include<string>
#include"cocos2d.h"
#include"base/CCEvent.h"
#include"base/CCEventMouse.h"
#include"base/CCEventListenerMouse.h"
#include"SimpleAudioEngine.h"
#include"DrawObject.h"
#include"DrawRectangle.h"
#include"DrawPlane.h"
#include"DrawCircle.h"

USING_NS_CC;
using namespace std;
using namespace CocosDenshion;

#define DATA_FILE "SceneManager.txt"
#define SCENE_MATERIAL PhysicsMaterial(1.0, 0, 0.1)
#define SCENE_EDGE_WIDTH 3.0

#define EDGE_TAG 50
#define OBJECT_COLLISION_ANNOUNCEMENT "Object collision detected"
#define EDGE_COLLISION_ANNOUNCEMENT "Edge collision detected"

#define BACKGROUND_MUSIC "Chiru-Saisei-No-Uta.mp3"
#define RECT_SOUND "sword_attack.wav"
#define CIRCLE_SOUND "gun_shot.wav"
#define EFFECT_VOLUME 8.0
#define BACKGROUND_MUSIC_VOLUME 2.0

#define RECT_TYPE "RECT"
#define CIRCLE_TYPE "CIRCLE"
#define PLANE_TYPE "PLANE"

#define AMOUNT_FORMAT "%s %d"
#define TYPE_FORMAT "%s %s"
#define RECT_POSITION_FORMAT "%s %d,%d,%d,%d"
#define CIRCLE_POSITION_FORMAT "%s %d,%d,%d"
#define PLANE_POSITION_FORMAT "%s %d,%d,%d,%d"    
#define VELOCITY_FORMAT "%s %d"

#define SCENE_INITIAL_MASS 0
#define SNOW_SPEED 4.0

#define NORMAL_TYPE 1
#define COLLIDED_TYPE 2

const auto RECT_COLOR = Color4F::BLUE;
const auto COLLIDED_RECT_COLOR = Color4F::MAGENTA;
const auto CIRCLE_COLOR = Color4F::RED;
const auto COLLIDED_CIRCLE_COLOR = Color4F::GREEN;
const auto PLANE_COLOR = Color4F::GREEN;
const auto COLLIDED_PLANE_COLOR = Color4F::YELLOW;

class MainScene :public Scene{
public:
	list<DrawObject*> m_ObjectList;
	DrawObject* m_ClickedObjectPointer;
	int m_iObjectAmount;
	EventListenerMouse *mouseListener;
	Vec2 m_MousePreviousPosition;

public:
	virtual ~MainScene();
	
public:
	static Scene* s_CreateScene();
	virtual bool init();
	virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags);
	
	void ChangeObjectColor(int type, DrawObject *object);

	void onMouseDown(Event* event);
	void onMouseMove(Event* event);
	void onMouseScroll(Event* event);
	void onMouseUp(Event* event);

	bool onContactBegin(PhysicsContact &contact);
	void onContactSeparate(PhysicsContact &contact);

	CREATE_FUNC(MainScene);
};