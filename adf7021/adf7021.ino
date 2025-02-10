/*  RF7021_V12 
    TCXO 19.68 MHz
    R=2, PFD=9.84MHz
    GMSK BT=0.5
    9600 bps
    R_divider=Enable
    Fdev=2400
    PFD=
*/


#include <SPI.h>
#include <SoftwareSerial.h>


//Wiring
#define CE      2     // CHIP ENABLE
#define SEL     7     // Go high after register was send
#define SDATA   11    // MCU MSB to ADF   MOSI
#define SREAD   12    // MCU Readback     MISO
#define SCLK    13    // clk
#define TxRxCLK  9    // pair to MCU TxDATA
#define TxRxDATA 8    // pair to MCU RxDATA

SoftwareSerial mySerial(TxRxDATA , TxRxCLK);           // RX, TX


void setup() {
  
  Serial.begin(9600);
  mySerial.begin(9600);
  SPI.begin();
  SPI.setDataMode( SPI_MODE0 );
  SPI.setBitOrder( MSBFIRST );
  SPI.setClockDivider( SPI_CLOCK_DIV16 );   // 16MHz/16 =1MHz

  Serial.println("Start");
  pinMode(CE , OUTPUT);
  pinMode(SEL , OUTPUT);
  digitalWrite(CE, 1);
  digitalWrite(SEL, 0);
  
  readSPIData();
  R1();
  R3();
  R0(1);
  R2();
  R5();
  R4();

  
  
  delay(2000);
}

void loop() {
  if(Serial.available()>0){             // TX
    R0(1);
    mySerial.println(Serial.read());
    R0(0);
  }
  if(mySerial.available()>0){            //RX
    Serial.println(mySerial.read());
  }
  delay(1000);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

void R0(int TX){
  digitalWrite(SEL,0);
  delay(100);
  if(TX==1){  // 0x12C35130, 0001 0010 1100 0011 0101 0001 0011 0000 , R=2 , Int_N=88 , Frac_N=13587 , 435MHz
    SPI.transfer(0x12);
    SPI.transfer(0xC3);
    SPI.transfer(0x51);
    SPI.transfer(0x30);
    delayMicroseconds(1);
    digitalWrite(SEL,1);
    delayMicroseconds(1);
    digitalWrite(SEL,0);
    Serial.println("TX mode");
  }
  if(TX==0){  // 0x1AC35130, 0001 1010 1100 0011 0101 0001 0011 0000 , R=2 , Int_N=88 , Frac_N=13587 , 435MHz
    SPI.transfer(0x1A);
    SPI.transfer(0xC3);
    SPI.transfer(0x51);
    SPI.transfer(0x30);
    delayMicroseconds(1);
    digitalWrite(SEL,1);
    delayMicroseconds(1);
    digitalWrite(SEL,0);
  }
  Serial.println("in regis");
}

void R1(){    // 0x14FA2A1, 0001 0100 1111 1010 0010 1010 0001 , Internal L , VCO Bias=2mA , VCO UP=2 , RF Div by 2=ON , VCO ON , Icp=2.1mA , CLKOUT Div=10 , R counter=2 , 435MHz
  digitalWrite(SEL,0);
  delay(100);
  SPI.transfer(0x01);
  SPI.transfer(0x4F);
  SPI.transfer(0xA2);
  SPI.transfer(0xA1);
    delayMicroseconds(1);
  digitalWrite(SEL,1);
  delayMicroseconds(1);
  digitalWrite(SEL,0);
  Serial.println("in regis");
}

void R2(){    // 0x5CD1092
  digitalWrite(SEL,0);
  delay(100);
  SPI.transfer(0x05);
  SPI.transfer(0xCD);
  SPI.transfer(0x10);
  SPI.transfer(0x92);
    delayMicroseconds(1);
  digitalWrite(SEL,1);
  delayMicroseconds(1);
  digitalWrite(SEL,0);
  Serial.println("in regis");
}

void R3(){    // 0xEB17FE63
  digitalWrite(SEL,0);
  delay(100);
  SPI.transfer(0xEB);
  SPI.transfer(0x17);
  SPI.transfer(0xFE);
  SPI.transfer(0x63);
    delayMicroseconds(1);
  digitalWrite(SEL,1);
  delayMicroseconds(1);
  digitalWrite(SEL,0);
  Serial.println("in regis");
}

void R4(){    //0x150AA04
  digitalWrite(SEL,0);
  delay(100);
  SPI.transfer(0x01);
  SPI.transfer(0x50);
  SPI.transfer(0xAA);
  SPI.transfer(0x04);
    delayMicroseconds(1);
  digitalWrite(SEL,1);
  delayMicroseconds(1);
  digitalWrite(SEL,0);
  Serial.println("in regis");
}

void R5(){
  digitalWrite(SEL,0);
  delay(100);
  SPI.transfer(0x05);
    delayMicroseconds(1);
  digitalWrite(SEL,1);
  delayMicroseconds(1);
  digitalWrite(SEL,0);
  Serial.println("in regis");
}

void R6(){
  digitalWrite(SEL,0);
  delay(100);
  SPI.transfer(0x06);
    delayMicroseconds(1);
  digitalWrite(SEL,1);
  delayMicroseconds(1);
  digitalWrite(SEL,0);
  Serial.println("in regis");
}

void R10(){   // 0x289635A
  digitalWrite(SEL,0);
  delay(100);
  SPI.transfer(0x28);
  SPI.transfer(0x96);
  SPI.transfer(0x35);
  SPI.transfer(0x5A);
    delayMicroseconds(1);
  digitalWrite(SEL,1);
  delayMicroseconds(1);
  digitalWrite(SEL,0);
  Serial.println("in regis");
}

void readSPIData() {
  digitalWrite(SEL, LOW);
  SPI.transfer(0x05);  // ส่ง MSB ของคำสั่ง
  SPI.transfer(0x57);  // ส่ง LSB ของคำสั่ง
  delayMicroseconds(10);  // เพิ่ม delay เล็กน้อยหลังส่งคำสั่ง
  digitalWrite(SEL, HIGH);
  byte receivedData = SPI.transfer(0x00);  // ส่ง dummy byte เพื่อรับข้อมูลกลับ

  delayMicroseconds(10);

  digitalWrite(SEL, LOW);

  Serial.print("Received Data: ");
  Serial.println(receivedData, BIN);  // แสดงข้อมูลที่ได้รับในรูปแบบเลขฐานสอง
}





