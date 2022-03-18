#include "state.h"
#include <stdio.h>

void stage_as_str(t_stage stage, char *buffer) {
    switch (stage)
    {
    case G_INIT:
        sprintf(buffer, "PLACE YOUR WORKER");
        break;
    
    case G_MOVE_SELECT:
        sprintf(buffer, "SELECT YOUR WORKER");
        break;

    case G_MOVE:
        sprintf(buffer, "MOVE SELECTED YOUR WORKER");
        break;
    
    case G_BUILD:
        sprintf(buffer, "BUILD SOMETHING");
        break;

    default:
        sprintf(buffer, "GAME END");
        break;
    }
}
