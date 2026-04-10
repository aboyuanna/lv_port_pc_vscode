/**
 * @file main.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE /* needed for usleep() */
#endif

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _MSC_VER
#include <Windows.h>
#else
#include <pthread.h>
#include <unistd.h>
#endif
#include <SDL.h>

#include "lvgl/demos/lv_demos.h"
#include "lvgl/examples/lv_examples.h"
#include "lvgl/lvgl.h"

#include "hal/hal.h"

#define MAIN_PAGE_WIDTH 720                 // 主页面宽度
#define MAIN_PAGE_HEIGHT 720                // 主页面高度
#define MAIN_PAGE_BG_COLOR lv_color_black() // 主页面背景颜色

#define LV_STATUS_BAR_WIDTH (MAIN_PAGE_WIDTH)         // 状态栏宽度
#define LV_STATUS_BAR_HEIGHT (70)                     // 状态栏高度
#define STATUS_BAR_OBJ_BG_COLOR lv_color_black()      // 状态栏背景颜色
#define STATUS_BAR_LABEL_FONT_COLOER lv_color_white() // 状态栏标签文本颜色

// LV_FONT_DECLARE(my_equalwidth_font16);
LV_FONT_DECLARE(my_equalwidth_font20);
LV_FONT_DECLARE(my_equalwidth_font24);
// LV_FONT_DECLARE(my_equalwidth_font32);
LV_FONT_DECLARE(my_equalwidth_font48);
LV_FONT_DECLARE(my_equalwidth_font64);
LV_FONT_DECLARE(equalwidth_128);
LV_FONT_DECLARE(equalwidth_48);

/*********************
 *      DEFINES
 *********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void ui_init(void);

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

#if LV_USE_OS != LV_OS_FREERTOS

int main(int argc, char **argv)
{
  (void)argc; /*Unused*/
  (void)argv; /*Unused*/

  /*Initialize LVGL*/
  lv_init();

  /*Initialize the HAL (display, input devices, tick) for LVGL*/
  sdl_hal_init(720, 720);

  ui_init();

  while (1)
  {
    /* Periodically call the lv_task handler.
     * It could be done in a timer interrupt or an OS task too.*/
    uint32_t sleep_time_ms = lv_timer_handler();
    if (sleep_time_ms == LV_NO_TIMER_READY)
    {
      sleep_time_ms = LV_DEF_REFR_PERIOD;
    }
#ifdef _MSC_VER
    Sleep(sleep_time_ms);
#else
    usleep(sleep_time_ms * 1000);
#endif
  }

  return 0;
}

#endif

/**********************
 *   STATIC FUNCTIONS
 **********************/

#define EVENT_CMD_FROM_APP 0x1000

#define IMG_SRC(file_name) "A:src/img/" file_name

static const char *arc_pic = IMG_SRC("arc.png");
static const char *auto_mode_pic = IMG_SRC("auto_mode.png");
static const char *cooling_pic = IMG_SRC("cooling.png");
static const char *fan_pic = IMG_SRC("fan.png");
static const char *fan1_pic = IMG_SRC("fan1.png");
static const char *fan2_pic = IMG_SRC("fan2.png");
static const char *fan3_pic = IMG_SRC("fan3.png");
static const char *fanA_pic = IMG_SRC("fanA.png");
static const char *heating_pic = IMG_SRC("heating.png");
static const char *humidity_pic = IMG_SRC("humidity.png");
static const char *bluetooth_pic = IMG_SRC("bluetooth.png");
static const char *sip_call_pic = IMG_SRC("sip_call.png");
static const char *room_service_pic = IMG_SRC("room_service.png");
static const char *call_pic = IMG_SRC("call.png");
static const char *hangup_pic = IMG_SRC("hangup.png");
static const char *microphone_on_pic = IMG_SRC("microphone_on.png");
static const char *microphone_off_pic = IMG_SRC("microphone_off.png");
static const char *dial_pic = IMG_SRC("dial.png");
static const char *speaker_on_pic = IMG_SRC("speaker_on.png");
static const char *speaker_off_pic = IMG_SRC("speaker_off.png");
static const char *backspace_pic = IMG_SRC("backspace.png");
static const char *back_pic = IMG_SRC("back.png");
static const char *clean_pic = IMG_SRC("clean.png");
static const char *power_pic = IMG_SRC("power.png");
static const char *temperature_pic = IMG_SRC("temperature.png");
static const char *tv_pic = IMG_SRC("tv.png");
static const char *volume_pic = IMG_SRC("volume.png");
static const char *wind_big_pic = IMG_SRC("wind_big.png");
static const char *dnd_pic = IMG_SRC("dnd.png");

static void ble_slave_cmd_post_to_eventLoop(uint8_t *cmd, uint8_t len, uint32_t event)
{
  (void)event;
  if (cmd == NULL || len == 0)
  {
    printf("cmd: <empty>\n");
    return;
  }

  printf("cmd[%u]: ", (unsigned int)len);
  for (uint8_t i = 0; i < len; i++)
  {
    printf("0x%02X", cmd[i]);
    if (i + 1 < len)
    {
      printf(" ");
    }
  }
  printf("\n");
}

static void bsp_display_lock(uint8_t slot)
{
}
static void bsp_display_unlock(void)
{
}

#define CONTRAL_PAGE_WIDTH 720  // 控制页面宽度
#define CONTRAL_PAGE_HEIGHT 620 // 控制页面高度

#define GRID_SIZE 150
#define GRID_SPACING 20

#define SHOW_OBJ_WIDTH (GRID_SIZE * 4 + GRID_SPACING * 3)
#define SHOW_OBJ_HEIGHT (GRID_SIZE * 3 + GRID_SPACING * 2)

#define AREA_BG_COLOR lv_color_hex(0x202020) // 部件区域背景颜色

#define TIP_BAR_WIDTH 700 // 圆形提示栏宽度
#define TIP_BAR_HEIGHT 30 // 圆形提示栏高度

#define CONTROL_WIDGET_ROWS 3 // 部件显示行数
#define CONTROL_WIDGET_COLS 4 // 部件显示列数

#define OPEN_STATE_DEFAULT_COLOR lv_color_hex(0xE0E0E0)  // 图标打开状态颜色
#define CLOSE_STATE_DEFAULT_COLOR lv_color_hex(0x404040) // 图标关闭状态颜色
#define CLEAN_ON_COLOR lv_color_hex(0x00FF00)            // clean开启按钮颜色
#define DND_ON_COLOR lv_color_hex(0xFF0000)              // dnd开启按钮颜色

typedef enum
{
  GRID_TYPE_1X1 = 1,
  GRID_TYPE_1X2_OR_2X1 = 2,
  GRID_TYPE_2X2 = 4,
  GRID_TYPE_3X2 = 6
} grid_type_t;

enum
{
  DEVICE_TYPE_UNKNOW = 0,
  DEVICE_TYPE_RCU_CLEAN,
  DEVICE_TYPE_RCU_DND,
  DEVICE_TYPE_RCU_ONOFF,
  DEVICE_TYPE_RCU_DIMMING,
  DEVICE_TYPE_RCU_IO,
  DEVICE_TYPE_RCU_VIRTUAL,
  DEVICE_TYPE_RCU_SCENE,
  DEVICE_TYPE_CURTAIN_SWITCH,
  DEVICE_TYPE_CURTAIN_SLIDER,
  DEVICE_TYPE_THERMOSTAT,
  DEVICE_TYPE_BT_BOX,
  DEVICE_TYPE_CLEAN_DND,
};

// 图标开关
typedef struct img_switch
{
  uint8_t status;
  uint8_t update_status;
  lv_obj_t *switch_imgbtn; // 图标开关部件
  char *img_addr;          // 图标描述符
} img_switch_t;

// 窗帘开关
typedef struct curtain_switch
{
  uint8_t status;
  uint8_t update_status;
  lv_obj_t *up_imgbtn;           // 上图标开关部件
  lv_obj_t *down_imgbtn;         // 下图标开关部件
  lv_image_dsc_t *up_img_addr;   // 上图标描述符
  lv_image_dsc_t *down_img_addr; // 下图标描述符
} curtain_switch_t;

// 滑块
typedef struct dimmer_slider
{
  uint8_t status;
  uint8_t update_status;
  lv_obj_t *slider_obj;    // 滑块部件
  lv_obj_t *slider_imgbtn; // 滑块图标部件
  char *slider_img_addr;   // 滑块图标描述符
} dimmer_slider_t;

// 温控器
typedef struct thermostat
{
  uint8_t power;
  uint8_t mode;
  uint8_t fan;
  float temp;
  float temp_setting;
  float rh;

  uint8_t fan_support;
  uint8_t mode_support;
  float cool_min_setting;
  float cool_max_setting;
  bool use_celsius;
  float heat_min_setting;
  float heat_max_setting;

  lv_obj_t *power_img;
  lv_obj_t *mode_img;
  lv_obj_t *fan_img;

  lv_obj_t *power_imgbtn;
  lv_obj_t *mode_imgbtn;
  lv_obj_t *fan_imgbtn;
  lv_obj_t *temp_arc;
  lv_obj_t *temp_set_label;
  lv_obj_t *temp_label;
  lv_obj_t *rh_label;
} thermostat_t;

typedef struct bt_box
{
  uint8_t volume;
  bool tv; // tv or bluetooth
  char password[5];

  lv_obj_t *volume_slider;
  lv_obj_t *source_btn;
  lv_obj_t *source_img;
  lv_obj_t *password_label;
} bt_box_t;

typedef struct clean_dnd
{
  bool clean_on;
  bool dnd_on;
  lv_obj_t *clean_btn;
  lv_obj_t *dnd_btn;
  lv_obj_t *clean_label;
  lv_obj_t *dnd_label;
} clean_dnd_t;

typedef struct device_node
{
  uint8_t macAddress[6];
  uint8_t slot;
  uint8_t gang;
  uint8_t device_type;
  uint8_t gateway[6];
  uint8_t page_index;
  uint8_t show_index;
  uint8_t angle;
  uint32_t invincible_timestamp;
  union
  {
    img_switch_t *img_switch;
    dimmer_slider_t *dimmer_slider;
    curtain_switch_t *curtain_switch;
    thermostat_t *thermostat;
    bt_box_t *bt_box;
    clean_dnd_t *clean_dnd;
  };
  struct device_node *next; // 链表后继
} device_node_t;

// 控制页面结构体链表
typedef struct contral_page
{
  char *page_name;            // 标识控制页面名字
  lv_obj_t *contral_page_obj; // 控制页面部件
  struct contral_page *next;  // 链表后继
} contral_page_t;

static contral_page_t *contral_page_list = NULL;
static lv_obj_t *contral_page_tileview = NULL; // 控制页面平铺视图部件
static lv_obj_t *tip_bar_obj = NULL;           // 圆形提示栏显示存放部件

static device_node_t *device_node_list = NULL;

/***************************************************控制页面上滑回退手势事件处理函数*****************************************************/
#define BACK_AREA_MIN_Y ((720) - (100))

