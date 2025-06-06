#ifndef DRIVER_H
#define DRIVER_H

#if SDL_VER_RES == 240

#define ENABLE_FACE_ELECROW // elecrow analog
#define ENABLE_FACE_34_2 // (Shadow) 
#define ENABLE_FACE_75_2 // (Analog)
#define ENABLE_FACE_79_2 // (Blue)
#define ENABLE_FACE_116_ // (Outline)
#define ENABLE_FACE_756_2 // (Red)
#define ENABLE_FACE_B_W_RESIZED // (B & W)
#define ENABLE_FACE_KENYA // (Kenya)
#define ENABLE_FACE_PIXEL_RESIZED // (Pixel)
#define ENABLE_FACE_RADAR // (Radar)
#define ENABLE_FACE_SMART_RESIZED // (Smart)
#define ENABLE_FACE_TIX_RESIZED // (Tix)
#define ENABLE_FACE_WFB_RESIZED // (WFB)

#endif

#if SDL_VER_RES == 280

#define ENABLE_FACE_174 // (174)
#define ENABLE_FACE_228 // (228)
#define ENABLE_FACE_1041 // (1041)
#define ENABLE_FACE_1167 // (1167)
#define ENABLE_FACE_1169 // (1169)
#define ENABLE_FACE_2051 // (2051)
#define ENABLE_FACE_2151 // (2151)
#define ENABLE_FACE_3589 // (3589)

#endif

#define ENABLE_GAME_RACING
#define ENABLE_GAME_SIMON

#define ENABLE_APP_CALENDAR
#define ENABLE_APP_SAMPLE
// #define ENABLE_APP_QMI8658C
#define ENABLE_APP_NAVIGATION
#define ENABLE_APP_CONTACTS
#define ENABLE_APP_TIMER

#ifdef __cplusplus
extern "C" {
#endif


void hal_setup(void);
void hal_loop(void);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*DRIVER_H*/
