#include "CollisionHandling.h"
#include <iostream>
#include <map>
#include <string>
#include <typeinfo>
#include <typeindex>
#include "ResourcesManager.h"
#include "MovingObjects/Player.h"
#include "MovingObjects/Enemies/Orange.h"
#include "MovingObjects/Enemies/RollingEnemy.h"
#include "MovingObjects/Enemies/FlyingMonster.h"
#include "MovingObjects/Enemies/Jellyfish.h"
#include "StaticObjects/Tile.h"
#include "StaticObjects/SurpriseBox.h"
#include "StaticObjects/Escalator.h"
#include "StaticObjects/Cannon.h"
#include "StaticObjects/Coin.h"
#include "StaticObjects/SpringBoard.h"
#include "StaticObjects/Bone.h"
#include "StaticObjects/Spike.h"
#include "StaticObjects/Carnivorous.h"
#include "StaticObjects/Bullet.h"
#include "StaticObjects/Water.h"
#include "StaticObjects/Door.h"
#include "StaticObjects/Bubble.h"
#include "macros.h"


namespace
{
  
    void playerEnemy(GameObject& player, GameObject& enemy)
    {
        Player& p = dynamic_cast<Player&>(player);
        Enemy& e = dynamic_cast<Enemy&>(enemy);
        
        //player steps on enemy:
        if (p.getPrevLoc().y <= e.getPosition().y - e.getGlobalBounds().height) {
            ResourcesManager::instance().playSound(Sound::hit);
            e.setDispose();
        }
        //enemy hurts the player:
        else if(!p.defended()) {
            ResourcesManager::instance().playSound(Sound::hurt);
            p.decreaseLives();
            p.setDispose();
        }
    }

    void playerRollingEnemy(GameObject& player, GameObject& rollingEnemy)
    {
        Player& p = dynamic_cast<Player&>(player);
        RollingEnemy& r = dynamic_cast<RollingEnemy&>(rollingEnemy);

        //player steps on rolling enemy:
        if (p.getPrevLoc().y <= r.getPosition().y - r.getGlobalBounds().height) {
            //makes enemy crazy:
            if (!r.rolling()) {
                r.setRolling();
                p.littleJump();
            }
            else { //already crazy, dispose him:
                ResourcesManager::instance().playSound(Sound::hit);
                ResourcesManager::instance().pauseSound(Sound::enemy);
                r.setDispose();   
            }
        }
        else if (!p.defended()) {
            ResourcesManager::instance().playSound(Sound::hurt);
            p.decreaseLives();
            p.setDispose();
        }
    }

    void playerSpike(GameObject& player, GameObject& spike)
    {
        Player& p = dynamic_cast<Player&>(player);
        Spike& s = dynamic_cast<Spike&>(spike);

        //player steps on spike:
        if (p.getPrevLoc().y <= s.getPosition().y - s.getGlobalBounds().height) {
            if (!p.defended()) {
                ResourcesManager::instance().playSound(Sound::hurt);
                p.decreaseLives();
                p.setDispose();
            }
            else { 
                p.setPosition({ p.getPrevLoc().x, p.getPosition().y });
            }
        }
        else { //player hits the spike from the sides - go back
            p.setPosition({ p.getPrevLoc().x,p.getPosition().y });
        }
    }

    void playerCarnivorous(GameObject& player, GameObject& /*carnivorous*/)
    {
        Player& p = dynamic_cast<Player&>(player);
        if (!p.defended()) {
            ResourcesManager::instance().playSound(Sound::hurt);
            p.decreaseLives();
            p.setDispose();
        }
    }

    void playerBullet(GameObject& player, GameObject& /*bullet*/)
    {
        Player& p = dynamic_cast<Player&>(player);
        if (!p.defended()) {
            ResourcesManager::instance().playSound(Sound::hurt);
            p.decreaseLives();
            p.setDispose();
        }
    }

