#ifndef DEFS_H
#define DEFS_H

#define EXIT_ERROR          1
#define EXIT_SUCCESS        0
#define MAX_KEYBOARD_KEYS   350
#define FPS                 60
#define FPS_TIME            ( 1000 / FPS )
#define MAX_SND_CHANNELS    16
#define MAX_LINE_LENGTH     1024
#define SMALL_TEXT_BUFFER   64
#define MAX_KEYBOARD_KEYS   350
#define MAX_MOUSE_BUTTONS   350
#define MAX_BUFFER_SIZE     128
#define MAX_FILE_NAME_LEN   48
#define TEXTURE_BUFFER_SIZE 4
#define WINDOW_UPDATE_TIMER 1000
#define PI                  3.14159265358979323846

enum GameState { RUNNING, PREGAME, INIT, TRANSITION, PAUSED };

#endif // DEFS_H
