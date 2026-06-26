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
#include <stdlib.h>

#include "../app/dtmf.h"
#include "../app/menu.h"
#include "../bitmaps.h"
#include "../board.h"
#include "../dcs.h"
#include "../driver/backlight.h"
#include "../driver/bk4819.h"
#include "../driver/eeprom.h"
#include "../driver/st7565.h"
#include "../external/printf/printf.h"
#include "../frequencies.h"
#include "../helper/battery.h"
#include "../misc.h"
#include "../settings.h"
#ifdef ENABLE_FEAT_F4HWN
    #include "../version.h"
#endif
#include "font.h"
#include "helper.h"
#include "inputbox.h"
#include "menu.h"
#include "strings.h"
#include "ui.h"


const t_menu_item MenuList[] =
{
//   text,          menu ID
    {"Adim",        MENU_STEP          },
    {"TXGucu",    MENU_TXP           }, // was "TXP"
    {"RxDCS",       MENU_R_DCS         }, // was "R_DCS"
    {"RxCTCS",      MENU_R_CTCS        }, // was "R_CTCS"
    {"TxDCS",       MENU_T_DCS         }, // was "T_DCS"
    {"TxCTCS",      MENU_T_CTCS        }, // was "T_CTCS"
    {"TxOfsetYon",  MENU_SFT_D         }, // was "SFT_D"
    {"Ofset",      MENU_OFFSET        }, // was "OFFSET"
    {"BantGenis",   MENU_W_N           },
#ifndef ENABLE_FEAT_F4HWN
    {"Karistirici", MENU_SCR           }, // was "SCR"
#endif
    {"MesgulKilit", MENU_BCL           }, // was "BCL"
    {"Kompander",   MENU_COMPAND       },
    {"Modulasyon", MENU_AM            }, // was "AM"
#ifdef ENABLE_FEAT_F4HWN
    {"TXKiliti",   MENU_TX_LOCK       }, 
#endif
    {"ListeyeEkle1", MENU_S_ADD1        },
    {"ListeyeEkle2", MENU_S_ADD2        },
    {"ListeyeEkle3", MENU_S_ADD3        },
    {"Kaydet",      MENU_MEM_CH        }, // was "MEM-CH"
    {"Sil",      MENU_DEL_CH        }, // was "DEL-CH"
    {"KanalIsmi", MENU_MEM_NAME      },

    {"TaramaList",  MENU_S_LIST        },
    {"TaramaList1", MENU_SLIST1        },
    {"TaramaList2", MENU_SLIST2        },
    {"TaramaList3", MENU_SLIST3        },
    {"Tarama",      MENU_SC_REV        },
#ifndef ENABLE_FEAT_F4HWN
    #ifdef ENABLE_NOAA
        {"NOAA-S",      MENU_NOAA_S    },
    #endif
#endif
    {"F1Kisa",      MENU_F1SHRT        },
    {"F1Uzun",      MENU_F1LONG        },
    {"F2Kisa",      MENU_F2SHRT        },
    {"F2Uzun",      MENU_F2LONG        },
    {"MUzun",       MENU_MLONG         },

    {"OtoKilit",   MENU_AUTOLK        }, // was "AUTOLk"
    {"TXSuresi",    MENU_TOT           }, // was "TOT"
    {"PilTasarruf", MENU_SAVE          }, // was "SAVE"
    {"PilGostergesi", MENU_BAT_TXT       },
    {"Mikrofon",    MENU_MIC           },
    {"MikrofonBar", MENU_MIC_BAR       },
    {"KanalGorunumu", MENU_MDF           }, // was "MDF"
    {"AcilisEkrani", MENU_PONMSG        },
    {"ArkaIsikZaman", MENU_ABR           }, // was "ABR"
    {"ArkaIsikMin", MENU_ABR_MIN       },
    {"ArkaIsikMax", MENU_ABR_MAX       },
    {"ArkaIsikTxRx", MENU_ABR_ON_TX_RX  },
    {"TusSesi",    MENU_BEEP          },
#ifdef ENABLE_VOICE
    {"SesDili",   MENU_VOICE         },
#endif
    {"RogerBeep",   MENU_ROGER         },
    {"KuyrukKes",   MENU_STE           },
    {"TersKuyruk",  MENU_RP_STE        },
    {"TekKanalAra", MENU_1_CALL        },
#ifdef ENABLE_ALARM
    {"AlarmModu",  MENU_AL_MOD        },
#endif
#ifdef ENABLE_DTMF_CALLING
    {"ANI ID",      MENU_ANI_ID        },
#endif
    {"YukariKod",   MENU_UPCODE        },
    {"AsagiKod",    MENU_DWCODE        },
    {"PTT ID",      MENU_PTT_ID        },
    {"DTMFDurum",   MENU_D_ST          },
#ifdef ENABLE_DTMF_CALLING
    {"DTMFCevap",   MENU_D_RSP         },
    {"DTMFBekle",   MENU_D_HOLD        },
#endif
    {"DTMFGecik",   MENU_D_PRE         },
#ifdef ENABLE_DTMF_CALLING
    {"DTMFKodCo",   MENU_D_DCD         },
    {"DTMFListe",   MENU_D_LIST        },
#endif
    {"DTMFCanli",   MENU_D_LIVE_DEC    }, // live DTMF decoder
#ifndef ENABLE_FEAT_F4HWN
    #ifdef ENABLE_AM_FIX
        {"AM Fix",      MENU_AM_FIX        },
    #endif
#endif
    {"VOX",         MENU_VOX           },
#ifdef ENABLE_FEAT_F4HWN
    {"SistemBilgi", MENU_VOL           }, // was "VOL"
#else
    {"PilVoltaji",  MENU_VOL           }, // was "VOL"
#endif
    {"RXModu",      MENU_TDR           },
    {"Susturma",    MENU_SQL           },
#ifdef ENABLE_FEAT_F4HWN
    {"GucAyar",     MENU_SET_PWR       },
    {"PTTAyar",     MENU_SET_PTT       },
    {"TXSureAyar",  MENU_SET_TOT       },
    {"EOTUyari",    MENU_SET_EOT       },
    {"KontrastAyar", MENU_SET_CTR       },
    {"TersAyar",    MENU_SET_INV       },
    {"KilitAyar",   MENU_SET_LCK       },
    {"MetreAyar",   MENU_SET_MET       },
    {"ArayuzAyar",  MENU_SET_GUI       },
    {"ZamanAyar",   MENU_SET_TMR       },
#ifdef ENABLE_FEAT_F4HWN_SLEEP
    {"UykuAyar",     MENU_SET_OFF      },
#endif
#ifdef ENABLE_FEAT_F4HWN_NARROWER
    {"NFMAyar",     MENU_SET_NFM       },
#endif
#ifdef ENABLE_FEAT_F4HWN_VOL
    {"SesAyar",     MENU_SET_VOL       },
#endif
#ifdef ENABLE_FEAT_F4HWN_RESCUE_OPS
    {"TusAyar",     MENU_SET_KEY       },
#endif
#ifdef ENABLE_NOAA
    {"SetNWR",      MENU_NOAA_S    },
#endif
#endif
    // hidden menu items from here on
    // enabled if pressing both the PTT and upper side button at power-on
    {"FrekansKilit", MENU_F_LOCK        },
#ifndef ENABLE_FEAT_F4HWN
    {"Tx 200",      MENU_200TX         }, // was "200TX"
    {"Tx 350",      MENU_350TX         }, // was "350TX"
    {"Tx 500",      MENU_500TX         }, // was "500TX"
#endif
    {"350MHzAc",    MENU_350EN         }, // was "350EN"
#ifndef ENABLE_FEAT_F4HWN
    {"KaristiriciAc", MENU_SCREN         }, // was "SCREN"
#endif
#ifdef ENABLE_F_CAL_MENU
    {"FrekansKal",  MENU_F_CALI        }, // referans kristal kalibrasyonu
#endif
    {"PilKalibrasyon", MENU_BATCAL        }, // battery voltage calibration
    {"PilTipi",     MENU_BATTYP        }, // battery type 1600/2200mAh
    {"FabrikaSifir", MENU_RESET         }, // might be better to move this to the hidden menu items ?

    {"",                              0xff               }  // end of list - DO NOT delete or move this this
};

