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

}

void Player::setPosition(float x, float y)
{

}

void Player::playAnimations()
{
    switch (_currentState) {
        case IDLE:
            
            break;
        case TURN:
            break;
        case RUN:
            break;
        default:
            _currentState = IDLE;
            break;
    }
}

void createAnimations()
{

}

float Player::positionX()
{
    return _posX;
}

float Player::positionY()
{
    return _posY;
}
