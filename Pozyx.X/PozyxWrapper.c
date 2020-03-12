/*
    PozyxWrapper.cpp - Custom implementation file for interacting 
    with Pozyx device
 */

#include "Pozyx.h"
#include "Pozyx_definitions.h"
#include "PozyxWrapper.h"
#include "Timers.h"
#include <math.h>
#include "CommsIDs.h"
#include "Initialize.h"
#include "Timers.h"

//#define DEBUG
#define FASTTRANSFER
#ifdef  FASTTRANSFER

#endif
uint16_t device_id = 0x6741;
uint16_t remote_id = 0x6715; // the network ID of the remote device
uint16_t destination_id_1 = 0x6719; //device id of left anchor on collection bin
uint16_t destination_id_2 = 0x6e21; //device id of right anchor on collection bin
uint8_t ranging_protocol = POZYX_RANGE_PROTOCOL_PRECISION; // ranging protocol of the Pozyx.
uint16_t DevY[AVERAGEAMOUNT];
uint16_t RemY[AVERAGEAMOUNT];
bool remote = true;

uint8_t Head_1 = 0;
uint8_t Head_2 = 0;

int deviceLeftStatus;
int deviceRightStatus;

device_range_t deviceLeftRange;
device_range_t deviceRightRange;

device_range_t remoteLeftRange;
device_range_t remoteRightRange;

//Temporary until I can store in struct
double device_pos_X;
double device_pos_Y;
double remote_pos_X;
double remote_pos_Y;
double center_X;
double center_Y;
double mid_X;
double mid_Y;

double heading;
int quadrant = 0;


//Param for remote device
uint16_t DevX[AVERAGEAMOUNT];
uint16_t RemX[AVERAGEAMOUNT];
uint8_t Head_3 = 0;
uint8_t Head_4 = 0;
//Statuses for connection between remote device and left and right anchors on collection bin
int remoteLeftStatus;
int remoteRightStatus;

double slope, A, B, m;
double remoteLeftAngle, remoteRightAngle; //global var to store calculation for updateTagAngles function


unsigned long powerOfTwo(unsigned long x);
double lawOfCOS(uint32_t a, uint32_t b, uint32_t c);

//GYRO STUFF
int16_t gyro_raw[3];
long offsetG_Y;
int gyroYDPS;
int highG_y = -5000;
int lowG_y = 5000;
long lastMillis;
double yAngle = 0;
double lastyAngle = 0;
bool flag = 1;
unsigned long previousMillis;
unsigned long interval;
double currentHeading;
int count = 0;

timers_t TransmitTimer;

double headingAvg[10];

void updateHeading() {
    // CALCULATIONS FOR HEADING: CHECK WITH PEERS TO MAKE SURE THIS IS THE CORRECT METHOD
    heading = (atan2((device_pos_X) - (remote_pos_X), (device_pos_Y) - (remote_pos_Y)) * RadToDeg); //RadToPi defined in PozyxWrapper.
    if (heading > 0)heading = 360 - heading;
    else heading = fabs(heading);

}

void PozyxBoot() {
#ifdef FASTTRANSFER
#endif
    if (Pozyx_begin() == POZYX_FAILURE) {
#ifdef DEBUG
        Serial.println("ERROR: Unable to connect to POZYX shield");
        Serial.println("Reset required");
#endif
        delay(100);
    }
    // setting the remote_id back to NULL will use the local Pozyx
    if (!isRemote) {
        remote_id = NULL;
    }
#ifdef DEBUG
    Serial.println("------------POZYX RANGING V1.1------------");
    Serial.println("NOTES:");
    Serial.println("- Change the parameters:");
    Serial.println("\tdestination_id (target device)");
    Serial.println("\trange_step (mm)");
    Serial.println();
    Serial.println("- Approach target device to see range and");
    Serial.println("led control");
    Serial.println("------------POZYX RANGING V1.1------------");
    Serial.println();
    Serial.println("START Ranging:");
#endif

    // make sure the pozyx system has no control over the LEDs, we're the boss
    //uint8_t led_config = 0x0;
    int status;
    //    status = setLedConfig(led_config, remote_id);
    //    // do the same with the
    //    status = setLedConfig(led_config, destination_id_1);
    //    // do the same with the
    //    status = setLedConfig(led_config, destination_id_2);
    // set the ranging protocol
    //getSystemError(NULL) ;
    status = setRangingProtocol(ranging_protocol, remote_id);

    getSystemError(NULL);
    status = setSensorMode(0, remote_id);
}

