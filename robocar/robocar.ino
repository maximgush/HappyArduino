// подключите пины контроллера к цифровым пинам Arduino

// первый двигатель
int in1 = 14;
int in2 = 12;

// второй двигатель
int in3 = 13;
int in4 = 15;

int velocityMove = 500;
int velocityTurn = 1020;

void setup()
{
  // инициализируем все пины для управления двигателями как outputs
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void MoveForward()
{
  digitalWrite(in1, LOW);
  analogWrite(in2, velocityMove);
  digitalWrite(in3, LOW);
  analogWrite(in4, velocityMove);
}

void MoveBackward()
{
  digitalWrite(in1, HIGH);
  analogWrite(in2, velocityMove);  
  digitalWrite(in3, HIGH);
  analogWrite(in4, velocityMove);
}

void TurnLeft()
{
  digitalWrite(in1, LOW);
  analogWrite(in2, velocityTurn); 
  digitalWrite(in3, HIGH);
  analogWrite(in4, velocityTurn);
}
void TurnRight()
{
  digitalWrite(in1, HIGH);
  analogWrite(in2, velocityTurn); 
  digitalWrite(in3, LOW);
  analogWrite(in4, velocityTurn);
}

void Stop(int t)
{
  digitalWrite(in1, LOW);
  analogWrite(in2, 0); 
  digitalWrite(in3, LOW);
  analogWrite(in4, 0);
  delay(t);
}

void loop()
{
  Stop(5000);
  
  MoveForward(); 
  delay(3000); 

  Stop(1000);
  
  TurnRight(); 
  delay(1000);

  Stop(1000);  

  MoveForward(); 
  delay(3000); 

  Stop(1000);

  MoveBackward(); 
  delay(3000); 

  Stop(1000);

  TurnLeft(); 
  delay(1000);

  Stop(1000);
  
  MoveBackward(); 
  delay(3000); 

  
  /*delay(1000);
  demoTwo();
  delay(1000);*/
}
