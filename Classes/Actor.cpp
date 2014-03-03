//
//  Actor.cpp
//  RealSoccer
//
//  Created by ck02-216 on 1/9/14.
//
//

#include "Actor.h"
#include "game_basic.h"
#include "match_define.h"

#define MIN_VALUE_TO_ZERO(_value,_min) if(fabs(_value)<_min) _value=0;

Actor::Actor()
:m_posZ(0.0f)
,m_angle(0.0f)
{
    m_speed[X] = m_speed[Y] = m_speed[Z] = 0.0f;
    m_acc[X] = m_acc[Y] = m_acc[Z] = 0.0f;
    m_force[X] = m_force[Y] = m_force[Z] = 0.0f;
    m_lastPos[X] = m_lastPos[Y] = m_lastPos[Z] = 0.0f;
}

Actor::~Actor()
{
}

void Actor::update(float dt)
{
    //CCLog("%f", dt);
}

void Actor::checkMinToZero(int axis)
{
    if(fabs(m_speed[axis]) < fabs(m_acc[axis]) && m_speed[axis]*m_acc[axis] < 0.0f)
    {
        stop(axis);
    }
}

void Actor::stop(int axis)
{
    m_speed[axis] = 0.0f;
    m_acc[axis] = 0.0f;
}

void Actor::stop()
{
    stop(X);
    stop(Y);
    stop(Z);
}

void Actor::force(float forceX, float forceY, float forceZ)
{
    m_force[X] = forceX;
    m_force[Y] = forceY;
    m_force[Z] = forceZ;
}

void Actor::setSpeed(float speedX, float speedY, float speedZ)
{
    m_speed[X] = speedX;
    m_speed[Y] = speedY;
    m_speed[Z] = speedZ;
}

void Actor::updatePosition()
{
    m_speed[X] += m_acc[X];
    m_speed[Y] += m_acc[Y];
    m_speed[Z] += m_acc[Z];
    
    m_lastPos[X] = getPositionX();
    m_lastPos[Y] = getPositionY();
    m_lastPos[Z] = getPositionZ();
    
    setPositionX(getPositionX() + m_speed[X]);
    setPositionY(getPositionY() + m_speed[Y]);
    setPositionZ(getPositionZ() + m_speed[Z]);
}