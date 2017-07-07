/*******************************************************************************
@file `main.cpp`
  Created June 28, 2017

@author CJ Dimaano
  <c.j.s.dimaano@gmail.com>
*******************************************************************************/

#include "Factory.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_log.h>

#define SCREEN_HEIGHT 480
#define SCREEN_WIDTH 640

/* Static variables ***********************************************************/

/**
 * `sdlWindow`
 *
 *   The main SDL window.
 */
static SDL_Window *sdlWindow = NULL;

/**
 * `sdlRenderer`
 *
 *   The SDL renderer used to draw onto the window.
 */
static SDL_Renderer *sdlRenderer = NULL;

/**
 * `factorySpritesheet`
 *
 *   The spritesheet for the factory.
 */
static SDL_Texture *factorySpritesheet = NULL;

/**
 * `factory`
 *
 *   _The_ factory.
 */
static Factory *factory = NULL;

/* Function declarations ******************************************************/

static bool init();
static void close();
static void update(unsigned int);
static void draw();
static SDL_Texture *loadTexture(const char *const);

/* Main ***********************************************************************/

int main() {

  /*** Initialize SDL and global data. ***/
  if (!init())
    return -1;

  /*** Start the render loop. ***/
  SDL_Event evt;
  bool quit = false;
  unsigned int currTick = SDL_GetTicks();
  unsigned int prevTick = currTick;
  while (!quit) {

    /*** Handle SDL events. ***/
    while (SDL_PollEvent(&evt) != 0) {
      switch (evt.type) {
      case SDL_QUIT:
        quit = true;
        break;
      }
    }

    /*** Update the window. ***/
    update(currTick - prevTick);
    draw();

    /*** Update the previous and current tick. ***/
    prevTick = currTick;
    currTick = SDL_GetTicks();
  }

  close();

  return 0;
}

/* Function definitions *******************************************************/

/**
 * `init`
 *
 *   Initializes SDL and global data.
 */
static bool init() {

  /*** Initialize SDL. ***/
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "Unable to initialize SDL: %s\n",
                    SDL_GetError());
    return false;
  }

  /*** Initialize PNG loading. ***/
  const int imgFlags = IMG_INIT_PNG;
  if (!(IMG_Init(imgFlags) & imgFlags)) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to initialize SDL_Image: %s\n",
                 IMG_GetError());
    close();
    return false;
  }

  /*** Create the main window. ***/
  sdlWindow = SDL_CreateWindow("Factory Example", SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                               SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (sdlWindow == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to create window: %s\n",
                 SDL_GetError());
    close();
    return false;
  }

  /*** Create renderer for the window. ***/
  sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED);
  if (sdlRenderer == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to create renderer: %s\n",
                 SDL_GetError());
    close();
    return false;
  }

  /*** Set renderer color. ***/
  SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 1);

  /*** Load image. ***/
  factorySpritesheet = loadTexture("sheet.png");
  if (factorySpritesheet == NULL) {
    close();
    return false;
  }

  /*** Create the factory. ***/
  factory = new Factory(factorySpritesheet, 0, 0, 15, 11);

  /*** Add consumers. ***/
  factory->AddConsumerMachine(1, 0);
  factory->AddConsumerMachine(4, 0);
  factory->AddConsumerMachine(7, 0);
  factory->AddConsumerMachine(10, 0);
  factory->AddConsumerMachine(13, 0);

  /*** Add producers. ***/
  factory->AddProducerMachine(1, 9);
  factory->AddProducerMachine(4, 9);
  factory->AddProducerMachine(7, 9);
  factory->AddProducerMachine(10, 9);
  factory->AddProducerMachine(13, 9);

  /*** Add robots. ***/
  factory->AddRobotMachine(7, 5);

  return true;
}

/**
 * `close`
 *
 *   Frees resources and shuts down SDL.
 */
static void close() {

  /*** Delete the factory. ***/
  if (factory != NULL) {
    delete factory;
    factory = NULL;
  }

  /*** Destroy the texture. ***/
  if (factorySpritesheet != NULL) {
    SDL_DestroyTexture(factorySpritesheet);
    factorySpritesheet = NULL;
  }

  /*** Destroy the renderer. ***/
  if (sdlRenderer != NULL) {
    SDL_DestroyRenderer(sdlRenderer);
    sdlRenderer = NULL;
  }

  /*** Destroy the window. ***/
  if (sdlWindow != NULL) {
    SDL_DestroyWindow(sdlWindow);
    sdlWindow = NULL;
  }

  /*** Quit SDL subsystems. ***/
  IMG_Quit();
  SDL_Quit();
}

static void update(unsigned int dt) { factory->Update(dt); }

static void draw() {
  SDL_RenderClear(sdlRenderer);
  factory->Draw(sdlRenderer);
  SDL_RenderPresent(sdlRenderer);
}

/**
 * `loadTexture`
 *
 *   Loads a texture from file.
 */
static SDL_Texture *loadTexture(const char *const file) {

  /*** Load the image as a surface. ***/
  SDL_Surface *surface = IMG_Load(file);
  if (surface == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to load image '%s': %s\n",
                 file, IMG_GetError());
    return NULL;
  }

  /*** Set the transparent pixel color. ***/
  SDL_SetColorKey(surface, SDL_TRUE,
                  SDL_MapRGB(surface->format, 0xFF, 0, 0xFF));

  /*** Create texture from surface pixels. ***/
  SDL_Texture *texture = SDL_CreateTextureFromSurface(sdlRenderer, surface);
  SDL_FreeSurface(surface);
  if (texture == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR,
                 "Unable to create texture from '%s': %s\n", file,
                 SDL_GetError());
    return NULL;
  }

  return texture;
}
