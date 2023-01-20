#pragma once
#include "Beam.h"
#include "Hammer.h"
using SS = SpriteSheet;

class BeamPairAndHammers {
  public:
    BeamPairAndHammers(SS* beamSS, SS* lHammerSS, SS* rHammerSS);
    void setPosY(int value);
    void setOffsetX(int value);
    int getHeight();
    void update();
    void render(SDL_Renderer* debugRenderer);
  private:
    int beamWidth;
    int height;
    Beam leftBeam;
    Beam rightBeam;
    Hammer leftHammer;
    Hammer rightHammer;
    int posX;
    int posY;
    int offsetX;
};
