#include "game_basic.h"

#include "ShootPractice.h"
#include "Ball.h"
#include "Goal.h"

USING_NS_CC;

ShootPractice::ShootPractice()
{
}

ShootPractice::~ShootPractice()
{
}

void ShootPractice::onEnter()
{
    CCLayer::onEnter();
    
    //field
    CCSprite* pBackground = CCSprite::create("match/field.jpg");
    pBackground->setPosition(VisibleRect::center());
    addChild(pBackground, 0);
    
    m_ball = Ball::create();
    addChild(m_ball);
    m_ball->retain();
    
    m_goal = Goal::create();
    addChild(m_goal);
    m_goal->retain();
    
    //debug label
    m_debugLabel = CCLabelTTF::create("debug string", "Arial", 12);
    m_debugLabel->setDimensions(CCSizeMake(80, 80));
    m_debugLabel->setPosition(ccp(VisibleRect::left().x + 100, VisibleRect::top().y - 50));
    m_debugLabel->setHorizontalAlignment(kCCTextAlignmentLeft);
    m_debugLabel->setVerticalAlignment(kCCVerticalTextAlignmentTop);
    addChild(m_debugLabel);
    
    //reset button
    CCLabelTTF* pLabel = CCLabelTTF::create("RESET", "Arial", 24);
    CCMenuItemLabel* pItem = CCMenuItemLabel::create(pLabel, this, menu_selector(ShootPractice::resetCallback));
    CCMenu* resetBtn = CCMenu::create(pItem, NULL);
    resetBtn->setPosition(ccp(VisibleRect::right().x - 100, VisibleRect::bottom().y + 100));
    addChild(resetBtn);
    
    setTouchMode(kCCTouchesOneByOne);
    setTouchEnabled(true);
    
    schedule(schedule_selector(ShootPractice::update));
}

void ShootPractice::reset()
{
    m_ball->reset();
}

void ShootPractice::resetCallback(CCObject* pSender)
{
    reset();
}

void ShootPractice::update(float dt)
{
    if(m_goal->checkBall(m_ball))
    {
        CCLog("GOAL!!!!!!!!!!!!!!!!!!!!!!");
    }
}

void ShootPractice::onExit()
{
    m_ball->release();
    m_goal->release();
    
    CCLayer::onExit();
}

bool ShootPractice::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
    if(m_ball && m_ball->containsTouchLocation(touch))
        return false;
    else
        return true;
}

void ShootPractice::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    if(m_ball)
    {
        m_ball->m_debugMovePoint = touch->getLocation();
    }
    m_debugLabel->setString(CCString::createWithFormat(" x:%.2f \n y:%.2f", touch->getLocation().x, touch->getLocation().y)->getCString());
}

void ShootPractice::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
}

