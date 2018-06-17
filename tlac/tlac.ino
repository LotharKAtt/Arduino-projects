int led1 = 4;
int led2 = 3;
int tlac = 2;

boolean sviti = false;

void setup(){
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(tlac,INPUT);  
}

void loop(){
  if(digitalRead(tlac)){
    if (sviti){
      sviti = false;
    }
    else sviti = true;
    digitalWrite(led2,sviti);
    digitalWrite(led1,!sviti);
    while(digitalRead(tlac)){
      delay(50);
    }
  }
}

