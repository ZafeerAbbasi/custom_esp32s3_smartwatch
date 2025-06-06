
// File generated by bin2lvgl
// developed by fbiego. 
// https://github.com/fbiego
// Watchface: 34_2

#include "34_2.h"

#ifdef ENABLE_FACE_34_2

lv_obj_t *face_34_2;
lv_obj_t *face_34_2_0_304;
lv_obj_t *face_34_2_1_58396;
lv_obj_t *face_34_2_2_58427;
lv_obj_t *face_34_2_3_58427;
lv_obj_t *face_34_2_4_58396;
lv_obj_t *face_34_2_5_58427;
lv_obj_t *face_34_2_6_58427;
lv_obj_t *face_34_2_7_58427;
lv_obj_t *face_34_2_8_58427;
lv_obj_t *face_34_2_9_59419;
lv_obj_t *face_34_2_10_59419;
lv_obj_t *face_34_2_11_86291;
lv_obj_t *face_34_2_12_86291;
lv_obj_t *face_34_2_14_118067;


#if LV_COLOR_DEPTH != 16
#error "LV_COLOR_DEPTH should be 16bit for watchfaces"
#endif

const lv_img_dsc_t *face_34_2_dial_img_2_58427_group[] = {
	&face_34_2_dial_img_2_58427_0,
	&face_34_2_dial_img_2_58427_1,
	&face_34_2_dial_img_2_58427_2,
	&face_34_2_dial_img_2_58427_3,
	&face_34_2_dial_img_2_58427_4,
	&face_34_2_dial_img_2_58427_5,
	&face_34_2_dial_img_2_58427_6,
	&face_34_2_dial_img_2_58427_7,
	&face_34_2_dial_img_2_58427_8,
	&face_34_2_dial_img_2_58427_9,
};
const lv_img_dsc_t *face_34_2_dial_img_9_59419_group[] = {
	&face_34_2_dial_img_9_59419_0,
	&face_34_2_dial_img_9_59419_1,
	&face_34_2_dial_img_9_59419_2,
	&face_34_2_dial_img_9_59419_3,
	&face_34_2_dial_img_9_59419_4,
	&face_34_2_dial_img_9_59419_5,
	&face_34_2_dial_img_9_59419_6,
	&face_34_2_dial_img_9_59419_7,
	&face_34_2_dial_img_9_59419_8,
	&face_34_2_dial_img_9_59419_9,
};
const lv_img_dsc_t *face_34_2_dial_img_11_86291_group[] = {
	&face_34_2_dial_img_11_86291_0,
	&face_34_2_dial_img_11_86291_1,
	&face_34_2_dial_img_11_86291_2,
	&face_34_2_dial_img_11_86291_3,
	&face_34_2_dial_img_11_86291_4,
	&face_34_2_dial_img_11_86291_5,
	&face_34_2_dial_img_11_86291_6,
	&face_34_2_dial_img_11_86291_7,
	&face_34_2_dial_img_11_86291_8,
	&face_34_2_dial_img_11_86291_9,
};
const lv_img_dsc_t *face_34_2_dial_img_13_113625_group[] = {
	&face_34_2_dial_img_13_113625_0,
	&face_34_2_dial_img_13_113625_1,
	&face_34_2_dial_img_13_113625_2,
	&face_34_2_dial_img_13_113625_3,
	&face_34_2_dial_img_13_113625_4,
	&face_34_2_dial_img_13_113625_5,
	&face_34_2_dial_img_13_113625_6,
};
const lv_img_dsc_t *face_34_2_dial_img_14_118067_group[] = {
	&face_34_2_dial_img_14_118067_0,
	&face_34_2_dial_img_14_118067_1,
	&face_34_2_dial_img_14_118067_2,
	&face_34_2_dial_img_14_118067_3,
	&face_34_2_dial_img_14_118067_4,
	&face_34_2_dial_img_14_118067_5,
	&face_34_2_dial_img_14_118067_6,
};




#endif

