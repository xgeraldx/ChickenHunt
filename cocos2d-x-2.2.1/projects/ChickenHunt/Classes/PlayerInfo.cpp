//
//  PlayerInfo.cpp
//  ChickenHunt
//
//  Created by Gerald Quick on 12/19/13.
//
//

#include "PlayerInfo.h"

PlayerInfo* PlayerInfo::m_PlayerInfo = NULL;

PlayerInfo::PlayerInfo()
{
}

PlayerInfo* PlayerInfo::GetInstance(void)
{
    if(NULL == m_PlayerInfo)
    {
        m_PlayerInfo = new PlayerInfo();
    }
    
    return m_PlayerInfo;
}
int PlayerInfo::getScore()
{
    return Score;
}

void PlayerInfo::setScore(int value)
{
    Score = value;
}