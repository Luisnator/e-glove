#include "stateMachine.h"
StateMachine::StateMachine()
{
    //bh.setupBluetooth();
    pinMode(laserpointer_pin,OUTPUT);
}
void StateMachine::init()
{
    gr.init();
}
void StateMachine::changeState(int state)
{
    this->state = state;
}
void StateMachine::work()
{
    static uint32_t prev_ms = millis();
    if ((millis() - prev_ms) > 16)
    {
        gr.updateMPU();
        prev_ms = millis();
    }
    //Serial.println(state);
    if(!fs.isFlexed())
    {
        digitalWrite(laserpointer_pin,LOW); 
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
            w_interval = 0;
            break;
        }
        case browser:
        {
            int gesture = gr.getGesture();
            w_interval = interval;
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
                bh.sendInt(scrollup);
                previousMillis = currentMillis;
                break;
            }
            case DownSwipe:
            {
                bh.sendInt(scrolldown);
                previousMillis = currentMillis;
                break;
            }
            case LeftRoll:
            {
                bh.sendInt(volumedown);
                w_interval = 100;
                previousMillis = currentMillis;
                break;
            }
            case RightRoll:
            {
                bh.sendInt(volumeup);
                w_interval = 100;
                previousMillis = currentMillis;
                break;
            }
            default:
            {
                w_interval = 0;
                break;
            }
            }
            break;
        }
        case multimedia:
        {
            int gesture = gr.getGesture();
            w_interval = interval;
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
                w_interval = 100;
                break;
            }
            case RightRoll:
            {
                bh.sendInt(volumeup);
                previousMillis = currentMillis;
                w_interval = 100;
                break;
            }
            default:
            {
                w_interval = 0;
                break;
            }
            }
            break;
        }
        case presentation:
        {
            int gesture = gr.getGesture();
            w_interval = interval;
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
                w_interval = 100;
                break;
            }
            case RightRoll:
            {
                bh.sendInt(volumeup);
                previousMillis = currentMillis;
                w_interval = 100;
                break;
            }
            default:
            {
                w_interval = 0;
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