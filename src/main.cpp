


#include <vector>
#include <cmath>
#include <math.h>
#include <iostream>
#include <iterator>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Constants.cpp"
#include "SpriteSheet.h"
#include "Beam.h"
//#include "BeamPairAndHammers.h"
#include "GroundAndBackground.h"
//#include "TiledItemScroller.h"
#include "Player.h"
#include "Hammer.h"
//#include "Scroller.h"


void limitMaxFPS(Uint32 startingTick) {
  if((1000 / FPS) > SDL_GetTicks() - startingTick) {
    SDL_Delay((1000 / FPS) - (SDL_GetTicks() - startingTick));
  }
}

void clearScreen(SDL_Renderer* renderer) {
  SDL_SetRenderDrawColor(renderer, 71, 196, 228, 255);
  SDL_RenderClear(renderer);
}

SDL_Texture* loadTexture(std::string filePath, SDL_Renderer* renderer) {
  char* filePathCStr = const_cast<char*>(filePath.c_str());
  SDL_Surface* temp = IMG_Load(filePathCStr);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, temp);
  SDL_FreeSurface(temp);
  return texture;
}

int main(int argc, char** args) {

  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;

  if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    std::cerr << "Failed to initialize SDL." << std::endl << SDL_GetError() << std::endl;
  }
  if (SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer)) {
    std::cerr << "Failed to initialize window." << std::endl << SDL_GetError() << std::endl;
  }
  
  SDL_Texture* playerTex = loadTexture("res/player.png", renderer);
  SDL_Texture* copterTex = loadTexture("res/copter.png", renderer);
  SDL_Texture* beamTex = loadTexture("res/beam.png", renderer);
  SDL_Texture* hammerTex = loadTexture("res/hammer.png", renderer);
  SDL_Texture* groundTex = loadTexture("res/ground.png", renderer);
  SDL_Texture* backgroundTex = loadTexture("res/background.png", renderer);

  SDL_SetWindowTitle(window, "Swing Copters");
  SpriteSheet playerSS = SpriteSheet(renderer, playerTex, 42, 48, 2);
  SpriteSheet copterSS = SpriteSheet(renderer, copterTex, 66, 18, 4);
  SpriteSheet beamSS = SpriteSheet(renderer, beamTex, BEAM_WIDTH, 33);
  SpriteSheet hammerSS = SpriteSheet(renderer, hammerTex, 63, 96);
  SpriteSheet groundSS = SpriteSheet(renderer, groundTex, 432, 222);
  SpriteSheet backgroundSS = SpriteSheet(renderer, backgroundTex, 432, 285);

  Player player = Player(playerSS, copterSS);
  auto groundAndBackground = GroundAndBackground(&groundSS, &backgroundSS);
  //auto itemFactory = BeamPairAndHammersFactory(beamSS, hammerSS, hammerSS);
  //auto tiledItemScroller = TiledItemScroller(itemFactory);

  SDL_Event event;
  Uint32 startingTick;
  bool isRunning = true;
  std::cout << "Starting main event loop." << std::endl;
  float initialFallingVelocity = 2.0f;
  float fallingVelocity = initialFallingVelocity;
  float fallingAcceleration = 0.4f;

  while(isRunning) {
    startingTick = SDL_GetTicks(); // Number of milliseconds since SDL initialized.
    clearScreen(renderer);

    while(SDL_PollEvent(&event)) {
      if(event.type == SDL_QUIT) {
        isRunning = false;
        break;
      }
      if(event.type == SDL_KEYDOWN) {
        switch( event.key.keysym.sym )
        {
          case SDLK_SPACE:
            if(player.isFlying()) player.startFalling();
            break;
          case SDLK_LEFT:
            player.faceLeft();
            break;
          case SDLK_RIGHT:
            player.faceRight();
            break;
        }
        if(player.isDead() == false && player.isFalling() == false && player.isFlying() == false) {
          player.startFlying();
        }
        if(player.isDead()) player.revive();
      }
    }

    /* *** Update *** */
    player.update();
    groundAndBackground.update();
    //tiledItemScroller.update();

    if(player.isFlying()) {
      fallingVelocity = initialFallingVelocity;
      //tiledItemScroller.setVelocity(-1.0f);
      groundAndBackground.setVelocity(-1.0f);
    } else if(player.isFalling()) {
      //tiledItemScroller.setVelocity(fallingVelocity);
      groundAndBackground.setVelocity(fallingVelocity);
      fallingVelocity += fallingAcceleration;
    } else {
      //tiledItemScroller.setVelocity(0);
      groundAndBackground.setVelocity(0);
    }

    if(player.isFalling() && groundAndBackground.isAtInitialHeight()) {
      player.kill();
    }

    /* *** Render *** */
    groundAndBackground.renderBackground();
    player.render(renderer);
    groundAndBackground.renderForeground();
    //tiledItemScroller.render(renderer);
    SDL_RenderPresent(renderer);
    limitMaxFPS(startingTick);
  }
}
