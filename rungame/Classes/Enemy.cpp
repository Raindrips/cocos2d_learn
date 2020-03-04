#include "Enemy.h"


Enemy::Enemy(void):isActivie( false)
{
}


Enemy::~Enemy(void)
{
}

bool Enemy::initWithData( EnemyData data ){

	// 利用父类来去进行初始化精灵的工作
	if ( !Sprite::initWithFile( data._imageName.c_str() ))
	{
		return false;
	}

	this->initEnemyByData( data );

	return true;
}


/*  初始化方法   */
void Enemy::initEnemyByData( EnemyData data ){

	this->setPosition( data._startPoint );
	this->isActivie = data.isActive;
}




bool Enemy::isCollsitionWithOthers( Node* node ){

	Rect otherRect = node->boundingBox();

	if ( otherRect.intersectsRect( this->boundingBox() ))
	{
		return true;
	}

	return false;
}


Enemy* Enemy::createEnemyWithData( EnemyData data ){

	Enemy* e = new Enemy;
	e->autorelease();
	e->initWithData( data );

	return e;
}
