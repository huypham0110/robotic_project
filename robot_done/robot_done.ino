#include <TimerOne.h>

#define chieuThuan   0  
#define chieuNghich  1

//MOTOR LINK3
#define ENA3    20
#define ENB3    21
#define PWM3    44
#define IN13    40
#define IN23    42
#define limit0  31

//Theta 1
#define ena     8
#define dir1    5
#define tep1    2
#define limit1  33

//Theta 2
#define dir2    6
#define tep2    3
#define limit2  35

//Rely nam cham
#define magnet  46

//LINK 3
double alpha3, beta3, gamma3;
double Kp3, Kd3, Ki3;
volatile double Output3, Outputlast3;
volatile double etheta3,etheta_d3,etheta_dd3;
volatile double vitri3;
volatile double pulse_theta3;

double vitridat3_d[6];
double vitridat3_angle[6];
double vitridat3Old;

double P, I, D;
double T=0.01; 

int bienDone=0;

//THETA 1, THETA 2
long delayStep = 1000;

double step1[6];
double step2[6];

double theta1[6];
double theta2[6];

double gocOld1=0;
double gocOld2=0;

int statusStep;
                       
//
String dataReceive ="";
int soLuongVat=0;
int mode=254;  
int bienDem = 0;

void setup() 
{
  Serial.begin(115200);
  
  //LINK3
  pinMode(limit0,INPUT_PULLUP);
  pinMode(ENA3,INPUT_PULLUP);
  pinMode(ENB3,INPUT_PULLUP);
  pinMode(PWM3,OUTPUT);
  pinMode(IN13,OUTPUT);
  pinMode(IN23,OUTPUT);
  
  //THETA 1
  pinMode(limit1,INPUT_PULLUP);
  pinMode(ena, OUTPUT);
  pinMode(tep1, OUTPUT);
  pinMode(dir1, OUTPUT);
  
  //THETA 2
  pinMode(limit2,INPUT_PULLUP);
  pinMode(tep2, OUTPUT);
  pinMode(dir2, OUTPUT);

  // HUT
  pinMode(magnet, OUTPUT);
  digitalWrite(magnet, LOW);
  
  //LINK3
  P=35;
  I=0;
  D=0.5;
  
  etheta3=0,etheta_d3=0,etheta_dd3=0;
  Output3=0,Outputlast3=0;
  pulse_theta3=0;
  vitri3=0;
  for(int i=0; i<6; i++) vitridat3_angle[i]=0;
  vitridat3Old=0;

  // Link 1 2 
  statusStep=0;
  digitalWrite(ena, statusStep);
  digitalWrite(dir1, chieuNghich);
  digitalWrite(dir2, chieuThuan);

  //DEM XUNG
  attachInterrupt(digitalPinToInterrupt(20), read_encoder3, CHANGE);
  attachInterrupt(digitalPinToInterrupt(21), read_encoder3, CHANGE);  
}

