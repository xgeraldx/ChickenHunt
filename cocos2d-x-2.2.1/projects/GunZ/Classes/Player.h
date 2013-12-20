//
//  Player.h
//  GunZ
//
//  Created by Gerald Quick on 12/10/13.
//
//

#ifndef __GunZ__Player__
#define __GunZ__Player__

#include "cocos2d.h"


class Player : public cocos2d::CCObject
{
    

private:
    int _health;
    int _score;
    int _kills;
    float _posX;
    float _posY;
    cocos2d::CCSequence * _idle;
    cocos2d::CCSequence * _turn;
    cocos2d::CCSequence * _run;
    cocos2d::CCSequence * _spool;
    cocos2d::CCSequence * _shoot;
    cocos2d::CCSequence * _cooldown;
    
public:
    cocos2d::CCSprite * _sprite;
    enum DIRECTION {LEFT,RIGHT};
    enum PLAYERSTATE {IDLE,RUN,SPOOL,SHOOT,COOLDOWN,TURN,DEAD};
    PLAYERSTATE _currentState;
    DIRECTION _facingDirection;
    
    Player(void);
    ~Player(void);

    int getHealth();
    int getScore();
    int getKills();
    bool _turning;
    bool _idleReady;
    bool _runReady;
    void addHealth(int);
    void addScore(int);
    void addKill(int);
    void takeDamage(int);
    void setPosition(cocos2d::CCPoint);
    void setPosition(float,float);
    void playAnimation();
    void createAnimation();
    void updateAnimation();
    float positionX();
    float positionY();
    void idleAnimationDone(cocos2d::CCNode *);
    void turnAnimationDone(cocos2d::CCNode *);
    void runAnimationDone(cocos2d::CCNode *);
};

#endif /* defined(__GunZ__Player__) */
