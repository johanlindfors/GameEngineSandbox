#pragma once
#include <chrono>

#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 400
#define FRAMES_PER_SECOND 60
#define TILE_SIZE 40
#define EMPTY 0
#define WALL 1
#define SPOT 2
#define CRATE 3
#define PLAYER 4
//#define FONT "vga_bold_16x16.png"
#define LOADING_PAUSE 150ms
#define FONT "vga_16x16.png"
#define IS_ANIMATED true
#if IS_ANIMATED == true
#define TILES "tiles3.png"
#else
#define TILES "tiles.png"
#endif

#define SAMPLE_MAP "\
##########\r\n\
#####  ..#\r\n\
##### $  #\r\n\
####    .#\r\n\
###  $   #\r\n\
###     .#\r\n\
#     ####\r\n\
# $ $ @###\r\n\
##       #\r\n\
##########\r\n"

#define EASY_MAP "##########|#####    #|#####    #|####     #|###      #|###     .#|#     ####|#   $ @###|##       #|##########"
#define MEDIUM_MAP "##########|#####    #|#####    #|####    .#|###      #|###     .#|#     ####|# $ $ @###|##       #|##########"
#define HARD_MAP "##########|#####  ..#|##### $  #|####    .#|###  $   #|###     .#|#     ####|# $ $ @###|##       #|##########"
