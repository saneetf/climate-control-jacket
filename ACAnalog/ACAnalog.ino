// Ver.:1.05
// Date:01-06-2017
//=====================================================================================================================
//==========================================      PIN MAPPINGS      ===================================================
//=====================================================================================================================

int tempsensor = A0;
int coolmos1 = 9;
int coolmos2 = 6;
int coolmos3 = 3;
int coolmos4 = 10;
int hotmos = 5;

//=====================================================================================================================

void setup()
{
  pinMode(coolmos1,OUTPUT);
  pinMode(coolmos2,OUTPUT);
  pinMode(coolmos3,OUTPUT);
  pinMode(coolmos4,OUTPUT);
  pinMode(hotmos,OUTPUT);
  Serial.begin(9600);
}
void loop()
{
  
  int temp=(5.0*analogRead(tempsensor)*100.0)/1024;                 //get temperature in degree celsius
  Serial.print("sensor Temp:");                                     //Print Sensor Data to Serial Monitor
  Serial.println(temp);
  
  if(temp<=20) //start heater, disable cooler ----------------------( INVERTED LOGIC )----------------------------
  {
    //Turn off Coolers
    digitalWrite(coolmos1,HIGH);
    digitalWrite(coolmos2,HIGH);
    digitalWrite(coolmos3,HIGH);
    digitalWrite(coolmos4,HIGH);

    //Turn on Heater
    temp=constrain(temp,0,20);
    analogWrite(hotmos, map(temp,0,20,128,0) );
  }
  
  else if(temp>=26) //start cooler, disable heater ----------------------( INVERTED LOGIC )----------------------------
  {
    //Turn on Coolers
    temp=constrain(temp,26,50);
    int temp2 = map(temp,26,50,128,0);
    analogWrite(coolmos1,temp2);
    analogWrite(coolmos2,temp2);
    analogWrite(coolmos3,temp2);
    analogWrite(coolmos4,temp2);
    
    //Turn off Heater
    analogWrite(hotmos,HIGH);
  }
  
  else //between temperature 20-25, disable all --------------------( INVERTED LOGIC )----------------------------
  {
    //Turn off everything
    digitalWrite(coolmos1,HIGH);
    digitalWrite(coolmos2,HIGH);
    digitalWrite(coolmos3,HIGH);
    digitalWrite(coolmos4,HIGH);
    digitalWrite(hotmos,HIGH);
  }
  delay(5000); //wait 5sec. till next reading
}
