#include<16f887.h>
#device adc = 10
#fuses hs
#use delay(clock=20M)
#USE RS232(baud =9600,xmit = pin_c6, rcv = pin_c7)
#define lcd_rs          pin_b5
#define lcd_rw          pin_b6
#define lcd_e           pin_b7
#define output_lcd      output_d
#include<tv_lcd.c>
unsigned int8 kq,nhan;
unsigned int16 kqadc,nhanadc;

void demsp()
{
   kq=get_timer1();
   if(kq>24) set_timer1(1);
   putc(kq);
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
      printf(lcd_data,"DEM SP: %02u CAI", nhan);
      lcd_command(0xc0);
      printf(lcd_data,"NHIET DO: %02lu C",nhanadc);
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
   setup_adc(ADC_CLOCK_DIV_32);
   setup_adc_ports(san4|vss_vdd);
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);
   while(true)
   {  
      demsp();
      lm35();
      
      
      hienthi();
   }
}
#INT_RDA
void ngatuart()
{
   nhan=getc();
   nhanadc = getc();

}
