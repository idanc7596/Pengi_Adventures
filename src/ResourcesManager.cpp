#include "ResourcesManager.h"
#include "Direction.h"
#include "macros.h"
#include <stdexcept>

//init animations data:
namespace
{
    AnimationData playerData()
    {
        sf::Vector2i walkSize(67, 73);

        AnimationData playerAnimationData;

        sf::Vector2i currStart(0, 0);
        for (int i = 0; i < PLAYER_WALK_FRAMES; i++) {
            playerAnimationData.m_data[Direction::Left].emplace_back(currStart, walkSize);
            currStart.x += walkSize.x;
          
        }

        currStart = {0, walkSize.y};
        for (int i = 0; i < PLAYER_WALK_FRAMES; i++) {
            playerAnimationData.m_data[Direction::Right].emplace_back(currStart, walkSize);
            currStart.x += walkSize.x;
        }


        playerAnimationData.m_data[Direction::SwimLeft].emplace_back(sf::IntRect({0,184}, {92,73}));
        playerAnimationData.m_data[Direction::SwimLeft].emplace_back(sf::IntRect({92,184}, {92,60}));
        playerAnimationData.m_data[Direction::SwimLeft].emplace_back(sf::IntRect({ 0,184 }, { 92,73 }));
        playerAnimationData.m_data[Direction::SwimLeft].emplace_back(sf::IntRect({ 92,184 }, { 92,60 }));

        playerAnimationData.m_data[Direction::SwimRight].emplace_back(sf::IntRect({0,276}, {92,73}));
        playerAnimationData.m_data[Direction::SwimRight].emplace_back(sf::IntRect({92,276}, {92,60}));
        playerAnimationData.m_data[Direction::SwimRight].emplace_back(sf::IntRect({ 0,276 }, { 92,73 }));
        playerAnimationData.m_data[Direction::SwimRight].emplace_back(sf::IntRect({ 92,276 }, { 92,60 }));


        return playerAnimationData;
    }

    AnimationData orangeData()
    {
        sf::Vector2i size(95, 67);
        sf::Vector2i space(0, 28);

        AnimationData orangeAnimationData;

        sf::Vector2i currStart(0, 0);
        for (int i = 0; i < ORANGE_WALK_FRAMES; i++) {
            orangeAnimationData.m_data[Direction::Left].emplace_back(currStart, size);
            currStart.x += size.x;
        }

        currStart = { 0, size.y + space.y };
        for (int i = 0; i < ORANGE_WALK_FRAMES; i++) {
            orangeAnimationData.m_data[Direction::Right].emplace_back(currStart, size);
            currStart.x += size.x;
        }

        return orangeAnimationData;
    }

    AnimationData rollingEnemyData()
    {
        sf::Vector2i size(95, 85);
        sf::Vector2i space(0, 10);

        AnimationData rollingEnemyAnimationData;

        sf::Vector2i currStart(0, 475);
        for (int i = 0; i < ROLLING_ENEMY_FRAMES; i++) {
            rollingEnemyAnimationData.m_data[Direction::Left].emplace_back(currStart, size);
            currStart.x += size.x;
        }

        currStart = { 0, 475 + space.y + size.y };
        for (int i = 0; i < ROLLING_ENEMY_FRAMES; i++) {
            rollingEnemyAnimationData.m_data[Direction::Right].emplace_back(currStart, size);
            currStart.x += size.x;
        }

        return rollingEnemyAnimationData;
    }

    AnimationData jellyfishData()
    {
        sf::Vector2i size(67, 67);

        AnimationData jellyfishAnimationData;

        sf::Vector2i currStart(0, 201);
        for (int i = 0; i < JELLYFISH_FRAMES; i++) {
            jellyfishAnimationData.m_data[Direction::Left].emplace_back(currStart, size);
            jellyfishAnimationData.m_data[Direction::Right].emplace_back(currStart, size);
            currStart.x += size.x;
        }


        return jellyfishAnimationData;
    }

