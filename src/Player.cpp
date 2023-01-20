#include "Player.h"
#include "Constants.cpp"
#include <iostream>

constexpr int FRAME_FACING_LEFT = 1;
constexpr int FRAME_FACING_RIGHT = 0;
constexpr int NUM_FRAMES_PER_COPTER_FRAME = 6;
constexpr int VELOCITY_ON_FIRST_MOVE = 4;
constexpr float MAX_ACCELERATION_X = 0.4;
constexpr float FALLING_ANGULAR_VELOCITY = -12;
constexpr float FALLING_ACCELERATION = -0.2;

Player::Player(SS& playerSS, SS& copterSS): playerSS(playerSS), copterSS(copterSS) {
  this->initialPosX = (WINDOW_WIDTH / 2) - (this->playerSS.getWidth() / 2);
  this->initialPosY = WINDOW_HEIGHT - 128;
  this->playerSS.setPosX(initialPosX);
  this->playerSS.setPosY(initialPosY);
  this->velocityX = 0;
  this->accelerationX = 0;
  this->isFacingLeft = false;
  // Animation state.
  this->copterFrameCounter = 0;
  // Lifetime state.
  this->flying = false;
  this->falling = false;
  this->dead = false;
    // Falling state.
  this->fallingAngle = 0;
  this->fallingVelocity = 0;
}

void Player::startFlying() {
  this->flying = true;
  this->falling = false;
  this->dead = false;
  this->accelerationX = MAX_ACCELERATION_X;
  this->velocityX = VELOCITY_ON_FIRST_MOVE * (this->isFacingLeft ? -1 : 1);
}

void Player::startFalling() {
  this->flying = false;
  this->falling = true;
}

void Player::kill() {
  this->playerSS.setPosY(initialPosY);
  this->accelerationX = 0;
  this->velocityX = 0;
  this->fallingAngle = 180;
  this->fallingVelocity = 0;
  this->faceRight();
  this->flying = false;
  this->falling = false;
  this->dead = true;
}

void Player::revive() {
  this->playerSS.setPosX(initialPosX);
  this->playerSS.setPosY(initialPosY);
  this->accelerationX = 0;
  this->velocityX = 0;
  this->faceRight();
  this->fallingAngle = 0;
  this->fallingVelocity = 0;
  this->flying = false;
  this->falling = false;
  this->dead = false;
}

void Player::faceRight() {
  if(this->isDead()) return;
  this->isFacingLeft = false;
  this->playerSS.setFrameNum(FRAME_FACING_RIGHT);
}

void Player::faceLeft() {
  if(this->isDead()) return;
  this->isFacingLeft = true;
  this->playerSS.setFrameNum(FRAME_FACING_LEFT);
}

void Player::update() {
  if(this->isFalling()) {
    this->fallingAngle += FALLING_ANGULAR_VELOCITY;
    this->fallingVelocity += FALLING_ACCELERATION;
    return;
  }
  this->copterFrameCounter += 1;
  if(this->copterFrameCounter >= NUM_FRAMES_PER_COPTER_FRAME) {
    int numFrames = this->copterSS.getNumFrames();
    int currentFrame = this->copterSS.getFrameNum();
    int nextFrame = (currentFrame + 1) % numFrames;
    this->copterSS.setFrameNum(nextFrame);
    this->copterFrameCounter = 0;
  }

  if(this->isFlying()) {
    if(this->isFacingLeft == true) { this->velocityX -= this->accelerationX; }
    if(this->isFacingLeft == false) { this->velocityX += this->accelerationX; }
    this->playerSS.setPosX(this->playerSS.getPosX() + this->velocityX);
  }

  if(this->playerSS.getPosX() < 0)
    this->startFalling();
  if((this->playerSS.getPosX() + this->playerSS.getWidth()) >= WINDOW_WIDTH)
    this->startFalling();
}

void Player::render(SDL_Renderer* tempRenderer) {
  if(this->isFalling() || this->isDead()) {
    this->playerSS.renderWithRotation(fallingAngle, NULL);
    return;
  }
  float angle = this->velocityX*4; // Magic number, just feels good man.
  int playerGlobalCenterX = this->playerSS.getPosX()+this->playerSS.getWidth()/2;
  int playerGlobalCenterY = this->playerSS.getPosY()+this->playerSS.getHeight()/2;
  // Calculate the center of the copter's x direction, assuming the player is directly centered "beneath" the copter.
  int playerHeight = this->playerSS.getHeight();
  int copterHeight = this->copterSS.getHeight();
  int copterGlobalCenterX = playerGlobalCenterX+0.5*sin(angle*3.14/180)*(playerHeight+copterHeight);
  // Calculate the center of the copter's y direction.
  int copterGlobalCenterY = playerGlobalCenterY-0.5*cos(angle*3.14/180)*(playerHeight+copterHeight);
  int copterWidth = this->copterSS.getWidth();
  // All rotation calculations are done on the centers of the copter and player,
  // only then is the copter's position determined from the calculated center.
  int copterPosX = copterGlobalCenterX - copterWidth/2;
  int copterPosY = copterGlobalCenterY - copterHeight/2;
  this->copterSS.setPosX(copterPosX);
  this->copterSS.setPosY(copterPosY);
  this->playerSS.renderWithRotation(angle, NULL);
  this->copterSS.renderWithRotation(angle, NULL);
}

bool Player::isFlying() {
  return this->flying;
}

bool Player::isFalling() {
  return this->falling;
}

double Player::getFallingVelocity() {
  return this->fallingVelocity;
}

bool Player::isDead() {
  return this->dead;
}
