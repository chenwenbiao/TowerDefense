#include "tower.h"

NAMESPACE_TD_BEGIN

const String IEnemy::strTypeEnemy = "Enemy";
const String ITower::strTypeTower = "Tower";

ITower::ITower() : ITDObject( ITower::strTypeTower ){
	m_nHP = 10;
}

ITDObject* ITower::create( const String& strFileName )
{
	ITower* pBody = new ITower();
	pBody->initWithSpriteFrameName( strFileName.c_str() );
	pBody->autorelease();
	return pBody;
}

ITDObject* ITower::create( int nX, int nY, const String& strFileName )
{
	ITDObject* pBody = ITower::create( strFileName );
	pBody->setPosition( ccp(nX, nY) );
	return pBody;
}

ITDObject* ITower::create( CCTexture2D* pTextrue2D )
{
	ITDObject* pBody = new ITower();
	pBody->initWithTexture( pTextrue2D );
	pBody->autorelease();
	return pBody;
}


void ITower::ChangeState( const String& strState )
{
// 	CCActionInterval*  action1 = CCTintTo::create(0.3, 255, 0, 255);
// 	CCActionInterval*  action2 = CCTintBy::create(0.3, -127, -255, -127);
// 	CCActionInterval*  action2Back = action2->reverse();
// 
// 	runAction( action1);
// 	runAction( CCSequence::create( action2, action2Back, NULL));

	CCSpeed* pSpeed = CCSpeed::create( (CCActionInterval*)this->getActionByTag(0), 0.5 );
}

void ITower::update( float dt )
{
	if ( m_pAI != 0 )
	{
		m_pAI->Update( dt, this );
	}
}

void ITower::End()
{
	m_pAI = NULL;
}

IEnemy::IEnemy( INode* pNode ) : ITDObject( IEnemy::strTypeEnemy ){
	m_nHP = 99;
	CCProgressTimer* pHP = CCProgressTimer::create( CCSprite::create( "hp.png" ) );
	setHPProgress( pHP );
	pHP->setPercentage(100);		//设置初始百分比的值
	pHP->setBarChangeRate(ccp(1, 0));    //设置进度条的长度和高度开始变化的大小
	pHP->setType(kCCProgressTimerTypeBar);    //设置进度条为水平
	pNode->addChild( pHP );
}

ITDObject* IEnemy::create( const String& strFileName, INode* pNode )
{
	IEnemy* pBody = new IEnemy( pNode);
	pBody->initWithSpriteFrameName( strFileName.c_str() );
	pBody->autorelease();
	return pBody;
}

ITDObject* IEnemy::create( int nX, int nY, const String& strFileName )
{
	ITDObject* pBody = IEnemy::create( strFileName, NULL );
	pBody->setPosition( ccp(nX, nY) );
	return pBody;
}

ITDObject* IEnemy::create( CCTexture2D* pTextrue2D )
{
	ITDObject* pBody = new IEnemy( NULL );
	pBody->initWithTexture( pTextrue2D );
	pBody->autorelease();
	return pBody;
}

void IEnemy::ChangeState( const String& strState )
{
	CCActionInterval*  action1 = CCTintTo::create(0.3, 255, 0, 255);
	CCActionInterval*  action2 = CCTintBy::create(0.3, -127, -255, -127);
	CCActionInterval*  action2Back = action2->reverse();

	runAction( action1);
	runAction( CCSequence::create( action2, action2Back, NULL));
// 	CCSpeed* pSpeed = CCSpeed::create( (CCActionInterval*)this->getActionByTag(0), 0.5 );
// 	this->runAction( pSpeed );
}

void IEnemy::update( float dt )
{
	getHPProgress()->setPosition( ccp( this->getPositionX() , this->getPositionY() + this->getContentSize().height ) );    //放置进度条位置
	getHPProgress()->setPercentage( m_nHP );
	if ( m_pAI != 0 )
	{
		m_pAI->Update( dt, this );
	}
}

void IEnemy::End()
{
	getHPProgress()->removeFromParentAndCleanup( true );
	this->removeFromParentAndCleanup( true );

	ITDGod::GetSingletonPtr()->Remove( this );
}

NAMESPACE_TD_END