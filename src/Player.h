#pragma once
#include "SpriteSheet.h"
#include <SDL2/SDL.h>
using SS = SpriteSheet;

class Player {
  public:
    Player(SS& playerSS, SS& copterSS);
    void resurrect();
    void faceRight();
    void faceLeft();
    void update();
    void render(SDL_Renderer* tempRenderer);
    bool isFlying();
    bool isFalling();
    void startFlying();
    void startFalling();
    void kill();
    void revive();
    double getFallingVelocity();
    bool isDead();
  private:
    SpriteSheet& playerSS;
    SpriteSheet& copterSS;
    // Linear position, velocity, and acceleration.
    int initialPosX;
    int initialPosY;
    double velocityX;
    double accelerationX;
    bool isFacingLeft;
    // Animation state.
    int copterFrameCounter;
    // Lifetime state.
    bool flying;
    bool falling;
    bool dead;
    // Falling state.
    double fallingAngle;
    double fallingVelocity;
};