void updateStatus() {
    /* Get the ranging data from the Pozyx devices */
    /* Ranges from the main Pozyx device on the robot to the beacons */
    deviceLeftStatus = doRanging(destination_id_1, &deviceLeftRange);
    __delay_ms(1);
    deviceRightStatus = doRanging(destination_id_2, &deviceRightRange);
    __delay_ms(1);
    /* Ranges from the secondary Pozyx device on the robot to the beacons */
    remoteLeftStatus = doRemoteRanging(remote_id, destination_id_1, &remoteLeftRange);
    __delay_ms(1);
    remoteRightStatus = doRemoteRanging(remote_id, destination_id_2, &remoteRightRange);
    // Standard error fix
    remoteLeftRange.distance += 100;
    remoteRightRange.distance += 100;

    /* Verify that all the data was valid data before it is used to get the new coordinates */
    if ((deviceLeftStatus == POZYX_SUCCESS && deviceRightStatus == POZYX_SUCCESS) && (remoteLeftStatus == POZYX_SUCCESS && remoteRightStatus == POZYX_SUCCESS)) {
        updateCoordinates();
    } else {
#ifdef DEBUG
        Serial.print("Error in 'UPDATESTATUS' for REMOTE. Cause: remoteLeftStatus a/or remoteRightStatus failure: ");
        Serial.print(deviceLeftStatus);
        Serial.print('|');
        Serial.print(deviceRightStatus);
        Serial.print('|');
        Serial.print(remoteLeftStatus);
        Serial.print('|');
        Serial.println(remoteLeftStatus);

#endif
    }


}

/* Returns the average of a buffer that is 'AVERAGEAMOUNT' large*/
double getBuffAvg(uint16_t *buff) {
    long double sum = 0;
    int i;
    /* Summing components */
    for (i = 0; i < AVERAGEAMOUNT; i++) {
        sum += (double) buff[i];
    }
    /* divide by the size of buffer, returning average */
    return (double) (sum / ((double) AVERAGEAMOUNT));
}

/* Adds a single value to the head of a ring buffer */
void BufferAddVal(uint16_t *buff, uint8_t *head, double val) //updates the value of buff
{
    /* If the value that is about to be passed onto the buffer is bad, ignore it.*/
    if(fabs(val) < 5000)
    {
        /* Add value to head */
        buff[(*head)++] = (int32_t) val;
        /* Increment head */
        if (*head >= AVERAGEAMOUNT) {
            *head = 0;
        }
    }
}

void calculateCenter() {
    //Code originally from David's 'newTestArena' code:
    //mid-point between Pozyx sensors on robot
    mid_X = (device_pos_X + remote_pos_X) / 2.0;
    mid_Y = (device_pos_Y + remote_pos_Y) / 2.0;
    //    
    //    //compute unit vector in direction of robot heading
    //    double x_component = (remote_pos_X - device_pos_X);
    //    double y_component = (remote_pos_Y - device_pos_Y);
    //
    //    double Slope = x_component/y_component;
    //    
    //    double b = mid_Y - (Slope)*mid_X;
    //    double centX;
    //    double Clc = MID_DIST/(sqrt(1+pow(Slope,2)));
    //    if(x_component > 0)
    //        centX = mid_X + Clc;
    //    else
    //        centX = mid_X - Clc;
    //    center_X = mid_X - ((MID_DIST * y_component) / TAG_DIST);
    //    center_Y = mid_Y + ((MID_DIST * x_component) / TAG_DIST);
    center_X = mid_X + MID_DIST * cos(currentHeading * DegToRad);
    center_Y = mid_Y + MID_DIST * sin(currentHeading * DegToRad);

}

long long pow2(long long _val, int scale) {
    return _val * _val;
}

