#include "MainScene.h"

MainScene::~MainScene()
{
	for (list<DrawObject*>::iterator iter = this->m_ObjectList.begin(); iter != this->m_ObjectList.end(); ++iter) {
		(*iter)->clear();
	}
	this->m_ObjectList.clear();                   //engine takes care of withdrawing memory
	SimpleAudioEngine::getInstance()->end();
}

Scene * MainScene::s_CreateScene()
{
	return MainScene::create();
}

bool MainScene::init()
{
	if (!Scene::initWithPhysics())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	this->m_iObjectAmount = 0;
	this->m_ClickedObjectPointer = NULL;
	
	auto audioEngine = SimpleAudioEngine::getInstance();

	audioEngine->preloadBackgroundMusic(BACKGROUND_MUSIC);
	audioEngine->setBackgroundMusicVolume(BACKGROUND_MUSIC_VOLUME);
	audioEngine->playBackgroundMusic(BACKGROUND_MUSIC,true);

	audioEngine->setEffectsVolume(EFFECT_VOLUME);
	audioEngine->preloadEffect(RECT_SOUND);
	audioEngine->preloadEffect(CIRCLE_SOUND);

	this->mouseListener = EventListenerMouse::create();
	this->mouseListener->onMouseDown = CC_CALLBACK_1(MainScene::onMouseDown, this);
	this->mouseListener->onMouseMove = CC_CALLBACK_1(MainScene::onMouseMove, this);
	this->mouseListener->onMouseScroll = CC_CALLBACK_1(MainScene::onMouseScroll, this);
	this->mouseListener->onMouseUp = CC_CALLBACK_1(MainScene::onMouseUp, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(this->mouseListener, this);

	auto physicsBody = PhysicsBody::createEdgeBox(visibleSize, SCENE_MATERIAL, SCENE_EDGE_WIDTH);
	physicsBody->setCollisionBitmask(COLLISION_MASK);
	physicsBody->setContactTestBitmask(COLLISION_MASK);

	auto edgeBox = Node::create();
	edgeBox->addComponent(physicsBody);
	edgeBox->setTag(EDGE_TAG);
	edgeBox->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
	this->addChild(edgeBox);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(MainScene::onContactBegin, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(MainScene::onContactSeparate, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	auto particleSnow = ParticleSnow::create();
	particleSnow->setDuration(ParticleSystem::DURATION_INFINITY);
	particleSnow->setEmitterMode(ParticleSystem::Mode::GRAVITY);
	particleSnow->setSpeed(SNOW_SPEED);
	this->addChild(particleSnow);

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
		switch (this->m_ClickedObjectPointer->getTag()) {
		case RECT_TAG:
			this->m_ClickedObjectPointer->startParticle();
			SimpleAudioEngine::getInstance()->playEffect(RECT_SOUND);
			break;
		case CIRCLE_TAG:
			this->m_ClickedObjectPointer->startParticle();
			SimpleAudioEngine::getInstance()->playEffect(CIRCLE_SOUND);
			break;
		case PLANE_TAG:
			break;
		}

		this->m_ClickedObjectPointer->getPhysicsBody()->setDynamic(false);
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
		switch (this->m_ClickedObjectPointer->getTag()) {
		case RECT_TAG:
			this->m_ClickedObjectPointer->stopParticle();
			SimpleAudioEngine::getInstance()->stopAllEffects();
			break;
		case CIRCLE_TAG:
			this->m_ClickedObjectPointer->stopParticle();
			SimpleAudioEngine::getInstance()->stopAllEffects();
			break;
		case PLANE_TAG:
			break;
		}

		this->m_ClickedObjectPointer->getPhysicsBody()->setDynamic(true);
	}

	this->m_ClickedObjectPointer = NULL;
}

bool MainScene::onContactBegin(PhysicsContact & contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	if (nodeA && nodeB) {
		if (nodeA->getTag() == EDGE_TAG || nodeB->getTag() == EDGE_TAG) {
			CCLOG(EDGE_COLLISION_ANNOUNCEMENT);
		}
		else {
			CCLOG(OBJECT_COLLISION_ANNOUNCEMENT);
		}

		if (nodeA->getTag() != EDGE_TAG) {
			DrawObject *objectA = (DrawObject*)nodeA;
			objectA->m_iContactCount++;
			if (objectA->m_iContactCount == 1) {
				ChangeObjectColor(COLLIDED_TYPE, objectA);
			}
		}

		if (nodeB->getTag() != EDGE_TAG) {
			DrawObject *objectB = (DrawObject*)nodeB;
			objectB->m_iContactCount++;
			if (objectB->m_iContactCount == 1) {
				ChangeObjectColor(COLLIDED_TYPE, objectB);
			}
		}

		return true;
	}
	return false;
}

void MainScene::onContactSeparate(PhysicsContact & contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	if (nodeA && nodeB) {
		if (nodeA->getTag() != EDGE_TAG) {
			DrawObject* objectA = (DrawObject*)nodeA;
			objectA->m_iContactCount--;
			if (objectA->m_iContactCount == 0) {
				ChangeObjectColor(NORMAL_TYPE, objectA);
			}
		}

		if (nodeB->getTag() != EDGE_TAG) {
			DrawObject* objectB = (DrawObject*)nodeB;
			objectB->m_iContactCount--;
			if (objectB->m_iContactCount == 0) {
				ChangeObjectColor(NORMAL_TYPE, objectB);
			}
		}
	}
}

void MainScene::ChangeObjectColor(int type, DrawObject *object)
{
	switch (object->getTag()) {
	case RECT_TAG:
		if (type == NORMAL_TYPE) {
			object->ChangeColor(RECT_COLOR);
		}
		else {
			object->ChangeColor(COLLIDED_RECT_COLOR);
		}
		break;
	case CIRCLE_TAG:
		if (type == NORMAL_TYPE) {
			object->ChangeColor(CIRCLE_COLOR);
		}
		else {
			object->ChangeColor(COLLIDED_CIRCLE_COLOR);
		}
		break;
	case PLANE_TAG:
		//...
		break;
	}
}


