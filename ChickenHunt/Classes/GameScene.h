//
//  GameScene.h
//  ChickenHunt
//
//  Created by Gerald Quick on 12/11/13.
//
//

#ifndef __ChickenHunt__GameScene__
#define __ChickenHunt__GameScene__

#include "cocos2d.h"
#include "CCParallaxNodeExtras.h"
#include "Chicken.h"
#include "FlyingChicken.h"

class GameScene : public cocos2d::CCLayer
{
private:
    int _score;
    CCString * strScore;
    CCSprite *_sky;
    CCSprite *_background1;
    CCSprite *_background2;
    CCSprite *_background3;
    CCSprite *_background4;
    CCPoint _skyPos;
    CCLabelBMFont * _scoreDisplay;
    float _backgroundPointsPerSecX;
    CCSpriteBatchNode * _gameBatchNode;
    CCSpriteBatchNode * _flyingChickenNode;
    CCSpriteBatchNode * _shellsNode;
    Chicken * foreChick;
    int _currentAmmo;
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    CCParallaxNodeExtras *_backgroundNode;
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    virtual void didAccelerate(CCAcceleration* pAccelerationValue);
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    void update(float dt);
    void ccTouchesBegan(CCSet* pTouches, CCEvent* event);
    void addScore(int value);
    // implement the "static node()" method manually
    CREATE_FUNC(GameScene);
};

#endif /* defined(__ChickenHunt__GameScene__) */
