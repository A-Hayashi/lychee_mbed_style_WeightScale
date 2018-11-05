
#ifndef EASY_ATTACH_CAMERA_AND_LCD_H
#define EASY_ATTACH_CAMERA_AND_LCD_H

#include "DisplayBace.h"

// camera
#if MBED_CONF_APP_CAMERA
  // camera-type
  #define CAMERA_CVBS                 1
  #define CAMERA_MT9V111              2
  #define CAMERA_OV7725               3
  #define CAMERA_OV5642               4
  #define CAMERA_WIRELESS_CAMERA      0x83

  // shield-type
  #define SHIELD_AUDIO_CAMERA         1
  #define SHIELD_WIRELESS_CAMERA      2

  // camera module
  #define MODULE_VDC                  0
  #define MODULE_CEU                  1

  #define CAMERA_MODULE               MODULE_VDC

  #ifndef MBED_CONF_APP_SHIELD_TYPE
    #if defined(TARGET_RZ_A1H)
      #if (MBED_CONF_APP_CAMERA_TYPE == CAMERA_WIRELESS_CAMERA)
        #define MBED_CONF_APP_SHIELD_TYPE  SHIELD_WIRELESS_CAMERA
        #undef  MBED_CONF_APP_CAMERA_TYPE
        #define MBED_CONF_APP_CAMERA_TYPE  CAMERA_OV7725
      #else
        #define MBED_CONF_APP_SHIELD_TYPE  SHIELD_AUDIO_CAMERA
      #endif
    #endif
  #endif

  #ifndef MBED_CONF_APP_CAMERA_TYPE
    #if defined(TARGET_GR_LYCHEE)
      #define MBED_CONF_APP_CAMERA_TYPE    CAMERA_OV7725
    #else
      #define MBED_CONF_APP_CAMERA_TYPE    CAMERA_MT9V111
    #endif
  #endif

  #if (MBED_CONF_APP_CAMERA_TYPE == CAMERA_CVBS) && defined(TARGET_GR_LYCHEE)
    #error "MBED_CONF_APP_CAMERA_TYPE is not supported in this target."
  #endif

  #if MBED_CONF_APP_CAMERA_TYPE == CAMERA_MT9V111
    #include "MT9V111_config.h"
  #elif MBED_CONF_APP_CAMERA_TYPE == CAMERA_OV7725
    #include "OV7725_config.h"
  #elif MBED_CONF_APP_CAMERA_TYPE == CAMERA_OV5642
    #include "OV5642_config.h"
  #endif
#endif

// lcd
#if MBED_CONF_APP_LCD
  // lcd-type
  #define GR_PEACH_4_3INCH_SHIELD     0x0000
  #define GR_PEACH_7_1INCH_SHIELD     0x0001
  #define GR_PEACH_RSK_TFT            0x0002
  #define GR_PEACH_DISPLAY_SHIELD     0x0100
  #define GR_LYCHEE_TF043HV001A0      0x1000
  #define GR_LYCHEE_ATM0430D25        0x1001
  #define GR_LYCHEE_FG040346DSSWBG03  0x1002

  #define GR_LYCHEE_LCD               GR_LYCHEE_TF043HV001A0

  #ifndef MBED_CONF_APP_LCD_TYPE
    #if defined(TARGET_RZ_A1H)
      #define MBED_CONF_APP_LCD_TYPE    GR_PEACH_4_3INCH_SHIELD
    #elif defined(TARGET_GR_LYCHEE)
      #define MBED_CONF_APP_LCD_TYPE    GR_LYCHEE_LCD
    #endif
  #endif

  #if defined(TARGET_RZ_A1H) && ((MBED_CONF_APP_LCD_TYPE & 0xF000) != 0x0000)
    #error "MBED_CONF_APP_LCD_TYPE is not supported in this target."
  #endif
  #if defined(TARGET_GR_LYCHEE) && ((MBED_CONF_APP_LCD_TYPE & 0xF000) != 0x1000)
    #error "MBED_CONF_APP_LCD_TYPE is not supported in this target."
  #endif

  #if MBED_CONF_APP_LCD_TYPE == GR_PEACH_4_3INCH_SHIELD
    #include "LCD_shield_config_4_3inch.h"
  #elif MBED_CONF_APP_LCD_TYPE == GR_PEACH_7_1INCH_SHIELD
    #include "LCD_shield_config_7_1inch.h"
  #elif MBED_CONF_APP_LCD_TYPE == GR_PEACH_RSK_TFT
    #include "LCD_shield_config_RSK_TFT.h"
  #elif MBED_CONF_APP_LCD_TYPE == GR_PEACH_DISPLAY_SHIELD
    #include "Display_shield_config.h"
  #elif MBED_CONF_APP_LCD_TYPE == GR_LYCHEE_TF043HV001A0
    #include "LCD_config_TF043HV001A0.h"
  #elif MBED_CONF_APP_LCD_TYPE == GR_LYCHEE_ATM0430D25
    #include "LCD_config_ATM0430D25.h"
  #elif MBED_CONF_APP_LCD_TYPE == GR_LYCHEE_FG040346DSSWBG03
    #include "LCD_config_FG040346DSSWBG03.h"
  #else
    #error "No lcd chosen. Please add 'config.lcd-type.value' to your mbed_app.json (see README.md for more information)."
  #endif
#endif

extern DisplayBase::graphics_error_t EasyAttach_Init(
    DisplayBase& Display,
    uint16_t cap_width = 0,
    uint16_t cap_height = 0
);

extern DisplayBase::graphics_error_t EasyAttach_CameraStart(
    DisplayBase& Display,
    DisplayBase::video_input_channel_t channel = DisplayBase::VIDEO_INPUT_CHANNEL_0
);

extern void EasyAttach_SetTypicalBacklightVol(float typ_vol);

extern void EasyAttach_LcdBacklight(bool type = true);

extern void EasyAttach_LcdBacklight(float value);

#endif
