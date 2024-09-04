#include <string>
#include "world.h"

class Scene
{
public:
	std::string name;
	World world;
	Scene(std::string name);
};