void init_face_34_2(void (*callback)(const char*, const lv_img_dsc_t *, lv_obj_t **, lv_obj_t **)){
#ifdef ENABLE_FACE_34_2
    face_34_2 = lv_obj_create(NULL);
    lv_obj_remove_flag(face_34_2, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(face_34_2, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(face_34_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(face_34_2, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(face_34_2, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(face_34_2, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(face_34_2, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(face_34_2, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

    lv_obj_add_event_cb(face_34_2, onFaceEvent, LV_EVENT_ALL, NULL);

    
    face_34_2_0_304 = lv_image_create(face_34_2);
    lv_image_set_src(face_34_2_0_304, &face_34_2_dial_img_0_304_0);
    lv_obj_set_width(face_34_2_0_304, LV_SIZE_CONTENT);
    lv_obj_set_height(face_34_2_0_304, LV_SIZE_CONTENT);
    lv_obj_set_x(face_34_2_0_304, 0);
    lv_obj_set_y(face_34_2_0_304, 0);
    lv_obj_add_flag(face_34_2_0_304, LV_OBJ_FLAG_ADV_HITTEST );
    lv_obj_remove_flag(face_34_2_0_304, LV_OBJ_FLAG_SCROLLABLE );

    face_34_2_1_58396 = lv_image_create(face_34_2);
    lv_image_set_src(face_34_2_1_58396, &face_34_2_dial_img_1_58396_0);
    lv_obj_set_width(face_34_2_1_58396, LV_SIZE_CONTENT);
    lv_obj_set_height(face_34_2_1_58396, LV_SIZE_CONTENT);
    lv_obj_set_x(face_34_2_1_58396, 108);
    lv_obj_set_y(face_34_2_1_58396, 42);
    lv_obj_add_flag(face_34_2_1_58396, LV_OBJ_FLAG_ADV_HITTEST );
    lv_obj_remove_flag(face_34_2_1_58396, LV_OBJ_FLAG_SCROLLABLE );

    face_34_2_2_58427 = lv_image_create(face_34_2);
    lv_image_set_src(face_34_2_2_58427, &face_34_2_dial_img_2_58427_0);
    lv_obj_set_width(face_34_2_2_58427, LV_SIZE_CONTENT);
    lv_obj_set_height(face_34_2_2_58427, LV_SIZE_CONTENT);
    lv_obj_set_x(face_34_2_2_58427, 100);
    lv_obj_set_y(face_34_2_2_58427, 37);
    lv_obj_add_flag(face_34_2_2_58427, LV_OBJ_FLAG_ADV_HITTEST );
    lv_obj_remove_flag(face_34_2_2_58427, LV_OBJ_FLAG_SCROLLABLE );

    face_34_2_3_58427 = lv_image_create(face_34_2);
    lv_image_set_src(face_34_2_3_58427, &face_34_2_dial_img_2_58427_0);
    lv_obj_set_width(face_34_2_3_58427, LV_SIZE_CONTENT);
    lv_obj_set_height(face_34_2_3_58427, LV_SIZE_CONTENT);
    lv_obj_set_x(face_34_2_3_58427, 92);
    lv_obj_set_y(face_34_2_3_58427, 37);
    lv_obj_add_flag(face_34_2_3_58427, LV_OBJ_FLAG_ADV_HITTEST );
    lv_obj_remove_flag(face_34_2_3_58427, LV_OBJ_FLAG_SCROLLABLE );

    face_34_2_4_58396 = lv_image_create(face_34_2);
    lv_image_set_src(face_34_2_4_58396, &face_34_2_dial_img_1_58396_0);
    lv_obj_set_width(face_34_2_4_58396, LV_SIZE_CONTENT);
    lv_obj_set_height(face_34_2_4_58396, LV_SIZE_CONTENT);
    lv_obj_set_x(face_34_2_4_58396, 129);
    lv_obj_set_y(face_34_2_4_58396, 42);
    lv_obj_add_flag(face_34_2_4_58396, LV_OBJ_FLAG_ADV_HITTEST );
    lv_obj_remove_flag(face_34_2_4_58396, LV_OBJ_FLAG_SCROLLABLE );

    face_34_2_5_58427 = lv_image_create(face_34_2);
    lv_image_set_src(face_34_2_5_58427, &face_34_2_dial_img_2_58427_0);
    lv_obj_set_width(face_34_2_5_58427, LV_SIZE_CONTENT);
    lv_obj_set_height(face_34_2_5_58427, LV_SIZE_CONTENT);
    lv_obj_set_x(face_34_2_5_58427, 121);
    lv_obj_set_y(face_34_2_5_58427, 37);
    lv_obj_add_flag(face_34_2_5_58427, LV_OBJ_FLAG_ADV_HITTEST );
    lv_obj_remove_flag(face_34_2_5_58427, LV_OBJ_FLAG_SCROLLABLE );

    face_34_2_6_58427 = lv_image_create(face_34_2);
    lv_image_set_src(face_34_2_6_58427, &face_34_2_dial_img_2_58427_0);
    lv_obj_set_width(face_34_2_6_58427, LV_SIZE_CONTENT);
    lv_obj_set_height(face_34_2_6_58427, LV_SIZE_CONTENT);
    lv_obj_set_x(face_34_2_6_58427, 113);
    lv_obj_set_y(face_34_2_6_58427, 37);
    lv_obj_add_flag(face_34_2_6_58427, LV_OBJ_FLAG_ADV_HITTEST );
    lv_obj_remove_flag(face_34_2_6_58427, LV_OBJ_FLAG_SCROLLABLE );

    face_34_2_7_58427 = lv_image_create(face_34_2);
    lv_image_set_src(face_34_2_7_58427, &face_34_2_dial_img_2_58427_0);
    lv_obj_set_width(face_34_2_7_58427, LV_SIZE_CONTENT);
    lv_obj_set_height(face_34_2_7_58427, LV_SIZE_CONTENT);
    lv_obj_set_x(face_34_2_7_58427, 142);
    lv_obj_set_y(face_34_2_7_58427, 37);
    lv_obj_add_flag(face_34_2_7_58427, LV_OBJ_FLAG_ADV_HITTEST );
    lv_obj_remove_flag(face_34_2_7_58427, LV_OBJ_FLAG_SCROLLABLE );

    face_34_2_8_58427 = lv_image_create(face_34_2);
    lv_image_set_src(face_34_2_8_58427, &face_34_2_dial_img_2_58427_0);
    lv_obj_set_width(face_34_2_8_58427, LV_SIZE_CONTENT);
    lv_obj_set_height(face_34_2_8_58427, LV_SIZE_CONTENT);
    lv_obj_set_x(face_34_2_8_58427, 134);
    lv_obj_set_y(face_34_2_8_58427, 37);
    lv_obj_add_flag(face_34_2_8_58427, LV_OBJ_FLAG_ADV_HITTEST );
    lv_obj_remove_flag(face_34_2_8_58427, LV_OBJ_FLAG_SCROLLABLE );

    face_34_2_9_59419 = lv_image_create(face_34_2);
    lv_image_set_src(face_34_2_9_59419, &face_34_2_dial_img_9_59419_0);
    lv_obj_set_width(face_34_2_9_59419, LV_SIZE_CONTENT);
    lv_obj_set_height(face_34_2_9_59419, LV_SIZE_CONTENT);
    lv_obj_set_x(face_34_2_9_59419, 121);
    lv_obj_set_y(face_34_2_9_59419, 59);
    lv_obj_add_flag(face_34_2_9_59419, LV_OBJ_FLAG_ADV_HITTEST );
    lv_obj_remove_flag(face_34_2_9_59419, LV_OBJ_FLAG_SCROLLABLE );

    face_34_2_10_59419 = lv_image_create(face_34_2);
    lv_image_set_src(face_34_2_10_59419, &face_34_2_dial_img_9_59419_0);
    lv_obj_set_width(face_34_2_10_59419, LV_SIZE_CONTENT);
    lv_obj_set_height(face_34_2_10_59419, LV_SIZE_CONTENT);
    lv_obj_set_x(face_34_2_10_59419, 72);
    lv_obj_set_y(face_34_2_10_59419, 59);
    lv_obj_add_flag(face_34_2_10_59419, LV_OBJ_FLAG_ADV_HITTEST );
    lv_obj_remove_flag(face_34_2_10_59419, LV_OBJ_FLAG_SCROLLABLE );

    face_34_2_11_86291 = lv_image_create(face_34_2);
    lv_image_set_src(face_34_2_11_86291, &face_34_2_dial_img_11_86291_0);
    lv_obj_set_width(face_34_2_11_86291, LV_SIZE_CONTENT);
    lv_obj_set_height(face_34_2_11_86291, LV_SIZE_CONTENT);
    lv_obj_set_x(face_34_2_11_86291, 121);
    lv_obj_set_y(face_34_2_11_86291, 123);
    lv_obj_add_flag(face_34_2_11_86291, LV_OBJ_FLAG_ADV_HITTEST );
    lv_obj_remove_flag(face_34_2_11_86291, LV_OBJ_FLAG_SCROLLABLE );

    face_34_2_12_86291 = lv_image_create(face_34_2);
    lv_image_set_src(face_34_2_12_86291, &face_34_2_dial_img_11_86291_0);
    lv_obj_set_width(face_34_2_12_86291, LV_SIZE_CONTENT);
    lv_obj_set_height(face_34_2_12_86291, LV_SIZE_CONTENT);
    lv_obj_set_x(face_34_2_12_86291, 72);
    lv_obj_set_y(face_34_2_12_86291, 123);
    lv_obj_add_flag(face_34_2_12_86291, LV_OBJ_FLAG_ADV_HITTEST );
    lv_obj_remove_flag(face_34_2_12_86291, LV_OBJ_FLAG_SCROLLABLE );

    face_34_2_14_118067 = lv_image_create(face_34_2);
    lv_image_set_src(face_34_2_14_118067, &face_34_2_dial_img_14_118067_0);
    lv_obj_set_width(face_34_2_14_118067, LV_SIZE_CONTENT);
    lv_obj_set_height(face_34_2_14_118067, LV_SIZE_CONTENT);
    lv_obj_set_x(face_34_2_14_118067, 105);
    lv_obj_set_y(face_34_2_14_118067, 192);
    lv_obj_add_flag(face_34_2_14_118067, LV_OBJ_FLAG_ADV_HITTEST );
    lv_obj_remove_flag(face_34_2_14_118067, LV_OBJ_FLAG_SCROLLABLE );


    callback("Shadow", &face_34_2_dial_img_preview_0, &face_34_2, NULL);

#endif
}

void update_time_34_2(int second, int minute, int hour, bool mode, bool am, int day, int month, int year, int weekday)
{
#ifdef ENABLE_FACE_34_2
    if (!face_34_2)
    {
        return;
    }
	lv_image_set_src(face_34_2_2_58427, face_34_2_dial_img_2_58427_group[(year / 1) % 10]);
	lv_image_set_src(face_34_2_3_58427, face_34_2_dial_img_2_58427_group[(year / 10) % 10]);
	lv_image_set_src(face_34_2_5_58427, face_34_2_dial_img_2_58427_group[(month / 1) % 10]);
	lv_image_set_src(face_34_2_6_58427, face_34_2_dial_img_2_58427_group[(month / 10) % 10]);
	lv_image_set_src(face_34_2_7_58427, face_34_2_dial_img_2_58427_group[(day / 1) % 10]);
	lv_image_set_src(face_34_2_8_58427, face_34_2_dial_img_2_58427_group[(day / 10) % 10]);
	lv_image_set_src(face_34_2_9_59419, face_34_2_dial_img_9_59419_group[(hour / 1) % 10]);
	lv_image_set_src(face_34_2_10_59419, face_34_2_dial_img_9_59419_group[(hour / 10) % 10]);
	lv_image_set_src(face_34_2_11_86291, face_34_2_dial_img_11_86291_group[(minute / 1) % 10]);
	lv_image_set_src(face_34_2_12_86291, face_34_2_dial_img_11_86291_group[(minute / 10) % 10]);
	lv_image_set_src(face_34_2_14_118067, face_34_2_dial_img_14_118067_group[((weekday + 6) / 1) % 7]);

#endif
}

void update_weather_34_2(int temp, int icon)
{
#ifdef ENABLE_FACE_34_2
    if (!face_34_2)
    {
        return;
    }

#endif
}

void update_status_34_2(int battery, bool connection){
#ifdef ENABLE_FACE_34_2
    if (!face_34_2)
    {
        return;
    }

#endif
}

void update_activity_34_2(int steps, int distance, int kcal)
{
#ifdef ENABLE_FACE_34_2
    if (!face_34_2)
    {
        return;
    }

#endif
}

void update_health_34_2(int bpm, int oxygen)
{
#ifdef ENABLE_FACE_34_2
    if (!face_34_2)
    {
        return;
    }

#endif
}

void update_all_34_2(int second, int minute, int hour, bool mode, bool am, int day, int month, int year, int weekday, 
    int temp, int icon, int battery, bool connection, int steps, int distance, int kcal, int bpm, int oxygen)
{
#ifdef ENABLE_FACE_34_2
    update_time_34_2(second, minute, hour, mode, am, day, month, year, weekday);
    update_weather_34_2(temp, icon);
    update_status_34_2(battery, connection);
    update_activity_34_2(steps, distance, kcal);
    update_health_34_2(bpm, oxygen);
#endif
}

void update_check_34_2(lv_obj_t *root, int second, int minute, int hour, bool mode, bool am, int day, int month, int year, int weekday, 
    int temp, int icon, int battery, bool connection, int steps, int distance, int kcal, int bpm, int oxygen)
{
#ifdef ENABLE_FACE_34_2
    if (root != face_34_2)
    {
        return;
    }
    update_time_34_2(second, minute, hour, mode, am, day, month, year, weekday);
    update_weather_34_2(temp, icon);
    update_status_34_2(battery, connection);
    update_activity_34_2(steps, distance, kcal);
    update_health_34_2(bpm, oxygen);
#endif
}


