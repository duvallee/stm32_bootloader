/*
 * File: usb_device.c
 *
 * Written by duvallee in 2018
 *
 */
#include "main.h"

#include "usbd_core.h"
#if defined(USE_USB_CDC_DEVICE)
#include "usbd_cdc.h"
#endif
#include "usbd_desc.h"
#include "usbd_cdc_interface.h"

#include "usb_device.h"

// ===============================================================================
USBD_HandleTypeDef gUSBD_Device;

#if defined(USE_USB_CDC_DEVICE)
extern USBD_CDC_ItfTypeDef USBD_CDC_fops;
#endif

/* --------------------------------------------------------------------------
 * Name : usb_device_init()
 *
 *
 * -------------------------------------------------------------------------- */
int usb_device_init(void)
{
#if defined(USE_USB_CDC_DEVICE)
   // Init Device Library
   USBD_Init(&gUSBD_Device, &VCP_Desc, 0);

   // Add Supported Class
   USBD_RegisterClass(&gUSBD_Device, USBD_CDC_CLASS);

   // Add CDC Interface Class
   USBD_CDC_RegisterInterface(&gUSBD_Device, &USBD_CDC_fops);

   // Start Device Process
   USBD_Start(&gUSBD_Device);

   HAL_PWREx_EnableUSBVoltageDetector();
#endif
   return 0;
}

/* --------------------------------------------------------------------------
 * Name : usb_read()
 *
 *
 * -------------------------------------------------------------------------- */
void usb_read(uint8_t* Buf, uint16_t Len)
{
#if 0    // for echo test
   usb_write(Buf, Len);
#endif
}

/* --------------------------------------------------------------------------
 * Name : usb_write()
 *
 *
 * -------------------------------------------------------------------------- */
void usb_write(uint8_t* Buf, uint16_t Len)
{
   CDC_Itf_Transmitter(Buf, Len);
}



