#include "SFApp.h"
int i = 0;
SFApp::SFApp(std::shared_ptr<SFWindow> window) : fire(0), is_running(true), sf_window(window) {
  int canvas_w, canvas_h;
  SDL_GetRendererOutputSize(sf_window->getRenderer(), &canvas_w, &canvas_h);

// LevelLoader loader;
// Level level = loader.load("level1.level");
// for (auto item : level.GetData()) {
//     auto p = createAsset(item);
//     item.type item.x item.y
// }
  
  app_box = make_shared<SFBoundingBox>(Vector2(canvas_w, canvas_h), canvas_w, canvas_h);
  player  = make_shared<SFAsset>(SFASSET_PLAYER, sf_window);
  auto player_pos = Point2(canvas_w/10, 50);
  player->SetPosition(player_pos);

  auto alien = make_shared<SFAsset>(SFASSET_ALIEN, sf_window);
  auto alien_pos   = Point2((canvas_w/7.5), 270);
  alien->SetPosition(alien_pos);
  aliens.push_back(alien);

  auto alien1 = make_shared<SFAsset>(SFASSET_ALIEN1, sf_window);
  auto alien_pos1   = Point2((canvas_w/1.3), 140);
  alien1->SetPosition(alien_pos1);
  aliens1.push_back(alien1);

  auto alien2 = make_shared<SFAsset>(SFASSET_ALIEN3, sf_window);
  auto alien_pos2   = Point2((canvas_w/3), 400);
  alien2->SetPosition(alien_pos2);
  aliens2.push_back(alien2);

  auto coin = make_shared<SFAsset>(SFASSET_COIN, sf_window);
  auto pos  = Point2((canvas_w/1.07), 130);
  coin->SetPosition(pos);
  coins.push_back(coin);

  auto coin1 = make_shared<SFAsset>(SFASSET_COIN, sf_window);
  auto pos1  = Point2((canvas_w/15), 322);
  coin1->SetPosition(pos1);
  coins.push_back(coin1);

  auto coin2 = make_shared<SFAsset>(SFASSET_COIN, sf_window);
  auto pos2  = Point2((canvas_w/4.5), 400);
  coin2->SetPosition(pos2);
  coins.push_back(coin2);

  auto wall = make_shared<SFAsset>(SFASSET_WALL, sf_window);
  auto wall_pos  = Point2((canvas_w/6), 100);
  wall->SetPosition(wall_pos);
  walls.push_back(wall);

  auto wall1 = make_shared<SFAsset>(SFASSET_WALL, sf_window);
  auto wall_pos1  = Point2((canvas_w/2.5), 100);
  wall1->SetPosition(wall_pos1);
  walls.push_back(wall1);

  auto wall2 = make_shared<SFAsset>(SFASSET_WALL1, sf_window);
  auto wall_pos2  = Point2((canvas_w/1.3), 5);
  wall2->SetPosition(wall_pos2);
  walls1.push_back(wall2);

  auto wall3 = make_shared<SFAsset>(SFASSET_WALL, sf_window);
  auto wall_pos3  = Point2((canvas_w/1.08), 100);
  wall3->SetPosition(wall_pos3);
  walls.push_back(wall3);

  auto wall4 = make_shared<SFAsset>(SFASSET_WALL, sf_window);
  auto wall_pos4  = Point2((canvas_w/1.2), 225);
  wall4->SetPosition(wall_pos4);
  walls.push_back(wall4);

  auto wall5 = make_shared<SFAsset>(SFASSET_WALL, sf_window);
  auto wall_pos5  = Point2((canvas_w/2), 225);
  wall5->SetPosition(wall_pos5);
  walls.push_back(wall5);

  auto wall6 = make_shared<SFAsset>(SFASSET_WALL, sf_window);
  auto wall_pos6  = Point2((canvas_w/3), 225);
  wall6->SetPosition(wall_pos6);
  walls.push_back(wall6);

  auto wall7 = make_shared<SFAsset>(SFASSET_WALL, sf_window);
  auto wall_pos7  = Point2((canvas_w/1.6), 350);
  wall7->SetPosition(wall_pos7);
  walls.push_back(wall7);

  auto wall8 = make_shared<SFAsset>(SFASSET_WALL, sf_window);
  auto wall_pos8  = Point2((canvas_w/3), 350);
  wall8->SetPosition(wall_pos8);
  walls.push_back(wall8);

  auto wall9 = make_shared<SFAsset>(SFASSET_WALL, sf_window);
  auto wall_pos9  = Point2((canvas_w/6), 350);
  wall9->SetPosition(wall_pos9);
  walls.push_back(wall9);

  auto wall10 = make_shared<SFAsset>(SFASSET_WALL2, sf_window);
  auto wall_pos10  = Point2((canvas_w/6), 471);
  wall10->SetPosition(wall_pos10);
  walls2.push_back(wall10);

  auto key = make_shared<SFAsset>(SFASSET_KEY, sf_window);
  auto key_pos  = Point2((canvas_w/1.1),50);
  key->SetPosition(key_pos);
  keys.push_back(key);
  
  auto star = make_shared<SFAsset>(SFASSET_STAR, sf_window);
  auto star_pos  = Point2((canvas_w/15), 420);
  star->SetPosition(star_pos);
  stars.push_back(star);

}

