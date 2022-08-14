#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Utils.hpp"

int main(int argc,char* args[])
{
	
	if(SDL_Init(SDL_INIT_VIDEO)>0)
		std::cout<<"SDL_Init has Failed. SDL_Error : "<<SDL_GetError() << std::endl;
	if(!(IMG_Init(IMG_INIT_PNG)))
		std::cout<<"IMG_Init has Failed. Error : "<<SDL_GetError() << std::endl;

	RenderWindow window("Kingdom RPG v1.0",1280,720);
	std::cout<< window.getRefreshRate()<<std::endl;

	SDL_Texture* grassTexture = window.loadTexture("res/gfx/ground_grass_1.png");
	SDL_Texture* palmtree = window.loadTexture("res/gfx/pixil-frame-0.png");
	std::vector<Entity>entitiees= {Entity(Vector2f(0,150),grassTexture),
						Entity(Vector2f(60,150),grassTexture),
						Entity(Vector2f(90,150),grassTexture),
						Entity(Vector2f(30,150),palmtree),
						Entity(Vector2f(120,150),grassTexture),
						Entity(Vector2f(150,150),grassTexture),
						Entity(Vector2f(180,150),grassTexture),
						Entity(Vector2f(210,150),grassTexture),
						Entity(Vector2f(240,150),grassTexture),
						Entity(Vector2f(270,150),grassTexture)};;
{						
	Entity divy(Vector2f(300,150),grassTexture);
	entitiees.push_back(divy);
}
	bool gamerunning=true;

	SDL_Event event;
	const float timeStep = 0.01f;
	float accumulator =0.0f;
	float currentTime = utils::hireTimeInSeconds();

	while(gamerunning)
	{
		int startTicks =SDL_GetTicks();

		float newTime =utils::hireTimeInSeconds();
		float frameTime = newTime -currentTime;

		if(frameTime>0.25f)
			frameTime=0.25f;

		currentTime = newTime;

		accumulator += frameTime;

		while(accumulator>=timeStep)
		{
			while(SDL_PollEvent(&event))
			{
			if(event.type==SDL_QUIT)
				gamerunning=false;
			}
			accumulator-=timeStep;
		}

		const float alpha = accumulator / timeStep;//50%?
		window.clear();

		for (Entity& e :entitiees){
			window.render(e);
		}
		
		

		window.display();
		int frameTicks = SDL_GetTicks() -startTicks;
		if(frameTicks<1000/window.getRefreshRate())
			SDL_Delay(1000/ window.getRefreshRate() -frameTicks);
		}
	window.cleanUp();
	SDL_Quit();

	return 0;

}