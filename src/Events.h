/*******************************************************************************
@file `Events.h`
  Created July 1, 2017

@author CJ Dimaano
  <c.j.s.dimaano@gmail.com>
*******************************************************************************/

#ifndef EVENTS_H
#define EVENTS_H

#include <SDL2/SDL_log.h>
#include <list>
#include <string>
#include <unordered_map>

/**
 * `EventPayload`
 *
 *   An event payload supplied at each emitted event and containing relevant
 *   event data.
 *
 * @param S
 *   The class of the event source.
 */
template <class S> class EventPayload {
public:
  /**
   * `EventPayload`
   *
   *   Constructor.
   *
   * @param eventSource
   *   The source object of the emitted event.
   *
   * @param eventTarget
   *   The target object of the emitted event.
   */
  EventPayload(S *const eventSource, void *const eventTarget)
      : source(eventSource), target(eventTarget) {}

  /**
   * `~EventPayload`
   *
   *   Destructor.
   */
  virtual ~EventPayload() {}

  /**
   * `source`
   *
   *   The source object of the emitted event.
   */
  S *const source;

  /**
   * `target`
   *
   *   The targeet object of the emitted event.
   */
  void *const target;
};

/**
 * `EventHandler`
 *
 *   Callback function type for handling events.
 *
 * @param P
 *   The class of the event payload.
 *
 * @param payload
 *   The payload associated with the event.
 */
template <class S, class P = EventPayload<S>>
using EventHandler = void (*)(P &payload);

/**
 * `EventEmitter`
 *
 *   Keeps track of events and event handlers, and emits events.
 */
template <class S, class P = EventPayload<S>> class EventEmitter {

  /**
   * `events`
   *
   *   Keeps track of events and associated event handlers.
   */
  std::unordered_map<std::string,
                     std::list<std::pair<void *const, EventHandler<S, P>>>>
      events;

public:
  /**
   * `~EventEmitter`
   *
   *   Destructor.
   */
  virtual ~EventEmitter() {}

  /**
   * `AddEvent`
   *
   *   Adds an event type to the events catalog.
   */
  void AddEvent(std::string value) {
    events.insert(
        std::pair<std::string,
                  std::list<std::pair<void *const, EventHandler<S, P>>>>(
            value, std::list<std::pair<void *const, EventHandler<S, P>>>()));
  }

  /**
   * `AddEventHandler`
   *
   *   Adds an event handler to an event in the catalog.
   */
  void AddEventHandler(std::string event, void *const target,
                       EventHandler<S, P> handler) {
    auto handlers = events.find(event);
    if (handlers == events.end())
      SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Event does not exist: %s\n",
                   event.c_str());
    else
      handlers->second.push_back(
          std::pair<void *const, EventHandler<S, P>>(target, handler));
  }

  /**
   * `RemoveEventHandler`
   *
   *   Removes an event handler from an event in the catalog.
   */
  void RemoveEventHandler(std::string event, void *const target,
                          EventHandler<S, P> handler) {
    auto handlers = events.find(event);
    if (handlers == events.end())
      SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Event does not exist: %s\n",
                   event.c_str());
    else
      handlers->second.remove(
          std::pair<void *const, EventHandler<S, P>>(target, handler));
  }

  /**
   * `EmitEvent`
   *
   *   Emits an event.
   */
  void EmitEvent(std::string event) {
    auto handlers = events.find(event);
    if (handlers == events.end())
      SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Event does not exist: %s\n",
                   event.c_str());
    else {
      for (std::pair<void *const, EventHandler<S, P>> handler :
           handlers->second) {
        P payload = MakePayload(handler.first);
        handler.second(payload);
      }
    }
  }

  virtual P MakePayload(void *const target) {
    return P(dynamic_cast<S *>(this), target);
  }
};

#endif