SFApp::~SFApp() {
}

/**
 * Handle all events that come from SDL.
 * These are timer or keyboard events.
 */
void SFApp::OnEvent(SFEvent& event) {
  SFEVENT the_event = event.GetCode();
  switch (the_event) {
  case SFEVENT_QUIT:
    is_running = false;
    break;
  case SFEVENT_UPDATE:
    OnUpdateWorld();
    OnRender();
    break;
  case SFEVENT_PLAYER_LEFT:
    if (player->IsAlive()) {
      player->GoWest();
     }
    break;
  case SFEVENT_PLAYER_RIGHT:
    if (player->IsAlive()) {
      player->GoEast();
     }
    break;
  case SFEVENT_PLAYER_UP:
    if (player->IsAlive()) {
      player->GoNorth();
     }
    break;
  case SFEVENT_PLAYER_DOWN:
    if (player->IsAlive()) {
      player->GoSouth();
     }
    break;
  }
}

int SFApp::OnExecute() {
  // Execute the app
  SDL_Event event;
  while (SDL_WaitEvent(&event) && is_running) {
    // wrap an SDL_Event with our SFEvent
    SFEvent sfevent((const SDL_Event) event);
    // handle our SFEvent
    OnEvent(sfevent);
  }
}

int SFApp::Counter(){
    i++;
    if (i == 1035){
	i = 0;
    }
}

