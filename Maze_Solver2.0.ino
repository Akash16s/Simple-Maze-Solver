const int trigPinF=13,echoPinF=12,trigPinR=11,echoPinR=10,trigPinL=9,echoPinL=8; //Ultrasonic Pins
const int rightUp=7,rightDown=6,leftUp=5,leftDown=4;                             //Motor Pins 
int orientation=0;                                                                                           /* 0
                                                                                                             2     1

                                                                                                                3*/
int walldistance=5,walldistanceMin=3;
int initial=0,noOfPoint=0;         
int pos[100][4];                              //1=persent not searched and 0 = searched
int back=0;
void setup() {
  pinMode(trigPinF,OUTPUT);
  pinMode(echoPinF,INPUT);
  pinMode(trigPinR,OUTPUT);
  pinMode(echoPinR,INPUT);
  pinMode(trigPinL,OUTPUT);
  pinMode(echoPinL,INPUT);
  pinMode(rightUp,OUTPUT);
  pinMode(rightDown,OUTPUT);
  pinMode(leftUp,OUTPUT);
  pinMode(leftDown,OUTPUT);

}

void loop() {
  delay(2000);   //for 2 seconds delay for intial movement
  forwards();
  if(distance(trigPinR,echoPinR)<walldistanceMin){
  analogWrite(rightUp,100);                   //rightwards movement
  digitalWrite(rightDown,LOW);
  analogWrite(leftUp,50);
  digitalWrite(leftDown,LOW);
  }
  if(distance(trigPinL,echoPinL)<walldistanceMin){
  analogWrite(rightUp,50);                   //leftwards movement
  digitalWrite(rightDown,LOW);
  analogWrite(leftUp,100);
  digitalWrite(leftDown,LOW);
 
  }
  forwards();
  if(back==1){ 
    backwardAlgo();
    }
  else{
  long distanceF=distance(trigPinF,echoPinF);
  long distanceR=distance(trigPinR,echoPinR);
  long distanceL=distance(trigPinL,echoPinL);
  if(distanceF>walldistance && distanceR>walldistance && distanceL>walldistance) allClear();
  else if (distanceF<walldistance && distanceR>walldistance && distanceL>walldistance) exceptForward();
  else if (distanceF>walldistance && distanceR>walldistance && distanceL<walldistance) exceptLeft();
  else if(distanceF>walldistance && distanceR<walldistance && distanceL>walldistance) exceptRight();
  else if(distanceF<walldistance && distanceR>walldistance && distanceL<walldistance)  onlyRight();
  else if (distanceF<walldistance && distanceR<walldistance && distanceL>walldistance) onlyLeft();
  else if (distanceF<walldistance && distanceR<walldistance && distanceL<walldistance) backMove();
  }
  }


 


//The Distance function
long distance(int trigPin,int echoPin)
{// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
long duration = pulseIn(echoPin, HIGH);
long distance= duration*0.034/2;
return distance;
}


void allClear(){                                //in this case all three sides are free
  noOfPoint++;
 switch(orientation){
  case 0: {pos[noOfPoint][0]=1;
          pos[noOfPoint][1]=0;
          pos[noOfPoint][2]=1;
          pos[noOfPoint][3]=0;}break;
  case 1:{pos[noOfPoint][0]=1;
          pos[noOfPoint][1]=1;
          pos[noOfPoint][2]=0;
          pos[noOfPoint][3]=0;}break;
  case 2:{pos[noOfPoint][0]=0;
          pos[noOfPoint][1]=0;
          pos[noOfPoint][2]=1;
          pos[noOfPoint][3]=1;}break;
  case 3:{pos[noOfPoint][0]=0;
          pos[noOfPoint][1]=1;
          pos[noOfPoint][2]=0;
          pos[noOfPoint][3]=1;}break;
 }
  rightwards();
  if(orientation==3) orientation=0;                     //this is orientation designator
  else orientation++;
  }

