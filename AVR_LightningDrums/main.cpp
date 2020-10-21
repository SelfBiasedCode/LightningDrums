#include <avr/io.h>
#include "../arduino/Arduino.h"
#include "FastLED.h"
#include "LightningConfig.h"
#include "util/delay.h"
#include "ChannelData.h"
#include "avr/sfr_defs.h"
#include "TickCounter.h"

// Static Memory
CRGB leds[CHANNELS];
channelData inputs[CHANNELS];

#if DEBUG
TickCounter::TickCounter<3> tc;
#endif

void setupData()
{
	// explicit configuration goes here
	inputs[0].pin = CHAN0_TRIGGER_PIN;
	inputs[0].reg = CHAN0_TRIGGER_REG;
	inputs[0].lowColour = CHAN0_COLOUR_LOW;
	inputs[0].highColour = CHAN0_COLOUR_HIGH;
	inputs[1].pin = CHAN1_TRIGGER_PIN;
	inputs[1].reg = CHAN1_TRIGGER_REG;
	inputs[1].lowColour = CHAN1_COLOUR_LOW;
	inputs[1].highColour = CHAN1_COLOUR_HIGH;
	inputs[2].pin = CHAN2_TRIGGER_PIN;
	inputs[2].reg = CHAN2_TRIGGER_REG;
	inputs[2].lowColour = CHAN2_COLOUR_LOW;
	inputs[2].highColour = CHAN2_COLOUR_HIGH;
	inputs[3].pin = CHAN3_TRIGGER_PIN;
	inputs[3].reg = CHAN3_TRIGGER_REG;
	inputs[3].lowColour = CHAN3_COLOUR_LOW;
	inputs[3].highColour = CHAN3_COLOUR_HIGH;
	inputs[4].pin = CHAN4_TRIGGER_PIN;
	inputs[4].reg = CHAN4_TRIGGER_REG;
	inputs[4].lowColour = CHAN4_COLOUR_LOW;
	inputs[4].highColour = CHAN4_COLOUR_HIGH;
	inputs[5].pin = CHAN5_TRIGGER_PIN;
	inputs[5].reg = CHAN5_TRIGGER_REG;
	inputs[5].lowColour = CHAN5_COLOUR_LOW;
	inputs[5].highColour = CHAN5_COLOUR_HIGH;

	// initialize all other members
	for (uint8_t chan = 0; chan < CHANNELS; chan++)
	{
		inputs[0].resetWait = 0;
	}
}

void setupLeds()
{
	// turn all LEDs off
	for (uint8_t i = 0; i < CHANNELS; i++)
	{
		leds[i] = 0x0;
	}
	
	// setup controller
	LEDS.addLeds<P9813, LED_DT, LED_CK, RGB>(leds, CHANNELS);
}

inline bool getPinState(uint8_t regAddr, uint8_t pin)
{
	// SFRs have relative addresses
	uint8_t addr = (regAddr) + 0x20;
	uint8_t regData = (*(volatile uint8_t *)(addr));
	bool state = (regData & (1 << pin));
	
	return state;
}

void processActivity()
{
	for (uint8_t chan = 0; chan < CHANNELS; chan++)
	{
		// readability alias
		channelData * channel = &inputs[chan];
		
		// get channel input
		bool inputActive = getPinState(channel->reg, channel->pin);
		
		// check if a colour change is required
		if (inputActive)
		{
			// set output
			leds[chan] = channel->highColour;
			
			// remember to switch later
			channel->resetWait = RESET_WAIT;
		}
		else if (channel->resetWait > 0)
		{
			channel->resetWait--;
		}
		else if (channel->resetWait == 0)
		{
			// reset output
			leds[chan] = channel->lowColour;
		}
	}
}

int main(void)
{
	// DEBUG: indicate reset through wait
	tc.startMetering();
	_delay_ms(500);
	tc.stopMetering();
	
	// initialization
	setupLeds();
	setupData();
	
	// main loop
	while(1)
	{
		tc.startMetering();
		
		// process changes
		processActivity();
		
		tc.stopMetering();
		tc.startMetering();
		
		// output changes
		FastLED.show();
		
		tc.stopMetering();
		
		// wait
		_delay_ms(LOOP_WAIT_MS);
	}
}

