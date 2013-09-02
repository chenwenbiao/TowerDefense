#pragma once
#include "cocos2d.h"
#include "interfacedef.h"
using namespace cocos2d;
class CBegin : public cocos2d::CCLayer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::CCScene* scene();

	// a selector callback
	void menuCloseCallback(CCObject* pSender);

	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);

	void CreateSprite( const String& strList, const String& strPng, int picNbr, CCPoint ptStart, float nTime = 0.1 );

	// implement the "static node()" method manually
	CREATE_FUNC(CBegin);
};