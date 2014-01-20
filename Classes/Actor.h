//
//  Actor.h
//  RealSoccer
//
//  Created by ck02-216 on 1/9/14.
//
//

#ifndef __RealSoccer__Actor__
#define __RealSoccer__Actor__

#include "cocos2d.h"

USING_NS_CC;

class Actor : public CCNode
{
public:
    Actor();
    virtual ~Actor();
    
    void setPositionZ(float z) {m_posZ = z;}
    float getPositionZ() {return m_posZ;}
    
    float getLastPosition(int axis) {return m_lastPos[axis];}
    float getSpeed(int axis) {return m_speed[axis];}
    float getAcc(int axis) {return m_acc[axis];}
    
    virtual void update(float dt);
    void updatePosition();
    void checkMinToZero(int axis);
    void stop();
    void stop(int axis);
    void force(float forceX, float forceY, float forceZ);
    void setSpeed(float speedX, float speedY, float speedZ);
    
protected:
    float m_posZ;
    float m_lastPos[3];
    
    float m_speed[3];
    
    float m_acc[3];
    
    float m_force[3];
    
    float m_angle;
};

#endif /* defined(__RealSoccer__Actor__) */
