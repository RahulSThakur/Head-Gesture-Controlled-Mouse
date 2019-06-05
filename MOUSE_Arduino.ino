/*
  //Details

  Accelerometer_Mouse
  This code reads the Memsic 2125 two-axis accelerometer, converts the pulses output by the 2125 into milli-g's (1/1000 of earth's gravity) and prints a mapped version of them over the serial connection to the computer.output. It then takes these mapped values and uses them for virtual mouse movement, clicking, and scrolling.

  The circuit:
  X output of accelerometer to digital pin 2
  Y output of accelerometer to digital pin 3
  +V of accelerometer to +5V
  GND of accelerometer to ground
  created by David Kerns of The Athenian School on Dec 3 2012, with a large portion of code taken from David A. Mellis' and Tom Igoe's found here: http://www.arduino.cc/en/Tutorial/Memsic2125
*/

#include<Mouse.h>
const int xPin = A1;   // const for X output of the accelerometer
const int yPin = A2;  // const for Y output of the accelerometer


void setup() {
  Serial.begin(9600); // initialize serial communications:
  pinMode(xPin, INPUT); // xPin connected to the accelerometer is input pinMode(yPin, INPUT);
  // yPin connected to the accelerometer is input
  Mouse.begin();

  // Serial.begin(9600); // Set up serial communication at 9600bps
  Serial.println("ready"); //Print ready once setup loop is finished

}

void loop() {

  int pulseX, pulseY; // Variables to read the pulse widths from accelerometer:
  int accelerationX, accelerationY; // Variables to contain the resulting accelerations

  //  pulseX = pulseIn(xPin, HIGH); // read pulse from x-axes
  //  pulseY = pulseIn(yPin, HIGH); // read pulse from y-axes
  // convert the pulse width into acceleration accelerationX and accelerationY are in milli-g's: earth's gravity is 1000 milli-g's, or 1g.
  //  accelerationX = ((pulseX / 10) - 500)/2 ;
  //  accelerationY = ((pulseY / 10) - 500)/2 ;
  accelerationX = analogRead(xPin);
  accelerationY = analogRead(yPin);
  accelerationX = map(accelerationX, 240, 440, -20, 20); //map the acceleration output to more manageable values
  //                                Average of min and max value of xAxis should be threshold or value at reference
  //                                select the mapping value according to the sensitivity. Higher range => High sensitivity
  //                                Use an external input reference (around 2v) as the values are between 200-400. It will increase the sensitivity.
  accelerationY = map(accelerationY, 170, 370, -20, 20); //map the acceleration output to more manageable values
//                                Average of min and max value of yAxis should be threshold or value at reference
  Serial.print(accelerationX); // print the x acceleration result
  Serial.print("\t"); // print a tab character:
  Serial.print(analogRead(xPin));
  Serial.print("\t");
  Serial.print(accelerationY); // print the y acceleration result
  Serial.print("\t");
  Serial.print(analogRead(yPin));
  Serial.println(); //print a new line 
  delay(500);
  if (accelerationX < -17) { // override loop for scrolling, if accelerationX < -17
    Mouse.move(0, 0, accelerationY); // mouse scroll function at the rate of accelerationY
  }
  else { // when accelerationX is > -17 (most of the time), do this loop
    if (accelerationY > 4 || accelerationY < -4) /*if accelerationY > 4 or < -4 || accelerationX < -4)) // or if accelerationY > 4 and < -4(accelerationX > 4)*/
    {
      Mouse.move(-accelerationX, -accelerationY, 0); // move the mouse the negative accelerations(X and Y), do not scroll
    }
  }

  if (accelerationY > 20) { //if the accelerationY value reaches a value of 20,

    Mouse.click(); //left click the computer's mouse

  }

  if (accelerationY > 35) { //if the accelerationY value reaches a value of 35,

    Mouse.click(); //left click once
    Mouse.click(); //left click again (resulting in a double click)
  }
  if (accelerationX > 20) { //if the accelerationX value reaches a value of 20,
    Mouse.click(MOUSE_RIGHT); //right click the computer's mouse
  }

}

