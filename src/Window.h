#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>

#include <stdexcept>
#include <string>
#include <memory>

#include <iostream>

struct Vec2 {
    float x { 0.f };
    float y { 0.f };
}; 

std::ostream& operator<<(std::ostream& os, const Vec2& v);

namespace ShooterTrainer{

    struct AspectRatio {
        Vec2 scale { 0, 0 };
        Vec2 logicalSize { 0, 0 };
    };

    static constexpr AspectRatio ASPECT_RATIOS[] = { 
        { { 4, 3    }, { 1024, 768  } },
        { { 16, 9   }, { 1920, 1080 } },
        { { 16, 10  }, { 1920, 1200 } },
        { { 21, 9   }, { 2560, 1080 } }
    };

    struct WindowSettings {
        const char* title       { nullptr };    // Set window title
        bool        fullscreen  { false };      // Set if window will open in fullscreen mode
        bool        resizable   { true };       // Set if window can be resized
        Vec2        size        { 800, 640 };   // Set first window size
        AspectRatio aspectRatio { ASPECT_RATIOS[1] };
    };
    
    class Window {
    public:
        Window();
        ~Window(); 

        bool init   (WindowSettings setSettings);
        bool isInit () const;

        void destroy ();

        const WindowSettings&   getSettings() const;
        void                    setSettings(const WindowSettings& setSettings);
        
        SDL_Renderer* getRenderer() const;
    private:
        bool            initialized { false };

        WindowSettings  settings    { };
        SDL_Window*     window      {nullptr};
        SDL_Renderer*   renderer    {nullptr};
    };

    using WindowPtr = std::shared_ptr<Window>;

   
    class RangeSession {
    public:
        RangeSession();
        ~RangeSession();

        bool init(WindowPtr setWindow=nullptr); // Must be an already initialized window if giving one
        void run(); // Throw runtime error if called before initializing

    private:
        WindowPtr window;
    };

    class Texture {
    public:
        Texture();
        ~Texture();

        int load(const std::string& path, SDL_Renderer* renderer);          // Return 1: Unable to load image. 2: Unable to color key. 3: Unable to create texture
        
        void render(SDL_Renderer* renderer, Vec2 pos, SDL_FRect* clip=nullptr, Vec2 clipSize={-1, -1});

        void destroy();
    private:
        SDL_Texture*    texture         { nullptr };
        Vec2            originalSize    { 0, 0 };
        Vec2            center          { 0, 0 };
    };
}