void updateCoordinates() //Needs re-worked. Will try something out once header + buffer working as intended
{
    
    int a = (int) remoteRightRange.distance;
    int b = (int) deviceRightRange.distance;
    int c = (int) remoteLeftRange.distance;
    int d = (int) deviceLeftRange.distance;
    int u = (int) ANCHORDISPLACEMENT;
    
    int dev_y,dev_x,rem_y,rem_x;
    //    double w = (double) TAG_DIST;
    
    //    Serial.print("right Remote: ");Serial.println(remoteRightRange.distance);
    //    Serial.print("left Remote: ");Serial.println(remoteLeftRange.distance);
    //    Serial.print("right device: ");Serial.println(deviceRightRange.distance);
    //    Serial.print("left device: ");Serial.println(deviceLeftRange.distance);
    
    long long num = pow2(b, 2);
    num = num - pow2(u, 2);
    num = num - pow2(d, 2);
    
    //calculate Y1 position (Y coordinate of Pozyx shield on Arduino device on robot)
    //device_pos_Y = sqrt(-1*powerOfTwo(((b*b)-(u*u)-(d*d))/(-2*u))+(unsigned long)(d*d));
    dev_y = (int)((sqrtl(( -1 * pow2( ((num) / (2 * u)), 2) + pow2(d, 2)))));
    
    
    //calculate Y2 position (Y coordinate of remote Pozyx beacon on robot)
    //remote_pos_Y = (sqrt(-1*powerOfTwo(((a*a)-(u*u)-(c*c))/(-2*u))+(unsigned long)(c*c)));
    num = pow2(a, 2);
    num = num - pow2(u, 2) - pow2(c, 2);
    
    long long g = -pow2((num) / (2 * u), 2) + pow2(c, 2);
    
    //long int tempG = g / 16.0;
    //rem_y = tempG * 4;

    rem_y = (int)(sqrt(g));        //FIXME
    
    //calculate X1 position (shield on arduino)
    //device_pos_X = ((d*d) - (b*b) + (u*u))/(2*u);
    num = pow2(d, 2) - pow2(b, 2) + pow2(u, 2);
    dev_x = (((num) / (2 * u)));
    //calculate X2 position (remote beacon)
    //remote_pos_X = ((c*c)-(a*a)+(u*u))/(2*u);
    num = pow2(c, 2) - pow2(a, 2) + pow2(u, 2);
    rem_x = ((num) / (2 * u));

    BufferAddVal(DevY, &Head_1, dev_y);
    BufferAddVal(RemY, &Head_2, rem_y);
    BufferAddVal(DevX, &Head_3, dev_x);
    BufferAddVal(RemX, &Head_4, rem_x);

    device_pos_Y = getBuffAvg(DevY);
    remote_pos_Y = getBuffAvg(RemY);
    device_pos_X = getBuffAvg(DevX);
    remote_pos_X = getBuffAvg(RemX);

}

double calculateX1Position() {
    double b = deviceRightRange.distance;
    double d = deviceLeftRange.distance;
    double u = ANCHORDISPLACEMENT;
    //double w = TAG_DIST;

    unsigned long squareThis = ((b * b)-(u * u)-(d * d)) / (-2 * u);
    unsigned long squared = powerOfTwo(squareThis);
    unsigned long secVal = -1 * squared + (unsigned long) (d * d);
#ifdef DEBUG
    Serial.println(sqrt(-1 * powerOfTwo(((b * b)-(u * u)-(d * d)) / (-2 * u))+(unsigned long) (d * d)));
#endif
    return sqrt(secVal);
}

double calculateX2Position() {
    double a = remoteRightRange.distance;
    double c = remoteLeftRange.distance;
    double u = ANCHORDISPLACEMENT;
    //double w = TAG_DIST;

    unsigned long squareThis = ((a * a)-(u * u)-(c * c)) / (-2 * u);
    unsigned long squared = powerOfTwo(squareThis);
    unsigned long secVal = -1 * squared + (unsigned long) (c * c);
#ifdef DEBUG
    Serial.println(sqrt(-1 * powerOfTwo(((a * a)-(u * u)-(c * c)) / (-2 * u))+(unsigned long) (c * c)));
#endif
    return sqrt(secVal);

}

double calculateY1Position() {
    double d = deviceLeftRange.distance;
    double b = deviceRightRange.distance;
    double u = ANCHORDISPLACEMENT;

    return (((d * d) - (b * b) + (u * u)) / (2 * u));
}

double calculateY2Position() {
    double a = remoteRightRange.distance;
    double c = remoteLeftRange.distance;
    double u = ANCHORDISPLACEMENT;

    return (((c * c)-(a * a)+(u * u)) / (2 * u));
}

unsigned long powerOfTwo(unsigned long x) {
    return x*x;
}

// GYRO IMPLEMENTATION //

void calibrateGyro() {
    int i;
    for (i = 0; i < 10; i++) {
        regRead(POZYX_GYRO_X, (uint8_t*) & gyro_raw, 3 * sizeof (int16_t));
        delay(5);
    }
    long sumY = 0;
    for (i = 0; i < Samples; i++) {
        regRead(POZYX_GYRO_X, (uint8_t*) & gyro_raw, 3 * sizeof (int16_t));
        sumY += gyro_raw[1];
        //Keep track of the highest values

        if (gyro_raw[1] > highG_y) highG_y = gyro_raw[1];
        //Keep track of the lowest values
        if (gyro_raw[1] < lowG_y) lowG_y = gyro_raw[1];
        delay(5);


    }
    int range = (abs(lowG_y) + abs(highG_y)) / 2;
    offsetG_Y = sumY / Samples;
    highG_y = range - offsetG_Y;
    lowG_y = -range - offsetG_Y;
    //  Serial.print("range:"); Serial.println(range);
}

