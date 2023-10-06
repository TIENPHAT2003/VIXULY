#include<16f887.h>
#fuses intrc_io
#use delay(clock=8M)
signed int8 i,dem=0;
unsigned int32 y,n, z;
const unsigned int8 maled[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
const unsigned int8 hu[]={0x89,0x63};
void led()
{
   output_c(hu[0]);  output_low(pin_d4);  delay_ms(1);   output_high(pin_d4);
   output_c(hu[1]);  output_low(pin_d5);  delay_ms(1);   output_high(pin_d5);
   output_c(maled[dem/10%10]);  output_low(pin_d6);  delay_ms(1);   output_high(pin_d6);
   output_c(maled[dem/1%10]);  output_low(pin_d7);  delay_ms(1);   output_high(pin_d7);
   //delay_ms(1);
}
void st()
{
   output_a(0xff);
   output_b(0xff);
//!   output_c(0xff);
//!   output_d(0xff);
//!   delay_ms(200);
    for(z=0;z<200;z++) 
    {    
      led();
       if(input(pin_e1)==0||input(pin_e2)==0) break;
       }
   output_a(0);
   output_b(0);
//!   output_c(0);
   output_d(0);
//!   delay_ms(200);
   for(z=0;z<200;z++) 
    {    
      led();
       if(input(pin_e1)==0||input(pin_e2)==0) break;
       }
}
void stsp()
{
   for(i=16;i>=0;i--)
   {
      y=0xffff>>i;
      // 8led 1111 1111 >>8 = 0000 0000 >>7 0000 0001
      output_a(y);
      output_b(y>>8);
//!      output_c(y>>16);
//!      output_d(y>>24);
      led();
      delay_ms(50);
      if(input(pin_e1)==0||input(pin_e2)==0) break;
   }
}
void spst()
{
   for(i=16;i>=0;i--)
   {
      y=0xffff<<i;
      // 8led 1111 1111 <<8 = 0000 0000 <<7 1000 0000
      output_a(y);
      output_b(y>>8);
//!      output_c(y>>16);
//!      output_d(y>>24);
      led();
      delay_ms(50);
      if(input(pin_e1)==0||input(pin_e2)==0) break;
   }
}
void tpst()
{
   for(i=16;i>=0;i--)
   {
      y=~(0xffff<<i);
      // 8led 1111 1111 >>8 = 0000 0000 >>7 1000 0000 sau khi dao 0111 1111
      output_a(y);
      output_b(y>>8);
//!      output_c(y>>16);
//!      output_d(y>>24);
      led();
      delay_ms(50);
      if(input(pin_e1)==0||input(pin_e2)==0) break;
   }
}
void ttsp()
{
   for(i=16;i>=0;i--)
   {
      y=~(0xffff>>i);
      output_a(y);
      output_b(y>>8);
//!      output_c(y>>16);
//!      output_d(y>>24);
      led();
      delay_ms(50);
      if(input(pin_e1)==0||input(pin_e2)==0) break;
   }
}
void strn()   // a,b sang tu phai sang trai c,d sang tu trai sang phai
{
   for(i=8;i>=0;i--)
   {
      y=(0xff<<i);  
      n=(0xff>>i);
      output_a(y);
//!      output_b(y>>8);
      output_b(n);
//!      output_d(n>>8);
      led();
      delay_ms(50);
      if(input(pin_e1)==0||input(pin_e2)==0) break;
  }
}
void snvt()   // a,b sang tu trai sang phai c,d sang tu pst
{
   for(i=8;i>=0;i--)
   {
      y=(0xff>>i);  
      n=(0xff<<i);
      output_a(y);
//!      output_b(y>>8);
      output_b(n);
//!      output_d(n>>8);
      led();
      delay_ms(50);
      if(input(pin_e1)==0||input(pin_e2)==0) break;
  }
 }
void tnvt()  
{
   for(i=8;i>=0;i--)
   {
      y=~(0xff>>i);  
      n=~(0xff<<i);
      output_a(y);
//!      output_b(y>>8);
      output_b(n);
//!      output_d(n>>8);
      led();
      delay_ms(50);
      if(input(pin_e1)==0||input(pin_e2)==0) break;
   }
}
void ttrn()  
{
   for(i=8;i>=0;i--)
   {
      y=~(0xff<<i);  
      n=~(0xff>>i);
      output_a(y);
//!      output_b(y>>8);
      output_b(n);
//!      output_d(n>>8);
      led();
      delay_ms(50);
      if(input(pin_e1)==0||input(pin_e2)==0) break;
  }
 }
void zichzac()
{
     for(i=16;i>=0;i--)
   {
      y=(0xaaaa>>i);
      output_a(y);
      output_b(y>>8);
//!      output_d(y>>16);
//!      output_c(y>>24);
      led();
      delay_ms(50);
      if(input(pin_e1)==0||input(pin_e2)==0) break;
   }
}
void nutnhan()
{
   if(input(pin_e1)==0)
   {
      delay_ms(20);
      if(input(pin_e1)==0)
      {
         dem=dem+1;
         while(input(pin_e1)==0);
      }
   }
   if(input(pin_e2)==0)
   {
      delay_ms(20);
      if(input(pin_e2)==0)
      {
         dem=dem-1;
         while(input(pin_e2)==0);
      }
   }
}

void main()
{  set_tris_a(0);
   set_tris_b(0);
   set_tris_c(0);
   set_tris_d(0);
   set_tris_e(0xf);
   while(true)
   {  nutnhan();
      if(dem==0)
      {
         output_a(0);
         output_b(0);
         output_c(0);
         output_d(0);
      }
      led();
      if(dem>10||dem<0) dem=0;
      if(dem==1)  st();
     
      if(dem==2)  stsp();
     
      if(dem==3)  spst();
     
      if(dem==4)  tpst();
      
      if(dem==5)  ttsp();
      
      if(dem==6)  strn();
      
      if(dem==7)  snvt();
      
      if(dem==8)  tnvt();
     
      if(dem==9)  ttrn();
      
      if(dem==10) zichzac();
     
   }
}
