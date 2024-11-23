#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "DEV_Config.h"
#include "TCS34725.h"
#include "ColorNaming.h"

UWORD r, g, b, c;

void sig_handler(int _)
{
  printf("\nStopping...\n");
  DEV_ModuleExit();
  exit(0);
}

int main(int argc, char *argv[])
{
  RGB rgb;
  UDOUBLE rgb888 = 0;

  /* Initialization failed. */
  if (DEV_ModuleInit()) {
    exit(0);
  }

  /* Trap SIGINT to exit early. Must be AFTER `gpioInitialise` */
  signal(SIGINT, sig_handler);

  /* Initialize TCS34725. */
  if (TCS34725_Init()) {
    printf("Failed to initialize TCS34725\n");
    exit(0);
  }

  /* Main loop to read color values. */
  while (1) {

    /* This provides the raw RGBC values. */
    rgb = TCS34725_Get_RGBData();

    /* Convert the raw values to RGB888 format.
    * Note: the interface also provides way to convert to 16-bit RGB
    * using TCS_34725_GetRGB565. We'll just use RGB888 for this example. */
    rgb888 = TCS34725_GetRGB888(rgb);

    /* Shift bits to extract and convert to decimal RGB values. */
    int red = (rgb888 >> 16) & 0xff;
    int green = (rgb888 >> 8) & 0xff;
    int blue = rgb888 & 0xff;
    float confidence;

    /* Get the (web) color names. */
    const char *color_name = GetColorName(red, green, blue, &confidence);

    /* Print color preview at start. */
    printf("\033[38;2;%d;%d;%dm█\033[0m", red, green, blue);

    /* Print RGB value name color name. */
    printf(" RGB888 : R=%d G=%d B=%d", red, green, blue);
    printf(" -> Color: %s (Confidence: %.2f%%)\n", color_name, confidence * 100);
  }

  return 0;
}