void exceptForward(){
 noOfPoint++;
 switch(orientation){
  case 0: {pos[noOfPoint][0]=0;
          pos[noOfPoint][1]=0;
          pos[noOfPoint][2]=1;
          pos[noOfPoint][3]=0;}break;
  case 1:{pos[noOfPoint][0]=1;
          pos[noOfPoint][1]=0;
          pos[noOfPoint][2]=0;
          pos[noOfPoint][3]=0;}break;
  case 2:{pos[noOfPoint][0]=0;
          pos[noOfPoint][1]=0;
          pos[noOfPoint][2]=0;
          pos[noOfPoint][3]=1;}break;
  case 3:{pos[noOfPoint][0]=0;
          pos[noOfPoint][1]=1;
          pos[noOfPoint][2]=0;
          pos[noOfPoint][3]=0;}break;
      }  
  rightwards();
  if(orientation==3) orientation=0;                     //this is orientation designator
  else orientation++;
}

void exceptLeft(){
  noOfPoint++;
  switch(orientation){
  case 0: {pos[noOfPoint][0]=1;
          pos[noOfPoint][1]=0;
          pos[noOfPoint][2]=0;
          pos[noOfPoint][3]=0;}break;
  case 1:{pos[noOfPoint][0]=0;
          pos[noOfPoint][1]=1;
          pos[noOfPoint][2]=0;
          pos[noOfPoint][3]=0;}break;
  case 2:{pos[noOfPoint][0]=0;
          pos[noOfPoint][1]=0;
          pos[noOfPoint][2]=2;
          pos[noOfPoint][3]=0;}break;
  case 3:{pos[noOfPoint][0]=0;
          pos[noOfPoint][1]=0;
          pos[noOfPoint][2]=0;
          pos[noOfPoint][3]=3;}break;
      }  
  rightwards();
  if(orientation==3) orientation=0;                     //this is orientation designator
  else orientation++;
 }

 void exceptRight(){
  noOfPoint++;
  switch(orientation){
  case 0: {pos[noOfPoint][0]=0;
          pos[noOfPoint][1]=0;
          pos[noOfPoint][2]=1;
          pos[noOfPoint][3]=0;}break;
  case 1:{pos[noOfPoint][0]=1;
          pos[noOfPoint][1]=0;
          pos[noOfPoint][2]=0;
          pos[noOfPoint][3]=0;}break;
  case 2:{pos[noOfPoint][0]=0;
          pos[noOfPoint][1]=0;
          pos[noOfPoint][2]=0;
          pos[noOfPoint][3]=1;}break;
  case 3:{pos[noOfPoint][0]=0;
          pos[noOfPoint][1]=1;
          pos[noOfPoint][2]=0;
          pos[noOfPoint][3]=0;}break;
      }  
  forwards();
  if(orientation==3) orientation=0;                     //this is orientation designator
  else orientation++;
 }

void onlyRight(){
  rightwards();
  if(orientation==3) orientation=0;                     //this is orientation designator
  else orientation++;
 }

 
void onlyLeft(){
  leftwards();
  if(orientation==3) orientation=0;                     //this is orientation designator
  else orientation--;
 }

void backMove(){
   back=1;
  switch(orientation){
    case 0: orientation=3; break;
    case 1: orientation=2; break;
    case 2:orientation=1; break;
    case 3:orientation=0; break;
    }
  backwards();
  forwards();
   }

