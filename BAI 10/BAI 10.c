#include<16f887.h>
#device adc = 10
#fuses hs
#use delay(clock=20M)

#define lcd_rs       pin_c5
#define lcd_rw       pin_c6
#define lcd_e        pin_c7
#define output_lcd   output_d

#include<tv_lcd.c>
unsigned int8 kq,bdn1,giay1=0,phut1=0,gio1=0;
unsigned int8 bdn2,giay2=0,phut2=0,gio2=0;
unsigned int16 kqadc1,kqadc2;
void demsp(){
   kq=get_timer0();
   if(kq>12) set_timer0(1);
   lcd_command(0x80);
   printf(lcd_data,"SO SP: %02u CAI",kq);
}
void demtimer1()
{
   if(bdn1==10){
      giay1++;
      bdn1=0;
      if(giay1>59){
         giay1=0;
         phut1++;
         if(phut1>59){
            phut1=0;
            gio1++;
            if(gio1>23)gio1=0;
         }
      }
   }
   lcd_command(0xc0);
   printf(lcd_data,"THOI GIAN: %02u:%02u:%02u",gio1,phut1,giay1);
}
void demtimer2()
{
   if(bdn2>=200){
      giay2++;
      bdn2=bdn2-200;
      if(giay2>59){
         giay2=0;
         phut2++;
         if(phut2>59){
            phut2=0;
            gio2++;
            if(gio2>23)gio2=0;
         }
      }
   }
   lcd_command(0x94);
   printf(lcd_data,"THOI GIAN: %02u:%02u:%02u",gio2,phut2,giay2);
}
void lm35()
{
   set_adc_channel(5);
   delay_ms(1);
   read_adc(ADC_START_ONLY);
   lcd_command(0xd4);
   printf(lcd_data,"%02lu C",kqadc1);
   lcd_command(0xd4+2);
   lcd_data(0xdf);
   set_adc_channel(6);
   delay_ms(1);
   read_adc(ADC_START_ONLY);
   lcd_command(0xd4+16);
   printf(lcd_data,"%02lu C",kqadc2);
   lcd_command(0xd4+18);
   lcd_data(0xdf);
}
void main()
{  
   set_tris_a(0xff);
   set_tris_c(0);
   set_tris_d(0);
   set_tris_e(0xff);
   lcd_setup();
   setup_timer_0(T0_EXT_H_TO_L);
   set_timer0(0);
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_8);
   set_timer1(3036);
   enable_interrupts(INT_TIMER1);
   setup_timer_2(T2_DIV_BY_16,98,16);
   set_timer2(0);
   enable_interrupts(INT_TIMER2);
   setup_adc(ADC_CLOCK_DIV_32);
   setup_adc_ports(san5|san6|vss_vdd);
   enable_interrupts(INT_AD);
   enable_interrupts(GLOBAL);
   while(true)
   {
      demsp();
      demtimer1();
      demtimer2();
      lm35();
   }
}
#INT_TIMER1
void ngattimer1(){
   set_timer1(3036);
   bdn1++;
}
#INT_TIMER2
void ngattimer2(){
   bdn2++;
}
#INT_AD
void ngatadc()
{
   kqadc1=read_adc(ADC_READ_ONLY)/2.046;
   kqadc2=read_adc(ADC_READ_ONLY)/2.046;
}
