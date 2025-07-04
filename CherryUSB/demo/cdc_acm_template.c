/*
 * Copyright (c) 2024, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "ds1302.h"
#include "usbd_core.h"
#include "usbd_cdc_acm.h"
#include "main.h"

/*!< endpoint address */
#define CDC_IN_EP  0x81
#define CDC_OUT_EP 0x02
#define CDC_INT_EP 0x83

#define USBD_VID           0xFFFF
#define USBD_PID           0xFFFF
#define USBD_MAX_POWER     100
#define USBD_LANGID_STRING 1033

/*!< config descriptor size */
#define USB_CONFIG_SIZE (9 + CDC_ACM_DESCRIPTOR_LEN)

#ifdef CONFIG_USB_HS
#define CDC_MAX_MPS 512
#else
#define CDC_MAX_MPS 64
#endif

#ifdef CONFIG_USBDEV_ADVANCE_DESC
static const uint8_t device_descriptor[] = {
    USB_DEVICE_DESCRIPTOR_INIT(USB_2_0, 0xEF, 0x02, 0x01, USBD_VID, USBD_PID, 0x0100, 0x01)
};

static const uint8_t config_descriptor[] = {
    USB_CONFIG_DESCRIPTOR_INIT(USB_CONFIG_SIZE, 0x02, 0x01, USB_CONFIG_BUS_POWERED, USBD_MAX_POWER),
    CDC_ACM_DESCRIPTOR_INIT(0x00, CDC_INT_EP, CDC_OUT_EP, CDC_IN_EP, CDC_MAX_MPS, 0x02)
};

static const uint8_t device_quality_descriptor[] = {
    ///////////////////////////////////////
    /// device qualifier descriptor
    ///////////////////////////////////////
    0x0a,
    USB_DESCRIPTOR_TYPE_DEVICE_QUALIFIER,
    0x00,
    0x02,
    0x00,
    0x00,
    0x00,
    0x40,
    0x00,
    0x00,
};

static const char *string_descriptors[] = {
    (const char[]){ 0x09, 0x04 }, /* Langid */
    "CherryUSB",                  /* Manufacturer */
    "CherryUSB CDC DEMO",         /* Product */
    "2022123456",                 /* Serial Number */
};

static const uint8_t *device_descriptor_callback(uint8_t speed)
{
    return device_descriptor;
}

static const uint8_t *config_descriptor_callback(uint8_t speed)
{
    return config_descriptor;
}

static const uint8_t *device_quality_descriptor_callback(uint8_t speed)
{
    return device_quality_descriptor;
}

static const char *string_descriptor_callback(uint8_t speed, uint8_t index)
{
    if (index > 3) {
        return NULL;
    }
    return string_descriptors[index];
}

const struct usb_descriptor cdc_descriptor = {
    .device_descriptor_callback = device_descriptor_callback,
    .config_descriptor_callback = config_descriptor_callback,
    .device_quality_descriptor_callback = device_quality_descriptor_callback,
    .string_descriptor_callback = string_descriptor_callback
};
#else
/*!< global descriptor */
static const uint8_t cdc_descriptor[] = {
    USB_DEVICE_DESCRIPTOR_INIT(USB_2_0, 0xEF, 0x02, 0x01, USBD_VID, USBD_PID, 0x0100, 0x01),
    USB_CONFIG_DESCRIPTOR_INIT(USB_CONFIG_SIZE, 0x02, 0x01, USB_CONFIG_BUS_POWERED, USBD_MAX_POWER),
    CDC_ACM_DESCRIPTOR_INIT(0x00, CDC_INT_EP, CDC_OUT_EP, CDC_IN_EP, CDC_MAX_MPS, 0x02),
    ///////////////////////////////////////
    /// string0 descriptor
    ///////////////////////////////////////
    USB_LANGID_INIT(USBD_LANGID_STRING),
    ///////////////////////////////////////
    /// string1 descriptor
    ///////////////////////////////////////
    0x14,                       /* bLength */
    USB_DESCRIPTOR_TYPE_STRING, /* bDescriptorType */
    'C', 0x00,                  /* wcChar0 */
    'h', 0x00,                  /* wcChar1 */
    'e', 0x00,                  /* wcChar2 */
    'r', 0x00,                  /* wcChar3 */
    'r', 0x00,                  /* wcChar4 */
    'y', 0x00,                  /* wcChar5 */
    'U', 0x00,                  /* wcChar6 */
    'S', 0x00,                  /* wcChar7 */
    'B', 0x00,                  /* wcChar8 */
    ///////////////////////////////////////
    /// string2 descriptor
    ///////////////////////////////////////
    0x26,                       /* bLength */
    USB_DESCRIPTOR_TYPE_STRING, /* bDescriptorType */
    'C', 0x00,                  /* wcChar0 */
    'h', 0x00,                  /* wcChar1 */
    'e', 0x00,                  /* wcChar2 */
    'r', 0x00,                  /* wcChar3 */
    'r', 0x00,                  /* wcChar4 */
    'y', 0x00,                  /* wcChar5 */
    'U', 0x00,                  /* wcChar6 */
    'S', 0x00,                  /* wcChar7 */
    'B', 0x00,                  /* wcChar8 */
    ' ', 0x00,                  /* wcChar9 */
    'C', 0x00,                  /* wcChar10 */
    'D', 0x00,                  /* wcChar11 */
    'C', 0x00,                  /* wcChar12 */
    ' ', 0x00,                  /* wcChar13 */
    'D', 0x00,                  /* wcChar14 */
    'E', 0x00,                  /* wcChar15 */
    'M', 0x00,                  /* wcChar16 */
    'O', 0x00,                  /* wcChar17 */
    ///////////////////////////////////////
    /// string3 descriptor
    ///////////////////////////////////////
    0x16,                       /* bLength */
    USB_DESCRIPTOR_TYPE_STRING, /* bDescriptorType */
    '2', 0x00,                  /* wcChar0 */
    '0', 0x00,                  /* wcChar1 */
    '2', 0x00,                  /* wcChar2 */
    '2', 0x00,                  /* wcChar3 */
    '1', 0x00,                  /* wcChar4 */
    '2', 0x00,                  /* wcChar5 */
    '3', 0x00,                  /* wcChar6 */
    '4', 0x00,                  /* wcChar7 */
    '5', 0x00,                  /* wcChar8 */
    '6', 0x00,                  /* wcChar9 */
#ifdef CONFIG_USB_HS
    ///////////////////////////////////////
    /// device qualifier descriptor
    ///////////////////////////////////////
    0x0a,
    USB_DESCRIPTOR_TYPE_DEVICE_QUALIFIER,
    0x00,
    0x02,
    0x00,
    0x00,
    0x00,
    0x40,
    0x00,
    0x00,
#endif
    0x00
};
#endif

USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t read_buffer[2048]; /* 2048 is only for test speed , please use CDC_MAX_MPS for common*/
USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t write_buffer[2048];

volatile bool ep_tx_busy_flag = false;

static void usbd_event_handler(uint8_t busid, uint8_t event)
{
    switch (event) {
        case USBD_EVENT_RESET:
            break;
        case USBD_EVENT_CONNECTED:
            break;
        case USBD_EVENT_DISCONNECTED:
            break;
        case USBD_EVENT_RESUME:
            break;
        case USBD_EVENT_SUSPEND:
            break;
        case USBD_EVENT_CONFIGURED:
            ep_tx_busy_flag = false;
            /* setup first out ep read transfer */
            usbd_ep_start_read(busid, CDC_OUT_EP, read_buffer, 2048);
            break;
        case USBD_EVENT_SET_REMOTE_WAKEUP:
            break;
        case USBD_EVENT_CLR_REMOTE_WAKEUP:
            break;

        default:
            break;
    }
}

int areTimeStructsEqual(const Time_s *time1, const Time_s *time2) {
    if (time1 == NULL || time2 == NULL) {
        return 0;
    }

    if (time1->day != time2->day) {
        return 1; // 星期几不相等
    }
    if (time1->sec != time2->sec) {
        return 1; // 秒不相等
    }
    if (time1->min != time2->min) {
        return 1; // 分不相等
    }
    if (time1->year != time2->year) {
        return 1; // 年不相等
    }
    if (time1->hour != time2->hour) {
        return 1; // 小时不相等
    }
    if (time1->date != time2->date) {
        return 1; // 月份中的日期不相等
    }
    if (time1->month != time2->month) {
        return 1; // 月不相等
    }
    if (time1->clockSystem != time2->clockSystem) {
        return 1; // 时钟系统不相等 (12h/24h)
    }
    if (time1->clockPeriod != time2->clockPeriod) {
        return 1; // AM/PM 不相等
    }

    return 0;
}

void usb_transmit_string(uint8_t *data, int32_t length);

