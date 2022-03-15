#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "OLED128x64_SH1106.h"
#include "OLED128x64_SSD1309.h"

extern bool haveDisplay;
extern bool needUpdateUI;
extern int editMode;
// ----- CUSTOM -----
extern bool displayOff;

extern OLED128x64_SH1106 SH1106;
extern OLED128x64_SSD1309 SSD1309;

class Display
{
public:
  Display(void) {}

  void begin(DisplayDriver* drv)
  {
    pDisplayDriver = drv;
    if(pDisplayDriver)
      pDisplayDriver->begin();
  }

  void drawBootScreen(void)
  { 
    if(pDisplayDriver)
      pDisplayDriver->drawBootScreen();
  }

  void drawUI(const char* plugin, const char* ip, const char* preset, float vol, int editMode = 0)
  {
    if(pDisplayDriver)
      pDisplayDriver->drawUI(plugin, ip, preset, vol, editMode);
  }

  void drawSwitchingPreset(void)
  {
    if(pDisplayDriver)
      pDisplayDriver->drawSwitchingPreset();
  }

    // ----- CUSTOM -----
    void displayOff(void)
    {
        if(pDisplayDriver)
            pDisplayDriver->displayOff();
    }

    void displayOn(void)
    {
        if(pDisplayDriver)
            pDisplayDriver->displayOn();
    }

private:
  DisplayDriver* pDisplayDriver = nullptr;
};

#endif
