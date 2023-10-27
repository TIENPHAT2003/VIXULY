#include<16f887.h>
#fuses intrc_io
#use delay(clock=8M)

#define lcd_rs pin_c5
#define lcd_rw pin_c6
#define lcd_e  pin_c7
#define output_lcd   output_d
#define mode   pin_e0
#include<tv_lcd.c>
#bit t1if = 0x0c.0
unsigned int32 y;
unsigned int8 ttdem=0, kq=0,bdn=0;
unsigned int8 gio=0,phut=0,giay=0;
void hienthi()
{
   lcd_setup();
   lcd_command(0x80);
   lcd_data("MSSV: 21151309");
}
void sangled(unsigned int8 led)
{
      y=~(0xffff<<led);
      output_a(y);
      output_b(y>>8);
}
void demsp()
{
   if(ttdem==0){
      kq=get_timer1();
      if(kq>16) set_timer1(1);
      lcd_command(0xc0);
      printf(lcd_data,"SP: %02u CAI",kq);
      sangled(kq);
   }
}
void donghoso()
{
   if(ttdem==1){
      if(t1if==1){
         set_timer1(15536);
         bdn++;
         t1if=0;
         if(bdn==10){
            bdn=0;
            giay++;
            if(giay>59){
               giay=0;
               phut++;
               if(phut>59){
                  phut=0;
                  gio++;
                  if(gio>23)gio=0;
               }
            }
         }
      }
      lcd_command(0xc0);
      printf(lcd_data,"%02u - %02u - %02u",gio,phut,giay);
   }
}
void main()
{
   set_tris_a(0);
   set_tris_b(0);
   set_tris_c(0x01); // 0000 0001 
   set_tris_d(0);
   set_tris_e(0xff);
   output_a(0);
   output_b(0);
   hienthi();
   setup_timer_1(t1_external|t1_div_by_1);
   set_timer1(0);
   while(true) 
   {
      if(input(mode)==0)
      {
         delay_ms(20);
         if(input(mode)==0)
         {
            ttdem=!ttdem;
            if(ttdem==1){
               hienthi();
               setup_timer_1(t1_internal|t1_div_by_4);
               set_timer1(15536);
               hienthi();
            }
            else{
               hienthi();
               setup_timer_1(t1_disabled);
               setup_timer_1(t1_external|t1_div_by_1);
               set_timer1(0);     
            }
            while(input(mode)==0);
         }
      }
      demsp();
      donghoso();
   }
}
