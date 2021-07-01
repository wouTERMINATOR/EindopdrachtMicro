/*
 * LCD.h
 *
 * Created: 28-6-2021 19:05:49
 *  Author: woute
 */ 


#ifndef LCD_H_
#define LCD_H_

void lcd_strobe_lcd_e(void);
void init_4bits_mode(void);
void lcd_write_string(char *str);
void lcd_write_data(unsigned char byte);
void lcd_write_cmd(unsigned char byte);
void lcd_clear(void);
void set_cursor(int position);

#endif /* LCD_H_ */