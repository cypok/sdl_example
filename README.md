# Example of using SDL + SDL\_gfx libraries

This is an example of simple 2D application that draws graphic primitives and
handles keyboard input.

![screenshot](https://github.com/cypok/sdl_example/raw/master/screenshot.png)

### More docs

Documentation for SDL\_gfx graphic primitives (points, circles, rects and etc.)
can be found
[here](http://www.ferzkopp.net/Software/SDL_gfx-2.0/Docs/html/_s_d_l__gfx_primitives_8h.html).

### Build & run on OS X

Install sdl & sdl\_gfx somehow. For example, use [homebrew](http://brew.sh):

    brew install sdl sdl_gfx

And use make to build:

    make && ./example

That's all! :sunglasses:

### Build & run on Linux

:bangbang: TODO :bangbang:

### Build & run on Windows using Visual C

Unzip `SDL-1.2.13_SDL_gfx-2.0.17-devel-win32-vc.zip` to some directory (it's
binary libraries compiled using Visual C).

Create empty Win32 application and add `example.c` to it.

Open Project | Properties | C/C++ | General. Add the following to Additional
Include Directories:

    C:\path\to\SDL-1.2.13\include
    C:\path\to\SDL-1.2.13\SDL_gfx-2.0.17\include

Open Project | Properties | Linker | Input. Add the following to Additional
Dependencies:

    C:\path\to\SDL-1.2.13\lib\SDL.lib
    C:\path\to\SDL-1.2.13\lib\SDLmain.lib
    C:\path\to\SDL-1.2.13\SDL_gfx-2.0.17\lib\SDL_gfx.lib

Copy following files to your project's directory:

    C:\path\to\SDL-1.2.13\lib\SDL.dll
    C:\path\to\SDL-1.2.13\SDL_gfx-2.0.17\lib\SDL_gfx.dll

Now you should be able to run the example.

### Build & run on Windows using something else

:bangbang: TODO :bangbang:

### Feedback

Any feedback is welcome! Open pull request or email to
vladimir.parfinenko@gmail.com.

