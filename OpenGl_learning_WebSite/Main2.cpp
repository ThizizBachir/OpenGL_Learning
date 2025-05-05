#include "Engine.h"

int main() {

	Engine::getInstance()->Init();


	while (!Engine::getInstance()->Closed())

	{
	   
		Engine::getInstance()->loop();

	}

	Engine::getInstance()->Shutdown();

	return 0;
}								    