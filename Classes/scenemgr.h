#pragma once

#include "cocos2d.h"
#include <string>
using namespace std;
USING_NS_CC;
typedef CCSprite ISprite;
typedef CCArray IArray;
typedef CCDictionary IDictionary;
typedef CCNode INode;
typedef string String;
typedef CCPoint IPoint;
typedef CCObject IBaseObject;
typedef CCPointArray IPath;

class IAi;

class IPropertyContainer{
	CC_SYNTHESIZE_RETAIN( IDictionary*, m_pProperties, Properties )
public:
	
	float GetPropertyAsFloat( const String& strName ){ 
		const CCString* pStr = m_pProperties->valueForKey( strName );
		if ( pStr )	{
			return pStr->floatValue();
		}
		return 0.0f;
	}
	String GetPropertyAsString( const String& strName ){
		const CCString* pStr = m_pProperties->valueForKey( strName );
		if ( pStr )	{
			return pStr->getCString();
		}
		return "";
	}
	int GetPropertyAsInt( const String& strName ){
		const CCString* pStr = m_pProperties->valueForKey( strName );
		if ( pStr )	{
			return pStr->intValue();
		}
		return 0;
	}
	IPoint GetPropertyAsPoint( const String& strName ){
		const CCString* pStr = m_pProperties->valueForKey( strName );
		if ( pStr )	{
			return CCPointFromString( pStr->getCString() );
		}
		return ccp(0,0);
	}
	
	void SetProperty( const String& strName, float f ){
		m_pProperties->setObject( CCString::createWithFormat("%f",f), strName );
	}
	void SetProperty( const String& strName, String str ){
		m_pProperties->setObject( CCString::create( str ), strName );
	}
	void SetProperty( const String& strName, int i ){
		m_pProperties->setObject( CCString::createWithFormat("%f",i), strName );
	}
	void SetProperty( const String& strName, IPoint pt ){}

public:
	IPropertyContainer() : m_pProperties(NULL){}
	~IPropertyContainer(){
		CC_SAFE_RELEASE_NULL( m_pProperties );
	}
};

class IFollower 
{
public:
	virtual void ParentUpdate(){};
};

class IGObject : public IFollower, public IPropertyContainer, public ISprite
{
	CC_SYNTHESIZE( String, m_strType, Type )
	CC_SYNTHESIZE( String, m_strName, Name )
public:
	IGObject(){}
	~IGObject(){}
	IBaseObject* copyWithZone(CCZone* pZone){

		CCZone* pNewZone = NULL;
		IGObject* pRet = NULL;
		if(pZone && pZone->m_pCopyObject) //in case of being called at sub class
		{
			pRet = (IGObject*)(pZone->m_pCopyObject);
		}
		else
		{
			pRet = new IGObject();
			pZone = pNewZone = new CCZone(pRet);
		}
		if ( getProperties() != NULL )
		{
			pRet->setProperties( (IDictionary*)getProperties()->copy() );
		}
		
		pRet->setType( m_strType );
		pRet->setName( m_strName );

		CC_SAFE_DELETE(pNewZone);
		return pRet;
	}
public:
	virtual void Create(){}
	virtual void Idle(){}
	virtual void Destory(){}
};

class IAi : public INode
{
	CC_SYNTHESIZE_RETAIN( IGObject*, m_pTarget, Target )
	CC_SYNTHESIZE( SEL_CallFuncND, m_func, CallBackFunc )
public:
	IAi( IGObject* pTarget, SEL_CallFuncND func ): m_pTarget(NULL), m_func( func ){
		setTarget( pTarget );
	};
	IAi(): m_pTarget(NULL){}
	~IAi(){
		CC_SAFE_RELEASE_NULL(m_pTarget);
	}
	IBaseObject* copyWithZone(CCZone* pZone)
	{
		CCZone* pNewZone = NULL;
		IAi* pRet = NULL;
		if(pZone && pZone->m_pCopyObject) //in case of being called at sub class
		{
			pRet = (IAi*)(pZone->m_pCopyObject);
		}
		else
		{
			pRet = new IAi();
			pZone = pNewZone = new CCZone(pRet);
		}
		return pRet;
	}
public:
	virtual bool UpdateAi( float dt ){
		return false;
	}
};


