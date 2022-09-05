#pragma once
#include <iostream>
#include <memory>
#include <map>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

template<typename T>
class Factory {
public:
	using pFnc = std::unique_ptr<T>(*)(); //the function that creates the object
	static std::unique_ptr<T> create(const std::string& name);
	static bool registerit(const std::string& name, pFnc);
private:
	static auto& getMap() {
		static std::map<std::string, pFnc> map;
		return map;
	}
};

//creates the objects according to the char that represents it
//(searches this char in the map):
template<typename T>
std::unique_ptr<T> Factory<T>::create(const std::string& name) {
	auto it = Factory::getMap().find(name);
	if (it == Factory::getMap().end())
		return nullptr;
	return it->second();
}


//register a pair of char+creator function into the map:
template<typename T>
bool Factory<T>::registerit(const std::string& name, pFnc f) {
	Factory::getMap().emplace(name, f);
	return true;
}

