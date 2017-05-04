#include "SFAsset.h"

int SFAsset::SFASSETID=0;
int NoOfCoins = 3;
int NoOfKeys = 1;
int gamestatus = 0;

SFAsset::SFAsset(SFASSETTYPE type, std::shared_ptr<SFWindow> window): type(type), sf_window(window) {
  this->id   = ++SFASSETID;

  switch (type) {
  case SFASSET_PLAYER:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/player.gif");
    break;
  case SFASSET_PROJECTILE:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/projectile.png");
    break;
  case SFASSET_PROJECTILE1:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/projectile1.png");
    break;
  case SFASSET_ALIEN:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/alien.png");
    break;
  case SFASSET_ALIEN1:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/alien1.png");
    break;
  case SFASSET_ALIEN2:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/alien2.png");
    break;
  case SFASSET_ALIEN3:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/alien3.png");
    break;
  case SFASSET_COIN:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/coin.png");
    break;
  case SFASSET_WALL:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/wall.png");
    break;
  case SFASSET_WALL1:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/wall1.png");
    break;
  case SFASSET_WALL2:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/wall2.png");
    break;
  case SFASSET_KEY:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/key.png");
    break;
  case SFASSET_STAR:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/star.png");
    break;

  }

  if(!sprite) {
    cerr << "Could not load asset of type " << type << endl;
    throw SF_ERROR_LOAD_ASSET;
  }

  // Get texture width & height
  int w, h;
  SDL_QueryTexture(sprite, NULL, NULL, &w, &h);

  // Initialise bounding box
  bbox = make_shared<SFBoundingBox>(SFBoundingBox(Vector2(0.0f, 0.0f), w, h));

  prevposition = make_shared<Point2>(Point2(0.0f, 0.0f));
}

SFAsset::SFAsset(const SFAsset& a) {
  sprite = a.sprite;
  sf_window = a.sf_window;
  bbox   = a.bbox;
  type   = a.type;
  prevposition = a.prevposition;
}

SFAsset::~SFAsset() {
  bbox.reset();
  if(sprite) {
    SDL_DestroyTexture(sprite);
    sprite = nullptr;
  }
}

/**
 * The logical coordinates in the game assume that the screen
 * is indexed from 0,0 in the bottom left corner.  The blittable
 * coordinates of the screen map 0,0 to the top left corner. We
 * need to convert between the two coordinate spaces.  We assume
 * that there is a 1-to-1 quantisation.
 */
Vector2 GameSpaceToScreenSpace(SDL_Renderer* renderer, Vector2 &r) {
  int w, h;
  SDL_GetRendererOutputSize(renderer, &w, &h);

  return Vector2 (
                  r.getX(),
                  (h - r.getY())
                  );
}

void SFAsset::SetPosition(Point2 & point) {
  Vector2 v(point.getX(), point.getY());
  bbox->SetCentre(v);
}

void SFAsset::SetPrevPosition(Point2 & prevposition) {
  Vector2 v(prevposition.getX(), prevposition.getY());
  bbox->SetCentre(v);
}

Point2 SFAsset::GetPosition() {
  return Point2(bbox->centre->getX(), bbox->centre->getY());
}


SFAssetId SFAsset::GetId() {
  return id;
}

void SFAsset::OnRender() {
  // 1. Get the SDL_Rect from SFBoundingBox
  SDL_Rect rect;

  Vector2 gs = (*(bbox->centre) + (*(bbox->extent_x) * -1)) + (*(bbox->extent_y) * 1);
  Vector2 ss = GameSpaceToScreenSpace(sf_window->getRenderer(), gs);
  rect.x = ss.getX();
  rect.y = ss.getY();
  rect.w = bbox->extent_x->getX() * 2;
  rect.h = bbox->extent_y->getY() * 2;

  // 2. Blit the sprite onto the level
  SDL_RenderCopy(sf_window->getRenderer(), sprite, NULL, &rect);
}

void SFAsset::GoWest() {
  prevposition = make_shared<Point2>(GetPosition());
  Vector2 c = *(bbox->centre) + Vector2(-5.0f, 0.0f);
  if(!(c.getX() < 0)) {
    bbox->centre.reset();
    bbox->centre = make_shared<Vector2>(c);
    SFASSET_PLAYER:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/player3.gif");
  }
}

void SFAsset::GoEast() {
  prevposition = make_shared<Point2>(GetPosition());
  int w, h;
  SDL_GetRendererOutputSize(sf_window->getRenderer(), &w, &h);

  Vector2 c = *(bbox->centre) + Vector2(5.0f, 0.0f);
  if(!(c.getX() > w)) {
    bbox->centre.reset();
    bbox->centre = make_shared<Vector2>(c);
    SFASSET_PLAYER:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/player4.gif");
  }
}

