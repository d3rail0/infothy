#define RAYGUI_IMPLEMENTATION

#include <iostream>
#include "Base/Application.h"

int main(void)
{
    
    std::unique_ptr app = std::make_unique<Application>();
    app->run();

    return 0;
}