    AnimationData flyingMonsterData()
    {
        sf::Vector2i size(102, 67);
        sf::Vector2i space(0, 0);

        AnimationData flyingMonsterAnimation;

        sf::Vector2i currStart(0, 268);
        for (int i = 0; i < FLYING_MONSTER_FRAMES; i++) {
            flyingMonsterAnimation.m_data[Direction::Left].emplace_back(currStart, size);
            currStart.x += size.x;
        }

        currStart = { 0, 335 };
        for (int i = 0; i < FLYING_MONSTER_FRAMES; i++) {
            flyingMonsterAnimation.m_data[Direction::Right].emplace_back(currStart, size);
            currStart.x += size.x;
        }

        return flyingMonsterAnimation;
    }

    AnimationData coinData()
    {
        sf::Vector2i size(48, 48);
        sf::Vector2i space(0, 0);

        AnimationData coinAnimationData;

        sf::Vector2i currStart(0, 1008);
        for (int i = 0; i < COIN_FRAMES; i++) {
            coinAnimationData.m_data[Direction::Stay].emplace_back(currStart, size);
            currStart.x += size.x;
        }

        return coinAnimationData;
    }

    AnimationData springBoardData()
    {
        sf::Vector2i size(48, 48);

        AnimationData springBoardAnimationData;

        sf::Vector2i currStart(0 , 48*14);

        for (int i = 0; i < SPRING_BOARD_FRAMES; i++) {
            springBoardAnimationData.m_data[Direction::Stay].emplace_back(currStart, size);
            currStart.x += size.x;
            currStart.y += int(0.2 * size.y);
            size.y = int(0.8 * size.y);
        }
        return springBoardAnimationData;
    }

    AnimationData boneData()
    {
        sf::Vector2i size(48, 48);
        sf::Vector2i space(0, 0);

        AnimationData boneAnimationData;

        sf::Vector2i currStart(0, 1056);
        for (int i = 0; i < BONE_FRAMES; i++) {
            boneAnimationData.m_data[Direction::Right].emplace_back(currStart, size);
            currStart.x += size.x;
        }

        return boneAnimationData;
    }

    AnimationData disposeData()
    {
        sf::Vector2i size(48, 48);
        sf::Vector2i space(0, 0);

        AnimationData disposeAnimationData;

        sf::Vector2i currStart(0, 1104);
        for (int i = 0; i < DISPOSE_FRAMES; i++) {
            disposeAnimationData.m_data[Direction::Stay].emplace_back(currStart, size);
            currStart.x += size.x;
        }

        return disposeAnimationData;
    }
}

ResourcesManager::ResourcesManager()
    : m_animations(int(Objects::max))
{ 
	initTextures();
    initTiles();
    initAnimationData();
	initFonts();
	initSounds();
	initMusics(); 
}

//singleton:
ResourcesManager& ResourcesManager::instance()
{
	static ResourcesManager instance; 
	return instance;
}

void ResourcesManager::initTextures()
{
    m_textures[Texture::background].loadFromFile("background.png");
    m_textures[Texture::player].loadFromFile("player.png");
    m_textures[Texture::enemies].loadFromFile("enemies.png");
    m_textures[Texture::tileSet].loadFromFile("tileSet.png");
    m_textures[Texture::menu].loadFromFile("menu.png");
    m_textures[Texture::instructions].loadFromFile("instructions.png");
    m_textures[Texture::levelUp].loadFromFile("levelUp.png");
    m_textures[Texture::lost].loadFromFile("lost.png");
    m_textures[Texture::win].loadFromFile("win.png");
}

