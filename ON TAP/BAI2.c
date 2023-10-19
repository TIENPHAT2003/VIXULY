#include<16f887.h>
#fuses intrc_io
#use delay(clock=8M)

#define LCD_ENABLE_PIN  PIN_E2                                    
#define LCD_RS_PIN      PIN_E0                                 
#define LCD_RW_PIN      PIN_E1                                  
#define LCD_DATA4       PIN_C4                                 
#define LCD_DATA5       PIN_c5                                   
#define LCD_DATA6       PIN_c6                                    
#define LCD_DATA7       PIN_c7
#include<tvkey4x4.c>
#include<LCD.c>
const unsigned int8 ma7doan[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
unsigned int8 kq=0, ttdem =1, gio=23,phut=59,giay=59;

void quetled()
{
   output_a(ma7doan[gio/10%10]); output_low(pin_d0); delay_ms(1); output_high(pin_d0);
   output_a(ma7doan[gio/1%10]); output_low(pin_d1); delay_ms(1); output_high(pin_d1);
   output_a(ma7doan[phut/10%10]); output_low(pin_d3); delay_ms(1); output_high(pin_d3);
   output_a(ma7doan[phut/1%10]); output_low(pin_d4); delay_ms(1); output_high(pin_d4);
   output_a(ma7doan[giay/10%10]); output_low(pin_d6); delay_ms(1); output_high(pin_d6);
   output_a(ma7doan[giay/1%10]); output_low(pin_d7); delay_ms(1); output_high(pin_d7);
   output_a(0xbf); output_low(pin_d2); delay_ms(1); output_high(pin_d2);
   output_a(0xbf); output_low(pin_d5); delay_ms(1); output_high(pin_d5);
}
void demsp()
{
   kq=get_timer1();
   if(kq>20) set_timer1(1);
   lcd_gotoxy(1,1);
   printf(lcd_putc,"SAN PHAM: %02u CAI",kq);
   if(input(pin_c3) == 0)
   {
      delay_ms(20);
      if(input(pin_c3) == 0)
      {
         ttdem =! ttdem;
         if(ttdem==1) setup_timer_1(t1_external|t1_div_by_1);
         else setup_timer_1(t1_disabled);
         while(input(pin_c3)==0);
      }
   }
}
void main()
{  
   set_tris_a(0);
   set_tris_b(0xff);
   set_tris_c(0X09);
   set_tris_d(0);
   set_tris_e(0);
   setup_timer_1(t1_external|t1_div_by_1);
   set_timer1(0);
   lcd_init();

   
   while(true)
   {
      demsp();
      quetled();
   }
}

