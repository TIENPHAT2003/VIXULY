#include<16f887.h>
#device adc = 10
#fuses hs
#use delay(clock=20M)
#USE RS232(baud =9600,xmit = pin_c6, rcv = pin_c7)
unsigned int8 kqsp,nhansp,i=0,nhantt;
unsigned int16 kqadc,nhanadc,duty=0;
#define lcd_rs          pin_b0
#define lcd_rw          pin_b1
#define lcd_e           pin_b2
#define output_lcd      output_d
#include<tv_lcd.c>
void demsp()
{
   kqsp=get_timer1();
   if(kqsp>24) set_timer1(1);
   putc(kqsp);
}
void lm35()
{
   set_adc_channel(4);
   delay_ms(1);
   kqadc=read_adc()*0.489;
   putc(kqadc);
}
void hienthi()
{
   lcd_command(0x80);
   printf(lcd_data,"DEM SP: %02u CAI", nhansp);
   lcd_command(0xc0);
   printf(lcd_data,"NHIET DO: %02lu C", nhanadc);
   lcd_command(0xc0+12);
   lcd_data(0xdf);
}
void main()
{
   set_tris_a(0xff);
   set_tris_b(0);
   set_tris_c(0x81);
   set_tris_d(0);
   lcd_setup();
   setup_timer_1(T1_EXTERNAL|T1_DIV_BY_1);
   set_timer1(0);
   setup_timer_2(T2_DIV_BY_16,249,1);
   setup_ccp1(CCP_PWM);
   output_low(pin_c1);
   set_pwm1_duty(duty);
   setup_adc(ADC_CLOCK_DIV_32);
   setup_adc_ports(SAN4|VSS_VDD);
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);
   while(true)
   {
      demsp();
      lm35();
      hienthi();
      if(nhanadc<=50) duty = 200;
      if(nhanadc>50 && nhanadc<=100) duty = 750;
      if(nhanadc>100) duty = 1000;
      if(nhantt==1) set_pwm1_duty(duty); 
      else set_pwm1_duty((int16)0);
   }
}
#INT_RDA
void ngatuart()
{
   if(i==0) nhansp=getc();
   if(i==1) nhanadc=getc();
   if(i==2) nhantt=getc();
   i++;
   if(i>2)i=0;
}
