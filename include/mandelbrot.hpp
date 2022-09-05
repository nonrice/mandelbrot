#include <vector>

int get_pixel(long double x, long double y, int iterations);

void get_pixel_range(int start, int end, std::vector<int>& pixels, int w, int h, long double zoom, long double vx, long double vy, int iterations);

void get_pixel_all_concurrent(std::vector<int>& pixels, int w, int h, long double zoom, long double vx, long double vy, int iterations, int thread_c);
