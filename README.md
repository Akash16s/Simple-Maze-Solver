# Simple-Maze-Solver
Simple Maze solver which remember its previous move
#previous initialisation
const int trigPinF=13,echoPinF=12,trigPinR=11,echoPinR=10,trigPinL=9,echoPinL=8; //Ultrasonic Pins
const int rightUp=7,rightDown=6,leftUp=5,leftDown=4;                             //Motor Pins 
int orientation=0;  //this tells us about orientation                                               0
                                                                                                 2     1  this is the direction                 
                                                                                                    3
int walldistance=5,walldistanceMin=3;
int initial=0,noOfPoint=0;         
int pos[100][4];                              //1=persent not searched and 0 = searched
int back=0;
