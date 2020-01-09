#include "DisplayHandler.h"
#include "stateMachine.h"
DisplayHandler::DisplayHandler()
{
}
DisplayHandler &DisplayHandler::getDisplayHandler()
{
    static DisplayHandler dh;
    return dh;
}
void DisplayHandler::setDisplayState(const int state)
{
    switch (state)
    {
    case laserpointer:
    {
        M5.Lcd.fillScreen(RED);
        M5.Lcd.setCursor(coords[0], coords[1]);
        M5.Lcd.setTextColor(WHITE);
        M5.Lcd.setTextSize(text_size);
        M5.Lcd.print("Laserpointer");
        break;
    }
    case browser:
    {
        M5.Lcd.fillScreen(GREEN);
        M5.Lcd.setCursor(coords[0], coords[1]);
        M5.Lcd.setTextColor(BLACK);
        M5.Lcd.setTextSize(text_size);
        M5.Lcd.print("Browser");
        break;
    }
    case multimedia:
    {
        M5.Lcd.fillScreen(BLUE);
        M5.Lcd.setCursor(coords[0], coords[1]);
        M5.Lcd.setTextColor(WHITE);
        M5.Lcd.setTextSize(text_size);
        M5.Lcd.print("Multimedia");
        break;
    }
    case presentation:
    {
        M5.Lcd.fillScreen(YELLOW);
        M5.Lcd.setCursor(coords[0], coords[1]);
        M5.Lcd.setTextColor(BLACK);
        M5.Lcd.setTextSize(text_size);
        M5.Lcd.print("Presentation");
        break;
    }
    default:
    {
        break;
    }
    }
}