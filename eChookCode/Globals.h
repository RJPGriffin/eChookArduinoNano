// Bluetooth Data Identifiers
// If these are altered the data will no longer be interpreted correctly by the phone.
const char SPEED_ID            = 's';
const char MOTOR_ID            = 'm';
const char CURRENT_ID          = 'i';
const char VOLTAGE_ID          = 'v';
const char VOLTAGE_LOWER_ID    = 'w';
const char THROTTLE_INPUT_ID   = 't';
const char THROTTLE_ACTUAL_ID  = 'd';
const char TEMP1_ID            = 'a';
const char TEMP2_ID            = 'b';
const char TEMP3_ID            = 'c';
const char LAUNCH_MODE_ID      = 'L';
const char CYCLE_VIEW_ID       = 'C';
const char GEAR_RATIO_ID       = 'r';
const char BRAKE_PRESSED_ID    = 'B';

// Variables to track timing
unsigned long lastShortDataSendTime = 0;      // Time last BT data packet was sent.
unsigned long lastWheelSpeedPollTime = 0;      // Time of last Wheel Speed check
unsigned long lastMotorSpeedPollTime = 0;      // Time of last Motor RPM check
unsigned long nextThrottleReadMs = 0;

// Read in values:
float batteryVoltageTotal   = 0;
float batteryVoltageLower   = 0;
float throttle              = 0;
float current               = 0;
float motorRPM              = 0;
float wheelRPM              = 0;
float wheelSpeed            = 0;
float gearRatio             = 0;
float tempOne               = 0;
float tempTwo               = 0;
float tempThree             = 0;
int brake                   = 0;

// Loop counter used for longer interval functions
int loopCounter = 0;

// Interrupt Variables.
volatile unsigned long motorPoll      = 0;
volatile unsigned long wheelPoll      = 0;
volatile unsigned long fanPoll        = 0;
// Tip: Any variables that are being used in an Interrupt Service Routine need to be declared as volatile. This ensures
// that each time the variable is accessed it is the master copy in RAM rather than a cached version within the CPU.
// This way the main loop and the ISR variables are always in sync

// Button Tracking variables
int cycleButtonPrevious   = LOW; // Track state so that a button press can be detected
int launchButtonPrevious  = LOW; // Track state so that a button press can be detected
int brakeButtonPrevious   = LOW; // Track state so that a button press can be detected
const int buttonDebounceTime = 50;


/**
 * For some signals it is desireable to average them over a longer period than is possible using the hardware
 * components on the board. To do this we average the last few readings taken by the Arduino.
 * When a new reading is taken it is added to an array. Each new reading takes the place of the oldest reading
 * in the array, so the array always contains the last X number of readings, where X is the size of the array.
 * In our case, for a reading being updated every 250ms, an array of length 4 would average the readings over
 * the last second.
 * To implement this in code, two golbal variables are needed per filter:
 *  > The Array - to store the last X number of readings
 *	> A Count - This dictates which position in the array a new reading goes to and loops between 0 and array length - 1
 * To make it simple to alter the length of time to average over it is good practice to define the max count
 * value and aray length as a global const too.
 */

//Current Smoothing Variables:

const int currentSmoothingSetting = 4; //current is sampled every 250ms, therefore 4 makes 1s of smoothing
int currentSmoothingArray[currentSmoothingSetting];
int currentSmoothingCount = 0;

//Speed Smoothing Variables:

const int speedSmoothingSetting = 3; //speed is sampled every 1s, therefore 3 makes 3 seconds of smoothing
int speedSmoothingArray[speedSmoothingSetting];
int speedSmoothingCount = 0;

// Experimental Area Variables:
volatile long lastMotorPollTime = 0;
volatile long lastMotorInterval = 0;
volatile long lastWheelPollTime = 0;
volatile long lastWheelInterval = 0;
