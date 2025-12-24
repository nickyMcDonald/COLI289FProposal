#pragma once
#include <raylib.h>

Rectangle* area_get()
{
    static Rectangle area = {0};
    return &area;
}

void area_update(int screenWidth, int screenHeight)
{
    Rectangle* area = area_get();
    
    if (screenWidth < screenHeight)
    {
        area->x = 0;
        area->y = (screenHeight - screenWidth) / 2;
        area->width = screenWidth;
        area->height = screenWidth;
    }
    else
    {
        area->x = (screenWidth - screenHeight) / 2;
        area->y = 0;
        area->width = screenHeight;
        area->height = screenHeight;
    }
}
