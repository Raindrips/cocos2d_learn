#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "cocos2d.h"
#include <string>
USING_NS_CC;

struct EnemyData
{

	bool isActive;
	Vec2 _startPoint; // 起始的位置
	//CCRect _collRect; // 自定义的碰撞区域
	std::string _imageName; // 小怪的图片

};

class Enemy : public Sprite
{
public:
	Enemy(void);
	~Enemy(void);

	static Enemy* createEnemyWithData( EnemyData data );
	virtual bool initWithData( EnemyData data );

	bool isActivie; // 是否活动
	Rect _enemyCollRect; // 小怪的全局碰撞对象

	/*
	@判断与其他的节点碰撞的方法
	@return:碰撞返回true
	*/
	bool isCollsitionWithOthers( Node* node );

private:
	void initEnemyByData( EnemyData _data );

};


#endif