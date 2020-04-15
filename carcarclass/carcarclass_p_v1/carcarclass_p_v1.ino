int motor1 = 2;//左
int motor1r = 4;
int motor2 = 8;//右
int motor2r = 7;
int EN_L = 5;
int EN_R = 6;
bool IRstat[6]={};
void setup() {
  // put your setup code here, to run once:
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  pinMode(A4,INPUT);
  pinMode(A5,INPUT);
  pinMode(motor1, OUTPUT); 
  pinMode(motor1r, OUTPUT); 
  pinMode(motor2, OUTPUT); 
  pinMode(motor2r, OUTPUT);
  pinMode(EN_L, OUTPUT);
  pinMode(EN_R,OUTPUT);
  Serial.begin(9600);
}
void direct(){
  float vR=109,vL=112;
  int back=0;
  int IRraw[6]={};
  double location=0;
  IRraw[0] = analogRead(A0);
  IRraw[1] = analogRead(A1);
  IRraw[2] = analogRead(A2);
  IRraw[3] = analogRead(A3);
  IRraw[4] = analogRead(A4);
  IRraw[5] = analogRead(A5);
  
  for(int i=0;i<6;i++){
    if(IRraw[i]>100){
      IRstat[i]=1;
      back++;
    }
    else{
      IRstat[i]=0;
    }
    Serial.print(IRstat[i]);
    Serial.print(" / ");
  }
  Serial.print("      ");
  /*Serial.print(IRraw[0]);
  Serial.print(" / ");
  Serial.print(IRraw[1]);
  Serial.print(" / ");
  Serial.print(IRraw[2]);
  Serial.print(" / ");
  Serial.print(IRraw[3]);
  Serial.print(" / ");
  Serial.print(IRraw[4]);
  Serial.print(" / ");
  Serial.println(IRraw[5]);*/
  if(back==0){
    location=0;
    vL=-89;
    vR=-87;
  }
  else{
  location = (-5*IRstat[0]-3*IRstat[1]-1*IRstat[2]+1*IRstat[3]+3*IRstat[4]+5*IRstat[5])/(IRstat[0]+IRstat[1]+IRstat[2]+IRstat[3]+IRstat[4]+IRstat[5]);
  location=location/5;
  }
  vL+=90*location;
  vR-=90*location;
  MotorWriting(vL,vR);
  Serial.print(vL);
  Serial.print(" / ");
  Serial.println(vR);
  
}
void MotorWriting(double vL,double vR){
  vR=int(vR);
  vL=int(vL);
  if(vL>=0){
    digitalWrite(motor1,HIGH);
    digitalWrite(motor1r,LOW);
  }
  else{
    digitalWrite(motor1,LOW);
    digitalWrite(motor1r,HIGH);
    vL=-vL;
  }
  if(vR>=0){
    digitalWrite(motor2,HIGH);
    digitalWrite(motor2r,LOW);
  }
  else{
    digitalWrite(motor2,LOW);
    digitalWrite(motor2r,HIGH);
    vR=-vR;
  }
  analogWrite(EN_R,vR);
  analogWrite(EN_L,vL);
}

/*void IRvalues(int IRraw[]){
  Serial.print(IRraw[0]);
  Serial.print(" / ");
  Serial.print(IRraw[1]);
  Serial.print(" / ");
  Serial.print(IRraw[2]);
  Serial.print(" / ");
  Serial.print(IRraw[3]);
  Serial.print(" / ");
  Serial.print(IRraw[4]);
  Serial.print(" / ");
  Serial.println(IRraw[5]);
}*/
void loop() {
  // put your main code here, to run repeatedly:
  direct();
  //IRvalues(*IRraw);
  delay(50);
}
