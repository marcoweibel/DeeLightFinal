//#include <RFduinoGZLL.h> // include rfduino library
//device_t role = DEVICE4; // set Device name... DEVICE2 to DEVICE7 / HOST
//
//String inputString = "";         // a string to hold incoming data
//boolean stringComplete = false;  // whether the string is complete
//
//int rPotVal = 0;       // variable to store the value coming from the R sensor 
//int gPotVal = 0;       // variable to store the value coming from the G sensor
//int bPotVal = 0;       // variable to store the value coming from the B sensor
//
//const int buttonUpPin = 5;     // the number of the pushbutton pin  
//
//const int buttonDownPin = 6;     // the number of the pushbutton pin
//
//void setup()
//{
//  Serial.begin(9600); // begin serial communications
//
//inputString.reserve(200);
//  RFduinoGZLL.txPowerLevel = 0;
//
//  // start the GZLL stack
//  RFduinoGZLL.begin(role); // begin BLE communications
//
//  pinMode(buttonUpPin, INPUT);
//pinMode(buttonDownPin, INPUT);
//}
//
//void loop()
//{
//
//  rPotVal = analogRead(2);
//gPotVal = analogRead(3);
//bPotVal = analogRead(4);
//
//int buttonUpState = digitalRead(buttonUpPin);
//int buttonDownState = digitalRead(buttonDownPin);
//
//rPotVal = map(rPotVal, 0, 1023, 0, 255);
//gPotVal = map(gPotVal, 0, 1023, 0, 255);
//bPotVal = map(bPotVal, 0, 1023, 0, 255);
//
////Serial.print(rPotVal);
////Serial.print(",");
////Serial.print(gPotVal);
////Serial.print(",");
////Serial.print(bPotVal);
////Serial.print(",");
////Serial.print(buttonUpState);
////Serial.print(",");
////Serial.println(buttonDownState);
//  
//  char sdata[49];
//  char mydata[20]; // declare mydata array
//
//  String mystr;
//  String sstr;
//
//   serialEvent(); //call the function
//  // print the string when a newline arrives:
//  if (stringComplete) {
////    Serial.println(inputString);
//    sstr=inputString;
//    // clear the string:
//    inputString = "";
//    stringComplete = false;
//  }
//
// 
//  mystr = "m," + rPotVal+", " + gPotVal+", " + bPotVal+", " + buttonUpState+", " + buttonDownState; // combining data for sending to other rfduino... change "a" to other characters to identify message package. your sstr is data from serial
//
//  mystr.toCharArray(mydata, 30); // place mystr data into character buffer
//
//Serial.println(mystr); // print buffer to serial
//
// RFduinoGZLL.sendToHost(mydata, 30); // send buffer to host other rfduino
//    delay(250);
//
//    
//}
//
//// if data is recived from another rfduino
//void RFduinoGZLL_onReceive(device_t device, int rssi, char *data, int len)
//{
//  // ignore acknowledgement without payload
//  if (len > 0)
//  {
//    // set the Green led if this device is the closest device
//    device_t closest_device = (device_t)data[0];
//    //digitalWrite(green_led, (role == closest_device));
//  }
//}
//
////event handler to get data from serial when newline is presented
//void serialEvent() {
//  while (Serial.available()) {
//    // get the new byte:
//    char inChar = (char)Serial.read();
//    // add it to the inputString:
//    inputString += inChar;
//    // if the incoming character is a newline, set a flag
//    // so the main loop can do something about it:
//    if (inChar == '\n') {
//      stringComplete = true;
//    }
//  }
//}



#include <RFduinoGZLL.h> // include rfduino library
device_t role = DEVICE4; // set Device name... DEVICE2 to DEVICE7 / HOST

//define pins

int rpin = 2;
int gpin = 3;
int bpin = 4;

int rval = 0;
int gval = 0;
int bval = 0;

int rvalp = 0;
int gvalp = 0;
int bvalp = 0;

const int buttonUpPin = 5;     // the number of the pushbutton pin  
const int buttonDownPin = 6;     // the number of the pushbutton pin


void setup()
{
  Serial.begin(9600); // begin serial communications
  pinMode(rpin, INPUT);
  pinMode(gpin, INPUT);
  pinMode(bpin, INPUT);

  pinMode(buttonUpPin, INPUT);
  pinMode(buttonDownPin, INPUT);

  RFduinoGZLL.txPowerLevel = 0;

  // start the GZLL stack
  RFduinoGZLL.begin(role); // begin BLE communications
}

void loop()
{
  char xdata[4];   //declaring character array -- 3 characters plus a nill charachter as terminator
  char ydata[4];
  char zdata[4];
  char updata[2];
  char downdata[2];
  char mydata[30]; // declare mydata array

  String xstr;//declaring string
  String ystr;//declaring string
  String zstr;//declaring string
  String upstr;
  String downstr;
  String mystr;

  
int buttonUpState = digitalRead(buttonUpPin);
int buttonDownState = digitalRead(buttonDownPin);

  rval = analogRead(rpin); // read pin sensor values and place into variavles
  gval = analogRead(gpin);
  bval = analogRead(bpin);

  rval = map(rval, 0, 1023, 0, 255);
gval = map(gval, 0, 1023, 0, 255);
bval = map(bval, 0, 1023, 0, 255);

  // convert sendor values to 3 characters.. i.e. value 2 converts to 002, value 40 converts to 040
  if (rval >= 100)
  {
    xstr = String(rval);
  }
  else if (rval < 100 && rval >= 10) {
    xstr = String(0) + String(rval);
  }
  else if (rval < 10) {
    xstr = String(0) + String(0) + String(rval);
  }
  
  
  if (gval >= 100)
  {
    ystr = String(gval);
  }
  else if (gval < 100 && gval >= 10) {
    ystr = String(0) + String(gval);
  }
  else if (gval < 10) {
    ystr = String(0) + String(0) + String(gval);
  }
  
  
  if (bval >= 100)
  {
    zstr = String(bval);
  }
  else if (bval < 100 && bval >= 10) {
    zstr = String(0) + String(bval);
  }
  else if (bval < 10) {
    zstr = String(0) + String(0) + String(bval);
  }

  upstr = String(buttonUpState);
  downstr = String(buttonDownState);

  xstr.toCharArray(xdata, 4); //passing the string value of sensors to the character array
  ystr.toCharArray(ydata, 4);
  zstr.toCharArray(zdata, 4);
  upstr.toCharArray(updata,2);
  downstr.toCharArray(downdata,2);

  mystr = "m," + xstr+"," + ystr+"," + zstr+"," + upstr+"," + downstr; // combining data for sending to other rfduino... change "a" to other characters to identify message package

  mystr.toCharArray(mydata, 30); // place mystr data into character buffer

  Serial.println(mystr); // print buffer to serial

 RFduinoGZLL.sendToHost(mydata, 30); // send buffer to host other rfduino
    delay(250);
}

// if data is recived from another rfduino
void RFduinoGZLL_onReceive(device_t device, int rssi, char *data, int len)
{
  // ignore acknowledgement without payload
  if (len > 0)
  {
    // set the Green led if this device is the closest device
    device_t closest_device = (device_t)data[0];
    //digitalWrite(green_led, (role == closest_device));
  }
}