const uint8_t FIRST_HIDDEN_MENU_ITEM = MENU_F_LOCK;

const char * const gSubMenu_TXP[] =
{
    "OZEL",
    STR_DUSUK,
    STR_DUSUK,
    STR_DUSUK,
    STR_DUSUK,
    STR_DUSUK,
    STR_ORTA,
    STR_YUKSEK
};

const char * const gSubMenu_SFT_D[] =
{
    STR_KAPALI,
    "+",
    "-"
};

const char * const gSubMenu_W_N[] =
{
    STR_GENIS,
    STR_DAR
};

const char * const gSubMenu_OFF_ON[] =
{
    STR_KAPALI,
    STR_ACIK
};

const char gSubMenu_NA[4] =
{
    "N/A"
};

const char* const gSubMenu_RXMode[] =
{
    "ANA\nTEK",       // TX and RX on main only
    "CIFT RX\nYANIT", // Watch both and respond
    "CAPRAZ\nBANT",      // TX on main, RX on secondary
    "ANA TX\nCIFT RX"  // always TX on main, but RX on both
};

#ifdef ENABLE_VOICE
    const char * const gSubMenu_VOICE[] =
    {
        STR_KAPALI,
        STR_CIN,
        STR_ING
    };
#endif

const char* const gSubMenu_MDF[] =
{
    STR_FREKANS,
    "KANAL\nNO",
    STR_ISIM,
    "ISIM\n+\nFREKANS"
};

#ifdef ENABLE_ALARM
    const char gSubMenu_AL_MOD[][5] =
    {
        "YER",
        "TON"
    };
#endif

#ifdef ENABLE_DTMF_CALLING
const char gSubMenu_D_RSP[][11] =
{
    "HICBIR\nSEY",
    "CAL",
    "YANIT",
    "IKISI"
};
#endif

const char* const gSubMenu_PTT_ID[] =
{
    STR_KAPALI,
    "YUKARI\nKOD",
    "ASAGI\nKOD",
    "YUK+ASAGI\nKOD",
    "APOLLO\nQUINDAR"
};

const char * const gSubMenu_PONMSG[] =
{
#ifdef ENABLE_FEAT_F4HWN
    STR_TUM,
    STR_SES,
#else
    STR_TUM,
#endif
    STR_MESAJ,
    STR_VOLTAJ,
    STR_YOK
};

const char * const gSubMenu_ROGER[] =
{
    STR_KAPALI,
    STR_ROGER,
    STR_MDC
};

const char * const gSubMenu_RESET[] =
{
    STR_VFO,
    STR_TUM
};

const char * const gSubMenu_F_LOCK[] =
{
    "DEFAULT+\n137-174\n400-470",
    "FCC HAM\n144-148\n420-450",
#ifdef ENABLE_FEAT_F4HWN_CA
    "CA HAM\n144-148\n430-450",
#endif
    "CE HAM\n144-146\n430-440",
    "GB HAM\n144-148\n430-440",
    "137-174\n400-430",
    "137-174\n400-438",
#ifdef ENABLE_FEAT_F4HWN_PMR
    "PMR 446",
#endif
#ifdef ENABLE_FEAT_F4HWN_GMRS_FRS_MURS
    "GMRS\nFRS\nMURS",
#endif
    "TUMUNU\nKAPAT",
    "TUMUNU\nACIK",
};

const char * const gSubMenu_RX_TX[] =
{
    STR_KAPALI,
    STR_TX,
    STR_RX,
    "TX/RX"
};

const char * const gSubMenu_BAT_TXT[] =
{
    STR_YOK,
    STR_VOLTAJ,
    STR_YUZDE
};

const char gSubMenu_BATTYP[][9] =
{
    "1600mAh",
    "2200mAh",
    "3500mAh"
};

#ifndef ENABLE_FEAT_F4HWN
const char * const gSubMenu_SCRAMBLER[] =
{
    STR_KAPALI,
    "2600Hz",
    "2700Hz",
    "2800Hz",
    "2900Hz",
    "3000Hz",
    "3100Hz",
    "3200Hz",
    "3300Hz",
    "3400Hz",
    "3500Hz"
};
#endif

#ifdef ENABLE_FEAT_F4HWN
    const char gSubMenu_SET_PWR[][6] =
    {
        "< 20m",
        "125m",
        "250m",
        "500m",
        "1",
        "2",
        "5"
    };

    const char * const gSubMenu_SET_PTT[] =
    {
        STR_KLASIK,
        "TEK BAS"
    };

    const char * const gSubMenu_SET_TOT[] =  // Use by SET_EOT too
    {
        STR_KAPALI,
        STR_SES,
        STR_GORSEL,
        STR_TUM
    };

    const char * const gSubMenu_SET_LCK[] =
    {
        STR_TUS,
        "TUS+PTT"
    };

    const char * const gSubMenu_SET_MET[] =
    {
        STR_KUCUK,
        STR_KLASIK
    };

    #ifdef ENABLE_FEAT_F4HWN_NARROWER
        const char * const gSubMenu_SET_NFM[] =
        {
            STR_DAR,
            STR_DAHADAR
        };
    #endif

    #ifdef ENABLE_FEAT_F4HWN_RESCUE_OPS
        const char gSubMenu_SET_KEY[][9] =
        {
            "KEY_MENU",
            "KEY_UP",
            "KEY_DOWN",
            "KEY_EXIT",
            "KEY_STAR"
        };
    #endif
