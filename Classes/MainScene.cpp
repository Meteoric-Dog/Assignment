#include "MainScene.h"

MainScene::~MainScene()
{
	this->m_ObjectList.clear();                   //engine takes care of withdrawing memory
	SimpleAudioEngine::getInstance()->end();
}

Scene * MainScene::s_CreateScene()
{
	return MainScene::create();
}

bool MainScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	this->m_iObjectAmount = 0;
	this->m_ClickedObjectPointer = NULL;
	
	auto audioEngine = SimpleAudioEngine::getInstance();
	//audioEngine->preloadBackgroundMusic(BACKGROUND_MUSIC);
	//audioEngine->playBackgroundMusic(BACKGROUND_MUSIC);
	audioEngine->setEffectsVolume(EFFECT_VOLUME);
	audioEngine->preloadEffect(RECT_SOUND);
	audioEngine->preloadEffect(CIRCLE_SOUND);

	this->mouseListener = EventListenerMouse::create();
	this->mouseListener->onMouseDown = CC_CALLBACK_1(MainScene::onMouseDown, this);
	this->mouseListener->onMouseMove = CC_CALLBACK_1(MainScene::onMouseMove, this);
	this->mouseListener->onMouseScroll = CC_CALLBACK_1(MainScene::onMouseScroll, this);
	this->mouseListener->onMouseUp = CC_CALLBACK_1(MainScene::onMouseUp, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(this->mouseListener, this);

	return true;
}

void MainScene::draw(Renderer * renderer, const Mat4 & transform, uint32_t flags)
{
	Scene::draw(renderer, transform, flags);

	fstream f;
	f.open(DATA_FILE, ios::in);

	if (!f.is_open()) {
		f.close();
		//CCLOG("CAN NOT OPEN FILE");
		return;
	}
	
	string temp;
	int bufferSize = 20, amount = 0;
	char *key = new char[bufferSize];
	char *value0 = new char[bufferSize];

	getline(f, temp);
	//CCLOG(temp.c_str());
	sscanf(temp.c_str(), AMOUNT_FORMAT, key, &amount);

	//sprintf(value0, "%d", amount);
	//CCLOG(value0);

	if (amount > this->m_iObjectAmount) {
		int iter = 0;
		int amountLinesPerObject = 5;
		int positionX = 0, positionY = 0, value1 = 0, value2 = 0, velocity = 0, extractedAmount = 0;
		Vec2 tempVelocity(0,0);
		string temp1, temp2;

		while (iter < this->m_iObjectAmount) {
			for (int i = 0; i < amountLinesPerObject; i++)
				getline(f, temp);
			iter++;
		}

		while (iter < amount) {
			DrawObject *object = NULL;

			getline(f, temp);
			getline(f, temp);
			getline(f, temp1);
			getline(f, temp2);

			sscanf(temp.c_str(), TYPE_FORMAT, key, value0);
			if (strcmp(value0, RECT_TYPE) == 0) {
				extractedAmount = sscanf(temp1.c_str(), RECT_POSITION_FORMAT, key, &positionX,
					&positionY, &value1, &value2);
				
				if (extractedAmount != 5) {
					iter++;
					continue;
				} 

				object = DrawRectangle::createObject(Vec2(positionX, positionY),
					SCENE_INITIAL_MASS, tempVelocity, RECT_COLOR, Size(value1, value2));
			}
			else 
				if (strcmp(value0, CIRCLE_TYPE) == 0) {
					extractedAmount = sscanf(temp1.c_str(), CIRCLE_POSITION_FORMAT, key, 
						&positionX, &positionY, &value1);
					if (extractedAmount != 4) {
						iter++;
						continue;
					}

					float tempAngle = 360;
					object = DrawCircle::createObject(Vec2(positionX, positionY), 
						SCENE_INITIAL_MASS, tempVelocity, CIRCLE_COLOR, value1, tempAngle);
				}		
				else 
					if (strcmp(value0, PLANE_TYPE) == 0) {
						extractedAmount = sscanf(temp1.c_str(), PLANE_POSITION_FORMAT, key, 
							&positionX, &positionY, &value1, &value2);
						if (extractedAmount != 5) {
							iter++;
							continue;
						}

						object = DrawPlane::createObject(Vec2(positionX, positionY), SCENE_INITIAL_MASS,
							tempVelocity, PLANE_COLOR, Vec2(value1, value2));
					}
			
			extractedAmount = sscanf(temp2.c_str(), VELOCITY_FORMAT, key, &value1);
			if (extractedAmount != 2) {
				iter++;
				continue;
			}
			object->SetVelocity(Vec2(value1, value1));

			object->InitDisplay();
			this->addChild(object);
			this->m_ObjectList.push_back(object);
			iter++;
			if (f.peek() == EOF) {     //to avoid the case there is no empty line at the end
				break;
			}
			getline(f, temp);
		}	

		this->m_iObjectAmount = amount;
	}

	delete[] key;
	delete[] value0;

	f.close();
}

void MainScene::onMouseDown(Event * event)
{
	EventMouse *mouseEvent = (EventMouse*)event;	
	this->m_MousePreviousPosition = mouseEvent->getLocationInView();
	for (list<DrawObject*>::iterator iter = this->m_ObjectList.begin();
		iter != this->m_ObjectList.end(); ++iter) {
		if ((*iter)->getBoundingBox().containsPoint(mouseEvent->getLocationInView())) {
			this->m_ClickedObjectPointer = *iter;
			//CCLOG("CLICKED");
		}
	}
	if (this->m_ClickedObjectPointer != NULL) {
		switch (this->m_ClickedObjectPointer->GetMark()) {
		case RECT_MARK:
			this->m_ClickedObjectPointer->ChangeColor(CLICKED_RECT_COLOR);
			SimpleAudioEngine::getInstance()->playEffect(RECT_SOUND);
			break;
		case CIRCLE_MARK:
			this->m_ClickedObjectPointer->ChangeColor(CLICKED_CIRCLE_COLOR);
			SimpleAudioEngine::getInstance()->playEffect(CIRCLE_SOUND);
			break;
		case PLANE_MARK:
			this->m_ClickedObjectPointer->ChangeColor(CLICKED_PLANE_COLOR);
			break;
		}
	}
}

void MainScene::onMouseMove(Event * event)
{
	if (this->m_ClickedObjectPointer != NULL) {
		EventMouse* mouseEvent = (EventMouse*)event;

		Vec2 currentPosition = mouseEvent->getLocationInView();
		Vec2 newObjectPosition = this->m_ClickedObjectPointer->getPosition()
			+ currentPosition - m_MousePreviousPosition;

		this->m_ClickedObjectPointer->setPosition(newObjectPosition);
		this->m_MousePreviousPosition = currentPosition;
	}
}

void MainScene::onMouseScroll(Event * event)
{
}

void MainScene::onMouseUp(Event * event)
{
	if (this->m_ClickedObjectPointer != NULL) {
		switch (this->m_ClickedObjectPointer->GetMark()) {
		case RECT_MARK:
			this->m_ClickedObjectPointer->ChangeColor(RECT_COLOR);
			SimpleAudioEngine::getInstance()->stopAllEffects();
			break;
		case CIRCLE_MARK:
			this->m_ClickedObjectPointer->ChangeColor(CIRCLE_COLOR);
			SimpleAudioEngine::getInstance()->stopAllEffects();
			break;
		case PLANE_MARK:
			this->m_ClickedObjectPointer->ChangeColor(PLANE_COLOR);
			break;
		}
	}
	
	this->m_ClickedObjectPointer = NULL;
}


