#include "LCD.h"

namespace unit
{
	/* LCDフォントサイズ */
#define CALIB_FONT (EV3_FONT_SMALL)
#define CALIB_FONT_WIDTH (6/*TODO: magic number*/)
#define CALIB_FONT_HEIGHT (8/*TODO: magic number*/)
	
	void LCD::display(char str[])
	{
		ev3_lcd_fill_rect(0, 0, EV3_LCD_WIDTH, EV3_LCD_HEIGHT, EV3_LCD_WHITE);
		ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT*1);
	}
}  // namespace unit
