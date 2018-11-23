#ifndef _DESCRIPTORS_H_
#define _DESCRIPTORS_H_
#include <LUFA/Drivers/USB/USB.h>
#include <avr/pgmspace.h>
typedef struct {
	USB_Descriptor_Configuration_Header_t Config;
	// Keyboard HID Interface
	USB_Descriptor_Interface_t            HID1_KeyboardInterface;
	USB_HID_Descriptor_HID_t              HID1_KeyboardHID;
	USB_Descriptor_Endpoint_t             HID1_ReportINEndpoint;
	USB_Descriptor_Endpoint_t             HID1_ReportOUTEndpoint;
	// Mouse HID Interface
	USB_Descriptor_Interface_t            HID2_MouseInterface;
	USB_HID_Descriptor_HID_t              HID2_MouseHID;
	USB_Descriptor_Endpoint_t             HID2_ReportINEndpoint;
	// Consumer HID Interface
	USB_Descriptor_Interface_t            HID3_ConsumerInterface;
	USB_HID_Descriptor_HID_t              HID3_ConsumerHID;
	USB_Descriptor_Endpoint_t             HID3_ReportINEndpoint;
	// Generic HID Interface
	USB_Descriptor_Interface_t            HID4_GenericInterface;
	USB_HID_Descriptor_HID_t              HID4_GenericHID;
	USB_Descriptor_Endpoint_t             HID4_ReportINEndpoint;
	USB_Descriptor_Endpoint_t             HID4_ReportOUTEndpoint;
} USB_Descriptor_Configuration_t;

enum InterfaceDescriptors_t { //Device interface descriptor IDs within the device.
	INTERFACE_ID_Keyboard = 0, //< Keyboard interface descriptor ID
	INTERFACE_ID_Mouse    = 1, //< Mouse interface descriptor ID
	INTERFACE_ID_Consumer = 2, //< Mouse interface descriptor ID
	INTERFACE_ID_Generic  = 3, //< GenericHID interface descriptor ID */
};
enum StringDescriptors_t { //Device string descriptor IDs within the device
	STRING_ID_Language     = 0, //< Supported Languages string descriptor ID (must be zero)
	STRING_ID_Manufacturer = 1, //< Manufacturer string ID
	STRING_ID_Product      = 2, //< Product string ID
	STRING_ID_Serial       = 3, //< Serial string ID
};
#define KEYBOARD_IN_EPADDR        (ENDPOINT_DIR_IN  | 1)	//Endpoint address of the Keyboard HID reporting IN endpoint.
#define KEYBOARD_OUT_EPADDR       (ENDPOINT_DIR_OUT | 2)	//Endpoint address of the Keyboard HID reporting OUT endpoint.
#define MOUSE_IN_EPADDR           (ENDPOINT_DIR_IN  | 3)	//Endpoint address of the Mouse HID reporting IN endpoint.
#define CONSUMER_IN_EPADDR        (ENDPOINT_DIR_IN  | 4)	//Endpoint address of the Consumer HID reporting IN endpoint.
#define GENERIC_IN_EPADDR         (ENDPOINT_DIR_IN  | 5)    //Endpoint address of the Generic HID reporting IN endpoint.
#define GENERIC_OUT_EPADDR        (ENDPOINT_DIR_OUT | 6)    //Endpoint address of the Generic HID reporting OUT endpoint. */
#define HID_EPSIZE                8 						//Size in bytes of each of the HID reporting IN and OUT endpoints.
#define HID_GENERIC_EPSIZE        8 						//Size in bytes of each of the Generic HID reporting IN and OUT endpoints.
uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue, const uint16_t wIndex, const void** const DescriptorAddress)
									ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(3);
#endif

