//Motor A control pan 
//Motor B control tilt
//Use WASD to control move :
//W: tilt upward,
//S: tilt downward
//A: pan left
//D: pan right


// Motor A 
 
int enA = 9;
int in1 = 8;
int in2 = 7;
 
// Motor B
 
int enB = 3;
int in3 = 5;
int in4 = 4;
 
void setup()
 
{
 
  // Set all the motor control pins to outputs
 
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
}


void loop() {
        char input;
        // send data only when you receive data:
        //if (Serial.available() > 0) {
                // read the incoming byte:
                input = Serial.read();
                if(input == 'w' || input == 'a' || input == 's' || input == 'd'){
                  if(input == 'a'){//Pan Left (Motor A)
                     digitalWrite(in1, HIGH);
                     digitalWrite(in2, LOW);
                     analogWrite(enA, 200);
                     delay(500);
                     Serial.print("I received: ");
                     Serial.println(input);
                     digitalWrite(in1, LOW); //turn off the motors
                     digitalWrite(in2, LOW);
                   }
                   if(input == 'd'){//Pan right (Motor A)
                     digitalWrite(in1, LOW);
                     digitalWrite(in2, HIGH);
                     analogWrite(enA, 200);
                     delay(500);
                     Serial.print("I received: ");
                     Serial.println(input);
                     digitalWrite(in1, LOW); //turn off the motors
                     digitalWrite(in2, LOW);
                    }
                   if(input == 'w'){//tilt up (Motor B)
                     digitalWrite(in3, HIGH);
                     digitalWrite(in4, LOW);
                     analogWrite(enB, 200);
                     delay(500);
                     Serial.print("I received: ");
                     Serial.println(input);
                     digitalWrite(in3, LOW); //turn off the motors
                     digitalWrite(in4, LOW);
                    }
                   if(input == 's'){//tilt down (Motor B)
                     digitalWrite(in3, LOW);
                     digitalWrite(in4, HIGH);
                     analogWrite(enB, 200);
                     delay(500);
                     Serial.print("I received: ");
                     Serial.println(input);
                     digitalWrite(in3, LOW); //turn off the motors
                     digitalWrite(in4, LOW);
                    }              
                }else{Serial.println("wrong ");}
        //}
}
//w: 119 10
//a: 97 10
//s: 115 10
//d: 100 10