void usbd_cdc_acm_bulk_out(uint8_t busid, uint8_t ep, uint32_t nbytes)
{
    USB_LOG_RAW("actual out len:%d\r\n", nbytes);

    for (int i = 0; i < nbytes; i++) {
        printf("%02x ", read_buffer[i]);
    }
    printf("\r\n");
    if (nbytes < sizeof(read_buffer)) {
        read_buffer[nbytes] = '\0';
    } else {
        USB_LOG_RAW("Warning: read_buffer might not be null-terminated safely for string parsing.\r\n");
        read_buffer[sizeof(read_buffer) - 1] = '\0';
    }

    char *endptr;
    char *str = (char*)read_buffer;

    syncTime.year = (int)strtol(str, &endptr, 10) - 2000;
    if (str == endptr || *endptr != '/') {
        printf("解析年份失败或格式不符！\r\n");
        goto parse_error;
    }
    str = endptr + 1;

    syncTime.month = (int)strtol(str, &endptr, 10);
    if (str == endptr || *endptr != '/') {
        printf("解析月份失败或格式不符！\r\n");
        goto parse_error;
    }
    str = endptr + 1;

    syncTime.date = (int)strtol(str, &endptr, 10);
    if (str == endptr || *endptr != ' ') {
        printf("解析日期失败或格式不符！\r\n");
        goto parse_error;
    }
    str = endptr + 1;

    syncTime.hour = (int)strtol(str, &endptr, 10);
    if (str == endptr || *endptr != ':') {
        printf("解析小时失败或格式不符！\r\n");
        goto parse_error;
    }
    str = endptr + 1;

    syncTime.min = (int)strtol(str, &endptr, 10);
    if (str == endptr || *endptr != ':') {
        printf("解析分钟失败或格式不符！\r\n");
        goto parse_error;
    }
    str = endptr + 1;

    syncTime.sec = (int)strtol(str, &endptr, 10);
    if (str == endptr) {
        printf("解析秒钟失败！\r\n");
        goto parse_error;
    }

    // handle sync time
    systemTime.sec = syncTime.sec;
    systemTime.min = syncTime.min;
    systemTime.hour = syncTime.hour;
    systemTime.date = syncTime.date;
    systemTime.month = syncTime.month;
    systemTime.year = syncTime.year;
    ds1302_set_time(&syncTime);
    ds1302_set_time(&syncTime);
    ds1302_get_time(&systemTime);

    if (0 == areTimeStructsEqual(&syncTime, &systemTime)) {
        err_times = 0;
        printf("OK!\r\n");
        sync_state = 0;
    }else {
        err_times = 0;
        printf("Time Sync Fail!\r\n");
        sync_state = 1;
    }

    printf("Current time: %d/%d/%d %d:%d:%d\r\n", systemTime.date, systemTime.month, systemTime.year, systemTime.hour, systemTime.min, systemTime.sec);

    goto parse_success;

parse_error:
    printf("时间字符串解析过程中发生错误！\r\n");

parse_success:
    /* setup next out ep read transfer */
    usbd_ep_start_read(busid, CDC_OUT_EP, read_buffer, 2048);
}

void usbd_cdc_acm_bulk_in(uint8_t busid, uint8_t ep, uint32_t nbytes)
{
    USB_LOG_RAW("actual in len:%d\r\n", (unsigned int)nbytes);

    if ((nbytes % usbd_get_ep_mps(busid, ep)) == 0 && nbytes) {
        /* send zlp */
        usbd_ep_start_write(busid, CDC_IN_EP, NULL, 0);
    } else {
        ep_tx_busy_flag = false;
    }
}

/*!< endpoint call back */
struct usbd_endpoint cdc_out_ep = {
    .ep_addr = CDC_OUT_EP,
    .ep_cb = usbd_cdc_acm_bulk_out
};

struct usbd_endpoint cdc_in_ep = {
    .ep_addr = CDC_IN_EP,
    .ep_cb = usbd_cdc_acm_bulk_in
};

static struct usbd_interface intf0;
static struct usbd_interface intf1;

void cdc_acm_init(uint8_t busid, uintptr_t reg_base)
{
    const uint8_t data[10] = { 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30 };

    memcpy(&write_buffer[0], data, 10);
    memset(&write_buffer[10], 'a', 2038);

#ifdef CONFIG_USBDEV_ADVANCE_DESC
    usbd_desc_register(busid, &cdc_descriptor);
#else
    usbd_desc_register(busid, cdc_descriptor);
#endif
    usbd_add_interface(busid, usbd_cdc_acm_init_intf(busid, &intf0));
    usbd_add_interface(busid, usbd_cdc_acm_init_intf(busid, &intf1));
    usbd_add_endpoint(busid, &cdc_out_ep);
    usbd_add_endpoint(busid, &cdc_in_ep);
    usbd_initialize(busid, reg_base, usbd_event_handler);
}

volatile uint8_t dtr_enable = 0;

void usbd_cdc_acm_set_dtr(uint8_t busid, uint8_t intf, bool dtr)
{
    if (dtr) {
        dtr_enable = 1;
    } else {
        dtr_enable = 0;
    }
}

void cdc_acm_data_send_with_dtr_test(uint8_t busid)
{
    if (dtr_enable) {
        ep_tx_busy_flag = true;
        usbd_ep_start_write(busid, CDC_IN_EP, write_buffer, 2048);
        while (ep_tx_busy_flag) {
        }
    }
}

void usb_transmit_string(uint8_t *data, int32_t length) {
    if (data == NULL || length <= 0) {
        return;
    }

    ep_tx_busy_flag = true;
    if (usbd_ep_start_write(0, CDC_IN_EP, data, length) == 0) {
        while (ep_tx_busy_flag) {
        }
    } else {
        ;
    }
}