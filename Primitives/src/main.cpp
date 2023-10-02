/***
 * main.cpp - Drawing Graphic Primitives
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


std::string hello = "Hello";
std::string world = "World";


int main(void) {
	uint32_t now, last = 0;
	int triWidth = GalacticUnicorn::WIDTH /4;
	int count =0;

	stdio_init_all();
	galactic_unicorn.init();

	sleep_ms(2000);
	printf("GO\n");

	for (;;) {
		now = to_ms_since_boot(get_absolute_time ());
		if((now - last) > 5000){
			graphics.set_pen(0, 0, 0);
			graphics.clear();

			//Draw the four Shapes
			for (int i=0; i < 4; i++){

				//Cycle colours
				int cycle = (count + i) % 4;
				switch(cycle){
				case 0:
					graphics.set_pen(0xff, 0xff, 0xff);
					break;
				case 1:
					graphics.set_pen(0xff, 0x00, 0x00);
					break;
				case 2:
					graphics.set_pen(0x00, 0xff, 0x00);
					break;
				case 3:
					graphics.set_pen(0x00, 0x00, 0xff);
					break;
				}

				//Draw selection of shapes
				switch(i){
				case 0:{
					//CIRCLE
					Point centre( triWidth/2, GalacticUnicorn::HEIGHT/2);
					graphics.circle(centre, triWidth/2);
					break;
				}
				case 1:{
					//TRIANGLE
					Point bl(triWidth , GalacticUnicorn::HEIGHT-1 );
					Point br(triWidth *2, GalacticUnicorn::HEIGHT-1 );
					Point tp(triWidth/2+ triWidth, 0);
					graphics.triangle(bl, br, tp);
					break;
				}
				case 2:{
					//RECTANGLE
					Rect r(triWidth * i, 0, triWidth, GalacticUnicorn::HEIGHT-1);
					graphics.rectangle(r);
					break;
				}
				case 3:{
					//LINE
					Point t(GalacticUnicorn::WIDTH -1, 0);
					Point b(t.x - triWidth, GalacticUnicorn::HEIGHT -1);
					graphics.thick_line(t, b, 2);
					break;
				}
				}

			}


			last = now;
			count ++;
			if (count >= 4){
				count = 0;
			}
		}


		//Automatically set brightness of display using Light Sensor
		uint16_t amb = galactic_unicorn.light();

		//Ambient light 30 = 0.30 Brightness
		//Ambient 300 = 1.0 Brightness
		float autoBright = ((float)amb - 30.0)/270 + 0.30;
		if (autoBright > 1.0){
			autoBright = 1.0;
		}
		galactic_unicorn.set_brightness(autoBright);
		galactic_unicorn.update(&graphics);

		sleep_ms(5);
	}

	return 0;
}
