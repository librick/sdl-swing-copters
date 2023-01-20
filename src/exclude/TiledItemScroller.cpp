#include "TiledItemScroller.h"
#include <math.h>
#include <iterator>
#include <ctime>
#include "Constants.cpp"
#include <iostream>


constexpr int VERTICAL_GAP_BETWEEN_ITEMS = 120;
constexpr int GROUND_HEIGHT = 76;
constexpr int INITIAL_HEIGHT_ABOVE_GROUND = 250;

int randomInt(int min, int max) {
   static bool first = true;
   if (first) 
   {  
      srand( time(NULL) ); //seeding for the first time only!
      first = false;
   }
   return min + rand() % (( max + 1 ) - min);
}

TiledItemScroller::TiledItemScroller(BeamPairAndHammersFactory* factory) {
  this->factory = factory;
  this->rollingOffset = 0;
  this->velocity = 0;
  auto temporaryItem = factory->create();
  int itemHeight = temporaryItem->getHeight();
  this->segmentHeight = itemHeight + VERTICAL_GAP_BETWEEN_ITEMS;
  // To determine how many items can fit on screen,
  // figure out how many non-fractional items can be on screen,
  // then allow for a fractional item on the top and a fractional item on the bottom.
  this->maxItemsInView = floor(WINDOW_HEIGHT / segmentHeight) + 2;
  std::cout << "Window height: " << WINDOW_HEIGHT << std::endl;
  std::cout << "Segment height: " << this->segmentHeight << std::endl;
  std::cout << "Max items in view: " << maxItemsInView << std::endl;
  this->reset();
}

void TiledItemScroller::setVelocity(float value) {
  this->velocity = value;
}

void TiledItemScroller::reset() {
  this->drawableItems.clear();
  for(int i = 0; i < this->maxItemsInView; i++) {
    auto item = this->factory->create();
    this->drawableItems.push_back(item);
  }
  this->horizontalOffsets.clear();
  for(int i = 0; i < 255; i++) {
    int randomOffsetX = randomInt(-200, 200);
    this->horizontalOffsets.push_back(randomOffsetX);
  }
}

void TiledItemScroller::update() {
  this->rollingOffset += this->velocity;
  if(this->rollingOffset > 0) this->rollingOffset = 0;
  std::vector<BeamPairAndHammers*>::iterator iter;
  for (iter = this->drawableItems.begin(); iter != this->drawableItems.end(); ) {
    auto item = *iter;
    item->update();
    ++iter;
  }
}

void TiledItemScroller::render(SDL_Renderer* debugRenderer) {
  const int groundOffset = GROUND_HEIGHT + INITIAL_HEIGHT_ABOVE_GROUND;
  int horizOffsetIndex = 0;
  int drawableItemIndex = this->drawableItems.size() - 1;
  std::vector<int>::iterator iter;
  for(iter = this->horizontalOffsets.begin(); iter != this->horizontalOffsets.end(); ) {
    //if(drawableItemIndex < 0) break;
    int posY = WINDOW_HEIGHT - (horizOffsetIndex+1)*this->segmentHeight - groundOffset - floor(rollingOffset);
    bool isVisible = (posY+this->segmentHeight) > 0 && posY < WINDOW_HEIGHT;
    if(isVisible) {
      //std::cout << drawableItemIndex << std::endl;
      auto drawableItem = this->drawableItems[drawableItemIndex];
      int offsetX = *iter;
      drawableItem->setOffsetX(offsetX);
      drawableItem->setPosY(posY);
      drawableItem->render(debugRenderer);
      --drawableItemIndex;
    }
    ++horizOffsetIndex;
    ++iter;
  }
}
