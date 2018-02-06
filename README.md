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

in this coding type we follow right wall following rule and also the bot can remember its previous decision
like north east west south we have 0,1,2,3 for direction.
and in every turn it changes its orientation values according to its real orientation and saves the data to the pos[100][4]
2-D array for every point of time of making decision.
noOfPoints saves the points of making decision and increment every time.
Some cases like for going back to previous point "back" is incremented and the pos values changes according to it
