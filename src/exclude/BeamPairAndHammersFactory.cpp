#include "BeamPairAndHammersFactory.h"

BeamPairAndHammersFactory::BeamPairAndHammersFactory(SS& beamSS, SS& lHammerSS, SS& rHammerSS) :
beamSS(beamSS), lHammerSS(lHammerSS), rHammerSS(rHammerSS) {}

BeamPairAndHammers* BeamPairAndHammersFactory::create() {
  BeamPairAndHammers* instance = new BeamPairAndHammers(
    &this->beamSS, &this->lHammerSS, &this->rHammerSS);
  return instance;
}
