/*****************************************************************************
* | File      	:   DEV_Config.c
* | Author      :   Waveshare team
* | Function    :   Hardware underlying interface
* | Info        :
*                Used to shield the underlying layers of each master 
*                and enhance portability
*----------------
* |	This version:   V1.0
* | Date        :   2019-01-18
* | Info        :

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#include "DEV_Config.h"

int fd;

/******************************************************************************
function:   Set the I2C device address
parameter	:
        Add : Device address
******************************************************************************/
void DEV_Set_I2CAddress(UBYTE Add)
{
  fd = i2cOpen(1, Add, 0);    // Per library, i2cFlags = 0
}
/******************************************************************************
function:	
	I2C Write and Read
******************************************************************************/
void DEV_I2C_WriteByte(UBYTE add_, UBYTE data_)
{
  i2cWriteByteData(fd, add_, data_);
}

void DEV_I2C_WriteWord(UBYTE add_, UWORD data_)
{
  i2cWriteWordData(fd, add_, data_);
}

UBYTE DEV_I2C_ReadByte(UBYTE add_)
{
  return i2cReadByteData(fd, add_);
}

UWORD DEV_I2C_ReadWord(UBYTE add_)
{
  return i2cReadWordData(fd, add_);
}
/******************************************************************************
function:	
	Module exits
******************************************************************************/
void DEV_ModuleExit(void)
{
    
}

/******************************************************************************
function:	
	Module initialization, BCM2835 library and initialization pins,
	I2C protocol
******************************************************************************/
UBYTE DEV_ModuleInit(void)
{
  if (gpioInitialise() < 0) {
      printf("pigpio init failed   !!!\r\n");
      return 1;
  } else {
      printf("pigpio init success  !!!\r\n");
  }
  //TODO: PWM Config 
  // softPwmCreate(PWM_PIN, 10, 100);
  // TODO: ** IS THIS THE CORRECT BINDING?? **
  gpioPWM(PWM_PIN, 100);


  fd = i2cOpen(1, IIC_Addr, 0);    // Per library, i2cFlags = 0
  gpioSetMode(INT_PIN, PI_INPUT);
  gpioSetPullUpDown(INT_PIN, PI_PUD_UP);
  return 0;
}

/************************************************/
