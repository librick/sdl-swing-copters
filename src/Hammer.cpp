#include "Hammer.h"

double degToRad(double degrees) {
  double pi = 22/7;
  return degrees * (pi/180);
}

Hammer::Hammer(SS* ss) : ss(ss) {
  this->posX = 0;
  this->posY = 0;
  this->angularVelocity = 0;
  this->angle = 50;
}

int Hammer::getHeight() { return this->ss->getHeight(); }

void Hammer::setPosX(int value) { this->posX = value; }

void Hammer::setPosY(int value) { this->posY = value; }

void Hammer::update() {
  this->updateAngle();
}

void Hammer::render() {
  this->ss->setPosX(this->posX);
  this->ss->setPosY(this->posY);
  SDL_Point center = { this->ss->getWidth() / 2, 0 };
  this->ss->renderWithRotation(this->angle, &center);
}

void Hammer::updateAngle() {
  double g = -0.05;
  double angularAcceleration = g * std::sin(degToRad(this->angle));
  this->angularVelocity += angularAcceleration;
  this->angle += this->angularVelocity;
}
