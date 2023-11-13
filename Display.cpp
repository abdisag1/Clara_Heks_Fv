#include "Display.h"
#include <LiquidCrystal_I2C.h>

using namespace std;

int state = 2;


Display::Display(byte pin) {
  this-> pin = pin;
  this-> text = "";

  init();

}



void Display::init() { // put your setup code here, to run once:
  // put your setup code here, to run once:
 

  Serial.begin(9600);

}

void Display::run(Clara &clara, LiquidCrystal_I2C &lcd) { // Has to be passed as a reference! See p. 255 in "Grundkurs C++"

  state = clara.get_state();
  float cl_pumped = clara.pump_count * clara.volume_per_pump;
  int upper_orp = 110;
  int lower_orp = 200;
  String upper_orp_string;
  String lower_orp_string;
  String S_voltage = String(clara.voltage);
  String flow_string = String(clara.get_flow()) + " l/min"; // Has to be replaced of course
  String chlorine_left = String(cl_pumped); // Has to be replaced of course
  String state_display = String("Stand By");
 //String time_left = String(clara.count_down_min);
  String battery_level = String(clara.get_voltage());
  String commulative_flow = String(100);


//inital welcome screen
if (state ==1) { 
    String message1 = "Clara Begins";
    String message2 = "Add 350ml Of Brine";
    String message3 = "& Add 4L of Water";
    String message4 = "Into The Prod Bottle";
     
    LCDWrite(message1,message2,message3,message4, lcd);
    delay(6000);
    clara.set_state(4);
    //Serial.println("1 sec");
  }


  else if (state == 2) {
    cl_pumped = clara.pump_count * clara.volume_per_pump;

    flow_string = String(clara.get_flow()) + " l/min"; // Has to be replaced of course
    chlorine_left = String(cl_pumped); // Has to be replaced of course
    state_display = String("In Production");
    String time_left = String(clara.count_down_min);
    commulative_flow = String(clara.flow_commulative);

    LCDWrite("Flow C: " + commulative_flow, "NaClO.Pumped: " + chlorine_left + " L" , "Time Left: " + time_left + " min", "State: " + state_display, lcd);



  }

  else if (state == 3) {
    cl_pumped = clara.pump_count * clara.volume_per_pump;

    flow_string = String(clara.get_flow()) + " l/min"; // Has to be replaced of course
    chlorine_left = String(cl_pumped); // Has to be replaced of course
    state_display = String("Stand By");
    battery_level = String(clara.get_voltage());
    commulative_flow = String(clara.flow_commulative);

    LCDWrite("Flow C: " + commulative_flow, "NaClO.Pumped: " + chlorine_left + " L" , "Battery Level: " + battery_level+"V", "State: " + state_display, lcd);

    


  }


  else if (state == 4) {


    cl_pumped = clara.pump_count * clara.volume_per_pump;
    flow_string = String(clara.get_flow()) + " l/min"; // Has to be replaced of course
    chlorine_left = String(cl_pumped); // Has to be replaced of course
    state_display = String("Stand By");
    battery_level = String(clara.get_voltage());
   
    commulative_flow = String(clara.flow_commulative);
   
  


    LCDWrite("Flow C  : " + commulative_flow, "NaClO.Pumped: " + chlorine_left + "L" , "S.Voltage: " + battery_level+"V", "State: " + state_display, lcd);



  }
  else if (state == 5) {
    cl_pumped = clara.pump_count * clara.volume_per_pump;
    flow_string = String(clara.get_flow()) + " l/min";
    chlorine_left = String(cl_pumped); // Has to be replaced of course
    state_display = String("Settling");
    battery_level = String(clara.get_voltage());
    commulative_flow = String(clara.flow_commulative);
    LCDWrite("Flow C: " + commulative_flow, "NaClO.Pumped: " + chlorine_left + " L" , "S.Voltage: " + battery_level+"V", "State: " + state_display, lcd);
  }
  else if (state == 6) {
    cl_pumped = clara.pump_count * clara.volume_per_pump;
    flow_string = String(clara.get_flow()) + " l/min";
    chlorine_left = String(cl_pumped); // Has to be replaced of course

    state_display = String("Valve opened");
    battery_level = String(clara.get_voltage());
    commulative_flow = String(clara.flow_commulative);
    LCDWrite("Flow C: " + commulative_flow, "NaClO.Pumped: " + chlorine_left + " L" , "S.Voltage: " + battery_level+"V", "State: " + state_display, lcd);
  }



}

void Display::LCDWrite(String text1, String text2, String text3, String text4, LiquidCrystal_I2C &lcd) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(text1);
  lcd.setCursor(0, 1);
  lcd.print(text2);
  lcd.setCursor(0, 2);
  lcd.print(text3);
  lcd.setCursor(0, 3);
  lcd.print(text4);
}
