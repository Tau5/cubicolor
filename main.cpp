
#include <SDL.h>
#include <SDL_ttf.h>
#include "cuby.hpp"
#include "texty.hpp"
#include "highscore.hpp"
#include "timer.hpp"
#include "other.hpp"
#include <stdio.h>
#include <string>
#include <random>
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 200;

const Uint32 TIMEOUT = 5000; //For the moment const, maybe in the future the timeout could be changed
int points = 0;
int lastPoints = 0;
string mode = "title";
SDL_Window *gwindow = NULL;
SDL_Surface *gScreenSurface = NULL;
SDL_Texture *gHelloWorld = NULL;
SDL_Event e;
SDL_Rect imgRect;
SDL_Renderer* gRenderer = NULL;
SDL_Rect playerRect;
TTF_Font* font = NULL;
string hs_text = "";
Cuby cubis[5];
enum cubi_types {
  CUBI_UP,
  CUBI_RIGHT,
  CUBI_DOWN,
  CUBI_LEFT
};
int cubis_type[5];
SDL_Color color_types[4] = {
  {r: 0xFF, g: 0xE9, b: 0x20, a: 255}, /*#FFE920*/
  {r: 0xFF, g: 0x26, b: 0x26, a: 255}, /*#FF2626*/
  {r: 0x5B, g: 0x5B, b: 0xFF, a: 255}, /*#5B5BFF*/
  {r: 0x27, g: 0xDE, b: 0x55, a: 255}  /*#27DE55*/
};
SDL_Rect pointsRect = {
  x: 0,
  y: 0,
  w: SCREEN_WIDTH/8,
  h: SCREEN_HEIGHT/3
};
SDL_Rect hsRect = {
  x: SCREEN_WIDTH-SCREEN_WIDTH/3,
  y: 0,
  w: SCREEN_WIDTH/4,
  h: SCREEN_HEIGHT/4
};
SDL_Rect timer_rect {
  x: 0,
  y: SCREEN_HEIGHT- SCREEN_HEIGHT/4,
  w: SCREEN_WIDTH,
  h: SCREEN_HEIGHT/4
};
SDL_Color timer_color = {0xB8, 0x9A, 0xFE}; //B89AFE
bool newhs = false;
int current_cubi = 0;
bool quit = false;
bool init();
bool loadMedia();
void close();
void render();
void color_cubis();
void randomize_cubis();
void restart();
int main(int argc, char *args[]) {
  if (init()) {
    if (loadMedia()) {
      SDL_FillRect(gScreenSurface, NULL, SDL_MapRGB(gScreenSurface->format, 0xFF, 0xFF, 0xFF));
      render();
      while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
          if (e.type == SDL_QUIT) {
            quit = true;
          }
            const Uint8* keyboard = SDL_GetKeyboardState(NULL);
            if (e.type == SDL_KEYDOWN) {
            if (mode == "game") {
              switch (cubis_type[current_cubi]) {
                case CUBI_UP:
                  if (keyboard[SDL_SCANCODE_UP]) {
                      cubis[current_cubi].set_color(0xAA, 0xAA, 0xAA, 255);
                      points++;
                  } else {
                    restart();
                  }
                  current_cubi++;
                  break;
                case CUBI_RIGHT:
                  if (keyboard[SDL_SCANCODE_RIGHT]) {
                      cubis[current_cubi].set_color(0xAA, 0xAA, 0xAA, 255);
                      points++;
                  } else {
                    restart();
                  }
                  current_cubi++;
                  break;
                case CUBI_DOWN:
                  if (keyboard[SDL_SCANCODE_DOWN]) {
                      cubis[current_cubi].set_color(0xAA, 0xAA, 0xAA, 255);
                      points++;
                  } else {
                    restart();
                  }
                  current_cubi++;
                  break;
                case CUBI_LEFT:
                  if (keyboard[SDL_SCANCODE_LEFT]) {
                      cubis[current_cubi].set_color(0xAA, 0xAA, 0xAA, 255);
                      points++;
                  } else {
                    restart();
                  }
                  current_cubi++;
                  break;
              }
            
              if (points < 0) {
                points = 0;
              }
              
              if (current_cubi >= 5) {
                current_cubi = 0;
                reset_timer(TIMEOUT);
                randomize_cubis();
                color_cubis();
              }
              } else {
              if (mode == "title") {
                if(keyboard[SDL_SCANCODE_H]) {
                  mode = "help";
                } else {
                  reset_timer(TIMEOUT);
                  mode = "game";
                }
                
              }
              if (mode == "help") {
                if(keyboard[SDL_SCANCODE_RETURN]) {
                  mode = "title";
                }
              }
              if (mode == "over") mode = "title";
              }
              
            } 
            
          }
          
        
        render();
        if (mode == "game") {
          if (get_timer_status()) {
            restart();
          }
        }
      }
    }
  }
  close();
  return 0;
}
bool init() {
  //Initialize SDL
  bool success = true;
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    success = false;
  } else {
    gwindow = SDL_CreateWindow("CubiColor", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gwindow == NULL) {
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
      success = false;
    } else {
      gRenderer = SDL_CreateRenderer( gwindow, -1, SDL_RENDERER_ACCELERATED );
      SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
      gScreenSurface = SDL_GetWindowSurface(gwindow);
      TTF_Init();
      font = TTF_OpenFont("./PixelOperator-Bold.ttf", 16);
      hs_text = "High score: " + to_string(get_highscore());
      //CUBIS SETUP
      for (int i=0; i<5; i++) {
          cubis[i].set_color(0xAA, 0xAA, 0xAA, 255);
        
        cubis[i].set_positon((SCREEN_WIDTH/5*i+1)+SCREEN_WIDTH/32 /* 640/32 = 20 */, SCREEN_HEIGHT/2);
        cubis[i].set_size(SCREEN_WIDTH/10, SCREEN_HEIGHT/20);
      }

      randomize_cubis();
      color_cubis();

    }
  }
  return success;
}

