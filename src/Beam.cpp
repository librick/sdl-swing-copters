#include "Beam.h"

Beam::Beam(SS* ss) : ss(ss) {}
int Beam::getHeight() { return this->ss->getHeight(); }
void Beam::setPosX(int value) { this->posX = value; }
void Beam::setPosY(int value) { this->posY = value; }
void Beam::render() {
  this->ss->setPosX(this->posX);
  this->ss->setPosY(this->posY);
  this->ss->render();
}
