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

//Wiring
#define Serial    Serial1
#define CE        PA10     // CHIP ENABLE
#define SEL       PB10     // Go high after register was send
#define SDATA     PA7    // MCU MSB to ADF   MOSI
#define SREAD     PA6    // MCU Readback     MISO
#define SCLK      PA5    // clk
#define TxRxCLK   PB6     // pair to MCU TxDATA
#define TxRxDATA  PB7     // pair to MCU RxDATA

//             MOSI    MISO  SCLK   SSEL
SPIClass SPI_1(SDATA, SREAD, SCLK,  PA4);

HardwareSerial Serial1(PA3, PA2);             // RX , TX              USART2
HardwareSerial mySerial(TxRxDATA, TxRxCLK);   // RX , TX    D2,D8     USART1


void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  Serial.println("Start");
  
  SPI_1.begin(); // Enable the SPI_1 instance with default SPISsettings
  SPI_1.setDataMode( SPI_MODE0 );
  SPI_1.setBitOrder( MSBFIRST );
  SPI_1.setClockDivider( SPI_CLOCK_DIV32 );
  
  pinMode(CE , OUTPUT);
  pinMode(SEL , OUTPUT);
  digitalWrite(CE, 0);    // clear Register
  delay(1000);
  digitalWrite(CE, 1);
  digitalWrite(SEL, 0);

  R0(0);
  R1();
  R3();
  R2();
  R4();
  R8();
  readSPIData();
  
  Serial.println("Finish setup");
  
  delay(2000);
}

void loop() {
  if(Serial.available()>0){             // TX
    R0(1);
    mySerial.println(Serial.readString());
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
    SPI_1.transfer(0x12);
    SPI_1.transfer(0xC3);
    SPI_1.transfer(0x51);
    SPI_1.transfer(0x30);
    Serial.println("TX mode");
  }
  if(TX==0){  // 0x1AC35130, 0001 1010 1100 0011 0101 0001 0011 0000 , R=2 , Int_N=88 , Frac_N=13587 , 435MHz
    SPI_1.transfer(0x1A);
    SPI_1.transfer(0xC3);
    SPI_1.transfer(0x51);
    SPI_1.transfer(0x30);
    Serial.println("RX mode");
  }
  delayMicroseconds(10);
  digitalWrite(SEL,1);
  delayMicroseconds(1);
  digitalWrite(SEL,0);
  Serial.println("in regis");
}

void R1(){    // 0x14FA2A1, 0001 0100 1111 1010 0010 1010 0001 , Internal L , VCO Bias=2mA , VCO UP=2 , RF Div by 2=ON , VCO ON , Icp=2.1mA , CLKOUT Div=10 , R counter=2 , 435MHz
  digitalWrite(SEL,0);
  SPI_1.transfer(0x01);
  SPI_1.transfer(0x4F);
  SPI_1.transfer(0xA2);
  SPI_1.transfer(0xA1);
  delayMicroseconds(10);
  digitalWrite(SEL,1);
  delayMicroseconds(1);
  digitalWrite(SEL,0);
  Serial.println("in regis");
}

void R2(){    // 0x5CD1092
  digitalWrite(SEL,0);
  SPI_1.transfer(0x05);
  SPI_1.transfer(0xCD);
  SPI_1.transfer(0x10);
  SPI_1.transfer(0x92);
  delayMicroseconds(10);
  digitalWrite(SEL,1);
  delayMicroseconds(1);
  digitalWrite(SEL,0);
  Serial.println("in regis");
}

void R3(){    // 0xEB17FE63
  digitalWrite(SEL,0);
  SPI_1.transfer(0xEB);
  SPI_1.transfer(0x17);
  SPI_1.transfer(0xFE);
  SPI_1.transfer(0x63);
  delayMicroseconds(10);
  digitalWrite(SEL,1);
  delayMicroseconds(1);
  digitalWrite(SEL,0);
  Serial.println("in regis");
}

void R4(){    //0x150AA04
  digitalWrite(SEL,0);
  SPI_1.transfer(0x01);
  SPI_1.transfer(0x50);
  SPI_1.transfer(0xAA);
  SPI_1.transfer(0x04);
  delayMicroseconds(10);
  digitalWrite(SEL,1);
  delayMicroseconds(1);
  digitalWrite(SEL,0);
  Serial.println("in regis");
}

void R5(){
  digitalWrite(SEL,0);
  SPI_1.transfer(0x05);
  delayMicroseconds(10);
  digitalWrite(SEL,1);
  delayMicroseconds(1);
  digitalWrite(SEL,0);
  Serial.println("in regis");
}

void R6(){
  digitalWrite(SEL,0);
  SPI_1.transfer(0x06);
  delayMicroseconds(10);
  digitalWrite(SEL,1);
  delayMicroseconds(1);
  digitalWrite(SEL,0);
  Serial.println("in regis");
}

void R8(){    // 0001 0111 1101 1000
  digitalWrite(SEL,0);
  SPI_1.transfer(0x17);
  SPI_1.transfer(0xD8);
  delayMicroseconds(10);
  digitalWrite(SEL,1);
  delayMicroseconds(1);
  digitalWrite(SEL,0);
  Serial.println("in regis");
}

void R10(){   // 0x289635A
  digitalWrite(SEL,0);
  SPI_1.transfer(0x28);
  SPI_1.transfer(0x96);
  SPI_1.transfer(0x35);
  SPI_1.transfer(0x5A);
  delayMicroseconds(10);
  digitalWrite(SEL,1);
  delayMicroseconds(1);
  digitalWrite(SEL,0);
  Serial.println("in regis");
}

void readSPIData() { // 0001 0100 0111
  digitalWrite(SEL, LOW);
  SPI_1.transfer(0x01);
  SPI_1.transfer(0x47);
  delayMicroseconds(1);  
  digitalWrite(SEL, HIGH);
  byte receivedData1 = SPI_1.transfer(0x00);  // ส่ง dummy byte เพื่อรับข้อมูลกลับ MSB
  byte receivedData2 = SPI_1.transfer(0x00);

  delayMicroseconds(10);

  digitalWrite(SEL, LOW);

  Serial.print("Received Data: ");
  Serial.print(receivedData1, BIN);
  Serial.println(receivedData2, BIN);
}


