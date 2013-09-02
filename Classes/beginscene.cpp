#include "beginscene.h"
#include "constdef.h"
#include "scenemgr.h"
#include "system.h"
#include "HelloWorldScene.h"
USING_NS_CC;


CCScene* CBegin::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	CBegin *layer = CBegin::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}
class CTest : public CCSprite{
public:
	void update(float dt){
		this->removeFromParentAndCleanup( true );
	}
};

// on "init" you need to initialize your instance
bool CBegin::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}
	this->setTouchEnabled( true );
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		this,
		menu_selector(CBegin::menuCloseCallback));

	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
		origin.y + pCloseItem->getContentSize().height/2));

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label


	CCLabelTTF* pLabel = CCLabelTTF::create("Tower Defense", "Arial", TITLE_FONT_SIZE);

	// position the label on the center of the screen
	pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
		origin.y + visibleSize.height - pLabel->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(pLabel, 1);

 	CreateSprite( "map1/1.plist","map1/1.png",20, ccp(100,100) );
// 
 	CreateSprite( "map1/2.plist","map1/2.png",20, ccp(200,100) );


// 
// 	CCSprite *psSprite1 = CCSprite::create("green.png");
// 	CCSprite *psSprite2 = CCSprite::create("red.png");


	
// 	//利用精灵创建进度条，并设置一些属性
// 	progresstime2 = CCProgressTimer::create(psSprite2);    //初始化CCProgressTimer
// 	progresstime2->setPercentage(100.0f);    //设置初始百分比的值
// 	progresstime2->setScale(3);            //设置进度条大小为原始的3倍
// 	progresstime2->setBarChangeRate(ccp(1, 0));    //设置进度条的长度和高度开始变化的大小
// 	progresstime2->setType(kCCProgressTimerTypeBar);    //设置进度条为水平
// 	progresstime2->setPosition(ccp(size.width/2, size.height/2 - 30));    //放置进度条位置
// 
// 	this->addChild(progresstime2, 101);    //加入Layer中

	this->scheduleUpdate();        //调用定时器更新进度条

	return true;
}


US_TD
void CBegin::menuCloseCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->pushScene( HelloWorld::scene() );
}

void CBegin::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	int a = 0;
}


void CBegin::CreateSprite( const String& strList, const String& strPng, int picNbr, CCPoint ptStart, float nTime )
{

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile( strList.c_str() ,strPng.c_str() );
	CCSprite* pSprite = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("sprite_1.png"));

	CCAnimation* animation = CCAnimation::create();
	for ( int i = 0; i < picNbr; i++ )
	{
		char szName[100] = {0};
		sprintf(szName, "sprite_%d.png", i);
		animation->addSpriteFrame( CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(szName));
	}
	pSprite->setPosition( ptStart );
	animation->setDelayPerUnit(nTime);
	CCAnimate* action = CCAnimate::create(animation);	
	pSprite->runAction( CCRepeatForever::create( action ) );

	this->addChild( pSprite );

	CCProgressTimer* progresstime1 = CCProgressTimer::create( CCSprite::create("hp.png") );
	//利用精灵创建进度条，并设置一些属性
	//progresstime1 = CCProgressTimer::create(psSprite1);    //初始化CCProgressTimer
	progresstime1->setPercentage(3);    //设置初始百分比的值
	progresstime1->setScale(3);            //设置进度条大小为原始的3倍
	progresstime1->setBarChangeRate(ccp(1, 0));    //设置进度条的长度和高度开始变化的大小


	progresstime1->setType(kCCProgressTimerTypeBar);    //设置进度条为水平
	progresstime1->setPosition( ccp( ptStart.x , ptStart.y + pSprite->getContentSize().height ) );    //放置进度条位置
	progresstime1->setPercentage( 50 );
	this->addChild(progresstime1, 100);    //加入Layer中
}