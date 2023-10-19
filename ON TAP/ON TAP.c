#include<16f887.h>
#fuses intrc_io
#use delay(clock=8M)

#define lcd_rs pin_c5
#define lcd_rw pin_c6
#define lcd_e pin_c7
#define output_lcd output_b
#include<tv_lcd.c>

signed int8 i;
unsigned int8 tt=1;
unsigned int32 y, speed = 100;

const unsigned int8 ma7doan[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};

void sangdan(unsigned int16 speed)
{
   for(i=12;i>=0;i--)
   {
      y=0xfff>>i;
      output_a(y);
      output_c(y>>8);
      delay_ms(speed);
      if(input(pin_e0)==0||input(pin_e1)==0||input(pin_e2)==0) break;
   }
}
void tatdan(unsigned int16 speed)
{
   for(i=12;i>=0;i--)
   {
      y=~(0xfff>>i);
      output_a(y);
      output_c(y>>8);
      delay_ms(speed);
      if(input(pin_e0)==0||input(pin_e1)==0||input(pin_e2)==0) break;
   }
   
}
void sangdich(unsigned int16 speed)
{
   for(i=12;i>=0;i--)
   {
      y=0x800>>i;
      output_a(y);
      output_c(y>>8);
      delay_ms(speed);
      if(input(pin_e0)==0||input(pin_e1)==0||input(pin_e2)==0) break;
   }
}
void tatdich(unsigned int16 speed)
{
   for(i=12;i>=0;i--)
   {
      y=~(0x800>>i);
      output_a(y);
      output_c(y>>8);
      delay_ms(speed);
      if(input(pin_e0)==0||input(pin_e1)==0||input(pin_e2)==0) break;
   }
}

void hienthi()
{  
   lcd_setup();
   lcd_command(0x80+1);
   lcd_data("Sang Dan 12 LED");
   lcd_command(0xc0+1);
   lcd_data("Tat Dan 12 LED");
   lcd_command(0x94+1);
   lcd_data("Sang Dich 12 LED");
   lcd_command(0xd4+1);
   lcd_data("Tat Dich 12 LED");
   if(tt == 1)
   {
      lcd_command(0x80);
      lcd_data(0x7e);
   }
   if(tt == 2)
   {
      lcd_command(0xc0);
      lcd_data(0x7e);
   }
   if(tt == 3)
   {
      lcd_command(0x94);
      lcd_data(0x7e);
   }
   if(tt == 4)
   {
      lcd_command(0xd4);
      lcd_data(0x7e);
   }
}

void nutnhan()
{
   if(input(pin_e0) == 0)
   {
      delay_ms(20);
      if(input(pin_e0)==0)
      {
         tt++;
         if(tt>4) tt = 1;
         hienthi();
         while(input(pin_e0)==0);
      }
   }
   if(input(pin_e1) == 0)
   {
      delay_ms(20);
      if(input(pin_e1)==0)
      {
         tt--;
         if(tt<1) tt = 4;
         hienthi();
         while(input(pin_e1)==0);
      }
   }
   if(input(pin_e2) == 0)
   {
      delay_ms(20);
      if(input(pin_e2)==0)
      {
         speed+=100;
         if(speed>900) speed = 100;
         output_d(ma7doan[speed/100%10]);
         while(input(pin_e2)==0);
      }
   }
}
void main()
{
   set_tris_a(0);
   set_tris_c(0);
   set_tris_b(0);
   set_tris_d(0);
   set_tris_e(0xff);
   output_a(0);
   output_c(0);
   lcd_setup();
   lcd_command(0x80);
   lcd_data(0x7e);
   lcd_command(0x80+1);
   lcd_data("Sang Dan 12 LED");
   lcd_command(0xc0+1);
   lcd_data("Tat Dan 12 LED");
   lcd_command(0x94+1);
   lcd_data("Sang Dich 12 LED");
   lcd_command(0xd4+1);
   lcd_data("Tat Dich 12 LED");
   output_d(ma7doan[speed/100%10]);
   while(true)
   {
      nutnhan();
      if(tt == 1) sangdan(1000-speed);
      if(tt == 2) tatdan(1000-speed);
      if(tt == 3) sangdich(1000-speed);
      if(tt == 4) tatdich(1000-speed);
   }
}
