//
//  Game.hpp
//  The Forgotten Tomb
//
//  Created by Michael Edwards on 3/14/17.
//
//

#ifndef Game_hpp
#define Game_hpp

#include "Layers/FPRenderLayer.hpp"

class Game : public mikedotcpp::FPRenderLayer
{
public:
    CREATE_FUNC( Game );
    
    virtual bool init() override;
    virtual void onEnter() override;
    virtual void update( float delta ) override;
    virtual void onKeyReleased( cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event ) override;
    void addFPSCamera( float fieldOfView, float nearPlane, float farPlane );
    void setMessage( const std::string& msg, const std::string& font, float fontSize, cocos2d::Vec2 normalizedPos );
    void setHintMessage( const std::string& msg, const std::string& font, float fontSize, cocos2d::Vec2 normalizedPos );
    void dismissHintMessage();
    
protected:
    float _nextFlicker = 0.f;
    
    cocos2d::AmbientLight* _ambientLight;
    cocos2d::PointLight* _pointLight1;
    cocos2d::PointLight* _pointLight2;
    cocos2d::SpotLight* _lavaLamp;
    cocos2d::SpotLight* _flashlight;
    
    cocos2d::Label* _hint;
    
    void setupLighting();
    void setupParticleEffects();
    
    void toggleFlashlight();
};

/**
 * A BehaviorFunction that allows players to walk up to tiles defined as items and pick them up
 * (remove them from the world) as the player walks over the item. **NOTE** there is no storage mechanism
 * or inventory implemented; override for custom functionality.
 */
class PickupObject : public mikedotcpp::BehaviorObject
{
public:
    PickupObject( mikedotcpp::GBRaycaster* gbRaycaster, cocos2d::Layer* layer ) : _raycaster( gbRaycaster ), _layer( layer ){};
    void onEnter( cocos2d::Vec3 enterPosition, cocos2d::Vec3 exitPosition ) override;
    void onExit( cocos2d::Vec3 enterPosition, cocos2d::Vec3 exitPosition ) override;
private:
    mikedotcpp::GBRaycaster* _raycaster;
    cocos2d::Layer* _layer;
    bool _entered = false;
    void flashScreen();
};

#endif /* Game_hpp */
