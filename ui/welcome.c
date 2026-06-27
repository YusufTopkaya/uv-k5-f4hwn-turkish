/* Copyright 2023 Dual Tachyon
 * https://github.com/DualTachyon
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 *     Unless required by applicable law or agreed to in writing, software
 *     distributed under the License is distributed on an "AS IS" BASIS,
 *     WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *     See the License for the specific language governing permissions and
 *     limitations under the License.
 */

#include <string.h>

#include "driver/eeprom.h"
#include "driver/st7565.h"
#include "driver/system.h"
#include "external/printf/printf.h"
#include "helper/battery.h"
#include "settings.h"
#include "misc.h"
#include "ui/helper.h"
#include "ui/welcome.h"
#include "ui/status.h"
#include "ui/strings.h"
#include "version.h"
#include "bitmaps.h"

#ifdef ENABLE_FEAT_F4HWN_SCREENSHOT
    #include "screenshot.h"
#endif

#ifdef ENABLE_FEAT_F4HWN
/* Apply a simple 2x2 Bayer dither to the boot logo.  level 0 = fully off,
 * level 1 = 25%, level 2 = 50%, level 3 = 75%, level 4 = fully on.
 * This lets the logo "fade" in/out on the 1-bit LCD. */
static void UI_DrawLogoWithFade(uint8_t level)
{
    const uint8_t bayer[2][2] = {{0, 2}, {3, 1}};

    for (uint8_t page = 0; page < 8; page++)
    {
        uint8_t *dst = (page == 0) ? gStatusLine : gFrameBuffer[page - 1];

        for (uint8_t x = 0; x < LCD_WIDTH; x++)
        {
            uint8_t src_byte = BITMAP_Logo[page][x];
            uint8_t dst_byte = 0;

            for (uint8_t bit = 0; bit < 8; bit++)
            {
                if ((src_byte & (1u << bit)) == 0)
                    continue;

                uint8_t y = (page * 8) + bit;
                uint8_t v = bayer[y & 1u][x & 1u];

                if (v < level)
                    dst_byte |= (1u << bit);
            }

            dst[x] = dst_byte;
        }
    }
}
#endif

void UI_DisplayReleaseKeys(void)
{
    memset(gStatusLine,  0, sizeof(gStatusLine));
#if defined(ENABLE_FEAT_F4HWN_CTR) || defined(ENABLE_FEAT_F4HWN_INV)
        ST7565_ContrastAndInv();
#endif
    UI_DisplayClear();

    UI_PrintString(STR_BIRAK, 0, 127, 1, 10);
    UI_PrintString(STR_TUM_TUSLARI, 0, 127, 3, 10);

    ST7565_BlitStatusLine();  // blank status line
    ST7565_BlitFullScreen();
}