#define tau     0.1
#define fs      10
#define DT      (1/(double)fs)
//#define alpha   1 - fabs(atan(((device_pos_X) - (remote_pos_X))/((device_pos_Y) - (remote_pos_Y)))/(M_PI/2))//(double)(tau)/(double)(tau+DT)
bool headingSet = false;

void adjustHeading() {
    double alpha = 1 - fabs(atan(((device_pos_X) - (remote_pos_X)) / ((device_pos_Y) - (remote_pos_Y))) / (M_PI / 2));
    if (alpha > .5) alpha = 1 - alpha;

    if (abs(millis() - previousMillis) > interval) {
        //update pozyx angle
        updateHeading();
        previousMillis = millis();


        lastyAngle = yAngle;

        //obtain the gyro offset
        if ((abs(lastMillis - millis())) > fs) {
            regRead(POZYX_GYRO_X, (uint8_t*) & gyro_raw, 3 * sizeof (int16_t));
            gyroYDPS = gyro_raw[1] - offsetG_Y;
            if (isWithinFloat(gyroYDPS, lowG_y * 1.1, highG_y * 1.1)) {
                gyroYDPS = 0;
                //yAngle = heading;
            }
            yAngle += ((double) gyroYDPS * SCALING_GYRO * ((double) (millis() - lastMillis) / 1000.0) / 16.0);

            lastMillis = millis();
        }

        if (yAngle > 360) yAngle -= 360;
        else if (yAngle < 0) yAngle += 360;
        // find the number of degrees between the two angles

        if ((alpha > 0.40) /*&& (alpha < 0.65)((AngleDist(yAngle,heading) ) > 10)*/  && headingSet == false && millis() > 6000) {
            yAngle = heading;
            headingSet = true;
        }
//        if (alpha > .4) {
//            //if (!((heading > 270 && yAngle < 90) || (heading < 90 && yAngle > 270)))
//                currentHeading = (1- alpha)*(yAngle) + (alpha)*(heading);
//        } else
            currentHeading = yAngle;


#ifdef DEBUG
        Serial.print("set?: ");
        Serial.println(headingSet);
        Serial.print("Y-Val: ");
        Serial.println(yAngle);
        Serial.print("Alpha: ");
        Serial.println(alpha);
        Serial.print("CURRENT HEADING: ");
        Serial.println(currentHeading);
        Serial.print("calculated heading: ");
        Serial.println(heading); //we're good!
#endif 
    }

}

int getPozyx_X() {
    return center_X;
}

int getPozyx_Y() {
    return center_Y;
}

int getPozyx_H() {
    return currentHeading;
}

int AngleDist(double a1, double a2) {
    int phi = abs((int) heading - (int) yAngle) % 360; // This is either the distance or 360 - distance
    int Difference = phi > 180 ? -(360 - phi) : phi;
    return Difference;

}
int lastTime = 0;