void SFAsset::GoEast1() {
  Vector2 c = *(bbox->centre) + Vector2(1.0f, 0.0f);
  bbox->centre.reset();
  bbox->centre = make_shared<Vector2>(c);
}

void SFAsset::GoWest1() {
  Vector2 c = *(bbox->centre) + Vector2(-1.0f, 0.0f);
  bbox->centre.reset();
  bbox->centre = make_shared<Vector2>(c);
}

void SFAsset::GoSouth1() {
  Vector2 c = *(bbox->centre) + Vector2(0.0f, -1.0f);
  bbox->centre.reset();
  bbox->centre = make_shared<Vector2>(c);
}

void SFAsset::GoNorth1() {
  Vector2 c = *(bbox->centre) + Vector2(0.0f, 1.0f);
  bbox->centre.reset();
  bbox->centre = make_shared<Vector2>(c);
}

void SFAsset::GoEast2() {
  Vector2 c = *(bbox->centre) + Vector2(5.0f, 0.0f);
  bbox->centre.reset();
  bbox->centre = make_shared<Vector2>(c);
}

void SFAsset::GoWest2() {
  Vector2 c = *(bbox->centre) + Vector2(-5.0f, 0.0f);
  bbox->centre.reset();
  bbox->centre = make_shared<Vector2>(c);
}

void SFAsset::GoSouth2() {
  Vector2 c = *(bbox->centre) + Vector2(0.0f, -5.0f);
  bbox->centre.reset();
  bbox->centre = make_shared<Vector2>(c);
}

void SFAsset::GoNorth2() {
  Vector2 c = *(bbox->centre) + Vector2(0.0f, 5.0f);
  bbox->centre.reset();
  bbox->centre = make_shared<Vector2>(c);
}

void SFAsset::GoNorth() {
  prevposition = make_shared<Point2>(GetPosition());
  int w, h;
  SDL_GetRendererOutputSize(sf_window->getRenderer(), &w, &h);

  Vector2 c = *(bbox->centre) + Vector2(0.0f, 5.0f);
  if(!(c.getY() > h)) {
    bbox->centre.reset();
    bbox->centre = make_shared<Vector2>(c);
    SFASSET_PLAYER:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/player.gif");
  }
}

void SFAsset::GoSouth() {
  prevposition = make_shared<Point2>(GetPosition());
  Vector2 c = *(bbox->centre) + Vector2(0.0f, -5.0f);
  if(!(c.getY() < 0.1)) {
    bbox->centre.reset();
    bbox->centre = make_shared<Vector2>(c);
    SFASSET_PLAYER:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/player2.gif");

  }
}

bool SFAsset::CollidesWith(shared_ptr<SFAsset> other) {
  return bbox->CollidesWith(other->bbox);
}

shared_ptr<SFBoundingBox> SFAsset::GetBoundingBox() {
  return bbox;
}

void SFAsset::SetNotAlive() {
  type = SFASSET_DEAD;
}

void SFAsset::SetAlive() {
  type != SFASSET_DEAD;
}

bool SFAsset::IsAlive() {
  return (SFASSET_DEAD != type);
}


void SFAsset::HandleCollision() {
  if(SFASSET_PROJECTILE == type || SFASSET_PROJECTILE1 == type || SFASSET_PLAYER == type || SFASSET_ALIEN == type) {
    SetNotAlive();
  }
}

void SFAsset::HandleCollisionPD() {
  if(SFASSET_PLAYER == type) {
    SetNotAlive();
  }
}

void SFAsset::HandleCollisionPandC() {
  if(SFASSET_COIN == type) {
    SetNotAlive();
    NoOfCoins--;
  }
}

void SFAsset::HandleCollisionPandK() {
  if(SFASSET_KEY == type) {
    SetNotAlive();
    NoOfKeys--;
  }
}

void SFAsset::HandleCollisionPandS() {
  if(SFASSET_STAR == type) {
    SetNotAlive();
  }
}
  
void SFAsset::HandleCollisionPandW() {
  if(SFASSET_PLAYER == type) {
    SetPrevPosition(*(prevposition.get()));
   }
}

void SFAsset::HandleCollisionPandW1() {
if (NoOfCoins != 0) {
  if(SFASSET_PLAYER == type) {
    SetPrevPosition(*(prevposition.get()));
   }
 }
}

void SFAsset::WallDisappear(){
  if (NoOfCoins == 0) {
      if(SFASSET_WALL1 == type) {
      SetNotAlive();
      }
}
}
void SFAsset::WallDisappear1(){
   if(NoOfKeys == 0){
	if(SFASSET_WALL2 == type){
	SetNotAlive();
	}
     }
}