void UI_DisplayWelcome(void)
{
    char WelcomeString0[16];
    char WelcomeString1[16];
    char WelcomeString2[16];
    char WelcomeString3[20];

    memset(gStatusLine,  0, sizeof(gStatusLine));

#if defined(ENABLE_FEAT_F4HWN_CTR) || defined(ENABLE_FEAT_F4HWN_INV)
        ST7565_ContrastAndInv();
#endif
    UI_DisplayClear();

#ifdef ENABLE_FEAT_F4HWN
    ST7565_BlitStatusLine();
    ST7565_BlitFullScreen();
    
    if (gEeprom.POWER_ON_DISPLAY_MODE == POWER_ON_DISPLAY_MODE_NONE || gEeprom.POWER_ON_DISPLAY_MODE == POWER_ON_DISPLAY_MODE_SOUND) {
        ST7565_FillScreen(0x00);
#else
    if (gEeprom.POWER_ON_DISPLAY_MODE == POWER_ON_DISPLAY_MODE_NONE || gEeprom.POWER_ON_DISPLAY_MODE == POWER_ON_DISPLAY_MODE_FULL_SCREEN) {
        ST7565_FillScreen(0xFF);
#endif
    } else {
        memset(WelcomeString0, 0, sizeof(WelcomeString0));
        memset(WelcomeString1, 0, sizeof(WelcomeString1));

        EEPROM_ReadBuffer(0x0EB0, WelcomeString0, 16);
        EEPROM_ReadBuffer(0x0EC0, WelcomeString1, 16);

        sprintf(WelcomeString2, "%u.%02uV %u%%",
                gBatteryVoltageAverage / 100,
                gBatteryVoltageAverage % 100,
                BATTERY_VoltsToPercent(gBatteryVoltageAverage));

        if (gEeprom.POWER_ON_DISPLAY_MODE == POWER_ON_DISPLAY_MODE_VOLTAGE)
        {
            strcpy(WelcomeString0, STR_VOLTAJ);
            strcpy(WelcomeString1, WelcomeString2);
        }
        else if(gEeprom.POWER_ON_DISPLAY_MODE == POWER_ON_DISPLAY_MODE_ALL)
        {
            if(strlen(WelcomeString0) == 0 && strlen(WelcomeString1) == 0)
            {
                strcpy(WelcomeString0, STR_HOSGELDIN);
                strcpy(WelcomeString1, WelcomeString2);
            }
            else if(strlen(WelcomeString0) == 0 || strlen(WelcomeString1) == 0)
            {
                if(strlen(WelcomeString0) == 0)
                {
                    strcpy(WelcomeString0, WelcomeString1);
                }
                strcpy(WelcomeString1, WelcomeString2);
            }
        }
        else if(gEeprom.POWER_ON_DISPLAY_MODE == POWER_ON_DISPLAY_MODE_MESSAGE)
        {
            if(strlen(WelcomeString0) == 0)
            {
                strcpy(WelcomeString0, STR_HOSGELDIN);
            }

            if(strlen(WelcomeString1) == 0)
            {
                strcpy(WelcomeString1, STR_HOSGELDIN);
            }
        }

#ifdef ENABLE_FEAT_F4HWN
        if (gEeprom.POWER_ON_DISPLAY_MODE == POWER_ON_DISPLAY_MODE_ALL)
        {
            const uint16_t frame_delay_ms = gEeprom.POWER_ON_LOGO_ANIM_SPEED ? 70 : 130;

            if (gEeprom.POWER_ON_LOGO_ANIMATION == 0)
            {
                // Animation disabled: show the logo fully lit immediately.
                UI_DrawLogoWithFade(4);
                ST7565_BlitStatusLine();
            }
            else
            {
                // Fade the boot logo in, then give it a gentle pulse, leaving it
                // fully visible for the rest of the boot delay.
                const uint8_t fade_levels[] = {0, 1, 2, 3, 4, 3, 2, 3, 4, 3, 2, 3, 4};

                for (uint8_t i = 0; i < ARRAY_SIZE(fade_levels); i++)
                {
                    UI_DrawLogoWithFade(fade_levels[i]);
                    ST7565_BlitStatusLine();
                    ST7565_BlitFullScreen();
                    SYSTEM_DelayMs(frame_delay_ms);
                }
            }
        }
        else
#endif
        {
            UI_PrintString(WelcomeString0, 0, 127, 0, 10);
            UI_PrintString(WelcomeString1, 0, 127, 2, 10);

#ifdef ENABLE_FEAT_F4HWN
            UI_PrintStringSmallNormal(Version, 0, 128, 4);

            UI_DrawLineBuffer(gFrameBuffer, 0, 31, 127, 31, 1); // Be ware, status zone = 8 lines, the rest = 56 ->total 64

            for (uint8_t i = 18; i < 110; i++)
            {
                gFrameBuffer[4][i] ^= 0xFF;
            }

            sprintf(WelcomeString3, "%s Surum", Edition);
            UI_PrintStringSmallNormal(WelcomeString3, 0, 127, 6);
#else
            UI_PrintStringSmallNormal(Version, 0, 127, 6);
#endif
        }

        //ST7565_BlitStatusLine();  // blank status line : I think it's useless
        ST7565_BlitFullScreen();

        #ifdef ENABLE_FEAT_F4HWN_SCREENSHOT
            getScreenShot(true);
        #endif
    }
}
