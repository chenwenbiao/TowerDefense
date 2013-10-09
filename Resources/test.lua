require( "object" )
function callbackfunc( name, t, pause )
	CCDirector:sharedDirector():getScheduler():scheduleScriptFunc(name, t, pause)
end


function main()
	local visibleSize = CCDirector:sharedDirector():getVisibleSize()
    local origin = CCDirector:sharedDirector():getVisibleOrigin()
	local scene = CCScene:create()
	CCDirector:sharedDirector():runWithScene(scene)
	
	local batchnode = CCSpriteBatchNode:create("enemy.png")
	local spbt = CCSpriteBatchNode:create( "Icon.png" );
	
	local function createmaplayer( scene )
		local maplayer = { layer, bPause = false, obs = {}, towers = {} , enemycounts = 0 }
		
		local function createlayer()
			local layer = CCLayer:create();
			layer:addChild( CCSprite:create("bk.jpg"))
			scene:addChild( layer )
			layer:addChild( batchnode )

			return layer
		end
		
		function createenemy()
			if maplayer.bPause == false and maplayer.enemycounts < 3 then
				local ob = IntelligentObject:create()
				ob:spriteini( batchnode:getTexture(), batchnode )
			--	local ccSprite = CCSprite:createWithTexture( batchnode:getTexture() )
			--	batchnode:addChild( ccSprite )
				--ob:getsprite():runAction( CCJumpTo:create( 2, ccp(300,300), 100, 10 ))
				
				if maplayer.enemycounts == 0 then
					ob.name = "mxm"
				end
				if maplayer.enemycounts == 1 then
					ob.name = "seliber"
				end
				if maplayer.enemycounts == 0 then
					local ai = jumpai:create();
					ai:settarget( ob )
					--ai:setendpt( ccp(300,300) )
					ob:addai( ai )
				end		
				local follower = hp:create()
				follower:ini( maplayer.layer, ob )
				ob:addfollower( follower )

				ob:getsprite():retain()
				table.insert( map.obs, ob )
				maplayer.enemycounts = maplayer.enemycounts+1
			--	ob:updateai()
			end
		end
		function updateai()
			for i, n in pairs(map.obs) do 
				local temp = n:getsprite():retainCount();
				if temp ~= 1 then
					n:update()		
				end	
			end 
			
			for i, n in pairs(map.towers) do 
				local temp = n:getsprite():retainCount();
				if temp ~= 1 then
					n:update()		
				end	
			end 
		end
		
		
		callbackfunc( createenemy, 1, false )
		callbackfunc( updateai, 0.1, false )
		
		maplayer.layer = createlayer()
		
		function maplayer:updateobj( src, objtype )
			
		end
		function maplayer:addobj( objtype )
			
		end		
		
		local touchBeginPoint = nil

        local function onTouchBegan(x, y)   		
				for i, n in pairs(map.towers) do 
					n:getsprite():removeFromParentAndCleanup();
					table.remove( map.towers )
				end 
				
			
				touchBeginPoint = {x = x, y = y}    
			
				ob = IntelligentObject:create()
				ob:spriteini( batchnode:getTexture(), batchnode )
						
				local ai = attackai:create();
				ai:settarget( ob )
				ai:setlist(map.obs)
				ob:addai( ai )
				ob:getsprite():retain()
				ob:setpos( ccp(x,y) )
				table.insert( map.towers, ob )
				
			return true
        end

        local function onTouchMoved(x, y)
            if touchBeginPoint then
               -- local cx, cy = layerFarm:getPosition()
               -- layerFarm:setPosition(cx + x - touchBeginPoint.x,
                --                      cy + y - touchBeginPoint.y)
                touchBeginPoint = {x = x, y = y}
            end
        end

        local function onTouchEnded(x, y)
            touchBeginPoint = nil
        end

        local function onTouch(eventType, x, y)
            if eventType == "began" then   
                return onTouchBegan(x, y)
            elseif eventType == "moved" then
                return onTouchMoved(x, y)
            else
                return onTouchEnded(x, y)
            end
        end

        maplayer.layer:registerScriptTouchHandler(onTouch)
        maplayer.layer:setTouchEnabled(true)
		return maplayer
	end
	
	local function createcontrollayer( scene )
		local controllayer = { layer }
		
		local function createlayer()
			local layer = CCLayer:create();
			layer:addChild( CCSprite:create("bk.jpg"))
			scene:addChild( layer )
			return layer
		end
		
		controllayer.layer = createlayer()
		
		

		local function menucallback()
			map.addobj("1")
		end	
			
		function controllayer:updatemenu( x,y )		
			local menuPopupItem = CCMenuItemImage:create("menu.png", "menu.png")
			menuPopupItem:setPosition(0, 0)
			menuPopupItem:registerScriptTapHandler(menucallback)
			menuPopup = CCMenu:createWithItem(menuPopupItem)
			menuPopup:setPosition( x, y )
			menuPopup:setVisible(true)
			controllayer.layer:addChild(menuPopup)
		end
		function controllayer:addobjmenu()
			
		end
		
		return controllayer
	end  
	map = createmaplayer( scene )
	
	--control = createcontrollayer( scene )
end
main();
