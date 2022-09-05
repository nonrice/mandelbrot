# Eric's Mandelbrot Set Renderer 

Realtime Mandelbrot Set renderer.

### Building
Make sure SDL2 is installed. Then run `make` in the project root. The binary will be located in the `bin` folder.

### Controls
- `W` and `S`: Zoom in and out
- Arrow keys: Move around

### Notes
Calculating the image at a fast refresh rate is very computationally expensive, so framerate drops are almost guaranteed to appear.

Floating point precision will prevent resolution from increasing once magnified past a certain point.

