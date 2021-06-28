/*
 * lcd.h
 *
 * Created: 10-2-2021 15:21:33
 *  Author: woute
 */ 


#ifndef LCD_H_
#define LCD_H_

void init();
void display_text(char *str);
void set_cursor(int position);

#endif /* LCD_H_ */