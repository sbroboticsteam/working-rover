#define SizeOfMessage 3                     //The size of the message to be received.
#define SizeOfData 3                        //The number of data bytes.
byte message[SizeOfMessage];                  //This is where the massage to be received will be stored.
byte data[SizeOfData];                        //This is where the data will be stored.
//The data is stored in the following format:
//data[0] is the direction pad, up
//data[1] is the direction pad, down
//data[2] is the direction pad, left
//data[3] is the direction pad, right
//data[4] is the start button
//data[5] is the back button
//data[6] is the left joystick button
//data[7] is the right joystick button
//data[8] is the left button (above the left bumper)
//data[9] is the right button (above the right bumper)
//data[10] is the A button
//data[11] is the B button
//data[12] is the X button
//data[13] is the Y button
//data[14] is the left joystick x axis value (128 is center, 0 is all the way to the right, 255 is all the way to the left)
//data[15] is the left joystick y axis value (128 is center, 0 is all the way down, 255 is all the way up)
//data[16] is the right joystick x axis value (128 is center, 0 is all the way to the right, 255 is all the way to the left)
//data[17] is the right joystick y axis value (128 is center, 0 is all the way down, 255 is all the way up)
//data[18] is the left bumper analog value (0 is not pressed, 255 is pressed all the way)
//data[19] is the right bumper analog value (0 is not pressed, 255 is pressed all the way)

//The following issues could arise (and the causes of those issues):
//1) The joystick values may only go down to 1 instead of 0 (clever rounding of a float to a byte to make easy data transmission)
//2) The joystick values may not reset to 128 if you let go of the stick (this is due to a mechanical issue in the controller;
//                                                                        I tried to add a deadzone, but it only covers part of the issue)
//3) There may be a very small lag if you spam all the inputs (I'm not sure where it's coming from, but I got rid of most of it;
//                                                              it should be so small you'd barely notice it, but if it's too much let me know)

//As far as I have tested, those are the only issues I see. If you find more, let me know.
//This code is given to you by Sasha, the Electrical Team Lead. If it ain't working, tell me: I'll fix it.
//                                                                If you ain't using it, I won't fix your shit, so GLHF.

const int leftFrontSpeed = 3;
const int leftFrontDir = 2;
const int leftBackSpeed = 6;
const int leftBackDir = 4;
const int rightFrontSpeed = 9;
const int rightFrontDir = 8;
const int rightBackSpeed = 11;
const int rightBackDir = 12; 
void setup() 
{
  Serial.begin(115200);
  pinMode(leftFrontSpeed, OUTPUT);
  pinMode(leftFrontDir, OUTPUT);
  pinMode(leftBackSpeed, OUTPUT);
  pinMode(leftBackDir, OUTPUT);
  pinMode(rightFrontSpeed, OUTPUT);
  pinMode(rightFrontDir, OUTPUT);
  pinMode(rightBackSpeed, OUTPUT);
  pinMode(rightBackDir, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop()  
{
  Serial.flush();
  delay(10);                                  //This is to let data get in. Should not have any noticable performace issues.

  if(Serial.available())
  {
    while(Serial.available())                //From here
    {
      Serial.readBytes(message, SizeOfMessage);
    }                                         

      Serial.flush();

//      Serial.print("Received: ");
//      Serial.print("Left Y: ");
//      Serial.print(message[0]);
//      Serial.print(" Right Y: ");
//      Serial.print(message[1]);
//      Serial.print(" Brake: ");
//      Serial.println(message[2]);

      int lefty = message[0];
      int righty = message[1];
      int brake = message[2];

      if (brake == 1)
      {
        lefty = 127;
        righty = 127;
        digitalWrite(13, HIGH);
      } else {
        digitalWrite(13, LOW);
      }

      if (lefty == 127)
      {
        analogWrite(leftFrontSpeed, 0);
        analogWrite(leftBackSpeed, 0);
      } 
      else if (lefty < 127) 
      {
        analogWrite(leftFrontSpeed, map(lefty, 127, 1, 1, 255));
        analogWrite(leftBackSpeed, map(lefty, 127, 1, 1, 255));
        //Serial.print("Adjusted Left Speed: ");
        //Serial.print(map(lefty, 127, 1, 1, 255));
        digitalWrite(leftFrontDir, HIGH);
        digitalWrite(leftBackDir, LOW);
      } 
      else if (lefty > 127)
      {
        analogWrite(leftFrontSpeed, map(lefty, 129, 255, 1, 255));
        analogWrite(leftBackSpeed, map(lefty, 129, 255, 1, 255));
        //Serial.print("Adjusted Left Speed: ");
       // Serial.print(map(lefty, 129, 255, 1, 255));
        digitalWrite(leftFrontDir, LOW);
        digitalWrite(leftBackDir, HIGH);
      }

      if (righty == 127)
      {
        analogWrite(rightFrontSpeed, 0);
        analogWrite(rightBackSpeed, 0);
      } 
      else if (righty < 127) 
      {
        analogWrite(rightFrontSpeed, map(righty, 127, 1, 1, 255));
        analogWrite(rightBackSpeed, map(righty, 127, 1, 1, 255));
      //  Serial.print("Adjusted Right Speed: ");
      //  Serial.print(map(righty, 127, 1, 1, 255));
        digitalWrite(rightFrontDir, LOW);
        digitalWrite(rightBackDir, HIGH);
      } 
      else if (righty > 127)
      {
        analogWrite(rightFrontSpeed, map(righty, 129, 255, 1, 255));
        analogWrite(rightBackSpeed, map(righty, 129, 255, 1, 255));
        //Serial.print("Adjusted Right Speed: ");
        //Serial.print(map(righty, 129, 255, 1, 255));
        digitalWrite(rightFrontDir, HIGH);
        digitalWrite(rightBackDir, LOW);
      }
      
    }
    
}
