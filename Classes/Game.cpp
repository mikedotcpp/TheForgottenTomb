//
//  Game.cpp
//  The Forgotten Tomb
//
//  Created by Michael Edwards on 3/14/17.
//
//

#include "Game.hpp"
#include "extensions/cocos-ext.h"
#include "audio/include/AudioEngine.h"

using namespace mikedotcpp;

#define INSTRUCTION_TAG 2106

bool Game::init()
{
    bool result = FPRenderLayer::init();
    
    cocos2d::FileUtils::getInstance()->addSearchPath( "maps/ForgottenTomb/" );
    cocos2d::FileUtils::getInstance()->addSearchPath( "maps/" );
    
    loadMap( "maps/TheForgottenTomb.json" );
    setupLighting();
    setupParticleEffects();
    
    return result;
}

void Game::setupLighting()
{
    cocos2d::Color3B lightColor = cocos2d::Color3B( 5, 5, 40 );
    _ambientLight = cocos2d::AmbientLight::create( lightColor );
    _layer3D->addChild( _ambientLight );
    
     lightColor = cocos2d::Color3B( 255, 165, 0 );
    cocos2d::Vec3 lightPosition = cocos2d::Vec3( 1603.057129f+128.f, 128.000000f*2.f, 193.909363f+128.f );
    _pointLight1 = cocos2d::PointLight::create( lightPosition, lightColor, 800 );
    _layer3D->addChild( _pointLight1 );
    
    lightPosition = cocos2d::Vec3( 1603.057129f+128.f, 128.000000f*2, 193.909363f+(128.f*12) );
    _pointLight2 = cocos2d::PointLight::create( lightPosition, lightColor, 800 );
    _layer3D->addChild( _pointLight2 );
    
    lightColor = cocos2d::Color3B( 255, 0, 0 );
    lightPosition = cocos2d::Vec3( 2620.694824f, 0.000000f, 382.676758f );
    cocos2d::Vec3 lightDirection = cocos2d::Vec3( 0.7, -3.7, 0.7 );
    _lavaLamp = cocos2d::SpotLight::create( lightDirection, lightPosition, lightColor, 60, 120, 600 );
    _layer3D->addChild( _lavaLamp );
}

