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
    
protected:
    float _nextFlicker = 0.f;
    
    cocos2d::AmbientLight* _ambientLight;
    cocos2d::PointLight* _pointLight1;
    cocos2d::PointLight* _pointLight2;
    cocos2d::SpotLight* _lavaLamp;
    cocos2d::SpotLight* _flashlight;
    
    void setupLighting();
    void setupParticleEffects();
    
    void toggleFlashlight();
    void setMessage( const std::string& msg, const std::string& font, float fontSize, cocos2d::Vec2 normalizedPos );
};

#endif /* Game_hpp */