void loop() 
{
  nhanDuLieu();

  if(bienDone==1 && (soLuongVat ==1 || soLuongVat ==2 || soLuongVat ==3 || soLuongVat ==4 || soLuongVat ==5))
  {
    switch(mode)
    {
      case 0:
        if(statusStep ==1)
        {
          statusStep=0;
          digitalWrite(ena, statusStep);
        }
        step1[1]=stepPulseCal1(theta1[1]);
        for(long i=0; i<step1[1]; i++) runStep1();
        
        step2[1]=stepPulseCal2(theta2[1]);
        for(long i=0; i<step2[1]; i++) runStep2();
  
        delay(500);
        hutVat();
        delay(500);
  
        mode++;
        bienDone=0;
        
        break;
        
      case 1:
        step1[0]=stepPulseCal1(theta1[0]);
        for(long i=0; i<step1[0]; i++) runStep1();
        
        step2[0]=stepPulseCal2(theta2[0]);
        for(long i=0; i<step2[0]; i++) runStep2();
  
        delay(500);
        thaVat();
        delay(500);
        mode++;
        if(mode>=(2*soLuongVat)) mode=200;
        
        bienDone=0;
        break;
  
      case 2:
        if(statusStep ==1)
        {
          statusStep=0;
          digitalWrite(ena, statusStep);
        }
        step1[2]=stepPulseCal1(theta1[2]);
        for(long i=0; i<step1[2]; i++) runStep1();
        
        step2[2]=stepPulseCal2(theta2[2]);
        for(long i=0; i<step2[2]; i++) runStep2();
  
        delay(500);
        hutVat();
        delay(500);
        mode++;
        
        bienDone=0;
        break;
  
      case 3:
        step1[0]=stepPulseCal1(theta1[0]);
        for(long i=0; i<step1[0]; i++) runStep1();
        
        step2[0]=stepPulseCal2(theta2[0]);
        for(long i=0; i<step2[0]; i++) runStep2();
  
        delay(500);
        thaVat();
        delay(500);
        mode++;
        if(mode>=(2*soLuongVat)) mode=200;
        
        bienDone=0;
        break;
  
      case 4:
        if(statusStep ==1)
        {
          statusStep=0;
          digitalWrite(ena, statusStep);
        }
        step1[3]=stepPulseCal1(theta1[3]);
        for(long i=0; i<step1[3]; i++) runStep1();
        
        step2[3]=stepPulseCal2(theta2[3]);
        for(long i=0; i<step2[3]; i++) runStep2();
  
        delay(500);
        hutVat();
        delay(500);
        mode++;
        
        bienDone=0;
        break;
  
      case 5:
        step1[0]=stepPulseCal1(theta1[0]);
        for(long i=0; i<step1[0]; i++) runStep1();
        
        step2[0]=stepPulseCal2(theta2[0]);
        for(long i=0; i<step2[0]; i++) runStep2();
  
        delay(500);
        thaVat();
        delay(500);
        mode++;
        if(mode>=(2*soLuongVat)) mode=200;
        
        bienDone=0;
        break;
        
      case 6:
        if(statusStep ==1)
        {
          statusStep=0;
          digitalWrite(ena, statusStep);
        }
        step1[4]=stepPulseCal1(theta1[4]);
        for(long i=0; i<step1[4]; i++) runStep1();
        
        step2[4]=stepPulseCal2(theta2[4]);
        for(long i=0; i<step2[4]; i++) runStep2();
  
        delay(500);
        hutVat();
        delay(500);
        mode++;
        
        bienDone=0;
        break;
  
      case 7:
        
        step1[0]=stepPulseCal1(theta1[0]);
        for(long i=0; i<step1[0]; i++) runStep1();
        
        step2[0]=stepPulseCal2(theta2[0]);
        for(long i=0; i<step2[0]; i++) runStep2();
  
        delay(500);
        thaVat();
        delay(500);
        mode++;
        if(mode>=(2*soLuongVat)) mode=200;
        
        bienDone=0;
        break;
  
      case 8:
        if(statusStep ==1)
        {
          statusStep=0;
          digitalWrite(ena, statusStep);
        }
        step1[5]=stepPulseCal1(theta1[5]);
        for(long i=0; i<step1[5]; i++) runStep1();
        
        step2[5]=stepPulseCal2(theta2[5]);
        for(long i=0; i<step2[5]; i++) runStep2();
  
        delay(500);
        hutVat();
        delay(500);
        mode++;
        
        bienDone=0;
        break;
  
      case 9:
        step1[0]=stepPulseCal1(theta1[0]);
        for(long i=0; i<step1[0]; i++) runStep1();
        
        step2[0]=stepPulseCal2(theta2[0]);
        for(long i=0; i<step2[0]; i++) runStep2();
  
        delay(500);
        thaVat();
        delay(500);
        mode++;
        if(mode>=(2*soLuongVat)) mode=200;
        
        bienDone=0;
        break;

      default:
        break;
    } 
  }

  Timer1.initialize(10000);
  Timer1.attachInterrupt(timer1ISR);
}