void Game::setupParticleEffects()
{
    cocos2d::FileUtils::getInstance()->addSearchPath( "Particle3D/materials" );
    cocos2d::FileUtils::getInstance()->addSearchPath( "Particle3D/scripts" );
    
    float flameHeight = 128.f;
    cocos2d::Vec3 flamePositions[] =
    {
        cocos2d::Vec3( 1603.057129f, flameHeight, 193.909363f+128.f ),
        cocos2d::Vec3( 1603.057129f+384.f, flameHeight, 193.909363f+128.f ),
        cocos2d::Vec3( 1603.057129f, flameHeight, 193.909363f+(128.f*13) ),
        cocos2d::Vec3( 1603.057129f+384.f, flameHeight, 193.909363f+(128.f*13) )
    };
    
    for( int i = 0; i < 4; ++i )
    {
        cocos2d::PUParticleSystem3D* pu = cocos2d::PUParticleSystem3D::create( "mp_torch.pu" );
        pu->setPosition3D( flamePositions[i] );
        pu->setCameraMask( (unsigned short)cocos2d::CameraFlag::USER1 );
        pu->setScale( 30.0f );
        pu->startParticleSystem();
        _layer3D->addChild( pu );
    }
    
    cocos2d::PUParticleSystem3D* particlePortal = cocos2d::PUParticleSystem3D::create( "example_010.pu" );
    particlePortal->setPosition3D( cocos2d::Vec3(1788.789917, 64.000000, 2100.844482) );
    particlePortal->setCameraMask( (unsigned short)cocos2d::CameraFlag::USER1 );
    particlePortal->setScale( 20.0f );
    particlePortal->startParticleSystem();
//    _layer3D->addChild( particlePortal );
    
    //
    // Sarcophagus
    //
    cocos2d::Sprite3D* sarcophagus = cocos2d::Sprite3D::create( "models/Sarcophagus/Sarcophagus.obj" );
    sarcophagus->setPosition3D( particlePortal->getPosition3D() );
    sarcophagus->setCameraMask( (unsigned short)cocos2d::CameraFlag::USER1 );
    sarcophagus->setRotation3D( cocos2d::Vec3( 0, 90.0f, 0 ) );
    sarcophagus->setScale( 20.0f );
    _layer3D->addChild( sarcophagus );
    
    
    //
    // Model testing
    //
//    cocos2d::Sprite3D* model = cocos2d::Sprite3D::create( "models/sg-sword-8-textured-poor-obj/sg-sword-8-textured-poor.obj" ); // scale = 0.009f
//    cocos2d::Sprite3D* model = cocos2d::Sprite3D::create( "models/wooden-ladder-low-poly-obj/wooden-ladder-low-poly.obj" ); // scale = 0.05f
//    cocos2d::Sprite3D* model = cocos2d::Sprite3D::create( "models/monster-sign-low-poly-obj/monster-sign-low-poly.obj" ); // scale = 0.25f
    cocos2d::Sprite3D* model = cocos2d::Sprite3D::create( "models/low-poly-key-obj/low-poly-key.obj" ); // scale = 0.005f
//    cocos2d::Sprite3D* model = cocos2d::Sprite3D::create( "models/low-poly-shovel-textured-obj/low-poly-shovel-textured.obj" );
//    cocos2d::Sprite3D* model = cocos2d::Sprite3D::create( "models/pistol-obj/pistol.obj" ); // scale = 0.25f
//    cocos2d::Sprite3D* model = cocos2d::Sprite3D::create( "models/zelda-master-sword-obj/zelda-master-sword.obj" );
    
    cocos2d::Vec3 pos = cocos2d::Vec3( 192.000000f, 512.000000f, 1088.000000f );
//    cocos2d::Vec3 pos = particlePortal->getPosition3D();
////    pos.y = 128.0f;
//    pos.y = 64.0f;
    
    model->setPosition3D( pos );
    model->runAction( cocos2d::RepeatForever::create( cocos2d::RotateBy::create( 1, cocos2d::Vec3( 0, 90.0f, 0 ) ) ) );
    model->setCameraMask( (unsigned short)cocos2d::CameraFlag::USER1 );
//    model->setScale( 0.25f );
//    model->setScale( 0.009f );
    model->setScale( 0.05f );
//    model->setScale( 3.0f );
    _layer3D->addChild( model );
}

void Game::onEnter()
{
    FPRenderLayer::onEnter();
    
    setMessage( "The Forgotten Tomb", "fonts/CAESAR.ttf", 80, cocos2d::Vec2( 0.5f, 0.5f ) );
//    setMessage( "Press the \'F\' key to toggle your flashlight.", "fonts/SFDisplay-Thin.ttf", 40, cocos2d::Vec2( 0.5f, 0.9f ) );
    
    addBehavior( new PickupObject( _raycaster, this ) );
}

