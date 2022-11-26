#include <stdio.h>
#include "graphics.h"

int main(void)
{
    printf("Engine starting...\n");

    int result = startGraphics(1280, 720);
    
    printf("Engine terminated.\n");

    return result;
}