//
//  Ball.cpp
//  RealSoccer
//
//  Created by ck02-216 on 1/8/14.
//
//

#include "Ball.h"
#include "game_basic.h"
#include "match_define.h"

Ball::Ball()
:m_state(kBallStateIdle)
,m_ballAnimRoll()
,m_ballSpr()
,m_touchPoint(CCPointZero)
,m_indicatorPoint(CCPointZero)
,m_ballRadius(0.0f)
,m_rect(CCRectZero)
,m_touchRect(CCRectZero)
,m_lastCollisionFlag(kBallCollisionNone)
{
    Actor::Actor();
    //sprite frame cache
    CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile("match/ball.plist");
}

Ball::~Ball()
{
    CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->removeSpriteFramesFromFile("match/ball.plist");
    
    m_ballAnimRoll->release();
}

bool Ball::init()
{
    //initial ball default shadow texture and some properties.
    //CCSprite::init();
    setPosition(VisibleRect::center());
    m_touchPoint = getPosition();
    m_ballRadius = BALL_RADIUS;
    
    m_rect = CCRectMake(-m_ballRadius, -m_ballRadius, m_ballRadius*2, m_ballRadius*2);
    m_touchRect = CCRectMake(-m_ballRadius*4, -m_ballRadius*4, m_ballRadius*8, m_ballRadius*8);
    
    //ball roll animation
    CCArray* animFrames = CCArray::createWithCapacity(12);
    char str[100] = {0};
    for(int i = 1; i <= 12; i++)
    {
        sprintf(str, "ball_%02d.png", i);
        CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
        animFrames->addObject(frame);
    }
    m_ballAnimRoll = CCAnimation::createWithSpriteFrames(animFrames, 0.1f);
    m_ballAnimRoll->retain();
    
    CCSprite* shadowSpr = CCSprite::createWithSpriteFrameName("ball_shadow.png");
    addChild(shadowSpr);
    
    
    //add ball sprite as a child node.
    m_ballSpr = CCSprite::createWithSpriteFrameName("ball_01.png");
    addChild(m_ballSpr);
    
    //debug label
    m_debugLabel = CCLabelTTF::create("debug string", "Arial", 12);
    m_debugLabel->setDimensions(CCSizeMake(80, 80));
    m_debugLabel->setPosition(ccp(-80,- 20));
    m_debugLabel->setHorizontalAlignment(kCCTextAlignmentLeft);
    addChild(m_debugLabel);
    
    
    update(0);
    
    schedule(schedule_selector(Ball::update));
    
    return true;
}

void Ball::reset()
{
    float offX = (float)(rand() % 200 - 100);
    float offY = (float)(rand() % 100);
    setPosition(ccp(VisibleRect::center().x + offX, VisibleRect::center().y + offY));
    setPositionZ(0.0f);
    stop();
    setState(kBallStateIdle);
}

void Ball::setState(BallState state)
{
    if(state == kBallStateMoveOnGround || state == kBallStateMoveInAir)
    {
        m_ballAnimRoll->setDelayPerUnit(0.1f);
        m_ballSpr->runAction(CCRepeatForever::create(CCAnimate::create(m_ballAnimRoll)));
    }
    else
    {
        m_ballSpr->stopAllActions();
    }
    m_state = state;
}

void Ball::update(float dt)
{
    dt = 0.033f;//temp for dev
    
    Actor::update(dt);
    
    if(m_force[X] != 0.0f)
    {
        m_speed[X] = m_force[X] * dt;
        m_force[X] = 0.0f;
    }
    if(m_force[Y] != 0.0f)
    {
        m_speed[Y] = m_force[Y] * dt;
        m_force[Y] = 0.0f;
    }
    if(m_force[Z] != 0.0f)
    {
        m_speed[Z] = m_force[Z] * dt;
        m_force[Z] = 0.0f;
    }
    
    CCPoint speed = ccp(getSpeed(X), getSpeed(Y));
    m_angle = speed.getAngle();
    if(m_state == kBallStateMoveInAir)
    {
        m_acc[Z] = -GRAVITY_ACC * dt;
    }
    else if(m_state == kBallStateMoveOnGround)
    {
        m_acc[X] = - cosf(m_angle) * RESISTANCE_GROUND * dt;
        m_acc[Y] = - sinf(m_angle) * RESISTANCE_GROUND * dt;
    }
    
    updatePosition();
    
    if(m_state == kBallStateMoveInAir)
    {
        if(m_posZ <= 0)//bounce on ground
        {
            m_posZ = 0;
            m_speed[Z] = -m_speed[Z] * BALL_BOUNCE_RATIO_ONGROUND;
            if(m_speed[Z] < -m_acc[Z])
            {
                stop(Z);
                setState(kBallStateMoveOnGround);
            }
        }
    }
    else if(m_state == kBallStateMoveOnGround)
    {
        checkMinToZero(X);
        checkMinToZero(Y);
        if(m_speed[X] == 0.0f && m_speed[Y] == 0.0f)
        {
            setState(kBallStateIdle);
        }
    }
    
    //m_ballSpr->setPositionY(rect().size.height/2 + m_posZ * PERSPECTIVE_RATIO);
    m_ballSpr->setPositionY(m_posZ * PERSPECTIVE_RATIO);
    
    m_debugLabel->setString(CCString::createWithFormat(" x:%.2f \n y:%.2f \n angle:%.2f", getPositionX(), getPositionY(), m_angle / M_PI * 180)->getCString());
}

