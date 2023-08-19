//
// This file is an example of how to use the RampSoakPID controller to control an oven.

// You simply need to create two functions:
// float measureTemp():            measures a temperature value
// setHeaterPWM(float pwmPercent): sets PWM for heating element
// 
// You can change the values in the setup function to better suit your needs.
// Use the serial monitor and serial plotter to see the data in real time.

#include <RampSoakPid.h>

float currentTemp;             // the thing we are trying to control (temperature in Celcius)
float pidOutput;                      // the output of the PID controller

void setup() {
  Serial.begin(115200);
  setPidCoefficients(1.0, 0.1, 1.0);  // P, I, D
  setIntegratorWindupLimit(100);      // Maximum value the integral term can reach (+/- 100)
  setRampLimit(-10, 10);              // Min, Max values for ramp rate (+/- 10 degrees Celcius per minute)
  setCrossoverDistance(10);           // How far from the setpoint before we start lowering the ramp rate to zero
                                      // So if our setpoint is 100C we will start lowering the ramp rate at 90C
  setDebugOnOff(true);                // Debugging logs are printed to the Serial port
}

void loop() {
  setTarget(100);                     // set a new value for the PID controller to reach (100 Celcius)
  
  while (true) {
    delay(100);                       // Update PID (once every 100ms recommended)
    // currentTemp = measureTemp();   // measure the temperature
    pidOutput = pidStep(currentTemp); // compute next PID step
    // setHeaterPWM(pidOutput);       // apply output of PID controller to heater
  }

}