#pragma once
#include "cocos2d.h"
using namespace cocos2d;
#include "templclassdef.h"

typedef CCNode INode;
typedef CCSprite ISprite;
typedef CCLayer ILayer;
typedef CCPoint IPoint;
typedef CCPointArray Path;
typedef unsigned int ID;
typedef CCObject IObject;

NAMESPACE_TD_BEGIN
class ITDObject;
class IAi : public INode{
public:
	virtual void Update( float dt, ITDObject* pObject ) = 0;
	CC_SYNTHESIZE( String, m_strType, Type )
};

class ITDObject : public ISprite{
	CC_SYNTHESIZE( IAi*, m_pAI, AI )
	CC_SYNTHESIZE( String, m_strType, Type)
	CC_SYNTHESIZE_RETAIN( CCProgressTimer*, m_pHPProgress, HPProgress );
public:
	ITDObject(const String& strType ) : m_pAI(0),m_pHPProgress(0), m_strType( strType), m_strState("") {}
	~ITDObject(){
		CC_SAFE_RELEASE_NULL( m_pHPProgress );
		CC_SAFE_RELEASE_NULL( m_pAI );
	}
	virtual void ChangeState( const String& strState ) = 0;	
	virtual void End(){}
	int m_nHP;
protected:
	String m_strState;
};

class ITDGod : public CSingleton<ITDGod>, public IObject{
	DEF_MEMBER( CCLayer*, m_pLayer, Layer)
public:
	virtual ITDObject* Create( const String& strName, INode* pNode, const String& strType = "Enemy" ) = 0;
	virtual void Remove( ID id, const String& strType = "" ) = 0;
	virtual void Remove( ITDObject* pObject ) = 0;
	virtual bool Traversal( CDelegateBase* pFun, const String& strType = "" ) = 0;
	virtual bool Ini( const String& strPath ) = 0;
	virtual ITDObject* GetObject( ID id, const String& strType = "" ) = 0;
};

class ITDMap : public INode{
public:
	virtual Path* GetPath( ID id = 0 ) = 0;
	virtual bool IsVisiblePosition( const IPoint* pt ) = 0;
	virtual bool DecorateLayer( ILayer* pLayer ) = 0;
protected:
	virtual bool LoadMap( const String& strFile) = 0;  
	friend class ITDMapMgr;
};


class ITDMapMgr : public CSingleton<ITDMapMgr>{
public:
	virtual bool Ini( const String& strPath ) = 0;
	virtual ITDMap* GetMap(unsigned int wIndex ) = 0;
};


class IActionMgr : public CSingleton<IActionMgr>
{
public:
	virtual bool DoAction( const ITDObject* pTagObject, const String& strAction ) = 0;
	virtual bool Ini( const String& strPath ) = 0;
};


class ITDLevel : public INode{
public:
	virtual bool Start( ILayer* pLayer, ITDMap* pMap ) = 0;
	virtual bool End() = 0;
protected:
	virtual bool LoadLevel( const String& strFile ) = 0;
	friend class ITDLevelMgr;
};

class ITDLevelMgr : public CSingleton<ITDLevelMgr>
{
public:
	virtual bool Ini( const String& strPath ) = 0;
	virtual ITDLevel* GetLevel( unsigned int wIndex ) = 0;
};

class IAiMgr : public CSingleton<IAiMgr>{
public:
	virtual void DecorateObject( ITDObject* pObject ) = 0;
	virtual bool Ini( const String& strPath ) = 0;
	virtual IAi* GetAi( const String& strType ) = 0;
};
NAMESPACE_TD_END