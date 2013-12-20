//
//  PlayerInfo.h
//  ChickenHunt
//
//  Created by Gerald Quick on 12/19/13.
//
//

#ifndef __ChickenHunt__PlayerInfo__
#define __ChickenHunt__PlayerInfo__

#include "cocos2d.h"

class PlayerInfo
{
private:
    int Score;
    int Misses;
    int Kills;
    
    
public:
    PlayerInfo();
    static PlayerInfo* GetInstance();
    static PlayerInfo* m_PlayerInfo;
    int getScore();
    void setScore(int value);
};

#endif /* defined(__ChickenHunt__PlayerInfo__) */
