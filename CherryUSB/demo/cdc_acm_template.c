/*
 * Copyright (c) 2024, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbd_core.h"
#include "usbd_cdc_acm.h"

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
/* USB rx ringbuffer */
#define USB_RX_DATA_SIZE 2048
uint8_t usb_rxBuffer_cherryusb[USB_RX_DATA_SIZE];
volatile uint32_t usb_rxBufPtrIn_cherryusb = 0;
volatile uint32_t usb_rxBufPtrOut_cherryusb = 0;

unsigned char vcp_read_cherryusb(void) {
    unsigned char c;
    if (usb_rxBufPtrIn_cherryusb == usb_rxBufPtrOut_cherryusb) {
        c = -1;
    } else {
        c = usb_rxBuffer_cherryusb[usb_rxBufPtrOut_cherryusb];
        usb_rxBufPtrOut_cherryusb = (usb_rxBufPtrOut_cherryusb + 1) % USB_RX_DATA_SIZE;
    }
    return c;
}

// 当 USB OUT 端点接收到数据时，USB 驱动会调用此函数
void usbd_cdc_acm_bulk_out(uint8_t busid, uint8_t ep, uint32_t nbytes)
{
    printf("\r\n--- usbd_cdc_acm_bulk_out called ---\r\n"); // 明确函数入口
    USB_LOG_RAW("actual out len:%d\r\n", (unsigned int)nbytes); // 打印接收到的字节数

    // 如果没有接收到数据，直接返回
    if (nbytes == 0) {
        printf("No data received (nbytes = 0).\r\n");
        // 仍然需要设置下一个读取传输
        usbd_ep_start_read(busid, CDC_OUT_EP, usb_rxBuffer_cherryusb, USB_RX_DATA_SIZE);
        return;
    }

    // --- 缓冲区空间检查 ---
    uint32_t current_buffer_free_space;
    if (usb_rxBufPtrIn_cherryusb >= usb_rxBufPtrOut_cherryusb) {
        current_buffer_free_space = USB_RX_DATA_SIZE - (usb_rxBufPtrIn_cherryusb - usb_rxBufPtrOut_cherryusb) - 1; // 留一个位置防止in==out被误判为空
    } else {
        current_buffer_free_space = (usb_rxBufPtrOut_cherryusb - usb_rxBufPtrIn_cherryusb) - 1;
    }

    if (nbytes > current_buffer_free_space) {
        printf("USB RX Buffer Overflow! Discarding %u bytes (Free space: %u).\r\n", (unsigned int)nbytes, (unsigned int)current_buffer_free_space);
        // 如果发生溢出，不处理这些数据，直接返回或只接受部分。
        // 这里我们选择丢弃所有。
        usbd_ep_start_read(busid, CDC_OUT_EP, usb_rxBuffer_cherryusb, USB_RX_DATA_SIZE);
        return;
    }

    // --- 打印接收到的原始数据 (十六进制和 ASCII) ---
    printf("Received data (Hex Dump):\r\n");
    for (uint32_t i = 0; i < nbytes; i++) {
        // 计算当前字节在 usb_rxBuffer_cherryusb 中的实际索引
        // 这里的关键是：数据是直接从 usb_rxBufPtrIn_cherryusb 开始写入的。
        // 所以我们应该从 usb_rxBufPtrIn_cherryusb 偏移 i 来读取。
        uint32_t data_index_in_buffer = (usb_rxBufPtrIn_cherryusb + i) % USB_RX_DATA_SIZE;
        uint8_t byte = usb_rxBuffer_cherryusb[data_index_in_buffer];

        // 打印十六进制值
        printf("%02X ", byte); // %02X 保证两位十六进制，不足补0

        // 每16个字节换行，方便查看
        if ((i + 1) % 16 == 0) {
            printf("\r\n");
        }
    }
    printf("\r\n"); // 确保最后有一个换行

    // 打印可打印的 ASCII 字符（如果数据是文本）
    printf("Received data (ASCII):\r\n[");
    for (uint32_t i = 0; i < nbytes; i++) {
        uint32_t data_index_in_buffer = (usb_rxBufPtrIn_cherryusb + i) % USB_RX_DATA_SIZE;
        uint8_t byte = usb_rxBuffer_cherryusb[data_index_in_buffer];
        // 只打印可显示的 ASCII 字符，否则打印 '.'
        if (byte >= 0x20 && byte <= 0x7E) {
            printf("%c", byte);
        } else {
            printf(".");
        }
    }
    printf("]\r\n");

    // --- 更新 'in' 指针 ---
    // 只有在数据被成功处理（即没有溢出）后才更新 'in' 指针
    usb_rxBufPtrIn_cherryusb = (usb_rxBufPtrIn_cherryusb + nbytes) % USB_RX_DATA_SIZE;
    printf("New usb_rxBufPtrIn_cherryusb: %lu\r\n", usb_rxBufPtrIn_cherryusb);

    /* setup next out ep read transfer */
    // 重新启动下一个 OUT 端点读取传输，继续将数据放入 usb_rxBuffer_cherryusb
    usbd_ep_start_read(busid, CDC_OUT_EP, usb_rxBuffer_cherryusb, USB_RX_DATA_SIZE);

    printf("--- usbd_cdc_acm_bulk_out finished ---\r\n\r\n");
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