void Ball::draw()
{
    //CCSprite::draw();
    glLineWidth(1.0f);
    ccDrawColor4B(255, 255, 255, 255);
    //ccDrawRect(m_rect.origin, ccpAdd(m_rect.origin, m_rect.size));
    ccDrawCircle(ccp(0.0f, 0.0f), m_ballRadius, 0, 10, false);
    
    ccDrawColor4B(0, 255, 255, 255);
    ccDrawLine(ccp(-100.0f, 0.0f), ccp(100.0f, 0.0f));
    ccDrawLine(ccp(0.0f, -100.0f), ccp(0.0f, 100.0f));
    
    if(m_state == kBallStateAim)
    {
        drawBallIndicator();
    }
}

void Ball::drawBallIndicator()
{
    //draw ball indicator
    m_indicatorPoint = ccpMult(ccpSub(getPosition(), m_touchPoint), 0.5);
    m_angle = m_indicatorPoint.getAngle();
    float ballIndicatorLen = m_touchPoint.getDistance(getPosition()) / 2;
    if(ballIndicatorLen > BALL_INDICATOR_MAX_LEN)
    {
        m_indicatorPoint = ccpMult(ccpSub(getPosition(), m_touchPoint), 0.5 * BALL_INDICATOR_MAX_LEN / ballIndicatorLen);
        ballIndicatorLen = BALL_INDICATOR_MAX_LEN;
    }
    
    GLubyte alpha = 255 * (ballIndicatorLen / BALL_INDICATOR_MAX_LEN);
    ccDrawColor4B(255, 0, 0, alpha);
    glLineWidth(BALL_INDICATOR_WIDTH);
    ccDrawLine(ccp(0, 0), m_indicatorPoint);
    
    ccDrawColor4B(255, 255, 255, 255);
    glLineWidth(1.0f);
    ccDrawLine(ccp(0.0f, 0.0f), ccpMult(m_indicatorPoint, 5.0f));
    
    //reduce drawpoint length to avoid pixel missing.
    CCPoint triAngleDrawPoint = ccpSub(m_indicatorPoint, ccpMult(ccpNormalize(m_indicatorPoint), 3.0f));
    
    float sinA = sinf(m_angle);// triAngleDrawPoint.y / ballIndicatorLen;
    float cosA = cosf(m_angle);// triAngleDrawPoint.x / ballIndicatorLen;
    
    CCPoint p1 = ccp(BALL_INDICATOR_TRIANGLE_WIDTH * cosA, BALL_INDICATOR_TRIANGLE_WIDTH * sinA);
    CCPoint p2 = ccp(BALL_INDICATOR_TRIANGLE_WIDTH * sinA, -BALL_INDICATOR_TRIANGLE_WIDTH * cosA);
    CCPoint vertices[] = {ccpAdd(triAngleDrawPoint, p1), ccpAdd(triAngleDrawPoint, p2), ccpSub(triAngleDrawPoint, p2)};
    ccDrawSolidPoly(vertices, 3, ccc4f(1.0f, 0.0f, 0.0f, alpha/255.0f));
}

Ball* Ball::create()
{
    Ball* ball = new Ball();
    ball->init();
    ball->autorelease();
    
    return ball;
}

void Ball::onEnter()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    CCNode::onEnter();
}

void Ball::onExit()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->removeDelegate(this);
    CCNode::onExit();
}

CCRect Ball::rect()
{
    return m_rect;
}

CCRect Ball::touchRect()
{
    return m_touchRect;
}

bool Ball::containsTouchLocation(CCTouch* touch)
{
    return touchRect().containsPoint(convertTouchToNodeSpaceAR(touch));
}

bool Ball::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
    if(m_state != kBallStateIdle)
        return false;
    if(!containsTouchLocation(touch))
        return false;
    
    setState(kBallStateAim);
    return true;
}

void Ball::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    CCAssert(m_state == kBallStateAim, "Ball - Unexpected state!");
    
    m_touchPoint = touch->getLocation();
}

void Ball::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
    CCAssert(m_state == kBallStateAim, "Ball - Unexpected state!");
    
    force(m_indicatorPoint.x * BALL_FORCE_MIN_FACTOR, m_indicatorPoint.y * BALL_FORCE_MIN_FACTOR, 80.0f * BALL_FORCE_MIN_FACTOR);
    //force(0.0f, 0.0f, 50.f * BALL_FORCE_MIN_FACTOR);
    setState(kBallStateMoveInAir);
    setLastCollisionFlag(kBallCollisionNone);
}