void printCH() {

#ifdef DEBUG
    printBasicXY();
    //  Serial.print("Center X: ");
    //  Serial.println(center_X);
    //  Serial.print("Center Y: ");
    //  Serial.println(center_Y);
    //  Serial.print("HEADING: ");
    //  Serial.println(heading);
    //  Serial.print("GYRO ASSISTED HEADING: ");
    //  Serial.println(currentHeading);
    //  Serial.print("diff: ");
    //  Serial.println(heading - currentHeading);
#endif
    //fastransfer send data to master
    // master address is 4
    // to load data in to FT send buffer use toSend(what index, data)
    // to send the data use sendData(address of receiver)
    // we need to send this info at 1 sec interval
    // use an if statemnet that will compare to current time to last time we send data
    // you want to use millis()


#ifdef FASTTRANSFER

    //Sending the message periodically
    if (abs(lastTime - millis()) > 200) {
        /* Loading the info for FastTransfer UART */
        FT_ToSend(getFThandle(), 1, center_X);
        FT_ToSend(getFThandle(), 2, center_Y);
        FT_ToSend(getFThandle(), 3, currentHeading);
        FT_ToSend(getFThandle(), 4, heading);
        FT_ToSend(getFThandle(), 5, device_pos_X);
        FT_ToSend(getFThandle(), 6, device_pos_Y);
        FT_ToSend(getFThandle(), 7, remote_pos_X);
        FT_ToSend(getFThandle(), 8, remote_pos_Y);
        FT_ToSend(getFThandle(), 9, deviceLeftRange.distance);
        FT_ToSend(getFThandle(), 10, deviceRightRange.distance);
        FT_ToSend(getFThandle(), 11, remoteLeftRange.distance);
        FT_ToSend(getFThandle(), 12, remoteRightRange.distance);
        // Sending....
        FT_Send(getFThandle(), 5);

        /**** Commented out because the "\PublishData" Functionality should be taking care of it ****/
        //        /* Transmit info on CAN bus */
        //        FTC_ToSend(getCanFThandle(), DATA_0 + GLOBAL_DATA_INDEX_PER_DEVICE*POZYX, center_X);
        //        FTC_ToSend(getCanFThandle(), DATA_1 + GLOBAL_DATA_INDEX_PER_DEVICE*POZYX, center_Y);
        //        FTC_ToSend(getCanFThandle(), DATA_2 + GLOBAL_DATA_INDEX_PER_DEVICE*POZYX, currentHeading);
        //        FTC_ToSend(getCanFThandle(), DATA_3 + GLOBAL_DATA_INDEX_PER_DEVICE*POZYX, heading);
        //        // Sending....
        //        FTC_Send(getCanFThandle(), GLOBAL_ADDRESS);

        lastTime = millis();
    }
#endif
}

bool isWithinFloat(double sample, double lowBound, double highBound) {
    return (sample > lowBound && sample < highBound);
}

//NOT REALLY NEEDED CURRENTLY, REMOVE SOON IF NO USAGE

int variance(uint32_t a[], int n) {
    // Compute mean (average of elements) 
    int sum = 0;
    int i;
    for (i = 0; i < n; i++)
        sum += a[i];
    double mean = (double) sum / (double) n;

    // Compute sum squared  
    // differences with mean. 
    double sqDiff = 0;
    for (i = 0; i < n; i++)
        sqDiff += (a[i] - mean) *
        (a[i] - mean);
    return sqDiff / n;
}

void printBasicXY() {
    //Two methods of printing; the first one is faster
    //calculateX1Position();  //Values of X1, X2 are printed during these function calls. The returned values are the 
    //double X2 = calculateX2Position();

    /*Serial.print("X1: ");
    calculateX1Position();
    Serial.print("X2: ");
    calculateX2Position();
     */
#ifdef DEBUG
    Serial.print("RoboTagDist: ");
    Serial.println(sqrt(powerOfTwo(device_pos_X - remote_pos_X) + powerOfTwo(device_pos_Y - remote_pos_Y)));
    Serial.print("Device X: ");
    Serial.print(device_pos_X);
    Serial.print("  Y: ");
    Serial.println(device_pos_Y);
    Serial.print("Remote X: ");
    Serial.print(remote_pos_X);
    Serial.print("  Y: ");
    Serial.println(remote_pos_Y);
    //  Serial.print("Center X: ");
    //  Serial.print(center_X);
    //  Serial.print(" Y: ");
    //  Serial.println(center_Y); 
#endif

}

/*
void updateDistances()
{
    deviceLeftStatus = doRanging(destination_id_1, &deviceLeftRange);
    deviceRightStatus = doRanging(destination_id_2, &deviceRightRange);
    remoteLeftStatus = doRemoteRanging(remote_id, destination_id_1, &remoteLeftRange);
    remoteRightStatus = doRemoteRanging(remote_id, destination_id_2, &remoteRightRange);
    if (deviceLeftStatus == POZYX_SUCCESS && deviceRightStatus == POZYX_SUCCESS)
    {
        //Updating the buffers
        BufferAddVal(deviceLeftDistanceBuffer, &bufferHead.deviceLeft, deviceLeftRange.distance); 
        BufferAddVal(deviceRightDistanceBuffer, &bufferHead.deviceRight, deviceRightRange.distance);
    }
#ifdef isRemote
    if (remoteLeftStatus == POZYX_SUCCESS && remoteRightStatus == POZYX_SUCCESS)
    {
        BufferAddVal(remoteLeftDistanceBuffer, &bufferHead.remoteLeft, remoteLeftRange.distance);
        BufferAddVal(remoteRightDistanceBuffer, &bufferHead.remoteRight, remoteRightRange.distance);
    }
#endif 
}
 */
