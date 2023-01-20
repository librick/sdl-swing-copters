#pragma once
#include <SDL2/SDL.h>
#include <iostream>

class SpriteSheet {
  public:
    SpriteSheet(SDL_Renderer* renderer, SDL_Texture* ssTexture, int width, int height, int numFrames=1);
    //SpriteSheet(SpriteSheet& obj);
    ~SpriteSheet();
    int getWidth();
    int getHeight();
    int getPosX();
    int getPosY();
    SDL_Point* getLocalCenter();
    int getNumFrames();
    int getFrameNum();
    SDL_Renderer* getRenderer();
    SDL_Texture* getTexture();
    void setPosX(int posX);
    void setPosY(int posY);
    void setFrameNum(int frameNum);
    void setDisplayHeight(int height);
    void setDisplayWidth(int width);
    void render();
    void renderWithRotation(double angle, SDL_Point* center);

  private:
    int posX;
    int posY;
    int numFrames = 1;
    int frameNum;
    SDL_Renderer* renderer = nullptr;
    SDL_Texture* ssTexture = nullptr;
    SDL_Rect textureRect;
    SDL_Rect windowRect;
};
