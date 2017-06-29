/*******************************************************************************
@file `AnimatedSprite.h`
  Created June 28, 2017

@author CJ Dimaano
  <c.j.s.dimaano@gmail.com>
*******************************************************************************/

#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include "Sprite.h"

/**
 * `AnimatedSprite`
 *
 *   Represents an animated game sprite.
 */
class AnimatedSprite : public Sprite {

  /**
   * `_frameDelay`
   *
   *   The number of ticks to display each frame.
   */
  unsigned int _frameDelay;

  /**
   * `_frameTick`
   *   The number of ticks since the last frame update.
   */
  unsigned int _frameTick;

  /**
   * `_frameCount`
   *
   *   The number of frames in the frames region.
   */
  int _frameCount;

  /**
   * `_currentFrame`
   *
   *   The current frame to be drawn.
   */
  int _currentFrame;

  /**
   * `_isPaused`
   *
   *   True if the animated sprite is paused; otherwise, false.
   */
  bool _isPaused;

  /**
   * `_framesRegion`
   *
   *   The region of sprite frames in the spritesheet.
   */
  SDL_Rect _framesRegion;

public:
  /**
   * `AnimatedSprite`
   *
   *   Constructor.
   *
   * @param spritesheet
   *   Reference to the spritesheet texture.
   *
   * @param framesRegion
   *   The region of the sprite frames in the spritesheet.
   *
   * @param drawRegion
   *   The region of the renderer on which to draw the sprite.
   *
   * @param frameHeight
   *   The height of each sprite frame.
   *
   * @param frameWidth
   *   The width of each sprite frame.
   *
   * @param frameCount
   *   The number of frames in the frames region.
   *
   * @param frameDelay
   *   The number of ticks to display each frame.
   */
  AnimatedSprite(SDL_Texture *const spritesheet, const SDL_Rect framesRegion,
                 const SDL_Rect drawRegion, const int frameHeight,
                 const int frameWidth, const int frameCount,
                 const unsigned int frameDelay);

  /**
   * `Play`
   *
   *   Starts animating the sprite.
   */
  void Play();

  /**
   * `Pause`
   *
   *   Stops animating the sprite.
   */
  void Pause();

  /**
   * `Restart`
   *
   *   Resets the current frame to the first.
   */
  void Restart();

  /**
   * `SetFrameDelay`
   *
   *   Sets the delay between each frame.
   */
  void SetFrameDelay(const unsigned int value);

  /**
   * `SetFrame`
   *
   *   Sets the current frame to be drawn.
   */
  void SetFrame(const int index);

  /**
   * `Update`
   *
   *   Updates the animated sprite.
   *
   * @param dt
   *   The change in ticks since the last update.
   */
  void Update(unsigned int dt);
};

#endif
