/*
 * This file contains all the values used to calibrate your eChook board.
 * By seperating these it makes it possible to update to newer code without
 * having to copy your calibrations across - just make sure you keep this file!
 *
 * The values provided by default are for the eChook's team dev board, but each
 * board is slightly different. These defaults will give readings that are reasonable,
 * but for extra accuracy, see the documentation to calibrate your own board.
 *
 * Every varialbe in this file begins with CAL_ so that it is identifiable in
 * the main code as being defined in this file.
 *
 */

//Bluetooth Settings
const String CAL_BT_NAME     = "eChook"; // Whatever you want to name your car's bluetooth
const float CAL_BT_BAUDRATE         = 115200;            // Baud Rate to run at. Must match Arduino's baud rate.

// Data Read and Transmit Interval:
const unsigned long CAL_DATA_TRANSMIT_INTERVAL     = 250;         // transmit interval in ms

// Car Specific Settings
const int CAL_WHEEL_MAGNETS        = 6;       //Number of magnets on wheel
const int CAL_MOTOR_MAGNETS        = 3;       // Number of magnets on motor shaft for hall effect sensor
const float CAL_WHEEL_CIRCUMFERENCE  = 1.178;     //Outer circumference of tyre, in Meters. i.e. the distance travelled in one revolution

//Board Specific Calibrations
const float CAL_REFERENCE_VOLTAGE   = 5;     // Voltage seen on the arduino 5V rail
const float CAL_BATTERY_TOTAL       = 6.15;  // Multiplier for 24v calculation. Calculated by 24v Input devided by voltage on Arduino pin A0
const float CAL_BATTERY_LOWER       = 3.071; // Multiplier for 12v calculation. Calculated by 12V Input devided by voltage on Arduino pin A7
const float CAL_CURRENT             = 37.55; // Current Multiplier - See documentation for calibration method

//Thermistor Calibration Values
const float CAL_THERM_A = 0.001871300068; //Steinhart-Hart constants - See documentation for calibration method
const float CAL_THERM_B = 0.00009436080271;
const float CAL_THERM_C = 0.0000007954800125;

//Throttle calibrations
const int CAL_THROTTLE_VARIABLE = 1; // 1 for a variable throttle, 0 for a push button (on/off) throttle.
const int CAL_THROTTLE_RAMP = 0; // 1 to enable. A simple implementation of a throttle ramp up
const int CAL_THROTTLE_LOW = 1; // This voltage and below is regarded as 0% throttle
const int CAL_THROTTLE_HIGH = 4; // This voltage and above is regarded as 100% throttle

// _______________________________________________________________
// Experimental Area!!
// Enabling these might break things :)

// These may break if the vehicle isn't moving
const int USE_IMPROVED_RPM_CALCULATION = 1; // Will work best with one magnet on the motor shaft
const int USE_IMPROVED_SPEED_CALCULATION = 1; // Will work best with one magnet on the wheel
