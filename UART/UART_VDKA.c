#include<16f887.h>
#device adc = 10
#fuses hs
#use delay(clock=20M)
#USE RS232(baud =9600,xmit = pin_c6, rcv = pin_c7)
unsigned int1 tt=0;
unsigned int8 kqsp,nhansp,i=0;
unsigned int16 kqadc,nhanadc;
const unsigned int8 ma7doan[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
void demsp()
{
   kqsp=24-get_timer1();
   if(kqsp<1) set_timer1(1);
   putc(kqsp);
}
void lm35()
{
   set_adc_channel(4);
   delay_ms(1);
   kqadc=read_adc()*0.489;
   putc(kqadc);
}
void quetled()
{
      output_d(ma7doan[nhansp/10%10]); output_low(pin_b0); delay_ms(1);output_high(pin_b0);
      output_d(ma7doan[nhansp/1%10]); output_low(pin_b1); delay_ms(1);output_high(pin_b1);
      output_d(ma7doan[nhanadc/10%10]); output_low(pin_b2); delay_ms(1);output_high(pin_b2);
      output_d(ma7doan[nhanadc/1%10]); output_low(pin_b3); delay_ms(1);output_high(pin_b3);
}
void main()
{
   set_tris_a(0xff);
   set_tris_b(0);
   set_tris_c(0x81);
   set_tris_d(0);
   setup_timer_1(T1_EXTERNAL|T1_DIV_BY_1);
   set_timer1(0);
   setup_adc(ADC_CLOCK_DIV_32);
   setup_adc_ports(SAN4|VSS_VDD);
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);
   while(true)
   {
      quetled();
      demsp();
      lm35();
      if(input(pin_e0) == 0)
      {
         delay_ms(20);
         if(input(pin_e0)==0)
         {
            tt=!tt;
            putc(tt);
            while(input(pin_e0)==0);
         }
      }
   }
}
#INT_RDA
void ngatuart()
{
   if(i==0) nhansp=getc();
   if(i==1) nhanadc=getc();
   i++;
   if(i>1)i=0;
}
