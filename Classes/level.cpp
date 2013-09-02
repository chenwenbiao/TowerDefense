#include "level.h"
#include "god.h"
NAMESPACE_TD_BEGIN
template<> ITDLevelMgr* CSingleton<ITDLevelMgr>::m_psSingleton = NULL;

CLevel::CLevel():m_pLayer(NULL),m_pMap(NULL),m_wCurrentIndex(0),m_wEnemyCount(1000),m_wTimeInterval(1){

}

CLevel::~CLevel()
{
	CC_SAFE_RELEASE_NULL( m_pMap );
	CC_SAFE_RELEASE_NULL( m_pLayer ); 
}

void CLevel::update(float delta)
{
	static float dtTime = 0;
	dtTime+= delta;
	if ( dtTime < m_wTimeInterval || m_wCurrentIndex >= m_wEnemyCount )
	{
		return;
	}
	if ( m_pLayer == 0 )
	{
		return;
	}
	dtTime = 0;

	ITDObject* pObject = ITDGod::GetSingletonPtr()->Create( "Enemy", m_pLayer );
	if ( pObject )
	{
		do 
		{    			
			CCAnimation* animation = CCAnimation::create();
			animation->addSpriteFrame( CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName( "enemy.png") );
			animation->addSpriteFrame( CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName( "tower.png") );
			animation->addSpriteFrame( CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName( "enemy.png") );
			animation->addSpriteFrame( CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName( "tower.png") );

			// should last 2.8 seconds. And there are 14 frames.
			animation->setDelayPerUnit(2.8f / 14.0f);
			animation->setRestoreOriginalFrame(true);

			CCAnimate* action = CCAnimate::create(animation);
			CCCardinalSplineTo *action2;

			int nTime = 5;
			if ( m_wCurrentIndex % 3 == 0 )
			{
				action2 = CCCardinalSplineTo::create(nTime, m_pMap->GetPath(), 1 );
				pObject->setPosition( m_pMap->GetPath()->getControlPointAtIndex(0) );
			}
			else if ( m_wCurrentIndex % 3 == 1 )
			{
				action2 = CCCardinalSplineTo::create(nTime, m_pMap->GetPath(1), 1 );
				pObject->setPosition(  m_pMap->GetPath(1)->getControlPointAtIndex(0) );
			}
			else
			{
				action2 = CCCardinalSplineTo::create(nTime, m_pMap->GetPath(2), 1 );
				pObject->setPosition( m_pMap->GetPath(2)->getControlPointAtIndex(0) );
			}
			
		//	shptr->runAction( CCMoveTo::create(10, ccp(100,100) ) );
			//CCCardinalSplineTo* reverse2 = (CCCardinalSplineTo*)action2->reverse();		
// 			//	CCSequence *seq2 = CCSequence::create(action2, reverse2, NULL);
			CCSequence* pSequence = CCSequence::create( action, action2, CCCallFunc::create( pObject, callfunc_selector(ITDObject::End) ),	NULL );
			pSequence->setTag(0);
 			pObject->runAction( pSequence );

			pObject->scheduleUpdate();
			m_wCurrentIndex++;
		} while (0);
	}	
}

bool CLevel::Start( ILayer* pLayer, ITDMap* pMap )
{
	setLayer( pLayer );
	setMap( pMap );
	m_pLayer->addChild( this );
	this->scheduleUpdateWithPriority(1);
	return true;
}

bool CLevel::End()
{
	m_pLayer->removeChild( this, true );
	m_wCurrentIndex = 0;
	m_wEnemyCount = 10;
	m_wTimeInterval = 1;
	this->unscheduleUpdate();
	return true;
}

CLevelMgr::CLevelMgr(): m_pLevels(NULL){}
CLevelMgr::~CLevelMgr(){
	CC_SAFE_RELEASE_NULL(m_pLevels);
}
ITDLevel* CLevelMgr::GetLevel( unsigned int wIndex )
{
	if ( wIndex < m_pLevels->count() )
	{
		return (ITDLevel*)m_pLevels->objectAtIndex( wIndex );
	}
	return NULL;
}

bool CLevelMgr::Ini( const String& strPath )
{
	setLevels( CCArray::createWithCapacity(10) );
	ITDLevel* pLevel = new CLevel();
	pLevel->autorelease();
	m_pLevels->addObject( pLevel );
	return false;
}

NAMESPACE_TD_END