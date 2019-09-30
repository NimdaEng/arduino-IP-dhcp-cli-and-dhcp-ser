
#include <EtherCard.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(9, 8, 7, 6, 5, 4);
static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x32 };

byte Ethernet::buffer[700];
static boolean dhcp = true;
//static int wakeOnLan = 3;
void setup () {
  //Serial.begin(9600);
  //pinMode(wakeOnLan, INPUT);
  lcd.begin(16, 2); 
  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print("Hello, JHATURAPHUT!");
   delay(1000);
  if (ether.begin(sizeof Ethernet::buffer, mymac) == 0) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Failed to access");
    lcd.setCursor(0, 0);
    lcd.print("Ethernet");    
  }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Setting up DHCP");
    lcd.setCursor(0, 1);
    lcd.print("Please wait.....");
    if (!ether.dhcpSetup()){      
      print_failed(); 
      dhcp = false; 
    delay(2500);
    }else{
      dhcp = true;
    }
    
  //ether.printIp("My IP: ", ether.myip);
 //ether.printIp("Netmask: ", ether.netmask);
  //ether.printIp("GW IP: ", ether.gwip);
  //ether.printIp("DNS IP: ", ether.dnsip);  
}

void loop () {  
  print_ip(ether.myip);
  delay(3500);
  print_NETMASK(ether.netmask);
  delay(3500);
  print_GATEWAY(ether.gwip);
  delay(3500);
  print_DNS(ether.dnsip);
  delay(3500); 
  if(!dhcp){ 
  //if(digitalRead(wakeOnLan) == HIGH){  
  print_failed();
  delay(3500);
  } 
}

void print_ip(byte ip[]){
  lcd.clear();  
  lcd.setCursor(0,0);
  lcd.print("IP Address:");
  lcd.setCursor(0,1);
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    lcd.print(ip[thisByte], DEC);
    if(thisByte < 3){
    lcd.print(".");
    }
  }
}

void print_DNS(byte ip[]){
  lcd.clear();
  lcd.print("DNS NAME:");
  lcd.setCursor(0,1);
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    lcd.print(ip[thisByte], DEC);
    if(thisByte < 3){
    lcd.print(".");
    }
  }
}

void print_NETMASK(byte ip[]){
  lcd.clear();
  lcd.print("SUBNETMASK:");
  lcd.setCursor(0,1);
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    lcd.print(ip[thisByte], DEC);
    if(thisByte < 3){
    lcd.print(".");
    }
  }
}

void print_GATEWAY(byte ip[]){
  lcd.clear();
  lcd.print("GATEWAY:");
  lcd.setCursor(0,1);
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    lcd.print(ip[thisByte], DEC);
    if(thisByte < 3){
    lcd.print(".");
    }
  }
}

void print_failed(){
    lcd.clear();
    lcd.setCursor(0, 0);   
    lcd.print("DHCP failed");  
}
void print_failed2(){
    lcd.clear();
    lcd.setCursor(0, 0);   
    lcd.print("DHCP failed2");  
}

