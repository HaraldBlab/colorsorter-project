# colorsorter-project

## Story
Last christmas I got the wonderful Lego (R) Art Iron man set.
https://www.lego.com/de-at/product/marvel-studios-iron-man-31199.
It offers three different portraits. Each assembles 20 x 20 x 9 bricks in 15 different colors.

### build
It was great fun to build the first of three portraits.

### disassemble
Before building the second portrait I have to disassemble the first one.

### sort
To make life easier I sorted the 3600 bricks by color. This is *troublesome*.
And it takes about 70 minutes to complete.

## Idea
Let the machine do the troublesome work. 

Build a machine with motors and color sensor to select a single brick, detect the brick color and deploy it to a bucket on its color.
Do it 3600 times, and sorting is done.

## Project
Motors: SG90 servo motors
Color sensor: ADPS9960 I2C device from Adafruit
Application: Sketch with microcontroller, make it happen on fpga.

*This is only sketch of a solution. Full implementation to come!*

### notebook
Jyputer notebook documentation.

### microcontroller
Arduino based sketch of the machine.

### fpga
FPGA based hardware solution of the machine.