    void playerStatic(GameObject& player, GameObject& stat)
    {
        Player& p = dynamic_cast<Player&>(player);
        StaticObject& s = dynamic_cast<StaticObject&>(stat);
      
        p.setDirection(Direction::Stay);

        //player heads the static object:
        if (p.getPrevLoc().y - p.getGlobalBounds().height > s.getPosition().y) {
            if (typeid(stat) == typeid(SurpriseBox)) {
                SurpriseBox& surpriseBox = dynamic_cast<SurpriseBox&>(s);
                surpriseBox.dropCoin();
            }
            p.goBack();
            p.setVelocity(-0.25f * p.getVelocity()); //go back to the ground faster
        }
        //player steps on static object:
        else if (p.getPrevLoc().y <= s.getPosition().y - s.getGlobalBounds().height) {
            p.setVelocity({ 0,0 });
            p.setPosition({ p.getPosition().x, p.getPrevLoc().y });
            p.canJump(true);
        }
        else { //player besides static object
            p.setPosition({ p.getPrevLoc().x ,p.getPosition().y });
        }
    }

    void playerEscalator(GameObject& player, GameObject& escalator)
    {
        Player& p = dynamic_cast<Player&>(player);
        Escalator& e = dynamic_cast<Escalator&>(escalator);
        p.setDirection(Direction::Stay); 
        sf::Vector2f newPos(p.getPosition());

        //player below the escalator:
        if (p.getPrevLoc().y - p.getGlobalBounds().height > e.getPrevLoc().y) {
            e.goBack();
            p.goBack();
            p.setVelocity(-0.5f * p.getVelocity()); //go back to the ground faster
        }
        if (p.getPrevLoc().y > e.getPosition().y) { //player is besides escalator
            newPos.x = p.getPrevLoc().x;
        }
        else { //player is on escalator
            p.setVelocity({ 0,0 });
            p.canJump(true);
            newPos.y = e.getPosition().y - e.getGlobalBounds().height + GAP;
        }
        p.setPosition(newPos);
    }
    
    void playerSpringBoard(GameObject& player, GameObject& springBoard)
    {
        Player& p = dynamic_cast<Player&>(player);
        SpringBoard& s = dynamic_cast<SpringBoard&>(springBoard);
        p.setDirection(Direction::Stay);

        //player steps on springboard:
        if (p.getPrevLoc().y <= s.getPosition().y - s.getGlobalBounds().height) {
            ResourcesManager::instance().playSound(Sound::springBoard);
            //attach the player to the springboard:
            p.setPosition({ p.getPosition().x, s.getPosition().y - s.getGlobalBounds().height });
            s.setActive(true); //activate the springboard
        }
        else { //player besides the springboard
            p.setPosition({ p.getPrevLoc().x ,p.getPosition().y });
        }
        if (s.animationEnd()) {
            p.setPosition({ p.getPosition().x, s.getPosition().y - s.getGlobalBounds().height });
            p.setVelocity({ 0, SPRINGBOARD_SPEED }); //player jump
            s.reset();
        }
    }

    void playerCoin(GameObject& player, GameObject& coin)
    {
        ResourcesManager::instance().playSound(Sound::coin);

        Player& p = dynamic_cast<Player&>(player);
        p.addScore(5);
        
        Coin& c = dynamic_cast<Coin&>(coin);
        c.setDispose();
    }

    void playerDoor(GameObject& player, GameObject& /*door*/)
    {
        Player& p = dynamic_cast<Player&>(player);
        p.setWin();
    }
  
    void enemyStatic(GameObject& enemy, GameObject& /*tile*/)
    {
        Enemy& e = dynamic_cast<Enemy&>(enemy);
        e.goBack();
        e.oppositeDirectionX();
    }

    void jellyfishTile(GameObject& jellyfish, GameObject& /*tile*/)
    {
        Jellyfish& j = dynamic_cast<Jellyfish&>(jellyfish);
        j.goBack();
        j.oppositeDirectionY();
    }

    void enemyBone(GameObject& enemy, GameObject& bone)
    {
        Enemy& e = dynamic_cast<Enemy&>(enemy);
        Bone& b = dynamic_cast<Bone&>(bone);

        ResourcesManager::instance().playSound(Sound::hit);
        e.setDispose(); 
        b.setDispose(); 
    }

    void rollingEnemyBone(GameObject& rollingEnemy, GameObject& bone)
    {
        RollingEnemy& r = dynamic_cast<RollingEnemy&>(rollingEnemy);
        Bone& b = dynamic_cast<Bone&>(bone);
        if (!r.rolling()) { //makes him crazy in the first bone hit:
            r.setRolling();
        }
        else { //already crazy:
            ResourcesManager::instance().pauseSound(Sound::enemy);
            ResourcesManager::instance().playSound(Sound::hit);
            r.setDispose();
        }
        b.setDispose();
    }

