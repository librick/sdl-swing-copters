#include "GroundAndBackground.h"
#include "Constants.cpp"
using SpriteSheet = SS;

constexpr int POS_Y_OFFSET = 134; // Magic number.

GroundAndBackground::GroundAndBackground(SS* groundSS, SS* backgroundSS) {
  this->velocity = 0;
  this->initialGroundTilesPosY = WINDOW_HEIGHT - groundSS->getHeight() + POS_Y_OFFSET;
  this->initialBackgroundTilesPosY = WINDOW_HEIGHT - backgroundSS->getHeight() + POS_Y_OFFSET;

  int maxNumGroundTiles = std::ceil(WINDOW_WIDTH / groundSS->getWidth()) + 1;
  for(int i = 0; i < maxNumGroundTiles; ++i) {
    SpriteSheet* newGroundSS = new SpriteSheet(*groundSS);
    newGroundSS->setPosY(initialGroundTilesPosY);
    this->groundSprites.push_back(newGroundSS);
  }
  int maxNumBkgSprites = std::ceil(WINDOW_WIDTH / backgroundSS->getWidth()) + 1;
  for(int i = 0; i < maxNumBkgSprites; ++i) {
    SpriteSheet* newBkgSS = new SpriteSheet(*backgroundSS);
    newBkgSS->setPosY(initialBackgroundTilesPosY);
    this->backgroundSprites.push_back(newBkgSS);
  }
}

bool GroundAndBackground::isAtInitialHeight() {
  for(auto it = std::begin(this->groundSprites); it != std::end(this->groundSprites); ++it) {
    SpriteSheet* item = *it;
    if(item->getPosY() == this->initialGroundTilesPosY) {
      return true;
    }
  }
  return false;
}

void GroundAndBackground::setVelocity(float value) {
  this->velocity = value;
}

void GroundAndBackground::update() {
  for(auto it = std::begin(this->backgroundSprites); it != std::end(this->backgroundSprites); ++it) {
    SpriteSheet* item = *it;
    int targetPosY = item->getPosY() - (int)this->velocity;
    item->setPosY(std::max(targetPosY, this->initialBackgroundTilesPosY));
  }
  for(auto it = std::begin(this->groundSprites); it != std::end(this->groundSprites); ++it) {
    SpriteSheet* item = *it;
    int targetPosY = item->getPosY() - (int)this->velocity;
    item->setPosY(std::max(targetPosY, this->initialGroundTilesPosY));
  }
}

void GroundAndBackground::renderBackground() {
  int numBkgInterations = 0;
  for(auto it = std::begin(this->backgroundSprites); it != std::end(this->backgroundSprites); ++it) {
    SpriteSheet* item = *it;
    item->setPosX(numBkgInterations * item->getWidth());
    item->render();
    numBkgInterations += 1;
  }
}

void GroundAndBackground::renderForeground() {
  int numGroundIterations = 0;
  for(auto it = std::begin(this->groundSprites); it != std::end(this->groundSprites); ++it) {
    SpriteSheet* item = *it;
    item->setPosX(numGroundIterations * item->getWidth());
    item->render();
    numGroundIterations += 1;
  }
}

void GroundAndBackground::reset() {
  for(auto it = std::begin(this->groundSprites); it != std::end(this->groundSprites); ++it) {
    SpriteSheet* item = *it;
    item->setPosY(this->initialGroundTilesPosY);
  }
    for(auto it = std::begin(this->backgroundSprites); it != std::end(this->backgroundSprites); ++it) {
    SpriteSheet* item = *it;
    item->setPosY(this->initialBackgroundTilesPosY);
  }
}
