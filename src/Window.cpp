#include "Window.h"

std::ostream& operator<<(std::ostream& os, const Vec2& v){
    os << '(' << v.x << ", " << v.y << ')';
    return os;
}

using namespace ShooterTrainer;

Window::Window(){

}
Window::~Window(){
    destroy();    
}
bool Window::init(WindowSettings setSettings){

    // Set appropriate settings
    settings = setSettings;
    SDL_WindowFlags flags { 0 };
    if(settings.fullscreen)
        flags |= SDL_WINDOW_FULLSCREEN;
    if(settings.resizable)
        flags |= SDL_WINDOW_RESIZABLE;
    if(!settings.title)
        settings.title = "NULL";

    if(!SDL_CreateWindowAndRenderer(settings.title, (int)settings.size.x, (int)settings.size.y, flags, &window, &renderer))
        return false; 

    if(!SDL_SetRenderLogicalPresentation(renderer, settings.aspectRatio.logicalSize.x, settings.aspectRatio.logicalSize.y, SDL_LOGICAL_PRESENTATION_LETTERBOX))
        return false;

    initialized = true;

    return initialized;
}
bool Window::isInit() const {
    return initialized;
}
void Window::destroy() {
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;

    SDL_DestroyWindow(window);
    window = nullptr;
}
const WindowSettings& Window::getSettings() const {
    return settings;
}
void Window::setSettings(const WindowSettings& setSettings){
    settings = setSettings;
}
SDL_Renderer* Window::getRenderer() const{
    return renderer;
}

RangeSession::RangeSession() {

}
RangeSession::~RangeSession() {

}
bool RangeSession::init(WindowPtr setWindow) {
    if(!setWindow){
        WindowSettings settings { "Range Session", false, true, Vec2{800, 640}, ASPECT_RATIOS[1] };

        window = std::make_shared<Window>(Window{ });
        return window->init(settings);
    }
    
    if(setWindow->isInit()){
        window = setWindow;
        return true;
    }
    else
        return false;
}
void RangeSession::run(){
    if(!window)
        throw std::runtime_error("Must initialize before running");

    // For testing
    SDL_Renderer* renderer = window->getRenderer();


    Texture USPSA;
    USPSA.load("bin/USPSA.png", renderer);
    // End test texture stuff


    // REAL CODE
    bool quit { false };

    SDL_Event e;
    SDL_zero(e);

    while(!quit){
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_EVENT_QUIT)
                quit = true;
            else if(e.type == SDL_EVENT_KEY_DOWN){
				if(e.key.key == SDLK_UP){
                    static int cur { 0 };
                    ++cur;
                    if(cur == 4)
                        cur = 0;
                    
                    WindowSettings setBuf { window->getSettings() };
                    setBuf.aspectRatio = ASPECT_RATIOS[cur];
                    window->setSettings(setBuf);
                    SDL_SetRenderLogicalPresentation(renderer, setBuf.aspectRatio.logicalSize.x, setBuf.aspectRatio.logicalSize.y, SDL_LOGICAL_PRESENTATION_LETTERBOX);
                }
        }
                
        //Fill the background 
        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( renderer );

        USPSA.render(renderer, {50, 100});
       
        // Update renderer
        SDL_RenderPresent(renderer);
        }
    }
}

Texture::Texture(){

}
Texture::~Texture(){

};
int Texture::load(const std::string& path, SDL_Renderer* renderer){
    destroy(); // Cleans texture if already in use
       
    SDL_Surface* loadedSurface { nullptr };
    loadedSurface = IMG_Load(path.c_str());

    if(!loadedSurface){
        SDL_DestroySurface(loadedSurface);
        return 1;
    }

    // Sets the color key to (255, 0, 255) to be transparent
    if(!SDL_SetSurfaceColorKey(loadedSurface, true, SDL_MapSurfaceRGB(loadedSurface, 0xFF, 0x00, 0xFF))){
        SDL_DestroySurface(loadedSurface);
        return 2;
    }

    texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if(!texture){
       SDL_DestroySurface(loadedSurface);
       return 3;
    }

    originalSize = { (float)loadedSurface->w, (float)loadedSurface->h };
    center = { originalSize.x / 2, originalSize.y / 2};

    SDL_DestroySurface(loadedSurface); // Cleanup local variable

    return 0;
}
void Texture::destroy(){
    SDL_DestroyTexture(texture);
    texture = nullptr;
    originalSize = { 0, 0 };
}
void Texture::render(SDL_Renderer* renderer, Vec2 pos, SDL_FRect* clip, Vec2 clipSize){
    SDL_FRect dstRect = { pos.x - center.x, pos.y - center.y, originalSize.x, originalSize.y };  // Set texture position to be center of the image

    if(clip){
        dstRect.w = clip->w;
        dstRect.h = clip->h;
    }

    // Resize if new dimensions are given
    if(clipSize.x > 0)
        dstRect.w = clipSize.x;
    if(clipSize.y > 0)
        dstRect.h = clipSize.y;

    SDL_RenderTexture(renderer, texture, clip, &dstRect);
}
