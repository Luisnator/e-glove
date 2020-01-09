#ifndef DISPLAYHANDLER_H
#define DISPLAYHANDLER_H
#include <M5Stack.h>

/*! \file displayHandler.h*/ 

//!  Class to handle the display of the m5stack
/*!*/
class DisplayHandler
{
private:
    int text_size = 4;         /*!< The size of the text on the display */
    int coords[2] = {10, 100}; /*!< Coordinates for the text on the display */
    //! Constructor for DisplayHandler class
    /*!*/
    DisplayHandler();

public:
    //! Singelton-Pattern function to receive an object
    /*!
      \return Refrence to the DisplayHandler object
    */
    static DisplayHandler &getDisplayHandler();
    //! Display the mode according to the state
    /*!
      \param state the current state
    */
    void setDisplayState(int state);
};
#endif