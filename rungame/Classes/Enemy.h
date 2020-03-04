#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "cocos2d.h"
#include <string>
USING_NS_CC;

struct EnemyData
{

	bool isActive;
	Vec2 _startPoint; // ��ʼ��λ��
	//CCRect _collRect; // �Զ������ײ����
	std::string _imageName; // С�ֵ�ͼƬ

};

class Enemy : public Sprite
{
public:
	Enemy(void);
	~Enemy(void);

	static Enemy* createEnemyWithData( EnemyData data );
	virtual bool initWithData( EnemyData data );

	bool isActivie; // �Ƿ�
	Rect _enemyCollRect; // С�ֵ�ȫ����ײ����

	/*
	@�ж��������Ľڵ���ײ�ķ���
	@return:��ײ����true
	*/
	bool isCollsitionWithOthers( Node* node );

private:
	void initEnemyByData( EnemyData _data );

};


#endif