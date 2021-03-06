//
//  Goal.cpp
//  RealSoccer
//
//  Created by ck02-216 on 1/14/14.
//
//

#include "Goal.h"

#include "match_define.h"
#include "Ball.h"

Goal::Goal()
{
}


Goal::~Goal()
{}

Goal* Goal::create()
{
    Goal* goal = new Goal();
    goal->init();
    goal->autorelease();
    
    return goal;
}

bool Goal::init()
{
    m_goalLeft = GOAL_LEFT;
    m_goalRight = GOAL_RIGHT;
    setPositionX((GOAL_LEFT + GOAL_RIGHT) / 2);
    setPositionY(GOAL_BOTTOM);
    m_goalWidth = (GOAL_RIGHT - GOAL_LEFT);
    m_goalHeight = (GOAL_TOP - GOAL_BOTTOM)/PERSPECTIVE_RATIO;
    m_goalDepth = GOAL_NET_BOTTOM - GOAL_BOTTOM;
    m_postRadius = GOAL_POST_RADIUS;
    return true;
}

void Goal::draw()
{
    glLineWidth(1.0f);
    ccDrawColor4B(0, 0, 255, 255);
    ccDrawCircle(ccp(-m_goalWidth/2, 0.0f), m_postRadius, 0, 10, false);
    ccDrawCircle(ccp(m_goalWidth/2, 0.0f), m_postRadius, 0, 10, false);
}

bool Goal::checkBallWithPost(Ball* ball, bool isLeftPost)
{
    int postX = -m_goalWidth/2;
    if(!isLeftPost)
        postX = m_goalWidth/2;
    
    BallCollisionFlag checkFlag = kBallCollisionLeftPost;
    if(!isLeftPost)
        checkFlag = kBallCollisionRightPost;
    
    if(ball->getLastCollisionFlag() != checkFlag)
    {
        CCPoint postPosition = ccp(getPositionX() + postX, getPositionY());
        float dis = ccpDistance(ball->getPosition(), postPosition);
        if(dis < m_postRadius + ball->getRadius() && ball->getPositionZ() < m_goalHeight)
        {
            CCLog("ballX:%.2f ballY:%.2f postX:%.2f postY:%.2f", ball->getPositionX(), ball->getPositionY(), postPosition.x, postPosition.y);
            
            CCPoint ballSpd = ccp(ball->getSpeed(X), ball->getSpeed(Y));
            float inAngle = ccpNeg(ballSpd).getAngle() * 180 / M_PI;
            float postBallAngle = ccpSub(ball->getPosition(), postPosition).getAngle() * 180 / M_PI;
            float outAngle = postBallAngle - (inAngle - postBallAngle);
            
            if(outAngle < -180.0f)
                outAngle += 360.0f;
            else if (outAngle > 180.0f)
                outAngle -= 360.0f;
            
            CCLog("check post: inAngle:%.2f postBallAngle:%.2f outAngle:%.2f", inAngle, postBallAngle, outAngle);
            
            outAngle = outAngle * M_PI / 180;
            
            ball->stop(X);
            ball->stop(Y);
            ball->setSpeed(ballSpd.getLength() * BALL_BOUNCE_RATIO_WITH_GOAL * cosf(outAngle),
                           ballSpd.getLength() * BALL_BOUNCE_RATIO_WITH_GOAL * sinf(outAngle),
                           ball->getSpeed(Z));
            ball->setLastCollisionFlag(checkFlag);
            return true;
        }
    }
    
    return false;
}

bool Goal::checkBallWithCrossbar(Ball* ball)
{
    if(ball->getLastCollisionFlag() == kBallCollisionCrossbar)
        return false;
    if(ball->getPositionX() < getPositionX() - m_goalWidth/2 || ball->getPositionX() > getPositionX() + m_goalWidth/2)
        return false;
    
    float dis = ccpDistance(ccp(ball->getPositionY(), ball->getPositionZ()), ccp(getPositionY(), m_goalHeight));
    if(dis < m_postRadius + ball->getRadius())
    {
        CCPoint ballSpd = ccp(ball->getSpeed(Y), ball->getSpeed(Z));
        
        float inAngle = ccpNeg(ballSpd).getAngle() * 180 / M_PI;
        float barBallAngle = ccpSub(ccp(ball->getPositionY(), ball->getPositionZ()), ccp(getPositionY(), m_goalHeight)).getAngle() * 180 / M_PI;
        float outAngle = barBallAngle - (inAngle - barBallAngle);
        
        if(outAngle < -180.0f)
            outAngle += 360.0f;
        else if (outAngle > 180.0f)
            outAngle -= 360.0f;
        
        CCLog("check crossbar: inAngle:%.2f barBallAngle:%.2f outAngle:%.2f", inAngle, barBallAngle, outAngle);
        
        outAngle = outAngle * M_PI / 180;
        
        ball->stop(Y);
        ball->stop(Z);
        ball->setSpeed(ball->getSpeed(X),
                       ballSpd.getLength() * BALL_BOUNCE_RATIO_WITH_GOAL * cosf(outAngle),
                       ballSpd.getLength() * BALL_BOUNCE_RATIO_WITH_GOAL * sinf(outAngle));
        ball->setLastCollisionFlag(kBallCollisionCrossbar);
        return true;
    }
    
    
    return false;
}

bool Goal::checkBallWithSideNet(Ball* ball, bool isLeft)
{
    if(ball->getLastCollisionFlag() == kBallCollisionSideNet)
        return false;
    
    int netX = getPositionX() - m_goalWidth/2;
    if(!isLeft)
        netX = getPositionX() + m_goalWidth/2;
    
    if(fabs(ball->getPositionX() - netX) < ball->getRadius()
       && ball->getPositionY() > getPositionY()
       && ball->getPositionY() < getPositionY() + m_goalDepth
       && ball->getPositionZ() < m_goalHeight)
    {
        float spdY = ball->getSpeed(Y);
        
        ball->stop(X);
        ball->stop(Y);
        ball->setSpeed(0.0f, spdY/2, ball->getSpeed(Z));
        ball->setLastCollisionFlag(kBallCollisionSideNet);
        return true;
    }
    
    return false;
}
bool Goal::checkBallWithBackNet(Ball* ball)
{
    if(ball->getLastCollisionFlag() == kBallCollisionBackNet)
        return false;
    
    if(fabsf(ball->getPositionY() - getPositionY() - m_goalDepth) < ball->getRadius()
       && ball->getPositionX() > getPositionX() - m_goalWidth/2
       && ball->getPositionX() < getPositionX() + m_goalWidth/2
       && ball->getPositionZ() < m_goalHeight)
    {
        float spdX = ball->getSpeed(X);
        
        ball->stop(X);
        ball->stop(Y);
        ball->setSpeed(spdX/2, 0.0f, ball->getSpeed(Z));
        ball->setLastCollisionFlag(kBallCollisionBackNet);
        return true;
    }
    
    return false;
}

bool Goal::checkBall(Ball *ball)
{
    //check collision with left post
    checkBallWithPost(ball, true);
    //check collision with right post
    checkBallWithPost(ball, false);
    //check collision with crossbar
    checkBallWithCrossbar(ball);
    //check with net
    checkBallWithSideNet(ball, true);
    checkBallWithSideNet(ball, false);
    checkBallWithBackNet(ball);
    
    return false;
}







