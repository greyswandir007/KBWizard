#include "KBDescr.h"
/*const USB_Descriptor_HIDReport_Datatype_t PROGMEM MouseReport[] = {//Report descriptor for mouse HID class
	HID_RI_USAGE_PAGE(8, 0x01), 			//Desktop
	HID_RI_USAGE(8, 0x02), 					//Mouse class
	HID_RI_COLLECTION(8, 0x01), 			//Application
		HID_RI_USAGE(8, 0x01), 				//Pointer
		HID_RI_COLLECTION(8, 0x00), 		//Physical device
			HID_RI_USAGE_PAGE(8, 0x09), 	//Buttons
			HID_RI_USAGE_MINIMUM(8, 0x01),	//
			HID_RI_USAGE_MAXIMUM(8, 0x03),	//
			HID_RI_LOGICAL_MINIMUM(8, 0x00),//
			HID_RI_LOGICAL_MAXIMUM(8, 0x01),//
			HID_RI_REPORT_COUNT(8, 0x03),	//Button count
			HID_RI_REPORT_SIZE(8, 0x01),
			HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),
			HID_RI_REPORT_COUNT(8, 0x01),
			HID_RI_REPORT_SIZE(8, 0x05),
			HID_RI_INPUT(8, HID_IOF_CONSTANT),
			HID_RI_USAGE_PAGE(8, 0x01), 	//Desktop
			HID_RI_USAGE(8, 0x30), 			//X
			HID_RI_USAGE(8, 0x31), 			//Y
			HID_RI_LOGICAL_MINIMUM(8, -128),	//Logical minimum -20
			HID_RI_LOGICAL_MAXIMUM(8,  127),	//Logical maximum +20
			HID_RI_PHYSICAL_MINIMUM(8, -128), //Physical minimum (resolution) -5
			HID_RI_PHYSICAL_MAXIMUM(8,  127),	//Physical maximum (resolution) +5
			HID_RI_REPORT_COUNT(8, 0x02),
			HID_RI_REPORT_SIZE(8, 0x08),
			HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_RELATIVE),
		HID_RI_END_COLLECTION(0),
	HID_RI_END_COLLECTION(0),
};*/
const USB_Descriptor_HIDReport_Datatype_t PROGMEM MouseReport[128] = {
     0x05, 0x01,        // USAGE_PAGE (Generic Desktop)
     0x09, 0x02,        // USAGE (Mouse)
     0xa1, 0x01,        // COLLECTION (Application)
     0x09, 0x02,        //   USAGE (Mouse)
     0xa1, 0x02,        //   COLLECTION (Logical)
     0x09, 0x01,        //     USAGE (Pointer)
     0xa1, 0x00,        //     COLLECTION (Physical)
                        // ------------------------------  Buttons
     0x05, 0x09,        //       USAGE_PAGE (Button)
     0x19, 0x01,        //       USAGE_MINIMUM (Button 1)
     0x29, 0x05,        //       USAGE_MAXIMUM (Button 5)
     0x15, 0x00,        //       LOGICAL_MINIMUM (0)
     0x25, 0x01,        //       LOGICAL_MAXIMUM (1)
     0x75, 0x01,        //       REPORT_SIZE (1)
     0x95, 0x05,        //       REPORT_COUNT (5)
     0x81, 0x02,        //       INPUT (Data,Var,Abs)
                        // ------------------------------  Padding
     0x75, 0x03,        //       REPORT_SIZE (3)
     0x95, 0x01,        //       REPORT_COUNT (1)
     0x81, 0x03,        //       INPUT (Cnst,Var,Abs)
                        // ------------------------------  X,Y position
     0x05, 0x01,        //       USAGE_PAGE (Generic Desktop)
     0x09, 0x30,        //       USAGE (X)
     0x09, 0x31,        //       USAGE (Y)
     0x15, 0x80,        //       LOGICAL_MINIMUM (-128)
     0x25, 0x7f,        //       LOGICAL_MAXIMUM (127)
     0x75, 0x08,        //       REPORT_SIZE (8)
     0x95, 0x02,        //       REPORT_COUNT (2)
     0x81, 0x06,        //       INPUT (Data,Var,Rel)
     0xa1, 0x02,        //       COLLECTION (Logical)
                        // ------------------------------  Vertical wheel res multiplier
     0x09, 0x48,        //         USAGE (Resolution Multiplier)
     0x15, 0x00,        //         LOGICAL_MINIMUM (0)
     0x25, 0x01,        //         LOGICAL_MAXIMUM (1)
     0x35, 0x01,        //         PHYSICAL_MINIMUM (1)
     0x45, 0x04,        //         PHYSICAL_MAXIMUM (4)
     0x75, 0x02,        //         REPORT_SIZE (2)
     0x95, 0x01,        //         REPORT_COUNT (1)
     0xb1, 0x02,        //         FEATURE (Data,Var,Abs)
                        // ------------------------------  Vertical wheel
     0x09, 0x38,        //         USAGE (Wheel)
     0x15, 0x80,        //         LOGICAL_MINIMUM (-128)
     0x25, 0x7f,        //         LOGICAL_MAXIMUM (127)
     0x35, 0x00,        //         PHYSICAL_MINIMUM (0)        - reset physical
     0x45, 0x00,        //         PHYSICAL_MAXIMUM (0)
     0x75, 0x08,        //         REPORT_SIZE (8)
     0x81, 0x06,        //         INPUT (Data,Var,Rel)
     0xc0,              //       END_COLLECTION
     0xa1, 0x02,        //       COLLECTION (Logical)
                        // ------------------------------  Horizontal wheel res multiplier
     0x09, 0x48,        //         USAGE (Resolution Multiplier)
     0x15, 0x00,        //         LOGICAL_MINIMUM (0)
     0x25, 0x01,        //         LOGICAL_MAXIMUM (1)
     0x35, 0x01,        //         PHYSICAL_MINIMUM (1)
     0x45, 0x04,        //         PHYSICAL_MAXIMUM (4)
     0x75, 0x02,        //         REPORT_SIZE (2)
     0x95, 0x01,        //         REPORT_COUNT (1)
     0xb1, 0x02,        //         FEATURE (Data,Var,Abs)
                        // ------------------------------  Padding for Feature report
     0x35, 0x00,        //         PHYSICAL_MINIMUM (0)        - reset physical
     0x45, 0x00,        //         PHYSICAL_MAXIMUM (0)
     0x75, 0x04,        //         REPORT_SIZE (4)
     0xb1, 0x03,        //         FEATURE (Cnst,Var,Abs)
                        // ------------------------------  Horizontal wheel
     0x05, 0x0c,        //         USAGE_PAGE (Consumer Devices)
     0x0a, 0x38, 0x02,  //         USAGE (AC Pan)
     0x15, 0x80,        //         LOGICAL_MINIMUM (-128)
     0x25, 0x7f,        //         LOGICAL_MAXIMUM (127)
     0x75, 0x08,        //         REPORT_SIZE (8)
     0x81, 0x06,        //         INPUT (Data,Var,Rel)
     0xc0,              //       END_COLLECTION
     0xc0,              //     END_COLLECTION
     0xc0,              //   END_COLLECTION
     0xc0               // END_COLLECTION
 };
