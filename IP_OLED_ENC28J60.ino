/*
 * Step1 : ต่อวงจรดังรูป

Arduino ENC28J60
5V  VCC
GND GND
pin 13  SCK
pin 12  SO
pin 11  SI
pin 10  CS
 */



#include <Arduino.h>
#include <EtherCard.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

#define OLED_MOSI   2   //
#define OLED_CLK    3   //
#define OLED_DC     4   //
#define OLED_CS     5   //
#define OLED_RESET  6   //
//U8G2_SSD1306_128X64_NONAME_1_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ OLED_CLK, /* data=*/ OLED_MOSI, /* cs=*/ OLED_CS, /* dc=*/ OLED_DC, /* reset=*/ OLED_RESET);
U8X8_SSD1306_128X64_NONAME_4W_SW_SPI u8x8(/* clock=*/ OLED_CLK, /* data=*/ OLED_MOSI, /* cs=*/ OLED_CS, /* dc=*/ OLED_DC, /* reset=*/ OLED_RESET);
static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x32 };
byte Ethernet::buffer[700];
static boolean dhcp = true;


void printNoAccess(){  
  
  u8x8.clearDisplay();
  u8x8.setFont(u8x8_font_amstrad_cpc_extended_r);  
  u8x8.setCursor(0,0);
  u8x8.print("Failed to access");
  u8x8.setCursor(0,1);
  u8x8.print("Ethernet");
}

void print_failed(){
  
  /*do{    
    u8g2.drawStr(0,21,"DHCP failed");
  }while( u8g2.nextPage() );*/
  u8x8.clearDisplay();
  u8x8.setFont(u8x8_font_amstrad_cpc_extended_r);  
  u8x8.setCursor(0,0);
  u8x8.print("DHCP failed.");
}

void print_welcome(){
  u8x8.clearDisplay();
  u8x8.setCursor(4,3); 
  u8x8.print("WELCOME");
  u8x8.setCursor(3,4); 
  u8x8.print("JATURAPAT");
}
String txt(byte ip[]){  
  String txt = "";  
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    txt += (String)ip[thisByte];
    if(thisByte < 3){
      txt += ".";
    }
  }
  return txt;
}

void setup(void) {
  Serial.begin(9600);
  u8x8.begin();
  u8x8.setPowerSave(0);
  //sendcommand(0xA0 | 0x1);
  u8x8.setFont(u8x8_font_amstrad_cpc_extended_r); 

  print_welcome();
  delay(4000);
  
  if (ether.begin(sizeof Ethernet::buffer, mymac) == 0) {
    printNoAccess();
    delay(3000);
  }

    u8x8.clearDisplay();    
    u8x8.setCursor(0, 0);
    u8x8.print("Setting up DHCP");    
    u8x8.setCursor(0, 1);
    u8x8.print("Please wait.....");

  if(!ether.dhcpSetup()){ 
    print_failed();
    delay(5000);    
  } 

  //พิมพ์ออกทาง Serial
  /*ether.printIp("My IP: ", ether.myip);
  ether.printIp("Netmask: ", ether.netmask);
  ether.printIp("GW IP: ", ether.gwip);
  ether.printIp("DNS IP: ", ether.dnsip);*/
}


void loop(void) {
    u8x8.clearDisplay();
    u8x8.setInverseFont(1);
    u8x8.setCursor(0, 0);
    u8x8.print("IP:");
    u8x8.setInverseFont(0);
    u8x8.setCursor(1, 1);
    u8x8.print(txt(ether.myip)); 
    u8x8.setInverseFont(1);
    u8x8.setCursor(0, 2);
    u8x8.print("Netmask:");
    u8x8.setInverseFont(0);
    u8x8.setCursor(1, 3);
    u8x8.print(txt(ether.netmask));
    u8x8.setInverseFont(1);
    u8x8.setCursor(0, 4);
    u8x8.print("Gateway:");
    u8x8.setInverseFont(0); 
    u8x8.setCursor(1, 5);
    u8x8.print(txt(ether.gwip)); 
    u8x8.setInverseFont(1);
    u8x8.setCursor(0, 6);
    u8x8.print("DNS:");
    u8x8.setInverseFont(0);
    u8x8.setCursor(1, 7);
    u8x8.print(txt(ether.dnsip)); 
    delay(3000);
}
