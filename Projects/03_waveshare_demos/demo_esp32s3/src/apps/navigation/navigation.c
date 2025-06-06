// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.2
// LVGL version: 8.3.6
// Project name: nav

/*
    Copyright (c) 2024 Felix Biego. All rights reserved.
    This work is licensed under the terms of the MIT license.
    For a copy, see <https://opensource.org/licenses/MIT>.
*/

#include "navigation.h"

#ifdef ENABLE_APP_NAVIGATION

#define CANVAS_WIDTH 48
#define CANVAS_HEIGHT 48

REGISTER_APP("Navigation", &ui_img_arrow_png, ui_navScreen, ui_navScreen_screen_init);

lv_obj_t *ui_navPanel;
lv_obj_t *ui_navDirection;
lv_obj_t *ui_navText;
lv_obj_t *ui_navDistance;
lv_obj_t *ui_navIconCanvas;
lv_obj_t *ui_navIcon;
lv_obj_t *ui_navTitle;

void ui_event_navScreen(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_SCREEN_LOAD_START)
    {
    }
    if (event_code == LV_EVENT_SCREEN_LOADED)
    {
        onGameOpened();
    }
    // if (event_code == LV_EVENT_SCREEN_UNLOAD_START)
    // {
    //     qmi8658c_active = false;
    // }
    if (event_code == LV_EVENT_SCREEN_UNLOADED)
    {
        onGameClosed();
    }

    if (event_code == LV_EVENT_GESTURE && lv_indev_get_gesture_dir(lv_indev_active()) == LV_DIR_RIGHT)
    {
        ui_app_exit();
    }
}

void ui_navScreen_screen_init()
{

    ui_navScreen = lv_obj_create(NULL);
    lv_obj_remove_flag(ui_navScreen, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(ui_navScreen, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_navScreen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_navPanel = lv_obj_create(ui_navScreen);
    lv_obj_set_width(ui_navPanel, 240);
    lv_obj_set_height(ui_navPanel, 240);
    lv_obj_set_align(ui_navPanel, LV_ALIGN_CENTER);
    lv_obj_remove_flag(ui_navPanel, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_radius(ui_navPanel, 120, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_navPanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_navPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_navPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_navDirection = lv_label_create(ui_navPanel);
    lv_obj_set_width(ui_navDirection, 180);
    lv_obj_set_height(ui_navDirection, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_navDirection, 0);
    lv_obj_set_y(ui_navDirection, 156);
    lv_obj_set_align(ui_navDirection, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_navDirection, "Available on v3.7.5+");
    lv_obj_set_style_text_align(ui_navDirection, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_navDirection, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_navText = lv_label_create(ui_navPanel);
    lv_obj_set_width(ui_navText, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_navText, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_navText, 0);
    lv_obj_set_y(ui_navText, 21);
    lv_obj_set_align(ui_navText, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_navText, "Navigation\nESP32 only");
    lv_obj_set_style_text_align(ui_navText, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_navText, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_navDistance = lv_label_create(ui_navPanel);
    lv_obj_set_width(ui_navDistance, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_navDistance, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_navDistance, 0);
    lv_obj_set_y(ui_navDistance, 121);
    lv_obj_set_align(ui_navDistance, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_navDistance, "Chronos");
    lv_obj_set_style_text_font(ui_navDistance, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);

    LV_DRAW_BUF_DEFINE_STATIC(cbuf, CANVAS_WIDTH, CANVAS_HEIGHT, LV_COLOR_FORMAT_I2);
    LV_DRAW_BUF_INIT_STATIC(cbuf);

    ui_navIconCanvas = lv_canvas_create(ui_navPanel);
    lv_canvas_set_draw_buf(ui_navIconCanvas, &cbuf);
    lv_obj_set_width(ui_navIconCanvas, 48);
    lv_obj_set_height(ui_navIconCanvas, 48);
    lv_obj_set_x(ui_navIconCanvas, 0);
    lv_obj_set_y(ui_navIconCanvas, 68);
    lv_obj_set_align(ui_navIconCanvas, LV_ALIGN_TOP_MID);
    lv_obj_remove_flag(ui_navIconCanvas, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_radius(ui_navIconCanvas, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_navIconCanvas, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_navIconCanvas, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_navIconCanvas, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_canvas_fill_bg(ui_navIconCanvas, lv_color_black(), LV_OPA_COVER);
    lv_canvas_set_palette(ui_navIconCanvas, 0, lv_color32_make(0, 0, 0, 255));
    lv_canvas_set_palette(ui_navIconCanvas, 1, lv_color32_make(255, 255, 255, 255));

    ui_navIcon = lv_image_create(ui_navPanel);
    lv_image_set_src(ui_navIcon, &ui_img_chronos_logo_png);
    lv_obj_set_width(ui_navIcon, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_navIcon, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_navIcon, 0);
    lv_obj_set_y(ui_navIcon, 68);
    lv_obj_set_align(ui_navIcon, LV_ALIGN_TOP_MID);
    lv_obj_remove_flag(ui_navIcon, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    // ui_navTitle = lv_label_create(ui_navPanel);
    // lv_obj_set_width(ui_navTitle, LV_SIZE_CONTENT);  /// 1
    // lv_obj_set_height(ui_navTitle, LV_SIZE_CONTENT); /// 1
    // lv_obj_set_align(ui_navTitle, LV_ALIGN_TOP_MID);
    // lv_label_set_text(ui_navTitle, "Navigation");
    // lv_obj_set_style_text_align(ui_navTitle, LV_TEXT_ALIGN_AUTO, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_text_decor(ui_navTitle, LV_TEXT_DECOR_UNDERLINE, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_text_font(ui_navTitle, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_navScreen, ui_event_navScreen, LV_EVENT_ALL, NULL);

}

#endif

void navigateInfo(const char *text, const char *title, const char *directions)
{
#ifdef ENABLE_APP_NAVIGATION
    if (!ui_navScreen){
        return;
    }
    lv_label_set_text(ui_navText, text);
    lv_label_set_text(ui_navDirection, directions);
    lv_label_set_text(ui_navDistance, title);

#endif
}

void navIconState(bool show)
{
#ifdef ENABLE_APP_NAVIGATION
    if (!ui_navScreen){
        return;
    }
    if (show)
    {
        lv_obj_remove_flag(ui_navIconCanvas, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_navIcon, LV_OBJ_FLAG_HIDDEN);
    }
    else
    {
        lv_obj_add_flag(ui_navIconCanvas, LV_OBJ_FLAG_HIDDEN);
        lv_obj_remove_flag(ui_navIcon, LV_OBJ_FLAG_HIDDEN);
    }
#endif
}

void setNavIconPx(uint16_t x, uint16_t y, bool on)
{
#ifdef ENABLE_APP_NAVIGATION
    if (!ui_navScreen){
        return;
    }
    if (on)
    {

        lv_canvas_set_px(ui_navIconCanvas, x, y, lv_color_make(255, 255, 255), LV_OPA_COVER);
    }
    else
    {
        lv_canvas_set_px(ui_navIconCanvas, x, y, lv_color_make(0, 0, 0), LV_OPA_COVER);
    }
#endif
}

lv_obj_t *get_nav_screen(void)
{
#ifdef ENABLE_APP_NAVIGATION
    return ui_navScreen;
#else
    return NULL;
#endif
}
