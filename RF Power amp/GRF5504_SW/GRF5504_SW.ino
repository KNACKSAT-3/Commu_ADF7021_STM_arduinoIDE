
#define VEN1 2
#define VEN2 3
#define SW1_1 8
#define SW1_2 9
#define SW2_1 10
#define SW2_2 11

int mode = 0;     // 0=RX,  1=TX
int pa = 0;       // 0=OFF, 1=ON

void setup() {
  Serial.begin(9600);
  pinMode(SW1_1, OUTPUT);
  pinMode(SW1_2, OUTPUT);
  pinMode(SW2_1, OUTPUT);
  pinMode(SW2_2, OUTPUT);
  pinMode(VEN1, OUTPUT);
  pinMode(VEN2, OUTPUT);
  
  RX();
  PA_OFF();
  stat(mode, pa);
  Serial.println("Setup pass");
}

void loop() {
  if(Serial.available()>0){                                             // Control by Serial upper text
  String cmd=Serial.readStringUntil('\n');
    if(cmd=="PA ON"){ PA_ON(); }
    else if(cmd=="PA OFF"){ PA_OFF(); }
    else if(cmd=="TX"){ TX(); }
    else if(cmd=="RX"){ RX(); }
    else{Serial.println("Wrong Command!!");}
    stat(mode, pa);                                                     // Show Current Status
  }
}


void PA_ON(){
  digitalWrite(VEN1,1);
  delay(5);
  digitalWrite(VEN2,1);
  Serial.println("PA ON");
  pa=1;
}

void PA_OFF(){
  digitalWrite(VEN1,0);
  delay(5);
  digitalWrite(VEN2,0);
  Serial.println("PA OFF");
  pa=0;
}

void TX(){
  digitalWrite(SW1_1,0);
  digitalWrite(SW1_2,1);
  digitalWrite(SW2_1,1);
  digitalWrite(SW2_2,0);
  Serial.println("TX mode");
  mode=1;
}

void RX(){
  digitalWrite(SW1_1,1);
  digitalWrite(SW1_2,0);
  digitalWrite(SW2_1,0);
  digitalWrite(SW2_2,1);
  Serial.println("RX mode");
  mode=0;
}

void stat(int mode, int pa){
  Serial.print("Current Status : ");
  if(mode==0){ Serial.print(" RX ,"); }
  else{ Serial.print(" TX ,"); }
  if(pa==0){ Serial.print(" PA OFF"); }
  else{ Serial.print(" PA ON"); }
  Serial.println();
}