#endif

const t_sidefunction gSubMenu_SIDEFUNCTIONS[] =
{
    {STR_YOK,          ACTION_OPT_NONE},
#ifdef ENABLE_FLASHLIGHT
    {STR_FENER,  ACTION_OPT_FLASHLIGHT},
#endif
    {STR_GUC,         ACTION_OPT_POWER},
    {STR_GOZLEM,       ACTION_OPT_MONITOR},
    {STR_TARA,          ACTION_OPT_SCAN},
#ifdef ENABLE_VOX
    {"VOX",             ACTION_OPT_VOX},
#endif
#ifdef ENABLE_ALARM
    {STR_ALARM,         ACTION_OPT_ALARM},
#endif
#ifdef ENABLE_FMRADIO
    {"FM RADYO",        ACTION_OPT_FM},
#endif
#ifdef ENABLE_TX1750
    {"1750Hz",          ACTION_OPT_1750},
#endif
#ifdef ENABLE_REGA
    {"REGA\nALARM",     ACTION_OPT_REGA_ALARM},
    {"REGA\nTEST",      ACTION_OPT_REGA_TEST},
#endif
    {STR_KILIT,  ACTION_OPT_KEYLOCK},
    {"VFO A\nVFO B",    ACTION_OPT_A_B},
    {"VFO\nKANAL",        ACTION_OPT_VFO_MR},
    {STR_MOD,           ACTION_OPT_SWITCH_DEMODUL},
#ifdef ENABLE_BLMIN_TMP_OFF
    {"BLMIN\nGEC KAP",  ACTION_OPT_BLMIN_TMP_OFF},      //BackLight Minimum Temporay OFF
#endif
#ifdef ENABLE_FEAT_F4HWN
    {"RX MODU",         ACTION_OPT_RXMODE},
    {"ANA\nTEK",       ACTION_OPT_MAINONLY},
    {STR_PTT,           ACTION_OPT_PTT},
    {"GENIS\nDAR",    ACTION_OPT_WN},
    #if !defined(ENABLE_SPECTRUM) || !defined(ENABLE_FMRADIO)
    {STR_SESSIZ,          ACTION_OPT_MUTE},
    #endif
    #ifdef ENABLE_FEAT_F4HWN_RESCUE_OPS
        {"YUKSEK\nGUC",    ACTION_OPT_POWER_HIGH},
        {"OFSETI\nKALDIR",  ACTION_OPT_REMOVE_OFFSET},
    #endif
#endif
};

const uint8_t gSubMenu_SIDEFUNCTIONS_size = ARRAY_SIZE(gSubMenu_SIDEFUNCTIONS);

bool    gIsInSubMenu;
uint8_t gMenuCursor;
int UI_MENU_GetCurrentMenuId() {
    if(gMenuCursor < ARRAY_SIZE(MenuList))
        return MenuList[gMenuCursor].menu_id;

    return MenuList[ARRAY_SIZE(MenuList)-1].menu_id;
}

uint8_t UI_MENU_GetMenuIdx(uint8_t id)
{
    for(uint8_t i = 0; i < ARRAY_SIZE(MenuList); i++)
        if(MenuList[i].menu_id == id)
            return i;
    return 0;
}

int32_t gSubMenuSelection;

// edit box
char    edit_original[17]; // a copy of the text before editing so that we can easily test for changes/difference
char    edit[17];
int     edit_index;

/* Draw one instance of a menu label at the given pixel offset, clipping to the
 * left panel.  A negative offset shifts the text left; parts falling outside
 * PanelWidth are simply not drawn. */
static void UI_PrintMenuLabelAt(const char *pString, uint8_t Line, uint8_t PanelWidth, int Offset)
{
    const uint8_t char_width = 7;
    const uint8_t char_pitch = 8;
    const size_t  len        = strlen(pString);

    for (size_t i = 0; i < len; i++)
    {
        int x = (int)(i * char_pitch) - Offset;
        if (x >= PanelWidth || x + char_width <= 0)
            continue;
        if (pString[i] <= ' ' || pString[i] >= 127)
            continue;

        const unsigned int index = pString[i] - ' ' - 1;
        int src = 0;
        int dst = x;
        int copy_width = char_width;

        if (dst < 0)
        {
            src = -dst;
            copy_width += dst;
            dst = 0;
        }
        if (dst + copy_width > PanelWidth)
            copy_width = PanelWidth - dst;
        if (copy_width <= 0)
            continue;

        memcpy(gFrameBuffer[Line + 0] + dst, &gFontBig[index][0] + src, copy_width);
        memcpy(gFrameBuffer[Line + 1] + dst, &gFontBig[index][7] + src, copy_width);
    }
}

/* Small-font label for the adjacent items in the custom menu layout.
 * Long labels are simply truncated to the number of characters that fit. */
static void UI_PrintMenuLabelSmallClip(const char *pString, uint8_t Line, uint8_t PanelWidth)
{
    const uint8_t char_pitch = 6; // small font width (5) + 1 spacing
    const size_t  max_chars  = PanelWidth / char_pitch;
    char buf[16];
    size_t len = strlen(pString);
    if (len > max_chars)
        len = max_chars;
    memcpy(buf, pString, len);
    buf[len] = '\0';
    UI_PrintStringSmallNormal(buf, 0, 0, Line);
}

/* HTML-marquee-style continuous left scroll.  The text moves steadily left,
 * disappears, then re-enters from the right after a small gap. */
static void UI_PrintMenuLabelScroll(const char *pString, uint8_t Line, uint8_t PanelWidth)
{
    const uint8_t char_pitch = 8;
    const size_t  len        = strlen(pString);
    const unsigned int total_width = len * char_pitch;

    if (total_width <= PanelWidth)
    {
        UI_PrintMenuLabelAt(pString, Line, PanelWidth, 0);
        return;
    }

    const int gap = 16;                           // blank gap before re-entry
    const int max_offset = total_width + gap;     // loop length
    const uint16_t step_period = 15;              // one pixel step every ~150 ms
    const int offset = (int)((gFlashLightBlinkCounter / step_period) % max_offset);

    // Clear the left panel area for this label first, otherwise the 1-pixel
    // character gaps and the re-entry gap leave old framebuffer pixels behind
    // and the scrolling text ghosts/overlaps with previous frames.
    memset(gFrameBuffer[Line + 0], 0, PanelWidth);
    memset(gFrameBuffer[Line + 1], 0, PanelWidth);

    UI_PrintMenuLabelAt(pString, Line, PanelWidth, offset);
    UI_PrintMenuLabelAt(pString, Line, PanelWidth, offset - total_width - gap);
}

