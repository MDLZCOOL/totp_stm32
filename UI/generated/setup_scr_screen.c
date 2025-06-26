/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"



void setup_scr_screen(lv_ui *ui)
{
    //Write codes screen
    ui->screen = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen, 480, 320);
    lv_obj_set_scrollbar_mode(ui->screen, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_cont_1
    ui->screen_cont_1 = lv_obj_create(ui->screen);
    lv_obj_set_pos(ui->screen_cont_1, 0, 0);
    lv_obj_set_size(ui->screen_cont_1, 480, 320);
    lv_obj_set_scrollbar_mode(ui->screen_cont_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_cont_1, lv_color_hex(0xc8c8c8), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_img_3
    ui->screen_img_3 = lv_img_create(ui->screen_cont_1);
    lv_obj_add_flag(ui->screen_img_3, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_img_3, &_about_alpha_30x30);
    lv_img_set_pivot(ui->screen_img_3, 50,50);
    lv_img_set_angle(ui->screen_img_3, 0);
    lv_obj_set_pos(ui->screen_img_3, 427, 16);
    lv_obj_set_size(ui->screen_img_3, 30, 30);

    //Write style for screen_img_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_img_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_img_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_img_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_img_3, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_img_2
    ui->screen_img_2 = lv_img_create(ui->screen_cont_1);
    lv_obj_add_flag(ui->screen_img_2, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_img_2, &_menu_alpha_30x30);
    lv_img_set_pivot(ui->screen_img_2, 50,50);
    lv_img_set_angle(ui->screen_img_2, 0);
    lv_obj_set_pos(ui->screen_img_2, 373, 16);
    lv_obj_set_size(ui->screen_img_2, 30, 30);

    //Write style for screen_img_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_img_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_img_2, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_label_1
    ui->screen_label_1 = lv_label_create(ui->screen_cont_1);
    lv_label_set_text(ui->screen_label_1, "Authenticator");
    lv_label_set_long_mode(ui->screen_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_label_1, 8, 13);
    lv_obj_set_size(ui->screen_label_1, 184, 32);

    //Write style for screen_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_label_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_label_1, &lv_font_arial_28, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_table_1
    ui->screen_table_1 = lv_table_create(ui->screen_cont_1);
    lv_table_set_col_cnt(ui->screen_table_1,3);
    lv_table_set_row_cnt(ui->screen_table_1,6);
    lv_table_set_cell_value(ui->screen_table_1,0,0,"账号");
    lv_table_set_cell_value(ui->screen_table_1,1,0,"-");
    lv_table_set_cell_value(ui->screen_table_1,2,0,"-");
    lv_table_set_cell_value(ui->screen_table_1,3,0,"-");
    lv_table_set_cell_value(ui->screen_table_1,4,0,"-");
    lv_table_set_cell_value(ui->screen_table_1,5,0,"-");
    lv_table_set_cell_value(ui->screen_table_1,0,1,"验证码");
    lv_table_set_cell_value(ui->screen_table_1,1,1,"-");
    lv_table_set_cell_value(ui->screen_table_1,2,1,"-");
    lv_table_set_cell_value(ui->screen_table_1,3,1,"-");
    lv_table_set_cell_value(ui->screen_table_1,4,1,"-");
    lv_table_set_cell_value(ui->screen_table_1,5,1,"-");
    lv_table_set_cell_value(ui->screen_table_1,0,2,"过期时间");
    lv_table_set_cell_value(ui->screen_table_1,1,2,"-");
    lv_table_set_cell_value(ui->screen_table_1,2,2,"-");
    lv_table_set_cell_value(ui->screen_table_1,3,2,"-");
    lv_table_set_cell_value(ui->screen_table_1,4,2,"-");
    lv_table_set_cell_value(ui->screen_table_1,5,2,"-");
    lv_obj_set_pos(ui->screen_table_1, 41, 65);
    lv_obj_set_scrollbar_mode(ui->screen_table_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_table_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_pad_top(ui->screen_table_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_table_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_table_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_table_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_table_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_table_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_table_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_table_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_table_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_table_1, lv_color_hex(0xd5dee6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_table_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_table_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_table_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_table_1, Part: LV_PART_ITEMS, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->screen_table_1, lv_color_hex(0x393c41), LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_table_1, &lv_font_SourceHanSerifSC_Regular_17, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_table_1, 255, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_table_1, LV_TEXT_ALIGN_CENTER, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_table_1, 0, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_table_1, 3, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_table_1, 255, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_table_1, lv_color_hex(0xd5dee6), LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_table_1, LV_BORDER_SIDE_FULL, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_table_1, 0, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_table_1, 10, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_table_1, 10, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_table_1, 10, LV_PART_ITEMS|LV_STATE_DEFAULT);

    //Write codes screen_list_2
    ui->screen_list_2 = lv_list_create(ui->screen_cont_1);
    ui->screen_list_2_item0 = lv_list_add_btn(ui->screen_list_2, LV_SYMBOL_EDIT, "Manual Edit");
    ui->screen_list_2_item1 = lv_list_add_btn(ui->screen_list_2, LV_SYMBOL_DOWNLOAD, "Import Account");
    ui->screen_list_2_item2 = lv_list_add_btn(ui->screen_list_2, LV_SYMBOL_DIRECTORY, "History");
    lv_obj_set_pos(ui->screen_list_2, 306, 47);
    lv_obj_set_size(ui->screen_list_2, 160, 108);
    lv_obj_set_scrollbar_mode(ui->screen_list_2, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->screen_list_2, LV_OBJ_FLAG_HIDDEN);

    //Write style state: LV_STATE_DEFAULT for &style_screen_list_2_main_main_default
    static lv_style_t style_screen_list_2_main_main_default;
    ui_init_style(&style_screen_list_2_main_main_default);

    lv_style_set_pad_top(&style_screen_list_2_main_main_default, 5);
    lv_style_set_pad_left(&style_screen_list_2_main_main_default, 5);
    lv_style_set_pad_right(&style_screen_list_2_main_main_default, 5);
    lv_style_set_pad_bottom(&style_screen_list_2_main_main_default, 5);
    lv_style_set_bg_opa(&style_screen_list_2_main_main_default, 255);
    lv_style_set_bg_color(&style_screen_list_2_main_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_screen_list_2_main_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_screen_list_2_main_main_default, 1);
    lv_style_set_border_opa(&style_screen_list_2_main_main_default, 255);
    lv_style_set_border_color(&style_screen_list_2_main_main_default, lv_color_hex(0xe1e6ee));
    lv_style_set_border_side(&style_screen_list_2_main_main_default, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(&style_screen_list_2_main_main_default, 3);
    lv_style_set_shadow_width(&style_screen_list_2_main_main_default, 4);
    lv_style_set_shadow_color(&style_screen_list_2_main_main_default, lv_color_hex(0x7a7d7f));
    lv_style_set_shadow_opa(&style_screen_list_2_main_main_default, 131);
    lv_style_set_shadow_spread(&style_screen_list_2_main_main_default, 5);
    lv_style_set_shadow_ofs_x(&style_screen_list_2_main_main_default, 5);
    lv_style_set_shadow_ofs_y(&style_screen_list_2_main_main_default, 5);
    lv_obj_add_style(ui->screen_list_2, &style_screen_list_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_screen_list_2_main_scrollbar_default
    static lv_style_t style_screen_list_2_main_scrollbar_default;
    ui_init_style(&style_screen_list_2_main_scrollbar_default);

    lv_style_set_radius(&style_screen_list_2_main_scrollbar_default, 3);
    lv_style_set_bg_opa(&style_screen_list_2_main_scrollbar_default, 255);
    lv_style_set_bg_color(&style_screen_list_2_main_scrollbar_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_screen_list_2_main_scrollbar_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(ui->screen_list_2, &style_screen_list_2_main_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_screen_list_2_extra_btns_main_default
    static lv_style_t style_screen_list_2_extra_btns_main_default;
    ui_init_style(&style_screen_list_2_extra_btns_main_default);

    lv_style_set_pad_top(&style_screen_list_2_extra_btns_main_default, 5);
    lv_style_set_pad_left(&style_screen_list_2_extra_btns_main_default, 5);
    lv_style_set_pad_right(&style_screen_list_2_extra_btns_main_default, 5);
    lv_style_set_pad_bottom(&style_screen_list_2_extra_btns_main_default, 5);
    lv_style_set_border_width(&style_screen_list_2_extra_btns_main_default, 0);
    lv_style_set_text_color(&style_screen_list_2_extra_btns_main_default, lv_color_hex(0x0D3055));
    lv_style_set_text_font(&style_screen_list_2_extra_btns_main_default, &lv_font_montserratMedium_12);
    lv_style_set_text_opa(&style_screen_list_2_extra_btns_main_default, 255);
    lv_style_set_radius(&style_screen_list_2_extra_btns_main_default, 3);
    lv_style_set_bg_opa(&style_screen_list_2_extra_btns_main_default, 255);
    lv_style_set_bg_color(&style_screen_list_2_extra_btns_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_screen_list_2_extra_btns_main_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(ui->screen_list_2_item2, &style_screen_list_2_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->screen_list_2_item1, &style_screen_list_2_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->screen_list_2_item0, &style_screen_list_2_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_screen_list_2_extra_texts_main_default
    static lv_style_t style_screen_list_2_extra_texts_main_default;
    ui_init_style(&style_screen_list_2_extra_texts_main_default);

    lv_style_set_pad_top(&style_screen_list_2_extra_texts_main_default, 5);
    lv_style_set_pad_left(&style_screen_list_2_extra_texts_main_default, 5);
    lv_style_set_pad_right(&style_screen_list_2_extra_texts_main_default, 5);
    lv_style_set_pad_bottom(&style_screen_list_2_extra_texts_main_default, 5);
    lv_style_set_border_width(&style_screen_list_2_extra_texts_main_default, 0);
    lv_style_set_text_color(&style_screen_list_2_extra_texts_main_default, lv_color_hex(0x0D3055));
    lv_style_set_text_font(&style_screen_list_2_extra_texts_main_default, &lv_font_arial_12);
    lv_style_set_text_opa(&style_screen_list_2_extra_texts_main_default, 255);
    lv_style_set_radius(&style_screen_list_2_extra_texts_main_default, 3);
    lv_style_set_transform_width(&style_screen_list_2_extra_texts_main_default, 0);
    lv_style_set_bg_opa(&style_screen_list_2_extra_texts_main_default, 255);
    lv_style_set_bg_color(&style_screen_list_2_extra_texts_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_screen_list_2_extra_texts_main_default, LV_GRAD_DIR_NONE);

    //Write codes screen_list_4
    ui->screen_list_4 = lv_list_create(ui->screen_cont_1);
    ui->screen_list_4_item0 = lv_list_add_btn(ui->screen_list_4, LV_SYMBOL_SHUFFLE, "Sync Timestamp");
    ui->screen_list_4_item1 = lv_list_add_btn(ui->screen_list_4, LV_SYMBOL_ENVELOPE, "About Me...");
    lv_obj_set_pos(ui->screen_list_4, 306, 47);
    lv_obj_set_size(ui->screen_list_4, 160, 65);
    lv_obj_set_scrollbar_mode(ui->screen_list_4, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->screen_list_4, LV_OBJ_FLAG_HIDDEN);

    //Write style state: LV_STATE_DEFAULT for &style_screen_list_4_main_main_default
    static lv_style_t style_screen_list_4_main_main_default;
    ui_init_style(&style_screen_list_4_main_main_default);

    lv_style_set_pad_top(&style_screen_list_4_main_main_default, 5);
    lv_style_set_pad_left(&style_screen_list_4_main_main_default, 5);
    lv_style_set_pad_right(&style_screen_list_4_main_main_default, 5);
    lv_style_set_pad_bottom(&style_screen_list_4_main_main_default, 5);
    lv_style_set_bg_opa(&style_screen_list_4_main_main_default, 255);
    lv_style_set_bg_color(&style_screen_list_4_main_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_screen_list_4_main_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_screen_list_4_main_main_default, 1);
    lv_style_set_border_opa(&style_screen_list_4_main_main_default, 255);
    lv_style_set_border_color(&style_screen_list_4_main_main_default, lv_color_hex(0xe1e6ee));
    lv_style_set_border_side(&style_screen_list_4_main_main_default, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(&style_screen_list_4_main_main_default, 3);
    lv_style_set_shadow_width(&style_screen_list_4_main_main_default, 4);
    lv_style_set_shadow_color(&style_screen_list_4_main_main_default, lv_color_hex(0x7a7d7f));
    lv_style_set_shadow_opa(&style_screen_list_4_main_main_default, 131);
    lv_style_set_shadow_spread(&style_screen_list_4_main_main_default, 5);
    lv_style_set_shadow_ofs_x(&style_screen_list_4_main_main_default, 5);
    lv_style_set_shadow_ofs_y(&style_screen_list_4_main_main_default, 5);
    lv_obj_add_style(ui->screen_list_4, &style_screen_list_4_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_screen_list_4_main_scrollbar_default
    static lv_style_t style_screen_list_4_main_scrollbar_default;
    ui_init_style(&style_screen_list_4_main_scrollbar_default);

    lv_style_set_radius(&style_screen_list_4_main_scrollbar_default, 3);
    lv_style_set_bg_opa(&style_screen_list_4_main_scrollbar_default, 255);
    lv_style_set_bg_color(&style_screen_list_4_main_scrollbar_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_screen_list_4_main_scrollbar_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(ui->screen_list_4, &style_screen_list_4_main_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_screen_list_4_extra_btns_main_default
    static lv_style_t style_screen_list_4_extra_btns_main_default;
    ui_init_style(&style_screen_list_4_extra_btns_main_default);

    lv_style_set_pad_top(&style_screen_list_4_extra_btns_main_default, 5);
    lv_style_set_pad_left(&style_screen_list_4_extra_btns_main_default, 5);
    lv_style_set_pad_right(&style_screen_list_4_extra_btns_main_default, 5);
    lv_style_set_pad_bottom(&style_screen_list_4_extra_btns_main_default, 5);
    lv_style_set_border_width(&style_screen_list_4_extra_btns_main_default, 0);
    lv_style_set_text_color(&style_screen_list_4_extra_btns_main_default, lv_color_hex(0x0D3055));
    lv_style_set_text_font(&style_screen_list_4_extra_btns_main_default, &lv_font_montserratMedium_12);
    lv_style_set_text_opa(&style_screen_list_4_extra_btns_main_default, 255);
    lv_style_set_radius(&style_screen_list_4_extra_btns_main_default, 3);
    lv_style_set_bg_opa(&style_screen_list_4_extra_btns_main_default, 255);
    lv_style_set_bg_color(&style_screen_list_4_extra_btns_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_screen_list_4_extra_btns_main_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(ui->screen_list_4_item1, &style_screen_list_4_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->screen_list_4_item0, &style_screen_list_4_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_screen_list_4_extra_texts_main_default
    static lv_style_t style_screen_list_4_extra_texts_main_default;
    ui_init_style(&style_screen_list_4_extra_texts_main_default);

    lv_style_set_pad_top(&style_screen_list_4_extra_texts_main_default, 5);
    lv_style_set_pad_left(&style_screen_list_4_extra_texts_main_default, 5);
    lv_style_set_pad_right(&style_screen_list_4_extra_texts_main_default, 5);
    lv_style_set_pad_bottom(&style_screen_list_4_extra_texts_main_default, 5);
    lv_style_set_border_width(&style_screen_list_4_extra_texts_main_default, 0);
    lv_style_set_text_color(&style_screen_list_4_extra_texts_main_default, lv_color_hex(0x0D3055));
    lv_style_set_text_font(&style_screen_list_4_extra_texts_main_default, &lv_font_arial_12);
    lv_style_set_text_opa(&style_screen_list_4_extra_texts_main_default, 255);
    lv_style_set_radius(&style_screen_list_4_extra_texts_main_default, 3);
    lv_style_set_transform_width(&style_screen_list_4_extra_texts_main_default, 0);
    lv_style_set_bg_opa(&style_screen_list_4_extra_texts_main_default, 255);
    lv_style_set_bg_color(&style_screen_list_4_extra_texts_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_screen_list_4_extra_texts_main_default, LV_GRAD_DIR_NONE);

    //Write codes screen_msgbox_1
    static const char * screen_msgbox_1_btns[] = {"Done", ""};
    ui->screen_msgbox_1 = lv_msgbox_create(ui->screen_cont_1, "USB DEVICE MSC", "\n请连接电脑\n\n修改MSC设备中的account.txt\n\n以更新账号信息\n", screen_msgbox_1_btns, false);
    lv_obj_set_size(lv_msgbox_get_btns(ui->screen_msgbox_1), 60, 29);
    lv_obj_set_pos(ui->screen_msgbox_1, 41, 56);
    lv_obj_set_size(ui->screen_msgbox_1, 394, 229);
    lv_obj_add_flag(ui->screen_msgbox_1, LV_OBJ_FLAG_HIDDEN);

    //Write style for screen_msgbox_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_msgbox_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_msgbox_1, lv_color_hex(0xb7b4b4), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_msgbox_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_msgbox_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_msgbox_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_msgbox_1, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->screen_msgbox_1, lv_color_hex(0x7a7d7f), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->screen_msgbox_1, 132, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->screen_msgbox_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui->screen_msgbox_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui->screen_msgbox_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_screen_msgbox_1_extra_title_main_default
    static lv_style_t style_screen_msgbox_1_extra_title_main_default;
    ui_init_style(&style_screen_msgbox_1_extra_title_main_default);

    lv_style_set_text_color(&style_screen_msgbox_1_extra_title_main_default, lv_color_hex(0x4e4e4e));
    lv_style_set_text_font(&style_screen_msgbox_1_extra_title_main_default, &lv_font_arial_20);
    lv_style_set_text_opa(&style_screen_msgbox_1_extra_title_main_default, 255);
    lv_style_set_text_letter_space(&style_screen_msgbox_1_extra_title_main_default, 0);
    lv_style_set_text_line_space(&style_screen_msgbox_1_extra_title_main_default, 0);
    lv_obj_add_style(lv_msgbox_get_title(ui->screen_msgbox_1), &style_screen_msgbox_1_extra_title_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_screen_msgbox_1_extra_content_main_default
    static lv_style_t style_screen_msgbox_1_extra_content_main_default;
    ui_init_style(&style_screen_msgbox_1_extra_content_main_default);

    lv_style_set_text_color(&style_screen_msgbox_1_extra_content_main_default, lv_color_hex(0x4e4e4e));
    lv_style_set_text_font(&style_screen_msgbox_1_extra_content_main_default, &lv_font_SourceHanSerifSC_Regular_18);
    lv_style_set_text_opa(&style_screen_msgbox_1_extra_content_main_default, 255);
    lv_style_set_text_letter_space(&style_screen_msgbox_1_extra_content_main_default, 0);
    lv_style_set_text_line_space(&style_screen_msgbox_1_extra_content_main_default, 0);
    lv_obj_add_style(lv_msgbox_get_text(ui->screen_msgbox_1), &style_screen_msgbox_1_extra_content_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_screen_msgbox_1_extra_btns_items_default
    static lv_style_t style_screen_msgbox_1_extra_btns_items_default;
    ui_init_style(&style_screen_msgbox_1_extra_btns_items_default);

    lv_style_set_bg_opa(&style_screen_msgbox_1_extra_btns_items_default, 255);
    lv_style_set_bg_color(&style_screen_msgbox_1_extra_btns_items_default, lv_color_hex(0xdcdcdc));
    lv_style_set_bg_grad_dir(&style_screen_msgbox_1_extra_btns_items_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_screen_msgbox_1_extra_btns_items_default, 0);
    lv_style_set_radius(&style_screen_msgbox_1_extra_btns_items_default, 5);
    lv_style_set_text_color(&style_screen_msgbox_1_extra_btns_items_default, lv_color_hex(0x4e4e4e));
    lv_style_set_text_font(&style_screen_msgbox_1_extra_btns_items_default, &lv_font_montserratMedium_15);
    lv_style_set_text_opa(&style_screen_msgbox_1_extra_btns_items_default, 255);
    lv_obj_add_style(lv_msgbox_get_btns(ui->screen_msgbox_1), &style_screen_msgbox_1_extra_btns_items_default, LV_PART_ITEMS|LV_STATE_DEFAULT);

    //Write codes screen_msgbox_2
    static const char * screen_msgbox_2_btns[] = {"Done", ""};
    ui->screen_msgbox_2 = lv_msgbox_create(ui->screen_cont_1, "USB DEVICE CDC ACM", "\n请连接上位机\n\n以便可以同步时间\n", screen_msgbox_2_btns, false);
    lv_obj_set_size(lv_msgbox_get_btns(ui->screen_msgbox_2), 60, 29);
    lv_obj_set_pos(ui->screen_msgbox_2, 40, 56);
    lv_obj_set_size(ui->screen_msgbox_2, 394, 229);
    lv_obj_add_flag(ui->screen_msgbox_2, LV_OBJ_FLAG_HIDDEN);

    //Write style for screen_msgbox_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_msgbox_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_msgbox_2, lv_color_hex(0xb7b4b4), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_msgbox_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_msgbox_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_msgbox_2, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_msgbox_2, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->screen_msgbox_2, lv_color_hex(0x7a7d7f), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->screen_msgbox_2, 132, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->screen_msgbox_2, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui->screen_msgbox_2, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui->screen_msgbox_2, 5, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_screen_msgbox_2_extra_title_main_default
    static lv_style_t style_screen_msgbox_2_extra_title_main_default;
    ui_init_style(&style_screen_msgbox_2_extra_title_main_default);

    lv_style_set_text_color(&style_screen_msgbox_2_extra_title_main_default, lv_color_hex(0x4e4e4e));
    lv_style_set_text_font(&style_screen_msgbox_2_extra_title_main_default, &lv_font_arial_20);
    lv_style_set_text_opa(&style_screen_msgbox_2_extra_title_main_default, 255);
    lv_style_set_text_letter_space(&style_screen_msgbox_2_extra_title_main_default, 0);
    lv_style_set_text_line_space(&style_screen_msgbox_2_extra_title_main_default, 0);
    lv_obj_add_style(lv_msgbox_get_title(ui->screen_msgbox_2), &style_screen_msgbox_2_extra_title_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_screen_msgbox_2_extra_content_main_default
    static lv_style_t style_screen_msgbox_2_extra_content_main_default;
    ui_init_style(&style_screen_msgbox_2_extra_content_main_default);

    lv_style_set_text_color(&style_screen_msgbox_2_extra_content_main_default, lv_color_hex(0x4e4e4e));
    lv_style_set_text_font(&style_screen_msgbox_2_extra_content_main_default, &lv_font_SourceHanSerifSC_Regular_18);
    lv_style_set_text_opa(&style_screen_msgbox_2_extra_content_main_default, 255);
    lv_style_set_text_letter_space(&style_screen_msgbox_2_extra_content_main_default, 0);
    lv_style_set_text_line_space(&style_screen_msgbox_2_extra_content_main_default, 0);
    lv_obj_add_style(lv_msgbox_get_text(ui->screen_msgbox_2), &style_screen_msgbox_2_extra_content_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_screen_msgbox_2_extra_btns_items_default
    static lv_style_t style_screen_msgbox_2_extra_btns_items_default;
    ui_init_style(&style_screen_msgbox_2_extra_btns_items_default);

    lv_style_set_bg_opa(&style_screen_msgbox_2_extra_btns_items_default, 255);
    lv_style_set_bg_color(&style_screen_msgbox_2_extra_btns_items_default, lv_color_hex(0xdcdcdc));
    lv_style_set_bg_grad_dir(&style_screen_msgbox_2_extra_btns_items_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_screen_msgbox_2_extra_btns_items_default, 0);
    lv_style_set_radius(&style_screen_msgbox_2_extra_btns_items_default, 5);
    lv_style_set_text_color(&style_screen_msgbox_2_extra_btns_items_default, lv_color_hex(0x4e4e4e));
    lv_style_set_text_font(&style_screen_msgbox_2_extra_btns_items_default, &lv_font_montserratMedium_15);
    lv_style_set_text_opa(&style_screen_msgbox_2_extra_btns_items_default, 255);
    lv_obj_add_style(lv_msgbox_get_btns(ui->screen_msgbox_2), &style_screen_msgbox_2_extra_btns_items_default, LV_PART_ITEMS|LV_STATE_DEFAULT);

    //Write codes screen_label_2
    ui->screen_label_2 = lv_label_create(ui->screen_cont_1);
    lv_label_set_text(ui->screen_label_2, "郭储源 2023302106\n电子产品设计与制作");
    lv_label_set_long_mode(ui->screen_label_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_label_2, 200, 15);
    lv_obj_set_size(ui->screen_label_2, 151, 32);

    //Write style for screen_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_label_2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_label_2, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_label_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_label_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_ta_1
    ui->screen_ta_1 = lv_textarea_create(ui->screen_cont_1);
    lv_textarea_set_text(ui->screen_ta_1, "Hello World");
    lv_textarea_set_placeholder_text(ui->screen_ta_1, "");
    lv_textarea_set_password_bullet(ui->screen_ta_1, "*");
    lv_textarea_set_password_mode(ui->screen_ta_1, false);
    lv_textarea_set_one_line(ui->screen_ta_1, false);
    lv_textarea_set_accepted_chars(ui->screen_ta_1, "");
    lv_textarea_set_max_length(ui->screen_ta_1, 128);
#if LV_USE_KEYBOARD != 0 || LV_USE_ZH_KEYBOARD != 0
    lv_obj_add_event_cb(ui->screen_ta_1, ta_event_cb, LV_EVENT_ALL, ui->g_kb_top_layer);
#endif
    lv_obj_set_pos(ui->screen_ta_1, 67, 62);
    lv_obj_set_size(ui->screen_ta_1, 344, 196);
    lv_obj_add_flag(ui->screen_ta_1, LV_OBJ_FLAG_HIDDEN);

    //Write style for screen_ta_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->screen_ta_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_ta_1, &lv_font_arial_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_ta_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_ta_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_ta_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_ta_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_ta_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_ta_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_ta_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_ta_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_ta_1, lv_color_hex(0xe6e6e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_ta_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_ta_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_ta_1, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_ta_1, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_ta_1, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_ta_1, 4, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_ta_1, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_ta_1, 255, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_ta_1, lv_color_hex(0x2195f6), LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_ta_1, LV_GRAD_DIR_NONE, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_ta_1, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //The custom code of screen.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen);

    //Init events for screen.
    events_init_screen(ui);
}
