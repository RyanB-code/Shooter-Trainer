#include <iostream>
#include <memory>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>

// constants
constexpr int kScreenWidth 	{ 640 };
constexpr int kScreenHeight 	{ 800 }; 

class LTexture;

bool init();
bool loadMedia();
void close();

SDL_Renderer* 	gRenderer 	{ nullptr };
SDL_Window* 	gWindow		{ nullptr };


// Class definitions
class LTexture
{
public:
	//Initializes texture variables
 	LTexture(){
		mTexture = nullptr;
		mWidth = 0;
		mHeight = 0;
	}

   	//Cleans up texture variables
	~LTexture(){
		destroy();
	}

    	//Loads texture from disk
    	bool loadFromFile( std::string path ){
		destroy(); // Cleans texture if already in use
		
		SDL_Surface* loadedSurface { nullptr };
		loadedSurface = IMG_Load(path.c_str());

		if(!loadedSurface){
			SDL_Log("Unable to load image %s. SDL Error: %s\n", path.c_str(), SDL_GetError());
			SDL_DestroySurface(loadedSurface);
			return false;
		}


		if(mTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface); mTexture == nullptr){
			SDL_DestroySurface(loadedSurface);
			SDL_Log("Unable to create texture from loaded pixels. SDL_Error %s\n", SDL_GetError());
			return false;
		}

		mWidth = loadedSurface->w;
		mHeight = loadedSurface->h;

		SDL_DestroySurface(loadedSurface); // Cleanup local variable

		return mTexture != nullptr;
	}

  	//Cleans up texture
    	void destroy(){
		SDL_DestroyTexture(mTexture);
		mTexture = nullptr;
		mWidth = 0;
		mHeight = 0;
	}

	//Draws texture
    	void render( float x, float y ){
		// Set texture position
		SDL_FRect dstRect = {x, y, static_cast<float>(mWidth), static_cast<float>(mHeight)};

		SDL_RenderTexture(gRenderer, mTexture, nullptr, &dstRect); // Render it
	}

    	//Gets texture dimensions
    	int getWidth()	{ return mWidth; };
    	int getHeight()	{ return mHeight; };

private:
    	//Contains texture data
    	SDL_Texture* mTexture;

    	//Texture dimensions
    	int mWidth;
    	int mHeight;
};




LTexture 	gPNGTexture;

int main(){

	int exitCode { 0 };

	if(!init()){
		SDL_Log("Unable to initialize program!\n");
		return 1;
	}

	if(!loadMedia()){
		SDL_Log("Unable to load media\n");
		return 2;
	}

	bool quit { false };

	SDL_Event e;
	SDL_zero(e);

	while(!quit){
		while(SDL_PollEvent(&e)){
			if(e.type == SDL_EVENT_QUIT)
				quit = true;
		}

		// fill background white
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);

		gPNGTexture.render(0.f, 0.f); 	// Render image on screen
		SDL_RenderPresent(gRenderer);	// Update screen
	}

	close();
	return exitCode;
}


// Function definitions
bool init(){

	if(!SDL_Init(SDL_INIT_VIDEO)){
		SDL_Log("SDL could not initialize. SDL Error: %s\n", SDL_GetError());
		return false;
	}

	// Create window with renderer
	if(!SDL_CreateWindowAndRenderer("Test Text", kScreenWidth, kScreenHeight, 0, &gWindow, &gRenderer)){
		SDL_Log("Window could not be created. SDL Error %s\n", SDL_GetError());
		return false;
	}

	/*
	// Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if(!(IMG_Init(imgFlags) & imgFlags)){
		SDL_Log("SDL_image could not initialize. SDL_image error: %s\n", SDL_GetError());
		return false;
	}
	*/

	return true;
}
bool loadMedia(){
	bool success { true };
	if(success = gPNGTexture.loadFromFile("bin/thumbnail.png"); !success){
		SDL_Log("Unable to load png image");
	}

	return success;
}
void close(){
	gPNGTexture.destroy();

	// Destroy window
	SDL_DestroyRenderer(gRenderer);
	gRenderer = nullptr;
	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;

	// Quit subsystems
	//IMG_Quit();
	SDL_Quit();
}