bool loadMedia() {
  bool success = true;
  return success;
}

void randomize_cubis() {
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator
    std::uniform_int_distribution<> random_cubi_type(CUBI_UP, CUBI_LEFT); // define the range
    for (int i=0;i<5;i++) {
      cubis_type[i] = random_cubi_type(eng);
    }
}

void color_cubis(){
  for (int i=0;i<5;i++){
    cubis[i].set_sdl_color(color_types[cubis_type[i]]);
  }
}

void render() {
  SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(gRenderer);
  if (mode == "game") {
      render_text(gRenderer, font, std::to_string(points), {0, 0, 0}, pointsRect);
      render_text(gRenderer, font, hs_text, {0, 0, 0}, hsRect);
      for (int i=0; i<5; i++) {
        cubis[i].render(gRenderer);
      }
      SDL_SetRenderDrawColor(gRenderer, timer_color.r, timer_color.g, timer_color.b, 0xFF);
      timer_rect.w = Adjust(get_timer_difference(), 0, TIMEOUT, 0, SCREEN_WIDTH);
      
      SDL_RenderFillRect(gRenderer, &timer_rect);
  }
  if (mode == "title") {
    SDL_Rect titleR {
      x: SCREEN_WIDTH/2-SCREEN_WIDTH/5,
      y: SCREEN_HEIGHT/10,
      w: SCREEN_WIDTH/3,
      h: SCREEN_HEIGHT/5
    };
    render_text(gRenderer, font, "CUBI COLOR", {0,0,0}, titleR);
    titleR.y = SCREEN_HEIGHT - SCREEN_HEIGHT/4;
    render_text(gRenderer, font, "Press H for help, press any other key to start", {0,0,0}, titleR);
  }
  if (mode == "over") {
    SDL_Rect titleR {
      x: SCREEN_WIDTH/2-SCREEN_WIDTH/5,
      y: SCREEN_HEIGHT/10,
      w: SCREEN_WIDTH/3,
      h: SCREEN_HEIGHT/5
    };
    SDL_Rect pointsR {
      x: SCREEN_WIDTH/2-SCREEN_WIDTH/5,
      y: SCREEN_HEIGHT/3,
      w: SCREEN_WIDTH,
      h: SCREEN_HEIGHT/3
    };
    render_text(gRenderer, font, "GAME OVER", {0,0,0}, titleR);
    titleR.y = SCREEN_HEIGHT - SCREEN_HEIGHT/4;
    titleR.w = SCREEN_WIDTH/2;
    titleR.x = SCREEN_WIDTH/4;
    render_text(gRenderer, font, "Press any key to go to the title screen", {0,0,0}, titleR);
    string pointsTXT = "Points: " + to_string(lastPoints);
    if (newhs) {
      pointsTXT+= "\nNEW RECORD!";
    } else {
      pointsTXT+= "\nRecord: " + to_string(get_highscore());
    }
    render_text(gRenderer, font, pointsTXT, {0,0,0}, pointsR);
  }
  if (mode == "help") {
    SDL_Rect keyR {
      x: SCREEN_WIDTH/4,
      y: SCREEN_HEIGHT - SCREEN_HEIGHT/4,
      w: SCREEN_WIDTH/2,
      h: SCREEN_HEIGHT/5
    };
    SDL_Rect helpR {
      x: 0,
      y: 0,
      w: SCREEN_WIDTH,
      h: SCREEN_HEIGHT-SCREEN_HEIGHT/5
    };
    render_text(gRenderer, font, "HELP\nIn CubiColor you are presented with rectangles of color, each color refers to a key and you have to press them correctly to gain points\nKEYS AND COLORS\n* Yellow - Up\n* Red - Right\n* Blue - Down\n* Green - Left", {0,0,0}, helpR);
    render_text(gRenderer, font, "Press Return/Enter to go to the title screen", {0xF,0xF,0xF}, keyR);
  }
  SDL_RenderPresent(gRenderer);

}
void close() {
  SDL_DestroyTexture(gHelloWorld);
  SDL_DestroyRenderer(gRenderer);
  SDL_DestroyWindow(gwindow);
  SDL_Quit();
}

void restart() {
  current_cubi = -1;
  newhs = update_highscore(points);
  hs_text = "High score: " + to_string(get_highscore());
  lastPoints = points;
  points = 0;
  mode = "over";
  render();
  randomize_cubis();
  color_cubis();
}

