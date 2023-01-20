#pragma once
#include <vector>
#include "SpriteSheet.h"
using SS = SpriteSheet;

class GroundAndBackground {
  public:
    GroundAndBackground(SS* groundSS, SS* backgroundSS);
    void setVelocity(float value);
    void update();
    void renderBackground();
    void renderForeground();
    void reset();
    bool isAtInitialHeight();
  private:
    float velocity;
    std::vector<SpriteSheet*> groundSprites;
    std::vector<SpriteSheet*> backgroundSprites;
    int initialGroundTilesPosY;
    int initialBackgroundTilesPosY;
};