void SFApp::OnUpdateWorld() {
  // Update projectile positions
  for(auto p: projectiles) {
        p->GoSouth1();
}
   for(auto p: projectiles1) {
        p->GoWest1();
}

   for(auto p: projectiles2) {
        p->GoEast1();
}


  // Update enemy positions
  for(auto a : aliens) {
	Counter();
	if (i >= 500 && i < 530){
	   a->GoWest2();
	   break;
        }
	
        if (i >= 1000 && i < 1030){
	   a->GoEast2();
	   break;
        }
  }

  for(auto a : aliens1) {
	Counter();
	if (i >= 500 && i < 530){
	   a->GoNorth2();
	   break;
        }
	
        if (i >= 1000 && i < 1030){
	   a->GoSouth2();
	   break;
        }
  }

  for(auto a : aliens2) {
	Counter();
	if (i >= 500 && i < 530){
	   a->GoNorth2();
	   break;
        }
	
        if (i >= 1000 && i < 1030){
	   a->GoSouth2();
	   break;
        }
  }

for(auto a : aliens) {
	Counter();
	if (i >= 422 && i < 425 || i >= 922 && i < 925){
	   fire ++;
           FireProjectile();
	   break;
        }
}

for(auto a : aliens1) {
	Counter();
	if (i >= 222 && i < 225 || i >= 722 && i < 725){
	   fire ++;
           FireProjectile1();
	   break;
        }
}

for(auto a : aliens2) {
	Counter();
	if (i >= 222 && i < 225 || i >= 722 && i < 725){
	   fire ++;
           FireProjectile2();
	   break;
        }
}
  // Detect collisions

  for(auto p : projectiles) {
    for(auto w : walls) {
      if(p->CollidesWith(w)) {
        p->HandleCollision();
        w->HandleCollision();
      }
    }
  }

for(auto p : projectiles) {
    for(auto w : walls1) {
      if(p->CollidesWith(w)) {
        p->HandleCollision();
        w->HandleCollision();
      }
    }
  }

for(auto p : projectiles) {
    for(auto w : walls2) {
      if(p->CollidesWith(w)) {
        p->HandleCollision();
        w->HandleCollision();
      }
    }
  }

  for(auto p : projectiles1) {
    for(auto w : walls) {
      if(p->CollidesWith(w)) {
        p->HandleCollision();
        w->HandleCollision();
      }
    }
  }

  for(auto p : projectiles1) {
    for(auto w : walls1) {
      if(p->CollidesWith(w)) {
        p->HandleCollision();
        w->HandleCollision();
      }
    }
  }

  for(auto p : projectiles1) {
    for(auto w : walls2) {
      if(p->CollidesWith(w)) {
        p->HandleCollision();
        w->HandleCollision();
      }
    }
  }

  for(auto p : projectiles2) {
    for(auto w : walls) {
      if(p->CollidesWith(w)) {
        p->HandleCollision();
        w->HandleCollision();
      }
    }
  }

  for(auto p : projectiles2) {
    for(auto w : walls1) {
      if(p->CollidesWith(w)) {
        p->HandleCollision();
        w->HandleCollision();
      }
    }
  }

  for(auto p : projectiles2) {
    for(auto w : walls2) {
      if(p->CollidesWith(w)) {
        p->HandleCollision();
        w->HandleCollision();
      }
    }
  }

   for (auto w : walls1) {
    for(auto c : coins) {
      if(player->CollidesWith(c)) {
        player->HandleCollisionPandC();
        c->HandleCollisionPandC();
	w->WallDisappear();
      }
    }
}

   for (auto w : walls2) {
    for(auto k : keys) {
      if(player->CollidesWith(k)) {
        player->HandleCollisionPandK();
        k->HandleCollisionPandK();
	w->WallDisappear1();
      }
    }
}
    for(auto s : stars) {
      if(s->CollidesWith(player)) {
        s->HandleCollisionPandS();
        player->HandleCollision();
      } 
 } 
    for(auto w : walls) {
      if(w->CollidesWith(player)) {
        w->HandleCollisionPandW();
        player->HandleCollisionPandW();
      } 
 } 

    for(auto w : walls1) {
      if(w->CollidesWith(player)) {
        w->HandleCollisionPandW1();
        player->HandleCollisionPandW1();
      } 
 } 
for(auto p : projectiles) {
    if(p->CollidesWith(player)) {
      p->HandleCollision();
      player->HandleCollision();
      cout<<"GAME OVER"<<endl;
    }
}
  
for(auto p : projectiles1) {
    if(p->CollidesWith(player)) {
      p->HandleCollision();
      player->HandleCollision();
      cout<<"GAME OVER"<<endl;
    }
}

for(auto p : projectiles2) {
    if(p->CollidesWith(player)) {
      p->HandleCollision();
      player->HandleCollision();
      cout<<"GAME OVER"<<endl;
    }
}

for(auto a : aliens) {
    if(a->CollidesWith(player)) {
      a->HandleCollision();
      player->HandleCollision();
      cout<<"GAME OVER"<<endl;
    }
}
  
for(auto a : aliens1) {
    if(a->CollidesWith(player)) {
      a->HandleCollision();
      player->HandleCollision();
      cout<<"GAME OVER"<<endl; 
    }
}

for(auto a : aliens2) {
    if(a->CollidesWith(player)) {
      a->HandleCollision();
      player->HandleCollision();
      cout<<"GAME OVER"<<endl;
    }
}
  // remove dead aliens (the long way)
  list<shared_ptr<SFAsset>> tmp;
  for(auto a : aliens) {
    if(a->IsAlive()) {
      tmp.push_back(a);
    }
  }
  aliens.clear();
  aliens = list<shared_ptr<SFAsset>>(tmp);

  list<shared_ptr<SFAsset>> rc;
  for(auto c : coins) {
    if(c->IsAlive()) {
      rc.push_back(c);
    }
  }
  coins.clear();
  coins = list<shared_ptr<SFAsset>>(rc);

  list<shared_ptr<SFAsset>> rp;
  for(auto p : projectiles) {
    if(p->IsAlive()) {
      rp.push_back(p);
    }
  }
  projectiles.clear();
  projectiles= list<shared_ptr<SFAsset>>(rp);

  list<shared_ptr<SFAsset>> rp1;
  for(auto p : projectiles1) {
    if(p->IsAlive()) {
      rp1.push_back(p);
    }
  }
  projectiles1.clear();
  projectiles1= list<shared_ptr<SFAsset>>(rp1);

  list<shared_ptr<SFAsset>> rp2;
  for(auto p : projectiles2) {
    if(p->IsAlive()) {
      rp2.push_back(p);
    }
  }
  projectiles2.clear();
  projectiles2= list<shared_ptr<SFAsset>>(rp2);

  list<shared_ptr<SFAsset>> rk;
  for(auto k : keys) {
    if(k->IsAlive()) {
      rk.push_back(k);
    }
  }
  keys.clear();
  keys= list<shared_ptr<SFAsset>>(rk);

  list<shared_ptr<SFAsset>> rs;
  for(auto s : stars) {
    if(s->IsAlive()) {
      rs.push_back(s);
    }
  }
  stars.clear();
  stars= list<shared_ptr<SFAsset>>(rs);

}
void SFApp::OnRender() {
  SDL_RenderClear(sf_window->getRenderer());

  // draw the player
  player->IsAlive();
  if (player->IsAlive()) {
    player->OnRender();
 }
  for(auto p: projectiles) {
    if(p->IsAlive()) {p->OnRender();}
  }

  for(auto p: projectiles1) {
    if(p->IsAlive()) {p->OnRender();}
  }

  for(auto p: projectiles2) {
    if(p->IsAlive()) {p->OnRender();}
  }

  for(auto a: aliens) {
    if(a->IsAlive()) {a->OnRender();}
  }

  for(auto a: aliens1) {
    if(a->IsAlive()) {a->OnRender();}
  }

  for(auto a: aliens2) {
    if(a->IsAlive()) {a->OnRender();}
  }

  for(auto c: coins) {
    if(c->IsAlive()) {c->OnRender();}
  }

  for(auto w: walls) {
    if(w->IsAlive()) {w->OnRender();}
  }

  for(auto w: walls1) {
    if(w->IsAlive()) {w->OnRender();}
  }

  for(auto w: walls2) {
    if(w->IsAlive()) {w->OnRender();}
  }

  for(auto k: keys) {
    if(k->IsAlive()) {k->OnRender();}
  }

  for(auto s: stars) {
    if(s->IsAlive()) {s->OnRender();}
  }



  // Switch the off-screen buffer to be on-screen
  SDL_RenderPresent(sf_window->getRenderer());
}

void SFApp::FireProjectile() {
  for(auto a : aliens){
   auto pb = make_shared<SFAsset>(SFASSET_PROJECTILE, sf_window);
   auto v  = a->GetPosition();
   pb->SetPosition(v);
   projectiles.push_back(pb);
  }
}
void SFApp::FireProjectile1() {
  for(auto a : aliens1){
   auto pb = make_shared<SFAsset>(SFASSET_PROJECTILE1, sf_window);
   auto v  = a->GetPosition();
   pb->SetPosition(v);
   projectiles1.push_back(pb);
  }
}
void SFApp::FireProjectile2() {
  for(auto a : aliens2){
   auto pb = make_shared<SFAsset>(SFASSET_PROJECTILE1, sf_window);
   auto v  = a->GetPosition();
   pb->SetPosition(v);
   projectiles2.push_back(pb);
  }
}

