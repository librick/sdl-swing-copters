#pragma once
#include "SpriteSheet.h"
using SS = SpriteSheet;

class Beam {
  public:
    Beam(SS* ss);
    int getHeight();
    void setPosX(int value);
    void setPosY(int value);
    void render();
  private:
    SS* ss;
    int posX;
    int posY;
};
