/* ===========================================================
Get data function of the Gesture  
Procedures::
1- Check flag which it should be true if the setup finished with no error
2- Check memory state 
      --reset it if needed 
      --otherwise, check for DMP data ready interrupt 
3- Read the DMP data
4- Present data in three different form depend on user choice 
==============================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "Glib.h"

/* uncomment "OUTPUT_READABLE_QUATERNION" if you want to see the actual
  quaternion components in a [w, x, y, z] format (not best for parsing
  on a remote host such as Processing or something though)*/
//#define OUTPUT_READABLE_QUATERNION

/* uncomment "OUTPUT_READABLE_EULER" if you want to see Euler angles
  (in degrees) calculated from the quaternions coming from the FIFO.
  Note that Euler angles suffer from gimbal lock (for more info, see
  http://en.wikipedia.org/wiki/Gimbal_lock)*/
//#define OUTPUT_READABLE_EULER

/* uncomment "OUTPUT_READABLE_YAWPITCHROLL" if you want to see the yaw/
  pitch/roll angles (in degrees) calculated from the quaternions coming
  from the FIFO. Note this also requires gravity vector calculations.
  Also note that yaw/pitch/roll angles suffer from gimbal lock (for
  more info, see: http://en.wikipedia.org/wiki/Gimbal_lock)*/
#define OUTPUT_READABLE_YAWPITCHROLL

//Get data in four different forms 
void Gdata() 
{
    // if programming failed, don't try to do anything
    if (!dmpReady) return;
    // get current FIFO count
    fifoCount = mpu.getFIFOCount();

    if (fifoCount == 1024) 
    {
        // reset so we can continue cleanly
        mpu.resetFIFO();
        printf("FIFO overflow!\n");

    // otherwise, check for DMP data ready interrupt (this should happen frequently)
    } 
    else if (fifoCount >= 42) 
    {
        // read a packet from FIFO
        mpu.getFIFOBytes(fifoBuffer, packetSize);
        
        #ifdef OUTPUT_READABLE_QUATERNION
            // display quaternion values in easy matrix form: w x y z
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            printf("quat %7.2f %7.2f %7.2f %7.2f    ", q.w,q.x,q.y,q.z);
        #endif

        #ifdef OUTPUT_READABLE_EULER
            // display Euler angles in degrees
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            mpu.dmpGetEuler(euler, &q);
            printf("euler %7.2f %7.2f %7.2f    ", euler[0] * 180/M_PI, euler[1] * 180/M_PI, euler[2] * 180/M_PI);
        #endif

        #ifdef OUTPUT_READABLE_YAWPITCHROLL
            // display Euler angles in degrees
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            mpu.dmpGetGravity(&gravity, &q);
            mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
            printf("Yaw  %5.f    ", ypr[0] * 180/M_PI);
            printf("Pitch %5.f   " ,ypr[1] * 180/M_PI);
            printf("roll %5.f   " ,ypr[2] * 180/M_PI); 
        #endif

        printf("\n");
    }
}
