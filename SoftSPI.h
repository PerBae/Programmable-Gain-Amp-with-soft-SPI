/*
 * SoftSPI.h
 *
 *  Created on: Dec 30, 2024
 *      Author: Per
 */

#ifndef SOFTSPI_H_
#define SOFTSPI_H_

class SoftSPI
{
public:
	SoftSPI(int polarity, int phase);
	virtual ~SoftSPI();

	unsigned int Transmit16Bits(unsigned int word);

protected:
	virtual void ClockHigh() = 0;
	virtual void ClockLow() = 0;
	virtual void DataHigh() = 0;
	virtual void DataLow() = 0;
	virtual void CsHigh() = 0;
	virtual void CsLow() = 0;
	virtual int  DataIn() = 0;

private:
	SoftSPI();
	int TransmitBit(int bit);
	void Init(void);

	int m_polarity;
	int m_phase;
	bool m_init;
};

#endif /* SOFTSPI_H_ */
