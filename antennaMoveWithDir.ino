
//Motor prev control pan 
//Motor curr control tilt
//Use WprevSD to control move :
//W: tilt upward,
//S: tilt downward
//prev: pan left
//D: pan right


// Motor prev 
 
int enA = 9;
int in1 = 8;
int in2 = 7;
 
// Motor curr
 
int enB = 3;
int in3 = 5;
int in4 = 4;

// Coordinates
float robotPos[2] = {1,1};
float groundPos[2] = {0,0};   //this will remain the same
float prev[2]={1.0,1.0};
float curr[2]={2.0,1.0};
float dTheta = 0.0;
float dPhi = 0.0;
float temp = 0.0;
int dirPan  = 1;
int dirTilt = 0;

void setup(){
 
  // Set all the motor control pins to outputs
 
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
}

void updatePos(char in){
  prev[0] = robotPos[0];
  prev[1] = robotPos[1];
  if(in == 'i' || in == 'j' || in == 'k' || in == 'l'){
    if(in == 'i'){//Pan Left (Motor prev)
       robotPos[1]+=1.0;
     }
     else if(in == 'j'){//Pan right (Motor prev)
      robotPos[0]-=1.0;
      }
     else if(in == 'k'){//tilt up (Motor curr)
       robotPos[1]-=1.0;
      }
     else if(in == 'l'){//tilt down (Motor curr)
       robotPos[0]+=1.0;
      }       
      
      //Serial.print("I received: ");
      Serial.print("x:");
      Serial.println(robotPos[0]); 
      Serial.print("\n y:");
      Serial.println(robotPos[1]); 
      
  }
  curr[0] = robotPos[0];
  curr[1] = robotPos[1];
        
  delay(500);
}

float mag(float vec[2]){
  return sqrt(vec[0]*vec[0]+vec[1]*vec[1]);
}
void updatedirPan(){
  if (0<curr[0]/prev[0]-curr[1]/prev[1]>0.5){
    if (curr[0]-prev[0]<=0 && curr[1]-prev[1]>=0){
      dirPan = -1;                                  // anticlockwise
    }else if (curr[0]-prev[0]>=0 && curr[1]-prev[1]<=0){
      dirPan = 1;                                   // clockwise
    }
  }
  //float mag = sqrt(curr);
  if (0<curr[0]/prev[0]-curr[1]/prev[1]<0.5){
    //dirPan =0;   // do not change the pan direction
    if ((curr[0]-prev[0])>0 or (curr[1]-prev[1])>0){
      dirTilt = 1;                                  // up
    }else if ((curr[0]-prev[0])<0 or (curr[1]-prev[1])<0){
      dirTilt = -1;                                 // down
    }
  }
}

void loop() {
        char input;
        
        /*get robotPos
        do robotPos-groundPos = prev
        delay_ms
        do robotPos - groundPos = curr
        do acos(-(curr0*prev0+curr1*prev1)/(sqrt(curr0^2+curr1^2)*sqrt(prev0^2+prev1^2)))
        deltaTheta = -()
        0.007874 m/s
        */

        temp = ((curr[0]*prev[0]+curr[1]*prev[1])/(sqrt(curr[0]*curr[0]+curr[1]*curr[1])*sqrt(prev[0]*prev[0]+prev[1]*prev[1])));
        dTheta = acos(temp);
        dPhi = atan(2.0/(robotPos[0]*robotPos[0]+robotPos[1]*robotPos[1]));
        
        // send data only when you receive data:
        if (Serial.available() > 0) {
                // read the incoming byte:
                input = Serial.read();

                updatePos(input);
                updatedirPan();
                Serial.print("dirPan");
                Serial.println(dirPan);
                Serial.print("dirTilt");
                Serial.println(dirTilt);
                if(input == 'w' || dirPan == 1 || input == 's' || dirPan == -1){
                  if(dirPan == -1){//Pan Left (Motor prev)
                     digitalWrite(in1, HIGH);
                     digitalWrite(in2, LOW);
                     analogWrite(enA, 200);
                     delay(500);
                     Serial.print("I received:a");
                     digitalWrite(in1, LOW); //turn off the motors
                     digitalWrite(in2, LOW);
                   }
                   if(dirPan==1){//Pan right (Motor prev)
                     digitalWrite(in1, LOW);
                     digitalWrite(in2, HIGH);
                     analogWrite(enA, 200);
                     delay(500);
                     Serial.print("I received:d ");
                     digitalWrite(in1, LOW); //turn off the motors
                     digitalWrite(in2, LOW);
                    }
                   if(input == 'w'){//tilt up (Motor curr)
                     digitalWrite(in3, HIGH);
                     digitalWrite(in4, LOW);
                     analogWrite(enB, 200);
                     delay(500);
                     Serial.print("I received:");
                     Serial.println(input);
                     digitalWrite(in3, LOW); //turn off the motors
                     digitalWrite(in4, LOW);
                    }
                   if(input == 's'){//tilt down (Motor curr)
                     digitalWrite(in3, LOW);
                     digitalWrite(in4, HIGH);
                     analogWrite(enB, 200);
                     delay(500);
                     Serial.print("I received:");
                     Serial.println(input);
                     digitalWrite(in3, LOW); //turn off the motors
                     digitalWrite(in4, LOW);
                    }              
                }else{Serial.println("wrong ");}
        }
}
//w: 119 10
//a: 97 10
//s: 115 10
//d: 100 10
