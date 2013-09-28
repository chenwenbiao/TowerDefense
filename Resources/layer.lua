object = { name = "object", id = 0 }
function object:create( extension )
	local t = setmetatable(extension or {}, self)
		self.__index = self
	return t
end
map = object:create( { enemypath = {}, layer } )
function map:ini(bkimage)
	self.layer = CCLayer:create();
	self.layer:addChild( CCSprite:create( bkimage ) )
	return self.layer; 
end
function map:getpath()
	return self.ememypath;
end
function map:setpath(enemypath)
	self.enemypath = enemypath
end
