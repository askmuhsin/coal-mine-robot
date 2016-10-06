
int MQ4 = 0;    //gas sensor 1 BLUE
int MQ9 = 0;    //gas sensor 2 YELLOW
int LM35 = 0;   //temperature sensor GREEN

int inByte = 0;  

const int Motor1Pin1 = 7;
const int Motor1Pin2 = 9;
const int Motor2Pin1 = 10;
const int Motor2Pin2 = 11;

#define trigPin 13
#define echoPin 12

const int Buzzer = 5;

int x,tempC = 0,check,sum=0,i[500];

const int buttonPin = 6;
int buttonState = 0 ; 

void setup()
{                
  Serial.begin(9600);
  pinMode(Motor1Pin1, OUTPUT);   
  pinMode(Motor1Pin2, OUTPUT);   
  pinMode(Motor2Pin1, OUTPUT);   
  pinMode(Motor2Pin2, OUTPUT); 
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);  
  pinMode(Buzzer, OUTPUT);
  pinMode(buttonPin, INPUT);
}


void loop()
 {  
   
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) 
  {     
    processingSwitch(); 
  } 
  
  if (buttonState == LOW)
  {
      long duration, distance;
      digitalWrite(trigPin, LOW);  
      delayMicroseconds(2); 
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10); 
      digitalWrite(trigPin, LOW);
      duration = pulseIn(echoPin, HIGH);
      distance = (duration/2) / 29.1;
  
 
  
if (distance>9)
  {
   
    GoForward();
    survOn();
  
  }
  
else
  
  {
   
    GoBackward();
    delay(700);
    GoLeft();
    delay(800);
 
  }
  }
 }
    
          


 void GoForward()
{
  digitalWrite(Motor1Pin2, LOW);
  digitalWrite(Motor1Pin1, HIGH);
  digitalWrite(Motor2Pin1, LOW);
  digitalWrite(Motor2Pin2, HIGH);
}
  
  void GoBackward()
  {
  digitalWrite(Motor1Pin1, LOW);
  digitalWrite(Motor1Pin2, HIGH);
  digitalWrite(Motor2Pin2, LOW);
  digitalWrite(Motor2Pin1, HIGH);
  }
  
  void GoRight()
  {
  digitalWrite(Motor1Pin2, LOW);
  digitalWrite(Motor1Pin1, HIGH);
  digitalWrite(Motor2Pin2, LOW);
  digitalWrite(Motor2Pin1, HIGH);
  }

 void GoLeft()
 {
  digitalWrite(Motor1Pin1, LOW);
  digitalWrite(Motor1Pin2, HIGH);
  digitalWrite(Motor2Pin1, LOW);
  digitalWrite(Motor2Pin2, HIGH);
 }
 
 void Stop()
 {
  digitalWrite(Motor1Pin2, LOW);
  digitalWrite(Motor1Pin1, LOW);
  digitalWrite(Motor2Pin1, LOW);
  digitalWrite(Motor2Pin2, LOW);
 }
 
 void survOn()
{
            // get incoming byte:
            inByte = Serial.read();
            
            // read  the value from LM35
            //for (int x=0; x<500;x++)
            //{
              LM35 = analogRead(A0);  
              //tempC = LM35;
              //i[x]=tempC;
              //sum=i[x]+sum;
            //}
            //LM35=sum/500;
            
            // read Methane, CNG Gas input:
            //for (int x=0; x<500;x++)
            //{
              MQ4  = analogRead(A1);  
              //tempC = MQ4;
              //i[x]=tempC;
              //sum=i[x]+sum;
            //}
            //MQ4=sum/500;
            
            // read  Carbon Monoxide, flammable gasses input:
            //for (int x=0; x<500;x++)
            //{
              MQ9  = analogRead(A2);  
              //tempC = MQ9;
              //i[x]=tempC;
              //sum=i[x]+sum;
            //}
            //MQ9=sum/500;
            
            // send sensor values:
            LM35 = (5.0 * LM35 * 100.0) / 1024;
     
      if (MQ4<500 && MQ9<100 && LM35<45)
      {
        digitalWrite(Buzzer,LOW);
        allsafe();
        
        delay(1000); 
      }
      else
      {
        //allsafe();
        digitalWrite(Buzzer,HIGH);
        sensor1();
        sensor2();
        sensor3();
        
        delay(1000); 
      }
        
           
}


void allsafe()
{
            Serial.print(MQ4);
            Serial.print(" -   Methane, CNG Gas||||");
            Serial.print(MQ9);
            Serial.print(" -   Carbon Monoxide, Flammable gas||||");
            Serial.print(LM35); 
            Serial.println("°C||||");
            Serial.println("  All Safe    All Safe    All Safe    All Safe    All Safe    All Safe    All Safe  ");           
              
}

void sensor1()
{           
            Serial.print(MQ4);
            Serial.print(" -   Methane, CNG Gas  ");
            if(MQ4>500)
            {
               Serial.println("  MAYDAY!!!!!!! Methane, CNG Gas level ALARMING");
            }
}

void sensor2()
{
            Serial.print(MQ9);
            Serial.print(" -   Carbon Monoxide, Flammable gasses  ");
            if(MQ9>100)
            {
               Serial.println("  MAYDAY!!!!!!! Carbon Monoxide, Flammable gasses level ALARMING");
            }
}

void sensor3()
{
            Serial.print(LM35);
            Serial.print(" °C  ");
            if(LM35>40)
            {
               Serial.println("  MAYDAY!!!!!!! Temperature level ALARMING");
            }
}


void processingSwitch()
{
    LM35 = analogRead(A0);
    LM35 = (5.0 * LM35 * 100.0) / 1024;
    Serial.println(LM35);
    delay(100);
    if(LM35>=45)
    {
      digitalWrite(Buzzer,HIGH);
    }
    else
    {
     digitalWrite(Buzzer,LOW);
    }
}

