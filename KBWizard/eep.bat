call config.bat
call avrdude.exe -c usbasp -p at90usb1287 -U eeprom:w:KBWizard.eep:i
