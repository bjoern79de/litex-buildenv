#include <stdlib.h>

#include <generated/csr.h>
#include <generated/mem.h>
#include <system.h>
#include <time.h>

#include "pattern.h"
#include "processor.h"
#include "stdio_wrap.h"
#include "uptime.h"
#include "version_data.h"

unsigned int pattern_framebuffer_base(void) {
	return FRAMEBUFFER_BASE_PATTERN;
}

#ifdef MAIN_RAM_BASE
static const unsigned int color_bar[8] = {
	YCBCR422_WHITE,
	YCBCR422_YELLOW,
	YCBCR422_CYAN,
	YCBCR422_GREEN,
	YCBCR422_PURPLE,
	YCBCR422_RED,
	YCBCR422_BLUE,
	YCBCR422_BLACK
};
#endif

#ifdef MAIN_RAM_BASE
static const unsigned char font5x7[] = {
	0x00, 0x00, 0x00, 0x00, 0x00,// (space)
	0x00, 0x00, 0x5F, 0x00, 0x00,// !
	0x00, 0x07, 0x00, 0x07, 0x00,// "
	0x14, 0x7F, 0x14, 0x7F, 0x14,// #
	0x24, 0x2A, 0x7F, 0x2A, 0x12,// $
	0x23, 0x13, 0x08, 0x64, 0x62,// %
	0x36, 0x49, 0x55, 0x22, 0x50,// &
	0x00, 0x05, 0x03, 0x00, 0x00,// '
	0x00, 0x1C, 0x22, 0x41, 0x00,// (
	0x00, 0x41, 0x22, 0x1C, 0x00,// )
	0x08, 0x2A, 0x1C, 0x2A, 0x08,// *
	0x08, 0x08, 0x3E, 0x08, 0x08,// +
	0x00, 0x50, 0x30, 0x00, 0x00,// ,
	0x08, 0x08, 0x08, 0x08, 0x08,// -
	0x00, 0x60, 0x60, 0x00, 0x00,// .
	0x20, 0x10, 0x08, 0x04, 0x02,// /
	0x3E, 0x51, 0x49, 0x45, 0x3E,// 0
	0x00, 0x42, 0x7F, 0x40, 0x00,// 1
	0x42, 0x61, 0x51, 0x49, 0x46,// 2
	0x21, 0x41, 0x45, 0x4B, 0x31,// 3
	0x18, 0x14, 0x12, 0x7F, 0x10,// 4
	0x27, 0x45, 0x45, 0x45, 0x39,// 5
	0x3C, 0x4A, 0x49, 0x49, 0x30,// 6
	0x01, 0x71, 0x09, 0x05, 0x03,// 7
	0x36, 0x49, 0x49, 0x49, 0x36,// 8
	0x06, 0x49, 0x49, 0x29, 0x1E,// 9
	0x00, 0x36, 0x36, 0x00, 0x00,// :
	0x00, 0x56, 0x36, 0x00, 0x00,// ;
	0x00, 0x08, 0x14, 0x22, 0x41,// <
	0x14, 0x14, 0x14, 0x14, 0x14,// =
	0x41, 0x22, 0x14, 0x08, 0x00,// >
	0x02, 0x01, 0x51, 0x09, 0x06,// ?
	0x32, 0x49, 0x79, 0x41, 0x3E,// @
	0x7E, 0x11, 0x11, 0x11, 0x7E,// A
	0x7F, 0x49, 0x49, 0x49, 0x36,// B
	0x3E, 0x41, 0x41, 0x41, 0x22,// C
	0x7F, 0x41, 0x41, 0x22, 0x1C,// D
	0x7F, 0x49, 0x49, 0x49, 0x41,// E
	0x7F, 0x09, 0x09, 0x01, 0x01,// F
	0x3E, 0x41, 0x41, 0x51, 0x32,// G
	0x7F, 0x08, 0x08, 0x08, 0x7F,// H
	0x00, 0x41, 0x7F, 0x41, 0x00,// I
	0x20, 0x40, 0x41, 0x3F, 0x01,// J
	0x7F, 0x08, 0x14, 0x22, 0x41,// K
	0x7F, 0x40, 0x40, 0x40, 0x40,// L
	0x7F, 0x02, 0x04, 0x02, 0x7F,// M
	0x7F, 0x04, 0x08, 0x10, 0x7F,// N
	0x3E, 0x41, 0x41, 0x41, 0x3E,// O
	0x7F, 0x09, 0x09, 0x09, 0x06,// P
	0x3E, 0x41, 0x51, 0x21, 0x5E,// Q
	0x7F, 0x09, 0x19, 0x29, 0x46,// R
	0x46, 0x49, 0x49, 0x49, 0x31,// S
	0x01, 0x01, 0x7F, 0x01, 0x01,// T
	0x3F, 0x40, 0x40, 0x40, 0x3F,// U
	0x1F, 0x20, 0x40, 0x20, 0x1F,// V
	0x7F, 0x20, 0x18, 0x20, 0x7F,// W
	0x63, 0x14, 0x08, 0x14, 0x63,// X
	0x03, 0x04, 0x78, 0x04, 0x03,// Y
	0x61, 0x51, 0x49, 0x45, 0x43,// Z
	0x00, 0x00, 0x7F, 0x41, 0x41,// [
	0x02, 0x04, 0x08, 0x10, 0x20,// "\"
	0x41, 0x41, 0x7F, 0x00, 0x00,// ]
	0x04, 0x02, 0x01, 0x02, 0x04,// ^
	0x40, 0x40, 0x40, 0x40, 0x40,// _
	0x00, 0x01, 0x02, 0x04, 0x00,// `
	0x20, 0x54, 0x54, 0x54, 0x78,// a
	0x7F, 0x48, 0x44, 0x44, 0x38,// b
	0x38, 0x44, 0x44, 0x44, 0x20,// c
	0x38, 0x44, 0x44, 0x48, 0x7F,// d
	0x38, 0x54, 0x54, 0x54, 0x18,// e
	0x08, 0x7E, 0x09, 0x01, 0x02,// f
	0x08, 0x14, 0x54, 0x54, 0x3C,// g
	0x7F, 0x08, 0x04, 0x04, 0x78,// h
	0x00, 0x44, 0x7D, 0x40, 0x00,// i
	0x20, 0x40, 0x44, 0x3D, 0x00,// j
	0x00, 0x7F, 0x10, 0x28, 0x44,// k
	0x00, 0x41, 0x7F, 0x40, 0x00,// l
	0x7C, 0x04, 0x18, 0x04, 0x78,// m
	0x7C, 0x08, 0x04, 0x04, 0x78,// n
	0x38, 0x44, 0x44, 0x44, 0x38,// o
	0x7C, 0x14, 0x14, 0x14, 0x08,// p
	0x08, 0x14, 0x14, 0x18, 0x7C,// q
	0x7C, 0x08, 0x04, 0x04, 0x08,// r
	0x48, 0x54, 0x54, 0x54, 0x20,// s
	0x04, 0x3F, 0x44, 0x40, 0x20,// t
	0x3C, 0x40, 0x40, 0x20, 0x7C,// u
	0x1C, 0x20, 0x40, 0x20, 0x1C,// v
	0x3C, 0x40, 0x30, 0x40, 0x3C,// w
	0x44, 0x28, 0x10, 0x28, 0x44,// x
	0x0C, 0x50, 0x50, 0x50, 0x3C,// y
	0x44, 0x64, 0x54, 0x4C, 0x44,// z
	0x00, 0x08, 0x36, 0x41, 0x00,// {
	0x00, 0x00, 0x7F, 0x00, 0x00,// |
	0x00, 0x41, 0x36, 0x08, 0x00,// }
	0x08, 0x08, 0x2A, 0x1C, 0x08,// ->
	0x08, 0x1C, 0x2A, 0x08, 0x08 // <-
};
#endif

