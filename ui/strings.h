#ifndef UI_STRINGS_H
#define UI_STRINGS_H

/* Centralised Turkish UI strings.
 * All strings are 7-bit ASCII replacements because the built-in font does not
 * support Turkish glyphs.  These constants are shared by every screen that
 * needs the same word, so translations stay consistent and duplicated ROM
 * strings are avoided where possible. */

/* On / off and common states */
extern const char STR_ACIK[];
extern const char STR_KAPALI[];
extern const char STR_YOK[];
extern const char STR_TUM[];
extern const char STR_DUR[];

/* Actions / modes that appear in several screens */
extern const char STR_TARA[];
extern const char STR_GUC[];
extern const char STR_MOD[];
extern const char STR_PTT[];
extern const char STR_VFO[];
extern const char STR_RX[];
extern const char STR_TX[];
extern const char STR_FM[];
extern const char STR_DTMF[];
extern const char STR_KILIT[];
extern const char STR_GOZLEM[];
extern const char STR_KARIS[];
extern const char STR_FENER[];
extern const char STR_ALARM[];
extern const char STR_SESSIZ[];
extern const char STR_BIP[];

/* Power and bandwidth */
extern const char STR_DUSUK[];
extern const char STR_ORTA[];
extern const char STR_YUKSEK[];
extern const char STR_GENIS[];
extern const char STR_DAR[];
extern const char STR_DAR_PLUS[];

/* Menu option words used by more than one submenu */
extern const char STR_SES[];
extern const char STR_GORSEL[];
extern const char STR_TUS[];
extern const char STR_KLASIK[];
extern const char STR_KUCUK[];
extern const char STR_DAHADAR[];
extern const char STR_LISTE[];
extern const char STR_MESAJ[];
extern const char STR_VOLTAJ[];
extern const char STR_YUZDE[];
extern const char STR_ROGER[];
extern const char STR_MDC[];
extern const char STR_CIN[];
extern const char STR_ING[];
extern const char STR_ISIM[];
extern const char STR_FREKANS[];
extern const char STR_KANAL[];

/* Main-screen / other UI labels */
extern const char STR_ARALIK[];
extern const char STR_EL_TARA[];
extern const char STR_KAYDET[];
extern const char STR_SIL[];
extern const char STR_HOSGELDIN[];
extern const char STR_BIRAK[];
extern const char STR_TUM_TUSLARI[];
extern const char STR_PIL_DUSUK[];
extern const char STR_TX_KAPALI[];
extern const char STR_SURE_DOLDU[];
extern const char STR_VOLTAJ_YUKSEK[];
extern const char STR_MESGUL[];
extern const char STR_KILIT_AC[];
extern const char STR_KILIDI_AC[];
extern const char STR_CIKIS_BAS[];
extern const char STR_SIFRE[];
extern const char STR_MHZ[];
extern const char STR_OKU_KLAVUZ[];

#endif
