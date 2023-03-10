/* MD5: bd520f1fad71abab5dfee001cd5b1d19*/
#if !defined(__PRODUCT_CONFIG_AUDIO_H__)
#define __PRODUCT_CONFIG_AUDIO_H__

#ifndef TENSILICA_BUILDS_HIFI
#define TENSILICA_BUILDS_HIFI "$(ROOT_XTENSA_PATH_W)/XtDevTools/install/builds/RE-2014.5-linux" 
#endif 

#ifndef TENSILICA_TOOLS_HIFI
#define TENSILICA_TOOLS_HIFI "$(ROOT_XTENSA_PATH_W)/XtDevTools/install/tools/RE-2014.5-linux" 
#endif 

#ifndef FEATURE_HIFI
#define FEATURE_HIFI FEATURE_ON 
#endif 

#ifndef FEATURE_HIFI_USE_ICC
#define FEATURE_HIFI_USE_ICC FEATURE_ON 
#endif 

#ifndef FEATURE_MBB_MODULE_AUDIO
#define FEATURE_MBB_MODULE_AUDIO FEATURE_OFF 
#endif 

#ifndef FEATURE_VOICE_UP
#define FEATURE_VOICE_UP FEATURE_OFF 
#endif 

#ifndef PLATFORM_CHIP_TYPE
#define PLATFORM_CHIP_TYPE hi3660 
#endif 

#endif /*__PRODUCT_CONFIG_H__*/ 
