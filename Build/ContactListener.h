#pragma once
#include <box2d/box2d.h>
#include <map>
#include <memory>
#include "Pig.h"
#include "Bird.h"
#include "DynamicObject.h"

class ContactListener : public b2ContactListener{
private:
	std::multimap<std::string, std::shared_ptr<DynamicObject>>& gameObjects;
public:
	ContactListener(std::multimap<std::string, std::shared_ptr<DynamicObject>>& gameObjects);
	void BeginContact(b2Contact* contact) override;
};

