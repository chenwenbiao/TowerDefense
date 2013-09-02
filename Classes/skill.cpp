#include "skill.h"
#include "system.h"
NAMESPACE_TD_BEGIN

const String ISkill::strTypeSkill = "Skill";

template<> CSkillMgr* CSingleton<CSkillMgr>::m_psSingleton = NULL;

ISkill::ISkill( const String& strType ) : ITDObject( strType ), m_pTargetObject(NULL), m_pSourceObject(NULL){
	 m_ptSpeed = ccp(5,5);
}

ISkill::~ISkill(){
	CC_SAFE_RELEASE_NULL(m_pTargetObject);
	CC_SAFE_RELEASE_NULL(m_pSourceObject);
}

ISkill* ISkill::create( const String& strName, ITDObject* pSource, ITDObject* pTarget )
{
	ISkill* pSkill = new ISkill( strName );
	pSkill->initWithFile( "skill.png" );
	pSkill->setSourceObject( pSource );
	pSkill->setTargetObject( pTarget );
	pSkill->autorelease();
	return pSkill;
}


bool collisionWithCircle(CCPoint circlePoint, float radius, CCPoint circlePointTwo, float radiusTwo)
{	
	float xdif = circlePoint.x - circlePointTwo.x;
	float ydif = circlePoint.y - circlePointTwo.y;

	float distance = sqrt(xdif * xdif + ydif * ydif);

	if(distance <= radius + radiusTwo) 
	{
		return true;
	}
	return false;	
}

float ISkill::calcAngle(CCPoint target) {
	float r = 0;
	CCPoint p2 = ccpSub(target, this->getPosition());
	r = ccpAngle(m_ptSpeed, p2); //计算夹角r是弧度值，不是角度值
	return r;
}

RotateDirection ISkill::calcDirection(CCPoint target) {
	CCPoint p2 = ccpSub(target, this->getPosition());
	if (ccpCross(m_ptSpeed, p2) > 0) {
		// 在opengl的右手坐标系中，向量叉乘大于0表示逆时针方向
		return COUNTERCLOCKWISE;
	} else if (ccpCross(m_ptSpeed, p2) < 0) {
		return CLOCKWISE;
	} else {
		return NO_ROTATE;
	}
}

void ISkill::move( CCPoint ptTarget ) {

	
			//step 1:确定角度
			//计算夹角r是弧度值，不是角度值
	float _rad = calcAngle( ptTarget ); 
	// 			if (_rad && _rad >= PI / 2) {
	// 				//角度大于90的时候放弃，不追踪
	// 				mTarget = NULL;
	// 				break;
	// 			}
	float _deg = CC_RADIANS_TO_DEGREES(_rad);

	float deltaR = _rad;// < mDeltaRadians ? _rad : mDeltaRadians;
	float deltaD = _deg;// < mDeltaDegree ? _deg : mDeltaDegree;

	//step 2:确定方向
	switch (calcDirection(ptTarget)) {
	case COUNTERCLOCKWISE: {
		m_ptSpeed = ccpRotateByAngle(m_ptSpeed, ccp(0,0), deltaR);
		break;
		}
	case CLOCKWISE: {
		m_ptSpeed = ccpRotateByAngle(m_ptSpeed, ccp(0,0), -deltaR);
	break;
		}
	default:
		break;
	}
	float delta = ccpAngle( m_pSourceObject->getPosition(), m_pTargetObject->getPosition() );
	delta = CC_RADIANS_TO_DEGREES( delta );
	if ( delta != 0 )
	{
		m_pSourceObject->setRotation( delta );
	}
	this->setPosition(ccpAdd(getPosition(), m_ptSpeed));
}

void ISkill::End()
{
	this->removeFromParentAndCleanup( true );
}

void ISkill::update( float dt )
{
	if ( m_pTargetObject->m_nHP == 0  )
	{
		End();
		return;
	}
	move( m_pTargetObject->getPosition() );
	if ( collisionWithCircle( this->getPosition(), 2, m_pTargetObject->getPosition(), 2 ) )
	{
		m_pTargetObject->ChangeState("");
		m_pTargetObject->m_nHP--;
		if ( m_pTargetObject->m_nHP == 0 )
		{
			m_pTargetObject->End();
			ITDGod::GetSingletonPtr()->Remove( m_pTargetObject );
		}	
		End();	
	}
}

CSkillMgr::CSkillMgr() : m_pSkills(NULL){}

CSkillMgr::~CSkillMgr(){
	CC_SAFE_RELEASE_NULL(m_pSkills);
}

ISkill* CSkillMgr::CreateSkill( const String& strName, ITDObject* source, ITDObject* target )
{	
	ISkill* pSkill = ISkill::create( strName, source, target );
	pSkill->setPosition( source->getPosition() );
	pSkill->scheduleUpdate();
	source->getParent()->addChild( pSkill );
	
	return pSkill;
}

ISkill* CSkillMgr::GetSkill( const unsigned int& key )
{
	return 0;
}

NAMESPACE_TD_END