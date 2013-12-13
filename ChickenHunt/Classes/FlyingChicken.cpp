//
//  FlyingChicken.cpp
//  ChickenHunt
//
//  Created by Gerald Quick on 12/13/13.
//
//

#include "FlyingChicken.h"

using namespace cocos2d;

FlyingChicken::FlyingChicken(CHICKENTYPE cType, bool vis)
{
    chickenType = cType;
    _bDead = false;
    _bVisible = vis;
    
}

FlyingChicken::~FlyingChicken()
{}

void FlyingChicken::createAnimations()
{
    
    CCAnimation* animation;
    CCSpriteFrame * frame;
    
    //create CCAnimation object
    animation = CCAnimation::create();
    CCString * name;
    for(int i = 0; i <= 12; i++) {
        name = CCString::createWithFormat("chickFlyLarge%i.png", i);
        frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
        animation->addSpriteFrame(frame);
    }
    
    animation->setDelayPerUnit(3 / 13.0f);
    animation->setRestoreOriginalFrame(true);
    _flying = CCSequence::create(
                               CCAnimate::create(animation),
                               CCCallFuncN::create(this, callfuncN_selector(FlyingChicken::flyingAnimationDone)),
                               NULL);
    _flying->retain();
    
    animation = CCAnimation::create();
    
    for(int i = 0; i <= 7; i++) {
        name = CCString::createWithFormat("chickFlyDieLarge%i.png", i);
        frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
        animation->addSpriteFrame(frame);
    }
    
    animation->setDelayPerUnit(3 / 7.0f);
    animation->setRestoreOriginalFrame(true);
    _die = CCSequence::create(
                                 CCAnimate::create(animation),
                                 CCCallFuncN::create(this, callfuncN_selector(FlyingChicken::flyingAnimationDone)),
                                 NULL);
    _die->retain();
}

void FlyingChicken::flyingAnimationDone(CCNode * pSender)
{

}