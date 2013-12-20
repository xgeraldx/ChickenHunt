//
//  Player.cpp
//  GunZ
//
//  Created by Gerald Quick on 12/10/13.
//
//

#include "Player.h"


USING_NS_CC;


Player::Player()
{
    _health = 100;
    _kills = 0;
    _score = 0;
    _currentState = IDLE;
    _facingDirection = RIGHT;
    _turning = false;
    _idleReady = true;
    _runReady = true;
}
Player::~Player(){}



int Player::getHealth()
{
    return _health;
}

int Player::getScore()
{
    return _score;
}

int Player::getKills()
{
    return _kills;
}

void Player::addHealth(int value)
{
    _health = MIN(_health +=value,100);
    
}

void Player::addScore(int value)
{
    _score += value;
}

void Player::addKill(int value)
{
    _kills += value;
}

void Player::takeDamage(int value)
{
    _health -= value;
    if(_health <= 0)
        _currentState = DEAD;
}

void Player::setPosition(cocos2d::CCPoint loc)
{
    _posX = loc.x;
    _posY = loc.y;
    _sprite->setPosition(loc);
}

void Player::createAnimation()
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
	animation->setLoops(1);
	animation->setDelayPerUnit(3 / 10.0f);
	animation->setRestoreOriginalFrame(true);
	//_player->runAction(CCAnimate::create(animation));
	_idle = CCSequence::create(CCAnimate::create(animation),CCCallFuncN::create(this,callfuncN_selector(Player::idleAnimationDone)),NULL);
	
	_idle->retain();

    animation = CCAnimation::create();
    
    for(int i = 1;i<=11;i++)
    {
        name = CCString::createWithFormat("turnleft%i.png",i);
        frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
        animation->addSpriteFrame(frame);
    }
    animation->setLoops(1);
    animation->setDelayPerUnit(.5/11.0f);
    animation->setRestoreOriginalFrame(true);
    
    _turn = CCSequence::create(CCAnimate::create(animation),CCCallFuncN::create(this,callfuncN_selector(Player::turnAnimationDone)),NULL);
    _turn->retain();
    
    animation = CCAnimation::create();
    
    for(int i = 1;i<=12;i++)
    {
        name = CCString::createWithFormat("run%i.png",i);
        frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
        animation->addSpriteFrame(frame);
    }
    animation->setLoops(1);
    animation->setDelayPerUnit(1/12.0f);
    animation->setRestoreOriginalFrame(false);
    
    _run = CCSequence::create(CCAnimate::create(animation),CCCallFuncN::create(this, callfuncN_selector(Player::runAnimationDone)),NULL);
    _run->retain();
    
}
void Player::runAnimationDone(CCNode * pSender)
{
    _runReady = true;
}
void Player::idleAnimationDone(CCNode * pSender)
{
    _idleReady = true;
}
void Player::turnAnimationDone(CCNode * pSender)
{
    _turning = false;
    if (_facingDirection == RIGHT) {
        _facingDirection = LEFT;
        _sprite->setFlipX(true);
        
    }else
    {
        _facingDirection = RIGHT;
        _sprite->setFlipX(false);
    }
    _currentState = IDLE;
    _idleReady = true;
    _runReady = true;
}
void Player::updateAnimation()
{
    playAnimation();
}

void Player::setPosition(float x, float y)
{
    _posX = x;
    _posY = y;
    _sprite->setPosition(ccp(x,y));
}

void Player::playAnimation()
{
    switch (_currentState) {
        case IDLE:
            if(_idleReady)
            {
                _idleReady = false;
                _sprite->runAction(_idle);
            }
            break;
        case TURN:
            if(!_turning)
            {
                _turning = true;
                _runReady = false;
                
                _sprite->stopAllActions();
                _sprite->runAction(_turn);
            }
            break;
        case RUN:
            if(_runReady)
            {
                _runReady = false;
                _sprite->runAction(_run);
            }
            break;
        default:
            _currentState = IDLE;
            break;
    }
}

//void createAnimations()
//{

//}

float Player::positionX()
{
    return _posX;
}

float Player::positionY()
{
    return _posY;
}
