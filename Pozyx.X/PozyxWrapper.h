/* 
 * File:   PozyxWrapper.h
 * Author: John
 *
 * Created on February 14, 2020, 1:08 PM
 */

#ifndef POZYXWRAPPER_H
#define	POZYXWRAPPER_H

#ifdef	__cplusplus
extern "C" {
#endif


#include <math.h>
#include <stdlib.h>
#include <stdint.h>
    //#define FASTTRANSFER
    //#define DEBUG

#define DUAL_POZYX                  //define if using remote + shield; else comment out!
#define isRemote true
#define M_PI 3.14159265358979323846264338327950288419716939937
#define RadToPi (180/M_PI)          //57.2957795131
#define ANCHORDISPLACEMENT  1600.0  //predefined distance between anchors on collection bin, in mm (was 1700)
#define MID_DIST 300.0              //set distance to center of robot
#define TAG_DIST 460.0              //was 460
#define magnitude TAG_DIST
#define Samples 50
#define SCALING_GYRO 0.98           // 0.0151


#define AVERAGEAMOUNT 10            //changed, needed more memory


    void PozyxBoot(); //Boots up Pozyx System, RUN THIS IN SETUP.
    void updateCoordinates(); //Mesh together calculateX1, X2, Y1 and Y2 methods together here  -> not in use quite yet (uses typedef struct; allocate to a namespace?)
    double calculateX1Position();
    double calculateX2Position();
    double calculateY1Position();
    double calculateY2Position();
    void printBasicXY();
    void printCH();
    void printGyro();
    void updateStatus();
    void updateHeading();

    void BufferAddVal(uint16_t *buff, uint8_t *head, double val);

    void calibrateGyro();
    void adjustHeading();

    int updateTagAngles(uint32_t distanceVals1, uint32_t distanceVals2, bool remote_flag);
    double getBuffAvg(uint16_t *buff);

    void calculateCenter();
    AngleDist(double a1, double a2);

    int getPozyx_X();
    int getPozyx_Y();
    int getPozyx_H();


    int variance(uint32_t a[], int n);
    bool isWithinFloat(double sample, double lowBound, double highBound);


#ifdef	__cplusplus
}
#endif

#endif	/* POZYXWRAPPER_H */

