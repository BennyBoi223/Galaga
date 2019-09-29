#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <SDL/SDL.h>
#include <iostream>
#include <time.h>

using namespace std;

int main ( int argc, char** argv )
{
    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
     }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(900, 700, 32,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }

    // load an image
    SDL_Surface* bmp = SDL_LoadBMP("cb.bmp");
    if (!bmp)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return 1;
    }

    // centre the bitmap on screen
    SDL_Rect dstrect;
    dstrect.x = (screen->w - bmp->w) / 2;
    dstrect.y = (screen->h - bmp->h) / 2;

    // TODO: modify game loop
    // game loop
    bool done = false;
    int fps;
    time_t lastUpdatedTime = time(NULL);
    while (!done)
    {
        // message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // check for messages
            switch (event.type)
            {
                // exit if the window is closed
            case SDL_QUIT:
                done = true;
                break;

                // check for keypresses
            case SDL_KEYDOWN: // KEYUP
                {
                    // exit if ESCAPE is pressed
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        done = true;
                    if (event.key.keysym.sym == SDLK_q)
                        done = true;
                    switch(event.key.keysym.sym) {
                        case SDLK_w:
                            cout << "Up key pressed" << endl;
                            break;
                        case SDLK_s:
                            cout << "Down key pressed" << endl;
                            break;
                        case SDLK_a:
                            cout << "Left key pressed" << endl;
                            break;
                        case SDLK_d:
                            cout << "Right key pressed" << endl;
                            break;
                        case SDLK_q:
                            done = true;
                            break;
                        case SDLK_ESCAPE:
                            done = true;
                            break;
                        }
                    break;
                }
            } // end switch
        } // end of message processing

        // DRAWING STARTS HERE

        // clear screen
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

        // draw bitmap
        SDL_BlitSurface(bmp, 0, screen, &dstrect);

        // DRAWING ENDS HERE

        // finally, update the screen :)
        SDL_Flip(screen);
        fps = fps + 1;

        time_t currentTime = time(NULL);
        double differenceSeconds = difftime(currentTime, lastUpdatedTime);
        if (differenceSeconds >= 1) {
            cout << "Frames per second: " << fps << endl;
            fps = 0;
            lastUpdatedTime = currentTime;
        }

    } // end main loop

    // free loaded bitmap
    SDL_FreeSurface(bmp);

    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}
