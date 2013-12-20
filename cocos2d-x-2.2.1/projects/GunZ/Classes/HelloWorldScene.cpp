#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;
using namespace CocosDenshion;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

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
    if ( !CCLayer::init() )
    {
        return false;
    }
    
	_pIdle = true;
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
	_background = CCSprite::create("sewerBackground.png");
	_background->setScale(1.5);
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	_background->setPosition(ccp(origin.x, visibleSize.height/2));
	this->addChild(_background,0);
	
	_batchNode = CCSpriteBatchNode::create("Anim-Player-hd-ipadhd.png");
	this->addChild(_batchNode);
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Anim-Player-hd-ipadhd.plist");
	_player._sprite = CCSprite::createWithSpriteFrameName("idle1.png");
	_player.setPosition(winSize.width /2, winSize.height /2);
	_batchNode->addChild(_player._sprite,1);
	_joystickBackground = CCSprite::create("joystickBase.png");
    _tumbstick = CCSprite::create("thumbstick.png");
    
    _player.createAnimation();
	_player.playAnimation();
	//SimpleAudioEngine::sharedEngine()->playBackgroundMusic("QuickSilver.wav",true);
	basePosition = ccp(150,150);
	SneakyJoystickSkinnedBase *joystickBase = SneakyJoystickSkinnedBase::create();
	SneakyJoystick *tmpJoystick = new SneakyJoystick();
	tmpJoystick->initWithRect(CCRect(0,0,50,50));
	joystickBase->setBackgroundSprite(_joystickBackground);
	joystickBase->setThumbSprite(_tumbstick);
	joystickBase->setJoystick(tmpJoystick);
	joystickBase->setPosition(basePosition);
	leftJoystick = joystickBase->getJoystick();
	this->addChild(joystickBase);
    firePosition = ccp(200,30);
	
    
    //CCLabelBMFont* pLabel = CCLabelBMFont::create("0", "fonts.fnt");
    //CCLabelTTF* pLabel = CCLabelTTF::create("00000", "Arial", 12);
    CCLabelBMFont* pLabel = CCLabelBMFont::create("0","fonts-ipadhd.fnt",winSize.width * .03f);
    // position the label on the center of the screen
	pLabel->setPosition(ccp(visibleSize.width * 0.08f + pLabel->getContentSize().width,
                            visibleSize.height * 0.94f));
	pLabel->setAnchorPoint(ccp(1,0.5));
    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    scheduleUpdate();
    
    return true;
}

 void HelloWorld::update(float dt)
{
    
    //CCLog("Update");
    _player.updateAnimation();
    if(_player._currentState != _player.TURN)
    {
        CCPoint scaledVelocity = ccpMult(leftJoystick->getVelocity(),75);
        CCPoint newposition = ccp(_player.positionX() + scaledVelocity.x * dt,_player.positionY() + scaledVelocity.y * dt);
        _player.setPosition(newposition);
        
    }
    CCPoint joyDir = leftJoystick->getStickPosition();
    if (joyDir.x < 0) {
        if(_player._facingDirection == _player.RIGHT)
        {
            _player._currentState = _player.TURN;
            
        }
    }
    else if(joyDir.x > 0)
    {
        if(_player._facingDirection == _player.LEFT)
        {
            _player._currentState = _player.TURN;
        }
    }
    
    if(joyDir.x < 0 || joyDir.x > 0)
    {
        if(_player._currentState != _player.TURN)
            _player._currentState = _player.RUN;
    }
    if(joyDir.x == 0)
    {
        _player._currentState = _player.IDLE;
    }
    
}

void HelloWorld::createActions()
{
	CCAnimation* animation;
	CCSpriteFrame * frame;

	//create CCAnimation object
	animation = CCAnimation::create();
	CCString * name;
	for(int i = 1;i<=5;i++)
	{
		name = CCString::createWithFormat("idle%i.png",i);
		frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
		animation->addSpriteFrame(frame);
	}
	for(int i = 5;i>=1;i--)
	{
		name = CCString::createWithFormat("idle%i.png",i);
		frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
		animation->addSpriteFrame(frame);
	}
	animation->setLoops(99);
	animation->setDelayPerUnit(3 / 10.0f);
	animation->setRestoreOriginalFrame(true);
	//_player->runAction(CCAnimate::create(animation));
	_idle = CCSequence::create(CCAnimate::create(animation),CCCallFuncN::create(this,callfuncN_selector(HelloWorld::animationDone)),NULL);
	
	_idle->retain();
}
void HelloWorld::animationDone(CCNode* pSender)
{
	
}

void HelloWorld::ccTouchesBegan(CCSet* pTouches, CCEvent* event)
{
	CCTouch *touch = (CCTouch *)pTouches->anyObject();

	if (touch)
	{
		CCPoint p = touch->getLocation();
		if(p.x < _player.positionX())
		{
			if(_player._facingDirection != _player.LEFT)
			{
				_player._currentState = _player.TURN;
				_player.playAnimation();
			}

		}

	}

	
}

void HelloWorld::createPools()
{
	CCSprite * sprite;
	int i;

	_bulletPool = cocos2d::CCArray::createWithCapacity(50);
	_bulletPool->retain();
	_bulletPoolIndex = 0;
	for(i =0;i<50;i++)
	{
		sprite = CCSprite::createWithSpriteFrameName("bullet1.png");
		sprite->setVisible(false);

	}
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