static void contral_back_gesture_event_cb(lv_event_t *e)
{
  lv_event_code_t code = lv_event_get_code(e);
  if (code != LV_EVENT_GESTURE)
    return;

  lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
  lv_indev_t *indev = lv_indev_get_act();

  if (dir == LV_DIR_TOP)
  {
    lv_point_t point, vect;
    lv_indev_get_point(indev, &point);
    lv_indev_get_vect(indev, &vect);

    lv_point_t start_point;
    start_point.x = point.x - vect.x;
    start_point.y = point.y - vect.y;

    if (start_point.y >= BACK_AREA_MIN_Y)
    { // 判断手势起始点是否在屏幕底部100像素区域内
      lv_obj_remove_event_cb(lv_scr_act(), contral_back_gesture_event_cb);
      if (contral_page_tileview && tip_bar_obj)
      {
        lv_obj_add_flag(contral_page_tileview, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(tip_bar_obj, LV_OBJ_FLAG_HIDDEN);
      }
      // lv_main_page_draw();
    }
  }
}

/***************************************************更新圆形提示框事件处理函数*****************************************************/
static void update_circle_tip_cb(lv_event_t *e)
{
  lv_obj_t *tileview = lv_event_get_target(e);
  lv_obj_t *tip_bar_obj = lv_event_get_user_data(e);

  lv_obj_t *current_tile = lv_tileview_get_tile_active(tileview);

  uint8_t page_num = 0;

  contral_page_t *contral_page_p = contral_page_list;
  while (contral_page_p != NULL)
  {
    if (contral_page_p->contral_page_obj == current_tile) // 查找当前页面位于链表的位置
    {
      break;
    }
    page_num++;
    contral_page_p = contral_page_p->next;
  }
  for (uint8_t i = 0; i < lv_obj_get_child_cnt(tip_bar_obj); i++)
  {
    if (i == page_num)
    {
      lv_obj_t *child = lv_obj_get_child(tip_bar_obj, page_num); // 标识当前页面 透明度最高
      lv_obj_set_style_bg_opa(child, LV_OPA_100, 0);
    }
    else
    {
      lv_obj_t *child = lv_obj_get_child(tip_bar_obj, i); // 标识其他页面 透明度调低
      lv_obj_set_style_bg_opa(child, LV_OPA_20, 0);
    }
  }
}

/***************************************************控制页面初始化页面绘制*****************************************************/
static void tileview_fast_anim_cb(lv_event_t *e)
{
  lv_obj_t *tv = lv_event_get_target(e);
  lv_obj_t *act_tile = lv_tileview_get_tile_active(tv);
  if (!act_tile)
    return;

  // 当前 tile 的列/行
  uint16_t col = lv_obj_get_x(act_tile) / lv_obj_get_width(tv);
  uint16_t row = lv_obj_get_y(act_tile) / lv_obj_get_height(tv);

  lv_coord_t x = col * lv_obj_get_width(tv);
  lv_coord_t y = row * lv_obj_get_height(tv);

  uint16_t anim_time = 50; // 快速动画时间
  lv_obj_scroll_to(tv, x, y, anim_time);
}

static void contral_page_tileview_tip_bar_draw(void)
{
  if (contral_page_tileview == NULL)
  {
    // 创建平铺视图
    contral_page_tileview = lv_tileview_create(lv_scr_act());
    lv_obj_set_size(contral_page_tileview, CONTRAL_PAGE_WIDTH, CONTRAL_PAGE_HEIGHT);
    lv_obj_align(contral_page_tileview, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_set_style_bg_color(contral_page_tileview, lv_color_black(), 0);
    lv_obj_set_style_border_width(contral_page_tileview, 0, 1);
    lv_obj_set_scrollbar_mode(contral_page_tileview, LV_SCROLLBAR_MODE_OFF);

    lv_obj_add_event_cb(contral_page_tileview, tileview_fast_anim_cb, LV_EVENT_SCROLL_END, NULL);
    lv_obj_add_event_cb(contral_page_tileview, tileview_fast_anim_cb, LV_EVENT_RELEASED, NULL);
  }
  if (tip_bar_obj == NULL)
  {
    // 创建圆形提示栏存放部件
    tip_bar_obj = lv_obj_create(lv_scr_act());
    lv_obj_set_size(tip_bar_obj, CONTRAL_PAGE_WIDTH, TIP_BAR_HEIGHT);
    lv_obj_align(tip_bar_obj, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_set_style_bg_color(tip_bar_obj, lv_color_black(), 0);
    lv_obj_set_style_radius(tip_bar_obj, 0, 0);
    lv_obj_set_style_border_width(tip_bar_obj, 0, 0);
    lv_obj_remove_flag(tip_bar_obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_layout(tip_bar_obj, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(tip_bar_obj, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(tip_bar_obj, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    lv_obj_add_event_cb(contral_page_tileview, update_circle_tip_cb, LV_EVENT_VALUE_CHANGED, tip_bar_obj);
  }
}

static device_node_t *add_deivce_node(void)
{
  device_node_t *newNode = (device_node_t *)malloc(sizeof(device_node_t));
  memset(newNode, 0, sizeof(device_node_t));
  newNode->next = NULL;
  if (device_node_list == NULL)
  {
    device_node_list = newNode;
    return newNode;
  }
  device_node_t *temp = device_node_list;
  while (temp->next != NULL)
  {
    temp = temp->next;
  }
  temp->next = newNode;
  return newNode;
}

static void node_timer_cb(void *arg)
{
}

static img_switch_t *add_img_switch_node(const char *img_addr)
{
  img_switch_t *node = (img_switch_t *)malloc(sizeof(img_switch_t));
  memset(node, 0, sizeof(img_switch_t));
  node->img_addr = img_addr;
  return node;
}

static dimmer_slider_t *add_dimmer_slider_node(const char *img_addr)
{
  dimmer_slider_t *node = (dimmer_slider_t *)malloc(sizeof(dimmer_slider_t));
  memset(node, 0, sizeof(dimmer_slider_t));
  node->slider_img_addr = img_addr;
  return node;
}

static thermostat_t *add_thermostat_node(void)
{
  thermostat_t *node = (thermostat_t *)malloc(sizeof(thermostat_t));
  memset(node, 0, sizeof(thermostat_t));
  return node;
}

static bt_box_t *add_bt_box_node(void)
{
  bt_box_t *node = (bt_box_t *)malloc(sizeof(bt_box_t));
  memset(node, 0, sizeof(bt_box_t));
  return node;
}

static clean_dnd_t *add_clean_dnd_node(void)
{
  clean_dnd_t *node = (clean_dnd_t *)malloc(sizeof(clean_dnd_t));
  if (node == NULL)
  {
    return NULL;
  }
  memset(node, 0, sizeof(clean_dnd_t));
  return node;
}

static void set_circle_switch_style(lv_obj_t *switch_btn, lv_obj_t *switch_img, lv_color_t icon_color, lv_color_t bg_color)
{
  if (switch_btn == NULL)
  {
    return;
  }
  if (switch_img != NULL)
  {
    lv_obj_set_style_img_recolor(switch_img, icon_color, LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(switch_img, LV_OPA_COVER, LV_STATE_DEFAULT);
  }
  lv_obj_set_style_bg_color(switch_btn, bg_color, LV_STATE_DEFAULT);
}

static void disable_button_shadow(lv_obj_t *btn)
{
  if (btn == NULL)
  {
    return;
  }
  lv_obj_set_style_shadow_width(btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_opa(btn, LV_OPA_TRANSP, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_offset_x(btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_offset_y(btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_obj_set_style_shadow_width(btn, 0, LV_PART_MAIN | LV_STATE_PRESSED);
  lv_obj_set_style_shadow_opa(btn, LV_OPA_TRANSP, LV_PART_MAIN | LV_STATE_PRESSED);
  lv_obj_set_style_shadow_offset_x(btn, 0, LV_PART_MAIN | LV_STATE_PRESSED);
  lv_obj_set_style_shadow_offset_y(btn, 0, LV_PART_MAIN | LV_STATE_PRESSED);

  lv_obj_set_style_shadow_width(btn, 0, LV_PART_MAIN | LV_STATE_CHECKED);
  lv_obj_set_style_shadow_opa(btn, LV_OPA_TRANSP, LV_PART_MAIN | LV_STATE_CHECKED);
  lv_obj_set_style_shadow_offset_x(btn, 0, LV_PART_MAIN | LV_STATE_CHECKED);
  lv_obj_set_style_shadow_offset_y(btn, 0, LV_PART_MAIN | LV_STATE_CHECKED);

  lv_obj_set_style_shadow_width(btn, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
  lv_obj_set_style_shadow_opa(btn, LV_OPA_TRANSP, LV_PART_MAIN | LV_STATE_FOCUSED);
  lv_obj_set_style_shadow_offset_x(btn, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
  lv_obj_set_style_shadow_offset_y(btn, 0, LV_PART_MAIN | LV_STATE_FOCUSED);

  lv_obj_set_style_shadow_width(btn, 0, LV_PART_MAIN | LV_STATE_DISABLED);
  lv_obj_set_style_shadow_opa(btn, LV_OPA_TRANSP, LV_PART_MAIN | LV_STATE_DISABLED);
  lv_obj_set_style_shadow_offset_x(btn, 0, LV_PART_MAIN | LV_STATE_DISABLED);
  lv_obj_set_style_shadow_offset_y(btn, 0, LV_PART_MAIN | LV_STATE_DISABLED);
}

/*********************************************控制页面图标开关状态切换事件回调函数************************************************/
static void update_switch_imgbtn_status(device_node_t *device)
{
  if (device == NULL)
  {
    return;
  }
  bsp_display_lock(0);

  lv_color_t color = CLOSE_STATE_DEFAULT_COLOR;
  if (device->device_type == DEVICE_TYPE_RCU_DND)
  {
    color = lv_color_hex(0xFF0000);
  }
  else if (device->device_type == DEVICE_TYPE_RCU_CLEAN)
  {
    color = lv_color_hex(0x00FF00);
  }

  lv_obj_t *switch_img = lv_obj_get_child(device->img_switch->switch_imgbtn, 0);
  if (device->img_switch->status == 1) // 设置为打开状态
  {
    set_circle_switch_style(device->img_switch->switch_imgbtn, switch_img, color, OPEN_STATE_DEFAULT_COLOR);
  }
  else if (device->img_switch->status == 0) // 设置为关闭状态
  {
    set_circle_switch_style(device->img_switch->switch_imgbtn, switch_img, OPEN_STATE_DEFAULT_COLOR, CLOSE_STATE_DEFAULT_COLOR);
  }
  bsp_display_unlock();
}

// 图标开关点击事件回调函数
static void contral_page_switch_imgbtn_click_cb(lv_event_t *e)
{
  lv_obj_t *switch_imgbtn = lv_event_get_target(e);
  if (switch_imgbtn == NULL)
  {
    return;
  }
  device_node_t *device = lv_event_get_user_data(e);
  if (device == NULL)
  {
    return;
  }
  if (device->img_switch->status == 1) // 当前为打开状态 切换为关闭状态
  {
    device->img_switch->status = 0;
  }
  else
  {
    device->img_switch->status = 1;
  }
  uint8_t cmd[128] = {0};
  cmd[0] = 0x15;
  memcpy(&cmd[1], device->gateway, 6);
  memcpy(&cmd[8], device->macAddress, 6);
  if (device->device_type == DEVICE_TYPE_RCU_CLEAN ||
      device->device_type == DEVICE_TYPE_RCU_DND ||
      device->device_type == DEVICE_TYPE_RCU_VIRTUAL)
  {
    cmd[7] = 11;
    cmd[14] = 0x97;
    cmd[15] = 0x21;
    cmd[16] = 0x03;
    cmd[17] = device->gang;
    cmd[18] = device->img_switch->status;
    ble_slave_cmd_post_to_eventLoop(cmd, 19, EVENT_CMD_FROM_APP);
  }
  else if (device->device_type == DEVICE_TYPE_RCU_ONOFF)
  {
    cmd[7] = 12;
    cmd[14] = 0x97;
    cmd[15] = 0x1F;
    cmd[16] = device->slot;
    cmd[17] = 0x80;
    cmd[18] = 0x00;
    cmd[19] = device->gang;
    if (cmd[19] > 0)
    {
      cmd[19]--;
      cmd[19] = ((1 << cmd[19]) << 4) | (device->img_switch->status ? (1 << cmd[19]) : 0);
      ble_slave_cmd_post_to_eventLoop(cmd, 20, EVENT_CMD_FROM_APP);
    }
  }
  else if (device->device_type == DEVICE_TYPE_RCU_IO)
  {
    cmd[7] = 11;
    cmd[14] = 0x97;
    cmd[15] = 0x21;
    cmd[16] = 0x01;
    cmd[17] = device->gang;
    cmd[18] = device->img_switch->status;
    ble_slave_cmd_post_to_eventLoop(cmd, 19, EVENT_CMD_FROM_APP);
  }
  else if (device->device_type == DEVICE_TYPE_RCU_SCENE)
  {
    cmd[7] = 10;
    cmd[14] = 0x8F;
    cmd[15] = 0x02;
    cmd[16] = 0x00;
    cmd[17] = device->gang;
    if (device->img_switch->status)
    {
      ble_slave_cmd_post_to_eventLoop(cmd, 18, EVENT_CMD_FROM_APP);
    }
    else
    {
      device->img_switch->status = 1;
    }
  }
  update_switch_imgbtn_status(device);
}

/*********************************************控制页面窗帘图标状态切换事件回调函数************************************************/
static void update_curtain_imgbtn_status(device_node_t *device)
{
  if (device == NULL)
  {
    return;
  }
  bsp_display_lock(0);
  lv_obj_t *up_img = lv_obj_get_child(device->curtain_switch->up_imgbtn, 0);
  lv_obj_t *down_img = lv_obj_get_child(device->curtain_switch->down_imgbtn, 0);
  if (device->curtain_switch->status == 0)
  {
    set_circle_switch_style(device->curtain_switch->up_imgbtn, up_img, OPEN_STATE_DEFAULT_COLOR, CLOSE_STATE_DEFAULT_COLOR);
    set_circle_switch_style(device->curtain_switch->down_imgbtn, down_img, CLOSE_STATE_DEFAULT_COLOR, OPEN_STATE_DEFAULT_COLOR);
  }
  else if (device->curtain_switch->status == 100)
  {
    set_circle_switch_style(device->curtain_switch->up_imgbtn, up_img, CLOSE_STATE_DEFAULT_COLOR, OPEN_STATE_DEFAULT_COLOR);
    set_circle_switch_style(device->curtain_switch->down_imgbtn, down_img, OPEN_STATE_DEFAULT_COLOR, CLOSE_STATE_DEFAULT_COLOR);
  }
  else
  {
    set_circle_switch_style(device->curtain_switch->up_imgbtn, up_img, OPEN_STATE_DEFAULT_COLOR, CLOSE_STATE_DEFAULT_COLOR);
    set_circle_switch_style(device->curtain_switch->down_imgbtn, down_img, OPEN_STATE_DEFAULT_COLOR, CLOSE_STATE_DEFAULT_COLOR);
  }
  bsp_display_unlock();
}

static void contral_page_curtain_imgbtn_click_cb(lv_event_t *e)
{
  lv_obj_t *switch_imgbtn = lv_event_get_target(e);
  if (switch_imgbtn == NULL)
  {
    return;
  }
  device_node_t *device = lv_event_get_user_data(e);
  if (device == NULL)
  {
    return;
  }
  if (device->curtain_switch->up_imgbtn == switch_imgbtn)
  {
    device->curtain_switch->status = 100;
  }
  else if (device->curtain_switch->down_imgbtn == switch_imgbtn)
  {
    device->curtain_switch->status = 0;
  }
  update_curtain_imgbtn_status(device);
  if (device->device_type == DEVICE_TYPE_CURTAIN_SWITCH)
  {
    uint8_t cmd[128] = {0};
    cmd[0] = 0x15;
    memcpy(&cmd[1], device->gateway, 6);
    memcpy(&cmd[8], device->macAddress, 6);
    cmd[7] = 9;
    cmd[14] = 0x89;
    cmd[15] = 0x20 + device->gang - 1;
    cmd[16] = device->curtain_switch->status;
    ble_slave_cmd_post_to_eventLoop(cmd, 17, EVENT_CMD_FROM_APP);
  }
}

static void update_clean_dnd_status(device_node_t *device)
{
  if (device == NULL || device->clean_dnd == NULL)
  {
    return;
  }

  bsp_display_lock(0);

  if (device->clean_dnd->clean_btn != NULL && device->clean_dnd->dnd_btn != NULL)
  {
    if (device->clean_dnd->clean_on)
    {
      lv_obj_set_style_bg_color(device->clean_dnd->clean_btn, OPEN_STATE_DEFAULT_COLOR, 0);
      if (device->clean_dnd->clean_label != NULL)
      {
        lv_obj_set_style_img_recolor(device->clean_dnd->clean_label, CLEAN_ON_COLOR, 0);
        lv_obj_set_style_img_recolor_opa(device->clean_dnd->clean_label, LV_OPA_COVER, 0);
      }
    }
    else
    {
      lv_obj_set_style_bg_color(device->clean_dnd->clean_btn, CLOSE_STATE_DEFAULT_COLOR, 0);
      if (device->clean_dnd->clean_label != NULL)
      {
        lv_obj_set_style_img_recolor(device->clean_dnd->clean_label, OPEN_STATE_DEFAULT_COLOR, 0);
        lv_obj_set_style_img_recolor_opa(device->clean_dnd->clean_label, LV_OPA_COVER, 0);
      }
    }

    if (device->clean_dnd->dnd_on)
    {
      lv_obj_set_style_bg_color(device->clean_dnd->dnd_btn, OPEN_STATE_DEFAULT_COLOR, 0);
      if (device->clean_dnd->dnd_label != NULL)
      {
        lv_obj_set_style_img_recolor(device->clean_dnd->dnd_label, DND_ON_COLOR, 0);
        lv_obj_set_style_img_recolor_opa(device->clean_dnd->dnd_label, LV_OPA_COVER, 0);
      }
    }
    else
    {
      lv_obj_set_style_bg_color(device->clean_dnd->dnd_btn, CLOSE_STATE_DEFAULT_COLOR, 0);
      if (device->clean_dnd->dnd_label != NULL)
      {
        lv_obj_set_style_img_recolor(device->clean_dnd->dnd_label, OPEN_STATE_DEFAULT_COLOR, 0);
        lv_obj_set_style_img_recolor_opa(device->clean_dnd->dnd_label, LV_OPA_COVER, 0);
      }
    }
  }

  bsp_display_unlock();
}

static void contral_page_clean_dnd_imgbtn_click_cb(lv_event_t *e)
{
  lv_obj_t *switch_imgbtn = lv_event_get_target(e);
  if (switch_imgbtn == NULL)
  {
    return;
  }

  device_node_t *device = lv_event_get_user_data(e);
  if (device == NULL || device->clean_dnd == NULL || device->device_type != DEVICE_TYPE_CLEAN_DND)
  {
    return;
  }

  if (switch_imgbtn == device->clean_dnd->clean_btn)
  {
    bool next_clean_on = !device->clean_dnd->clean_on;
    device->clean_dnd->clean_on = next_clean_on;
    if (next_clean_on)
    {
      device->clean_dnd->dnd_on = false;
    }
  }
  else if (switch_imgbtn == device->clean_dnd->dnd_btn)
  {
    bool next_dnd_on = !device->clean_dnd->dnd_on;
    device->clean_dnd->dnd_on = next_dnd_on;
    if (next_dnd_on)
    {
      device->clean_dnd->clean_on = false;
    }
  }

  update_clean_dnd_status(device);
}

/*********************************************控制页面滑块值变化事件回调函数************************************************/
static void update_slider_value(device_node_t *device)
{
  if (device == NULL)
  {
    return;
  }
  bsp_display_lock(0);
  lv_slider_set_value(device->dimmer_slider->slider_obj, device->dimmer_slider->status, LV_ANIM_OFF);
  bsp_display_unlock();
}

static void contral_page_slider_value_change_cb(lv_event_t *e)
{
  lv_obj_t *slider = lv_event_get_target(e);
  device_node_t *device = lv_event_get_user_data(e);
  if (device == NULL)
  {
    printf("get slider user data error");
    return;
  }
  device->dimmer_slider->status = lv_slider_get_value(slider); // 获取滑块当前值并赋值节点状态值
  if (device->device_type == DEVICE_TYPE_RCU_DIMMING)
  {
    uint8_t cmd[128] = {0};
    cmd[0] = 0x15;
    memcpy(&cmd[1], device->gateway, 6);
    memcpy(&cmd[8], device->macAddress, 6);
    cmd[7] = 12;
    cmd[14] = 0x97;
    cmd[15] = 0x1F;
    cmd[16] = device->slot;
    cmd[17] = 0x89;
    cmd[18] = 0x20 + device->gang - 1;
    cmd[19] = device->dimmer_slider->status * 255 / 100;
    ble_slave_cmd_post_to_eventLoop(cmd, 20, EVENT_CMD_FROM_APP);
  }
  else if (device->device_type == DEVICE_TYPE_CURTAIN_SLIDER)
  {
    uint8_t cmd[128] = {0};
    cmd[0] = 0x15;
    memcpy(&cmd[1], device->gateway, 6);
    memcpy(&cmd[8], device->macAddress, 6);
    cmd[7] = 9;
    cmd[14] = 0x89;
    cmd[15] = 0x20 + device->gang - 1;
    cmd[16] = device->dimmer_slider->status;
    ble_slave_cmd_post_to_eventLoop(cmd, 17, EVENT_CMD_FROM_APP);
  }
}

/*********************************************控制页面蓝牙盒子状态切换事件回调函数************************************************/
static void update_bt_box_status(device_node_t *device)
{
  if (device == NULL || device->bt_box == NULL)
  {
    return;
  }

  bsp_display_lock(0);

  if (device->bt_box->volume_slider != NULL)
  {
    lv_slider_set_value(device->bt_box->volume_slider, device->bt_box->volume, LV_ANIM_OFF);
  }

  if (device->bt_box->password_label != NULL)
  {
    if (device->bt_box->password[0] == 0 || device->bt_box->password[1] == 0 || device->bt_box->password[2] == 0 || device->bt_box->password[3] == 0)
    {
      lv_label_set_text(device->bt_box->password_label, "----");
    }
    else
    {
      lv_label_set_text_fmt(device->bt_box->password_label, "%c%c%c%c",
                            device->bt_box->password[0],
                            device->bt_box->password[1],
                            device->bt_box->password[2],
                            device->bt_box->password[3]);
    }
  }

  if (device->bt_box->source_img != NULL)
  {
    lv_image_set_src(device->bt_box->source_img, device->bt_box->tv ? bluetooth_pic : tv_pic);
  }

  bsp_display_unlock();
}

static void contral_page_bt_slider_value_change_cb(lv_event_t *e)
{
  lv_obj_t *slider = lv_event_get_target(e);
  device_node_t *device = lv_event_get_user_data(e);
  if (slider == NULL ||
      device == NULL ||
      device->bt_box == NULL ||
      device->device_type != DEVICE_TYPE_BT_BOX)
  {
    return;
  }

  device->bt_box->volume = lv_slider_get_value(slider);
}

static void contral_page_bt_imgbtn_click_cb(lv_event_t *e)
{
  lv_obj_t *switch_imgbtn = lv_event_get_target(e);
  if (switch_imgbtn == NULL)
  {
    return;
  }

  device_node_t *device = lv_event_get_user_data(e);
  if (device == NULL ||
      device->bt_box == NULL ||
      device->device_type != DEVICE_TYPE_BT_BOX)
  {
    return;
  }

  device->bt_box->tv = !device->bt_box->tv;
  update_bt_box_status(device);
}

/*********************************************控制页面温控器状态切换事件回调函数************************************************/
enum
{
  THERMOSTAT_POWER_OFF = 0,
  THERMOSTAT_POWER_ON,
};

enum
{
  THERMOSTAT_MODE_WIND = 0,
  THERMOSTAT_MODE_HEATING,
  THERMOSTAT_MODE_COOLING,
  THERMOSTAT_MODE_AUTO,
};

enum
{
  THERMOSTAT_FAN_OFF = 0,
  THERMOSTAT_FAN_AUTO,
  THERMOSTAT_FAN_1,
  THERMOSTAT_FAN_2,
  THERMOSTAT_FAN_3,
};

static float convert_celsius_to_fahrenheit(device_node_t *device, float celsius)
{
  if (device->thermostat->use_celsius)
  {
    return celsius;
  }
  return celsius * 1.8 + 32;
}

static float convert_fahrenheit_to_celsius(device_node_t *device, float fahrenheit)
{
  if (device->thermostat->use_celsius)
  {
    return fahrenheit;
  }
  return (fahrenheit - 32) / 1.8;
}

static void update_thermostat_touchable_status(device_node_t *device)
{
  if (device == NULL || device->thermostat == NULL)
  {
    return;
  }

  bool power_on = (device->thermostat->power == THERMOSTAT_POWER_ON);
  if (power_on)
  {
    if (device->thermostat->temp_arc != NULL)
    {
      lv_obj_add_flag(device->thermostat->temp_arc, LV_OBJ_FLAG_CLICKABLE);
    }
    if (device->thermostat->mode_imgbtn != NULL)
    {
      lv_obj_add_flag(device->thermostat->mode_imgbtn, LV_OBJ_FLAG_CLICKABLE);
    }
    if (device->thermostat->fan_imgbtn != NULL)
    {
      lv_obj_add_flag(device->thermostat->fan_imgbtn, LV_OBJ_FLAG_CLICKABLE);
    }
  }
  else
  {
    if (device->thermostat->temp_arc != NULL)
    {
      lv_obj_remove_flag(device->thermostat->temp_arc, LV_OBJ_FLAG_CLICKABLE);
    }
    if (device->thermostat->mode_imgbtn != NULL)
    {
      lv_obj_remove_flag(device->thermostat->mode_imgbtn, LV_OBJ_FLAG_CLICKABLE);
    }
    if (device->thermostat->fan_imgbtn != NULL)
    {
      lv_obj_remove_flag(device->thermostat->fan_imgbtn, LV_OBJ_FLAG_CLICKABLE);
    }
  }
}

static void update_thermostat_imgbtn_status(device_node_t *device)
{
  if (device == NULL || device->thermostat == NULL)
  {
    return;
  }
  bsp_display_lock(0);
  lv_image_set_src(device->thermostat->power_img, power_pic);
  if (device->thermostat->mode == THERMOSTAT_MODE_WIND)
  {
    lv_image_set_src(device->thermostat->mode_img, wind_big_pic);
  }
  else if (device->thermostat->mode == THERMOSTAT_MODE_HEATING)
  {
    lv_image_set_src(device->thermostat->mode_img, heating_pic);
  }
  else if (device->thermostat->mode == THERMOSTAT_MODE_COOLING)
  {
    lv_image_set_src(device->thermostat->mode_img, cooling_pic);
  }
  else if (device->thermostat->mode == THERMOSTAT_MODE_AUTO)
  {
    lv_image_set_src(device->thermostat->mode_img, auto_mode_pic);
  }
  if (device->thermostat->fan == THERMOSTAT_FAN_OFF)
  {
    lv_image_set_src(device->thermostat->fan_img, fan_pic);
  }
  else if (device->thermostat->fan == THERMOSTAT_FAN_AUTO)
  {
    lv_image_set_src(device->thermostat->fan_img, fanA_pic);
  }
  else if (device->thermostat->fan == THERMOSTAT_FAN_1)
  {
    lv_image_set_src(device->thermostat->fan_img, fan1_pic);
  }
  else if (device->thermostat->fan == THERMOSTAT_FAN_2)
  {
    lv_image_set_src(device->thermostat->fan_img, fan2_pic);
  }
  else if (device->thermostat->fan == THERMOSTAT_FAN_3)
  {
    lv_image_set_src(device->thermostat->fan_img, fan3_pic);
  }

  float temp_setting_min = device->thermostat->cool_min_setting;
  float temp_setting_max = device->thermostat->cool_max_setting;
  if (device->thermostat->mode != THERMOSTAT_MODE_HEATING)
  {
    temp_setting_min = device->thermostat->cool_min_setting;
    temp_setting_max = device->thermostat->cool_max_setting;
  }
  else
  {
    temp_setting_min = device->thermostat->heat_min_setting;
    temp_setting_max = device->thermostat->heat_max_setting;
  }
  if (device->thermostat->mode == THERMOSTAT_MODE_HEATING)
  {
    if (device->thermostat->temp_setting < temp_setting_min)
    {
      device->thermostat->temp_setting = temp_setting_min;
    }
    else if (device->thermostat->temp_setting > temp_setting_max)
    {
      device->thermostat->temp_setting = temp_setting_max;
    }
  }
  else
  {
    if (device->thermostat->temp_setting < temp_setting_min)
    {
      device->thermostat->temp_setting = temp_setting_min;
    }
    else if (device->thermostat->temp_setting > temp_setting_max)
    {
      device->thermostat->temp_setting = temp_setting_max;
    }
  }
  lv_arc_set_range(device->thermostat->temp_arc, (int16_t)temp_setting_min, (int16_t)temp_setting_max);
  lv_arc_set_value(device->thermostat->temp_arc, (int16_t)device->thermostat->temp_setting);
  lv_label_set_text_fmt(device->thermostat->temp_set_label, "%d", (int8_t)convert_celsius_to_fahrenheit(device, device->thermostat->temp_setting));

  if (device->thermostat->use_celsius)
  {
    lv_label_set_text_fmt(device->thermostat->temp_label, "%d°C", (int8_t)convert_celsius_to_fahrenheit(device, device->thermostat->temp));
  }
  else
  {
    lv_label_set_text_fmt(device->thermostat->temp_label, "%d°F", (int8_t)convert_celsius_to_fahrenheit(device, device->thermostat->temp));
  }
  lv_label_set_text_fmt(device->thermostat->rh_label, "%d%%", (int8_t)device->thermostat->rh);
  update_thermostat_touchable_status(device);

  bsp_display_unlock();
}

static void contral_page_arc_value_changed_cb(lv_event_t *e)
{
  lv_obj_t *arc = lv_event_get_target(e);
  int32_t value = lv_arc_get_value(arc);
  device_node_t *device = lv_event_get_user_data(e);
  if (device == NULL ||
      device->thermostat == NULL ||
      device->device_type != DEVICE_TYPE_THERMOSTAT)
  {
    return;
  }
  if (device->thermostat->power == THERMOSTAT_POWER_OFF)
  {
    return;
  }
  device->thermostat->temp_setting = convert_fahrenheit_to_celsius(device, (float)value);
  lv_label_set_text_fmt(device->thermostat->temp_set_label, "%d", (int8_t)convert_celsius_to_fahrenheit(device, device->thermostat->temp_setting));
  if (device->device_type == DEVICE_TYPE_THERMOSTAT && lv_event_get_code(e) == LV_EVENT_RELEASED)
  {
    uint8_t cmd[128] = {0};
    cmd[0] = 0x15;
    memcpy(&cmd[1], device->gateway, 6);
    memcpy(&cmd[8], device->macAddress, 6);
    cmd[14] = 0x94;
    cmd[15] = 0x06;
    cmd[16] = 0x00;
    cmd[17] = 0x00;
    // cmd[7] = 15;
    // cmd[18] = 0x04;
    // memcpy(&cmd[19], &device->thermostat->temp_setting, sizeof(float));
    // ble_slave_cmd_post_to_eventLoop(cmd, 23, EVENT_CMD_FROM_APP);
    cmd[7] = 12;
    cmd[18] = 0x01;
    cmd[19] = (uint8_t)device->thermostat->temp_setting;
    ble_slave_cmd_post_to_eventLoop(cmd, 20, EVENT_CMD_FROM_APP);
  }
}

static void contral_page_thermostat_imgbtn_click_cb(lv_event_t *e)
{
  lv_obj_t *switch_imgbtn = lv_event_get_target(e);
  if (switch_imgbtn == NULL)
  {
    return;
  }
  device_node_t *device = lv_event_get_user_data(e);
  if (device == NULL ||
      device->thermostat == NULL ||
      device->device_type != DEVICE_TYPE_THERMOSTAT)
  {
    return;
  }
  if (device->thermostat->power == THERMOSTAT_POWER_OFF &&
      switch_imgbtn != device->thermostat->power_imgbtn)
  {
    return;
  }
  if (switch_imgbtn == device->thermostat->power_imgbtn)
  {
    device->thermostat->power = !device->thermostat->power;
    if (device->thermostat->power == THERMOSTAT_POWER_ON)
    {
      lv_obj_set_style_img_recolor(device->thermostat->power_img, CLOSE_STATE_DEFAULT_COLOR, 0);
      lv_obj_set_style_bg_color(device->thermostat->power_imgbtn, OPEN_STATE_DEFAULT_COLOR, 0);
    }
    else
    {
      lv_obj_set_style_img_recolor(device->thermostat->power_img, OPEN_STATE_DEFAULT_COLOR, 0);
      lv_obj_set_style_bg_color(device->thermostat->power_imgbtn, CLOSE_STATE_DEFAULT_COLOR, 0);
    }
    update_thermostat_touchable_status(device);
    uint8_t cmd[128] = {0};
    cmd[0] = 0x15;
    memcpy(&cmd[1], device->gateway, 6);
    memcpy(&cmd[8], device->macAddress, 6);
    cmd[7] = 12;
    cmd[14] = 0x94;
    cmd[15] = 0x03;
    cmd[16] = 0x00;
    cmd[17] = 0x00;
    cmd[18] = 0x01;
    cmd[19] = device->thermostat->power;
    ble_slave_cmd_post_to_eventLoop(cmd, 20, EVENT_CMD_FROM_APP);
  }
  else if (switch_imgbtn == device->thermostat->mode_imgbtn)
  {
    if (device->thermostat->mode_support == 0)
    {
      device->thermostat->mode++;
      if (device->thermostat->mode > 2)
      {
        device->thermostat->mode = 0;
      }
    }
    else if (device->thermostat->mode_support == 1)
    {
      device->thermostat->mode++;
      if (device->thermostat->mode == 2)
      {
        device->thermostat->mode++;
      }
      if (device->thermostat->mode > 2)
      {
        device->thermostat->mode = 0;
      }
    }
    else if (device->thermostat->mode_support == 2)
    {
      device->thermostat->mode++;
      if (device->thermostat->mode == 1)
      {
        device->thermostat->mode++;
      }
      if (device->thermostat->mode > 2)
      {
        device->thermostat->mode = 0;
      }
    }
    else if (device->thermostat->mode_support == 3)
    {
      device->thermostat->mode++;
      if (device->thermostat->mode > 3)
      {
        device->thermostat->mode = 0;
      }
    }
    if (device->thermostat->mode == THERMOSTAT_MODE_WIND)
    {
      lv_image_set_src(device->thermostat->mode_img, wind_big_pic);
    }
    else if (device->thermostat->mode == THERMOSTAT_MODE_HEATING)
    {
      lv_image_set_src(device->thermostat->mode_img, heating_pic);
    }
    else if (device->thermostat->mode == THERMOSTAT_MODE_COOLING)
    {
      lv_image_set_src(device->thermostat->mode_img, cooling_pic);
    }
    else if (device->thermostat->mode == THERMOSTAT_MODE_AUTO)
    {
      lv_image_set_src(device->thermostat->mode_img, auto_mode_pic);
    }
    float temp_setting_min = device->thermostat->cool_min_setting;
    float temp_setting_max = device->thermostat->cool_max_setting;
    if (device->thermostat->mode != THERMOSTAT_MODE_HEATING)
    {
      temp_setting_min = device->thermostat->cool_min_setting;
      temp_setting_max = device->thermostat->cool_max_setting;
    }
    else
    {
      temp_setting_min = device->thermostat->heat_min_setting;
      temp_setting_max = device->thermostat->heat_max_setting;
    }
    if (device->thermostat->mode == THERMOSTAT_MODE_HEATING)
    {
      if (device->thermostat->temp_setting < temp_setting_min)
      {
        device->thermostat->temp_setting = temp_setting_min;
      }
      else if (device->thermostat->temp_setting > temp_setting_max)
      {
        device->thermostat->temp_setting = temp_setting_max;
      }
    }
    else
    {
      if (device->thermostat->temp_setting < temp_setting_min)
      {
        device->thermostat->temp_setting = temp_setting_min;
      }
      else if (device->thermostat->temp_setting > temp_setting_max)
      {
        device->thermostat->temp_setting = temp_setting_max;
      }
    }
    lv_arc_set_range(device->thermostat->temp_arc, (int16_t)temp_setting_min, (int16_t)temp_setting_max);
    lv_arc_set_value(device->thermostat->temp_arc, (int16_t)device->thermostat->temp_setting);
    lv_label_set_text_fmt(device->thermostat->temp_set_label, "%d", (int8_t)convert_celsius_to_fahrenheit(device, device->thermostat->temp_setting));
    uint8_t cmd[128] = {0};
    cmd[0] = 0x15;
    memcpy(&cmd[1], device->gateway, 6);
    memcpy(&cmd[8], device->macAddress, 6);
    cmd[7] = 12;
    cmd[14] = 0x94;
    cmd[15] = 0x04;
    cmd[16] = 0x00;
    cmd[17] = 0x00;
    cmd[18] = 0x01;
    cmd[19] = device->thermostat->mode;
    ble_slave_cmd_post_to_eventLoop(cmd, 20, EVENT_CMD_FROM_APP);
  }
  else if (switch_imgbtn == device->thermostat->fan_imgbtn)
  {
    if (device->thermostat->fan_support == 0)
    {
      device->thermostat->fan = 0;
    }
    else if (device->thermostat->fan_support == 1)
    {
      device->thermostat->fan = 2;
    }
    else if (device->thermostat->fan_support == 2)
    {
      device->thermostat->fan++;
      if (device->thermostat->fan > 3)
      {
        device->thermostat->fan = 1;
      }
    }
    else if (device->thermostat->fan_support == 3)
    {
      device->thermostat->fan++;
      if (device->thermostat->fan > 4)
      {
        device->thermostat->fan = 1;
      }
    }
    if (device->thermostat->fan == THERMOSTAT_FAN_OFF)
    {
      lv_image_set_src(device->thermostat->fan_img, fan_pic);
    }
    else if (device->thermostat->fan == THERMOSTAT_FAN_AUTO)
    {
      lv_image_set_src(device->thermostat->fan_img, fanA_pic);
    }
    else if (device->thermostat->fan == THERMOSTAT_FAN_1)
    {
      lv_image_set_src(device->thermostat->fan_img, fan1_pic);
    }
    else if (device->thermostat->fan == THERMOSTAT_FAN_2)
    {
      lv_image_set_src(device->thermostat->fan_img, fan2_pic);
    }
    else if (device->thermostat->fan == THERMOSTAT_FAN_3)
    {
      lv_image_set_src(device->thermostat->fan_img, fan3_pic);
    }
    uint8_t cmd[128] = {0};
    cmd[0] = 0x15;
    memcpy(&cmd[1], device->gateway, 6);
    memcpy(&cmd[8], device->macAddress, 6);
    cmd[7] = 12;
    cmd[14] = 0x94;
    cmd[15] = 0x05;
    cmd[16] = 0x00;
    cmd[17] = 0x00;
    cmd[18] = 0x01;
    cmd[19] = device->thermostat->fan;
    ble_slave_cmd_post_to_eventLoop(cmd, 20, EVENT_CMD_FROM_APP);
  }
}

/*********************************************检查部件位置函数************************************************/
/**
 * @brief 检查指定位置是否能放置部件
 * @param type 部件类型
 * @param start_row 起始行
 * @param start_col 起始列
 * @return true表示可以放置，false表示不能放置
 */
static bool can_place_widget(grid_type_t grid, uint8_t angle, uint8_t start_row, uint8_t start_col, bool grid_occupied[][CONTROL_WIDGET_COLS])
{
  // 检查边界条件
  if (start_row >= CONTROL_WIDGET_ROWS || start_col >= CONTROL_WIDGET_COLS)
    return false;

  if (grid == GRID_TYPE_1X1) // 占用1格
  {
    // 按钮占用1格，只需检查当前单元格
    return !grid_occupied[start_row][start_col];
  }
  else if (grid == GRID_TYPE_1X2_OR_2X1) // 占用2格
  {
    if (angle == 0) // 占用1x2，检查当前行连续两列
    {
      if (start_col + 1 >= CONTROL_WIDGET_COLS)
        return false;
      return !grid_occupied[start_row][start_col] &&
             !grid_occupied[start_row][start_col + 1];
    }
    else if (angle == 1) // 占用2x1，检查当前列连续两行
    {
      if (start_row + 1 >= CONTROL_WIDGET_ROWS)
        return false;
      return !grid_occupied[start_row][start_col] &&
             !grid_occupied[start_row + 1][start_col];
    }
    else if (angle == 2) // 占用1x2，检查当前行连续两列
    {
      if (start_col < 1)
        return false;
      return !grid_occupied[start_row][start_col] &&
             !grid_occupied[start_row][start_col - 1];
    }
    else if (angle == 3) // 占用2x1，检查当前列连续两行
    {
      if (start_row < 1)
        return false;
      return !grid_occupied[start_row][start_col] &&
             !grid_occupied[start_row - 1][start_col];
    }
  }
  else if (grid == GRID_TYPE_2X2) // 占用4格
  {
    if (start_row + 1 >= CONTROL_WIDGET_ROWS || start_col + 1 >= CONTROL_WIDGET_COLS)
    {
      return false;
    }
    return !grid_occupied[start_row][start_col] &&
           !grid_occupied[start_row][start_col + 1] &&
           !grid_occupied[start_row + 1][start_col] &&
           !grid_occupied[start_row + 1][start_col + 1];
  }
  else if (grid == GRID_TYPE_3X2) // 占用6格
  {
    if (start_row + 1 >= CONTROL_WIDGET_ROWS || start_col + 2 >= CONTROL_WIDGET_COLS)
    {
      return false;
    }
    return !grid_occupied[start_row][start_col] &&
           !grid_occupied[start_row][start_col + 1] &&
           !grid_occupied[start_row][start_col + 2] &&
           !grid_occupied[start_row + 1][start_col] &&
           !grid_occupied[start_row + 1][start_col + 1] &&
           !grid_occupied[start_row + 1][start_col + 2];
  }
  return false;
}

/**
 * @brief 标记网格占用状态
 * @param type 部件类型
 * @param start_row 起始行
 * @param start_col 起始列
 */
static void mark_grid_occupied(grid_type_t grid, uint8_t angle, int start_row, int start_col, bool grid_occupied[][CONTROL_WIDGET_COLS])
{
  switch (grid)
  {
  case GRID_TYPE_1X1:
    grid_occupied[start_row][start_col] = true;
    break;
  case GRID_TYPE_1X2_OR_2X1:
    if (angle == 0)
    {
      grid_occupied[start_row][start_col] = true;
      grid_occupied[start_row][start_col + 1] = true;
      break;
    }
    else if (angle == 1)
    {
      grid_occupied[start_row][start_col] = true;
      grid_occupied[start_row + 1][start_col] = true;
      break;
    }
    else if (angle == 2)
    {
      grid_occupied[start_row][start_col] = true;
      grid_occupied[start_row][start_col - 1] = true;
      break;
    }
    else if (angle == 3)
    {
      grid_occupied[start_row][start_col] = true;
      grid_occupied[start_row - 1][start_col] = true;
      break;
    }
    break;
  case GRID_TYPE_2X2:
    grid_occupied[start_row][start_col] = true;
    grid_occupied[start_row][start_col + 1] = true;
    grid_occupied[start_row + 1][start_col] = true;
    grid_occupied[start_row + 1][start_col + 1] = true;
    break;
  case GRID_TYPE_3X2:
    grid_occupied[start_row][start_col] = true;
    grid_occupied[start_row][start_col + 1] = true;
    grid_occupied[start_row][start_col + 2] = true;
    grid_occupied[start_row + 1][start_col] = true;
    grid_occupied[start_row + 1][start_col + 1] = true;
    grid_occupied[start_row + 1][start_col + 2] = true;
    break;
  default:
    break;
  }
}

/***********************************************创建单个控制页面并绘制函数*****************************************************/
static void create_one_contral_page(const char *page_name, uint8_t page_index)
{
  if (contral_page_list == NULL)
  {
    contral_page_tileview_tip_bar_draw();
  }
  contral_page_t *newNode = (contral_page_t *)malloc(sizeof(contral_page_t));
  memset(newNode, 0, sizeof(contral_page_t));
  newNode->page_name = strdup(page_name);
  newNode->next = NULL;
  if (contral_page_list == NULL)
  {
    contral_page_list = newNode;
  }
  else
  {
    contral_page_t *temp = contral_page_list;
    while (temp->next != NULL)
    {
      temp = temp->next;
    }
    temp->next = newNode;
  }
  // 控制页面部件
  lv_obj_t *contral_page_obj = lv_tileview_add_tile(contral_page_tileview, page_index - 1, 0, LV_DIR_HOR); // 创建平铺视图子页面
  lv_obj_set_align(contral_page_obj, LV_ALIGN_BOTTOM_MID);
  lv_obj_set_style_border_width(contral_page_obj, 1, 0);

  // 房间名字标签
  lv_obj_t *room_label = lv_label_create(contral_page_obj);
  lv_obj_set_size(room_label, CONTRAL_PAGE_WIDTH, 60);
  lv_obj_set_align(room_label, LV_ALIGN_TOP_MID);
  lv_obj_set_style_align(room_label, LV_TEXT_ALIGN_CENTER, 0);
  lv_label_set_text_fmt(room_label, "%s", page_name);
  lv_obj_set_style_text_color(room_label, lv_color_white(), 0);
  lv_obj_set_style_text_align(room_label, LV_TEXT_ALIGN_CENTER, 0);
  lv_obj_set_style_text_font(room_label, &my_equalwidth_font48, 0);
  lv_obj_set_style_pad_top(room_label, 10, 0);

  // 创建存放容器
  lv_obj_t *show_page_obj = lv_obj_create(contral_page_obj);
  lv_obj_set_size(show_page_obj, SHOW_OBJ_WIDTH, SHOW_OBJ_HEIGHT);
  lv_obj_align(show_page_obj, LV_ALIGN_BOTTOM_MID, 0, -30);
  lv_obj_set_style_bg_color(show_page_obj, lv_color_black(), 0);
  lv_obj_set_style_border_width(show_page_obj, 0, 0);
  lv_obj_set_style_radius(show_page_obj, 35, 0);
  lv_obj_set_scrollbar_mode(show_page_obj, LV_SCROLLBAR_MODE_OFF);
  lv_obj_remove_flag(show_page_obj, LV_OBJ_FLAG_SCROLLABLE);

  static lv_coord_t col_dsc[] = {
      GRID_SIZE, GRID_SIZE, GRID_SIZE, GRID_SIZE, // 4列固定宽度
      LV_GRID_TEMPLATE_LAST};

  static lv_coord_t row_dsc[] = {
      GRID_SIZE, GRID_SIZE, GRID_SIZE, // 3行固定高度
      LV_GRID_TEMPLATE_LAST};

  lv_obj_set_grid_dsc_array(show_page_obj, col_dsc, row_dsc);
  lv_obj_set_layout(show_page_obj, LV_LAYOUT_GRID);

  lv_obj_set_style_pad_all(show_page_obj, 0, 0);               // 容器内边距
  lv_obj_set_style_pad_row(show_page_obj, GRID_SPACING, 0);    // 行间隙
  lv_obj_set_style_pad_column(show_page_obj, GRID_SPACING, 0); // 列间隙

  bool grid_occupied[CONTROL_WIDGET_ROWS][CONTROL_WIDGET_COLS] = {false}; // 网格占用状态初始化

  device_node_t *device = device_node_list;
  while (device != NULL)
  {
    if (device->page_index == page_index)
    {
      int row = (device->show_index - 1) / CONTROL_WIDGET_COLS; // 计算行列位置 索引从0开始
      int col = (device->show_index - 1) % CONTROL_WIDGET_COLS;
      if (row < 0 || row >= CONTROL_WIDGET_ROWS || col < 0 || col >= CONTROL_WIDGET_COLS)
      { // 非法索引跳过
        printf("show_index error");
        goto next_device;
      }

      if (device->device_type == DEVICE_TYPE_RCU_CLEAN ||
          device->device_type == DEVICE_TYPE_RCU_DND ||
          device->device_type == DEVICE_TYPE_RCU_ONOFF ||
          device->device_type == DEVICE_TYPE_RCU_IO ||
          device->device_type == DEVICE_TYPE_RCU_VIRTUAL ||
          device->device_type == DEVICE_TYPE_RCU_SCENE)
      {
        if (!can_place_widget(GRID_TYPE_1X1, device->angle, row, col, grid_occupied))
        {
          printf("can not found local");
          goto next_device;
        }
        // 开关图标存放背景部件
        lv_obj_t *switch_obj = lv_button_create(show_page_obj);
        lv_obj_set_size(switch_obj, (GRID_SIZE - 10), (GRID_SIZE - 10));
        lv_obj_set_style_radius(switch_obj, LV_RADIUS_CIRCLE, 0);
        lv_obj_set_style_bg_opa(switch_obj, LV_OPA_COVER, 0);
        lv_obj_set_style_bg_color(switch_obj, CLOSE_STATE_DEFAULT_COLOR, 0);
        lv_obj_set_style_border_width(switch_obj, 0, 0);
        lv_obj_set_style_pad_all(switch_obj, 0, 0);
        disable_button_shadow(switch_obj);
        lv_obj_remove_flag(switch_obj, LV_OBJ_FLAG_SCROLLABLE);
        // 开关图标
        lv_obj_t *switch_icon = lv_image_create(switch_obj);
        lv_obj_set_size(switch_icon, (GRID_SIZE - 10), (GRID_SIZE - 10));
        lv_image_set_src(switch_icon, device->img_switch->img_addr);
        lv_obj_center(switch_icon);
        lv_obj_set_style_img_recolor(switch_icon, OPEN_STATE_DEFAULT_COLOR, 0);
        lv_obj_set_style_img_recolor_opa(switch_icon, LV_OPA_COVER, LV_STATE_DEFAULT);
        lv_obj_add_event_cb(switch_obj, contral_page_switch_imgbtn_click_cb, LV_EVENT_CLICKED, device);
        // 设置网格单元格（1x1）
        lv_obj_set_grid_cell(switch_obj, LV_GRID_ALIGN_CENTER, col, 1, LV_GRID_ALIGN_CENTER, row, 1);
        mark_grid_occupied(GRID_TYPE_1X1, 0, row, col, grid_occupied); // 标记网格占用状态
        device->img_switch->switch_imgbtn = switch_obj;                // 赋值图标开关部件
      }
      else if (device->device_type == DEVICE_TYPE_CURTAIN_SLIDER ||
               device->device_type == DEVICE_TYPE_RCU_DIMMING)
      {
        if (!can_place_widget(GRID_TYPE_1X2_OR_2X1, device->angle, row, col, grid_occupied))
        {
          printf("can not found local");
          goto next_device;
        }

        // 滑块部件
        lv_obj_t *slider = lv_slider_create(show_page_obj);
        lv_obj_set_style_radius(slider, 35, LV_PART_MAIN);
        lv_obj_set_style_radius(slider, 35, LV_PART_INDICATOR);
        lv_obj_set_style_bg_color(slider, AREA_BG_COLOR, LV_PART_MAIN);
        lv_obj_set_style_bg_color(slider, OPEN_STATE_DEFAULT_COLOR, LV_PART_INDICATOR);
        lv_obj_set_style_bg_opa(slider, 255, LV_PART_MAIN);
        lv_obj_set_style_bg_opa(slider, 255, LV_PART_INDICATOR);
        lv_obj_remove_style(slider, NULL, LV_PART_KNOB);
        lv_slider_set_range(slider, 0, 100);
        lv_slider_set_value(slider, 0, LV_ANIM_OFF);
        lv_obj_remove_flag(slider, LV_OBJ_FLAG_GESTURE_BUBBLE);
        lv_obj_add_event_cb(slider, contral_page_slider_value_change_cb, LV_EVENT_RELEASED, device);

        // 滑块图标
        lv_obj_t *slider_imgbtn = lv_image_create(slider);
        lv_obj_set_size(slider_imgbtn, 60, 60);
        lv_obj_set_style_opa(slider_imgbtn, LV_OPA_100, 0);
        lv_image_set_src(slider_imgbtn, device->dimmer_slider->slider_img_addr);

        if (device->angle == 0)
        {
          lv_obj_set_size(slider, (GRID_SIZE * 2 + GRID_SPACING), GRID_SIZE);
          lv_obj_align(slider_imgbtn, LV_ALIGN_LEFT_MID, 5, 0);
          lv_obj_set_grid_cell(slider, LV_GRID_ALIGN_CENTER, col, 2, LV_GRID_ALIGN_CENTER, row, 1);
          mark_grid_occupied(GRID_TYPE_1X2_OR_2X1, device->angle, row, col, grid_occupied);
        }
        else if (device->angle == 1)
        {
          lv_obj_set_size(slider, GRID_SIZE, (GRID_SIZE * 2 + GRID_SPACING));
          lv_obj_align(slider_imgbtn, LV_ALIGN_TOP_MID, 0, 5);
          lv_obj_set_grid_cell(slider, LV_GRID_ALIGN_CENTER, col, 1, LV_GRID_ALIGN_CENTER, row, 2);
          mark_grid_occupied(GRID_TYPE_1X2_OR_2X1, device->angle, row, col, grid_occupied);
        }
        else if (device->angle == 2)
        {
          lv_obj_set_size(slider, (GRID_SIZE * 2 + GRID_SPACING), GRID_SIZE);
          lv_obj_align(slider_imgbtn, LV_ALIGN_RIGHT_MID, -5, 0);
          lv_obj_set_grid_cell(slider, LV_GRID_ALIGN_CENTER, col - 1, 2, LV_GRID_ALIGN_CENTER, row, 1);
          mark_grid_occupied(GRID_TYPE_1X2_OR_2X1, device->angle, row, col, grid_occupied);
        }
        else if (device->angle == 3)
        {
          lv_obj_set_size(slider, GRID_SIZE, (GRID_SIZE * 2 + GRID_SPACING));
          lv_obj_align(slider_imgbtn, LV_ALIGN_BOTTOM_MID, 0, -5);
          lv_obj_set_grid_cell(slider, LV_GRID_ALIGN_CENTER, col, 1, LV_GRID_ALIGN_CENTER, row - 1, 2);
          mark_grid_occupied(GRID_TYPE_1X2_OR_2X1, device->angle, row, col, grid_occupied);
        }
        device->dimmer_slider->slider_obj = slider;           // 赋值滑块部件
        device->dimmer_slider->slider_imgbtn = slider_imgbtn; // 赋值滑块图标部件
      }
      else if (device->device_type == DEVICE_TYPE_CURTAIN_SWITCH)
      {
        if (!can_place_widget(GRID_TYPE_1X2_OR_2X1, device->angle, row, col, grid_occupied))
        {
          printf("can not found local");
          goto next_device;
        }

        // 窗帘区域存放背景部件
        lv_obj_t *curtain_obj = lv_obj_create(show_page_obj);
        lv_obj_set_style_bg_color(curtain_obj, AREA_BG_COLOR, 0);
        lv_obj_set_style_radius(curtain_obj, 35, 0);
        lv_obj_set_style_border_width(curtain_obj, 0, 0);
        lv_obj_remove_flag(curtain_obj, LV_OBJ_FLAG_SCROLLABLE);

        // 开关图标存放背景部件1
        lv_obj_t *switch_obj1 = lv_button_create(curtain_obj);
        lv_obj_set_size(switch_obj1, 120, 120);
        lv_obj_set_style_radius(switch_obj1, LV_RADIUS_CIRCLE, 0);
        lv_obj_set_style_bg_opa(switch_obj1, LV_OPA_COVER, 0);
        lv_obj_set_style_bg_color(switch_obj1, CLOSE_STATE_DEFAULT_COLOR, 0);
        lv_obj_set_style_border_width(switch_obj1, 0, 0);
        lv_obj_set_style_pad_all(switch_obj1, 0, 0);
        disable_button_shadow(switch_obj1);

        // 开关图标1
        lv_obj_t *switch_icon1 = lv_image_create(switch_obj1);
        lv_image_set_src(switch_icon1, device->curtain_switch->down_img_addr);
        lv_obj_center(switch_icon1);
        lv_obj_set_size(switch_icon1, 60, 60);
        lv_obj_set_style_img_recolor(switch_icon1, OPEN_STATE_DEFAULT_COLOR, 0);
        lv_obj_set_style_img_recolor_opa(switch_icon1, LV_OPA_COVER, LV_STATE_DEFAULT);
        lv_obj_add_event_cb(switch_obj1, contral_page_curtain_imgbtn_click_cb, LV_EVENT_CLICKED, device);

        // 开关图标存放背景部件2
        lv_obj_t *switch_obj2 = lv_button_create(curtain_obj);
        lv_obj_set_size(switch_obj2, 120, 120);
        lv_obj_set_style_radius(switch_obj2, LV_RADIUS_CIRCLE, 0);
        lv_obj_set_style_bg_opa(switch_obj2, LV_OPA_COVER, 0);
        lv_obj_set_style_bg_color(switch_obj2, CLOSE_STATE_DEFAULT_COLOR, 0);
        lv_obj_set_style_border_width(switch_obj2, 0, 0);
        lv_obj_set_style_pad_all(switch_obj2, 0, 0);
        disable_button_shadow(switch_obj2);

        // 开关图标2
        lv_obj_t *switch_icon2 = lv_image_create(switch_obj2);
        lv_image_set_src(switch_icon2, device->curtain_switch->up_img_addr);
        lv_obj_center(switch_icon2);
        lv_obj_set_size(switch_icon2, 60, 60);
        lv_obj_set_style_img_recolor(switch_icon2, OPEN_STATE_DEFAULT_COLOR, 0);
        lv_obj_set_style_img_recolor_opa(switch_icon2, LV_OPA_COVER, LV_STATE_DEFAULT);
        lv_obj_add_event_cb(switch_obj2, contral_page_curtain_imgbtn_click_cb, LV_EVENT_CLICKED, device);

        if (device->angle == 0)
        {
          lv_obj_set_size(curtain_obj, (GRID_SIZE * 2 + GRID_SPACING), GRID_SIZE);
          mark_grid_occupied(GRID_TYPE_1X2_OR_2X1, device->angle, row, col, grid_occupied);
          lv_obj_set_grid_cell(curtain_obj, LV_GRID_ALIGN_CENTER, col, 2, LV_GRID_ALIGN_CENTER, row, 1);
        }
        else if (device->angle == 1)
        {
          lv_obj_set_size(curtain_obj, GRID_SIZE, (GRID_SIZE * 2 + GRID_SPACING));
          mark_grid_occupied(GRID_TYPE_1X2_OR_2X1, device->angle, row, col, grid_occupied);
          lv_obj_set_grid_cell(curtain_obj, LV_GRID_ALIGN_CENTER, col, 1, LV_GRID_ALIGN_CENTER, row, 2);
        }
        else if (device->angle == 2)
        {
          lv_obj_set_size(curtain_obj, (GRID_SIZE * 2 + GRID_SPACING), GRID_SIZE);
          mark_grid_occupied(GRID_TYPE_1X2_OR_2X1, device->angle, row, col, grid_occupied);
          lv_obj_set_grid_cell(curtain_obj, LV_GRID_ALIGN_CENTER, col - 1, 2, LV_GRID_ALIGN_CENTER, row, 1);
        }
        else if (device->angle == 3)
        {
          lv_obj_set_size(curtain_obj, GRID_SIZE, (GRID_SIZE * 2 + GRID_SPACING));
          mark_grid_occupied(GRID_TYPE_1X2_OR_2X1, device->angle, row, col, grid_occupied);
          lv_obj_set_grid_cell(curtain_obj, LV_GRID_ALIGN_CENTER, col, 1, LV_GRID_ALIGN_CENTER, row - 1, 2);
        }

        device->curtain_switch->up_imgbtn = switch_obj1;   // 赋值窗帘上图标部件
        device->curtain_switch->down_imgbtn = switch_obj2; // 赋值窗帘下图标部件
      }
      else if (device->device_type == DEVICE_TYPE_CLEAN_DND)
      {
        if (!can_place_widget(GRID_TYPE_1X2_OR_2X1, device->angle, row, col, grid_occupied))
        {
          printf("can not found local");
          goto next_device;
        }

        lv_obj_t *clean_dnd_obj = lv_obj_create(show_page_obj);
        lv_obj_set_style_bg_color(clean_dnd_obj, AREA_BG_COLOR, 0);
        lv_obj_set_style_radius(clean_dnd_obj, 35, 0);
        lv_obj_set_style_border_width(clean_dnd_obj, 0, 0);
        lv_obj_remove_flag(clean_dnd_obj, LV_OBJ_FLAG_SCROLLABLE);

        lv_obj_t *dnd_btn = lv_button_create(clean_dnd_obj);
        lv_obj_set_size(dnd_btn, 120, 120);
        lv_obj_set_style_radius(dnd_btn, LV_RADIUS_CIRCLE, 0);
        lv_obj_set_style_bg_opa(dnd_btn, LV_OPA_COVER, 0);
        lv_obj_set_style_bg_color(dnd_btn, CLOSE_STATE_DEFAULT_COLOR, 0);
        lv_obj_set_style_border_width(dnd_btn, 0, 0);
        lv_obj_set_style_pad_all(dnd_btn, 0, 0);
        disable_button_shadow(dnd_btn);
        lv_obj_add_event_cb(dnd_btn, contral_page_clean_dnd_imgbtn_click_cb, LV_EVENT_CLICKED, device);

        lv_obj_t *dnd_label = lv_image_create(dnd_btn);
        lv_image_set_src(dnd_label, dnd_pic);
        lv_obj_set_size(dnd_label, 60, 60);
        lv_obj_center(dnd_label);

        lv_obj_t *clean_btn = lv_button_create(clean_dnd_obj);
        lv_obj_set_size(clean_btn, 120, 120);
        lv_obj_set_style_radius(clean_btn, LV_RADIUS_CIRCLE, 0);
        lv_obj_set_style_bg_opa(clean_btn, LV_OPA_COVER, 0);
        lv_obj_set_style_bg_color(clean_btn, CLOSE_STATE_DEFAULT_COLOR, 0);
        lv_obj_set_style_border_width(clean_btn, 0, 0);
        lv_obj_set_style_pad_all(clean_btn, 0, 0);
        disable_button_shadow(clean_btn);
        lv_obj_add_event_cb(clean_btn, contral_page_clean_dnd_imgbtn_click_cb, LV_EVENT_CLICKED, device);

        lv_obj_t *clean_label = lv_image_create(clean_btn);
        lv_image_set_src(clean_label, clean_pic);
        lv_obj_set_size(clean_label, 60, 60);
        lv_obj_center(clean_label);

        if (device->angle == 0)
        {
          lv_obj_set_size(clean_dnd_obj, (GRID_SIZE * 2 + GRID_SPACING), GRID_SIZE);
          lv_obj_align(dnd_btn, LV_ALIGN_LEFT_MID, 0, 0);
          lv_obj_align(clean_btn, LV_ALIGN_RIGHT_MID, 0, 0);
          mark_grid_occupied(GRID_TYPE_1X2_OR_2X1, device->angle, row, col, grid_occupied);
          lv_obj_set_grid_cell(clean_dnd_obj, LV_GRID_ALIGN_CENTER, col, 2, LV_GRID_ALIGN_CENTER, row, 1);
        }
        else if (device->angle == 1)
        {
          lv_obj_set_size(clean_dnd_obj, GRID_SIZE, (GRID_SIZE * 2 + GRID_SPACING));
          lv_obj_align(dnd_btn, LV_ALIGN_TOP_MID, 0, 0);
          lv_obj_align(clean_btn, LV_ALIGN_BOTTOM_MID, 0, 0);
          mark_grid_occupied(GRID_TYPE_1X2_OR_2X1, device->angle, row, col, grid_occupied);
          lv_obj_set_grid_cell(clean_dnd_obj, LV_GRID_ALIGN_CENTER, col, 1, LV_GRID_ALIGN_CENTER, row, 2);
        }
        else if (device->angle == 2)
        {
          lv_obj_set_size(clean_dnd_obj, (GRID_SIZE * 2 + GRID_SPACING), GRID_SIZE);
          lv_obj_align(dnd_btn, LV_ALIGN_RIGHT_MID, 0, 0);
          lv_obj_align(clean_btn, LV_ALIGN_LEFT_MID, 0, 0);
          mark_grid_occupied(GRID_TYPE_1X2_OR_2X1, device->angle, row, col, grid_occupied);
          lv_obj_set_grid_cell(clean_dnd_obj, LV_GRID_ALIGN_CENTER, col - 1, 2, LV_GRID_ALIGN_CENTER, row, 1);
        }
        else if (device->angle == 3)
        {
          lv_obj_set_size(clean_dnd_obj, GRID_SIZE, (GRID_SIZE * 2 + GRID_SPACING));
          lv_obj_align(dnd_btn, LV_ALIGN_BOTTOM_MID, 0, 0);
          lv_obj_align(clean_btn, LV_ALIGN_TOP_MID, 0, 0);
          mark_grid_occupied(GRID_TYPE_1X2_OR_2X1, device->angle, row, col, grid_occupied);
          lv_obj_set_grid_cell(clean_dnd_obj, LV_GRID_ALIGN_CENTER, col, 1, LV_GRID_ALIGN_CENTER, row - 1, 2);
        }

        device->clean_dnd->clean_btn = clean_btn;
        device->clean_dnd->dnd_btn = dnd_btn;
        device->clean_dnd->clean_label = clean_label;
        device->clean_dnd->dnd_label = dnd_label;
        update_clean_dnd_status(device);
      }
      else if (device->device_type == DEVICE_TYPE_BT_BOX)
      {
        if (!can_place_widget(GRID_TYPE_2X2, device->angle, row, col, grid_occupied))
        {
          printf("can not found local");
          goto next_device;
        }

        lv_obj_t *bt_box = lv_obj_create(show_page_obj);
        lv_obj_set_size(bt_box, (GRID_SIZE * 2 + GRID_SPACING), (GRID_SIZE * 2 + GRID_SPACING));
        lv_obj_set_style_bg_color(bt_box, AREA_BG_COLOR, 0);
        lv_obj_set_style_radius(bt_box, 35, 0);
        lv_obj_set_style_border_width(bt_box, 0, 0);
        lv_obj_remove_flag(bt_box, LV_OBJ_FLAG_SCROLLABLE);

        lv_coord_t bt_slider_w = (GRID_SIZE * 2 - GRID_SPACING);
        lv_coord_t bt_slider_h = (GRID_SIZE - GRID_SPACING);

        lv_obj_t *volume_slider = lv_slider_create(bt_box);
        lv_obj_set_size(volume_slider, bt_slider_w, bt_slider_h);
        lv_obj_align(volume_slider, LV_ALIGN_BOTTOM_MID, 0, 0);
        lv_obj_set_style_radius(volume_slider, 35, LV_PART_MAIN);
        lv_obj_set_style_radius(volume_slider, 35, LV_PART_INDICATOR);
        lv_obj_set_style_bg_color(volume_slider, CLOSE_STATE_DEFAULT_COLOR, LV_PART_MAIN);
        lv_obj_set_style_bg_color(volume_slider, OPEN_STATE_DEFAULT_COLOR, LV_PART_INDICATOR);
        lv_obj_set_style_bg_opa(volume_slider, LV_OPA_COVER, LV_PART_MAIN);
        lv_obj_set_style_bg_opa(volume_slider, LV_OPA_COVER, LV_PART_INDICATOR);
        lv_obj_remove_style(volume_slider, NULL, LV_PART_KNOB);
        lv_slider_set_range(volume_slider, 0, 100);
        lv_obj_remove_flag(volume_slider, LV_OBJ_FLAG_GESTURE_BUBBLE);
        lv_obj_add_event_cb(volume_slider, contral_page_bt_slider_value_change_cb, LV_EVENT_RELEASED, device);

        lv_obj_t *volume_icon = lv_label_create(volume_slider);
        lv_obj_set_style_text_font(volume_icon, &lv_font_montserrat_36, 0);
        lv_label_set_text(volume_icon, LV_SYMBOL_AUDIO);
        lv_obj_set_style_text_color(volume_icon, lv_color_white(), 0);
        lv_obj_align(volume_icon, LV_ALIGN_LEFT_MID, 10, 0);

        lv_obj_t *info_row = lv_obj_create(bt_box);
        lv_obj_set_size(info_row, bt_slider_w, bt_slider_h);
        lv_obj_align(info_row, LV_ALIGN_TOP_MID, 0, -10);
        lv_obj_set_style_bg_opa(info_row, LV_OPA_TRANSP, 0);
        lv_obj_set_style_border_width(info_row, 0, 0);
        lv_obj_set_style_pad_left(info_row, 0, 0);
        lv_obj_set_style_pad_right(info_row, 0, 0);
        lv_obj_set_style_pad_top(info_row, 0, 0);
        lv_obj_set_style_pad_bottom(info_row, 0, 0);
        lv_obj_remove_flag(info_row, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_set_layout(info_row, LV_LAYOUT_FLEX);
        lv_obj_set_flex_flow(info_row, LV_FLEX_FLOW_ROW);
        lv_obj_set_flex_align(info_row, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

        lv_obj_t *source_btn = lv_button_create(info_row);
        lv_obj_set_size(source_btn, 110, 110);
        lv_obj_align(source_btn, LV_ALIGN_LEFT_MID, 0, 0);
        lv_obj_set_style_radius(source_btn, LV_RADIUS_CIRCLE, 0);
        lv_obj_set_style_bg_opa(source_btn, LV_OPA_COVER, 0);
        lv_obj_set_style_bg_color(source_btn, CLOSE_STATE_DEFAULT_COLOR, 0);
        lv_obj_set_style_border_width(source_btn, 0, 0);
        lv_obj_set_style_pad_all(source_btn, 0, 0);
        disable_button_shadow(source_btn);
        lv_obj_add_event_cb(source_btn, contral_page_bt_imgbtn_click_cb, LV_EVENT_CLICKED, device);

        lv_obj_t *source_img = lv_image_create(source_btn);
        lv_obj_center(source_img);

        lv_obj_t *password_label = lv_label_create(info_row);
        lv_obj_align(password_label, LV_ALIGN_RIGHT_MID, 0, 0);
        // lv_obj_set_style_translate_y(password_label, 10, 0);
        lv_obj_set_style_text_font(password_label, &my_equalwidth_font64, 0);
        lv_obj_set_style_text_color(password_label, lv_color_white(), 0);

        device->bt_box->volume_slider = volume_slider;
        device->bt_box->source_btn = source_btn;
        device->bt_box->source_img = source_img;
        device->bt_box->password_label = password_label;
        update_bt_box_status(device);

        mark_grid_occupied(GRID_TYPE_2X2, device->angle, row, col, grid_occupied);
        lv_obj_set_grid_cell(bt_box, LV_GRID_ALIGN_CENTER, col, 2, LV_GRID_ALIGN_CENTER, row, 2);
      }
      else if (device->device_type == DEVICE_TYPE_THERMOSTAT)
      {
        if (!can_place_widget(GRID_TYPE_3X2, device->angle, row, col, grid_occupied))
        {
          printf("can not found local");
          goto next_device;
        }

        device->thermostat->power = THERMOSTAT_POWER_OFF;
        device->thermostat->mode = THERMOSTAT_MODE_WIND;
        device->thermostat->fan = THERMOSTAT_FAN_AUTO;
        device->thermostat->temp = 26.0f;
        device->thermostat->temp_setting = 26.0f;
        device->thermostat->rh = 50.0f;
        device->thermostat->cool_min_setting = 5.0f;
        device->thermostat->cool_max_setting = 35.0f;
        device->thermostat->heat_min_setting = 5.0f;
        device->thermostat->heat_max_setting = 35.0f;
        device->thermostat->use_celsius = true;
        device->thermostat->fan_support = 3;
        device->thermostat->mode_support = 0;

        lv_obj_t *thermostat = lv_obj_create(show_page_obj);
        lv_obj_set_size(thermostat, (GRID_SIZE * 3 + GRID_SPACING * 2), (GRID_SIZE * 2 + GRID_SPACING * 1));
        lv_obj_center(thermostat);
        lv_obj_set_style_bg_color(thermostat, AREA_BG_COLOR, 0);
        lv_obj_set_style_radius(thermostat, 35, 0);
        lv_obj_set_style_border_width(thermostat, 0, 0);
        lv_obj_remove_flag(thermostat, LV_OBJ_FLAG_SCROLLABLE);

        device->thermostat->temp_arc = lv_arc_create(thermostat);
        /* Increase hit area without changing visual size */
        lv_obj_set_ext_click_area(device->thermostat->temp_arc, 24);
        lv_arc_set_bg_angles(device->thermostat->temp_arc, 170, 10);
        lv_obj_remove_style(device->thermostat->temp_arc, NULL, LV_PART_KNOB);
        lv_obj_set_size(device->thermostat->temp_arc, 270, 270);
        lv_obj_align(device->thermostat->temp_arc, LV_ALIGN_LEFT_MID, 12, 0);

        static lv_style_t style_bg;
        lv_style_init(&style_bg);
        lv_style_set_arc_width(&style_bg, 30);
        lv_style_set_arc_color(&style_bg, CLOSE_STATE_DEFAULT_COLOR);
        lv_obj_add_style(device->thermostat->temp_arc, &style_bg, LV_PART_MAIN);

        static lv_style_t style_indicator;
        lv_style_init(&style_indicator);
        lv_style_set_arc_width(&style_indicator, 30);
        lv_obj_add_style(device->thermostat->temp_arc, &style_indicator, LV_PART_INDICATOR);
        lv_obj_set_style_arc_image_src(device->thermostat->temp_arc, arc_pic, LV_PART_INDICATOR);

        device->thermostat->temp_set_label = lv_label_create(device->thermostat->temp_arc);
        lv_obj_set_style_text_font(device->thermostat->temp_set_label, &equalwidth_128, 0);
        lv_obj_set_style_text_color(device->thermostat->temp_set_label, lv_color_white(), 0);
        lv_obj_center(device->thermostat->temp_set_label);
        lv_obj_set_style_text_align(device->thermostat->temp_set_label, LV_TEXT_ALIGN_CENTER, 0);
        lv_obj_add_event_cb(device->thermostat->temp_arc, contral_page_arc_value_changed_cb, LV_EVENT_VALUE_CHANGED, device);
        lv_obj_add_event_cb(device->thermostat->temp_arc, contral_page_arc_value_changed_cb, LV_EVENT_RELEASED, device);

        /* 右侧按键容器：竖排 + 等间距 */
        lv_obj_t *right_btn_col = lv_obj_create(thermostat);
        lv_obj_set_size(right_btn_col, 90, 300);
        lv_obj_align(right_btn_col, LV_ALIGN_RIGHT_MID, 0, 0);
        lv_obj_set_style_bg_opa(right_btn_col, LV_OPA_TRANSP, 0);
        lv_obj_set_style_border_width(right_btn_col, 0, 0);
        lv_obj_set_style_pad_all(right_btn_col, 0, 0);
        lv_obj_remove_flag(right_btn_col, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_set_layout(right_btn_col, LV_LAYOUT_FLEX);
        lv_obj_set_flex_flow(right_btn_col, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_flex_align(right_btn_col, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

        device->thermostat->power_imgbtn = lv_button_create(right_btn_col);
        lv_obj_set_size(device->thermostat->power_imgbtn, 80, 80);
        lv_obj_set_style_radius(device->thermostat->power_imgbtn, LV_RADIUS_CIRCLE, 0);
        lv_obj_set_style_bg_opa(device->thermostat->power_imgbtn, LV_OPA_COVER, 0);
        lv_obj_set_style_bg_color(device->thermostat->power_imgbtn, CLOSE_STATE_DEFAULT_COLOR, 0);
        lv_obj_set_style_border_width(device->thermostat->power_imgbtn, 0, 0);
        lv_obj_set_style_pad_all(device->thermostat->power_imgbtn, 0, 0);
        disable_button_shadow(device->thermostat->power_imgbtn);
        device->thermostat->power_img = lv_image_create(device->thermostat->power_imgbtn);
        lv_obj_center(device->thermostat->power_img);
        lv_obj_set_style_img_recolor(device->thermostat->power_img, OPEN_STATE_DEFAULT_COLOR, 0);
        lv_obj_set_style_img_recolor_opa(device->thermostat->power_img, LV_OPA_COVER, 0);

        device->thermostat->mode_imgbtn = lv_button_create(right_btn_col);
        lv_obj_set_size(device->thermostat->mode_imgbtn, 80, 80);
        lv_obj_set_style_radius(device->thermostat->mode_imgbtn, LV_RADIUS_CIRCLE, 0);
        lv_obj_set_style_bg_opa(device->thermostat->mode_imgbtn, LV_OPA_COVER, 0);
        lv_obj_set_style_bg_color(device->thermostat->mode_imgbtn, CLOSE_STATE_DEFAULT_COLOR, 0);
        lv_obj_set_style_border_width(device->thermostat->mode_imgbtn, 0, 0);
        lv_obj_set_style_pad_all(device->thermostat->mode_imgbtn, 0, 0);
        disable_button_shadow(device->thermostat->mode_imgbtn);
        device->thermostat->mode_img = lv_image_create(device->thermostat->mode_imgbtn);
        lv_obj_center(device->thermostat->mode_img);
        // lv_obj_set_style_img_recolor(device->thermostat->mode_img, OPEN_STATE_DEFAULT_COLOR, 0);
        // lv_obj_set_style_img_recolor_opa(device->thermostat->mode_img, LV_OPA_COVER, 0);

        device->thermostat->fan_imgbtn = lv_button_create(right_btn_col);
        lv_obj_set_size(device->thermostat->fan_imgbtn, 80, 80);
        lv_obj_set_style_radius(device->thermostat->fan_imgbtn, LV_RADIUS_CIRCLE, 0);
        lv_obj_set_style_bg_opa(device->thermostat->fan_imgbtn, LV_OPA_COVER, 0);
        lv_obj_set_style_bg_color(device->thermostat->fan_imgbtn, CLOSE_STATE_DEFAULT_COLOR, 0);
        lv_obj_set_style_border_width(device->thermostat->fan_imgbtn, 0, 0);
        lv_obj_set_style_pad_all(device->thermostat->fan_imgbtn, 0, 0);
        disable_button_shadow(device->thermostat->fan_imgbtn);
        device->thermostat->fan_img = lv_image_create(device->thermostat->fan_imgbtn);
        lv_obj_center(device->thermostat->fan_img);
        // lv_obj_set_style_img_recolor(device->thermostat->fan_img, OPEN_STATE_DEFAULT_COLOR, 0);
        // lv_obj_set_style_img_recolor_opa(device->thermostat->fan_img, LV_OPA_COVER, 0);

        lv_obj_add_event_cb(device->thermostat->power_imgbtn, contral_page_thermostat_imgbtn_click_cb, LV_EVENT_CLICKED, device);
        lv_obj_add_event_cb(device->thermostat->mode_imgbtn, contral_page_thermostat_imgbtn_click_cb, LV_EVENT_CLICKED, device);
        lv_obj_add_event_cb(device->thermostat->fan_imgbtn, contral_page_thermostat_imgbtn_click_cb, LV_EVENT_CLICKED, device);

        /* 室内温湿度*/
        lv_obj_t *indoor_row = lv_obj_create(thermostat);
        lv_obj_set_size(indoor_row, 290, LV_SIZE_CONTENT);
        lv_obj_align(indoor_row, LV_ALIGN_BOTTOM_LEFT, 5, 0);
        lv_obj_set_style_bg_opa(indoor_row, LV_OPA_TRANSP, 0);
        lv_obj_set_style_border_width(indoor_row, 0, 0);
        lv_obj_set_style_pad_all(indoor_row, 0, 0);
        lv_obj_remove_flag(indoor_row, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_set_layout(indoor_row, LV_LAYOUT_FLEX);
        lv_obj_set_flex_flow(indoor_row, LV_FLEX_FLOW_ROW);
        lv_obj_set_flex_align(indoor_row, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_style_pad_column(indoor_row, 0, 0);

        lv_obj_t *temp_group = lv_obj_create(indoor_row);
        lv_obj_set_size(temp_group, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
        lv_obj_set_style_bg_opa(temp_group, LV_OPA_TRANSP, 0);
        lv_obj_set_style_border_width(temp_group, 0, 0);
        lv_obj_set_style_pad_all(temp_group, 0, 0);
        lv_obj_remove_flag(temp_group, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_set_layout(temp_group, LV_LAYOUT_FLEX);
        lv_obj_set_flex_flow(temp_group, LV_FLEX_FLOW_ROW);
        lv_obj_set_flex_align(temp_group, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_style_pad_column(temp_group, 0, 0);

        lv_obj_t *temp_icon = lv_image_create(temp_group);
        lv_image_set_src(temp_icon, temperature_pic);
        /* Compensate transparent edge in PNG so icon/text look closer */
        lv_obj_set_style_pad_right(temp_icon, -30, 0);
        device->thermostat->temp_label = lv_label_create(temp_group);
        lv_obj_set_style_text_font(device->thermostat->temp_label, &equalwidth_48, 0);
        lv_obj_set_style_text_color(device->thermostat->temp_label, lv_color_white(), 0);
        lv_obj_set_style_pad_left(device->thermostat->temp_label, 0, 0);

        lv_obj_t *humi_group = lv_obj_create(indoor_row);
        lv_obj_set_size(humi_group, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
        lv_obj_set_style_bg_opa(humi_group, LV_OPA_TRANSP, 0);
        lv_obj_set_style_border_width(humi_group, 0, 0);
        lv_obj_set_style_pad_all(humi_group, 0, 0);
        lv_obj_remove_flag(humi_group, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_set_layout(humi_group, LV_LAYOUT_FLEX);
        lv_obj_set_flex_flow(humi_group, LV_FLEX_FLOW_ROW);
        lv_obj_set_flex_align(humi_group, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_style_pad_column(humi_group, 0, 0);

        lv_obj_t *humi_icon = lv_image_create(humi_group);
        lv_image_set_src(humi_icon, humidity_pic);
        lv_obj_set_style_pad_right(humi_icon, -20, 0);
        device->thermostat->rh_label = lv_label_create(humi_group);
        lv_obj_set_style_text_font(device->thermostat->rh_label, &my_equalwidth_font48, 0);
        lv_obj_set_style_text_color(device->thermostat->rh_label, lv_color_white(), 0);
        lv_obj_set_style_pad_left(device->thermostat->rh_label, 0, 0);
        lv_obj_set_style_translate_y(humi_icon, 4, 0);
        lv_obj_set_style_translate_y(device->thermostat->rh_label, 8, 0);

        update_thermostat_imgbtn_status(device);

        // lv_obj_set_size(thermostat, 470, 310);
        //  lv_obj_align(thermostat, LV_ALIGN_LEFT_MID, 3, 0);
        //  lv_obj_align(thermostat, LV_ALIGN_RIGHT_MID, -3, 0);
        mark_grid_occupied(GRID_TYPE_3X2, device->angle, row, col, grid_occupied);
        lv_obj_set_grid_cell(thermostat, LV_GRID_ALIGN_CENTER, col, 3, LV_GRID_ALIGN_CENTER, row, 2);
      }
    }
  next_device:
    device = device->next;
  }

  newNode->contral_page_obj = contral_page_obj; // 赋值页面部件

  lv_obj_t *circle_obj = lv_obj_create(tip_bar_obj); // 新增圆形部件表示新增页面
  lv_obj_set_size(circle_obj, 8, 8);
  lv_obj_set_style_radius(circle_obj, LV_RADIUS_CIRCLE, 0);
  lv_obj_set_style_bg_color(circle_obj, lv_color_white(), 0);
  lv_obj_set_style_opa(circle_obj, LV_OPA_100, 0);
  lv_obj_set_style_border_width(circle_obj, 0, 0);

  lv_tileview_set_tile_by_index(contral_page_tileview, 0, 0, LV_ANIM_OFF);       // 手动设置首页面为当前活动页面
  lv_obj_send_event(contral_page_tileview, LV_EVENT_VALUE_CHANGED, tip_bar_obj); // 手动触发事件更新页面显示
}

/******************************************************控制页面绘制函数*****************************************************/
static void create_contral_page(void)
{
  device_node_t *device = add_deivce_node();
  device->slot = 0x94;
  device->gang = 0x11;
  device->device_type = DEVICE_TYPE_THERMOSTAT;
  device->page_index = 1;
  device->show_index = 1;
  device->angle = 0;
  device->thermostat = (thermostat_t *)add_thermostat_node();

  device = add_deivce_node();
  device->slot = 0x89;
  device->gang = 0x01;
  device->device_type = DEVICE_TYPE_RCU_DIMMING;
  device->page_index = 1;
  device->show_index = 8;
  device->angle = 3;
  device->dimmer_slider = (dimmer_slider_t *)add_dimmer_slider_node(power_pic);

  device = add_deivce_node();
  device->slot = 0x89;
  device->gang = 0x02;
  device->device_type = DEVICE_TYPE_RCU_DIMMING;
  device->page_index = 1;
  device->show_index = 9;
  device->angle = 0;
  device->dimmer_slider = (dimmer_slider_t *)add_dimmer_slider_node(power_pic);

  device = add_deivce_node();
  device->slot = 0x80;
  device->gang = 0x01;
  device->device_type = DEVICE_TYPE_RCU_ONOFF;
  device->page_index = 1;
  device->show_index = 11;
  device->angle = 0;
  device->img_switch = (img_switch_t *)add_img_switch_node(power_pic);

  device = add_deivce_node();
  device->slot = 0x80;
  device->gang = 0x02;
  device->device_type = DEVICE_TYPE_RCU_ONOFF;
  device->page_index = 1;
  device->show_index = 12;
  device->angle = 0;
  device->img_switch = (img_switch_t *)add_img_switch_node(power_pic);

  device = add_deivce_node();
  device->slot = 0x96;
  device->gang = 0x01;
  device->device_type = DEVICE_TYPE_BT_BOX;
  device->page_index = 2;
  device->show_index = 1;
  device->angle = 0;
  device->bt_box = (bt_box_t *)add_bt_box_node();

  device = add_deivce_node();
  device->slot = 0x89;
  device->gang = 0x02;
  device->device_type = DEVICE_TYPE_RCU_DIMMING;
  device->page_index = 2;
  device->show_index = 3;
  device->angle = 1;
  device->dimmer_slider = (dimmer_slider_t *)add_dimmer_slider_node(power_pic);

  device = add_deivce_node();
  device->slot = 0x89;
  device->gang = 0x02;
  device->device_type = DEVICE_TYPE_RCU_DIMMING;
  device->page_index = 2;
  device->show_index = 8;
  device->angle = 3;
  device->dimmer_slider = (dimmer_slider_t *)add_dimmer_slider_node(power_pic);

  device = add_deivce_node();
  device->slot = 0x81;
  device->gang = 0x01;
  device->device_type = DEVICE_TYPE_CLEAN_DND;
  device->page_index = 2;
  device->show_index = 9;
  device->angle = 0;
  device->clean_dnd = (clean_dnd_t *)add_clean_dnd_node();

  device = add_deivce_node();
  device->slot = 0x81;
  device->gang = 0x01;
  device->device_type = DEVICE_TYPE_CLEAN_DND;
  device->page_index = 2;
  device->show_index = 12;
  device->angle = 2;
  device->clean_dnd = (clean_dnd_t *)add_clean_dnd_node();

  create_one_contral_page("Living Room", 1);
  create_one_contral_page("Media Room", 2);
  /*
  if (contral_page_tileview)
  {
    lv_obj_add_flag(contral_page_tileview, LV_OBJ_FLAG_HIDDEN);
  }
  if (tip_bar_obj)
  {
    lv_obj_add_flag(tip_bar_obj, LV_OBJ_FLAG_HIDDEN);
  }
  */
}

#define PHONE_NUMBER_MAX_LEN 31
#define PHONE_DIAL_PANEL_WIDTH 560
#define PHONE_DIAL_IDLE_BACK_MS 5000
static char phone_number_buf[PHONE_NUMBER_MAX_LEN + 1] = {0};
static size_t phone_number_len = 0;
static lv_obj_t *phone_number_label = NULL;
static lv_obj_t *phone_number_box = NULL;
static lv_obj_t *phone_home_page = NULL;
static lv_obj_t *phone_dial_page = NULL;
static lv_obj_t *phone_call_page = NULL;
static lv_obj_t *phone_call_number_label = NULL;
static lv_obj_t *phone_answer_page = NULL;
static lv_obj_t *phone_answer_number_label = NULL;
static lv_obj_t *phone_connected_page = NULL;
static lv_obj_t *phone_connected_number_label = NULL;
static lv_obj_t *phone_connected_duration_label = NULL;
static lv_obj_t *phone_connected_volume_slider = NULL;
static lv_obj_t *phone_connected_volume_value_label = NULL;
static lv_obj_t *phone_connected_mic_img = NULL;
static lv_obj_t *phone_connected_speaker_img = NULL;
static lv_obj_t *phone_connected_dial_panel = NULL;
static lv_obj_t *phone_connected_dial_text_box = NULL;
static lv_obj_t *phone_connected_dial_label = NULL;
static lv_timer_t *phone_dial_idle_timer = NULL;
static lv_timer_t *phone_connect_timer = NULL;
static lv_timer_t *phone_connected_duration_timer = NULL;
static uint32_t phone_connected_elapsed_sec = 0;
static bool phone_connected_mic_on = true;
static bool phone_connected_speaker_on = true;
static char phone_connected_dial_buf[PHONE_NUMBER_MAX_LEN + 1] = {0};
static size_t phone_connected_dial_len = 0;
static char phone_active_number[PHONE_NUMBER_MAX_LEN + 1] = {0};

static void phone_create_home_page(void);
static void phone_create_dial_page(void);
static void phone_create_call_page(const char *number);
static void phone_create_answer_page(const char *number);
static void phone_create_connected_page(const char *number);
static void phone_update_number_label(void);
static void phone_answer_btn_event_cb(lv_event_t *e);

static bool phone_set_number(const char *text)
{
  if (text == NULL)
  {
    return false;
  }

  size_t text_len = strlen(text);
  if (text_len > PHONE_NUMBER_MAX_LEN)
  {
    text_len = PHONE_NUMBER_MAX_LEN;
  }

  memcpy(phone_number_buf, text, text_len);
  phone_number_buf[text_len] = '\0';
  phone_number_len = text_len;
  return true;
}

static bool phone_append_char(char ch)
{
  if (phone_number_len >= PHONE_NUMBER_MAX_LEN)
  {
    return false;
  }

  phone_number_buf[phone_number_len] = ch;
  phone_number_len++;
  phone_number_buf[phone_number_len] = '\0';
  return true;
}

static void phone_clear_number(void)
{
  phone_number_buf[0] = '\0';
  phone_number_len = 0;
}

static void phone_backspace_one(void)
{
  if (phone_number_len == 0)
  {
    return;
  }

  phone_number_len--;
  phone_number_buf[phone_number_len] = '\0';
}

static void phone_set_active_number(const char *number)
{
  if (number == NULL || number[0] == '\0')
  {
    phone_active_number[0] = '\0';
    return;
  }

  lv_snprintf(phone_active_number, sizeof(phone_active_number), "%.*s", PHONE_NUMBER_MAX_LEN, number);
}

static const char *phone_get_active_number(void)
{
  return (phone_active_number[0] == '\0') ? "Unknown" : phone_active_number;
}

static void phone_set_number_label(lv_obj_t *label, const char *number)
{
  if (label == NULL)
  {
    return;
  }

  if (number != NULL && number[0] != '\0')
  {
    lv_label_set_text(label, number);
    lv_obj_set_style_text_color(label, lv_color_white(), 0);
  }
  else
  {
    lv_label_set_text(label, "Unknown");
    lv_obj_set_style_text_color(label, lv_color_hex(0x777777), 0);
  }
}

static void phone_update_connected_duration_label(void)
{
  if (phone_connected_duration_label == NULL)
  {
    return;
  }

  uint32_t h = phone_connected_elapsed_sec / 3600U;
  uint32_t m = (phone_connected_elapsed_sec % 3600U) / 60U;
  uint32_t s = phone_connected_elapsed_sec % 60U;

  char buf[16] = {0};
  if (h > 0)
  {
    snprintf(buf, sizeof(buf), "%02u:%02u:%02u", (unsigned int)h, (unsigned int)m, (unsigned int)s);
  }
  else
  {
    snprintf(buf, sizeof(buf), "%02u:%02u", (unsigned int)m, (unsigned int)s);
  }
  lv_label_set_text(phone_connected_duration_label, buf);
}

static void phone_update_connected_volume_label(void)
{
  if (phone_connected_volume_slider == NULL || phone_connected_volume_value_label == NULL)
  {
    return;
  }

  char buf[8] = {0};
  lv_snprintf(buf, sizeof(buf), "%d", (int)lv_slider_get_value(phone_connected_volume_slider));
  lv_label_set_text(phone_connected_volume_value_label, buf);
  lv_obj_align_to(phone_connected_volume_value_label, phone_connected_volume_slider, LV_ALIGN_OUT_TOP_MID, 0, -5);
}

static void phone_connected_volume_slider_event_cb(lv_event_t *e)
{
  (void)e;
  phone_update_connected_volume_label();
}

static bool phone_connected_dial_append_char(char ch)
{
  if (phone_connected_dial_len >= PHONE_NUMBER_MAX_LEN)
  {
    return false;
  }

  phone_connected_dial_buf[phone_connected_dial_len] = ch;
  phone_connected_dial_len++;
  phone_connected_dial_buf[phone_connected_dial_len] = '\0';
  return true;
}

static void phone_connected_dial_update_label(void)
{
  if (phone_connected_dial_label == NULL || phone_connected_dial_text_box == NULL)
  {
    return;
  }

  if (phone_connected_dial_len == 0 || phone_connected_dial_buf == NULL)
  {
    lv_label_set_text(phone_connected_dial_label, "");
    lv_obj_set_style_text_color(phone_connected_dial_label, lv_color_hex(0x777777), 0);
  }
  else
  {
    lv_label_set_text(phone_connected_dial_label, phone_connected_dial_buf);
    lv_obj_set_style_text_color(phone_connected_dial_label, lv_color_white(), 0);
  }

  lv_obj_update_layout(phone_connected_dial_text_box);
  lv_coord_t box_w = lv_obj_get_width(phone_connected_dial_text_box);
  lv_coord_t box_h = lv_obj_get_height(phone_connected_dial_text_box);
  lv_coord_t text_w = lv_obj_get_width(phone_connected_dial_label);
  lv_coord_t text_h = lv_obj_get_height(phone_connected_dial_label);
  lv_obj_set_y(phone_connected_dial_label, (box_h - text_h) / 2 + 4);
  lv_obj_set_x(phone_connected_dial_label, 0);

  if (text_w <= box_w)
  {
    lv_obj_scroll_to_x(phone_connected_dial_text_box, 0, LV_ANIM_OFF);
  }
  else
  {
    lv_obj_scroll_to_x(phone_connected_dial_text_box, text_w - box_w, LV_ANIM_OFF);
  }
}

static void phone_connected_dial_clear(void)
{
  phone_connected_dial_buf[0] = '\0';
  phone_connected_dial_len = 0;
  phone_connected_dial_update_label();
}

static void phone_connected_dial_hide(void)
{
  if (phone_connected_dial_panel != NULL)
  {
    lv_obj_add_flag(phone_connected_dial_panel, LV_OBJ_FLAG_HIDDEN);
  }
}

static void phone_connected_dial_toggle(void)
{
  if (phone_connected_dial_panel == NULL)
  {
    return;
  }

  if (lv_obj_has_flag(phone_connected_dial_panel, LV_OBJ_FLAG_HIDDEN))
  {
    lv_obj_remove_flag(phone_connected_dial_panel, LV_OBJ_FLAG_HIDDEN);
  }
  else
  {
    lv_obj_add_flag(phone_connected_dial_panel, LV_OBJ_FLAG_HIDDEN);
  }
}

static void phone_connected_dial_key_btn_event_cb(lv_event_t *e)
{
  lv_event_code_t code = lv_event_get_code(e);
  const char *key = (const char *)lv_event_get_user_data(e);
  if (key == NULL || key[0] == '\0')
  {
    return;
  }

  if (strcmp(key, "BACKSPACE") == 0)
  {
    if (code == LV_EVENT_LONG_PRESSED)
    {
      phone_connected_dial_clear();
    }
    else if (phone_connected_dial_len > 0)
    {
      phone_connected_dial_len--;
      phone_connected_dial_buf[phone_connected_dial_len] = '\0';
      phone_connected_dial_update_label();
    }
    return;
  }

  if (phone_connected_dial_len >= PHONE_NUMBER_MAX_LEN)
  {
    printf("Connected dial number limit reached: max %d bytes\n", PHONE_NUMBER_MAX_LEN);
    return;
  }

  if (!phone_connected_dial_append_char(key[0]))
  {
    printf("Connected dial number limit reached: max %d bytes\n", PHONE_NUMBER_MAX_LEN);
    return;
  }

  phone_connected_dial_update_label();
}

static void phone_stop_connect_timer(void)
{
  if (phone_connect_timer != NULL)
  {
    lv_timer_pause(phone_connect_timer);
  }
}

static void phone_stop_connected_duration_timer(void)
{
  if (phone_connected_duration_timer != NULL)
  {
    lv_timer_pause(phone_connected_duration_timer);
  }
}

static void phone_pause_dial_idle_timer(void)
{
  if (phone_dial_idle_timer != NULL)
  {
    lv_timer_pause(phone_dial_idle_timer);
  }
}

static void phone_resume_dial_idle_timer(void)
{
  if (phone_dial_idle_timer != NULL)
  {
    lv_timer_reset(phone_dial_idle_timer);
    lv_timer_resume(phone_dial_idle_timer);
  }
}

static void phone_hide_all_pages(void)
{
  if (phone_home_page != NULL)
  {
    lv_obj_add_flag(phone_home_page, LV_OBJ_FLAG_HIDDEN);
  }
  if (phone_dial_page != NULL)
  {
    lv_obj_add_flag(phone_dial_page, LV_OBJ_FLAG_HIDDEN);
  }
  if (phone_call_page != NULL)
  {
    lv_obj_add_flag(phone_call_page, LV_OBJ_FLAG_HIDDEN);
  }
  if (phone_answer_page != NULL)
  {
    lv_obj_add_flag(phone_answer_page, LV_OBJ_FLAG_HIDDEN);
  }
  if (phone_connected_page != NULL)
  {
    lv_obj_add_flag(phone_connected_page, LV_OBJ_FLAG_HIDDEN);
  }
}

static void phone_connected_duration_timer_cb(lv_timer_t *timer)
{
  (void)timer;
  phone_connected_elapsed_sec++;
  phone_update_connected_duration_label();
}

static void phone_show_connected_page(const char *number)
{
  if (number != NULL)
  {
    phone_set_active_number(number);
  }

  phone_create_connected_page(phone_get_active_number());
  if (phone_connected_page == NULL)
  {
    return;
  }

  phone_stop_connect_timer();
  phone_pause_dial_idle_timer();

  phone_connected_elapsed_sec = 0;
  phone_update_connected_duration_label();
  if (phone_connected_duration_timer != NULL)
  {
    lv_timer_set_period(phone_connected_duration_timer, 1000);
    lv_timer_set_repeat_count(phone_connected_duration_timer, -1);
    lv_timer_reset(phone_connected_duration_timer);
    lv_timer_resume(phone_connected_duration_timer);
  }

  phone_hide_all_pages();
  lv_obj_remove_flag(phone_connected_page, LV_OBJ_FLAG_HIDDEN);
  phone_connected_dial_clear();
  phone_connected_dial_hide();
}

static void phone_connect_timer_cb(lv_timer_t *timer)
{
  (void)timer;

  if (phone_call_page == NULL)
  {
    return;
  }

  if (lv_obj_has_flag(phone_call_page, LV_OBJ_FLAG_HIDDEN))
  {
    return;
  }

  phone_show_connected_page(NULL);
}

static void phone_show_home_page(void)
{
  phone_create_home_page();
  if (phone_home_page == NULL)
  {
    return;
  }

  phone_stop_connect_timer();
  phone_stop_connected_duration_timer();
  phone_pause_dial_idle_timer();
  phone_connected_dial_hide();
  phone_clear_number();
  phone_update_number_label();
  phone_hide_all_pages();
  lv_obj_remove_flag(phone_home_page, LV_OBJ_FLAG_HIDDEN);
}

static void phone_show_dial_page(void)
{
  phone_create_dial_page();
  if (phone_dial_page == NULL)
  {
    return;
  }

  phone_stop_connect_timer();
  phone_stop_connected_duration_timer();
  phone_resume_dial_idle_timer();
  phone_connected_dial_hide();
  phone_hide_all_pages();
  lv_obj_remove_flag(phone_dial_page, LV_OBJ_FLAG_HIDDEN);

  lv_display_trigger_activity(NULL);
}

static void phone_show_call_page(const char *number)
{
  phone_set_active_number(number);
  phone_create_call_page(phone_get_active_number());
  if (phone_call_page == NULL)
  {
    return;
  }

  phone_stop_connected_duration_timer();
  phone_pause_dial_idle_timer();
  phone_connected_dial_hide();
  phone_hide_all_pages();
  lv_obj_remove_flag(phone_call_page, LV_OBJ_FLAG_HIDDEN);

  if (phone_connect_timer != NULL)
  {
    lv_timer_set_period(phone_connect_timer, 1200);
    lv_timer_set_repeat_count(phone_connect_timer, 1);
    lv_timer_reset(phone_connect_timer);
    lv_timer_resume(phone_connect_timer);
  }
}

static void phone_show_answer_page(const char *number)
{
  phone_set_active_number(number);
  phone_create_answer_page(phone_get_active_number());
  if (phone_answer_page == NULL)
  {
    return;
  }

  phone_stop_connect_timer();
  phone_stop_connected_duration_timer();
  phone_pause_dial_idle_timer();
  phone_connected_dial_hide();
  phone_hide_all_pages();
  lv_obj_remove_flag(phone_answer_page, LV_OBJ_FLAG_HIDDEN);
}

static void phone_cancel_call_btn_event_cb(lv_event_t *e)
{
  (void)e;
  if (phone_active_number[0] != '\0')
  {
    printf("Call canceled: %s\n", phone_active_number);
  }

  phone_show_dial_page();
}

static void phone_answer_btn_event_cb(lv_event_t *e)
{
  const char *action = (const char *)lv_event_get_user_data(e);
  if (action == NULL)
  {
    return;
  }

  if (strcmp(action, "ANSWER") == 0)
  {
    printf("Incoming call answered\n");
    phone_show_connected_page(NULL);
  }
  else if (strcmp(action, "HANGUP") == 0)
  {
    if (phone_active_number[0] != '\0')
    {
      printf("Incoming call rejected: %s\n", phone_active_number);
    }
    phone_show_home_page();
  }
}

static void phone_connected_btn_event_cb(lv_event_t *e)
{
  const char *action = (const char *)lv_event_get_user_data(e);
  if (action == NULL)
  {
    return;
  }

  if (strcmp(action, "HANGUP") == 0)
  {
    phone_cancel_call_btn_event_cb(e);
  }
  else if (strcmp(action, "MIC") == 0)
  {
    phone_connected_mic_on = !phone_connected_mic_on;
    if (phone_connected_mic_img != NULL)
    {
      lv_image_set_src(phone_connected_mic_img, phone_connected_mic_on ? microphone_on_pic : microphone_off_pic);
    }
  }
  else if (strcmp(action, "DIAL") == 0)
  {
    phone_connected_dial_toggle();
  }
  else if (strcmp(action, "SPK") == 0)
  {
    phone_connected_speaker_on = !phone_connected_speaker_on;
    if (phone_connected_speaker_img != NULL)
    {
      lv_image_set_src(phone_connected_speaker_img, phone_connected_speaker_on ? speaker_on_pic : speaker_off_pic);
    }
  }
}

static void phone_home_call_btn_event_cb(lv_event_t *e)
{
  lv_event_code_t code = lv_event_get_code(e);

  if (code == LV_EVENT_LONG_PRESSED)
  {
    phone_show_answer_page("10086");
    return;
  }

  if (code == LV_EVENT_SHORT_CLICKED)
  {
    phone_show_dial_page();
  }
}

static void phone_dial_back_btn_event_cb(lv_event_t *e)
{
  (void)e;
  phone_show_home_page();
}

static void phone_dial_idle_timer_cb(lv_timer_t *timer)
{
  (void)timer;

  if (phone_dial_page == NULL || phone_home_page == NULL)
  {
    return;
  }

  if (lv_obj_has_flag(phone_dial_page, LV_OBJ_FLAG_HIDDEN))
  {
    return;
  }

  if (lv_display_get_inactive_time(NULL) >= PHONE_DIAL_IDLE_BACK_MS)
  {
    phone_show_home_page();
  }
}

static void phone_update_number_label(void)
{
  if (phone_number_label == NULL || phone_number_box == NULL)
  {
    return;
  }

  if (phone_number_len == 0)
  {
    lv_label_set_text(phone_number_label, "Enter Number");
    lv_obj_set_style_text_color(phone_number_label, lv_color_hex(0x666666), 0);
  }
  else
  {
    lv_label_set_text(phone_number_label, phone_number_buf);
    lv_obj_set_style_text_color(phone_number_label, lv_color_white(), 0);
  }

  lv_obj_update_layout(phone_number_box);

  lv_coord_t box_w = lv_obj_get_width(phone_number_box);
  lv_coord_t box_h = lv_obj_get_height(phone_number_box);
  lv_coord_t text_w = lv_obj_get_width(phone_number_label);
  lv_coord_t text_h = lv_obj_get_height(phone_number_label);
  lv_obj_set_y(phone_number_label, (box_h - text_h) / 2 + 5);

  if (text_w <= box_w)
  {
    lv_obj_set_x(phone_number_label, (box_w - text_w) / 2);
    lv_obj_scroll_to_x(phone_number_box, 0, LV_ANIM_OFF);
  }
  else
  {
    lv_obj_set_x(phone_number_label, 0);
    lv_obj_scroll_to_x(phone_number_box, text_w - box_w, LV_ANIM_OFF);
  }
}

static void phone_keypad_btn_event_cb(lv_event_t *e)
{
  lv_event_code_t code = lv_event_get_code(e);
  const char *key = (const char *)lv_event_get_user_data(e);
  if (key == NULL)
  {
    return;
  }

  if (strcmp(key, "DEL") == 0 || strcmp(key, "BACKSPACE") == 0)
  {
    if (strcmp(key, "BACKSPACE") == 0 && code == LV_EVENT_LONG_PRESSED)
    {
      phone_clear_number();
    }
    else
    {
      phone_backspace_one();
    }
  }
  else if (strcmp(key, "CLR") == 0)
  {
    phone_clear_number();
  }
  else if (strcmp(key, "CALL") == 0 || strcmp(key, "call") == 0)
  {
    if (phone_number_len > 0)
    {
      printf("Dialing: %s\n", phone_number_buf);
      phone_show_call_page(phone_number_buf);
    }
  }
  else if (strcmp(key, "CALL_SERVICE") == 0)
  {
    phone_set_number("8888");
  }
  else
  {
    if (phone_number_len >= PHONE_NUMBER_MAX_LEN)
    {
      printf("Phone number limit reached: max %d bytes\n", PHONE_NUMBER_MAX_LEN);
      phone_update_number_label();
      return;
    }

    if (!phone_append_char(key[0]))
    {
      printf("Phone number limit reached: max %d bytes\n", PHONE_NUMBER_MAX_LEN);
    }
  }

  phone_update_number_label();
}

static void phone_create_dial_objects(void)
{
  if (phone_dial_page != NULL)
  {
    return;
  }

  phone_dial_page = lv_obj_create(lv_scr_act());
  lv_obj_set_size(phone_dial_page, MAIN_PAGE_WIDTH, (MAIN_PAGE_HEIGHT - LV_STATUS_BAR_HEIGHT));
  lv_obj_align(phone_dial_page, LV_ALIGN_BOTTOM_MID, 0, 0);
  lv_obj_set_style_bg_color(phone_dial_page, lv_color_black(), 0);
  lv_obj_set_style_border_width(phone_dial_page, 0, 0);
  lv_obj_set_style_pad_all(phone_dial_page, 0, 0);
  lv_obj_remove_flag(phone_dial_page, LV_OBJ_FLAG_SCROLLABLE);

  lv_obj_t *back_btn = lv_button_create(phone_dial_page);
  lv_obj_set_size(back_btn, 80, 80);
  lv_obj_align(back_btn, LV_ALIGN_TOP_LEFT, 16, 16);
  lv_obj_set_style_radius(back_btn, 35, 0);
  lv_obj_set_style_bg_opa(back_btn, LV_OPA_TRANSP, 0);
  lv_obj_set_style_border_width(back_btn, 0, 0);
  disable_button_shadow(back_btn);
  lv_obj_add_event_cb(back_btn, phone_dial_back_btn_event_cb, LV_EVENT_CLICKED, NULL);

  lv_obj_t *back_img = lv_image_create(back_btn);
  lv_image_set_src(back_img, back_pic);
  lv_obj_center(back_img);

  phone_number_box = lv_obj_create(phone_dial_page);
  lv_obj_set_size(phone_number_box, PHONE_DIAL_PANEL_WIDTH, 60);
  lv_obj_align(phone_number_box, LV_ALIGN_TOP_MID, 0, 76);
  lv_obj_set_style_bg_opa(phone_number_box, LV_OPA_TRANSP, 0);
  lv_obj_set_style_border_width(phone_number_box, 0, 0);
  lv_obj_set_style_pad_all(phone_number_box, 0, 0);
  lv_obj_set_scrollbar_mode(phone_number_box, LV_SCROLLBAR_MODE_OFF);
  lv_obj_set_scroll_dir(phone_number_box, LV_DIR_HOR);

  phone_number_label = lv_label_create(phone_number_box);
  lv_label_set_long_mode(phone_number_label, LV_LABEL_LONG_MODE_CLIP);
  lv_obj_set_height(phone_number_label, 56);
  lv_obj_set_style_text_align(phone_number_label, LV_TEXT_ALIGN_LEFT, 0);
  lv_obj_set_style_text_font(phone_number_label, &my_equalwidth_font48, 0);
  phone_clear_number();
  phone_update_number_label();

  lv_obj_t *dial_separator = lv_obj_create(phone_dial_page);
  lv_obj_set_size(dial_separator, PHONE_DIAL_PANEL_WIDTH, 2);
  lv_obj_align(dial_separator, LV_ALIGN_TOP_MID, 0, 144);
  lv_obj_set_style_radius(dial_separator, 0, 0);
  lv_obj_set_style_bg_color(dial_separator, lv_color_hex(0x3A3A3A), 0);
  lv_obj_set_style_border_width(dial_separator, 0, 0);
  lv_obj_remove_flag(dial_separator, LV_OBJ_FLAG_SCROLLABLE);

  lv_obj_t *keypad = lv_obj_create(phone_dial_page);
  lv_obj_set_size(keypad, PHONE_DIAL_PANEL_WIDTH, 432);
  lv_obj_align(keypad, LV_ALIGN_TOP_MID, 0, 160);
  lv_obj_set_style_bg_opa(keypad, LV_OPA_TRANSP, 0);
  lv_obj_set_style_border_width(keypad, 0, 0);
  lv_obj_set_style_pad_all(keypad, 0, 0);
  lv_obj_set_style_pad_row(keypad, 8, 0);
  lv_obj_set_style_pad_column(keypad, 10, 0);
  lv_obj_set_layout(keypad, LV_LAYOUT_FLEX);
  lv_obj_set_flex_flow(keypad, LV_FLEX_FLOW_ROW_WRAP);
  lv_obj_set_flex_align(keypad, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);
  lv_obj_remove_flag(keypad, LV_OBJ_FLAG_SCROLLABLE);

  static const char *dial_keys[] = {
      "1", "2", "3",
      "4", "5", "6",
      "7", "8", "9",
      "*", "0", "#"};

  for (uint8_t i = 0; i < sizeof(dial_keys) / sizeof(dial_keys[0]); i++)
  {
    lv_obj_t *btn = lv_button_create(keypad);
    lv_obj_set_size(btn, 180, 80);
    lv_obj_set_style_radius(btn, 35, 0);
    lv_obj_set_style_bg_color(btn, CLOSE_STATE_DEFAULT_COLOR, 0);
    lv_obj_set_style_border_width(btn, 0, 0);
    disable_button_shadow(btn);
    lv_obj_add_event_cb(btn, phone_keypad_btn_event_cb, LV_EVENT_CLICKED, (void *)dial_keys[i]);

    lv_obj_t *label = lv_label_create(btn);
    lv_label_set_text(label, dial_keys[i]);
    lv_obj_set_style_text_font(label, &my_equalwidth_font48, 0);
    lv_obj_set_style_text_color(label, lv_color_white(), 0);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 5);
  }

  lv_obj_t *service_btn = lv_button_create(keypad);
  lv_obj_set_size(service_btn, 180, 80);
  lv_obj_set_style_radius(service_btn, 35, 0);
  lv_obj_set_style_bg_color(service_btn, lv_color_hex(0xB00020), 0);
  lv_obj_set_style_border_width(service_btn, 0, 0);
  disable_button_shadow(service_btn);
  lv_obj_add_event_cb(service_btn, phone_keypad_btn_event_cb, LV_EVENT_CLICKED, (void *)"CALL_SERVICE");
  lv_obj_t *service_img = lv_image_create(service_btn);
  lv_image_set_src(service_img, room_service_pic);
  lv_obj_center(service_img);

  lv_obj_t *phone_call_btn = lv_button_create(keypad);
  lv_obj_set_size(phone_call_btn, 180, 80);
  lv_obj_set_style_radius(phone_call_btn, 35, 0);
  lv_obj_set_style_bg_color(phone_call_btn, lv_color_hex(0x1E8E3E), 0);
  lv_obj_set_style_border_width(phone_call_btn, 0, 0);
  disable_button_shadow(phone_call_btn);
  lv_obj_add_event_cb(phone_call_btn, phone_keypad_btn_event_cb, LV_EVENT_CLICKED, (void *)"call");
  lv_obj_t *phone_call_img = lv_image_create(phone_call_btn);
  lv_image_set_src(phone_call_img, call_pic);
  lv_obj_center(phone_call_img);

  lv_obj_t *backspace_btn = lv_button_create(keypad);
  lv_obj_set_size(backspace_btn, 180, 80);
  lv_obj_set_style_radius(backspace_btn, 35, 0);
  lv_obj_set_style_bg_color(backspace_btn, CLOSE_STATE_DEFAULT_COLOR, 0);
  lv_obj_set_style_border_width(backspace_btn, 0, 0);
  disable_button_shadow(backspace_btn);
  lv_obj_add_event_cb(backspace_btn, phone_keypad_btn_event_cb, LV_EVENT_CLICKED, (void *)"BACKSPACE");
  lv_obj_add_event_cb(backspace_btn, phone_keypad_btn_event_cb, LV_EVENT_LONG_PRESSED, (void *)"BACKSPACE");
  lv_obj_t *backspace_img = lv_image_create(backspace_btn);
  lv_image_set_src(backspace_img, backspace_pic);
  lv_obj_align(backspace_img, LV_ALIGN_CENTER, -5, 0);
}

static void phone_create_call_objects(void)
{
  if (phone_call_page != NULL)
  {
    return;
  }

  phone_call_page = lv_obj_create(lv_scr_act());
  lv_obj_set_size(phone_call_page, MAIN_PAGE_WIDTH, (MAIN_PAGE_HEIGHT - LV_STATUS_BAR_HEIGHT));
  lv_obj_align(phone_call_page, LV_ALIGN_BOTTOM_MID, 0, 0);
  lv_obj_set_style_bg_color(phone_call_page, lv_color_black(), 0);
  lv_obj_set_style_border_width(phone_call_page, 0, 0);
  lv_obj_set_style_pad_all(phone_call_page, 0, 0);
  lv_obj_remove_flag(phone_call_page, LV_OBJ_FLAG_SCROLLABLE);

  lv_obj_t *calling_number_box = lv_obj_create(phone_call_page);
  lv_obj_set_size(calling_number_box, PHONE_DIAL_PANEL_WIDTH, 80);
  lv_obj_align(calling_number_box, LV_ALIGN_TOP_MID, 0, 120);
  lv_obj_set_style_bg_opa(calling_number_box, LV_OPA_TRANSP, 0);
  lv_obj_set_style_border_width(calling_number_box, 0, 0);
  lv_obj_set_style_pad_all(calling_number_box, 0, 0);
  lv_obj_remove_flag(calling_number_box, LV_OBJ_FLAG_SCROLLABLE);

  phone_call_number_label = lv_label_create(calling_number_box);
  lv_label_set_long_mode(phone_call_number_label, LV_LABEL_LONG_MODE_SCROLL_CIRCULAR);
  lv_obj_set_width(phone_call_number_label, PHONE_DIAL_PANEL_WIDTH);
  lv_obj_set_style_text_font(phone_call_number_label, &my_equalwidth_font64, 0);
  lv_obj_set_style_text_align(phone_call_number_label, LV_TEXT_ALIGN_CENTER, 0);
  lv_obj_center(phone_call_number_label);
  phone_set_number_label(phone_call_number_label, NULL);

  lv_obj_t *cancel_btn = lv_button_create(phone_call_page);
  lv_obj_set_size(cancel_btn, 120, 120);
  lv_obj_align(cancel_btn, LV_ALIGN_BOTTOM_MID, 0, -64);
  lv_obj_set_style_radius(cancel_btn, 35, 0);
  lv_obj_set_style_bg_color(cancel_btn, lv_color_hex(0xB00020), 0);
  lv_obj_set_style_border_width(cancel_btn, 0, 0);
  disable_button_shadow(cancel_btn);
  lv_obj_add_event_cb(cancel_btn, phone_cancel_call_btn_event_cb, LV_EVENT_CLICKED, NULL);

  lv_obj_t *cancel_img = lv_image_create(cancel_btn);
  lv_image_set_src(cancel_img, hangup_pic);
  lv_obj_center(cancel_img);
}

static void phone_create_answer_objects(void)
{
  if (phone_answer_page != NULL)
  {
    return;
  }

  phone_answer_page = lv_obj_create(lv_scr_act());
  lv_obj_set_size(phone_answer_page, MAIN_PAGE_WIDTH, (MAIN_PAGE_HEIGHT - LV_STATUS_BAR_HEIGHT));
  lv_obj_align(phone_answer_page, LV_ALIGN_BOTTOM_MID, 0, 0);
  lv_obj_set_style_bg_color(phone_answer_page, lv_color_black(), 0);
  lv_obj_set_style_border_width(phone_answer_page, 0, 0);
  lv_obj_set_style_pad_all(phone_answer_page, 0, 0);
  lv_obj_remove_flag(phone_answer_page, LV_OBJ_FLAG_SCROLLABLE);

  lv_obj_t *incoming_number_box = lv_obj_create(phone_answer_page);
  lv_obj_set_size(incoming_number_box, PHONE_DIAL_PANEL_WIDTH, 80);
  lv_obj_align(incoming_number_box, LV_ALIGN_TOP_MID, 0, 120);
  lv_obj_set_style_bg_opa(incoming_number_box, LV_OPA_TRANSP, 0);
  lv_obj_set_style_border_width(incoming_number_box, 0, 0);
  lv_obj_set_style_pad_all(incoming_number_box, 0, 0);
  lv_obj_remove_flag(incoming_number_box, LV_OBJ_FLAG_SCROLLABLE);

  phone_answer_number_label = lv_label_create(incoming_number_box);
  lv_label_set_long_mode(phone_answer_number_label, LV_LABEL_LONG_MODE_SCROLL_CIRCULAR);
  lv_obj_set_width(phone_answer_number_label, PHONE_DIAL_PANEL_WIDTH);
  lv_obj_set_style_text_font(phone_answer_number_label, &my_equalwidth_font64, 0);
  lv_obj_set_style_text_align(phone_answer_number_label, LV_TEXT_ALIGN_CENTER, 0);
  lv_obj_center(phone_answer_number_label);
  phone_set_number_label(phone_answer_number_label, NULL);

  lv_obj_t *answer_btn = lv_button_create(phone_answer_page);
  lv_obj_set_size(answer_btn, 120, 120);
  lv_obj_align(answer_btn, LV_ALIGN_BOTTOM_MID, 120, -64);
  lv_obj_set_style_radius(answer_btn, 35, 0);
  lv_obj_set_style_bg_color(answer_btn, lv_color_hex(0x1E8E3E), 0);
  lv_obj_set_style_border_width(answer_btn, 0, 0);
  disable_button_shadow(answer_btn);
  lv_obj_add_event_cb(answer_btn, phone_answer_btn_event_cb, LV_EVENT_CLICKED, (void *)"ANSWER");

  lv_obj_t *answer_img = lv_image_create(answer_btn);
  lv_image_set_src(answer_img, call_pic);
  lv_obj_center(answer_img);

  lv_obj_t *hangup_btn = lv_button_create(phone_answer_page);
  lv_obj_set_size(hangup_btn, 120, 120);
  lv_obj_align(hangup_btn, LV_ALIGN_BOTTOM_MID, -120, -64);
  lv_obj_set_style_radius(hangup_btn, 35, 0);
  lv_obj_set_style_bg_color(hangup_btn, lv_color_hex(0xB00020), 0);
  lv_obj_set_style_border_width(hangup_btn, 0, 0);
  disable_button_shadow(hangup_btn);
  lv_obj_add_event_cb(hangup_btn, phone_answer_btn_event_cb, LV_EVENT_CLICKED, (void *)"HANGUP");

  lv_obj_t *hangup_img = lv_image_create(hangup_btn);
  lv_image_set_src(hangup_img, hangup_pic);
  lv_obj_center(hangup_img);
}

static void phone_create_connected_objects(void)
{
  if (phone_connected_page != NULL)
  {
    return;
  }

  phone_connected_page = lv_obj_create(lv_scr_act());
  lv_obj_set_size(phone_connected_page, MAIN_PAGE_WIDTH, (MAIN_PAGE_HEIGHT - LV_STATUS_BAR_HEIGHT));
  lv_obj_align(phone_connected_page, LV_ALIGN_BOTTOM_MID, 0, 0);
  lv_obj_set_style_bg_color(phone_connected_page, lv_color_black(), 0);
  lv_obj_set_style_border_width(phone_connected_page, 0, 0);
  lv_obj_set_style_pad_all(phone_connected_page, 0, 0);
  lv_obj_remove_flag(phone_connected_page, LV_OBJ_FLAG_SCROLLABLE);

  lv_obj_t *connected_number_box = lv_obj_create(phone_connected_page);
  lv_obj_set_size(connected_number_box, PHONE_DIAL_PANEL_WIDTH, 80);
  lv_obj_align(connected_number_box, LV_ALIGN_TOP_MID, 0, 96);
  lv_obj_set_style_bg_opa(connected_number_box, LV_OPA_TRANSP, 0);
  lv_obj_set_style_border_width(connected_number_box, 0, 0);
  lv_obj_set_style_pad_all(connected_number_box, 0, 0);
  lv_obj_remove_flag(connected_number_box, LV_OBJ_FLAG_SCROLLABLE);

  phone_connected_number_label = lv_label_create(connected_number_box);
  lv_label_set_long_mode(phone_connected_number_label, LV_LABEL_LONG_MODE_SCROLL_CIRCULAR);
  lv_obj_set_width(phone_connected_number_label, PHONE_DIAL_PANEL_WIDTH);
  lv_obj_set_style_text_font(phone_connected_number_label, &my_equalwidth_font64, 0);
  lv_obj_set_style_text_align(phone_connected_number_label, LV_TEXT_ALIGN_CENTER, 0);
  lv_obj_center(phone_connected_number_label);
  phone_set_number_label(phone_connected_number_label, NULL);

  phone_connected_duration_label = lv_label_create(phone_connected_page);
  lv_label_set_text(phone_connected_duration_label, "00:00");
  lv_obj_set_style_text_font(phone_connected_duration_label, &my_equalwidth_font48, 0);
  lv_obj_set_style_text_color(phone_connected_duration_label, lv_color_hex(0xAFAFAF), 0);
  lv_obj_align(phone_connected_duration_label, LV_ALIGN_TOP_MID, 0, 220);

  phone_connected_volume_slider = NULL;
  phone_connected_volume_value_label = NULL;
  phone_connected_volume_slider = lv_slider_create(phone_connected_page);
  lv_obj_set_size(phone_connected_volume_slider, 40, 300);
  lv_obj_align(phone_connected_volume_slider, LV_ALIGN_RIGHT_MID, -20, -100);
  lv_slider_set_range(phone_connected_volume_slider, 0, 100);
  lv_slider_set_value(phone_connected_volume_slider, 60, LV_ANIM_OFF);
  lv_obj_add_event_cb(phone_connected_volume_slider, phone_connected_volume_slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL);

  lv_obj_set_style_bg_color(phone_connected_volume_slider, CLOSE_STATE_DEFAULT_COLOR, LV_PART_MAIN);
  lv_obj_set_style_bg_opa(phone_connected_volume_slider, LV_OPA_COVER, LV_PART_MAIN);
  lv_obj_set_style_radius(phone_connected_volume_slider, 20, LV_PART_MAIN);
  lv_obj_set_style_bg_color(phone_connected_volume_slider, OPEN_STATE_DEFAULT_COLOR, LV_PART_INDICATOR);
  lv_obj_set_style_bg_opa(phone_connected_volume_slider, LV_OPA_COVER, LV_PART_INDICATOR);
  lv_obj_set_style_radius(phone_connected_volume_slider, 20, LV_PART_INDICATOR);

  lv_obj_set_style_bg_opa(phone_connected_volume_slider, LV_OPA_TRANSP, LV_PART_KNOB);
  lv_obj_set_style_border_opa(phone_connected_volume_slider, LV_OPA_TRANSP, LV_PART_KNOB);
  lv_obj_set_style_shadow_opa(phone_connected_volume_slider, LV_OPA_TRANSP, LV_PART_KNOB);
  lv_obj_set_style_outline_opa(phone_connected_volume_slider, LV_OPA_TRANSP, LV_PART_KNOB);

  lv_obj_t *connected_volume_icon = lv_label_create(phone_connected_volume_slider);
  lv_obj_set_style_text_font(connected_volume_icon, &lv_font_montserrat_24, 0);
  lv_label_set_text(connected_volume_icon, LV_SYMBOL_AUDIO);
  lv_obj_set_style_text_color(connected_volume_icon, lv_color_white(), 0);
  lv_obj_align(connected_volume_icon, LV_ALIGN_BOTTOM_MID, 0, -8);

  phone_connected_volume_value_label = lv_label_create(phone_connected_page);
  lv_obj_set_style_text_font(phone_connected_volume_value_label, &my_equalwidth_font24, 0);
  lv_obj_set_style_text_color(phone_connected_volume_value_label, lv_color_white(), 0);
  phone_update_connected_volume_label();

  lv_obj_t *connected_action_row = lv_obj_create(phone_connected_page);
  lv_obj_set_size(connected_action_row, 640, 140);
  lv_obj_align(connected_action_row, LV_ALIGN_BOTTOM_MID, 0, -30);
  lv_obj_set_style_bg_opa(connected_action_row, LV_OPA_TRANSP, 0);
  lv_obj_set_style_border_width(connected_action_row, 0, 0);
  lv_obj_set_style_pad_all(connected_action_row, 0, 0);
  lv_obj_set_style_pad_column(connected_action_row, 20, 0);
  lv_obj_remove_flag(connected_action_row, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_layout(connected_action_row, LV_LAYOUT_FLEX);
  lv_obj_set_flex_flow(connected_action_row, LV_FLEX_FLOW_ROW);
  lv_obj_set_flex_align(connected_action_row, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

  phone_connected_mic_on = true;
  phone_connected_speaker_on = true;
  phone_connected_mic_img = NULL;
  phone_connected_speaker_img = NULL;

  const char *connected_icons[4] = {microphone_on_pic, dial_pic, hangup_pic, speaker_on_pic};
  const char *connected_actions[4] = {"MIC", "DIAL", "HANGUP", "SPK"};
  for (uint8_t i = 0; i < 4; i++)
  {
    lv_obj_t *btn = lv_button_create(connected_action_row);
    lv_obj_set_size(btn, 120, 120);
    lv_obj_set_style_radius(btn, 35, 0);
    lv_obj_set_style_bg_color(btn, (i == 2) ? lv_color_hex(0xB00020) : CLOSE_STATE_DEFAULT_COLOR, 0);
    lv_obj_set_style_border_width(btn, 0, 0);
    disable_button_shadow(btn);
    lv_obj_add_event_cb(btn, phone_connected_btn_event_cb, LV_EVENT_CLICKED, (void *)connected_actions[i]);

    lv_obj_t *img = lv_image_create(btn);
    lv_image_set_src(img, connected_icons[i]);
    lv_obj_center(img);
    if (i == 0)
    {
      phone_connected_mic_img = img;
    }
    else if (i == 3)
    {
      phone_connected_speaker_img = img;
    }
  }

  phone_connected_dial_panel = lv_obj_create(phone_connected_page);
  lv_obj_set_size(phone_connected_dial_panel, PHONE_DIAL_PANEL_WIDTH, 450);
  lv_obj_align(phone_connected_dial_panel, LV_ALIGN_TOP_MID, 0, 20);
  lv_obj_set_style_bg_color(phone_connected_dial_panel, AREA_BG_COLOR, 0);
  lv_obj_set_style_radius(phone_connected_dial_panel, 35, 0);
  lv_obj_set_style_border_width(phone_connected_dial_panel, 0, 0);
  lv_obj_set_style_pad_all(phone_connected_dial_panel, 0, 0);
  lv_obj_remove_flag(phone_connected_dial_panel, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_add_flag(phone_connected_dial_panel, LV_OBJ_FLAG_HIDDEN);

  lv_obj_t *connected_dial_number_box = lv_obj_create(phone_connected_dial_panel);
  lv_obj_set_size(connected_dial_number_box, PHONE_DIAL_PANEL_WIDTH - 20, 50);
  lv_obj_align(connected_dial_number_box, LV_ALIGN_TOP_MID, 5, 15);
  lv_obj_set_style_bg_opa(connected_dial_number_box, LV_OPA_TRANSP, 0);
  lv_obj_set_style_border_width(connected_dial_number_box, 0, 0);
  lv_obj_set_style_border_side(connected_dial_number_box, LV_BORDER_SIDE_BOTTOM, 0);
  lv_obj_set_style_pad_all(connected_dial_number_box, 0, 0);
  lv_obj_remove_flag(connected_dial_number_box, LV_OBJ_FLAG_SCROLLABLE);

  phone_connected_dial_text_box = lv_obj_create(connected_dial_number_box);
  lv_obj_set_size(phone_connected_dial_text_box, PHONE_DIAL_PANEL_WIDTH - 120, 50);
  lv_obj_align(phone_connected_dial_text_box, LV_ALIGN_LEFT_MID, 0, 0);
  lv_obj_set_style_bg_opa(phone_connected_dial_text_box, LV_OPA_TRANSP, 0);
  lv_obj_set_style_border_width(phone_connected_dial_text_box, 0, 0);
  lv_obj_set_style_pad_all(phone_connected_dial_text_box, 0, 0);
  lv_obj_set_scrollbar_mode(phone_connected_dial_text_box, LV_SCROLLBAR_MODE_OFF);
  lv_obj_set_scroll_dir(phone_connected_dial_text_box, LV_DIR_HOR);

  phone_connected_dial_label = lv_label_create(phone_connected_dial_text_box);
  lv_label_set_long_mode(phone_connected_dial_label, LV_LABEL_LONG_MODE_CLIP);
  lv_obj_set_style_text_font(phone_connected_dial_label, &my_equalwidth_font48, 0);
  lv_obj_set_style_text_align(phone_connected_dial_label, LV_TEXT_ALIGN_LEFT, 0);
  phone_connected_dial_clear();

  lv_obj_t *connected_dial_backspace_btn = lv_button_create(connected_dial_number_box);
  lv_obj_set_size(connected_dial_backspace_btn, 72, 72);
  lv_obj_align(connected_dial_backspace_btn, LV_ALIGN_RIGHT_MID, -10, 0);
  lv_obj_set_style_radius(connected_dial_backspace_btn, 35, 0);
  lv_obj_set_style_bg_opa(connected_dial_backspace_btn, LV_OPA_TRANSP, 0);
  lv_obj_set_style_border_width(connected_dial_backspace_btn, 0, 0);
  disable_button_shadow(connected_dial_backspace_btn);
  lv_obj_add_event_cb(connected_dial_backspace_btn, phone_connected_dial_key_btn_event_cb, LV_EVENT_CLICKED, (void *)"BACKSPACE");
  lv_obj_add_event_cb(connected_dial_backspace_btn, phone_connected_dial_key_btn_event_cb, LV_EVENT_LONG_PRESSED, (void *)"BACKSPACE");
  lv_obj_t *connected_dial_backspace_img = lv_image_create(connected_dial_backspace_btn);
  lv_image_set_src(connected_dial_backspace_img, backspace_pic);
  lv_obj_align(connected_dial_backspace_img, LV_ALIGN_CENTER, 0, 0);

  lv_obj_t *connected_dial_keypad = lv_obj_create(phone_connected_dial_panel);
  lv_obj_set_size(connected_dial_keypad, PHONE_DIAL_PANEL_WIDTH - 20, 350);
  lv_obj_align(connected_dial_keypad, LV_ALIGN_BOTTOM_MID, 0, -8);
  lv_obj_set_style_bg_opa(connected_dial_keypad, LV_OPA_TRANSP, 0);
  lv_obj_set_style_border_width(connected_dial_keypad, 0, 0);
  lv_obj_set_style_pad_all(connected_dial_keypad, 0, 0);
  lv_obj_set_style_pad_row(connected_dial_keypad, 10, 0);
  lv_obj_set_style_pad_column(connected_dial_keypad, 10, 0);
  static lv_coord_t connected_dial_col_dsc[] = {
      173, 173, 173, LV_GRID_TEMPLATE_LAST};
  static lv_coord_t connected_dial_row_dsc[] = {
      80, 80, 80, 80, LV_GRID_TEMPLATE_LAST};
  lv_obj_set_grid_dsc_array(connected_dial_keypad, connected_dial_col_dsc, connected_dial_row_dsc);
  lv_obj_set_layout(connected_dial_keypad, LV_LAYOUT_GRID);
  lv_obj_remove_flag(connected_dial_keypad, LV_OBJ_FLAG_SCROLLABLE);

  static const char *connected_dial_keys[] = {
      "1", "2", "3",
      "4", "5", "6",
      "7", "8", "9",
      "*", "0", "#"};

  for (uint8_t i = 0; i < sizeof(connected_dial_keys) / sizeof(connected_dial_keys[0]); i++)
  {
    lv_obj_t *btn = lv_button_create(connected_dial_keypad);
    lv_obj_set_size(btn, 160, 75);
    lv_obj_set_style_radius(btn, 35, 0);
    lv_obj_set_style_bg_color(btn, CLOSE_STATE_DEFAULT_COLOR, 0);
    lv_obj_set_style_border_width(btn, 0, 0);
    disable_button_shadow(btn);
    lv_obj_add_event_cb(btn, phone_connected_dial_key_btn_event_cb, LV_EVENT_CLICKED, (void *)connected_dial_keys[i]);
    lv_obj_set_grid_cell(btn, LV_GRID_ALIGN_STRETCH, i % 3, 1, LV_GRID_ALIGN_STRETCH, i / 3, 1);

    lv_obj_t *label = lv_label_create(btn);
    lv_label_set_text(label, connected_dial_keys[i]);
    lv_obj_set_style_text_font(label, &my_equalwidth_font48, 0);
    lv_obj_set_style_text_color(label, lv_color_white(), 0);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 5);
  }
}

static void phone_create_home_page(void)
{
  if (phone_home_page != NULL)
  {
    return;
  }

  phone_home_page = lv_obj_create(lv_scr_act());
  lv_obj_set_size(phone_home_page, MAIN_PAGE_WIDTH, (MAIN_PAGE_HEIGHT - LV_STATUS_BAR_HEIGHT));
  lv_obj_align(phone_home_page, LV_ALIGN_BOTTOM_MID, 0, 0);
  lv_obj_set_style_bg_color(phone_home_page, lv_color_black(), 0);
  lv_obj_set_style_border_width(phone_home_page, 0, 0);
  lv_obj_set_style_pad_all(phone_home_page, 0, 0);
  lv_obj_remove_flag(phone_home_page, LV_OBJ_FLAG_SCROLLABLE);

  lv_obj_t *home_call_btn = lv_button_create(phone_home_page);
  lv_obj_set_size(home_call_btn, 150, 150);
  lv_obj_align(home_call_btn, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_style_radius(home_call_btn, 35, 0);
  lv_obj_set_style_bg_color(home_call_btn, lv_color_hex(0x1E8E3E), 0);
  lv_obj_set_style_border_width(home_call_btn, 0, 0);
  disable_button_shadow(home_call_btn);
  lv_obj_add_event_cb(home_call_btn, phone_home_call_btn_event_cb, LV_EVENT_SHORT_CLICKED, NULL);
  lv_obj_add_event_cb(home_call_btn, phone_home_call_btn_event_cb, LV_EVENT_LONG_PRESSED, NULL);

  lv_obj_t *home_call_img = lv_image_create(home_call_btn);
  lv_image_set_src(home_call_img, sip_call_pic);
  lv_obj_center(home_call_img);
}

static void phone_create_dial_page(void)
{
  if (phone_dial_page == NULL)
  {
    phone_create_dial_objects();
  }

  if (phone_dial_idle_timer == NULL)
  {
    phone_dial_idle_timer = lv_timer_create(phone_dial_idle_timer_cb, 1000, NULL);
  }
}

static void phone_create_call_page(const char *number)
{
  phone_create_call_objects();
  phone_set_number_label(phone_call_number_label, number);

  if (phone_connect_timer == NULL)
  {
    phone_connect_timer = lv_timer_create(phone_connect_timer_cb, 1200, NULL);
    lv_timer_set_auto_delete(phone_connect_timer, false);
  }
}

static void phone_create_answer_page(const char *number)
{
  phone_create_answer_objects();
  phone_set_number_label(phone_answer_number_label, number);
}

static void phone_create_connected_page(const char *number)
{
  phone_create_connected_objects();
  phone_set_number_label(phone_connected_number_label, number);

  if (phone_connected_duration_timer == NULL)
  {
    phone_connected_duration_timer = lv_timer_create(phone_connected_duration_timer_cb, 1000, NULL);
  }
}

static void create_phone_page(void)
{
  lv_indev_t *indev = NULL;
  while ((indev = lv_indev_get_next(indev)) != NULL)
  {
    lv_indev_set_long_press_time(indev, 1000);
  }

  phone_create_home_page();

  phone_show_home_page();
}

static void ui_init(void)
{
  // create_contral_page();
  create_phone_page();
  // phone_create_answer_page("");
}