class ISkill : public IGObject{
public:
	virtual bool MakeDamage(){}
public:
	virtual void Create(){
		// run animate
		// run idle
	}
	virtual void Idle(){
		// change state
		// call destory
		// unsch
	}
	virtual void Destory(){
		// make hp
		// remove
		// 
	}
	IBaseObject* copyWithZone(CCZone* pZone)
	{
		CCZone* pNewZone = NULL;
		ISkill* pRet = NULL;
		if(pZone && pZone->m_pCopyObject) //in case of being called at sub class
		{
			pRet = (ISkill*)(pZone->m_pCopyObject);
		}
		else
		{
			pRet = new ISkill();
			pZone = pNewZone = new CCZone(pRet);
		}
		return pRet;
	}
};

class ISkillManager : public IBaseObject{
public:
	virtual ISkill* CreateSkill( const String& strName ){
		ISkill* pSkill = new ISkill();
		pSkill->autorelease();
		return pSkill;
	}
};
class Intelligent : public IGObject{
	CC_SYNTHESIZE_RETAIN( IArray*, m_pAis, Ais )
	CC_SYNTHESIZE_RETAIN( IDictionary*, m_pFollowers, Followers )
	CC_SYNTHESIZE_RETAIN( IArray*, m_pSkills, Skills )
public:
	Intelligent(): m_pFollowers(NULL), m_pAis(NULL), m_pSkills(NULL){
		setAis( IArray::createWithCapacity(10) );
		setFollowers( IDictionary::create() );
		setSkills( IArray::createWithCapacity(10) );
	}
	~Intelligent(){
		CC_SAFE_RELEASE_NULL( m_pAis );
		CC_SAFE_RELEASE_NULL( m_pFollowers );
		CC_SAFE_RELEASE_NULL( m_pSkills );
	}
	IBaseObject* copyWithZone(CCZone* pZone)
	{
		CCZone* pNewZone = NULL;
		Intelligent* pRet = NULL;
		if(pZone && pZone->m_pCopyObject) //in case of being called at sub class
		{
			pRet = (Intelligent*)(pZone->m_pCopyObject);
		}
		else
		{
			pRet = new Intelligent();
			pZone = pNewZone = new CCZone(pRet);
		}
		IGObject::copyWithZone(pZone);

		pRet->initWithTexture( this->getTexture() );
		
		if ( m_pAis != NULL )
		{
			//IArray* pCopy = (IArray*)m_pAis->copy();
			IBaseObject* pObject = NULL;
			CCARRAY_FOREACH( m_pAis, pObject ){
				IAi* pTemp = dynamic_cast<IAi*>(pObject);
				if ( pTemp ){
					pRet->AddAi( (IAi*)pTemp->copy() );
				}
			}
		}
		if ( m_pFollowers != NULL )
		{
			pRet->setFollowers( (IDictionary*)getFollowers()->copy() );
		}
		if ( m_pSkills != NULL )
		{
			pRet->setSkills( (IArray*)getSkills()->copy() );
		}

		CC_SAFE_DELETE(pNewZone);
		return pRet;
	}
public:
	virtual void AddFollower( const String& strKey, IGObject* pObject ){
		IArray* pArray = dynamic_cast<IArray*>(m_pFollowers->objectForKey( strKey ));
		if ( pArray == 0 ){
			IArray* pArray = new IArray();
			pArray->initWithObject( pObject );
			m_pFollowers->setObject( pArray, strKey );
		}
		else{
			pArray->addObject( pObject );
		}
	}

	virtual void RemoveFollower( const String& strKey ){
		m_pFollowers->removeObjectForKey( strKey );
	}

	virtual void AddAi( IAi* pAi ){
		pAi->setTarget( this );
		m_pAis->addObject( pAi );
	}
	virtual void ChangeState( const String& strState ){
		UpdateFollowers( strState );
	}
	void update(float delta){
		UpdateAis( delta );
	}
	virtual void Attack(){
	}
protected:
	void UpdateAis( float dt )
	{
		IBaseObject* pObject = NULL;
		CCARRAY_FOREACH( m_pAis, pObject )
		{
			IAi* pAi = dynamic_cast<IAi*>(pObject);
			if ( pAi && pAi->UpdateAi( dt ) == true )
			{
				break;
			}
		}
	}
	void UpdateFollowers( const String& strName ){
		IArray* pArray = dynamic_cast<IArray*>(m_pFollowers->objectForKey( strName ));
		if ( pArray )
		{
			IBaseObject* pObject = NULL;
			CCARRAY_FOREACH( pArray, pObject ){
				IGObject* pTemp = dynamic_cast<IGObject*>(pObject);
				if ( pTemp ){
					pTemp->ParentUpdate();
				}
			}
		}
	}
};

