#include <iostream>
#include <cmath>
#include <thread>
#include <iomanip>
#include <unistd.h>
#include <cstdlib>

#include <SDL.h>
#include "tinycolormap.hpp"
#include "mandelbrot.hpp"

int main(int argc, char** argv){
    int w=400;
    int h=300;
    int iterations = 500;
    int thread_c = std::thread::hardware_concurrency();
    
    int opt;
    while ((opt = getopt(argc, argv, "w:h:t:i:")) != -1){
        if (optarg == NULL) return 1;

        int arg = std::atoi(optarg);
        if (arg <= 0){
            std::cout << "[init] Invalid value for option \"" << char(opt) << "\"\n";
            return 1;
        }

        if (opt == 'w') w = arg;
        else if (opt == 'h') h = arg;
        else if (opt == 't') thread_c = arg;
        else if (opt == 'i') iterations = arg;

    }
    
    std::cout << "[init] Starting with params: h=" << h << " w=" << w << " iterations=" << iterations << " thread_c=" << thread_c << '\n';
    if (SDL_Init(SDL_INIT_VIDEO) == 0) std::cout << "[init] Successfully initialized SDL\n";
    else {
        std::cout << "[init] Failed to initialize SDL\n";
        return 1;
    }
    SDL_Window* window = SDL_CreateWindow("Mandelbrot", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_OPENGL);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, w, h);
    uint32_t* texture_buf = new uint32_t[w*h];
    std::cout << "[init] Initialization complete\n";

    std::vector<int> pixels(w*h);
    long double vx=-0.7, vy=0;
    long double zoom=w/4;
    uint32_t last = 0;
    bool running = true;
    while (running){
        SDL_Event event;
        while (SDL_PollEvent(&event)) running = (event.type != SDL_QUIT);
        
        uint32_t dt = SDL_GetTicks()-last;
        last += dt;
        std::cout.flush();
        std::cout << std::fixed << std::setprecision(8);
        std::cout << "\33[2K[info] fps: " << 1000/dt << '\n';
        std::cout << "\33[2K[info] zoom: " << zoom << '\n';
        std::cout << "\33[2K[info] pos: " << vx << ", " << vy << "\n";
        std::cout << "\r\033[A\033[A\033[A";

        const double dt_mul = dt/16;
        const Uint8* keys = SDL_GetKeyboardState(NULL);
        if (keys[SDL_SCANCODE_UP]) vy -= 4/zoom * dt_mul;
        if (keys[SDL_SCANCODE_DOWN]) vy += 4/zoom * dt_mul;
        if (keys[SDL_SCANCODE_LEFT]) vx -= 4/zoom * dt_mul;
        if (keys[SDL_SCANCODE_RIGHT]) vx += 4/zoom * dt_mul;
        if (keys[SDL_SCANCODE_W]) zoom *= std::pow(1.01, dt_mul);
        if (keys[SDL_SCANCODE_S]) zoom /= std::pow(1.01, dt_mul);
        
        get_pixel_all_concurrent(pixels, w, h, zoom, vx, vy, iterations, thread_c);
    
        for (int i=0; i<w*h; ++i){
            tinycolormap::Color pix_clr = tinycolormap::GetColor(double(pixels[i])/iterations, tinycolormap::ColormapType::Cubehelix);
            texture_buf[i] = 0xFF000000 | (int(pix_clr.r()*255)<<16) | (int(pix_clr.g()*255)<<8) | int(pix_clr.b()*255);
        }
        SDL_RenderClear(renderer);
        SDL_UpdateTexture(texture, NULL, texture_buf, w * sizeof(uint32_t));
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }
	
    SDL_Quit();
    SDL_DestroyTexture(texture);
    delete[] texture_buf;
    std::cout << "[free] Finished\n";
}