void dieukhiendongco(double out, int thuan, int nghich, int pwm)
{
  constrain(out,-255,255);
  
  if(out>0)                           //QUAY THUAN
  {
    analogWrite(pwm,out);
    digitalWrite(thuan, HIGH);
    digitalWrite(nghich, LOW);
  }
  else if(out<0)                      //QUAY NGHICH
  {
    analogWrite(pwm,abs(out));
    digitalWrite(thuan, LOW);
    digitalWrite(nghich, HIGH);
  }
  else                                //DUNG
  {
    analogWrite(pwm,0);
    digitalWrite(thuan, LOW);
    digitalWrite(nghich, LOW);
  }
}

void PID3(double Kp3, double Ki3, double Kd3, double vitridat3)
{
  vitri3 = (double)((pulse_theta3*360.0/495.0))/4.0; 
  etheta3 = vitridat3 - vitri3;
  
  if(vitridat3Old != vitridat3)
  {
    bienDone = 0;
    vitridat3Old = vitridat3;
    bienDem = 0;
  }
  else if(etheta3 > -5 && etheta3 < 5) 
  {
    bienDem++;
    if(bienDem == 100)
    {
      bienDem = 0;
      bienDone = 1;
    }
  }
  
  alpha3=2*T*Kp3+Ki3*T*T+2*Kd3;
  beta3=T*T*Ki3-4*Kd3-2*T*Kp3;
  gamma3=2*Kd3;
  Output3=(alpha3*etheta3+beta3*etheta_d3+gamma3*etheta_dd3+2*T*Outputlast3)/(2*T);
  etheta_dd3=etheta_d3;
  etheta_d3=etheta3;
  Outputlast3=Output3;
  Output3=constrain(Output3, -255, 255);
  
  Serial.println(vitri3);
  Serial.println(etheta3);
  Serial.println("----        ");
}

void timer1ISR()
{
  if(mode==255) // PID cho set home
  {
    PID3(P,I,D,vitridat3_angle[0]);
    dieukhiendongco(Output3,IN23,IN13,PWM3); 
  }

  if(mode==0) // Chay toi vi tri 1
  {
    PID3(P,I,D,vitridat3_angle[1]);
    dieukhiendongco(Output3,IN23,IN13,PWM3); 
  }
  
  if(mode==1) // Chay toi vi tri tha
  {
    PID3(P,I,D,vitridat3_angle[0]);
    dieukhiendongco(Output3,IN23,IN13,PWM3); 
  }
  
  if(mode==2) // Chay toi vi tri 2
  {
    PID3(P,I,D,vitridat3_angle[2]);
    dieukhiendongco(Output3,IN23,IN13,PWM3); 
  }
  
  if(mode==3) // Chay toi vi tri tha
  {
    PID3(P,I,D,vitridat3_angle[0]);
    dieukhiendongco(Output3,IN23,IN13,PWM3); 
  }

  if(mode==4) // Chay toi vi tri 3
  {
    PID3(P,I,D,vitridat3_angle[3]);
    dieukhiendongco(Output3,IN23,IN13,PWM3); 
  }

  if(mode==5) // Chay toi vi tri tha
  {
    PID3(P,I,D,vitridat3_angle[0]);
    dieukhiendongco(Output3,IN23,IN13,PWM3); 
  }

  if(mode==6) // Chay toi vi tri 4
  {
    PID3(P,I,D,vitridat3_angle[4]);
    dieukhiendongco(Output3,IN23,IN13,PWM3); 
  }
  
  if(mode==7) // Chay toi vi tri tha
  {
    PID3(P,I,D,vitridat3_angle[0]);
    dieukhiendongco(Output3,IN23,IN13,PWM3); 
  }

  if(mode==8) // Chay toi vi tri 5
  {
    PID3(P,I,D,vitridat3_angle[5]);
    dieukhiendongco(Output3,IN23,IN13,PWM3); 
  }
  
  if(mode==9) // Chay toi vi tri tha
  {
    PID3(P,I,D,vitridat3_angle[0]);
    dieukhiendongco(Output3,IN23,IN13,PWM3); 
  }
}

