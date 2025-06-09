// #include <stdlib.h>
// #include <stdio.h>
// #include <unistd.h>
// #include "lvgl/lvgl.h"
// #include "lvgl/examples/lv_examples.h"
// #include "lvgl/demos/lv_demos.h"


// #define SCREEN_WIDTH  240
// #define SCREEN_HEIGHT 280

// void create_ui(void) {

//     lv_obj_t *h_scroll_container = lv_obj_create(lv_scr_act());
//     lv_obj_remove_style_all(h_scroll_container);  // Remove border/shadow/padding
//     lv_obj_set_size(h_scroll_container, LV_HOR_RES, LV_VER_RES);
//     lv_obj_add_flag(h_scroll_container, LV_OBJ_FLAG_SCROLL_ONE);
//     lv_obj_set_scroll_snap_x(h_scroll_container, LV_SCROLL_SNAP_START);
//     lv_obj_set_scroll_dir(h_scroll_container, LV_DIR_HOR);
//     lv_obj_set_scrollbar_mode(h_scroll_container, LV_SCROLLBAR_MODE_OFF);

//     // ✅ Use FLEX layout with horizontal flow
//     lv_obj_set_layout(h_scroll_container, LV_LAYOUT_FLEX);
//     lv_obj_set_flex_flow(h_scroll_container, LV_FLEX_FLOW_ROW);  // Arrange children horizontally

//     // ✅ Remove all spacing/padding
//     lv_obj_set_style_pad_all(h_scroll_container, 0, 0);    // Internal padding
//     lv_obj_set_style_pad_row(h_scroll_container, 0, 0);
//     lv_obj_set_style_pad_column(h_scroll_container, 0, 0);
//     lv_obj_set_style_pad_gap(h_scroll_container, 0, 0);



//     lv_obj_t *screen1 = lv_obj_create(h_scroll_container);
//     lv_obj_remove_style_all(screen1);
//     lv_obj_set_size(screen1, LV_HOR_RES, LV_VER_RES);

//     lv_obj_set_style_bg_opa(screen1, LV_OPA_COVER, 0);  // Needed to show bg
//     lv_obj_set_style_bg_color(screen1, lv_color_make( 13, 17, 23 ), LV_PART_MAIN);
//     lv_obj_set_style_bg_grad_color(screen1, lv_color_make( 40, 52, 71 ), LV_PART_MAIN);
//     lv_obj_set_style_bg_grad_dir(screen1, LV_GRAD_DIR_VER, LV_PART_MAIN);

//     //Add time label
//     lv_obj_t *label_clock = lv_label_create(screen1);
//     lv_obj_t *label_date = lv_label_create( screen1 );
//     lv_obj_t *label_day = lv_label_create( screen1 );
//     lv_obj_t *label_month = lv_label_create( screen1 );
//     lv_obj_t *label_year = lv_label_create( screen1 );

//     lv_label_set_text( label_clock, "8:38 PM" );
//     lv_label_set_text( label_date, "23" );
//     lv_label_set_text( label_day, "Wed" );
//     lv_label_set_text( label_month, "Apr" );
//     lv_label_set_text( label_year, "2025" );

//     lv_obj_set_style_text_font(label_day, &lv_font_montserrat_16, LV_PART_MAIN);
//     lv_obj_set_style_text_font(label_month, &lv_font_montserrat_12, LV_PART_MAIN);
//     lv_obj_set_style_text_font(label_date, &lv_font_montserrat_40, LV_PART_MAIN);
//     lv_obj_set_style_text_font(label_year, &lv_font_montserrat_12, LV_PART_MAIN);

//     lv_obj_set_style_text_color(label_day, lv_color_white(), LV_PART_MAIN);
//     lv_obj_set_style_text_color(label_month, lv_color_white(), LV_PART_MAIN);
//     lv_obj_set_style_text_color(label_year, lv_color_white(), LV_PART_MAIN);
//     lv_obj_set_style_text_color(label_date, lv_color_white(), LV_PART_MAIN);
//     lv_obj_set_style_text_color(label_clock, lv_color_white(), LV_PART_MAIN);


//     /*Set various date elements alignment*/
//     lv_obj_align(label_clock, LV_ALIGN_TOP_RIGHT, LV_PCT(-30), LV_PCT(30));
//     lv_obj_align(label_date, LV_ALIGN_TOP_LEFT, LV_PCT(5), LV_PCT(40));
//     lv_obj_align(label_day, LV_ALIGN_TOP_LEFT, LV_PCT(5), LV_PCT(35));
//     lv_obj_align(label_month, LV_ALIGN_TOP_LEFT, LV_PCT(5), LV_PCT(30));
//     lv_obj_align(label_year, LV_ALIGN_TOP_LEFT, LV_PCT(5), LV_PCT(55));

//     // // Add time label
//     // lv_obj_t *label_time = lv_label_create(screen1);
//     // lv_label_set_text(label_time, "12:45");
//     // lv_obj_align(label_time, LV_ALIGN_CENTER, 0, -20);

//     // // Add date label
//     // lv_obj_t *label_date = lv_label_create(screen1);
//     // lv_label_set_text(label_date, "Wed, Apr 23");
//     // lv_obj_align(label_date, LV_ALIGN_CENTER, 0, 20);

//     lv_obj_t *screen2 = lv_obj_create(h_scroll_container);
//     lv_obj_set_layout(screen2, LV_LAYOUT_FLEX);
//     lv_obj_set_flex_flow(screen2, LV_FLEX_FLOW_COLUMN);
//     lv_obj_set_size(screen2, LV_HOR_RES, LV_VER_RES);
//     lv_obj_set_pos(screen2, LV_HOR_RES, 0);  // Place to the right

//     lv_obj_set_scroll_dir(screen2, LV_DIR_VER); // Vertical scroll for this screen
//     lv_obj_add_flag(screen2, LV_OBJ_FLAG_SCROLL_ONE);
//     lv_obj_set_scrollbar_mode(screen2, LV_SCROLLBAR_MODE_ACTIVE);
//     lv_obj_set_flex_align(screen2, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);


//     // Add rounded menu buttons
//     for(int i = 0; i < 5; i++) {
//         lv_obj_t *btn = lv_btn_create(screen2);
//         lv_obj_set_size(btn, 180, 60);
//         lv_obj_set_style_radius(btn, 30, 0);
//         lv_obj_add_flag(btn, LV_OBJ_FLAG_SNAPPABLE);  // Optional for snapping

//         // Center contents (label)
//         lv_obj_t *label = lv_label_create(btn);
//         lv_label_set_text_fmt(label, "Option %d", i + 1);
//         lv_obj_center(label);
//     }
// }
