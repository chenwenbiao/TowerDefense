#pragma once
#include "cocos2d.h"
#include "interfacedef.h"

NAMESPACE_TD_BEGIN
class ITower : public ITDObject
{
public:
	static const String strTypeTower;
public:
	ITower();

	virtual void ChangeState( const String& strState );

	virtual void update(  float dt );

	static ITDObject* create( int nX, int nY, const String& strFileName );

	static ITDObject* create( const String& strFileName );

	static ITDObject* create( CCTexture2D* pTextrue2D );

	virtual void End();
};

class IEnemy : public ITDObject
{
public:
	static const String strTypeEnemy;
public:
	IEnemy( INode* pNode );

	virtual void ChangeState( const String& strState );

	virtual void update(  float dt );

	static ITDObject* create( int nX, int nY, const String& strFileName );

	static ITDObject* create( const String& strFileName, INode* pNode );

	static ITDObject* create( CCTexture2D* pTextrue2D );

	virtual void End();
};
NAMESPACE_TD_END