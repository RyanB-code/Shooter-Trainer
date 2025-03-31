#include <iostream>
#include <memory>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

class Window {
public:
	Window(std::string setTitle="Test Window") : title {setTitle} { }
	~Window() { 
		destroy();
	}

	bool init(int height, int width){
		if(!SDL_Init(SDL_INIT_VIDEO) ){
			SDL_Log("SDL could not initialize. SDL Error: %s\n", SDL_GetError());
			return false;
		}
		
		window = SDL_CreateWindow(title.c_str(), width, height, 0);
		
		if(!window){
			SDL_Log("Window could not be created. SDL Error: %s\n", SDL_GetError());
			return false;
		}

		surface = SDL_GetWindowSurface( window );
	
		return true;
	}
	void destroy(){
		SDL_DestroyWindow(window);
		window 	= nullptr;
		surface = nullptr;
	}
	
	SDL_Window* 	getWindowPtr() 	{ return window; };
	SDL_Surface*	getSurfacePtr()	{ return surface; };

private:
	SDL_Window* 	window;
	SDL_Surface*	surface;
	std::string title;
};

int main(){
	std::cout << "Hello, world!\n";
	std::cout << "Test 4\n";

	constexpr int height 	{ 640 };
	constexpr int width	{ 800 };

	Window window;

	if(!window.init(height, width))
		return false;

	SDL_Surface* 	testSurface 	{ nullptr };


	std::string imagePath { "bin/sdl-test_round.bmp" };
	if(testSurface = SDL_LoadBMP(imagePath.c_str()); testSurface == nullptr){
		SDL_Log("Unable to load image. SDL Error: %s\n", SDL_GetError());
		return false;
	}

	// Getting input
	bool quit { false };

	SDL_Event e;
	SDL_zero( e );

	while(quit == false){
		while(SDL_PollEvent(&e)){
			if(e.type == SDL_EVENT_QUIT)
				quit = true;
		}

		SDL_FillSurfaceRect(window.getSurfacePtr(), nullptr, SDL_MapSurfaceRGB(window.getSurfacePtr(), 0xFF, 0xFF, 0xFF) );

		SDL_BlitSurface(testSurface, nullptr, window.getSurfacePtr(), nullptr);

		SDL_UpdateWindowSurface(window.getWindowPtr());
	}

	
	SDL_DestroySurface(testSurface);
	testSurface = nullptr;

	window.destroy();

	SDL_Quit();

	return 0;
}