const USB_Descriptor_HIDReport_Datatype_t PROGMEM KeyboardReport[] = {//Report descriptor for keyboard HID class
	HID_RI_USAGE_PAGE(8, 0x01), 			//Desktop
	HID_RI_USAGE(8, 0x06), 					//Keyboard
	HID_RI_COLLECTION(8, 0x01), 			//Application
		HID_RI_USAGE_PAGE(8, 0x07), 		//Key Codes
		HID_RI_USAGE_MINIMUM(8, 0xE0), 		//Keyboard Left Control
		HID_RI_USAGE_MAXIMUM(8, 0xE7), 		//Keyboard Right GUI
		HID_RI_LOGICAL_MINIMUM(8, 0x00),
		HID_RI_LOGICAL_MAXIMUM(8, 0x01),
		HID_RI_REPORT_SIZE(8, 0x01),
		HID_RI_REPORT_COUNT(8, 0x08),
		HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),
		HID_RI_REPORT_COUNT(8, 0x01),
		HID_RI_REPORT_SIZE(8, 0x08),
		HID_RI_INPUT(8, HID_IOF_CONSTANT),
		HID_RI_USAGE_PAGE(8, 0x08), 		//LEDs
		HID_RI_USAGE_MINIMUM(8, 0x01), 		//NumLock
		HID_RI_USAGE_MAXIMUM(8, 0x05), 		//Kana
		HID_RI_REPORT_COUNT(8, 0x05),
		HID_RI_REPORT_SIZE(8, 0x01),
		HID_RI_OUTPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE | HID_IOF_NON_VOLATILE),
		HID_RI_REPORT_COUNT(8, 0x01),
		HID_RI_REPORT_SIZE(8, 0x03),
		HID_RI_OUTPUT(8, HID_IOF_CONSTANT),
		HID_RI_LOGICAL_MINIMUM(8, 0x00),
		HID_RI_LOGICAL_MAXIMUM(8, 0x65),
		HID_RI_USAGE_PAGE(8, 0x07), 		//Keyboard
		HID_RI_USAGE_MINIMUM(8, 0x00), 		//Reserved (no event indicated)
		HID_RI_USAGE_MAXIMUM(8, 0x65), 		//Keyboard Application
		HID_RI_REPORT_COUNT(8, 0x06),
		HID_RI_REPORT_SIZE(8, 0x08),
		HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_ARRAY | HID_IOF_ABSOLUTE),
	HID_RI_END_COLLECTION(0),
};
const USB_Descriptor_HIDReport_Datatype_t PROGMEM ConsumerReport[] = {
    0x05, 0x0c,         // USAGE_PAGE (Consumer Devices)
    0x09, 0x01,             // USAGE (Consumer Control)
    0xa1, 0x01,             // COLLECTION (Application)
    0x05, 0x0c,         	// USAGE_PAGE (Consumer Devices)
    0x85, 0x01,             // REPORT_ID (1)
    0x15, 0x00,             // LOGICAL_MINIMUM (0)
    0x25, 0x01,             // LOGICAL_MAXIMUM (1)
    0x75, 0x01,             // REPORT_SIZE (1)
    0x95, 0x10,             // REPORT_COUNT (16)
    0x09, 0xe2,             // USAGE (Mute) 0x01
    0x09, 0xe9,             // USAGE (Volume Up) 0x02
    0x09, 0xea,             // USAGE (Volume Down) 0x03
    0x09, 0xcd,             // USAGE (Play/Pause) 0x04
    0x09, 0xb7,             // USAGE (Stop) 0x05
    0x09, 0xb6,             // USAGE (Scan Previous Track) 0x06
    0x09, 0xb5,             // USAGE (Scan Next Track) 0x07
    0x0a, 0x8a, 0x01,       // USAGE (Mail) 0x08
    0x0a, 0x92, 0x01,       // USAGE (Calculator) 0x09
    0x0a, 0x21, 0x02,       // USAGE (www search) 0x0a
    0x0a, 0x23, 0x02,       // USAGE (www home) 0x0b
    0x0a, 0x2a, 0x02,       // USAGE (www favorites) 0x0c
    0x0a, 0x27, 0x02,       // USAGE (www refresh) 0x0d
    0x0a, 0x26, 0x02,       // USAGE (www stop) 0x0e
    0x0a, 0x25, 0x02,       // USAGE (www forward) 0x0f
    0x0a, 0x24, 0x02,       // USAGE (www back) 0x10
    0x81, 0x62,             // INPUT (Data,Var,Abs,NPrf,Null)
    0xc0,                   // System Control Descriptor

    0x05, 0x01, 			// Usage Page (Generic Desktop)
    0x09, 0x80,				// Usage (System Control)
    0xA1, 0x01,				// Collection (Application)
    0x05, 0x01, 			// Usage Page (Generic Desktop)
    0x85, 0x02,				// Report ID 0x02 [SYSTEM CTRL]
    0x19, 0x82,				// Usage minimum (System Sleep)
    0x29, 0x83,				// Usage maximum (System Wake up)
    0x95, 0x02,				// Report count (2)
    0x81, 0x06,				// Input (data, variable, relative, Preferred)
    0x95, 0x06,				// Report count (6)
    0x81, 0x01,				// Input (Constant)
    0xC0					// End Collection
};
const USB_Descriptor_HIDReport_Datatype_t PROGMEM GenericReport[] = {//Report descriptor for generic HID class
	HID_RI_USAGE_PAGE(16, 0xFF00),	/* Vendor Page 0 */
	HID_RI_USAGE(8, 0x01),			/* Vendor Usage 1 */
	HID_RI_COLLECTION(8, 0x01),		/* Vendor Usage 1 */
	    HID_RI_USAGE(8, 0x02),		/* Vendor Usage 2 */
	    HID_RI_LOGICAL_MINIMUM(8, 0x00),
	    HID_RI_LOGICAL_MAXIMUM(8, 0xFF),
	    HID_RI_REPORT_SIZE(8, 0x08),
	    HID_RI_REPORT_COUNT(8, HID_GENERIC_EPSIZE),
	    HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),
	    HID_RI_USAGE(8, 0x03),		/* Vendor Usage 3 */
	    HID_RI_LOGICAL_MINIMUM(8, 0x00),
	    HID_RI_LOGICAL_MAXIMUM(8, 0xFF),
	    HID_RI_REPORT_SIZE(8, 0x08),
	    HID_RI_REPORT_COUNT(8, HID_GENERIC_EPSIZE),
	    HID_RI_OUTPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE | HID_IOF_NON_VOLATILE),
	HID_RI_END_COLLECTION(0),
};
const USB_Descriptor_Device_t PROGMEM DeviceDescriptor = {//USB version, control endpoint size and the number of device configurations
	.Header                 = {.Size = sizeof(USB_Descriptor_Device_t), .Type = DTYPE_Device},
	.USBSpecification       = VERSION_BCD(1,1,0),
	.Class                  = USB_CSCP_NoDeviceClass,
	.SubClass               = USB_CSCP_NoDeviceSubclass,
	.Protocol               = USB_CSCP_NoDeviceProtocol,
	.Endpoint0Size          = FIXED_CONTROL_ENDPOINT_SIZE,
	.VendorID               = 0x1209,
	.ProductID              = 0x411D,
	.ReleaseNumber          = VERSION_BCD(0,0,1),
	.ManufacturerStrIndex   = STRING_ID_Manufacturer,
	.ProductStrIndex        = STRING_ID_Product,
	.SerialNumStrIndex      = STRING_ID_Serial,
	.NumberOfConfigurations = FIXED_NUM_CONFIGURATIONS
};
/** Configuration descriptor structure. This descriptor, located in FLASH memory, describes the usage
 *  of the device in one of its supported configurations, including information about any device interfaces
 *  and endpoints. The descriptor is read out by the USB host during the enumeration process when selecting
 *  a configuration so that the host may correctly communicate with the USB device. */
