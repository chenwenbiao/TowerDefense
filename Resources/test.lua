require "object"
require "layer"


function main()
	local batchnode = CCSpriteBatchNode:create("enemy.png")
	local visibleSize = CCDirector:sharedDirector():getVisibleSize()
    local origin = CCDirector:sharedDirector():getVisibleOrigin()
	local spbt = CCSpriteBatchNode:create( "Icon.png" );
	local menu
	local function createmap()
		local map1 = map:create();
        local layer = map1:ini( "bk.jpg" );
		return layer;
	end
		
	local bklayer = createmap();

    bklayer:addChild( batchnode );
    bklayer:addChild(spbt)
	local function remove(send)
		send:removeFromParentAndCleanup(true)
	end

	local function createenemy()
			local sp = CCSprite:createWithTexture( batchnode:getTexture() )
			batchnode:addChild(sp)
			
			local array = CCArray:create()
			array:addObject( CCMoveTo:create( 5, ccp(200,200) ) )
			--array:addObject( CCCallFunc:create(remove ) )
			array:addObject(CCCallFuncN:create(remove) )
			local action = CCSequence:create(array)
			sp:runAction(action)
	end

	local function createLayerMenu()
        local layerMenu = CCLayer:create()

        local menuPopup, menuTools, effectID

        local function menuCallbackClosePopup()
            -- stop test sound effect
            SimpleAudioEngine:sharedEngine():stopEffect(effectID)
            menuPopup:setVisible(false)
            require "object"
            local sp = createobject("object")
            sp:spriteini("enemy.png")
            bklayer:addChild(sp)
			--createenemy();
        end

        local function menuCallbackOpenPopup()
            -- loop test sound effect
            local effectPath = CCFileUtils:sharedFileUtils():fullPathForFilename("effect1.wav")
            effectID = SimpleAudioEngine:sharedEngine():playEffect(effectPath)
          --  menuPopup:setVisible(true)
			
            local sp = createobject("object")
            sp:spriteini("enemy.png")
            bklayer:addChild(sp:getsprite())
						
			local a = moveai:create();
			a:settarget( sp )
			a:setendpt( point(200,200) )
			sp:addai( a )
    

            local bt = Bullet:create();
            bt:ini( sp, batchnode:getTexture(), bklayer ,10 ) 
           -- local b = jumpai:create();
          --  b:settarget( sp )
           -- b:setendpt( ccp(200,200) )
          --  sp:addai( b )
			if menu == nil then
				menu = TowerSelectLayer:ini( ccp(200,200), sp, bklayer )
			else
				menu:setVisible( true )
			end
			local function update()
				sp:update();
			end
			callbackfunc( update, 1, false )
        end

        -- add a popup menu
        local menuPopupItem = CCMenuItemImage:create("menu2.png", "menu2.png")
        menuPopupItem:setPosition(0, 0)
        menuPopupItem:registerScriptTapHandler(menuCallbackClosePopup)
        menuPopup = CCMenu:createWithItem(menuPopupItem)
        menuPopup:setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2)
        menuPopup:setVisible(false)
        layerMenu:addChild(menuPopup)

        -- add the left-bottom "tools" menu to invoke menuPopup
        local menuToolsItem = CCMenuItemImage:create("menu1.png", "menu1.png")
        menuToolsItem:setPosition(0, 0)
        menuToolsItem:registerScriptTapHandler(menuCallbackOpenPopup)
        menuTools = CCMenu:createWithItem(menuToolsItem)
        local itemWidth = menuToolsItem:getContentSize().width
        local itemHeight = menuToolsItem:getContentSize().height
        menuTools:setPosition(origin.x + itemWidth/2, origin.y + itemHeight/2)
        layerMenu:addChild(menuTools)

        return layerMenu
    end
    local sceneGame = CCScene:create()
    sceneGame:addChild( bklayer )
    sceneGame:addChild(createLayerMenu())
    CCDirector:sharedDirector():runWithScene(sceneGame)

	--create menu
    
end
main();
