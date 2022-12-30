#include "SDL.h"
#include <cairo/cairo.h>

int main(int argc, char * argv[])
{
  int i = 0;
  SDL_bool done = SDL_FALSE;
  SDL_Window* window = SDL_CreateWindow("Hello, world!", 10, 10, 200, 200, 0);
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
  SDL_Texture* texture = SDL_CreateTexture(renderer,
                                           SDL_PIXELFORMAT_RGB24,
                                           SDL_TEXTUREACCESS_STREAMING,
                                           200,
                                           200);

  /*
  int stride;
  unsigned char *data;
  cairo_surface_t *surface;

  stride = cairo_format_stride_for_width (CAIRO_FORMAT_ARGB32, 200);
  data = malloc (stride * 200);
  surface = cairo_image_surface_create_for_data(data, CAIRO_FORMAT_ARGB32,
                                                200, 200,
                                                stride);
  */


  /*
   * SDL_TEXTUREACCESS_STREAMING changes frequently, lockable
   * SDL_TEXTUREACCESS_TARGET can be used as a render target

  cairo_t *cr = cairo_create(surface);
  cairo_select_font_face(cr, "serif", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
  cairo_set_font_size(cr, 12.0);
  cairo_set_source_rgb(cr, 0.0, 1.0, 1.0);
  cairo_move_to(cr, 10.0, 10.0);
  cairo_show_text (cr, "Hello, world");
   */

  // cairo_destroy (cr);
  // cairo_surface_write_to_png (surface, "hello.png");
  // cairo_surface_destroy (surface);

  while (!done) {
    SDL_Event event;

    /*
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawLine(renderer, 0, 0, 100, 100);
    SDL_RenderPresent(renderer);
    */

    int stride;
    uint8_t *drawctx;

    SDL_LockTexture(texture, NULL, (void**) &drawctx, &stride);

    for (int i = 0; i < 200 * 200 * 3; ++i)  {
      drawctx[i] = i;
    }

    SDL_UnlockTexture(texture);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);


    if (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        done = SDL_TRUE;
        break;
      }
    }
  }

  return 0;
}