const USB_Descriptor_Configuration_t PROGMEM ConfigurationDescriptor = {//Device usage in one of its supported configurations, interfaces and endpoints.
	.Config = {
		.Header                 = {.Size = sizeof(USB_Descriptor_Configuration_Header_t), .Type = DTYPE_Configuration},
		.TotalConfigurationSize = sizeof(USB_Descriptor_Configuration_t),
		.TotalInterfaces        = 4,
		.ConfigurationNumber    = 1,
		.ConfigurationStrIndex  = NO_DESCRIPTOR,
		.ConfigAttributes       = (USB_CONFIG_ATTR_RESERVED | USB_CONFIG_ATTR_SELFPOWERED),
		.MaxPowerConsumption    = USB_CONFIG_POWER_MA(100)
	},
	.HID1_KeyboardInterface = {
		.Header                 = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},
		.InterfaceNumber        = INTERFACE_ID_Keyboard,
		.AlternateSetting       = 0x00,
		.TotalEndpoints         = 2,
		.Class                  = HID_CSCP_HIDClass,
		.SubClass               = HID_CSCP_BootSubclass,
		.Protocol               = HID_CSCP_KeyboardBootProtocol,
		.InterfaceStrIndex      = NO_DESCRIPTOR
	},
	.HID1_KeyboardHID = {
		.Header                 = {.Size = sizeof(USB_HID_Descriptor_HID_t), .Type = HID_DTYPE_HID},
		.HIDSpec                = VERSION_BCD(1,1,1),
		.CountryCode            = 0x00,
		.TotalReportDescriptors = 1,
		.HIDReportType          = HID_DTYPE_Report,
		.HIDReportLength        = sizeof(KeyboardReport)
	},
	.HID1_ReportINEndpoint = {
		.Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},
		.EndpointAddress        = KEYBOARD_IN_EPADDR,
		.Attributes             = (EP_TYPE_INTERRUPT | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
		.EndpointSize           = HID_EPSIZE,
		.PollingIntervalMS      = 0x08
	},
	.HID1_ReportOUTEndpoint = {
		.Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},
		.EndpointAddress        = KEYBOARD_OUT_EPADDR,
		.Attributes             = (EP_TYPE_INTERRUPT | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
		.EndpointSize           = HID_EPSIZE,
		.PollingIntervalMS      = 0x08
	},
	.HID2_MouseInterface = {
		.Header                 = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},
		.InterfaceNumber        = INTERFACE_ID_Mouse,
		.AlternateSetting       = 0x00,
		.TotalEndpoints         = 1,
		.Class                  = HID_CSCP_HIDClass,
		.SubClass               = HID_CSCP_BootSubclass,
		.Protocol               = HID_CSCP_MouseBootProtocol,
		.InterfaceStrIndex      = NO_DESCRIPTOR
	},
	.HID2_MouseHID = {
		.Header                 = {.Size = sizeof(USB_HID_Descriptor_HID_t), .Type = HID_DTYPE_HID},
		.HIDSpec                = VERSION_BCD(1,1,1),
		.CountryCode            = 0x00,
		.TotalReportDescriptors = 1,
		.HIDReportType          = HID_DTYPE_Report,
		.HIDReportLength        = sizeof(MouseReport)
	},
	.HID2_ReportINEndpoint = {
		.Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},
		.EndpointAddress        = MOUSE_IN_EPADDR,
		.Attributes             = (EP_TYPE_INTERRUPT | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
		.EndpointSize           = HID_EPSIZE,
		.PollingIntervalMS      = 0x08
	},
	.HID3_ConsumerInterface = {
		.Header                 = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},
		.InterfaceNumber        = INTERFACE_ID_Consumer,
		.AlternateSetting       = 0x00,
		.TotalEndpoints         = 1,
		.Class                  = HID_CSCP_HIDClass,
		.SubClass               = HID_CSCP_NonBootSubclass,
		.Protocol               = HID_CSCP_NonBootProtocol,
		.InterfaceStrIndex      = NO_DESCRIPTOR
	},
	.HID3_ConsumerHID = {
		.Header                 = {.Size = sizeof(USB_HID_Descriptor_HID_t), .Type = HID_DTYPE_HID},
		.HIDSpec                = VERSION_BCD(1,1,1),
		.CountryCode            = 0x00,
		.TotalReportDescriptors = 1,
		.HIDReportType          = HID_DTYPE_Report,
		.HIDReportLength        = sizeof(ConsumerReport)
	},
	.HID3_ReportINEndpoint = {
		.Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},
		.EndpointAddress        = CONSUMER_IN_EPADDR,
		.Attributes             = (EP_TYPE_INTERRUPT | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
		.EndpointSize           = HID_EPSIZE,
		.PollingIntervalMS      = 0x08
	},
	.HID4_GenericInterface = {
		.Header                 = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},
		.InterfaceNumber        = INTERFACE_ID_Generic,
		.AlternateSetting       = 0x00,
		.TotalEndpoints         = 2,
		.Class                  = HID_CSCP_HIDClass,
		.SubClass               = HID_CSCP_NonBootSubclass,
		.Protocol               = HID_CSCP_NonBootProtocol,
		.InterfaceStrIndex      = NO_DESCRIPTOR
	},
	.HID4_GenericHID = {
		.Header                 = {.Size = sizeof(USB_HID_Descriptor_HID_t), .Type = HID_DTYPE_HID},
		.HIDSpec                = VERSION_BCD(1,1,1),
		.CountryCode            = 0x00,
		.TotalReportDescriptors = 1,
		.HIDReportType          = HID_DTYPE_Report,
		.HIDReportLength        = sizeof(GenericReport)
	},
	.HID4_ReportINEndpoint = {
		.Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},
		.EndpointAddress        = GENERIC_IN_EPADDR,
		.Attributes             = (EP_TYPE_INTERRUPT | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
		.EndpointSize           = HID_GENERIC_EPSIZE,
		.PollingIntervalMS      = 0x08
	},
	.HID4_ReportOUTEndpoint = {
		.Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},
		.EndpointAddress        = GENERIC_OUT_EPADDR,
		.Attributes             = (EP_TYPE_INTERRUPT | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
		.EndpointSize           = HID_GENERIC_EPSIZE,
		.PollingIntervalMS      = 0x08
	}
};
const USB_Descriptor_String_t PROGMEM LanguageString = USB_STRING_DESCRIPTOR_ARRAY(LANGUAGE_ID_ENG);//Language ID
const USB_Descriptor_String_t PROGMEM ManufacturerString = USB_STRING_DESCRIPTOR(L"Wizard Inc.");//Manufacturer String
#ifdef LEFT_PART_KEY
const USB_Descriptor_String_t PROGMEM ProductString = USB_STRING_DESCRIPTOR(L"KBWizardLeft");//Product string
#else
const USB_Descriptor_String_t PROGMEM ProductString = USB_STRING_DESCRIPTOR(L"KBWizardRight");//Product string
#endif
const USB_Descriptor_String_t PROGMEM SerialString = USB_STRING_DESCRIPTOR(L"00000001");//Serial string
/** This function is called by the library when in device mode, and must be overridden (see "USB Descriptors" documentation)
 *  by the application code so that the address and size of a requested descriptor can be given to the USB library. When
 *  the device receives a Get Descriptor request on the control endpoint, this function is called so that the descriptor
 * details can be passed back and the appropriate descriptor sent back to the USB host. */
uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue, const uint16_t wIndex, const void** const DescriptorAddress) {
	const uint8_t  DescriptorType   = (wValue >> 8);
	const uint8_t  DescriptorNumber = (wValue & 0xFF);
	const void* Address = NULL;
	uint16_t    Size    = NO_DESCRIPTOR;
	switch (DescriptorType) {
		case DTYPE_Device:
			Address = &DeviceDescriptor;
			Size    = sizeof(USB_Descriptor_Device_t);
			break;
		case DTYPE_Configuration:
			Address = &ConfigurationDescriptor;
			Size    = sizeof(USB_Descriptor_Configuration_t);
			break;
		case DTYPE_String:
			switch (DescriptorNumber) {
				case STRING_ID_Language:
					Address = &LanguageString;
					Size    = pgm_read_byte(&LanguageString.Header.Size);
					break;
				case STRING_ID_Manufacturer:
					Address = &ManufacturerString;
					Size    = pgm_read_byte(&ManufacturerString.Header.Size);
					break;
				case STRING_ID_Product:
					Address = &ProductString;
					Size    = pgm_read_byte(&ProductString.Header.Size);
					break;
				case STRING_ID_Serial:
					Address = &SerialString;
					Size = pgm_read_byte(&SerialString.Header.Size);
					break;
			}
			break;
		case HID_DTYPE_HID:
			switch (wIndex) {
				case (INTERFACE_ID_Keyboard):
					Address = &ConfigurationDescriptor.HID1_KeyboardHID;
					Size    = sizeof(USB_HID_Descriptor_HID_t);
					break;
				case (INTERFACE_ID_Mouse):
					Address = &ConfigurationDescriptor.HID2_MouseHID;
					Size    = sizeof(USB_HID_Descriptor_HID_t);
					break;
				case (INTERFACE_ID_Consumer):
					Address = &ConfigurationDescriptor.HID3_ConsumerHID;
					Size    = sizeof(USB_HID_Descriptor_HID_t);
					break;
				case (INTERFACE_ID_Generic):
					Address = &ConfigurationDescriptor.HID4_GenericHID;
					Size    = sizeof(USB_HID_Descriptor_HID_t);
					break;
			}
			break;
		case HID_DTYPE_Report:
			switch (wIndex) {
				case INTERFACE_ID_Keyboard:
					Address = &KeyboardReport;
					Size    = sizeof(KeyboardReport);
					break;
				case INTERFACE_ID_Mouse:
					Address = &MouseReport;
					Size    = sizeof(MouseReport);
					break;
				case INTERFACE_ID_Consumer:
					Address = &ConsumerReport;
					Size = sizeof(ConsumerReport);
					break;
				case INTERFACE_ID_Generic:
					Address = &GenericReport;
					Size    = sizeof(GenericReport);
					break;
			}
			break;
	}
	*DescriptorAddress = Address;
	return Size;
}

