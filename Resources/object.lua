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
	return object.name, object.id
end
function object:print()
	for k ,v in pairs(object) do
		print( k, "--", v)
	end
end

IntelligentObject = object:create({ ai = {}, actions = { oncreate, onidle, ondestory }, sprite, skill})

function IntelligentObject:addai( ai )
	self.ai[#(self.ai)] = ai
end
function IntelligentObject:addskill( skill )
	self.skill[#(self.skill)] = skill
end
function IntelligentObject:print()
	for i = 0 , #(self.ai) do
		print( self.ai[i] )
	end 
end 
function IntelligentObject:update()
	for i = 0 , #(self.ai) do
		self.ai[i].doai();
	end 
end
function IntelligentObject:oncreate()
	self.actions["oncreate"].doaction();
end
function IntelligentObject:setaction( name, ac )
	self.actions[name] = ac
end
function IntelligentObject:spriteini(path)
	self.sprite = CCSprite:create( path )
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

actions = object:create( {} )
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

function createobject(name)	
	local obj = nil;
	if name == "object" then
		obj = object:create();
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
	--target:runAction( CCMoveTo:create( 5, endpt ) )
	print("moveai")
end
function setendpt( endpt )
	self.endpt = endpt
end

createobject("object"):print()

local hu = createobject("human")
hu:addai( createobject("moveai") );
hu:print();
hu:update();

hu:setaction("oncreate",actions:create())
hu:oncreate();
