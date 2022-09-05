# Eric's Mandelbrot Set Renderer 

Realtime interactive Mandelbrot Set renderer.

### Building
Make sure SDL2 is installed. Then run `make` in the project root. The binary will be located in the `bin` folder.

### Controls
- `W` and `S`: Zoom in and out
- Arrow keys: Move around

### Command Line Options
**-h** *height*<br>
&nbsp;&nbsp;&nbsp;&nbsp;Set height of window. Defaults to `300`.

**-w** *width*<br>
&nbsp;&nbsp;&nbsp;&nbsp;Set width of window. Defaults to `400`.

**-i** *iterations*<br>
&nbsp;&nbsp;&nbsp;&nbsp;Set maximum iterations to process when evaluating a point. Defaults to `500`.

**-t** *threads*<br>
&nbsp;&nbsp;&nbsp;&nbsp;Set number of threads to use. Defaults to the return value of `std::thread::hardware_concurrency()`.

### Notes
Floating point precision will prevent resolution from increasing once magnified past a certain point.
