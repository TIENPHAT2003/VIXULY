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
#include<LCD.c>
#include<tvkey4x4.c>
#bit t0if = 0x0b.2
const unsigned int8 ma7doan[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
unsigned int8 gio=0,phut=0, giay=55;
unsigned int8 bdn,kq=0,mp,dem,flag=0;
unsigned int8 ttdem=0, gioihan=20,tong=0, ns=0;

void matranphim()
{
   mp=key_4x4();
   if(mp==0){
      dem = 0;
      flag++;
   }
   if(mp==1){
      dem = 1;
      flag++;
   }
   if(mp==2){
      dem = 2;
      flag++;
   }
   if(mp==3){
      dem = 3;
      flag++;
   }
   if(mp==4){
      dem = 4;
      flag++;
   }
   if(mp==5){
      dem = 5;
      flag++;
   }
   if(mp==6){
      dem = 6;
      flag++;
   }
   if(mp==7){
      dem = 7;
      flag++;
   }
   if(mp==8){
      dem = 8;
      flag++;
   }
   if(mp==9){
      dem = 9;
      flag++;
   }
}
void datgioihan()
{
   if(flag==1){
      gioihan=dem*10;
   }
   if(flag==2){
      gioihan=gioihan+dem;
      flag=0;
      
   }
   lcd_gotoxy(1,2);
   printf(lcd_putc,"GIOI HAN: %02u", gioihan);
}
void quetled(){
   if(t0if == 1)
   {
      set_timer0(100);
      bdn++;
      t0if=0;
      if(bdn==50){
         bdn=0;
         giay++;
         if(giay>59){
            giay=0;
            phut++;
            if(phut>59){
               phut=0;
               gio++;
               if(gio>23){
                  phut=0;
                  gio=0;
               }
            }
         }
      }
   }
   output_b(ma7doan[gio/10%10]);output_low(pin_a0); delay_ms(1); output_high(pin_a0);
   output_b(ma7doan[gio/1%10]);output_low(pin_a1); delay_ms(1); output_high(pin_a1);
   output_b(ma7doan[phut/10%10]);output_low(pin_a3); delay_ms(1); output_high(pin_a3);
   output_b(ma7doan[phut/1%10]);output_low(pin_a4); delay_ms(1); output_high(pin_a4);
   output_b(ma7doan[giay/10%10]);output_low(pin_a6); delay_ms(1); output_high(pin_a6);
   output_b(ma7doan[giay/1%10]);output_low(pin_a7); delay_ms(1); output_high(pin_a7);
   output_b(0xbf);output_low(pin_a2); delay_ms(1); output_high(pin_a2);
   output_b(0xbf);output_low(pin_a5); delay_ms(1); output_high(pin_a5);
}
void demsp(unsigned int8 gh)
{
   datgioihan();
   if(input(pin_c3)==0)
   {
      delay_ms(20);
      if(input(pin_c3)==0){
         ttdem=!ttdem;
         if(ttdem==1) setup_timer_1(t1_external|t1_div_by_1);
         else setup_timer_1(t1_disabled);
         while(input(pin_c3)==0);
      }
   }
  
   kq=get_timer1();
   if(kq>gh){
      set_timer1(1);
      tong+=gh;
   }
   lcd_gotoxy(1,1);
   printf(lcd_putc,"SAN PHAM : %02u CAI",kq);
   
}
void nangsuat(){
   if(giay>59){
      ns=tong/1;
   }
   lcd_gotoxy(21,1);
   printf(lcd_putc,"NANG SUAT: %03u Cai",ns);
}
void main()
{
   set_tris_a(0);
   set_tris_b(0);
   set_tris_e(0);
   set_tris_c(0x0f);
   set_tris_d(0xff);
   setup_timer_0(t0_internal|t0_div_256);
   set_timer0(100);
   setup_timer_1(t1_disabled);
   set_timer1(0);
   lcd_init();
   lcd_gotoxy(1,1);
   printf(lcd_putc,"SAN PHAM : %02u CAI",kq);
   while(true)
   {
      matranphim();
      quetled();
      
      demsp(gioihan);
      nangsuat();
   }
}
