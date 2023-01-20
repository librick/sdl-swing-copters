#include "SpriteSheet.h"
#include <iostream>


SpriteSheet::SpriteSheet(SDL_Renderer* renderer, SDL_Texture* ssTexture, int width, int height, int numFrames) {
  this->renderer = renderer;
  this->ssTexture = ssTexture;
  this->windowRect.x = 0;
  this->windowRect.y = 0;
  this->windowRect.w = width;
  this->windowRect.h = height;
  this->numFrames = numFrames;
  this->frameNum = 0;
  this->textureRect.x = 0;
  this->textureRect.y = 0;
  this->posX = 0;
  this->posY = 0;
  SDL_QueryTexture(this->ssTexture, NULL, NULL, &this->textureRect.w, &this->textureRect.h);
  this->textureRect.w /= this->numFrames;
  this->windowRect.w = this->textureRect.w;
  this->windowRect.h = this->textureRect.h;
}

// SpriteSheet::SpriteSheet(SpriteSheet& obj) {
//   this->renderer = obj.getRenderer();
//   this->ssTexture = obj.getTexture(); 
//   this->windowRect.x = 0;
//   this->windowRect.y = 0;
//   this->windowRect.w = obj.getWidth();
//   this->windowRect.h = obj.getHeight();
//   this->textureRect.x = 0;
//   this->textureRect.y = 0;
//   this->posX = 0;
//   this->posY = 0;
//   SDL_QueryTexture(this->ssTexture, NULL, NULL, &this->textureRect.w, &this->textureRect.h);
//   this->numFrames = obj.getNumFrames();
//   this->textureRect.w /= this->numFrames;
//   this->windowRect.w = this->textureRect.w;
//   this->windowRect.h = this->textureRect.h;
// }

SpriteSheet::~SpriteSheet() {
  SDL_DestroyTexture(this->ssTexture);
}

int SpriteSheet::getWidth() { return this->windowRect.w; }
int SpriteSheet::getHeight() { return this->windowRect.h; }
int SpriteSheet::getPosX() { return this->posX; }
int SpriteSheet::getPosY() { return this->posY; }

// See: https://wiki.libsdl.org/SDL_RenderCopyEx
// The parameter center is described as
// "a pointer to a point indicating the point around which dstrect will be rotated
// (if NULL, rotation will be done around dstrect.w / 2, dstrect.h / 2)".
// So this is not a global center but a center local to the destination rect
// when rendered.
SDL_Point* SpriteSheet::getLocalCenter() {
  int centerX = this->getWidth() / 2;
  int centerY = this->getHeight() / 2;
  return new SDL_Point{ x: centerX, y: centerY };
}

int SpriteSheet::getNumFrames() { return this->numFrames; }
int SpriteSheet::getFrameNum() { return this->frameNum; }
SDL_Renderer* SpriteSheet::getRenderer() { return this->renderer; }
SDL_Texture* SpriteSheet::getTexture() { return this->ssTexture; }
void SpriteSheet::setPosX(int posX) { this->posX = posX; }
void SpriteSheet::setPosY(int posY) { this->posY = posY; }

void SpriteSheet::setFrameNum(int frameNum) {
  this->frameNum = frameNum;
  this->textureRect.x = this->windowRect.w * frameNum;
}

void SpriteSheet::setDisplayHeight(int height) { this->windowRect.h = height; }
void SpriteSheet::setDisplayWidth(int width) { this->windowRect.w = width; }

void SpriteSheet::render() {
  this->windowRect.x = this->posX;
  this->windowRect.y = this->posY;
  SDL_RenderCopy(this->renderer, this->ssTexture, &this->textureRect, &this->windowRect);
}

void SpriteSheet::renderWithRotation(double angle, SDL_Point* center) {
  this->windowRect.x = this->posX;
  this->windowRect.y = this->posY;
  SDL_RenderCopyEx(this->renderer, this->ssTexture, &this->textureRect, &this->windowRect, angle, center, SDL_FLIP_NONE);
}
