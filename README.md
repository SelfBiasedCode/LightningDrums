# LightningDrums

## Summary


## Technical Details

## Requirements
* Arduino IDE
* FastLED (download via Arduino IDE)
* AtmelStudio 7
* avr-gcc 7 or higher (download at https://blog.zakkemble.net/avr-gcc-builds/ )

## Build

1. Install Arduino IDE, ideally to the default path C:\Program Files (x86)\Arduino .
2. Download FastLED using the Arduino IDE library manager.
3. If the library was downloaded to $User\Arduino\libraries: move it to the "libraries" folder in the Arduino executable folder.
4. Install AtmelStudio.
5. Download avr-gcc 7 or higher and add it as a toolchain to Atmel Studio. There are two options to do this:
5.1 Go to the Atmel Studio folder (default: C:\Program Files (x86)\Atmel\Studio\7.0), then to toolchain\avr8. Rename the existing  folder "avr8-gnu-toolchain" to "avr8-gnu-toolchain_old". Extract the new avr-gcc folder into the "avr8" folder and rename it to "avr8-gnu-toolchain". Atmel Studio will automatically use the new version from now on.
5.2 Go to the Atmel Studio folder (default: C:\Program Files (x86)\Atmel\Studio\7.0), then to toolchain\avr8. Extract the new avr-gcc folder into the "avr8" folder. Open Atmel Studio and go to Tools -> Options -> Toolchain. Select "Atmel AVR 8-Bit (C language)" in the dropdown. Click "Add Flavour", enter a meaningful name and select the new avr-gcc directory as a path. Close the dialog and make sure the new flavour is the default one. Repeat this for "Atmel AVR 8-Bit (CPP language)".
6. Open the LightingDrums Solution.
7. Build.

## Usage


## Known Issues


## TODO
