
 Programmable Gain Amp with soft SPI

This version was created for MCUs like NUCLEO-C031C6 from ST.
I have used the STM32CubeIDE to generate the driver code.

The programmable resistor MCP41010 code implements the in- and out- functions needed to generate SPI communication. These functions are:
void MCP41010::ClockHigh()
void MCP41010::ClockLow()
void MCP41010::DataHigh()
void MCP41010::DataLow()
void MCP41010::CsHigh()
void MCP41010::CsLow()
int  MCP41010::DataIn()

You will need to modify them to match your hardware.

## functions

/*******************************************
 * constructor
 *
 *******************************************/

MCP41010::MCP41010()

/*******************************************
 * destructor
 *
 *******************************************/

MCP41010::~MCP41010()

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
 *******************************************/

void MCP41010::SetGain(int gain)

/*******************************************
 * set potentiometer
 *
 * resistanceCode: 0 to 255
 * 255 is close to max of the sesistor
 *******************************************/

void MCP41010::SetPotentiometer(unsigned char resistanceCode)


## example usage

#include "mcp41010.h"

	MCP41010 mcp;

  	mcp.SetGain(2);
