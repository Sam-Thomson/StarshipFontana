#ifndef SFAPP_H
#define SFAPP_H

#include <memory>   // Pull in std::shared_ptr
#include <iostream> // Pull in std::cerr, std::endl
#include <list>     // Pull in list
#include <sstream>

using namespace std;

#include "SFCommon.h"
#include "SFEvent.h"
#include "SFAsset.h"

/**
 * Represents the StarshipFontana application.  It has responsibilities for
 * * Creating and destroying the app window
 * * Processing game events
 */
class SFApp {
public:
  SFApp(std::shared_ptr<SFWindow>);
  virtual ~SFApp();
  void    OnEvent(SFEvent &);
  int     OnExecute();
  int     Counter();
  void    OnUpdateWorld();
  void    OnRender();

  void    FireProjectile();
  void    FireProjectile1();
  void    FireProjectile2();
private:
  bool                    is_running;

  shared_ptr<SFWindow>       sf_window;

  shared_ptr<SFAsset>        player;
  shared_ptr<SFBoundingBox>  app_box;
  list<shared_ptr<SFAsset> > projectiles;
  list<shared_ptr<SFAsset> > projectiles1;
  list<shared_ptr<SFAsset> > projectiles2;
  list<shared_ptr<SFAsset> > aliens;
  list<shared_ptr<SFAsset> > aliens1;
  list<shared_ptr<SFAsset> > aliens2;
  list<shared_ptr<SFAsset> > coins;
  list<shared_ptr<SFAsset> > walls;
  list<shared_ptr<SFAsset> > walls1;
  list<shared_ptr<SFAsset> > walls2;
  list<shared_ptr<SFAsset> > keys;
  list<shared_ptr<SFAsset> > stars;
  list<shared_ptr<SFAsset> > messages;
  list<shared_ptr<SFAsset> > messages1;

  int fire;
};
#endif
