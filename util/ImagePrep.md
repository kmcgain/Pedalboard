# Steps
Create a 128x96 bmp
Use gimp:
* image->Mode->RGB
* image->Precision->16 bit
* File->Export as bmp
  * Untick 'Compatibility: Do not write color...'
  * Select 16 bit R5G6B5

LCD Image Converter (https://sourceforge.net/projects/lcd-image-converter/):
* New
* Image->Import
* Options->Conversion
* Image->Block size: 16 bit 
* Show Preview
* Copy the displayed bytes and create a variable const uint16_t delayImg[] PROGMEM { PUT_THE_BYTES_HERE };