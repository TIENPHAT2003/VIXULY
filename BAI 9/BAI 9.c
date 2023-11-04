#include<16f887.h>
//!#device adc=10
#fuses hs
#use delay(clock=20M)
#define lcd_rs pin_c5
#define lcd_rw pin_c6
#define lcd_e  pin_c7
#define output_lcd   output_d
#include<tv_lcd.c>

#bit t0if = 0x0b.2
unsigned int1 ttdem=0;
unsigned int8 kq,bdn,giay=0,phut=0,gio=0;
unsigned int16 kqadc1, kqadc2;
void demsp(){
   kq = get_timer1();
   if(kq>24) set_timer1(1);
   lcd_command(0x80);
   printf(lcd_data,"SO SAN PHAM: %02u CAI", kq);
}
void demdongho()
{
   if(t0if==1){
      set_timer0(5.6);
      t0if=0;
      bdn++;
      if(bdn==78){
         bdn=0;
         giay++;
         if(giay>59){
            giay=0;
            phut++;
            if(phut>59){
               phut=0;
               gio++;
               if(gio>23) gio=0;
            }
         }
      }
   }
   lcd_command(0xc0);
   printf(lcd_data,"THOI GIAN: %02u:%02u:%02u", gio, phut, giay);
}
void lm35()
{
   set_adc_channel(6);
   delay_ms(1);
//!   kqadc1=read_adc()*0.489; // 10 bit tham chieu noi
   kqadc1=read_adc()/2.55; // 8 bit tham chieu ngoai
   set_adc_channel(7);
   delay_ms(1);
//!   kqadc2=read_adc()*0.489; // 10 bit tham chieu noi
   kqadc2=read_adc()/2.55; // 8 bit tham chieu ngoai
   lcd_command(0x94);
   printf(lcd_data,"%02lu C",kqadc1);
   lcd_command(0x94+2);
   lcd_data(0xdf);
   lcd_command(0x94+16);
   printf(lcd_data,"%02lu C",kqadc2);
   lcd_command(0x94+18);
   lcd_data(0xdf);
}
void main(){
   set_tris_a(0xff);  
   set_tris_c(0x01);
   set_tris_d(0);
   set_tris_e(0xff);
   lcd_setup();
   setup_timer_1(t1_disabled);
   set_timer1(0);
   setup_timer_0(t0_internal|t0_div_256);
   set_timer0(5.6);
   lcd_command(0xD4);
   lcd_data("DANG DUNG");
   setup_adc(adc_clock_div_32);
//!   setup_adc_ports(san6|san7|vss_vdd);
   setup_adc_ports(san6|san7|vref_vref);
   while(true)
   {  
      demsp();
      demdongho();
      lm35();
      if(input(pin_e0)==0) {
         delay_ms(20);
         if(input(pin_e0)==0){
            ttdem=!ttdem;
            if(ttdem==1){
               lcd_command(0xD4);
               lcd_data("DANG CHAY");
               setup_timer_1(t1_external|t1_div_by_1);
            }
            else {
               setup_timer_1(t1_disabled);
               lcd_command(0xD4);
               lcd_data("DANG DUNG");
            }
         }
      }
   }
}
