#pragma once
#include "StaticObjects/StaticObject.h"
#include "ResourcesManager.h"
#include <vector>
#include <fstream>
#include <memory>
class Controller;

class Board {
public:
	Board(Controller& controller);
	void readLevelFromFile(int levelNum);
	void draw(sf::RenderWindow& window) const;
	void update(sf::Time delta);
	int getNumOfStaticObjects() const;
	StaticObject& getStaticObject(int i) const; 
	void addStaticObject(std::unique_ptr<StaticObject> staticObject);

private:
	Controller& m_controller;
	std::ifstream m_file;
	int m_rows, m_cols;
	std::vector<std::unique_ptr<StaticObject>> m_staticObjects;
};