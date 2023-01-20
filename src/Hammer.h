#pragma once
#include "SpriteSheet.h"
using SS = SpriteSheet;

class Hammer {
  public:
    Hammer(SS* ss);
    int getHeight();
    void setPosX(int value);
    void setPosY(int value);
    void update();
    void render();
  private:
    SS* ss;
    int posX;
    int posY;
    double angularVelocity;
    double angle;
    void updateAngle();
};