void ResourcesManager::initTiles()
{
    const int size = 48;
    const sf::Vector2i tileSize(size, size);

    m_tiles[Tiles::grass] = sf::IntRect({ 1*size, 0 }, tileSize);
    m_tiles[Tiles::grassLeft] = sf::IntRect({ 0, 0 }, tileSize);
    m_tiles[Tiles::grassRight] = sf::IntRect({ 2*size, 0 }, tileSize);
    m_tiles[Tiles::flatGrass] = sf::IntRect({ 6 * size, 0 }, { size,36 });
    m_tiles[Tiles::flatGrassLeft] = sf::IntRect({ 5 * size, 0 }, { size,36 });
    m_tiles[Tiles::flatGrassRight] = sf::IntRect({ 7 * size, 0 }, { size,36 });
    m_tiles[Tiles::stones] = sf::IntRect({ 1*size, 1*size }, tileSize);
    m_tiles[Tiles::stonesLeft] = sf::IntRect({ 0, 1*size }, tileSize);
    m_tiles[Tiles::stonesRight] = sf::IntRect({ 2*size, 1*size }, tileSize);
    m_tiles[Tiles::soil] = sf::IntRect({ 1*size, 2*size }, tileSize);
    m_tiles[Tiles::soilLeft] = sf::IntRect({ 0, 2*size }, tileSize);
    m_tiles[Tiles::soilRight] = sf::IntRect({ 2*size, 2*size }, tileSize);
    m_tiles[Tiles::soilCornerLeft] = sf::IntRect({ 0, 3*size }, tileSize);
    m_tiles[Tiles::soilCornerRight] = sf::IntRect({ 2*size, 3*size }, tileSize);
    m_tiles[Tiles::soilBottom] = sf::IntRect({ 1*size, 3*size }, tileSize);
    m_tiles[Tiles::soilHoles] = sf::IntRect({ 3*size, 3*size }, tileSize);
    m_tiles[Tiles::wood] = sf::IntRect({ 5*size, 2*size }, { size*3, 38 });
    m_tiles[Tiles::silverBrick] = sf::IntRect({ 7*size, 4*size }, tileSize);
    m_tiles[Tiles::goldBrick] = sf::IntRect({ 8*size, 4*size }, tileSize);
    m_tiles[Tiles::redBrick] = sf::IntRect({ 7*size, 5*size }, tileSize);
    m_tiles[Tiles::woodBrick] = sf::IntRect({ 2*size, 9*size }, tileSize);
    m_tiles[Tiles::smallBrick] = sf::IntRect({ 7 * size, 3 * size }, {size,23});
    m_tiles[Tiles::largeBrick] = sf::IntRect({ 5 * size, 4 * size }, { 2*size,2*size });
    m_tiles[Tiles::surpriseBox] = sf::IntRect({ 8*size, 5*size }, tileSize);
    m_tiles[Tiles::water] = sf::IntRect({ 1*size, 11*size }, tileSize);
    m_tiles[Tiles::waterBottom] = sf::IntRect({ 1*size, 12*size }, tileSize);
    m_tiles[Tiles::waterCornerLeft] = sf::IntRect({ 2*size, 12*size }, tileSize);
    m_tiles[Tiles::waterCornerRight] = sf::IntRect({ 0, 12*size }, tileSize);
    m_tiles[Tiles::escalator] = sf::IntRect({ 5*size, 3*size }, {94, 27});
    m_tiles[Tiles::cannon] = sf::IntRect({6*size, 19*size}, {75,73});
    m_tiles[Tiles::bullet] = sf::IntRect({8*size, 19*size}, {48,17});
    m_tiles[Tiles::heart] = sf::IntRect({ 3*size, 19*size }, { size,size });
    m_tiles[Tiles::springBoard] = sf::IntRect({ 0, 14*size }, tileSize);
    m_tiles[Tiles::spike] = sf::IntRect({ 4*size, 15*size }, {78,85});
    m_tiles[Tiles::carnivorous] = sf::IntRect({ 8*size, 15*size }, { 68,2*size });
    m_tiles[Tiles::door] = sf::IntRect({ 0*size, 8*size }, { 2*size,3*size });
    m_tiles[Tiles::play] = sf::IntRect({ 0*size, 24*size }, { 242,83 });
    m_tiles[Tiles::instructions] = sf::IntRect({ 0*size, 26*size }, { 242,83 });
    m_tiles[Tiles::exit] = sf::IntRect({ 0*size, 28*size }, { 242,83 });
    m_tiles[Tiles::back] = sf::IntRect({ 0 * size, 30 * size }, { 242,83 });
    m_tiles[Tiles::bubble] = sf::IntRect({ 6 * size, 24 * size }, { 2 * size, 2 * size });
}

void ResourcesManager::initAnimationData()
{
    m_animations[Objects::player] = playerData();
    m_animations[Objects::orange] = orangeData();
    m_animations[Objects::rollingEnemy] = rollingEnemyData();
    m_animations[Objects::jellyfish] = jellyfishData();
    m_animations[Objects::flyingMonster] = flyingMonsterData();
    m_animations[Objects::coin] = coinData();
    m_animations[Objects::springBoard] = springBoardData();
    m_animations[Objects::bone] = boneData();
    m_animations[Objects::dispose] = disposeData();
}