void Game::setMessage( const std::string& msg, const std::string& font, float fontSize, cocos2d::Vec2 normalizedPos )
{
    int textTag = INSTRUCTION_TAG;
    cocos2d::Label* text = (cocos2d::Label*)_layer3D->getChildByTag( textTag );
    if( text == nullptr )
    {
        text = cocos2d::Label::createWithTTF( msg, font, fontSize );
//        text = cocos2d::Label::createWithTTF( msg, "fonts/CAESAR.ttf", 80 );
        text->setTag( textTag );
        _layer3D->addChild( text );
    }
    text->setString( msg );
    text->setNormalizedPosition( normalizedPos );
//    text->setNormalizedPosition( cocos2d::Vec2( 0.5f, 0.5f ) );
    text->setColor( cocos2d::Color3B::WHITE );
    text->setOpacity( 0 );
    float duration = 1.25f;
    text->runAction( cocos2d::Sequence::create( cocos2d::FadeIn::create( duration ), NULL) );
    text->runAction( cocos2d::Sequence::create( cocos2d::MoveBy::create( duration, cocos2d::Vec2( 0, 20 ) ), NULL ) );
    text->runAction( cocos2d::Sequence::create( cocos2d::DelayTime::create( duration*3 ), cocos2d::FadeOut::create( duration ), NULL ) );
    text->runAction( cocos2d::Sequence::create( cocos2d::DelayTime::create( duration*3 ), cocos2d::MoveBy::create( duration, cocos2d::Vec2( 0, -20 ) ),
                                               cocos2d::RemoveSelf::create(), NULL ) );
}

void Game::setHintMessage( const std::string& msg, const std::string& font, float fontSize, cocos2d::Vec2 normalizedPos )
{
    if( _hint )
    {
        _hint->removeFromParent();
    }
    _hint = cocos2d::Label::createWithTTF( msg, font, fontSize );
    _hint->setString( msg );
    _layer3D->addChild( _hint );
    
    cocos2d::Size winsize = cocos2d::Director::getInstance()->getWinSize();
    _hint->setPosition( winsize.width*normalizedPos.x, winsize.height*normalizedPos.y );
    
    _hint->setColor( cocos2d::Color3B::WHITE );
    _hint->setOpacity( 0 );
    
    float duration = 0.10f;
    _hint->stopAllActions();
    _hint->runAction( cocos2d::Sequence::create( cocos2d::FadeIn::create( duration ), NULL) );
    _hint->runAction( cocos2d::Sequence::create( cocos2d::MoveBy::create( duration, cocos2d::Vec2( 0, 20 ) ), NULL ) );
    
    _interact = true;
}

void Game::dismissHintMessage()
{
    float duration = 0.10f;
    if( _hint )
    {
        _hint->stopAllActions();
        _hint->runAction( cocos2d::Sequence::create( cocos2d::FadeOut::create( duration ), NULL ) );
        _hint->runAction( cocos2d::Sequence::create( cocos2d::MoveBy::create( duration, cocos2d::Vec2( 0, -20 ) ),
                                                     cocos2d::ToggleVisibility::create(), NULL ) );
    }
    _interact = false;
}

void Game::addFPSCamera( float fieldOfView, float nearPlane, float farPlane )
{
    FPRenderLayer::addFPSCamera( fieldOfView, nearPlane, farPlane );
    
    //
    // Add flashlight to the camera.
    //
    cocos2d::Vec3 lightDirection = cocos2d::Vec3( 0, 0, -30 );
    cocos2d::Vec3 lightPosition = cocos2d::Vec3::ZERO;
    cocos2d::Color3B lightColor = cocos2d::Color3B::WHITE;
    float innerAngle = 50, outerAngle = 100, range = 500;
    _flashlight = cocos2d::SpotLight::create( lightDirection, lightPosition, lightColor, innerAngle, outerAngle, range );
    _flashlight->retain();
    _fpsCamera->addChild( _flashlight );
    
    //
    // Testing a simple gun model.
    //
    cocos2d::Sprite3D* gun = cocos2d::Sprite3D::create( "models/pistol-obj/pistol.obj" ); // scale = 0.25f
    cocos2d::Vec3 pos = cocos2d::Vec3( 20.000000f, -30.000000f, -70.000000f );
    gun->setPosition3D( pos );
    gun->setRotation3D( cocos2d::Vec3( 0, -150.0f, 0 ) );
    gun->setCameraMask( (unsigned short)cocos2d::CameraFlag::USER2 );
    _playerRightHand->addChild( gun );
}