void UI_DisplayMenu(void)
{
    const unsigned int menu_list_width = 6; // max no. of characters on the menu list (left side)
    const unsigned int menu_item_x1    = (8 * menu_list_width) + 2;
    const unsigned int menu_item_x2    = LCD_WIDTH - 1;
    unsigned int       i;
    char               String[64];  // bigger cuz we can now do multi-line in one string (use '\n' char)

#ifdef ENABLE_DTMF_CALLING
    char               Contact[16];
#endif

    UI_DisplayClear();

#ifdef ENABLE_FEAT_F4HWN
    UI_DrawLineBuffer(gFrameBuffer, 48, 0, 48, 55, 1); // Be ware, status zone = 8 lines, the rest = 56 ->total 64
    //UI_DrawLineDottedBuffer(gFrameBuffer, 0, 46, 50, 46, 1);

    for (uint8_t i = 0; i < 48; i += 2)
    {
        gFrameBuffer[5][i] = 0x40;
    }
#endif

#ifndef ENABLE_CUSTOM_MENU_LAYOUT
        // original menu layout
    for (i = 0; i < 3; i++)
        if (gMenuCursor > 0 || i > 0)
            if ((gMenuListCount - 1) != gMenuCursor || i != 2)
                UI_PrintMenuLabelScroll(MenuList[gMenuCursor + i - 1].name, i * 2, 8 * menu_list_width);

    // invert the current menu list item pixels
    for (i = 0; i < (8 * menu_list_width); i++)
    {
        gFrameBuffer[2][i] ^= 0xFF;
        gFrameBuffer[3][i] ^= 0xFF;
    }

    // draw vertical separating dotted line
    for (i = 0; i < 7; i++)
        gFrameBuffer[i][(8 * menu_list_width) + 1] = 0xAA;

    // draw the little sub-menu triangle marker
    if (gIsInSubMenu)
        memcpy(gFrameBuffer[0] + (8 * menu_list_width) + 1, BITMAP_CurrentIndicator, sizeof(BITMAP_CurrentIndicator));

    // draw the menu index number/count
    sprintf(String, "%2u.%u", 1 + gMenuCursor, gMenuListCount);

    UI_PrintStringSmallNormal(String, 2, 0, 6);

#else
    {   // new menu layout .. experimental & unfinished
        const int menu_index = gMenuCursor;  // current selected menu item
        i = 1;

        if (!gIsInSubMenu) {
            while (i < 2)
            {   // leading menu items - small text
                const int k = menu_index + i - 2;
                if (k < 0)
                    UI_PrintMenuLabelSmallClip(MenuList[gMenuListCount + k].name, i, 8 * menu_list_width);  // wrap-a-round
                else if (k >= 0 && k < (int)gMenuListCount)
                    UI_PrintMenuLabelSmallClip(MenuList[k].name, i, 8 * menu_list_width);
                i++;
            }

            // current menu item - keep big n fat
            if (menu_index >= 0 && menu_index < (int)gMenuListCount)
                UI_PrintMenuLabelScroll(MenuList[menu_index].name, 2, 8 * menu_list_width);
            i++;

            while (i < 4)
            {   // trailing menu item - small text
                const int k = menu_index + i - 2;
                if (k >= 0 && k < (int)gMenuListCount)
                    UI_PrintMenuLabelSmallClip(MenuList[k].name, 1 + i, 8 * menu_list_width);
                else if (k >= (int)gMenuListCount)
                    UI_PrintMenuLabelSmallClip(MenuList[gMenuListCount - k].name, 1 + i, 8 * menu_list_width);  // wrap-a-round
                i++;
            }

            // draw the menu index number/count
#ifndef ENABLE_FEAT_F4HWN
            sprintf(String, "%2u.%u", 1 + gMenuCursor, gMenuListCount);
            UI_PrintStringSmallNormal(String, 2, 0, 6);
#endif
        }
        else if (menu_index >= 0 && menu_index < (int)gMenuListCount)
        {   // current menu item
//          strcat(String, ":");
            UI_PrintMenuLabelScroll(MenuList[menu_index].name, 0, 8 * menu_list_width);
//          UI_PrintStringSmallNormal(String, 0, 0, 0);
        }

#ifdef ENABLE_FEAT_F4HWN
        sprintf(String, "%02u/%u", 1 + gMenuCursor, gMenuListCount);
        UI_PrintStringSmallNormal(String, 6, 0, 6);
#endif
    }
#endif

    // **************

    memset(String, 0, sizeof(String));

    bool already_printed = false;

    /* Brightness is set to max in some entries of this menu. Return it to the configured brightness
       level the "next" time we enter here.I.e., when we move from one menu to another.
       It also has to be set back to max when pressing the Exit key. */

    BACKLIGHT_TurnOn();

    #if !defined(ENABLE_SPECTRUM) || !defined(ENABLE_FMRADIO)
        uint8_t gaugeLine = 0;
        uint8_t gaugeMin = 0;
        uint8_t gaugeMax = 0;
    #endif

    switch (UI_MENU_GetCurrentMenuId())
    {
        case MENU_SQL:
            sprintf(String, "%d", gSubMenuSelection);
            break;

        case MENU_MIC:
            {   // display the mic gain in actual dB rather than just an index number
                const uint8_t mic = gMicGain_dB2[gSubMenuSelection];
                sprintf(String, "+%u.%01udB", mic / 2, mic % 2);
            }
            break;

        case MENU_MIC_BAR:
            #ifdef ENABLE_AUDIO_BAR
                strcpy(String, gSubMenu_OFF_ON[gSubMenuSelection]);
            #else
                strcpy(String, gSubMenu_NA);
            #endif
            break;

        case MENU_STEP: {
            uint16_t step = gStepFrequencyTable[FREQUENCY_GetStepIdxFromSortedIdx(gSubMenuSelection)];
            sprintf(String, "%d.%02ukHz", step / 100, step % 100);
            break;
        }

        case MENU_TXP:
            if(gSubMenuSelection == 0)
            {
                strcpy(String, gSubMenu_TXP[gSubMenuSelection]);
            }
            else if(gSubMenuSelection >= 1 && gSubMenuSelection <= 5)
            {
                sprintf(String, "DUSUK %u\n%sW", gSubMenuSelection, gSubMenu_SET_PWR[gSubMenuSelection - 1]);
            }
            else
            {
                sprintf(String, "%s\n%sW", gSubMenu_TXP[gSubMenuSelection], gSubMenu_SET_PWR[gSubMenuSelection - 1]);
            }
            break;

        case MENU_R_DCS:
        case MENU_T_DCS:
            if (gSubMenuSelection == 0)
                strcpy(String, gSubMenu_OFF_ON[0]);
            else if (gSubMenuSelection < 105)
                sprintf(String, "D%03oN", DCS_Options[gSubMenuSelection -   1]);
            else
                sprintf(String, "D%03oI", DCS_Options[gSubMenuSelection - 105]);
            break;

        case MENU_R_CTCS:
        case MENU_T_CTCS:
        {
            if (gSubMenuSelection == 0)
                strcpy(String, gSubMenu_OFF_ON[0]);
            else
                sprintf(String, "%u.%uHz", CTCSS_Options[gSubMenuSelection - 1] / 10, CTCSS_Options[gSubMenuSelection - 1] % 10);
            break;
        }

        case MENU_SFT_D:
            strcpy(String, gSubMenu_SFT_D[gSubMenuSelection]);
            break;

        case MENU_OFFSET:
            if (!gIsInSubMenu || gInputBoxIndex == 0)
            {
                sprintf(String, "%3d.%05u", gSubMenuSelection / 100000, abs(gSubMenuSelection) % 100000);
                UI_PrintString(String, menu_item_x1, menu_item_x2, 1, 8);
            }
            else
            {
                const char * ascii = INPUTBOX_GetAscii();
                sprintf(String, "%.3s.%.3s  ",ascii, ascii + 3);
                UI_PrintString(String, menu_item_x1, menu_item_x2, 1, 8);
            }

            UI_PrintString(STR_MHZ, menu_item_x1, menu_item_x2, 3, 8);

            already_printed = true;
            break;

        case MENU_W_N:
            strcpy(String, gSubMenu_W_N[gSubMenuSelection]);
            break;

#ifndef ENABLE_FEAT_F4HWN
        case MENU_SCR:
            strcpy(String, gSubMenu_SCRAMBLER[gSubMenuSelection]);
            #if 1
                if (gSubMenuSelection > 0 && gSetting_ScrambleEnable)
                    BK4819_EnableScramble(gSubMenuSelection - 1);
                else
                    BK4819_DisableScramble();
            #endif
            break;
#endif

        case MENU_VOX:
            #ifdef ENABLE_VOX
                sprintf(String, gSubMenuSelection == 0 ? gSubMenu_OFF_ON[0] : "%u", gSubMenuSelection);
            #else
                strcpy(String, gSubMenu_NA);
            #endif
            break;

        case MENU_ABR:
            if(gSubMenuSelection == 0)
            {
                strcpy(String, gSubMenu_OFF_ON[0]);
            }
            else if(gSubMenuSelection < 61)
            {
                sprintf(String, "%02dm:%02ds", (((gSubMenuSelection) * 5) / 60), (((gSubMenuSelection) * 5) % 60));
                #if !defined(ENABLE_SPECTRUM) || !defined(ENABLE_FMRADIO)
                //ST7565_Gauge(4, 1, 60, gSubMenuSelection);
                gaugeLine = 4;
                gaugeMin = 1;
                gaugeMax = 60;
                #endif
            }
            else
            {
                strcpy(String, STR_ACIK);
            }

            // Obsolete ???
            //if(BACKLIGHT_GetBrightness() < 4)
            //    BACKLIGHT_SetBrightness(4);
            break;

        case MENU_ABR_MIN:
        case MENU_ABR_MAX:
            sprintf(String, "%d", gSubMenuSelection);
            if(gIsInSubMenu)
                BACKLIGHT_SetBrightness(gSubMenuSelection);
            // Obsolete ???
            //else if(BACKLIGHT_GetBrightness() < 4)
            //    BACKLIGHT_SetBrightness(4);
            break;

        case MENU_AM:
            strcpy(String, gModulationStr[gSubMenuSelection]);
            break;

        case MENU_AUTOLK:
            if (gSubMenuSelection == 0)
                strcpy(String, gSubMenu_OFF_ON[0]);
            else
            {
                sprintf(String, "%02dm:%02ds", ((gSubMenuSelection * 15) / 60), ((gSubMenuSelection * 15) % 60));
                #if !defined(ENABLE_SPECTRUM) || !defined(ENABLE_FMRADIO)
                //ST7565_Gauge(4, 1, 40, gSubMenuSelection);
                gaugeLine = 4;
                gaugeMin = 1;
                gaugeMax = 40;
                #endif
            }
            break;

        case MENU_COMPAND:
        case MENU_ABR_ON_TX_RX:
            strcpy(String, gSubMenu_RX_TX[gSubMenuSelection]);
            break;

        #ifndef ENABLE_FEAT_F4HWN
            #ifdef ENABLE_AM_FIX
                case MENU_AM_FIX:
            #endif
        #endif
        case MENU_BCL:
        case MENU_BEEP:
        case MENU_S_ADD1:
        case MENU_S_ADD2:
        case MENU_S_ADD3:
        case MENU_STE:
        case MENU_D_ST:
#ifdef ENABLE_DTMF_CALLING
        case MENU_D_DCD:
#endif
        case MENU_D_LIVE_DEC:
        #ifdef ENABLE_NOAA
            case MENU_NOAA_S:
        #endif
#ifndef ENABLE_FEAT_F4HWN
        case MENU_350TX:
        case MENU_200TX:
        case MENU_500TX:
#endif
        case MENU_350EN:
#ifndef ENABLE_FEAT_F4HWN
        case MENU_SCREN:
#endif
#ifdef ENABLE_FEAT_F4HWN
        case MENU_SET_TMR:
#endif
            strcpy(String, gSubMenu_OFF_ON[gSubMenuSelection]);
            break;

        case MENU_MEM_CH:
        case MENU_1_CALL:
        case MENU_DEL_CH:
        {
            const bool valid = RADIO_CheckValidChannel(gSubMenuSelection, false, 0);

            UI_GenerateChannelStringEx(String, valid, gSubMenuSelection);
            UI_PrintString(String, menu_item_x1, menu_item_x2, 0, 8);

            if (valid && !gAskForConfirmation)
            {   // show the frequency so that the user knows the channels frequency
                const uint32_t frequency = SETTINGS_FetchChannelFrequency(gSubMenuSelection);
                sprintf(String, "%u.%05u", frequency / 100000, frequency % 100000);
                UI_PrintString(String, menu_item_x1, menu_item_x2, 4, 8);
            }

            SETTINGS_FetchChannelName(String, gSubMenuSelection);
            UI_PrintString(String[0] ? String : "--", menu_item_x1, menu_item_x2, 2, 8);
            already_printed = true;
            break;
        }

        case MENU_MEM_NAME:
        {
            const bool valid = RADIO_CheckValidChannel(gSubMenuSelection, false, 0);

            UI_GenerateChannelStringEx(String, valid, gSubMenuSelection);
            UI_PrintString(String, menu_item_x1, menu_item_x2, 0, 8);

            if (valid)
            {
                const uint32_t frequency = SETTINGS_FetchChannelFrequency(gSubMenuSelection);

                //if (!gIsInSubMenu || edit_index < 0)
                if (!gIsInSubMenu)
                    edit_index = -1;
                if (edit_index < 0)
                {   // show the channel name
                    SETTINGS_FetchChannelName(String, gSubMenuSelection);
                    const char *pPrintStr = String[0] ? String : "--";
                    UI_PrintString(pPrintStr, menu_item_x1, menu_item_x2, 2, 8);
                }
                else
                {   // show the channel name being edited
                    //UI_PrintString(edit, menu_item_x1, 0, 2, 8);
                    UI_PrintString(edit, menu_item_x1, menu_item_x2, 2, 8);
                    if (edit_index < 10)
                        //UI_PrintString("^", menu_item_x1 + (8 * edit_index), 0, 4, 8);  // show the cursor
                        UI_PrintString("^", menu_item_x1 - 1 + (8 * edit_index),0, 4, 8); // show the cursor
                }

                if (!gAskForConfirmation)
                {   // show the frequency so that the user knows the channels frequency
                    sprintf(String, "%u.%05u", frequency / 100000, frequency % 100000);
                    UI_PrintString(String, menu_item_x1, menu_item_x2, 4 + (gIsInSubMenu && edit_index >= 0), 8);
                }
            }

            already_printed = true;
            break;
        }

        case MENU_SAVE:
            sprintf(String, gSubMenuSelection == 0 ? gSubMenu_OFF_ON[0] : "1:%u", gSubMenuSelection);
            break;

        case MENU_TDR:
            strcpy(String, gSubMenu_RXMode[gSubMenuSelection]);
            break;

        case MENU_TOT:
            sprintf(String, "%02dm:%02ds", (((gSubMenuSelection + 1) * 5) / 60), (((gSubMenuSelection + 1) * 5) % 60));
            #if !defined(ENABLE_SPECTRUM) || !defined(ENABLE_FMRADIO)
            //ST7565_Gauge(4, 5, 179, gSubMenuSelection);
            gaugeLine = 4;
            gaugeMin = 5;
            gaugeMax = 179;
            #endif
            break;

        #ifdef ENABLE_VOICE
            case MENU_VOICE:
                strcpy(String, gSubMenu_VOICE[gSubMenuSelection]);
                break;
        #endif

        case MENU_SC_REV:
            if(gSubMenuSelection == 0)
            {
                strcpy(String, STR_DUR);
            }
            else if(gSubMenuSelection < 81)
            {
                sprintf(String, "CARRIER\n%02ds:%03dms", ((gSubMenuSelection * 250) / 1000), ((gSubMenuSelection * 250) % 1000));
                #if !defined(ENABLE_SPECTRUM) || !defined(ENABLE_FMRADIO)
                //ST7565_Gauge(5, 1, 80, gSubMenuSelection);
                gaugeLine = 5;
                gaugeMin = 1;
                gaugeMax = 80;
                #endif
            }
            else
            {
                sprintf(String, "TIMEOUT\n%02dm:%02ds", (((gSubMenuSelection - 80) * 5) / 60), (((gSubMenuSelection - 80) * 5) % 60));
                #if !defined(ENABLE_SPECTRUM) || !defined(ENABLE_FMRADIO)
                //ST7565_Gauge(5, 80, 104, gSubMenuSelection);
                gaugeLine = 5;
                gaugeMin = 80;
                gaugeMax = 104;
                #endif
            }
            break;

        case MENU_MDF:
            strcpy(String, gSubMenu_MDF[gSubMenuSelection]);
            break;

        case MENU_RP_STE:
            sprintf(String, gSubMenuSelection == 0 ? gSubMenu_OFF_ON[0] : "%u*100ms", gSubMenuSelection);
            break;

        case MENU_S_LIST:
            if (gSubMenuSelection == 0)
                strcpy(String, "LISTE [0]\nYOK");
            else if (gSubMenuSelection < 4)
                sprintf(String, "LISTE [%u]", gSubMenuSelection);
            else if (gSubMenuSelection == 4)
                strcpy(String, "LISTELER\n[1, 2, 3]");
            else if (gSubMenuSelection == 5)
                strcpy(String, STR_TUM);
            break;

        #ifdef ENABLE_ALARM
            case MENU_AL_MOD:
                sprintf(String, gSubMenu_AL_MOD[gSubMenuSelection]);
                break;
        #endif

#ifdef ENABLE_DTMF_CALLING
        case MENU_ANI_ID:
            strcpy(String, gEeprom.ANI_DTMF_ID);
            break;
#endif
        case MENU_UPCODE:
            sprintf(String, "%.8s\n%.8s", gEeprom.DTMF_UP_CODE, gEeprom.DTMF_UP_CODE + 8);
            break;

        case MENU_DWCODE:
            sprintf(String, "%.8s\n%.8s", gEeprom.DTMF_DOWN_CODE, gEeprom.DTMF_DOWN_CODE + 8);
            break;

#ifdef ENABLE_DTMF_CALLING
        case MENU_D_RSP:
            strcpy(String, gSubMenu_D_RSP[gSubMenuSelection]);
            break;

        case MENU_D_HOLD:
            sprintf(String, "%ds", gSubMenuSelection);
            break;
#endif
        case MENU_D_PRE:
            sprintf(String, "%d*10ms", gSubMenuSelection);
            break;

        case MENU_PTT_ID:
            strcpy(String, gSubMenu_PTT_ID[gSubMenuSelection]);
            break;

        case MENU_BAT_TXT:
            strcpy(String, gSubMenu_BAT_TXT[gSubMenuSelection]);
            break;

#ifdef ENABLE_DTMF_CALLING
        case MENU_D_LIST:
            gIsDtmfContactValid = DTMF_GetContact((int)gSubMenuSelection - 1, Contact);
            if (!gIsDtmfContactValid)
                strcpy(String, STR_YOK);
            else
                memcpy(String, Contact, 8);
            break;
#endif

        case MENU_PONMSG:
            strcpy(String, gSubMenu_PONMSG[gSubMenuSelection]);
            break;

        case MENU_ROGER:
            strcpy(String, gSubMenu_ROGER[gSubMenuSelection]);
            break;

        case MENU_VOL:
#ifdef ENABLE_FEAT_F4HWN
            sprintf(String, "%s\n%s",
                AUTHOR_STRING_2,
                VERSION_STRING_2
            );
#else
            sprintf(String, "%u.%02uV\n%u%%",
                gBatteryVoltageAverage / 100, gBatteryVoltageAverage % 100,
                BATTERY_VoltsToPercent(gBatteryVoltageAverage));
#endif
            break;

        case MENU_RESET:
            strcpy(String, gSubMenu_RESET[gSubMenuSelection]);
            break;

        case MENU_F_LOCK:
#ifdef ENABLE_FEAT_F4HWN
            if(!gIsInSubMenu && gUnlockAllTxConfCnt>0 && gUnlockAllTxConfCnt<3)
#else
            if(!gIsInSubMenu && gUnlockAllTxConfCnt>0 && gUnlockAllTxConfCnt<10)
#endif
                strcpy(String, STR_OKU_KLAVUZ);
            else
                strcpy(String, gSubMenu_F_LOCK[gSubMenuSelection]);
            break;

        #ifdef ENABLE_F_CAL_MENU
            case MENU_F_CALI:
                {
                    const uint32_t value   = 22656 + gSubMenuSelection;
                    const uint32_t xtal_Hz = (0x4f0000u + value) * 5;

                    writeXtalFreqCal(gSubMenuSelection, false);

                    sprintf(String, "%d\n%u.%06u\nMHz",
                        gSubMenuSelection,
                        xtal_Hz / 1000000, xtal_Hz % 1000000);
                }
                break;
        #endif

        case MENU_BATCAL:
        {
            const uint16_t vol = (uint32_t)gBatteryVoltageAverage * gBatteryCalibration[3] / gSubMenuSelection;
            sprintf(String, "%u.%02uV\n%u", vol / 100, vol % 100, gSubMenuSelection);
            break;
        }

        case MENU_BATTYP:
            strcpy(String, gSubMenu_BATTYP[gSubMenuSelection]);
            break;

        case MENU_F1SHRT:
        case MENU_F1LONG:
        case MENU_F2SHRT:
        case MENU_F2LONG:
        case MENU_MLONG:
            strcpy(String, gSubMenu_SIDEFUNCTIONS[gSubMenuSelection].name);
            break;

#ifdef ENABLE_FEAT_F4HWN_SLEEP
        case MENU_SET_OFF:
            if(gSubMenuSelection == 0)
            {
                strcpy(String, gSubMenu_OFF_ON[0]);
            }
            else if(gSubMenuSelection < 121)
            {
                sprintf(String, "%dh:%02dm", (gSubMenuSelection / 60), (gSubMenuSelection % 60));
                #if !defined(ENABLE_SPECTRUM) || !defined(ENABLE_FMRADIO)
                //ST7565_Gauge(4, 1, 120, gSubMenuSelection);
                gaugeLine = 4;
                gaugeMin = 1;
                gaugeMax = 120;
                #endif
            }
            break;
#endif

#ifdef ENABLE_FEAT_F4HWN
        case MENU_SET_PWR:
            if(gSubMenuSelection >= 0 && gSubMenuSelection <= 4)
            {
                sprintf(String, "DUSUK %u\n%sW", gSubMenuSelection + 1, gSubMenu_SET_PWR[gSubMenuSelection]);
            }
            else
            {
                sprintf(String, "%s\n%sW", gSubMenu_TXP[gSubMenuSelection + 1], gSubMenu_SET_PWR[gSubMenuSelection]);
            }
            break;
    
        case MENU_SET_PTT:
            strcpy(String, gSubMenu_SET_PTT[gSubMenuSelection]);
            break;

        case MENU_SET_TOT:
        case MENU_SET_EOT:
            strcpy(String, gSubMenu_SET_TOT[gSubMenuSelection]); // Same as SET_TOT
            break;

        case MENU_SET_CTR:
            #ifdef ENABLE_FEAT_F4HWN_CTR
                sprintf(String, "%d", gSubMenuSelection);
                gSetting_set_ctr = gSubMenuSelection;
                ST7565_ContrastAndInv();
            #else
                strcpy(String, gSubMenu_NA);
            #endif
            break;

        case MENU_SET_INV:
            #ifdef ENABLE_FEAT_F4HWN_INV
                strcpy(String, gSubMenu_OFF_ON[gSubMenuSelection]);
                ST7565_ContrastAndInv();
            #else
                strcpy(String, gSubMenu_NA);
            #endif
            break;

        case MENU_TX_LOCK:
            if(TX_freq_check(gEeprom.VfoInfo[gEeprom.TX_VFO].pTX->Frequency) == 0)
            {
                strcpy(String, "FKilit\nPlaninda");
            }
            else
            {
                strcpy(String, gSubMenu_OFF_ON[gSubMenuSelection]);
            }
            break;

        case MENU_SET_LCK:
            strcpy(String, gSubMenu_SET_LCK[gSubMenuSelection]);
            break;

        case MENU_SET_MET:
        case MENU_SET_GUI:
            strcpy(String, gSubMenu_SET_MET[gSubMenuSelection]); // Same as SET_MET
            break;

        #ifdef ENABLE_FEAT_F4HWN_NARROWER
            case MENU_SET_NFM:
                strcpy(String, gSubMenu_SET_NFM[gSubMenuSelection]);
                break;
        #endif

        #ifdef ENABLE_FEAT_F4HWN_VOL
            case MENU_SET_VOL:
                if(gSubMenuSelection == 0)
                {
                    strcpy(String, gSubMenu_OFF_ON[0]);
                }
                else if(gSubMenuSelection < 64)
                {
                    sprintf(String, "%02u", gSubMenuSelection);
                    #if !defined(ENABLE_SPECTRUM) || !defined(ENABLE_FMRADIO)
                    //ST7565_Gauge(4, 1, 63, gSubMenuSelection);
                    gaugeLine = 4;
                    gaugeMin = 1;
                    gaugeMax = 63;
                    #endif
                }
                gEeprom.VOLUME_GAIN = gSubMenuSelection;
                BK4819_WriteRegister(BK4819_REG_48,
                    (11u << 12)                |     // ??? .. 0 ~ 15, doesn't seem to make any difference
                    ( 0u << 10)                |     // AF Rx Gain-1
                    (gEeprom.VOLUME_GAIN << 4) |     // AF Rx Gain-2
                    (gEeprom.DAC_GAIN    << 0));     // AF DAC Gain (after Gain-1 and Gain-2)
                break;
        #endif

        #ifdef ENABLE_FEAT_F4HWN_RESCUE_OPS
            case MENU_SET_KEY:
                strcpy(String, gSubMenu_SET_KEY[gSubMenuSelection]);
                break;                
        #endif
#endif

    }

    #if !defined(ENABLE_SPECTRUM) || !defined(ENABLE_FMRADIO)
    if(gaugeLine != 0)
    {
        ST7565_Gauge(gaugeLine, gaugeMin, gaugeMax, gSubMenuSelection);
    }
    #endif

    if (!already_printed)
    {   // we now do multi-line text in a single string

        unsigned int y;
        unsigned int lines = 1;
        unsigned int len   = strlen(String);
        bool         small = false;

        if (len > 0)
        {
            // count number of lines
            for (i = 0; i < len; i++)
            {
                if (String[i] == '\n' && i < (len - 1))
                {   // found new line char
                    lines++;
                    String[i] = 0;  // null terminate the line
                }
            }

            if (lines > 3)
            {   // use small text
                small = true;
                if (lines > 7)
                    lines = 7;
            }

            // center vertically'ish
            /*
            if (small)
                y = 3 - ((lines + 0) / 2);  // untested
            else
                y = 2 - ((lines + 0) / 2);
            */

            y = (small ? 3 : 2) - (lines / 2); 

            // only for SysInf
            if(UI_MENU_GetCurrentMenuId() == MENU_VOL)
            {
                sprintf(edit, "%u.%02uV %u%%",
                    gBatteryVoltageAverage / 100, gBatteryVoltageAverage % 100,
                    BATTERY_VoltsToPercent(gBatteryVoltageAverage)
                );

                UI_PrintStringSmallNormal(edit, 54, 127, 1);

                #ifdef ENABLE_FEAT_F4HWN
                    UI_PrintStringSmallNormal(Edition, 54, 127, 6);
                #endif

                y = 2;
            }

            // draw the text lines
            for (i = 0; i < len && lines > 0; lines--)
            {
                if (small)
                    UI_PrintStringSmallNormal(String + i, menu_item_x1, menu_item_x2, y);
                else
                    UI_PrintString(String + i, menu_item_x1, menu_item_x2, y, 8);

                // look for start of next line
                while (i < len && String[i] >= 32)
                    i++;

                // hop over the null term char(s)
                while (i < len && String[i] < 32)
                    i++;

                y += small ? 1 : 2;
            }
        }
    }

    if (UI_MENU_GetCurrentMenuId() == MENU_SLIST1 || UI_MENU_GetCurrentMenuId() == MENU_SLIST2 || UI_MENU_GetCurrentMenuId() == MENU_SLIST3)
    {
        i = UI_MENU_GetCurrentMenuId() - MENU_SLIST1;

        const char *pPrintStr = String;

        if (gSubMenuSelection < 0) {
            pPrintStr = STR_YOK;
        } else {
            UI_GenerateChannelStringEx(String, true, gSubMenuSelection);
            pPrintStr = String;
        }

        // channel number
        UI_PrintString(pPrintStr, menu_item_x1, menu_item_x2, 0, 8);

        SETTINGS_FetchChannelName(String, gSubMenuSelection);
        pPrintStr = String[0] ? String : "--";

        // channel name and scan-list
        if (gSubMenuSelection < 0 || !gEeprom.SCAN_LIST_ENABLED[i]) {
            UI_PrintString(pPrintStr, menu_item_x1, menu_item_x2, 2, 8);
        } else {
            /*
            UI_PrintStringSmallNormal(pPrintStr, menu_item_x1, menu_item_x2, 2);

            if (IS_MR_CHANNEL(gEeprom.SCANLIST_PRIORITY_CH1[i])) {
                sprintf(String, "PRI%d:%u", 1, gEeprom.SCANLIST_PRIORITY_CH1[i] + 1);
                UI_PrintString(String, menu_item_x1, menu_item_x2, 3, 8);
            }

            if (IS_MR_CHANNEL(gEeprom.SCANLIST_PRIORITY_CH2[i])) {
                sprintf(String, "PRI%d:%u", 2, gEeprom.SCANLIST_PRIORITY_CH2[i] + 1);
                UI_PrintString(String, menu_item_x1, menu_item_x2, 5, 8);
            }
            */

            UI_PrintStringSmallNormal(pPrintStr, menu_item_x1, menu_item_x2, 2);

            for (uint8_t pri = 1; pri <= 2; pri++) {
                uint8_t channel = (pri == 1) ? gEeprom.SCANLIST_PRIORITY_CH1[i] : gEeprom.SCANLIST_PRIORITY_CH2[i];

                if (IS_MR_CHANNEL(channel)) {
                    sprintf(String, "PRI%d:%u", pri, channel + 1);
                    UI_PrintString(String, menu_item_x1, menu_item_x2, pri * 2 + 1, 8);
                }
            }

        }
    }

    if ((UI_MENU_GetCurrentMenuId() == MENU_R_CTCS || UI_MENU_GetCurrentMenuId() == MENU_R_DCS) && gCssBackgroundScan)
        UI_PrintString(STR_TARA, menu_item_x1, menu_item_x2, 4, 8);

#ifdef ENABLE_DTMF_CALLING
    if (UI_MENU_GetCurrentMenuId() == MENU_D_LIST && gIsDtmfContactValid) {
        Contact[11] = 0;
        memcpy(&gDTMF_ID, Contact + 8, 4);
        sprintf(String, "ID:%4s", gDTMF_ID);
        UI_PrintString(String, menu_item_x1, menu_item_x2, 4, 8);
    }
#endif

    if (UI_MENU_GetCurrentMenuId() == MENU_R_CTCS ||
        UI_MENU_GetCurrentMenuId() == MENU_T_CTCS ||
        UI_MENU_GetCurrentMenuId() == MENU_R_DCS  ||
        UI_MENU_GetCurrentMenuId() == MENU_T_DCS
#ifdef ENABLE_DTMF_CALLING
        || UI_MENU_GetCurrentMenuId() == MENU_D_LIST
#endif
    ) {
        sprintf(String, "%2d", gSubMenuSelection);
        UI_PrintStringSmallNormal(String, 105, 0, 0);
    }

    if ((UI_MENU_GetCurrentMenuId() == MENU_RESET    ||
         UI_MENU_GetCurrentMenuId() == MENU_MEM_CH   ||
         UI_MENU_GetCurrentMenuId() == MENU_MEM_NAME ||
         UI_MENU_GetCurrentMenuId() == MENU_DEL_CH) && gAskForConfirmation)
    {   // display confirmation
        const char *pPrintStr = (gAskForConfirmation == 1) ? "EMIN?" : "BEKLE!";
        UI_PrintString(pPrintStr, menu_item_x1, menu_item_x2, 5, 8);
    }

    ST7565_BlitFullScreen();
}