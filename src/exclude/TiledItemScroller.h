#pragma once
#include <vector>
#include "SpriteSheet.h"
#include "BeamPairAndHammers.h"
#include "BeamPairAndHammersFactory.h"
#include "GroundAndBackground.h"

class TiledItemScroller {
  public:
    TiledItemScroller(BeamPairAndHammersFactory* factory);
    void reset();
    void update();
    void render(SDL_Renderer* debugRenderer);
    void setVelocity(float value);
  private:
    BeamPairAndHammersFactory* factory;
    int segmentHeight;
    int maxItemsInView;
    std::vector<BeamPairAndHammers*> drawableItems;
    std::vector<int> horizontalOffsets;
    float rollingOffset;
    float velocity;
};
