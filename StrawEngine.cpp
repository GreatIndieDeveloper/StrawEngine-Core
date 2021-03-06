#include "Engine/Addons/Animator.h"
#include "Engine/Game/Entity.h"
#include "Engine/Game/Game.h"
#include "Engine/IO/Window.h"
#include "Engine/Rendering/Animation.h"
#include <cmath>
#include <ctime>
#include <iostream>
#include <random>
#include "Engine/Addons/Script.h"
class CustomShader : public Shader{
public:
  CustomShader(std::string fragpath,std::string verpath) : Shader(fragpath,verpath) {}
  
};
class MyGame : public Game {
  EntityHandler me;
  void Start() override {
     me = MakeSprite(X_Vector(500,0), X_Vector(100,100),false);
     me->GetAddon<Sprite>()->tex = GetTexture("/home/mohamedmedhat/StrawEngine/StrawEngine-Core/Assets/wall.jpg");
     
     
  }
  void Update(float dt) override {
  }
  void FixedUpdate(float dt) override {
  }
  void OnGUI() override{
    GUI::StartRow(600,200,2);
    GUI::Button("TEST");
    GUI::Label("SCORE : " );
  }
};

int main() {
  PhysicsSystem::Gravity = -40;
  Window x(1000, 1000, "TES");
  MyGame gm;
  
  x.Loop(&gm);
     
}
