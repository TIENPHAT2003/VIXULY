#include<16f887.h>
#fuses intrc_io
#use delay(clock=8M)
signed int8 i,dem=0;
unsigned int32 y,n;

#define lcd_rs pin_c5
#define lcd_rw pin_c6
#define lcd_e pin_c7
#define output_lcd output_d
#include <tv_lcd.c>
#include<stdlib.h>
void st()
{
   output_a(0xff);
   output_b(0xff);
   delay_ms(200);
   if(input(pin_e1)==0||input(pin_e2)==0) break;
   output_a(0);
   output_b(0);   
   if(input(pin_e1)==0||input(pin_e2)==0) break;
}
void stsp()
{
   for(i=16;i>=0;i--)
   {
      y=0xffff>>i;
      // 8led 1111 1111 >>8 = 0000 0000 >>7 0000 0001
      output_a(y);
      output_b(y>>8);
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
      output_b(n);
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
      output_b(n);
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
      output_b(n);
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
      output_b(n);
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
      delay_ms(100);
      if(input(pin_e1)==0||input(pin_e2)==0) break;
   }
}

void lcd_trangthai()
{  
      lcd_setup();
      lcd_command(0x80);
      lcd_data("HO TEN: VU TIEN PHAT");
      lcd_command(0xc0);
      lcd_data("MSSV: 21151309");
      lcd_command(0x94);
      if(dem==1)  lcd_data("SANG TAT"); // sang tat
     
      if(dem==2)  lcd_data("SANG DAN SANG PHAI"); // sang dan sang phai
     
      if(dem==3)  lcd_data("SANG DAN SANG TRAI"); // sang dan sang trai
     
      if(dem==4)  lcd_data("TAT DAN SANG TRAI"); // tat dan sang trai
      
      if(dem==5)  lcd_data("TAT DAN SANG PHAI"); // tat dan sang phai
      
      if(dem==6)  lcd_data("SANG TRONG RA");; // sang trong ra
      
      if(dem==7)  lcd_data("SANG NGOAI VAO"); // sang ngoai vao
      
      if(dem==8)  lcd_data("TAT NGOAI VAO"); // tat ngoai vao
     
      if(dem==9)  lcd_data("TAT TRONG RA"); // tat trong ra
      
      if(dem==10) lcd_data("ZICH ZAC"); // zich zac
}
void nutnhan()
{
   if(input(pin_e1)==0)
   {
      delay_ms(20);
      if(input(pin_e1)==0)
      {
         dem++;
         if(dem>10) dem = 1;
         lcd_trangthai();
         lcd_command(0xd4);
         printf(lcd_data, "SO RANDOM: %lu", rand()%100);
         while(input(pin_e1)==0);
      }
   }
   if(input(pin_e2)==0)
   {
      delay_ms(20);
      if(input(pin_e2)==0)
      {
         dem--;
         if(dem < 1) dem = 10;
         lcd_trangthai();
         lcd_command(0xd4);
         printf(lcd_data, "SO RANDOM: %lu", rand()%100);
         while(input(pin_e2)==0);
      }
   }
}

void main()
{  set_tris_a(0);
   set_tris_b(0);
   set_tris_c(0);
   set_tris_d(0);
   set_tris_e(0xff);
   output_a(0);
   output_b(0);
   lcd_setup();
   lcd_command(0x80);
   lcd_data("HO TEN: VU TIEN PHAT");
   lcd_command(0xc0);
   lcd_data("MSSV: 21151309");
   lcd_command(0x94);
   lcd_data("KHONG CO TRANG THAI");
   lcd_command(0xd4);
   printf(lcd_data, "SO RANDOM: %lu", rand()%100);
   while(true)
   {  
      nutnhan();
      if(dem==1)  st(); // sang tat
     
      if(dem==2)  stsp(); // sang dan sang phai
     
      if(dem==3)  spst(); // sang dan sang trai
     
      if(dem==4)  tpst(); // tat dan sang trai
      
      if(dem==5)  ttsp(); // tat dan sang phai
      
      if(dem==6)  strn(); // sang trong ra
      
      if(dem==7)  snvt(); // sang ngoai vao
      
      if(dem==8)  tnvt(); // tat ngoai vao
     
      if(dem==9)  ttrn(); // tat trong ra
      
      if(dem==10) zichzac(); // zich zac
   }
}
