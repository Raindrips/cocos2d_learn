#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <vector>


USING_NS_CC;

#include "Enemy.h"
class HelloWorld : public cocos2d::CCLayer
{
public:

	HelloWorld();
	~HelloWorld();
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* scene();

	// a selector callback
	void menuCloseCallback(CCObject* pSender);

	void init_bg();

	// implement the "static node()" method manually
	CREATE_FUNC(HelloWorld);
	CCSprite* bg01;
	CCSprite* bg02;

	CCTMXTiledMap* _bgMap01;
	CCTMXTiledMap* _bgMap02;

	//实现背景无限滚动
	void bg_move_logic(float dt);

	//玩家运动的核心逻辑 
	void player_move_logic(float dt);

	void speed_up_callback(Ref* ref);

	void start_speed_up_callback(float dt);
	bool isSpeeding;

	// 获取人物的动画
	Animation* __get_role_animation__();

	Sprite* m_playerSprite;

	bool TouchBegan(Touch* pTouch, Event* pEvent);
	virtual void onEnter();
	virtual void onExit();

	float _bgMoveSpeed;


	float gravity;  // 重力 
	float velocity; // 速度
	__Array* enemyArray; // 存储小怪的数组

	void init_enenmys();

	std::vector<EnemyData> _enemyDatasVector; // 小怪的信息集合 相当于阵列信息


};

#endif // __HELLOWORLD_SCENE_H__
