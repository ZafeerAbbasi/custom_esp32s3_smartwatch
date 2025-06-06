// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.2
// LVGL version: 9.1.0
// Project name: lv_9_16bit

#include "timer.h"

#ifdef ENABLE_APP_TIMER


REGISTER_APP("Timer", &ui_img_timer_png, ui_timerScreen, timer_screen_init);

static lv_obj_t *ui_timerScreen;
static lv_obj_t *ui_customTimer;
static lv_obj_t *ui_minLabel;
static lv_obj_t *ui_minutesRoller;
static lv_obj_t *ui_secLabel;
static lv_obj_t *ui_secondsRoller;
static lv_obj_t *ui_startCustom;
static lv_obj_t *ui_timerText;
static lv_obj_t *ui_customLabel;
static lv_obj_t *ui_runningTimer;
static lv_obj_t *ui_timerinfo;
static lv_obj_t *ui_arcTimer;
static lv_obj_t *ui_startCustom1;
static lv_obj_t *ui_customLabel1;

static const char *time_59 = "0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25\n26\n27\n28\n29\n30\n31\n32\n33\n34\n35\n36\n37\n38\n39\n40\n41\n42\n43\n44\n45\n46\n47\n48\n49\n50\n51\n52\n53\n54\n55\n56\n57\n58\n59";

static int minutes = 0;
static int seconds = 0;
static int rem_time = 0;

lv_timer_t *time_timer = NULL;

void ui_event_timerScreen(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_SCREEN_LOAD_START)
    {

        if (time_timer != NULL)
        {
            lv_obj_add_flag(ui_customTimer, LV_OBJ_FLAG_HIDDEN);
            lv_obj_remove_flag(ui_runningTimer, LV_OBJ_FLAG_HIDDEN);
        }
        else
        {
            lv_obj_remove_flag(ui_customTimer, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(ui_runningTimer, LV_OBJ_FLAG_HIDDEN);
        }
    }
    if (event_code == LV_EVENT_SCREEN_LOADED)
    {
        // onGameOpened();
    }
    if (event_code == LV_EVENT_SCREEN_UNLOAD_START)
    {
    }
    if (event_code == LV_EVENT_SCREEN_UNLOADED)
    {
        onGameClosed();
    }

    if (event_code == LV_EVENT_GESTURE && lv_indev_get_gesture_dir(lv_indev_active()) == LV_DIR_RIGHT)
    {
        ui_app_exit();
    }
}

void time_timer_cb(lv_timer_t *t)
{

    rem_time--;
    lv_label_set_text_fmt(ui_timerinfo, "%02d:%02d", rem_time / 60, rem_time % 60);
    lv_arc_set_value(ui_arcTimer, rem_time);

    if (rem_time <= 0)
    {
        lv_obj_remove_flag(ui_timerText, LV_OBJ_FLAG_HIDDEN);
        lv_label_set_text(ui_customLabel1, "Close");
        if (time_timer != NULL)
        {
            lv_timer_delete(time_timer);
            time_timer = NULL;
        }

        if (ui_timerScreen != lv_screen_active()){
            showError("Timer", "Timer has ended");
        }

        timerEnded(0);
        onGameClosed();
    }
}

void start_timer_event(lv_event_t *e)
{
    minutes = lv_roller_get_selected(ui_minutesRoller);
    seconds = lv_roller_get_selected(ui_secondsRoller);

    rem_time = (minutes * 60) + seconds;

    if (rem_time)
    {
        onGameOpened();

        lv_arc_set_range(ui_arcTimer, 0, rem_time);
        lv_arc_set_value(ui_arcTimer, rem_time);
        lv_label_set_text(ui_customLabel1, "Stop");
        lv_obj_add_flag(ui_timerText, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_customTimer, LV_OBJ_FLAG_HIDDEN);
        lv_obj_remove_flag(ui_runningTimer, LV_OBJ_FLAG_HIDDEN);

        lv_label_set_text_fmt(ui_timerinfo, "%02d:%02d", minutes, seconds);

        time_timer = lv_timer_create(time_timer_cb, 1000, NULL);
        lv_timer_set_repeat_count(time_timer, rem_time);
    }
}