class CMoveAi : public IAi
{
	CC_SYNTHESIZE_RETAIN( IPath*, m_pPath, Path )
public:
	CMoveAi( IPath* pPath, IGObject* pTarget, SEL_CallFuncND func ) : IAi( pTarget, func ), m_pPath(NULL){
		setPath( pPath );
	}
	CMoveAi(): m_pPath(NULL){}
	~CMoveAi(){
		CC_SAFE_RELEASE_NULL( m_pPath );
	}
	IBaseObject* copyWithZone(CCZone* pZone)
	{
		CCZone* pNewZone = NULL;
		CMoveAi* pRet = NULL;
		if(pZone && pZone->m_pCopyObject) //in case of being called at sub class
		{
			pRet = (CMoveAi*)(pZone->m_pCopyObject);
		}
		else
		{
			pRet = new CMoveAi();
			pZone = pNewZone = new CCZone(pRet);
		}
		// don't copy target and callbackfunc
		if ( m_pPath != NULL )
		{
			pRet->setPath( (IPath*)m_pPath->copy());
		}	
		CC_SAFE_DELETE(pNewZone);
		return pRet;
	}
public:

	bool UpdateAi( float dt ){
		Move( dt );
		if ( IsEnd() ){
			/*this->func( NULL, NULL );*/
		}
		return false;
	}
protected:
	void Move( float dt ){
		getTarget()->runAction( CCMoveBy::create( 1, ccp(10,10) ) );
	}
	bool IsEnd(){ return false;}
};

class CAttackAi : public IAi
{
	CC_SYNTHESIZE_RETAIN( IArray*, m_pAttackList, AttackList )
public:
	CAttackAi( IArray* pAttackList, IGObject* pTarget, SEL_CallFuncND func ) : IAi( pTarget, func ){
		setAttackList( pAttackList );
	}
	CAttackAi() : IAi(){}
	~CAttackAi()
	{
		CC_SAFE_RELEASE_NULL( m_pAttackList );
	}

	IBaseObject* copyWithZone(CCZone* pZone)
	{
		CCZone* pNewZone = NULL;
		CAttackAi* pRet = NULL;
		if(pZone && pZone->m_pCopyObject) //in case of being called at sub class
		{
			pRet = (CAttackAi*)(pZone->m_pCopyObject);
		}
		else
		{
			pRet = new CAttackAi();
			pZone = pNewZone = new CCZone(pRet);
		}
		// don't copy target and callbackfunc
		pRet->setAttackList( (IArray*)m_pAttackList->copy() );
		CC_SAFE_DELETE(pNewZone);
		return pRet;
	}
public:

	bool UpdateAi( float dt ){
		Attack();
		return false;
	}
protected:
	void Attack(){

	}
};

class HPDisplay : public IGObject{
	CC_SYNTHESIZE_RETAIN( IGObject*, m_pParent, Parent )
public:
	HPDisplay( IGObject* pParent ) : m_pParent(NULL){
		setParent( pParent );
	}
	~HPDisplay(){
		CC_SAFE_RELEASE( m_pParent );
	}
	void AutoHide( float dt ){
		setVisible( false );
	}
	bool DoChange(){
		unschedule( schedule_selector(HPDisplay::AutoHide) );
		ShowHp();
		schedule( schedule_selector(HPDisplay::AutoHide), 2.0f );
	}

protected:
	void ShowHp(){
		this->setVisible( true );
		int hp = m_pParent->GetPropertyAsInt( "hp" );
	}
};

class IAiManager : public IBaseObject
{
public:
	virtual IAi* CreateAi( const String& strName ){
		IAi* pAi = NULL;
		if ( strName == "move" )
		{
			pAi = new CMoveAi();
			pAi->autorelease();
		}
		else if ( strName == "attack" )
		{
			pAi = new CAttackAi();
			pAi->autorelease();
		}
		return pAi;
	}
};

class IGObjectManager
{
public:
	static CCSprite* CreateObject( const String& strName ){
		CCSprite* pObject = CCSprite::create( strName.c_str() );
		return pObject;
	}
};