void nhanDuLieu()
{
  if(Serial.available() > 0) 
  {
    dataReceive = Serial.readStringUntil('\n');
    if(dataReceive=="home")
    {
      resetPID();
      mode = 254; // Dung PID
      setHome();
      resetPID();
      dataReceive ="";
    }
    else if(dataReceive != "")
    {
      mode = 254;
      String soLuongVatStr = getValue(dataReceive, ',', 0);
      soLuongVat = soLuongVatStr.toInt(); 
      
      // Vi tri tha vat
      String vitridat3Str_0 = getValue(dataReceive, ',', 1);
      String theta1Str_0 = getValue(dataReceive, ',', 2);
      String theta2Str_0 = getValue(dataReceive, ',', 3);
      vitridat3_d[0] = vitridat3Str_0.toDouble();
      theta1[0] = theta1Str_0.toDouble();
      theta2[0] = theta2Str_0.toDouble();

      // Diem 1
      if(soLuongVat >= 1)
      {
        String vitridat3Str_1 = getValue(dataReceive, ',', 4);
        String theta1Str_1 = getValue(dataReceive, ',', 5);
        String theta2Str_1 = getValue(dataReceive, ',', 6);
        vitridat3_d[1] = vitridat3Str_1.toDouble();
        theta1[1] = theta1Str_1.toDouble();
        theta2[1] = theta2Str_1.toDouble();
      }

      // Diem 2
      if(soLuongVat >= 2)
      {
        String vitridat3Str_2 = getValue(dataReceive, ',', 7);
        String theta1Str_2 = getValue(dataReceive, ',', 8);
        String theta2Str_2 = getValue(dataReceive, ',', 9);
        vitridat3_d[2] = vitridat3Str_2.toDouble();
        theta1[2] = theta1Str_2.toDouble();
        theta2[2] = theta2Str_2.toDouble();
      }

      // Diem 3
      if(soLuongVat >= 3)
      {
        String vitridat3Str_3 = getValue(dataReceive, ',', 10);
        String theta1Str_3 = getValue(dataReceive, ',', 11);
        String theta2Str_3 = getValue(dataReceive, ',', 12);
        vitridat3_d[3] = vitridat3Str_3.toDouble();
        theta1[3] = theta1Str_3.toDouble();
        theta2[3] = theta2Str_3.toDouble();
      }
      
      // Diem 4
      if(soLuongVat >= 4)
      {
        String vitridat3Str_4 = getValue(dataReceive, ',', 13);
        String theta1Str_4 = getValue(dataReceive, ',', 14);
        String theta2Str_4 = getValue(dataReceive, ',', 15);
        vitridat3_d[4] = vitridat3Str_4.toDouble();
        theta1[4] = theta1Str_4.toDouble();
        theta2[4] = theta2Str_4.toDouble();
      }

      // Diem 5
      if(soLuongVat >= 5)
      {
        String vitridat3Str_5 = getValue(dataReceive, ',', 16);
        String theta1Str_5 = getValue(dataReceive, ',', 17);
        String theta2Str_5 = getValue(dataReceive, ',', 18);
        vitridat3_d[5] = vitridat3Str_5.toDouble();
        theta1[5] = theta1Str_5.toDouble();
        theta2[5] = theta2Str_5.toDouble();
      }

      for(int i=0; i<= soLuongVat; i++)
      {
        vitridat3_angle[i]=changeDToAngleCal(vitridat3_d[i]);
        Serial.println(vitridat3_d[i]);
        Serial.println(theta1[i]);
        Serial.println(theta2[i]);
        Serial.println("-----");
      }
      mode=0;
      dataReceive="";
    }
  }
}

