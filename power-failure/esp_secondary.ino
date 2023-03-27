const int trig_pin = D8;  //this pin will trigger primary esp and check its prescence

bool boot_mode = 1;   //0 for normal and 1 for power-failure
// default boot into power-failure mode.

void setSecondryMode()
{
  // 2 main steps 1) trigger the primary interupt  2) wait for response  3) set modes
  Serial.begin(9600);

  // trigger function
  pinMode(trig_pin, OUTPUT);
  digitalWrite(trig_pin,HIGH);
  delay(100);
  digitalWrite(trig_pin,LOW);

  // response loop requires serial comm [UART]
  for(int rep=0;rep<10;rep++) //will look for serial data 10 times
  {     

    if(Serial.available()>0)
    {
      String response = Serial.readString();
      if(response.compareTo("normal") == 10)        // for some reason wokwi shows 10 for successfull string equalization. docs show 0.
      {
        boot_mode = 0;    //set boot mode to normal
        goto print_boot_mode;   //goto saves time wasteage by skiping further loops
      }
    } //if end

  } //for loop end
  // if prog comes here without serial data -> power-failure mode
  print_boot_mode: 
    Serial.print("boot mode is ");
    Serial.print(boot_mode);
} //setsecondrymode ends here

void setup() {
  // first to be called on boot?

// function to set modes -> 1) normal  2) power-failure
setSecondryMode();

  Serial.begin(9600);
}
void loop() {
  if (boot_mode == 0)
  {
    // code for normal execution goes here
    Serial.println("looping in normal....");
    delay(1000);
  }
  if (boot_mode == 1)
  {
    // code for power failure execution goes here
    Serial.println("looping in power_failure....");
    delay(1000);
  }
}
