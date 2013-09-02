#include "god.h"
#include "tower.h"

NAMESPACE_TD_BEGIN

template<> ITDGod* CSingleton<ITDGod>::m_psSingleton = NULL;

CTDGod::CTDGod(){
	m_pEnemy = NULL;
	m_pTower = NULL;
	m_pSpriteBatchNode = NULL;
}
CTDGod::~CTDGod(){
	CC_SAFE_RELEASE_NULL( m_pEnemy );
	CC_SAFE_RELEASE_NULL( m_pTower );
	CC_SAFE_RELEASE_NULL( m_pSpriteBatchNode );
}


ITDObject* CTDGod::Create( const String& strName, INode* pNode, const String& strType /* = "Enemy" */ ) {
	ITDObject* pObject = NULL;
	if ( strType == ITower::strTypeTower )
	{
		pObject = ITower::create( "tower.png" );
		m_pTower->addObject( pObject );
		pNode->addChild( pObject );
	}
	else if ( strType == IEnemy::strTypeEnemy )
	{
		pObject = IEnemy::create( "enemy.png",pNode );
		m_pEnemy->addObject( pObject );
		pNode->addChild( pObject );
	}
	return pObject;
}
void CTDGod::Remove( ID id, const String& strType ){
	
	if ( strType == "" )
	{
		if ( RemoveFromArray( m_pEnemy, id ) == false )
		{
			RemoveFromArray( m_pTower, id );
		}
	}
	else
	{
		if ( strType == ITower::strTypeTower )
		{
			RemoveFromArray( m_pTower, id );
		}
		else
		{
			RemoveFromArray( m_pEnemy, id );
		}
	}
}
void CTDGod::Remove( ITDObject* pObject ){
	if ( pObject )
	{
		if ( pObject->getType() == ITower::strTypeTower )
		{
			m_pTower->fastRemoveObject( pObject );
		}
		else{
			m_pEnemy->fastRemoveObject( pObject );
		}
	}
}
bool CTDGod::Traversal( CDelegateBase* pFun, const String& strType ){
	if ( strType == "" )
	{
		if ( TraversalFromArray( m_pEnemy, pFun ) )
		{
			return TraversalFromArray( m_pTower, pFun );
		}		
	}
	else
	{
		if ( strType == ITower::strTypeTower )
		{
			return TraversalFromArray( m_pTower, pFun );
		}
		else if ( strType == IEnemy::strTypeEnemy )
		{
			return TraversalFromArray( m_pEnemy, pFun );
		}
	}
	return false;
}
bool CTDGod::Ini( const String& strPath ){

	setTowers( CCArray::createWithCapacity(100) );
	setEnemys( CCArray::createWithCapacity(100) );

	String strFileName = strPath + "source.plist";
	String strFileName2 = strPath + "source.png"; 
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile( strFileName.c_str(), strFileName2.c_str());

	return 0;
}

ITDObject* CTDGod::GetObject( ID id, const String& strType ){
	if ( strType == "" )
	{
		if ( GetObjecFromArray( m_pEnemy, id ) )
		{
			return GetObjecFromArray( m_pTower, id );
		}		
	}
	else
	{
		if ( strType == ITower::strTypeTower )
		{
			return GetObjecFromArray( m_pTower, id );
		}
		else if ( strType == IEnemy::strTypeEnemy )
		{
			return GetObjecFromArray( m_pEnemy, id );
		}
	}
	return NULL;
}


bool CTDGod::RemoveFromArray( cocos2d::CCArray* pArray, ID id )
{
	CCObject *pObject = NULL;
	CCARRAY_FOREACH(pArray, pObject)
	{
		if ( pObject->m_uID == id )
		{
			pArray->fastRemoveObject( pObject );
			return true;
		}
	}
	return false;
}

bool CTDGod::TraversalFromArray( cocos2d::CCArray* pArray, CDelegateBase* pFun )
{
	CCObject *pObject = NULL;
	CCARRAY_FOREACH(m_pEnemy, pObject)
	{	
		if ( (*pFun)( (void*)pObject ) == false )
		{
			return false;
		}
	}
	return true;
}

ITDObject* CTDGod::GetObjecFromArray( cocos2d::CCArray* pArray, ID id )
{
	CCObject *pObject = NULL;
	CCARRAY_FOREACH(pArray, pObject)
	{
		if ( pObject->m_uID == id )
		{
			return (ITDObject*)pObject;
		}
	}
	return NULL;
}

NAMESPACE_TD_END