static int inc_color(int color) {
	color++;
	return color%8;
}

static void pattern_draw_text_color(int x, int y, char *ptr, long background_color, long text_color) {
#ifdef MAIN_RAM_BASE
	int i, j, k;
	int adr;
	volatile unsigned int *framebuffer = (unsigned int *)(MAIN_RAM_BASE + pattern_framebuffer_base());
	for(i=0; ptr[i] != '\0'; i++) {
		for(j=-1; j<8; j++) {
			for(k=-1; k<6; k++) {
				adr = 6*(x + i) + k + (2*9*y + 2*j)*processor_h_active/2;
				if (k >= 0 && k < 5 && j >= 0 && j < 7 && ((font5x7[5*(ptr[i] - ' ') + k] >> j) & 0x1)) {
					framebuffer[adr + 0*processor_h_active/2] = text_color;
					framebuffer[adr + 1*processor_h_active/2] = text_color;
				} else {
					framebuffer[adr + 0*processor_h_active/2] = background_color;
					framebuffer[adr + 1*processor_h_active/2] = background_color;
				}
			}
		}
	}
/* FIXME: Framebuffer Should not even be compiled if no MAIN RAM */
#endif
}

static void pattern_draw_text(int x, int y, char *ptr) {
	pattern_draw_text_color(x, y, ptr, YCBCR422_WHITE, YCBCR422_BLACK);
}