    void playerWater(GameObject& player, GameObject& /*water*/)
    {
        Player& p = dynamic_cast<Player&>(player);
        p.setInWater(true);
    }

    void playerBubble(GameObject& player, GameObject& bubble)
    {
        Player& p = dynamic_cast<Player&>(player);
        Bubble& b = dynamic_cast<Bubble&>(bubble);

        //takes a defence bubble only if the player isn't defended:
        if (!p.defended()) {
            ResourcesManager::instance().playSound(Sound::bubble);
            p.setDefended(b);
        }

    }

    using HitFunctionPtr = void (*)(GameObject&, GameObject&);
    using Key = std::pair<std::type_index, std::type_index>;
    using HitMap = std::map<Key, HitFunctionPtr>;

    HitMap initializeCollisionMap()
    {
        HitMap phm;
        phm[Key(typeid(Player), typeid(Orange))] = &playerEnemy;
        phm[Key(typeid(Player), typeid(RollingEnemy))] = &playerRollingEnemy;
        phm[Key(typeid(Player), typeid(FlyingMonster))] = &playerEnemy;
        phm[Key(typeid(Player), typeid(Jellyfish))] = &playerEnemy;
        phm[Key(typeid(Player), typeid(Water))] = &playerWater;
        phm[Key(typeid(Player), typeid(Tile))] = &playerStatic;
        phm[Key(typeid(Player), typeid(SurpriseBox))] = &playerStatic;
        phm[Key(typeid(Player), typeid(Bubble))] = &playerBubble;
        phm[Key(typeid(Player), typeid(Cannon))] = &playerStatic;
        phm[Key(typeid(Player), typeid(Escalator))] = &playerEscalator;
        phm[Key(typeid(Player), typeid(Coin))] = &playerCoin;
        phm[Key(typeid(Player), typeid(SpringBoard))] = &playerSpringBoard;
        phm[Key(typeid(Player), typeid(Spike))] = &playerSpike;
        phm[Key(typeid(Player), typeid(Carnivorous))] = &playerCarnivorous;
        phm[Key(typeid(Player), typeid(Bullet))] = &playerBullet;
        phm[Key(typeid(Player), typeid(Door))] = &playerDoor;
        phm[Key(typeid(Orange), typeid(Tile))] = &enemyStatic;
        phm[Key(typeid(Orange), typeid(Cannon))] = &enemyStatic;
        phm[Key(typeid(Orange), typeid(Spike))] = &enemyStatic;
        phm[Key(typeid(Orange), typeid(SpringBoard))] = &enemyStatic;
        phm[Key(typeid(RollingEnemy), typeid(Tile))] = &enemyStatic;
        phm[Key(typeid(RollingEnemy), typeid(Spike))] = &enemyStatic;
        phm[Key(typeid(FlyingMonster), typeid(Tile))] = &enemyStatic;
        phm[Key(typeid(Jellyfish), typeid(Tile))] = &jellyfishTile;
        phm[Key(typeid(Orange), typeid(Bone))] = &enemyBone;
        phm[Key(typeid(RollingEnemy), typeid(Bone))] = &enemyBone;
        phm[Key(typeid(FlyingMonster), typeid(Bone))] = &enemyBone;
        phm[Key(typeid(Jellyfish), typeid(Bone))] = &enemyBone;
        phm[Key(typeid(RollingEnemy), typeid(Bone))] = &rollingEnemyBone;
        return phm;
    }

    HitFunctionPtr lookup(const std::type_index& class1, const std::type_index& class2)
    {
        static HitMap collisionMap = initializeCollisionMap();
        //search in the map for the relevant hit function of these two objects:
        auto mapEntry = collisionMap.find(std::make_pair(class1, class2));
        if (mapEntry == collisionMap.end())
        {
            return nullptr;
        }
        return mapEntry->second;
    }

} // end namespace


void processCollision(GameObject& object1, GameObject& object2)
{
    //checks if these two objects collide:
    if (object1.collides(object2)) {
        auto phf = lookup(typeid(object1), typeid(object2));
        if (phf) {
            phf(object1, object2); //calls the hit function
        }
    }
}
