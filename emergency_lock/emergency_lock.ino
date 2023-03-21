//BOARD PIN SETTING
//board considered: UNO
int reed_lock_pin = 13;  //for uno
int buzzer_pin = 12;  //for uno



//variable for code lock status. 
//update it everytime code changes the status.
bool virtual_lock_status;                 //1 is open and 0 is closed

//varible for reed lock status
bool real_lock_status;                    //1 is open and 0 is closed


//function for checking the real lock status
void reedLockCheck()
{
    //  declare the reading pin as input
    pinMode(reed_lock_pin, INPUT);
    //update the global variable directly
    real_lock_status = digitalRead(reed_lock_pin);
    
    //try using return type and static function for making code more secure
 
}

//function for buzzer ringing
void buzzerWithDelay(int time)
{
//   declare the buzzerpin as output
   pinMode(buzzer_pin, OUTPUT);
   for(int i = 0;i < time; i++)
   {
      digitalWrite(buzzer_pin,HIGH);
      delay(498);
      digitalWrite(buzzer_pin,LOW);
      delay(498);
   }
}

//implementing the conditional statement
//included in a function "door update" that changes the code lock status according to real lock status
int doorStatusUpdate()
// global variables used hence no arguments passed to function
{
    //  it is good to update the varibles as this function starts.
    //  call reedLockCheck function
    void reedLockCheck();
      if(virtual_lock_status==1 && real_lock_status==0)     //1 is open and 0 is closed
      {
        //    the real door is closed and needs to be updated into program
            virtual_lock_status = 0;
      }
      else if(virtual_lock_status==0 && real_lock_status==1)
      {
        //    emergency mode triggered
        
      }
      else
      {
        //    includes conditions where both variables are same. hence, system is stable and do nothin here 
        void buzzerWithDelay(30);  //the argument includes seconds of delay
        //    send message to owner
        // send live recording part
      }
}

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
