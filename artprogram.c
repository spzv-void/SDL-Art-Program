#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <math.h> 

#define WIDTH 1000
#define HEIGHT 680

int brushSize = 5;


SDL_Renderer *renderer;
SDL_Event event;
SDL_Color brushColor = {0, 0, 255, 255};

void DrawCircle(int centerX, int centerY, int radius) {
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x * x + y * y <= radius * radius) {
                SDL_RenderDrawPoint(
                    renderer,
                    centerX + x,
                    centerY + y
                );
            }
        }
    }
}


void DrawBrush(int x1, int y1, int x2, int y2, int radius) {
        int dx = x2 - x1;
        int dy = y2 - y1;

        int distance = sqrt(dx * dx + dy * dy);

        if (distance == 0) {
                DrawCircle(x1, y1, radius);
                return;
        }

        for (int i = 0; i <= distance; i++) {
                float t = (float)i / distance;

                int x = x1 + dx * t;
                int y = y1 + dy * t;

                DrawCircle(x, y, radius);
    }
}

void DrawingSystem(SDL_Texture *canvas) {
        static int previousX;
        static int previousY;
        static int wasDrawing = 0;

        int x, y;
        Uint32 input = SDL_GetMouseState(&x, &y);

        SDL_SetRenderTarget(renderer, canvas);
        SDL_SetRenderDrawColor(renderer, brushColor.r, brushColor.g, brushColor.b, brushColor.a);

        if (input & SDL_BUTTON(SDL_BUTTON_LEFT)) {
                if (wasDrawing) {
                        DrawBrush(
                                previousX,
                                previousY,
                                x,
                                y,
                                brushSize / 2
                        );
                } else {
                        DrawCircle(x, y, brushSize / 2);
                }

                previousX = x;
                previousY = y;
                wasDrawing = 1;

        } else {
                wasDrawing = 0;
        }

        SDL_SetRenderTarget(renderer, NULL);
}


void InitSDL() {
	SDL_Window *window;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	SDL_Texture *canvas = SDL_CreateTexture(
                renderer,
                SDL_PIXELFORMAT_RGBA8888,
                SDL_TEXTUREACCESS_TARGET,
                WIDTH,
                HEIGHT
        );

	SDL_SetRenderTarget(renderer, canvas);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderTarget(renderer, NULL);

	int running = 1;

	while (running) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					running = 0;
					break;
				case SDL_KEYDOWN:
                                        switch (event.key.keysym.scancode) {
                                                case SDL_SCANCODE_L:
                                                        if (brushSize > 1)
                                                        brushSize--;
							printf("%d\n", brushSize);
                                                        break;

                                                case SDL_SCANCODE_H:
                                                        brushSize++;
							printf("%d\n", brushSize);
                                                        break; 
						case SDL_SCANCODE_R:
							brushColor = (SDL_Color){255, 0, 0, 255};
							break;
						case SDL_SCANCODE_V:
							brushColor = (SDL_Color){0, 0, 0, 255};
							break;
						case SDL_SCANCODE_B:
							brushColor = (SDL_Color){0, 0, 255, 255};
							break;
                                                }
                                break;
			}
		}
		DrawingSystem(canvas);
		SDL_RenderCopy(renderer, canvas, NULL, NULL);
		SDL_RenderPresent(renderer);
	        SDL_Delay(1);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int main() {	
	InitSDL(); 
	return 0;
}
