#pragma once
#include "SpriteSheet.h"
#include "BeamPairAndHammers.h"
using SS = SpriteSheet;

class BeamPairAndHammersFactory {
  public:
    BeamPairAndHammersFactory(SS& beamSS, SS& lHammerSS, SS& rHammerSS);
    BeamPairAndHammers* create();
  private:
    SS& beamSS;
    SS& lHammerSS;
    SS& rHammerSS;
};
