#include "Board.h"
#include "Controller.h"
#include "MovingObjects/MovingObject.h"
#include "StaticObjects/SpringBoard.h"
#include "macros.h"
#include "Factory.h"
#include <string>
#include <sstream>


Board::Board(Controller& controller)
	: m_rows(0), m_cols(0),
	m_controller(controller)
{
}


void Board::readLevelFromFile(int levelNum)
{
	//clear the former level data:
	m_staticObjects.clear();

	std::string fileName = "Level" + std::to_string(levelNum) + ".txt";
	m_file.open(fileName);

	std::string line;
	std::getline(m_file, line);
	std::istringstream stringStream(line);
	stringStream >> m_rows >> m_cols; //read the level's dimensions

	char c;
	for (int row = 0; row < m_rows; row++) {
		for (int col = 0; col < m_cols; col++) {
			c = char(m_file.get());
			//create the objects according to the map in factory:
			//if nullptr returned it means that its symbol is not registered in the 
			//certain factory.
			auto staticObject = Factory<StaticObject>::create(std::string(1, c));
			auto movingObject = Factory<MovingObject>::create(std::string(1, c));
			if (staticObject) {
				staticObject->setPosition({ col * TILE_SIZE, row * TILE_SIZE });
				m_staticObjects.push_back(std::move(staticObject));
			}
			if (movingObject) {
				movingObject->setPosition({ col * TILE_SIZE, row * TILE_SIZE });
				m_controller.addMovingObject(std::move(movingObject));
			}
		}
		if (row != m_rows - 1) { //(don't read '\n' after last line)
			m_file.get(); //read '\n'
		}
	}

	m_file.close();
}


int Board::getNumOfStaticObjects() const
{
	return int(m_staticObjects.size());
}

StaticObject& Board::getStaticObject(int i) const
{
	return *m_staticObjects[i];
}

void Board::addStaticObject(std::unique_ptr<StaticObject> staticObject)
{
	m_staticObjects.push_back(std::move(staticObject));
}

void Board::update(sf::Time delta)
{
	for (auto& staticObject : m_staticObjects) {
		staticObject->update(delta, *this);
	}

	//erase disposed static objects:
	std::erase_if(m_staticObjects, [](const auto& staticObject) {
		return staticObject->dispose();
		});
}

void Board::draw(sf::RenderWindow& window) const
{
	for (auto& staticObject : m_staticObjects) {
		staticObject->draw(window);
	}
}
