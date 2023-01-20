#include "BeamPairAndHammers.h"
#include "Constants.cpp"
#include <ctime>

constexpr int HAMMER_WIDTH = 63;
constexpr int HAMMER_OFFSET_FROM_EDGE_OF_BEAM = 26;
constexpr int BEAM_SPACING_X = 200;

int random(int min, int max) {
   static bool first = true;
   if (first) 
   {  
      srand( time(NULL) ); //seeding for the first time only!
      first = false;
   }
   return min + rand() % (( max + 1 ) - min);
}

BeamPairAndHammers::BeamPairAndHammers(SS* beamSS, SS* lHammerSS, SS* rHammerSS) {
  this->posX = 0;
  this->posY = 0;
  this->offsetX = 0;
  this->height = beamSS->getHeight() + lHammerSS->getHeight();
  this->beamWidth = beamSS->getWidth();
  this->leftBeam = new Beam(beamSS);
  this->rightBeam = new Beam(beamSS);
  this->leftHammer = new Hammer(lHammerSS);
  this->rightHammer = new Hammer(rHammerSS);
}

void BeamPairAndHammers::setPosY(int value) { this->posY = value; }

void BeamPairAndHammers::setOffsetX(int value) { this->offsetX = value; }

int BeamPairAndHammers::getHeight() {
  return this->height;
}

void BeamPairAndHammers::update() {
  this->leftHammer.update();
  this->rightHammer.update();
}

void BeamPairAndHammers::render(SDL_Renderer* debugRenderer) {
  // Set x positions.
  int posXLeftBeam = (WINDOW_WIDTH/2)-(BEAM_SPACING_X/2)-this->beamWidth+this->offsetX;
  int posXLeftHammer = posXLeftBeam+this->beamWidth-floor(HAMMER_WIDTH/2)-HAMMER_OFFSET_FROM_EDGE_OF_BEAM;
  int posXRightBeam = posXLeftBeam+BEAM_SPACING_X+this->beamWidth;
  int posXRightHammer = posXRightBeam-(HAMMER_WIDTH/2)+HAMMER_OFFSET_FROM_EDGE_OF_BEAM;
  this->leftBeam.setPosX(posXLeftBeam);
  this->leftHammer.setPosX(posXLeftHammer);
  this->rightBeam.setPosX(posXRightBeam);
  this->rightHammer.setPosX(posXRightHammer);
  // Set y positions.
  this->leftBeam.setPosY(this->posY);
  this->rightBeam.setPosY(this->posY);
  this->leftHammer.setPosY(this->posY + 32); // TODO: where 32 is arbitrary offset.
  this->rightHammer.setPosY(this->posY + 32); // TODO: where 32 is arbitrary offset.
  // Render the child components.
  this->leftHammer.render();
  this->rightHammer.render();
  this->leftBeam.render();
  this->rightBeam.render();
  // Draw rect to debug bounding boxes.
  SDL_SetRenderDrawColor(debugRenderer, 255, 0, 0, 255);
  SDL_Rect* rect = new SDL_Rect{x: posXLeftBeam, y: this->posY+33, w: this->beamWidth, h: 96};
  SDL_RenderDrawRect(debugRenderer, rect);
}
