/*******************************************************************************
@file `Sprite.h`
  Created June 28, 2017

@author CJ Dimaano
  <c.j.s.dimaano@gmail.com>
*******************************************************************************/

#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>

/**
 * `Sprite`
 *
 *   Represents a game sprite.
 */
class Sprite {

  /**
   * `_spritesheet`
   *
   *   The spritesheet containing the sprite.
   */
  SDL_Texture *_spritesheet;

  /**
   * `_spriteRegion`
   *
   *   The region of the sprite on the spritesheet.
   */
  SDL_Rect _spriteRegion;

  /**
   * `_drawRegion`
   *
   *   The region of the renderer on which to draw the sprite.
   */
  SDL_Rect _drawRegion;

public:
  /**
   * `Sprite`
   *
   *   Constructor.
   *
   * @param spritesheet
   *   Reference to the spritesheet texture.
   *
   * @param spriteRegion
   *   The region of the sprite in the spritesheet.
   *
   * @param drawRegion
   *   The region of the renderer on which to draw the sprite.
   */
  Sprite(SDL_Texture *const spritesheet, const SDL_Rect spriteRegion,
         const SDL_Rect drawRegion);

  /**
   * `GetSpriteRegion`
   *
   *   Gets the sprite region by reference.
   */
  SDL_Rect &GetSpriteRegion();

  /**
   * `SetSpriteRegion`
   *
   *   Sets the sprite region to the given value.
   */
  void SetSpriteRegion(const SDL_Rect value);

  /**
   * `SetSpriteRegionLocation`
   *
   *   Sets the coordinates of the sprite region on the spritesheet.
   */
  void SetSpriteRegionLocation(const int x, const int y);

  /**
   * `SetSpriteRegionSize`
   *
   *   Sets the height and width of the sprite region on the spritesheet.
   */
  void SetSpriteRegionSize(const int height, const int width);

  /**
   * `GetDrawRegion`
   *
   *   Gets the draw region by reference.
   */
  SDL_Rect &GetDrawRegion();

  /**
   * `SetDrawRegion`
   *
   *  Sets the draw region to the given value.
   */
  void SetDrawRegion(const SDL_Rect value);

  /**
   * `SetDrawRegionLocation`
   *
   *   Sets the coordinates of the sprite region on the renderer.
   */
  void SetDrawRegionLocation(const int x, const int y);

  /**
   * `SetDrawRegionSize`
   *
   *   Sets the height and width of the sprite region on the renderer.
   */
  void SetDrawRegionSize(const int height, const int width);

  /**
   * `Draw`
   *
   *   Draws the sprite on the given renderer.
   */
  void Draw(SDL_Renderer *const sdlRenderer);
};

#endif