void backwardAlgo(){                                                  //this is for backward direction
  int f,r,l,b;
  pos[noOfPoint][0]=f;
  pos[noOfPoint][1]=r;
  pos[noOfPoint][2]=l;
  pos[noOfPoint][3]=b;
  switch(orientation){
    case 0: if(f==1&&r==1&&l==1){
             rightwards();
             pos[noOfPoint][1]=0;
             }
             else if(f==0&&r==1&&l==1){
              rightwards();
              pos[noOfPoint][1]=0;
             }
             else if(f==1&&r==0&&l==1){
              forwards();
              pos[noOfPoint][0]=0;
             }
             else if(f==1&&r==1&&l==0){
              forwards();
              pos[noOfPoint][0]=0;
             }
             else if(f==1&&r==0&&l==0){
              forwards();
              pos[noOfPoint][0]=0;
             }
             else if(f==0&&r==1&&l==0){
              rightwards();
              pos[noOfPoint][1]=0;
              }
             else if(f==0&&r==0&&l==1){
              leftwards();
              pos[noOfPoint][2]=0;
             }
             break;
     case 1: if(f==1&&r==1&&b==1){
             rightwards();
             pos[noOfPoint][3]=0;
             }
             else if(f==0&&r==1&&b==1){
              rightwards();
              pos[noOfPoint][3]=0;
             }
             else if(f==1&&r==0&&b==1){
              rightwards();
              pos[noOfPoint][3]=0;
             }
             else if(f==1&&r==1&&b==0){
              forwards();
              pos[noOfPoint][1]=0;
             }
             else if(f==1&&r==0&&b==0){
              leftwards();
              pos[noOfPoint][0]=0;
             }
             else if(f==0&&r==1&&b==0){
              forwards();
              pos[noOfPoint][1]=0;
              }
             else if(f==0&&r==0&&b==1){
              rightwards();
              pos[noOfPoint][3]=0;
             }
             break;
     case 2: if(f==1&&l==1&&b==1){
             rightwards();
             pos[noOfPoint][0]=0;
             }
             else if(f==0&&l==1&&b==1){
              forwards();
              pos[noOfPoint][2]=0;
             }
             else if(f==1&&l==0&&b==1){
              rightwards();
              pos[noOfPoint][0]=0;
             }
             else if(f==1&&l==1&&b==0){
              rightwards();
              pos[noOfPoint][0]=0;
             }
             else if(f==1&&l==0&&b==0){
              rightwards();
              pos[noOfPoint][0]=0;
             }
             else if(f==0&&l==1&&b==0){
              forwards();
              pos[noOfPoint][2]=0;
              }
             else if(f==0&&l==0&&b==1){
              leftwards();
              pos[noOfPoint][3]=0;
             }
             break;
    case 3: if(r==1&&l==1&&b==1){
             rightwards();
             pos[noOfPoint][2]=0;
             }
             else if(r==0&&l==1&&b==1){
              rightwards();
              pos[noOfPoint][2]=0;
             }
             else if(r==1&&l==0&&b==1){
              forwards();
              pos[noOfPoint][3]=0;
             }
             else if(r==1&&l==1&&b==0){
              rightwards();
              pos[noOfPoint][2]=0;
             }
             else if(r==1&&l==0&&b==0){
              leftwards();
              pos[noOfPoint][1]=0;
             }
             else if(r==0&&l==1&&b==0){
              rightwards();
              pos[noOfPoint][2]=0;
              }
             else if(r==0&&l==0&&b==1){
              forwards();
              pos[noOfPoint][3]=0;
             }
             break;
       }
  
  }







 //All Movement 
 void rightwards()
 {
  analogWrite(rightUp,75);                   //rightwards movement till delay
  analogWrite(rightDown,LOW);
  analogWrite(leftUp,LOW);
  digitalWrite(leftDown,75);
  delay(2000);
  digitalWrite(rightUp,LOW);
  digitalWrite(rightDown,LOW);
  digitalWrite(leftUp,LOW);
  digitalWrite(leftDown,LOW);
 }
 void forwards()
{
    analogWrite(rightUp,75);                 
  analogWrite(rightDown,LOW);
  analogWrite(leftUp,25);
  digitalWrite(leftDown,LOW);
}
void leftwards(){
  analogWrite(rightUp,LOW);                //leftwards          
  analogWrite(rightDown,75);
  analogWrite(leftUp,75);
  analogWrite(leftDown,LOW);
  delay(2000);
  digitalWrite(rightUp,LOW);
  digitalWrite(rightDown,LOW);
  digitalWrite(leftUp,LOW);
  digitalWrite(leftDown,LOW);
  
}

void backwards()
 {
 analogWrite(rightUp,75);                   //rightwards movement till delay
  analogWrite(rightDown,LOW);
  analogWrite(leftUp,LOW);
  digitalWrite(leftDown,75);
  delay(8000);
  digitalWrite(rightUp,LOW);
  digitalWrite(rightDown,LOW);
  digitalWrite(leftUp,LOW);
  digitalWrite(leftDown,LOW);
 }


