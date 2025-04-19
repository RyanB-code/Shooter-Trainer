#include <iostream>
#include <memory>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>

// constants
constexpr int kScreenWidth  { 640 };
constexpr int kScreenHeight     { 800 }; 

class LTexture;

bool init();
bool loadMedia();
void close();

SDL_Renderer*   gRenderer   { nullptr };
SDL_Window*     gWindow     { nullptr };


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

    static constexpr float kOriginalSize { -1.f };

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

        // Sets the color key to CYAN (0, 255, 255) to be transparent
        if(!SDL_SetSurfaceColorKey(loadedSurface, true, SDL_MapSurfaceRGB(loadedSurface, 0x00, 0xFF, 0xFF))){
            SDL_Log("Unable to color key. SDL Error: %s\n", SDL_GetError());
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
        void render( float x, float y, SDL_FRect* clip=nullptr, float width=kOriginalSize, float height=kOriginalSize){
        // Set texture position
        SDL_FRect dstRect = {x, y, static_cast<float>(mWidth), static_cast<float>(mHeight)};

        if(clip){
            dstRect.w = clip->w;
            dstRect.h = clip->h;
        }

        // Resize if new dimensions are given
        if(width > 0)
            dstRect.w = width;
        if(height > 0)
            dstRect.h = height;

        SDL_RenderTexture(gRenderer, mTexture, clip, &dstRect); // Render it
    }

        //Gets texture dimensions
        int getWidth()  { return mWidth; };
        int getHeight() { return mHeight; };

private:
        //Contains texture data
        SDL_Texture* mTexture;

        //Texture dimensions
        int mWidth;
        int mHeight;
};


LTexture gSpriteSheetTexture;

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
                
        //Fill the background 
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );


        // Sprite clip is what separates the PNG with all the dots
        // Coordinate system is TOP LEFT (0, 0), and each clip makes a new rect with the image cutout

        // init sprite clip
        constexpr float kSpriteSize { 100.f };
        SDL_FRect spriteClip { 0.f, 0.f, kSpriteSize, kSpriteSize };
        SDL_FRect spriteSize { 0.f, 0.f, kSpriteSize, kSpriteSize }; // init sprite size
        
        // Use top left sprite
        spriteClip.x = 0.f;
        spriteClip.y = 0.f;

        // Set sprite size to original size
        spriteSize.w = kSpriteSize;
        spriteSize.h = kSpriteSize;

        // Draw original sized sprite
        gSpriteSheetTexture.render(0.f, 0.f, &spriteClip, spriteSize.w, spriteSize.h);

        


                //Use top right sprite
                spriteClip.x = kSpriteSize;
                spriteClip.y =         0.f;

                //Set sprite to half size
                spriteSize.w = kSpriteSize * 0.5f;
                spriteSize.h = kSpriteSize * 0.5f;

                //Draw half size sprite
                gSpriteSheetTexture.render( kScreenWidth - spriteSize.w, 0.f, &spriteClip, spriteSize.w, spriteSize.h );
        





        //Use bottom left sprite
                spriteClip.x =         0.f;
                spriteClip.y = kSpriteSize;

                //Set sprite to double size
                spriteSize.w = kSpriteSize * 2.f;
                spriteSize.h = kSpriteSize * 2.f;
                
                //Draw double size sprite
                gSpriteSheetTexture.render(0.f, kScreenHeight - spriteSize.h, &spriteClip, spriteSize.w, spriteSize.h );


                //Use bottom right sprite
                spriteClip.x = kSpriteSize;
                spriteClip.y = kSpriteSize;

                //Squish the sprite vertically
                spriteSize.w = kSpriteSize;
                spriteSize.h = kSpriteSize * 0.5f;
                
                //Draw squished sprite
                gSpriteSheetTexture.render( kScreenWidth - spriteSize.w, kScreenHeight - spriteSize.h, &spriteClip, spriteSize.w, spriteSize.h );


                //Update screen
                SDL_RenderPresent( gRenderer );
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

    if(success &= gSpriteSheetTexture.loadFromFile("bin/dots.png"); !success)
        SDL_Log("Unable to load background image\n");

    return success;
}
void close(){
    // Destroy window
    SDL_DestroyRenderer(gRenderer);
    gRenderer = nullptr;
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;

    // Quit subsystems
    //IMG_Quit();
    SDL_Quit();
}


