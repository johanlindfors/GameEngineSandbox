#pragma once

#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 400
#define FRAMES_PER_SECOND 60
#define TILE_SIZE 40
#define EMPTY 0 
#define WALL 1
#define SPOT 2
#define CRATE 3
#define PLAYER 4

#define SAMPLE_MAP "###############  ..###### $  #####    .####  $   ####     .##     ##### $ $ @#####       ###########"
#define PARSED_MAP {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,2,2,1,1,1,1,1,1,0,3,0,0,1,1,1,1,1,0,0,0,0,2,1,1,1,1,0,0,3,0,0,0,1,1,1,1,0,0,0,0,0,2,1,1,0,0,0,0,0,1,1,1,1,1,0,3,0,3,0,4,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1}