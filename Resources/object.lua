function callbackfunc( name, t, pause )
	CCDirector:sharedDirector():getScheduler():scheduleScriptFunc(name, t, pause)
end

object = { name = "object", id = 0 }
function object:create( extension )
	local t = setmetatable(extension or {}, self)
		self.__index = self
	return t
end
function object:set( name, id )
	object.name = name
	object.id = id
end
function object:get()
	return object.name
end
function object:print()
	for k ,v in pairs(object) do
		print( k, "--", v)
	end
end

IntelligentObject = object:create({ ais = {}, actions = { oncreate, onidle, ondestory }, sprite, skills, step = 10, pos = ccp(0,0), attackrange = 10 })
function IntelligentObject:ini( pic, layer )
	self.spriteini( pic, layer )
end

function IntelligentObject:addai( obai )
	table.insert(self.ais, obai)
end

function IntelligentObject:addskill( skill )
	table.insert(self.skills, skill)
end
function IntelligentObject:print()
	print(self.name)
	for i,n in pairs(self.ais) do 
		n:doai()
	end	
end 
function IntelligentObject:update()
	for i,n in pairs(self.ais) do 
		n:doai()
	end	
end
function IntelligentObject:oncreate()
	self.actions["oncreate"]:doaction();
end
function IntelligentObject:setaction( name, ac )
	self.actions[name] = ac
end
function IntelligentObject:spriteini(pic, layer)
	self.sprite = CCSprite:createWithTexture( pic )
	layer:addChild( self.sprite )
--	callbackfunc( self.update, 1, false )
end
function IntelligentObject:getsprite()
	return self.sprite
end 
function IntelligentObject:setskillindex( index )
	self.skillindex = index
end
function IntelligentObject:attack( target )
	local skill = createobject( skill[0] );
end
function IntelligentObject:setstep( step )
	self.step = step
end
function IntelligentObject:getstep()
	return self.step
end
function IntelligentObject:setpos(pos)
	self.pos = pos
	self.sprite:setPosition( pos )
end
function IntelligentObject:getstep()
	return self.pos
end

actions = object:create( { plist, pic, count } )
function actions:ini()
	
end
function actions:doaction()
	print("actions");
end


skill = object:create( { src } )
function skill:setsrc( src )
	self.src = src
end
function skill:getsrc()
	return self.src
end 

single_skill = skill:create( { target} )
function single_skill:settarget( target )
	self.target = target
end
function single_skill:gettarget()
	return self.target
end
function single_skill:makedamage()
end

group_skill = skill:create( {} )
function group_skill:makedamage()
end

Bullet = IntelligentObject:create( {target,demage = 10} )
function Bullet:ini( target, pic, layer, demage ) 
	self.sprite = CCSprite:createWithTexture(pic)
	self.target = target;
	self.demage = demage;
	layer:addChild( self.sprite )
end 

function createobject(name)	
	local obj = nil;
	if name == "object" then
		obj = IntelligentObject:create();
		local a = moveai:create();
		a:settarget( obj )
		a:setendpt( ccp(200,200) )
		obj:addai( a )
		a:set("mxm",100)
	end
	if name == "human" then
		obj = IntelligentObject:create();
	end
	if name == "moveai" then
		obj = moveai:create();
	end
	if name == "single" then
		obj = single_skill:create();
	end
	if name == "group" then
		obj = group_skill:create();
	end
	return obj;
end

function createskill( name, src , target )
	local obj = nil;
	if name == "single" then
		obj = single_skill:create();	
		local ai = createobject("moveai")
		obj:setsrc( src );
		obj:setai( ai );
		
		skill:doaction( "oncreate" );
	end
	if name == "group" then
		obj = group_skill:create();
	end
	return obj;
end
	
ai = object:create( { target } )
function ai:settarget( target )
	self.target = target
end
moveai = ai:create( { endpt } )
function moveai:doai()
	--[[local sp = self.target:getsprite();
	local function remove()
		self.target:removeFromParentAndCleanup( true )
	end
		
	local array = CCArray:create()
	array:addObject( CCMoveTo:create( 5, self.endpt) )
	array:addObject(CCCallFuncN:create(remove) )
	local action = CCSequence:create(array)
	sp:runAction(action)--]]
			
	print("moveai")
end
function moveai:setendpt( endpt )
	self.endpt = endpt
end

jumpai = ai:create( { endpt } )
function jumpai:doai()
	local sp = self.target:getsprite();
	--sp:setPosition( self.endpt)
	local function remove()
		
	end
	local temp1 = sp:retainCount();
	if sp:getPositionX() > 100 then
		sp:removeFromParentAndCleanup( true )
		local temp2 = sp:retainCount();
	else
		sp:runAction( CCMoveBy:create( 1, ccp(100,100) ) )
	end
	--sp:runAction( CCSequence:create( CCMoveTo:create(5, self.endpt), CCCallFunc:create( remove ), nil ) )
	print("moveai")
end
function jumpai:setendpt( endpt )
	self.endpt = endpt
end

function point( x, y )
	return ccp( x, y )
end

attackai = ai:create( { objlist } )
function attackai:doai()
	for i,n in pairs( self.objlist) do
		local function Distance( ptsrc, pttarget )
			return 100
		end		
		local dis = Distance( self.target:getsprite():getPosition(), n:getsprite():getPosition() )
		if dis < 100 then
			n:getsprite():removeFromParentAndCleanup()
		end
		
	end
end
function attackai:setlist( list )
	self.objlist = list
end

--[[obs = {}

ob = IntelligentObject:create()
ob:set( "mxm", 0 )
ob:addai( moveai:create() )
ob:addai( moveai:create() )
ob:addai( moveai:create() )
ob:setaction( "oncreate", actions:create() )
ob:oncreate()

table.insert(obs, ob)

for i, n in pairs(obs) do
	n:print()
end

local ds = 0;--]]
