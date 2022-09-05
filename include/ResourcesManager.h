#pragma once
#include "AnimationData.h"
#include <vector>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

enum class Texture {
	background,
	player,
	enemies,
	tileSet,
	menu,
	instructions,
	levelUp,
	lost,
	win
};

enum class Tiles {
	grass,
	grassLeft,
	grassRight,
	flatGrass,
	flatGrassLeft,
	flatGrassRight,
	stones,
	stonesLeft,
	stonesRight,
	soil,
	soilLeft,
	soilRight,
	soilCornerLeft,
	soilCornerRight,
	soilBottom,
	soilHoles,
	wood,
	silverBrick,
	goldBrick,
	redBrick,
	woodBrick,
	smallBrick,
	largeBrick,
	surpriseBox,
	water,
	waterBottom,
	waterCornerLeft,
	waterCornerRight,
	escalator,
	cannon, 
	bullet,
	heart,
	springBoard,
	spike,
	carnivorous,
	door,
	bubble,
	play,
	instructions,
	exit,
	back,
};

enum class Font {
	infoBarFont
};

enum class Sound {
	menuMusic,
	gameMusic,
	bubble,
	click,
	coin,
	enemy,
	hit,
	hurt,
	jumpIntoWater,
	levelUp,
	lose,
	shoot,
	springBoard,
	surpriseBox,
	water,
	win
};

enum class Objects  //Animation objects
{
	player,
	orange,
	rollingEnemy,
	flyingMonster,
	escalator,
	coin,
	springBoard,
	bone,
	jellyfish,
	dispose,
	max,
};


class ResourcesManager {
public:
	~ResourcesManager() = default;
	static ResourcesManager& instance();

	const sf::Texture& getTexture(Texture id) const;
	const sf::IntRect& getTileRect(Tiles id) const;
	const AnimationData& getAnimationData(Objects object); ///const
	const sf::Font& getFont(Font id) const;
	void playSound(Sound id);
	void pauseSound(Sound id);
	void playMenuMusic();
	void playGameMusic();
	void stopMenuMusic();
	void stopGameMusic();
private:
	ResourcesManager();
	ResourcesManager(const ResourcesManager&) = default;
	ResourcesManager& operator=(const ResourcesManager&) = default;

	void initTextures();
	void initTiles();
	void initAnimationData();
	void initFonts();
	void initSounds();
	void initMusics();

	std::unordered_map<Texture, sf::Texture> m_textures;
	std::unordered_map<Tiles, sf::IntRect> m_tiles;
	std::unordered_map<Objects, AnimationData> m_animations;
	std::unordered_map<Font ,sf::Font> m_fonts;
	std::unordered_map<Sound ,sf::SoundBuffer> m_soundBuffers;
	std::unordered_map<Sound ,sf::Sound> m_sounds;
	sf::Music m_menuMusic;
	sf::Music m_gameMusic;
};