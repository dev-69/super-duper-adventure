//add interrupt for primary-life checking
const uint8_t InterruptPin = 12; // dekh le bhai

void IRAM_ATTR isr() //interrupt func.
{
 // serial comm here
// Serial.begin(9600);
// Serial.print("it works!");
 Serial.print("normal");    //transfers the life key
}
  
void setup() {
 Serial.begin(9600);
 pinMode(InterruptPin, INPUT);
 attachInterrupt(InterruptPin, isr, RISING);  //WHEN PIN 12 GOES HIGH INTERRUPT WILL BE SET.
}

void loop() 
{
 //IDHAR NORMAL CODE HOGA!  
}

//29097173
