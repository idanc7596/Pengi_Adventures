#include "MovingObjects/Player.h"
#include "ResourcesManager.h"
#include "Direction.h"
#include "StaticObjects/Bone.h"
#include "StaticObjects/Water.h"
#include "StaticObjects/Bubble.h"
#include "Board.h"

Player::Player()
    :MovingObject(Objects::player, Direction::Right, Texture::player)
{
    m_moveSpeed = 200.f;
}

void Player::decreaseLives()
{
    --m_lives;
}

void Player::resetForNewLevel()
{
    setPosition({ 0.f, 0.33f * WINDOW_HEIGHT });

    m_lives = numOfLives;
    m_win = false;

    m_score = 0;
    m_canJump = false;
    m_isJump = false;
    m_inWater = false;
    m_faceLeft = false;
}

void Player::resetForRestartLevel()
{
    setPosition({ 0.f, 0.33f * WINDOW_HEIGHT });

    m_score = 0;
    m_canJump = false;
    m_isJump = false;
    m_inWater = false;
    m_faceLeft = false;
}

void Player::update(sf::Time delta, Board& board)
{
    move(delta);
    shoot(board);
    setInWater(checkInWater(board));
    handleDefence(); //defence bubble
}

void Player::move(sf::Time delta)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) 
        && m_sprite.getPosition().x > 0) {
        m_faceLeft = true;
        m_velocity.x = -m_moveSpeed;
        m_animation.update(delta);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        m_faceLeft = false;
        m_velocity.x = m_moveSpeed;
        m_animation.update(delta);
    }
    else {
        m_velocity.x = 0; //stay in his place
    }

    //jumping:
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space)||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        && m_canJump) {
        m_isJump = true;
        m_velocity.y = -m_jumpSpeed;
        m_dir = Direction::Stay;
        if (!m_inWater) { //in water there is no jump limit
            m_canJump = false;
        }
    }

    //detecting we touch the ground:
    //first case: we are still in the air:
    if (m_sprite.getPosition().y < m_groundHeight || m_velocity.y < 0) {
        m_velocity.y += m_gravity; //accelerate the velocity towards the ground
    }
    else { //we are on the ground
        m_sprite.setPosition(m_sprite.getPosition().x, float(m_groundHeight));
        m_velocity.y = 0;
        m_isJump = false;
        m_canJump = true;
    }

    m_prevLoc = m_sprite.getPosition(); //will be used in collision handling
    m_sprite.move(m_velocity * delta.asSeconds());
}

void Player::littleJump()
{
    m_isJump = true;
    m_velocity.y = -0.7f*m_jumpSpeed;
    m_dir = Direction::Stay;
}


void Player::setDirection(sf::Keyboard::Key key)
{
    if (auto dir = toDirection(key))
    {
        if (m_inWater) {
            if (*dir == Direction::Left) {
                m_dir = Direction::SwimLeft;
            }
            else if(*dir == Direction::Right) {
                m_dir = Direction::SwimRight;
            }
        }
        else {
            m_dir = *dir;
        }
        m_animation.setDirection(m_dir);
    }
}

void Player::setDirection(Direction dir)
{
    m_dir = dir;
}

void Player::shoot(Board& board)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)
        && m_clock.getElapsedTime().asSeconds() > shootTimeGap) {
        ResourcesManager::instance().playSound(Sound::shoot);
        //spawn a bone:
        sf::Vector2f bonePosition(m_sprite.getPosition().x, 
            m_sprite.getPosition().y-m_sprite.getGlobalBounds().height/2.f);
        auto bone = std::make_unique<Bone>(bonePosition, *this);
        board.addStaticObject(std::move(bone));
        m_clock.restart();
    }
}

void Player::setInWater(bool inWater)
{
    m_inWater = inWater;
    if (inWater) {
        m_sprite.setColor(sf::Color(255, 255, 255, 180)); //opacity
        m_jumpSpeed = 200.f; //decrease the jump height in the water
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            m_dir = Direction::SwimLeft;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            m_dir = Direction::SwimRight;
        }     
    }
    else {
        m_sprite.setColor(sf::Color(255, 255, 255, 255)); 
        m_jumpSpeed = 432.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            m_dir = Direction::Left;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            m_dir = Direction::Right;

        }
    }
    m_animation.setDirection(m_dir);
}

bool Player::checkInWater(Board& board)
{
    //chack if the player is inside water (collides with some water tile):
    for (int i = 0; i < board.getNumOfStaticObjects(); i++) {
        if (Water* w = dynamic_cast<Water*>(&board.getStaticObject(i))) {
            if (this->collides(*w)) {
                if (!m_inWater) {
                    ResourcesManager::instance().playSound(Sound::jumpIntoWater);
                    m_waterClock.restart();
                }
                else if (m_waterClock.getElapsedTime().asSeconds() > waterTimeGap) {
                    //bubbles sound:
                    ResourcesManager::instance().playSound(Sound::water);
                    m_waterClock.restart();
                }
                return true;
            }
        }
    }
    return false;
}

int Player::getScore() const
{
    return m_score;
}

int Player::getLives() const
{
    return m_lives;
}

void Player::setLives(int lives)
{
    m_lives = lives;
}

void Player::addScore(int add)
{
    m_score += add;
}

bool Player::win() const
{
    return m_win;
}

void Player::setWin()
{
    m_win = true;
}

bool Player::isFaceLeft() const
{
    return m_faceLeft;
}

void Player::canJump(bool jump)
{
    m_canJump = jump;
}

bool Player::defended() const
{
    return m_defended; //by defence bubble
}

void Player::setDefended(Bubble& bubble)
{
    m_defended = true;
    m_bubble = &bubble; //save a reference to the bubble that defends the player
    m_defenceClock.restart();
}

void Player::handleDefence()
{
    if (m_defended) {
        if (m_defenceClock.getElapsedTime().asSeconds() > defenceTime) {
            m_defended = false;
            m_bubble->setDispose();
            m_bubble = nullptr;
            m_sprite.setColor(sf::Color(255, 255, 255, 255));
            return;
        }
        m_sprite.setColor(sf::Color(255, 255, 255, 180)); //opacity
        //so the bubble will follow the player's position:
        m_bubble->setPosition({ this->getPosition().x-15.f, this->getPosition().y+7.f });
    }
}