void stop_timer_event(lv_event_t *e)
{
    lv_obj_add_flag(ui_runningTimer, LV_OBJ_FLAG_HIDDEN);
    lv_obj_remove_flag(ui_customTimer, LV_OBJ_FLAG_HIDDEN);

    if (time_timer != NULL)
    {
        lv_timer_delete(time_timer);
        time_timer = NULL;
    }
    onGameClosed();
}



void timer_screen_init()
{
    ui_timerScreen = lv_obj_create(NULL);
    lv_obj_remove_flag(ui_timerScreen, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(ui_timerScreen, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_timerScreen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_customTimer = lv_obj_create(ui_timerScreen);
    lv_obj_remove_style_all(ui_customTimer);
    lv_obj_set_width(ui_customTimer, 240);
    lv_obj_set_height(ui_customTimer, 240);
    lv_obj_set_align(ui_customTimer, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_customTimer, LV_OBJ_FLAG_HIDDEN);                                /// Flags
    lv_obj_remove_flag(ui_customTimer, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(ui_customTimer, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_customTimer, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_minLabel = lv_label_create(ui_customTimer);
    lv_obj_set_width(ui_minLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_minLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_minLabel, -38);
    lv_obj_set_y(ui_minLabel, -95);
    lv_obj_set_align(ui_minLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_minLabel, "Min");
    lv_obj_set_style_text_color(ui_minLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_minLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_minLabel, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_minutesRoller = lv_roller_create(ui_customTimer);
    lv_roller_set_options(ui_minutesRoller, time_59, LV_ROLLER_MODE_INFINITE);
    lv_obj_set_height(ui_minutesRoller, 135);
    lv_obj_set_width(ui_minutesRoller, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_minutesRoller, -40);
    lv_obj_set_y(ui_minutesRoller, -15);
    lv_obj_set_align(ui_minutesRoller, LV_ALIGN_CENTER);
    lv_obj_set_style_text_color(ui_minutesRoller, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_minutesRoller, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_minutesRoller, &lv_font_montserrat_34, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_minutesRoller, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_minutesRoller, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_minutesRoller, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_text_font(ui_minutesRoller, &lv_font_montserrat_34, LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_minutesRoller, 5, LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_minutesRoller, lv_color_hex(0x222222), LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_minutesRoller, 255, LV_PART_SELECTED | LV_STATE_DEFAULT);

    ui_secLabel = lv_label_create(ui_customTimer);
    lv_obj_set_width(ui_secLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_secLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_secLabel, 38);
    lv_obj_set_y(ui_secLabel, -95);
    lv_obj_set_align(ui_secLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_secLabel, "Sec");
    lv_obj_set_style_text_color(ui_secLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_secLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_secLabel, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_secondsRoller = lv_roller_create(ui_customTimer);
    lv_roller_set_options(ui_secondsRoller, time_59, LV_ROLLER_MODE_INFINITE);
    lv_obj_set_height(ui_secondsRoller, 135);
    lv_obj_set_width(ui_secondsRoller, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_secondsRoller, 40);
    lv_obj_set_y(ui_secondsRoller, -15);
    lv_obj_set_align(ui_secondsRoller, LV_ALIGN_CENTER);
    lv_obj_set_style_text_color(ui_secondsRoller, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_secondsRoller, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_secondsRoller, &lv_font_montserrat_34, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_secondsRoller, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_secondsRoller, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_secondsRoller, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_text_font(ui_secondsRoller, &lv_font_montserrat_34, LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_secondsRoller, 5, LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_secondsRoller, lv_color_hex(0x222222), LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_secondsRoller, 255, LV_PART_SELECTED | LV_STATE_DEFAULT);

    ui_startCustom = lv_button_create(ui_customTimer);
    lv_obj_set_width(ui_startCustom, 105);
    lv_obj_set_height(ui_startCustom, 40);
    lv_obj_set_x(ui_startCustom, 0);
    lv_obj_set_y(ui_startCustom, -20);
    lv_obj_set_align(ui_startCustom, LV_ALIGN_BOTTOM_MID);
    lv_obj_add_flag(ui_startCustom, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_remove_flag(ui_startCustom, LV_OBJ_FLAG_SCROLLABLE);   /// Flags
    lv_obj_set_style_radius(ui_startCustom, 20, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_customLabel = lv_label_create(ui_startCustom);
    lv_obj_set_width(ui_customLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_customLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_customLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_customLabel, "Start");
    lv_obj_set_style_text_font(ui_customLabel, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_runningTimer = lv_obj_create(ui_timerScreen);
    lv_obj_remove_style_all(ui_runningTimer);
    lv_obj_set_width(ui_runningTimer, 240);
    lv_obj_set_height(ui_runningTimer, 240);
    lv_obj_set_align(ui_runningTimer, LV_ALIGN_CENTER);
    lv_obj_remove_flag(ui_runningTimer, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_timerText = lv_label_create(ui_runningTimer);
    lv_obj_set_width(ui_timerText, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_timerText, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_timerText, 0);
    lv_obj_set_y(ui_timerText, -50);
    lv_obj_set_align(ui_timerText, LV_ALIGN_CENTER);
    lv_label_set_text(ui_timerText, "Timer \nEnded");
    lv_obj_set_style_text_color(ui_timerText, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_timerText, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_timerText, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_timerText, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_timerinfo = lv_label_create(ui_runningTimer);
    lv_obj_set_width(ui_timerinfo, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_timerinfo, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_timerinfo, LV_ALIGN_CENTER);
    lv_label_set_text(ui_timerinfo, "25:10");
    lv_obj_set_style_text_color(ui_timerinfo, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_timerinfo, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_timerinfo, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_arcTimer = lv_arc_create(ui_runningTimer);
    lv_obj_set_width(ui_arcTimer, 220);
    lv_obj_set_height(ui_arcTimer, 220);
    lv_obj_set_align(ui_arcTimer, LV_ALIGN_CENTER);
    lv_obj_remove_flag(ui_arcTimer, LV_OBJ_FLAG_CLICKABLE); /// Flags
    lv_arc_set_value(ui_arcTimer, 50);
    lv_arc_set_bg_angles(ui_arcTimer, 0, 360);
    lv_arc_set_rotation(ui_arcTimer, 270);
    lv_obj_set_style_arc_color(ui_arcTimer, lv_color_hex(0x363636), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_arcTimer, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_arc_color(ui_arcTimer, lv_color_hex(0x17C571), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_arcTimer, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_arcTimer, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_arcTimer, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

    ui_startCustom1 = lv_button_create(ui_runningTimer);
    lv_obj_set_width(ui_startCustom1, 105);
    lv_obj_set_height(ui_startCustom1, 40);
    lv_obj_set_x(ui_startCustom1, 0);
    lv_obj_set_y(ui_startCustom1, -40);
    lv_obj_set_align(ui_startCustom1, LV_ALIGN_BOTTOM_MID);
    lv_obj_add_flag(ui_startCustom1, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_remove_flag(ui_startCustom1, LV_OBJ_FLAG_SCROLLABLE);   /// Flags
    lv_obj_set_style_radius(ui_startCustom1, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_startCustom1, lv_color_hex(0xCB7027), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_startCustom1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_customLabel1 = lv_label_create(ui_startCustom1);
    lv_obj_set_width(ui_customLabel1, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_customLabel1, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_customLabel1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_customLabel1, "Stop");
    lv_obj_set_style_text_font(ui_customLabel1, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_timerScreen, ui_event_timerScreen, LV_EVENT_ALL, NULL);

    lv_obj_add_event_cb(ui_startCustom, start_timer_event, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_startCustom1, stop_timer_event, LV_EVENT_CLICKED, NULL);

}

#endif