void pattern_next(void) {
	pattern++;
	pattern = pattern % PATTERN_MAX;
	pattern_fill_framebuffer(processor_h_active, processor_v_active);
}


void pattern_fill_framebuffer(int h_active, int w_active)
{
#ifdef MAIN_RAM_BASE
	int i, j;
	int color;
#ifdef CONFIG_L2_SIZE
	flush_l2_cache();
#endif
	color = -1;
	volatile unsigned int *framebuffer = (unsigned int *)(MAIN_RAM_BASE + pattern_framebuffer_base());
	if(pattern == PATTERN_COLOR_BARS) {
		/* color bar pattern */
		for(i=0; i<h_active*w_active*2/4; i++) {
			if(i%(h_active/16) == 0)
				color = inc_color(color);
			if(color >= 0)
				framebuffer[i] = color_bar[color];
		}
	} else {
		/* vertical black white lines */
		for(i=0; i<h_active*w_active*2/4; i++) {
			if(i%(h_active/16) == 0)
				color = inc_color(color);
			if(color >= 0)
				framebuffer[i] = 0x801080ff;
		}
	}

	// draw a border around that.
	for (i=0; i<h_active*2; i++) {
		framebuffer[i] = YCBCR422_WHITE;
	}

	for (i=(w_active-4)*h_active*2/4; i<h_active*w_active*2/4; i++) {
		framebuffer[i] = YCBCR422_WHITE;
	}

	for (i=0; i<w_active*2; i++) {
		// do the left bar
		for (j=0; j<2; j++) {
			framebuffer[(i*h_active)+j] = YCBCR422_WHITE;
			framebuffer[(i*h_active)+j + (1*h_active/2)] = YCBCR422_WHITE;
		}

		// do the right bar
		for (j=h_active-2; j<h_active; j++) {
			framebuffer[(i*h_active)+j] = YCBCR422_WHITE;
			framebuffer[(i*h_active)+j + (1*h_active/2)] = YCBCR422_WHITE;
		}
	}

	// Line 1 - uptime + version information
	int line = 1;
	pattern_draw_text(19, line, (char*)git_describe);
	line++;
	// Line 2 - build time data
	pattern_draw_text(1, line, "Built: "__DATE__" "__TIME__);
	line++;
	// Line 3- running on
	pattern_draw_text(1, line, "Running on ");
	pattern_draw_text(12, line, (char*)board);
	line++;

	// Line 4 - empty
	line++;

#ifndef HIDE_ADVERT
	// Line 5 - Hi!
	pattern_draw_text(1, line, "Hi! I am HDMI2USB ");
	line++;
	// Line 6+7 - Want...
	pattern_draw_text_color(1, line, "Want to hack on FOSS video capture systems?", YCBCR422_BLUE, YCBCR422_WHITE);
	line++;
	pattern_draw_text_color(1, line, "Get in touch with us! #timvideos on Freenode IRC", YCBCR422_RED, YCBCR422_WHITE);
	line++;
	// Line 8 - URLs..
	pattern_draw_text(1, line, "code.timvideos.us / enjoy-digital.fr");
	pattern_draw_text_color(6, line, "tim", YCBCR422_WHITE, YCBCR422_RED);
	pattern_draw_text_color(9, line, "videos", YCBCR422_WHITE, YCBCR422_BLUE);
	pattern_draw_text_color(27, line, "digital", YCBCR422_WHITE, YCBCR422_CYAN);
#endif

#ifdef CONFIG_L2_SIZE
	flush_l2_cache();
#endif
/* FIXME: Framebuffer Should not even be compiled if no MAIN RAM */
#endif
}

void pattern_service(void)
{
#ifdef MAIN_RAM_BASE
	static int last_event;
	static char buffer[16];

	if(elapsed(&last_event, CONFIG_CLOCK_FREQUENCY)) {
		sprintf(buffer, "Uptime: %s", uptime_str());
		pattern_draw_text(1, 1, buffer);
	}
#ifdef CONFIG_L2_SIZE
	flush_l2_cache();
#endif
/* FIXME: Framebuffer Should not even be compiled if no MAIN RAM */
#endif
}
