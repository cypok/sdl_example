#include <assert.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_gfxPrimitives.h>

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480
#define BPP 32

#define TITLE_X 30
#define TITLE_Y 10

#define FIELD_PADDING 30
#define BORDER_WIDTH 10
#define POINT_RADIUS 20

#define POINT_SPEED 3

#define COLOR_BORDER 0x0000FFFF
#define COLOR_FIELD  0x00FF00FF
#define COLOR_POINT  0xFF0000FF

static int field_x, field_y; // top-left corner
static int field_width, field_height;
static int point_x, point_y;


static void checkSDLResult(int result) {
    if (!result) {
        fprintf(stderr, "Error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

static SDL_Surface *createSurface() {
    SDL_Surface *screen;

    checkSDLResult(SDL_Init(SDL_INIT_VIDEO) == 0);
    atexit(SDL_Quit);

    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, BPP, SDL_HWSURFACE);
    checkSDLResult(screen != 0);

    checkSDLResult(SDL_EnableKeyRepeat(100, SDL_DEFAULT_REPEAT_INTERVAL) == 0);

    return screen;
}

static void initialDraw(SDL_Surface *screen) {
    // fill all screen with white color
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));

    stringColor(screen, TITLE_X, TITLE_Y, "Use arrows to move point, use Esc to exit.", 0x000000ff);

    // drawing border
    // 1---2
    // |   |
    // 3---4
    // 1-2
    boxColor(screen, field_x, field_y,
            field_x + field_width - 1, field_y + BORDER_WIDTH - 1,
            COLOR_BORDER);
    // 1-3
    boxColor(screen, field_x, field_y,
            field_x + BORDER_WIDTH - 1, field_y + field_height - 1,
            COLOR_BORDER);
    // 4-2
    boxColor(screen, field_x + field_width - 1, field_y + field_height - 1,
            field_x + field_width - BORDER_WIDTH - 1, field_y,
            COLOR_BORDER);
    // 4-3
    boxColor(screen, field_x + field_width - 1, field_y + field_height - 1,
            field_x, field_y + field_height - BORDER_WIDTH - 1,
            COLOR_BORDER);

    // draw field
    boxColor(screen, field_x + BORDER_WIDTH, field_y + BORDER_WIDTH,
            field_x + field_width - BORDER_WIDTH - 1, field_y + field_height - BORDER_WIDTH - 1,
            COLOR_FIELD);

    point_x = field_x + field_width/2;
    point_y = field_y + field_height/2;

    filledCircleColor(screen, point_x, point_y, POINT_RADIUS, COLOR_POINT);
}

/* Returns 1 if quit. */
static int processKey(SDL_Surface *screen, int key) {
    // position change
    int dx = 0;
    int dy = 0;

    switch (key) {
        case SDLK_ESCAPE:
            return 1;

        case SDLK_UP:
            if (point_y - POINT_RADIUS - BORDER_WIDTH > field_y) {
                dy = -1;
            }
            break;
        case SDLK_DOWN:
            if (point_y + POINT_RADIUS + BORDER_WIDTH < field_y + field_height - 1) {
                dy = 1;
            }
            break;
        case SDLK_LEFT:
            if (point_x - POINT_RADIUS - BORDER_WIDTH > field_x) {
                dx = -1;
            }
            break;
        case SDLK_RIGHT:
            if (point_x + POINT_RADIUS + BORDER_WIDTH < field_x + field_width - 1) {
                dx = 1;
            }
            break;
    }

    if (dx != 0 || dy != 0) {
        filledCircleColor(screen, point_x, point_y, POINT_RADIUS, COLOR_FIELD);
        point_x += dx*POINT_SPEED;
        point_y += dy*POINT_SPEED;
        filledCircleColor(screen, point_x, point_y, POINT_RADIUS, COLOR_POINT);
    }
    return 0;
}

int main() {
    int quit;
    SDL_Surface *screen = createSurface();

    // calculate size of field and other initializations
    field_x = FIELD_PADDING;
    field_y = FIELD_PADDING + TITLE_Y + 10; // 10 is approximation of title height
    field_width = SCREEN_WIDTH - field_x - FIELD_PADDING;
    field_height = SCREEN_HEIGHT - field_y - FIELD_PADDING;

    initialDraw(screen);

    quit = 0;
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = 1;
                    break;

                case SDL_KEYDOWN:
                    if (processKey(screen, event.key.keysym.sym)) {
                        quit = 1;
                    }
                    break;
            }
        }

        SDL_Flip(screen);
        SDL_Delay(33); // ~ 60 fps
    }

    return 0;
}

