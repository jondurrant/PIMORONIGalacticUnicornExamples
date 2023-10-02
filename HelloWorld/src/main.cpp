/***
 * main.cpp - Simple Hello World
 * With PiMoroni Galactic Unicorn
 * Jon Durrant
 * 24-Sep-2023
 *
 *
 */

#include "pico/stdlib.h"
#include <stdio.h>
#include <cstring>


#include "libraries/pico_graphics/pico_graphics.hpp"
#include "galactic_unicorn.hpp"

using namespace pimoroni;

PicoGraphics_PenRGB888 graphics(53, 11, nullptr);
GalacticUnicorn galactic_unicorn;


std::string hello 			= "Hello";
std::string drjonea 		= "DrJonEA";
std::string world 			= "World";

int main(void) {
	uint32_t now, last = 0;
	bool doStart = true;

	stdio_init_all();
	galactic_unicorn.init();


	for (;;) {
		if (galactic_unicorn.is_pressed(
				galactic_unicorn.SWITCH_BRIGHTNESS_UP)) {
			galactic_unicorn.adjust_brightness(+0.01);
		}
		if (galactic_unicorn.is_pressed(
				galactic_unicorn.SWITCH_BRIGHTNESS_DOWN)) {
			galactic_unicorn.adjust_brightness(-0.01);
		}

		//Flip between two steps every 5Seconds
		now = to_ms_since_boot(get_absolute_time ());
		if((now - last) > 5000){
			graphics.set_pen(0, 0, 0);
			graphics.clear();

			if (doStart){
				graphics.set_pen(0x50, 0x50, 0xff);
				graphics.text(hello, Point(0, -1), -1, 2.0, 0.0);
			} else {
				graphics.set_pen(0xFF, 0x50, 0x50);
				graphics.text(drjonea, Point(2, -1), -1, 1.0, 0.0);
				graphics.set_pen(0x40, 0xFF, 0x50);
				graphics.text(world, Point(2, 5), -1, 1.0, 0.0);

			}



			last = now;
			doStart = !doStart;
		}


		//Update is needed for both new graphics and any change in brightness
		galactic_unicorn.update(&graphics);
		sleep_ms(5);

	}

	return 0;
}
