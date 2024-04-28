#include "dependencies/Visualizer.h"



int main()
{
    Menu men;
    men.draw();
    Visualizer viz;
    viz.setup();
    viz.run();
}