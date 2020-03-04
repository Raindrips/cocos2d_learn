#undef UNICODE
#include "HelloWorldScene.h"

USING_NS_CC;
using namespace std;


HelloWorld::HelloWorld() {

	enemyArray = Array::create();

	CC_SAFE_RETAIN(enemyArray);

	isSpeeding = false;
	_bgMoveSpeed = 1.0f;

}
HelloWorld::~HelloWorld() {

	CC_SAFE_RELEASE_NULL(enemyArray);
	CC_SAFE_RELEASE_NULL(_bgMap01);
	CC_SAFE_RELEASE_NULL(_bgMap02);

}
Scene* HelloWorld::scene()
{
	// 'scene' is an autorelease object
	Scene* scene = Scene::create();

	// 'layer' is an autorelease object
	HelloWorld* layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);
	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!CCLayer::init())
	{
		return false;
	}

	gravity = 0.2f;
	velocity = -2.0f;

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("runner.plist");

	Size size = Director::sharedDirector()->getWinSize();
	m_playerSprite = Sprite::createWithSpriteFrameName("runner0.png");
	m_playerSprite->setPosition(Vec2(size.width / 3, size.height / 4));

	Animate* animate = Animate::create(__get_role_animation__());
	m_playerSprite->runAction(RepeatForever::create(animate));

	addChild(m_playerSprite, 10);

	this->init_bg();

	MenuItemImage* speedUp = MenuItemImage::create("start_n.png", "start_s.png", this, menu_selector(HelloWorld::speed_up_callback));
	speedUp->setPosition(size.width * 0.75f, size.height * 0.75f);
	speedUp->setScale(0.5f);

	Menu* m = Menu::create(speedUp, NULL);
	m->setPosition(Vec2());
	addChild(m, 10);

	init_enenmys();
	return true;
}

void HelloWorld::speed_up_callback(Object* ref) {
	if (isSpeeding)
		return;

	isSpeeding = true;
	_bgMoveSpeed = 4.0f;

	this->scheduleOnce(schedule_selector(HelloWorld::start_speed_up_callback), 2.0f);
}

void HelloWorld::start_speed_up_callback(float dt) {

	isSpeeding = false;
	_bgMoveSpeed = 1.0f;

}

/************************************************************************/
/*  初始化创建背景的方法                                                                     */

/************************************************************************/
void HelloWorld::init_bg() {

	_bgMap01 = TMXTiledMap::create("map00.tmx");
	_bgMap02 = TMXTiledMap::create("map01.tmx");
	_bgMap01->retain();
	_bgMap02->retain();

	_bgMap01->setPosition(Vec2());
	_bgMap02->setPosition(ccp(_bgMap01->getContentSize().width, 0));

	_bgMap01->setAnchorPoint(Vec2());
	_bgMap02->setAnchorPoint(Vec2());

	addChild(_bgMap01, -1);
	addChild(_bgMap02, -1);


	//背景移动
	this->schedule(schedule_selector(HelloWorld::bg_move_logic), 1.0f / 60.0f);
	//人物移动
	this->schedule(schedule_selector(HelloWorld::player_move_logic), 1.0f / 60.0f);
}



void HelloWorld::bg_move_logic(float dt) {

	_bgMap01->setPositionX(_bgMap01->getPositionX() - _bgMoveSpeed);
	_bgMap02->setPositionX(_bgMap01->getPositionX() + _bgMap01->getContentSize().width);

	if (_bgMap02->getPositionX() <= 0)
	{
		_bgMap01->setPositionX(0);
	}
}

void HelloWorld::player_move_logic(float dt)
{
	Size sizeWin = Director::sharedDirector()->getWinSize();

	velocity -= gravity;
	//不断的加上这个大小
	m_playerSprite->setPositionY(m_playerSprite->getPositionY() + velocity);

	if (m_playerSprite->getPositionY() <= sizeWin.height / 4)
	{
		m_playerSprite->setPositionY(sizeWin.height / 4);
	}
	Ref* obj = nullptr;
	CCARRAY_FOREACH(enemyArray, obj) {
		Enemy* sp = static_cast<Enemy*>(obj);

		bool isColl = sp->isCollsitionWithOthers(m_playerSprite);
		if (isColl)
		{
			MessageBox("Game Over", "Title");
			this->unscheduleAllSelectors();
			break;
		}
		sp->setPositionX(sp->getPositionX() - 2);
	}
}


bool HelloWorld::TouchBegan(Touch* pTouch, Event* pEvent) {
	velocity = 5;
	return true;
}

void HelloWorld::onEnter() {
	Layer::onEnter();
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::TouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

}

void HelloWorld::onExit() {

	_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ALL_AT_ONCE);
	Layer::onExit();
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
	Director::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}


void HelloWorld::init_enenmys() {

	EnemyData d1;
	d1.isActive = false;
	d1._startPoint = ccp(400, 100);
	d1._imageName = "CloseSelected.png";

	EnemyData d2;
	d2.isActive = false;
	d2._startPoint = ccp(400, 190);
	d2._imageName = "CloseSelected.png";

	_enemyDatasVector.push_back(d1);
	_enemyDatasVector.push_back(d2);

	for (auto &e: _enemyDatasVector)
	{
		Enemy* enemy = Enemy::createEnemyWithData(e);
		addChild(enemy, 10);
		enemyArray->addObject(enemy);
	}
}

Animation* HelloWorld::__get_role_animation__() {
	Vector<SpriteFrame*> array;
	String temp;
	for (int i = 0; i < 8; i++)
	{
		temp.initWithFormat("runner%d.png", i);
		SpriteFrame* frame = SpriteFrameCache::getInstance()->spriteFrameByName(temp._string);
		array.pushBack(frame);
	}
	auto* anim = Animation::createWithSpriteFrames(array);
	anim->setDelayPerUnit(10.0f/60.0f);
	return anim;
}