void setHome()
{
  setHomePID();
  if(etheta3 < 5 && etheta3 > -5)
  {
    setHomeTheta2_deba();
    setHomeTheta1();
    setHomeTheta2();
  }
  mode = 254;
}

void setHomePID()
{
  while (digitalRead(limit0)!= 0)
  {   
    analogWrite(PWM3,255);
    digitalWrite(IN23, LOW);
    digitalWrite(IN13, HIGH);
    if (digitalRead(limit0)== 0)
    {
      delay(50);
      break;
      while(digitalRead(limit0)== 0);
      delay(50);
    }
  }
  resetPID();
  vitridat3_angle[0] = changeDToAngleCal(-50);
  mode = 255; // chay lai PID
}

void setHomeTheta1()
{
  digitalWrite(dir1, chieuThuan);
  while(digitalRead(limit1)!= 0) runStep1();
  gocOld1=0;
  digitalWrite(dir1, chieuNghich);
  for(long i=0; i<1550; i++) runStep1();
}

void setHomeTheta2()
{
  digitalWrite(dir2, chieuNghich);
  while(digitalRead(limit2)!= 0) runStep2();
  gocOld2=0;
  step2[0]=stepPulseCal2((139-gocOld1));
  for(long i=0; i<step2[0]-5; i++) runStep2();
  gocOld2=0;
}

void setHomeTheta2_deba()
{
  if((gocOld2 < 0) && (soLuongVat != 0)) 
  {
    step2[0]=stepPulseCal2(0);
    for(long i=0; i<step2[0]; i++) runStep2();
  }
}

void hutVat()
{
  delay(500);
  digitalWrite(magnet, HIGH);
  delay(500);
}

void thaVat()
{
  delay(500);
  digitalWrite(magnet, LOW);
  delay(500);
}

double stepPulseCal1(double thetaStep)
{
  double gocCal = -(gocOld1) + thetaStep;
  gocOld1 = thetaStep;

  if(gocCal >= 0) digitalWrite(dir1, chieuThuan);
  else digitalWrite(dir1, chieuNghich);
  
  gocCal  = abs(gocCal );
  return (gocCal /(1.8))*16*80/60; // che do 1/16 step, ti so 2 pully bi dong/chu dong: 80/60
}

double stepPulseCal2(double thetaStep)
{
  double gocCal = -(gocOld2) + thetaStep;
  gocOld2 = thetaStep;

  if(gocCal >= 0) digitalWrite(dir2, chieuThuan);
  else digitalWrite(dir2, chieuNghich);
  
  gocCal  = abs(gocCal );
  return (gocCal /(1.8))*16*80/60; // che do 1/16 step, ti so 2 pully bi dong/chu dong: 80/60
}

double changeDToAngleCal(double d)
{
  return -d*45;
}

void resetPID()
{
  pulse_theta3=0;
  etheta_dd3 = 0; etheta_d3 = 0;  etheta3 = 0;
  Output3 = 0;
  Outputlast3 = 0;
  bienDone=0;
  vitridat3Old=0;
}

void runStep1()
{
  digitalWrite(tep1,HIGH); 
  delayMicroseconds(delayStep);  
  digitalWrite(tep1,LOW); 
  delayMicroseconds(delayStep);
}

void runStep2()
{
  digitalWrite(tep2,HIGH); 
  delayMicroseconds(delayStep);  
  digitalWrite(tep2,LOW); 
  delayMicroseconds(delayStep);
}

void read_encoder3() 
{
    static int8_t lookup_table[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};
    static uint8_t enc_val = 0;

    enc_val = (enc_val << 2);
    enc_val = ((digitalRead(20)<<1|enc_val|digitalRead(21))&0x0f);

    pulse_theta3 = pulse_theta3 + lookup_table[enc_val];
} 

String getValue(String data, char separator, int index) 
{
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length() - 1;
  
  for (int i = 0; i <= maxIndex && found <= index; i++) 
  {
    if (data.charAt(i) == separator || i == maxIndex) 
    {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
