#define RXPIN 5
#define TXPIN 4

#define DDPIN 5

SoftwareSerial Roomba(RXPIN, TXPIN);

void wakeUp (void)
{
  digitalWrite(DDPIN, HIGH);
  delay(100);
  digitalWrite(DDPIN, LOW);
  delay(500);
  digitalWrite(DDPIN, HIGH);
  delay(2000);
}

void startSafe()
{  
  Roomba.write(128);  //Start
  Roomba.write(131);  //Safe mode
  delay(1000);
}

void playSound (int num) 
{
  switch (num)
  { 
    case 1: 
      Roomba.write("\x8c\x01\x04\x42\x20\x3e\x20\x42\x20\x3e\x20"); // [140] [1] [4] [68] [32] ... place "start sound" in slot 1
      Roomba.write("\x8d\x01"); // [141] [1] play it (in slot 1)
      break;
 
    case 2: 
      Roomba.write("\x8c\x01\x01\x3c\x20"); // place "low freq sound" in slot 2
      Roomba.write("\x8d\x01"); // play it (in slot 2)
      break;

    case 3:
      Roomba.write("\x8c\x01\x01\x48\x20"); // place "high freq sound" in slot 3
      Roomba.write("\x8d\x01"); // play it (in slot 3)
      break;
  }
}

void drive(int right, int left)
{
  right = constrain(right, -500, 500);
  left = constrain(left, -500, 500);

  Roomba.write(145);
  Roomba.write(right >> 8);
  Roomba.write(right);
  Roomba.write(left >> 8);
  Roomba.write(left);
}