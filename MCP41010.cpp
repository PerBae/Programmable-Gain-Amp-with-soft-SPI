/*
 * MCP41010.cpp
 *
 *  Created on: Dec 30, 2024
 *      Author: Per
 */
#include "stm32c0xx_hal.h"
#include "stm32c0xx_hal_def.h"
#include "stm32c031xx.h"
#include "stm32c0xx_hal_gpio.h"

#include "MCP41010.h"

/*******************************************
 * constructor
 *
 *******************************************/
MCP41010::MCP41010() : SoftSPI(1,0) // phase & pol
{

}

/*******************************************
 * destructor
 *
 *******************************************/
MCP41010::~MCP41010()
{
}

/*******************************************
 * set gain for non-inverting amplifier
 *
 * The resistor feeds the inverting input via its wiper.
 * The ends of the resistor are connected to ground and
 * amplifier output respectively.
 * See https://ww1.microchip.com/downloads/aemDocuments/documents/OTH/ProductDocuments/DataSheets/11195c.pdf
 * figure 4-5.
 *
 * gain = 1 + code/(256-code)
 *
 * 1 <= gain <= 256
 *
 *******************************************/
void MCP41010::SetGain(int gain)
{
#define CMD_CODE 0x1300	//write all pots

	if(gain < 1)
		gain = 1;

	if(gain > 256)
		gain = 256;

	int code = ((gain-1)*256)/gain;

	Transmit16Bits(CMD_CODE | code);
}

/*******************************************
 * set potentiometer
 *
 * resistanceCode: 0 to 255
 * 255 is close to 10 k ohm
 *******************************************/
void MCP41010::SetPotentiometer(unsigned char resistanceCode)
{
	Transmit16Bits(CMD_CODE | resistanceCode);
}

/*******************************************
 * set clock line high
 *
 * pin B4
 *******************************************/
void MCP41010::ClockHigh()
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
}
/*******************************************
 * set clock line low
 *
 * pin B4
 *******************************************/
void MCP41010::ClockLow()
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
}
/*******************************************
 * set data line high
 *
 * pin B5
 *******************************************/
void MCP41010::DataHigh()
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
}
/*******************************************
 * set data line low
 *
 * pin B5
 *******************************************/
void MCP41010::DataLow()
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
}
/*******************************************
 * set CS high
 *
 * pin B6
 *******************************************/
void MCP41010::CsHigh()
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
}
/*******************************************
 * set CS low
 *
 * pin B6
 *******************************************/
void MCP41010::CsLow()
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
}
/*******************************************
 * read 1 bit data
 *
 *******************************************/
int  MCP41010::DataIn()
{
	return 0; //MCP41xxx does not send data
}
