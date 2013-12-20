#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Player.h"
#include "SneakyJoystick.h"
#include "SneakyJoystickSkinnedBase.h"
#include "SneakyButton.h"
#include "SneakyButtonSkinnedBase.h"

class HelloWorld : public cocos2d::CCLayer
{
	//enum Direction {LEFT,RIGHT};
private:
	cocos2d::CCPoint basePosition;
	cocos2d::CCPoint firePosition;
    cocos2d::CCSprite * _joystickBackground;
    cocos2d::CCSprite * _tumbstick;
	cocos2d::CCSpriteBatchNode * _batchNode;
	cocos2d::CCSprite * _background;
	cocos2d::CCSprite * _dot;
	//cocos2d::CCSprite * _player;
	cocos2d::CCArray * _bulletPool;
	cocos2d::CCSequence * _idle;
	bool _pIdle;
	int _bulletPoolIndex;
	Player _player;
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
	SneakyJoystick *leftJoystick;
	SneakyButton *fireButton;
	virtual void update(float);
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(cocos2d::CCObject* pSender);
    void createPools();
	void createActions();
	void animationDone(cocos2d::CCNode* pSender);
	void ccTouchesBegan(cocos2d::CCSet*,cocos2d::CCEvent*);
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
