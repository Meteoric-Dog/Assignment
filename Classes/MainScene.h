#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<list>
#include<fstream>
#include<string>
#include"cocos2d.h"
#include"DrawObject.h"
#include"DrawRectangle.h"
#include"DrawPlane.h"
#include"DrawCircle.h"

USING_NS_CC;
using namespace std;

#define DATA_FILE "SceneManager.txt"
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

const auto RECT_COLOR = Color4F::BLUE;
const auto CLICKED_RECT_COLOR = Color4F::MAGENTA;
const auto CIRCLE_COLOR = Color4F::RED;
const auto CLICKED_CIRCLE_COLOR = Color4F::GREEN;
const auto PLANE_COLOR = Color4F::GREEN;
const auto CLICKED_PLANE_COLOR = Color4F::YELLOW;

class MainScene :public Scene{
public:
	list<DrawObject> m_ObjectList;
	int m_iObjectAmount;

public:
	virtual ~MainScene();
	
public:
	static Scene* s_CreateScene();
	virtual bool init();
	virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags);

	CREATE_FUNC(MainScene);
};