//
//  Goal.h
//  RealSoccer
//
//  Created by ck02-216 on 1/14/14.
//
//

#ifndef __RealSoccer__Goal__
#define __RealSoccer__Goal__

#include "cocos2d.h"

USING_NS_CC;

class Ball;
class Goal : public CCNode
{
public:
    Goal();
    ~Goal();
    
    bool init();
    
    bool checkBall(Ball* ball);
    bool checkBallWithPost(Ball* ball, bool isLeftPost);
    bool checkBallWithCrossbar(Ball* ball);
    
    virtual void draw();
    
    static Goal* create();
    
private:
    float m_goalLeft;
    float m_goalRight;
    float m_goalWidth;
    float m_goalHeight;
    float m_postRadius;
};

#endif /* defined(__RealSoccer__Goal__) */
