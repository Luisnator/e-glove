#include "stateMachine.h"
StateMachine::StateMachine()
{
    pinMode(laserpointer_pin, OUTPUT);
}
void StateMachine::init()
{
    gr.init();
    bh.setupBluetooth();
    dh.init();
    dh.setDisplayState(state);
}
void StateMachine::changeState(int state)
{
    this->state = state;
    dh.setDisplayState(state);
}
void StateMachine::work()
{
    static uint32_t prev_ms = millis();
    if ((millis() - prev_ms) > 16)
    {
        gr.updateMPU();
        prev_ms = millis();
    }
    if (!fs.isFlexed())
    {
        digitalWrite(laserpointer_pin, LOW);
    }
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= w_interval && fs.isFlexed())
    {
        previousMillis = currentMillis;
        switch (state)
        {
        case laserpointer:
        {
            digitalWrite(laserpointer_pin, HIGH);
            w_interval = no_pause;
            break;
        }
        case browser:
        {
            int gesture = gr.getGesture();
            w_interval = long_pause;
            switch (gesture)
            {
            case LeftSwipe:
            {
                bh.sendInt(browsernextpage);
                previousMillis = currentMillis;
                break;
            }
            case RightSwipe:
            {
                bh.sendInt(browserpreviouspage);
                previousMillis = currentMillis;
                break;
            }
            case UpSwipe:
            {
                //repeat 12 times
                for (int i = 0; i < scrollrepeat; i++)
                {
                    bh.sendInt(scrolldown);
                }
                previousMillis = currentMillis;
                break;
            }
            case DownSwipe:
            {
                //repeat 12 times
                for (int i = 0; i < scrollrepeat; i++)
                {
                    bh.sendInt(scrollup);
                }
                previousMillis = currentMillis;
                break;
            }
            case LeftRoll:
            {
                bh.sendInt(volumedown);
                w_interval = short_pause;
                previousMillis = currentMillis;
                break;
            }
            case RightRoll:
            {
                bh.sendInt(volumeup);
                w_interval = short_pause;
                previousMillis = currentMillis;
                break;
            }
            default:
            {
                w_interval = no_pause;
                break;
            }
            }
            break;
        }
        case multimedia:
        {
            int gesture = gr.getGesture();
            w_interval = long_pause;
            switch (gesture)
            {
            case LeftSwipe:
            {
                bh.sendInt(nexttrack);
                previousMillis = currentMillis;
                break;
            }
            case RightSwipe:
            {
                bh.sendInt(previoustrack);
                previousMillis = currentMillis;
                break;
            }
            case UpSwipe:
            {
                bh.sendInt(playpause);
                previousMillis = currentMillis;
                break;
            }
            case DownSwipe:
            {
                bh.sendInt(playpause);
                previousMillis = currentMillis;
                break;
            }
            case LeftRoll:
            {
                bh.sendInt(volumedown);
                previousMillis = currentMillis;
                w_interval = short_pause;
                break;
            }
            case RightRoll:
            {
                bh.sendInt(volumeup);
                previousMillis = currentMillis;
                w_interval = short_pause;
                break;
            }
            default:
            {
                w_interval = no_pause;
                break;
            }
            }
            break;
        }
        case presentation:
        {
            int gesture = gr.getGesture();
            w_interval = long_pause;
            switch (gesture)
            {
            case LeftSwipe:
            {
                bh.sendInt(nextpage);
                previousMillis = currentMillis;
                break;
            }
            case RightSwipe:
            {
                bh.sendInt(previouspage);
                previousMillis = currentMillis;
                break;
            }
            case UpSwipe:
            {
                bh.sendInt(startpresentation);
                previousMillis = currentMillis;
                break;
            }
            case DownSwipe:
            {
                bh.sendInt(endpresentation);
                previousMillis = currentMillis;
                break;
            }
            case LeftRoll:
            {
                bh.sendInt(volumedown);
                previousMillis = currentMillis;
                w_interval = short_pause;
                break;
            }
            case RightRoll:
            {
                bh.sendInt(volumeup);
                previousMillis = currentMillis;
                w_interval = short_pause;
                break;
            }
            default:
            {
                w_interval = no_pause;
                break;
            }
            }
            break;
        }
        default:
        {
            break;
        }
        }
    }
}