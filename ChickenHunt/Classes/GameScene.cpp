//
//  GameScene.cpp
//  ChickenHunt
//
//  Created by Gerald Quick on 12/11/13.
//
//

#include "GameScene.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;

CCScene* GameScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameScene *layer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    _score = 0;
    _currentAmmo = 2;
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Anim-MH-Foreground-ipadhd.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Anim-MH-Flying-ipadhd.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Anim-MHShells-ipadhd.plist");
    _gameBatchNode = CCSpriteBatchNode::create("Anim-MH-Foreground-ipadhd.png");
    _flyingChickenNode = CCSpriteBatchNode::create("Anim-MH-Flying-ipadhd.png");
    _shellsNode = CCSpriteBatchNode::create("Anim-MH-Shells-ipadhd.png");
    this->addChild(_gameBatchNode);
    this->addChild(_flyingChickenNode);
    this->addChild(_shellsNode);
    
    _backgroundNode = CCParallaxNodeExtras::node();
    this->addChild(_backgroundNode,-1);
    
    auto _sky = CCSprite::create("sky.png");
    auto _background1 = CCSprite::create("background1.png");
    auto _background2 = CCSprite::create("background2.png");
    auto _background3 = CCSprite::create("background3.png");
    auto _background4 = CCSprite::create("background4.png");
    
    //background speeds
    CCPoint skySpeed = ccp(0.05,0);
    CCPoint bg1Speed = ccp(.105,0);
    CCPoint bg2Speed = ccp(.08,0);
    CCPoint bg3Speed = ccp(.12,0);
    CCPoint bg4Speed = ccp(.5,0);
    
    
    _sky->setScale(1.2f);
    _background1->setScale(1.2f);
    _background2->setScale(1.2f);
    _background3->setScale(1.2f);
    _background4->setScale(1.2f);
    
    //add children to background node
    _backgroundNode->addChild(_sky, 0, skySpeed, ccp(visibleSize.width,visibleSize.height/2));
   // _backgroundNode->addChild(_background1,1,bg1Speed, ccp(visibleSize.width,visibleSize.height/2));
    _backgroundNode->addChild(_background2,2,bg2Speed, ccp(visibleSize.width,visibleSize.height/2));
    _backgroundNode->addChild(_background3,3,bg3Speed, ccp(visibleSize.width,visibleSize.height/2.5));
    _backgroundNode->addChild(_background4,4,bg4Speed, ccp(_background4->boundingBox().size.width ,visibleSize.height/2));
    
    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                                          "CloseNormal.png",
                                                          "CloseSelected.png",
                                                          this,
                                                          menu_selector(GameScene::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));
    
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
    
    foreChick = new Chicken();
    foreChick->_sprite = CCSprite::createWithSpriteFrameName("mhfore1.png");
    this->addChild(foreChick->_sprite,5);
    foreChick->createAnimations();
    foreChick->_sprite->setPosition(CCPoint(ccp(visibleSize.width/2,foreChick->_sprite->boundingBox().size.height/2)));
    foreChick->setVisible(true);
    foreChick->show();

    /////////////////////////////
    // 3. add your codes below...
    
    // add a label shows "Hello World"
    // create and initialize a label
    
    CCLabelTTF* pLabel = CCLabelTTF::create("Game Scene", "Arial", 24);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));
    auto CCString * value = CCString::createWithFormat("Score:%i",_score);
    _scoreDisplay = CCLabelBMFont::create(value->getCString(), "fonts-ipadhd.fnt", visibleSize.width * 0.3f);
    _scoreDisplay->setAnchorPoint(ccp(1,0.5));
    _scoreDisplay->setPosition(ccp(visibleSize.width * 0.8f, visibleSize.height * 0.94f));
    this->addChild(_scoreDisplay);
    
    // add the label as a child to this layer
    this->addChild(pLabel, 1);
    this->setAccelerometerEnabled(true);
    this->setTouchEnabled(true);
    this->scheduleUpdate();
    
    return true;
}

void GameScene::update(float dt)
{
    _skyPos = _backgroundNode->getPosition();
    CCPoint backgroundScrollVert = ccp(_backgroundPointsPerSecX,0);
    if(_skyPos.x >= -11900.0 && _skyPos.x < 1)
    {
    //    backgroundScrollVert = ccp(-1000, 0);
        _backgroundNode->setPosition(ccpAdd(_backgroundNode->getPosition(), ccpMult(backgroundScrollVert, dt)));
    }else
    {
        if(_skyPos.x <= -11900)
        {
            if (_backgroundPointsPerSecX > 0.0f) {
                _backgroundNode->setPosition(ccpAdd(_backgroundNode->getPosition(), ccpMult(backgroundScrollVert, dt)));
            }
        }
        if (_skyPos.x >=1) {
            if (_backgroundPointsPerSecX < 0.0f) {
                _backgroundNode->setPosition(ccpAdd(_backgroundNode->getPosition(), ccpMult(backgroundScrollVert, dt)));
            }
        }
    }
        
    //{
    //    backgroundScrollVert = ccp(1000, 0);
    //}
    //CCLog("Position: %f",_backgroundPointsPerSecX);
}

void GameScene::ccTouchesBegan(CCSet* pTouches, CCEvent* event)
{
    CCTouch *touch = (CCTouch *)pTouches->anyObject();
    if (_currentAmmo <=0) {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("shotgunempty.mp3");
    }else
    {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("shotgunfire.mp3");
        _currentAmmo--;
    
        if (touch) {
            CCLog("Touch: x: %f, y: %f",touch->getLocation().x,touch->getLocation().y);
            if(foreChick->_sprite->boundingBox().containsPoint(touch->getLocation()))
            {
                if(!foreChick->isDead())
                {
                    foreChick->die();
                    addScore(50);
                }
            }
        }
    }
    
    
    
}
void GameScene::addScore(int v)
{
    _score += v;
    auto CCString * value = CCString::createWithFormat("Score:%i", _score);
    _scoreDisplay->setString(value->getCString());
}
void GameScene::didAccelerate(CCAcceleration* pAccelerationValue) {
#define KFILTERINGFACTOR 0.1
#define KRESTACCELX -0.8
#define KSHIPMAXPOINTSPERSEC (winSize.width*2)
#define KMAXDIFFX 0.2
    
    double rollingX;
    
    // Cocos2DX inverts X and Y accelerometer depending on device orientation
    // in landscape mode right x=-y and y=x !!! (Strange and confusing choice)
    pAccelerationValue->y = -pAccelerationValue->x;
    rollingX = (pAccelerationValue->y * KFILTERINGFACTOR) + (rollingX * (1.0 - KFILTERINGFACTOR));
    float accelX = pAccelerationValue->y - rollingX;
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    float accelDiff = accelX - KRESTACCELX;
    float accelFraction = accelDiff / KMAXDIFFX;
    _backgroundPointsPerSecX = KSHIPMAXPOINTSPERSEC * accelFraction;
    CCLog("Accel: %f",_backgroundPointsPerSecX);
}

void GameScene::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
