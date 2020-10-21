/*
 * ChannelData.h
 *
 * Created: 03/02/2020 21:21:20
 *  Author: SelfBiasedCode
 */ 


#ifndef CHANNELDATA_H_
#define CHANNELDATA_H_

struct channelData
{
	uint8_t reg;
	uint8_t pin;
	CRGB highColour;
	CRGB lowColour;
	uint8_t resetWait;
};

#endif /* CHANNELDATA_H_ */