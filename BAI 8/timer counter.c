#include<16f887.h>
#fuses hs
#use delay(clock=20M)

#define lcd_rs pin_c5
#define lcd_rw pin_c6
#define lcd_e pin_c7
#define output_lcd   output_d

#include<tv_lcd.c>
#bit T1IF =  0x0c.0
unsigned int8 kq =0,bdn=0, gio =23, phut =59, giay =55, bdn1=0,tt=0;
void demsp()
{
   kq = get_timer0();
   if(kq>24) set_timer0(1);
   lcd_command(0xc0);
   printf(lcd_data, "SO LUONG SP: %u ", kq);
}
void nutnhan()
{
   if(input(pin_e0) == 0){
      delay_ms(20);
      if(input(pin_e0)==0){
         tt++;
         if(tt>5) tt=1;
         while(input(pin_e0)==0);
      }
   }
   lcd_command(0xd4);
   printf(lcd_data,"TAN SO: %u Hz", tt);
}
void demdongho()
{
   if(T1IF == 1)
   {
      set_timer1(15536);
      T1IF =0;
      bdn++;
      bdn1++;
      if(tt==1)
      {
         if(bdn1>=50){
            output_toggle(pin_b0);
            bdn1 =0;
         }
      }
      if(tt==2)
      {
         if(bdn1>=25) 
         {
            output_toggle(pin_b0);
            bdn1 =0;
         }
      }
      if(tt==3)
      {
         if(bdn1>=17) 
         {
            output_toggle(pin_b0);
            bdn1 =0;
         }
      }
      if(tt==4)
      {
         if(bdn1>=13) 
         {
            output_toggle(pin_b0);
            bdn1 =0;
         }
      }
      if(tt==5)
      {
         if(bdn1>=10) 
         {
            output_toggle(pin_b0);
            bdn1 =0;
         }
      }
      if(bdn == 100) 
      {
         bdn =0;
         giay++;
         if(giay>59)
         {
            giay =0;
            phut++;
            if(phut>59)
            {
               phut =0;
               gio++;
               if(gio>23) gio = 0;
            }
         }
      }
   }
   lcd_command(0x94);
   printf(lcd_data, "THOI GIAN: %02u:%02u:%02u", gio, phut, giay);
}
void main()
{
   set_tris_c(0);
   set_tris_d(0);
   set_tris_a(0x10); //A4 input
   set_tris_e(0xff);
   set_tris_b(0);
   setup_timer_0(t0_ext_h_to_l|t0_div_1);
   set_timer0(0);
   setup_timer_1(t1_internal|t1_div_by_1);
   set_timer1(15536);
   lcd_setup();
   lcd_command(0x80);
   lcd_data("HO TEN: VU TIEN PHAT");
   lcd_command(0xc0);
   printf(lcd_data, "SO LUONG SP: %u", kq);
   while(true)
   {
      nutnhan();
      demsp();
      demdongho();
   }
}
