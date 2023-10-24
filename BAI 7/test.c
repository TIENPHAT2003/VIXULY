#include<16f887.h>
#fuses hs
#use delay(clock=20M)

#define lcd_rs pin_c5
#define lcd_rw pin_c6
#define lcd_e  pin_c7
#define output_lcd output_d
#include<tv_lcd.c>

void main()
{  
   set_tris_c(0);
   set_tris_d(0);
   lcd_setup();
   lcd_command(0x80);
   lcd_data("CHUC BAN CO MOT NGAY");
   lcd_command(0xc0+8);
   lcd_data("20/10");
   lcd_command(0x94+1);
   lcd_data("VUI VE VA HANH PHUC");
   lcd_command(0xd4);
   while(true)
   {
   
   }
}
