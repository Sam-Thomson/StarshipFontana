#ifndef SFASSET_H
#define SFASSET_H

#include <string>
#include <memory>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

#include "SFCommon.h"
#include "SFEvent.h"
#include "SFWindow.h"
#include "SFBoundingBox.h"

/**
 * We could create SFPlayer, SFProjectile and SFAsset which are subclasses
 * of SFAsset.  However, I've made an implementation decision to use this
 * enum to mark the type of the SFAsset.  If we add more asset types then
 * the subclassing strategy becomes a better option.
 */
enum SFASSETTYPE {SFASSET_DEAD, SFASSET_PLAYER, SFASSET_PROJECTILE, SFASSET_PROJECTILE1, SFASSET_ALIEN, SFASSET_ALIEN1, SFASSET_ALIEN2, SFASSET_ALIEN3, SFASSET_COIN, SFASSET_WALL, SFASSET_WALL1, SFASSET_WALL2, SFASSET_KEY, SFASSET_STAR, SFASSET_NOTHING};

class SFAsset {
public:
  SFAsset(const SFASSETTYPE, const std::shared_ptr<SFWindow>);
  SFAsset(const SFAsset&);
  virtual ~SFAsset();

  virtual void      SetPosition(Point2 &);
  virtual Point2    GetPosition();
  virtual void      SetPrevPosition(Point2 &);
  virtual SFAssetId GetId();
  virtual void      OnRender();
  virtual void      GoEast();
  virtual void      GoEast1();
  virtual void      GoEast2();
  virtual void      GoWest();
  virtual void      GoWest1();
  virtual void      GoWest2();
  virtual void      GoNorth();
  virtual void      GoNorth1();
  virtual void      GoNorth2();
  virtual void      GoSouth();
  virtual void      GoSouth1();
  virtual void      GoSouth2();
  virtual void      SetNotAlive();
  virtual void      SetAlive();
  virtual bool      IsAlive();
  virtual void      HandleCollision();
  virtual void      HandleCollisionPD();
  virtual void      HandleCollisionPandC();
  virtual void      HandleCollisionPandK();
  virtual void      HandleCollisionPandS();
  virtual void      HandleCollisionPandW();
  virtual void      HandleCollisionPandW1();
  virtual void      WallDisappear();
  virtual void      WallDisappear1();

  virtual bool                      CollidesWith(shared_ptr<SFAsset>);
  virtual shared_ptr<SFBoundingBox> GetBoundingBox();
private:
  // it would be nice if we could make this into a smart pointer,
  // but, because we need to call SDL_FreeSurface on it, we can't.
  // (or we could use a std::shared_ptr with a custom Deleter, but
  // that's a little too much right now)
  SDL_Texture               * sprite;
  shared_ptr<SFBoundingBox>   bbox;
  SFASSETTYPE                 type;
  SFAssetId                   id;
  std::shared_ptr<SFWindow>   sf_window;
  std::shared_ptr<Point2> prevposition;

  static int SFASSETID;
};

#endif
