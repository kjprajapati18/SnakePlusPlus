#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;

using ComponentID = std::size_t;
static ComponentID lastID = 0;

inline ComponentID getComponentTypeID() {
	return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept {
	static_assert(std::is_base_of<Component, T>::value, "");
	static ComponentID typeID = getComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, 32>;

class Component {

public:
	Entity* entity = nullptr;

	virtual void init() {}
	virtual void update() {}
	virtual void draw(){}

	virtual ~Component(){}
};

class Entity {
private:
	bool active = true;
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;

public:
	void update() {
		for (auto& c : components) c->update();
	}
	void draw() {
		for (auto& c : components) c->draw();
	}

	bool isActive() const { return active; }

	void destroy() { active = false; }

	template <typename T> bool hasComponent() const {
		return componentBitSet[getComponentTypeID<T>()];
	}

	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs) {
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));

		componentArray[getComponentTypeID<T>()] = c;
		componentBitSet[getComponentTypeID<T>()] = true;

		c->init();
		return *c;
	}

	template <typename T> T& getComponent() const {
		//auto ptr(componentArray[getComponentTypeID<T>()]);
		//return *static_cast<T*>(ptr);
		auto ptr = componentArray.at(getComponentTypeID<T>());
		return *static_cast<T*>(ptr);
	}
};


class Manager {
private:
	std::vector<std::unique_ptr<Entity>> entities;
	friend class StateHandler;

public:
	void update() {
		for (auto& e : entities) e->update();
	}
	void draw() {
		for (auto& e : entities) e->draw();
	}

	void refresh() {
		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity>& mEntity)
			{
				return !mEntity->isActive();
			}),
			std::end(entities));
	}

	void clean() {
		entities.clear();
	}

	std::vector<std::unique_ptr<Entity>>& getEntities() {
		return entities;
	}

	Entity& addEntity() {
		Entity* e = new Entity();
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));
		return *e;
	}

};