void Game::update( float delta )
{
    FPRenderLayer::update( delta );
    
    _nextFlicker -= delta;
    static int flickerCounter = 0;
    static cocos2d::Vec3 cachedLightPos1 = _pointLight1->getPosition3D();
    static cocos2d::Vec3 cachedLightPos2 = _pointLight2->getPosition3D();
    static cocos2d::Vec3 cachedLavaLampPos = _lavaLamp->getPosition3D();
    if( _nextFlicker < 0 )
    {
        ++flickerCounter;
        _nextFlicker = 0.1f;
        cocos2d::Vec3 flickerPos = cocos2d::Vec3( rand() % 30 - 15, rand() % 30 - 15, rand() % 30 - 15 );
        cocos2d::Vec3 pos1 = _pointLight1->getPosition3D();
        cocos2d::Vec3 pos2 = _pointLight2->getPosition3D();
        cocos2d::Vec3 pos3 = _lavaLamp->getPosition3D();
        pos1.add( flickerPos );
        pos2.add( flickerPos );
        pos3.add( flickerPos );
        _pointLight1->setPosition3D( pos1 );
        _pointLight2->setPosition3D( pos2);
        _lavaLamp->setPosition3D( pos3 );
    }
    if( flickerCounter > 10 )
    {
        flickerCounter = 0;
        _pointLight1->setPosition3D( cachedLightPos1 );
        _pointLight2->setPosition3D( cachedLightPos2 );
        _lavaLamp->setPosition3D( cachedLavaLampPos );
    }
}

void Game::onKeyReleased( cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event )
{
    FPRenderLayer::onKeyReleased( keyCode, event );
    
    if( keyCode == cocos2d::EventKeyboard::KeyCode::KEY_F )
    {
        toggleFlashlight();
        cocos2d::Vec3 pos = _fpsCamera->getPosition3D();
    }
    else if( keyCode == cocos2d::EventKeyboard::KeyCode::KEY_E )
    {
        if( _interact )
        {
            Point3f playerPosition = Point3f( _fpsCamera->getPosition3D().x, _fpsCamera->getPosition3D().y, _fpsCamera->getPosition3D().z );
            _raycaster->clearTileResourceAt( playerPosition );
            flashScreen();
            dismissHintMessage();
        }
    }
}

void Game::toggleFlashlight()
{
    if( _flashlight->getParent() == nullptr )
    {
        _fpsCamera->addChild( _flashlight );
    }
    else
    {
        _flashlight->removeFromParent();
    }
}

void Game::flashScreen()
{
    cocos2d::Size winSize = cocos2d::Director::getInstance()->getWinSize();
    cocos2d::LayerColor* flash = cocos2d::LayerColor::create( cocos2d::Color4B( 255, 255, 0, 100 ), winSize.width, winSize.height );
    cocos2d::FadeOut* fade = cocos2d::FadeOut::create( 0.5f );
    cocos2d::RemoveSelf* removeSelf = cocos2d::RemoveSelf::create();
    cocos2d::Sequence* sequence = cocos2d::Sequence::create( fade, removeSelf, NULL );
    flash->runAction( sequence );
    addChild( flash );
    cocos2d::experimental::AudioEngine::play2d( "sounds/dsitemup.wav" );
}

/**
 * When the player enters this tile, we should have it removed from the map. Additionally, you may want to call 
 * some code that increments a counter or stores a reference to the object in some sort of inventory.
 */
void PickupObject::onEnter( cocos2d::Vec3 enterPosition, cocos2d::Vec3 exitPosition )
{
    _layer->setHintMessage( "Press \'E\' to examine the pistol.", "fonts/SFDisplay-Thin.ttf", 40, cocos2d::Vec2( 0.5f, 0.1f ) );
}


void PickupObject::onExit( cocos2d::Vec3 enterPosition, cocos2d::Vec3 exitPosition )
{
    _layer->dismissHintMessage();
    _entered = false;
}
