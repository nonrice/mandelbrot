#include <thread>
#include <vector>

int get_pixel(long double x, long double y, int iterations){
    long double cx=x, cy=y;
    for (int it=0; it<iterations; ++it){
        if (cx*cx + cy*cy > 4) return it;
        long double tx=cx;
        cx = cx*cx - cy*cy + x;
        cy = 2*tx*cy + y;
    }
    return iterations;
}

void get_pixel_range(int start, int end, std::vector<int>& pixels, int w, int h, long double zoom, long double vx, long double vy, int iterations){
    for (int i=start; i<end; ++i){
        pixels[i] = get_pixel((i%(int)w-w/2)/zoom + vx, (i/(int)w-h/2)/zoom + vy, iterations);
    }
}

void get_pixel_all_concurrent(std::vector<int>& pixels, int w, int h, long double zoom, long double vx, long double vy, int iterations, int thread_c){
    std::vector<std::thread> threads;
    int range_size = w*h / thread_c;
    for (int i=0; i<thread_c; ++i){
        threads.emplace_back(get_pixel_range, i*range_size, (i == thread_c-1) ? w*h : (i+1)*range_size, std::ref(pixels), w, h, zoom, vx, vy, iterations);
    }

    for (std::thread& t : threads) if (t.joinable()) t.join();
}
