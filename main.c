
#include <SDL.h>
#include <stdio.h>

typedef enum {false, true} bool;

void next();
void init_screen();
SDL_Surface* get_digit_srf(int digit);

bool init_sdl();
bool load_media();
void deinit_sdl();

const int SINGLE_IMAGE_WIDTH = 173;
const int SINGLE_IMAGE_HEIGHT = 231;
const int SCREEN_WIDTH = SINGLE_IMAGE_WIDTH * 3;
const int SCREEN_HEIGHT = SINGLE_IMAGE_HEIGHT;

SDL_Window *window = NULL;
SDL_Surface *screen_surface = NULL;
SDL_Event e;
SDL_Rect dest;

SDL_Surface *digit_0_srf = NULL;
SDL_Surface *digit_1_srf = NULL;
SDL_Surface *digit_2_srf = NULL;
SDL_Surface *digit_3_srf = NULL;
SDL_Surface *digit_4_srf = NULL;
SDL_Surface *digit_5_srf = NULL;
SDL_Surface *digit_6_srf = NULL;
SDL_Surface *digit_7_srf = NULL;
SDL_Surface *digit_8_srf = NULL;
SDL_Surface *digit_9_srf = NULL;
SDL_Surface *digit_null_srf = NULL;

int main_counter = 0;
const int BASE = 10;

int main(int argc, char *args[]) {
    if (!init_sdl()) return 1;
    if (!load_media()) return 2;

    init_screen();

    while (SDL_WaitEvent(&e) != 0) {

        if (e.type == SDL_QUIT)
            break;
        else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_DOWN:
                next();
                break;

                default: break;
            }
        }

        SDL_UpdateWindowSurface(window);
    }

    deinit_sdl();

	return 0;
}


void next() {
    main_counter++;

    if (main_counter < 10) {
        int digit = main_counter;
        SDL_Surface *temp_srf = get_digit_srf(digit);
        dest.x = SINGLE_IMAGE_WIDTH;
        SDL_BlitSurface(temp_srf, NULL, screen_surface, &dest);
    } else if (main_counter >=10 && main_counter < 100) {
        int digit = main_counter;
        int digit_2 = digit % BASE;
        int digit_1 = digit / BASE;
        //printf("digit_1: %d, digit_2: %d\n", digit_1, digit_2);
        SDL_Surface *temp_1_srf = get_digit_srf(digit_1);
        SDL_Surface *temp_2_srf = get_digit_srf(digit_2);
        dest.x = SINGLE_IMAGE_WIDTH;
        SDL_BlitSurface(temp_1_srf, NULL, screen_surface, &dest);
        dest.x = SINGLE_IMAGE_WIDTH * 2;
        SDL_BlitSurface(temp_2_srf, NULL, screen_surface, &dest);
    } else {
        int digit = main_counter;
        int digit_3 = digit % BASE;
        digit /= BASE;
        int digit_2 = digit % BASE;
        int digit_1 = digit / BASE;
        SDL_Surface *temp_1_srf = get_digit_srf(digit_1);
        SDL_Surface *temp_2_srf = get_digit_srf(digit_2);
        SDL_Surface *temp_3_srf = get_digit_srf(digit_3);
        dest.x = 0;
        SDL_BlitSurface(temp_1_srf, NULL, screen_surface, &dest);
        dest.x = SINGLE_IMAGE_WIDTH;
        SDL_BlitSurface(temp_2_srf, NULL, screen_surface, &dest);
        dest.x = SINGLE_IMAGE_WIDTH * 2;
        SDL_BlitSurface(temp_3_srf, NULL, screen_surface, &dest);
    }
}

SDL_Surface* get_digit_srf(int digit) {
    if (digit == 0) return digit_0_srf;
    if (digit == 1) return digit_1_srf;
    if (digit == 2) return digit_2_srf;
    if (digit == 3) return digit_3_srf;
    if (digit == 4) return digit_4_srf;
    if (digit == 5) return digit_5_srf;
    if (digit == 6) return digit_6_srf;
    if (digit == 7) return digit_7_srf;
    if (digit == 8) return digit_8_srf;
    if (digit == 9) return digit_9_srf;

    return digit_null_srf;
}

void init_screen() {
    dest.x = SINGLE_IMAGE_WIDTH;
    dest.y = 0;
    dest.w = SINGLE_IMAGE_WIDTH;
    dest.h = SINGLE_IMAGE_HEIGHT;
    SDL_BlitSurface(digit_0_srf, NULL, screen_surface, &dest);

    dest.x = 0;
    SDL_BlitSurface(digit_null_srf, NULL, screen_surface, &dest);

    dest.x = SINGLE_IMAGE_WIDTH * 2;
    SDL_BlitSurface(digit_null_srf, NULL, screen_surface, &dest);

    SDL_UpdateWindowSurface(window);
}

bool init_sdl() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	} else {
		window = SDL_CreateWindow("Electronic Beads", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			return false;
		} else {
			screen_surface = SDL_GetWindowSurface(window);
            return true;
		}
	}
}

bool load_media() {
    digit_0_srf = SDL_LoadBMP("images/digits/bmp/digit_0.bmp");
    digit_1_srf = SDL_LoadBMP("images/digits/bmp/digit_1.bmp");
    digit_2_srf = SDL_LoadBMP("images/digits/bmp/digit_2.bmp");
    digit_3_srf = SDL_LoadBMP("images/digits/bmp/digit_3.bmp");
    digit_4_srf = SDL_LoadBMP("images/digits/bmp/digit_4.bmp");
    digit_5_srf = SDL_LoadBMP("images/digits/bmp/digit_5.bmp");
    digit_6_srf = SDL_LoadBMP("images/digits/bmp/digit_6.bmp");
    digit_7_srf = SDL_LoadBMP("images/digits/bmp/digit_7.bmp");
    digit_8_srf = SDL_LoadBMP("images/digits/bmp/digit_8.bmp");
    digit_9_srf = SDL_LoadBMP("images/digits/bmp/digit_9.bmp");
    digit_null_srf = SDL_LoadBMP("images/digits/bmp/digit_null.bmp");

    if (digit_0_srf == NULL ||
        digit_1_srf == NULL ||
        digit_2_srf == NULL ||
        digit_3_srf == NULL ||
        digit_4_srf == NULL ||
        digit_5_srf == NULL ||
        digit_6_srf == NULL ||
        digit_7_srf == NULL ||
        digit_8_srf == NULL ||
        digit_9_srf == NULL ||
        digit_null_srf == NULL)
    {
        printf("Unable to load digit images! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

void deinit_sdl() {
    SDL_FreeSurface(digit_0_srf);
    SDL_FreeSurface(digit_1_srf);
    SDL_FreeSurface(digit_2_srf);
    SDL_FreeSurface(digit_3_srf);
    SDL_FreeSurface(digit_4_srf);
    SDL_FreeSurface(digit_5_srf);
    SDL_FreeSurface(digit_6_srf);
    SDL_FreeSurface(digit_7_srf);
    SDL_FreeSurface(digit_8_srf);
    SDL_FreeSurface(digit_9_srf);
    SDL_FreeSurface(digit_null_srf);

    screen_surface = NULL;

    SDL_DestroyWindow(window);
    window = NULL;

    SDL_Quit();
}
