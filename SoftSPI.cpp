/*
 * SoftSPI.cpp
 *
 *  Created on: Dec 30, 2024
 *      Author: Per
 *
 *  Purpose: base class for SPI via GPIO
 */

#include "SoftSPI.h"

#define CLK_IDLE    if(m_polarity) 		\
				 	{ 					\
						ClockHigh(); 	\
					}					\
					else 				\
					{ 					\
						ClockLow(); 	\
					}

#define CLK_ACTIVE  if(!m_polarity) 	\
				 	{ 					\
						ClockHigh(); 	\
					}					\
					else 				\
					{ 					\
						ClockLow(); 	\
					}

#define DATA_OUT	if(bit)			 	\
						DataHigh();		\
					else				\
						DataLow();

/*******************************************
 * constructor
 *
 *******************************************/
SoftSPI::SoftSPI(int polarity, int phase): m_polarity(polarity), m_phase(phase),m_init(false)
{
}

/*******************************************
 * destructor
 *
 *******************************************/
SoftSPI::~SoftSPI()
{
}

/*******************************************
 * init
 *
 *******************************************/
void SoftSPI::Init(void)
{
	CsHigh();

	CLK_IDLE;

	m_init=true;
}

/*******************************************
 * Transmit one bit
 *
 * word: data to send
 *
 * returns data received
 *******************************************/
int SoftSPI::TransmitBit(int bit)
{
	int result=0;

	if(m_phase)
	{
		CLK_ACTIVE;
		DATA_OUT;
		CLK_IDLE;
		result = DataIn();
	}
	else
	{
		DATA_OUT;
		CLK_ACTIVE;
		result = DataIn();
		CLK_IDLE;
	}

	return result;
}
/*******************************************
 * Transmit 16 Bits
 *
 * word: data to send
 *
 * returns data received
 *******************************************/
unsigned int SoftSPI::Transmit16Bits(unsigned int word)
{
	unsigned int result=0;

	if(!m_init)
		Init();

	CsLow();


	for(int i=0; i<16; i++)
	{
		//msb first
		int bit = (word >> (15-i)) & 1;
		bit = TransmitBit(bit);
		result |= (bit << (15-i));
	}

	CsHigh();

	return result;
}
