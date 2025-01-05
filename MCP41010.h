/*
 * MCP41010.h
 *
 *  Created on: Dec 30, 2024
 *      Author: Per
 */

#ifndef MCP41010_H_
#define MCP41010_H_

#include "softspi.h"

class MCP41010 : public SoftSPI
{
public:
	MCP41010();
	virtual ~MCP41010();
	void SetPotentiometer(unsigned char resistanceCode);
	void SetGain(int gain);

private:
	void ClockHigh();
	void ClockLow();
	void DataHigh();
	void DataLow();
	void CsHigh();
	void CsLow();
	int  DataIn();

};

#endif /* MCP41010_H_ */