void ResourcesManager::initFonts()
{
    m_fonts[Font::infoBarFont].loadFromFile("infoBarFont.ttf");
}

void ResourcesManager::initSounds()
{
    m_soundBuffers[Sound::bubble].loadFromFile("bubble.wav");
    m_sounds[Sound::bubble] = sf::Sound(m_soundBuffers[Sound::bubble]);
    m_sounds[Sound::bubble].setVolume(30.f);

    m_soundBuffers[Sound::click].loadFromFile("click.wav");
    m_sounds[Sound::click] = sf::Sound(m_soundBuffers[Sound::click]);
    
    m_soundBuffers[Sound::coin].loadFromFile("coin.wav");
    m_sounds[Sound::coin] = sf::Sound(m_soundBuffers[Sound::coin]);
   
    m_soundBuffers[Sound::enemy].loadFromFile("enemy.wav");
    m_sounds[Sound::enemy] = sf::Sound(m_soundBuffers[Sound::enemy]);
   
    m_soundBuffers[Sound::hit].loadFromFile("hit.wav");
    m_sounds[Sound::hit] = sf::Sound(m_soundBuffers[Sound::hit]);
    m_sounds[Sound::hit].setVolume(20.f);
    
    m_soundBuffers[Sound::hurt].loadFromFile("hurt.wav");
    m_sounds[Sound::hurt] = sf::Sound(m_soundBuffers[Sound::hurt]);
   
    m_soundBuffers[Sound::jumpIntoWater].loadFromFile("jumpIntoWater.wav");
    m_sounds[Sound::jumpIntoWater] = sf::Sound(m_soundBuffers[Sound::jumpIntoWater]);
   
    m_soundBuffers[Sound::levelUp].loadFromFile("levelUp.wav");
    m_sounds[Sound::levelUp] = sf::Sound(m_soundBuffers[Sound::levelUp]);
    
    m_soundBuffers[Sound::lose].loadFromFile("lose.wav");
    m_sounds[Sound::lose] = sf::Sound(m_soundBuffers[Sound::lose]);
   
    m_soundBuffers[Sound::shoot].loadFromFile("shoot.wav");
    m_sounds[Sound::shoot] = sf::Sound(m_soundBuffers[Sound::shoot]);
   
    m_soundBuffers[Sound::springBoard].loadFromFile("springBoard.wav");
    m_sounds[Sound::springBoard] = sf::Sound(m_soundBuffers[Sound::springBoard]);
    
    m_soundBuffers[Sound::surpriseBox].loadFromFile("surpriseBox.wav");
    m_sounds[Sound::surpriseBox] = sf::Sound(m_soundBuffers[Sound::surpriseBox]);
    
    m_soundBuffers[Sound::water].loadFromFile("water.wav");
    m_sounds[Sound::water] = sf::Sound(m_soundBuffers[Sound::water]);
    m_sounds[Sound::water].setVolume(35.f);
   
    m_soundBuffers[Sound::win].loadFromFile("win.wav");
    m_sounds[Sound::win] = sf::Sound(m_soundBuffers[Sound::win]);
    
}

void ResourcesManager::initMusics()
{
	m_menuMusic.openFromFile("menuMusic.wav");
	m_menuMusic.setLoop(true);

	m_gameMusic.openFromFile("gameMusic.wav");
	m_gameMusic.setLoop(true);
}

void ResourcesManager::playMenuMusic()
{
    m_menuMusic.play();
}

void ResourcesManager::playGameMusic()
{
    m_gameMusic.play();
}

void ResourcesManager::stopMenuMusic()
{
    m_menuMusic.stop();
}

void ResourcesManager::stopGameMusic()
{
    m_gameMusic.stop();
}

const sf::Texture& ResourcesManager::getTexture(Texture id) const
{
    return m_textures.at(id);
}

const sf::IntRect& ResourcesManager::getTileRect(Tiles id) const
{
    return m_tiles.at(id); //animation frame
}

const AnimationData& ResourcesManager::getAnimationData(Objects object)
{
    return m_animations[object];
}

const sf::Font& ResourcesManager::getFont(Font id) const
{
    return m_fonts.at(id);
}

void ResourcesManager::playSound(Sound id)
{
    m_sounds[id].play();
}

void ResourcesManager::pauseSound(Sound id)
{
    m_sounds[id].pause();
}