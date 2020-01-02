#ifndef DISPLAYHANDLER_H
#define DISPLAYHANDLER_H
#include <M5Stack.h>
class DisplayHandler{
    private:
    int text_size = 4;
    int coords[2] = {10,100};
    DisplayHandler();
    public:
    static DisplayHandler& getDisplayHandler();
    void init();
    void setDisplayState(int state);

};
#endif