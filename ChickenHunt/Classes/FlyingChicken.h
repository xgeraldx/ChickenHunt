//
//  FlyingChicken.h
//  ChickenHunt
//
//  Created by Gerald Quick on 12/13/13.
//
//

#ifndef __ChickenHunt__FlyingChicken__
#define __ChickenHunt__FlyingChicken__
#include "Chicken.h"


enum FLYINGDIRECTION {LEFT,RIGHT};
enum CHICKENTYPE {LARGE,MED,SMALL};

class FlyingChicken : public Chicken
{

private:
    cocos2d::CCSequence * _flying;
    //cocos2d::CCSequence * _die;
    
public:
    CHICKENTYPE chickenType;
    FlyingChicken(CHICKENTYPE cType, bool vis);
    ~FlyingChicken(void);
    FLYINGDIRECTION flyingDirection;
    virtual void createAnimations();
    void flyingAnimationDone(cocos2d::CCNode * pSender);
};


#endif /* defined(__ChickenHunt__FlyingChicken__) */
