// Required proteus firmware libraries
#include <FEHMotor.h>
#include <FEHServo.h>
#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHRPS.h>

// Required personal libraries
#include "include/constants.h"
#include "include/globals.h"
#include "include/functions.h"

// Required C++ libraries
#include <cmath>

// Init functions //////////////////////////////////////////

void initRobot() {
    LCD.Clear( FEHLCD::Black );
    LCD.SetFontColor( FEHLCD::White );
    servoLever.SetMin(SERVO_LEVER_MIN);
    servoLever.SetMax(SERVO_LEVER_MAX);
    flipLeverReset();
    servoCoin.SetMin(SERVO_COIN_MIN);
    servoCoin.SetMax(SERVO_COIN_MAX);
    servoCoin.SetDegree(SERVO_COIN_POS_NEUTRAL);
    servoClaw.SetMin(SERVO_CLAW_MIN);
    servoClaw.SetMax(SERVO_CLAW_MAX);
    servoClaw.SetDegree(SERVO_CLAW_POS_NEUTRAL);
    return;
}

void printInit() {
    // Print info for drive motors
    LCD.Write("Left Motor Init-{");
    LCD.Write("Port:");
    LCD.Write(MOTOR_PORT_FL);
    LCD.Write(",Volts:");
    LCD.Write(MOTOR_VOLTS);
    LCD.WriteLine("}");

    LCD.Write("Right Motor Init-{");
    LCD.Write("Port:");
    LCD.Write(MOTOR_PORT_FR);
    LCD.Write(",Volts:");
    LCD.Write(MOTOR_VOLTS);
    LCD.WriteLine("}");

    Sleep(1.0);

    // Print info for servo motors
    LCD.Write("Lever Servo Init-{");
    LCD.Write("Port:");
    LCD.Write(SERVO_PORT_LEVER);
    LCD.Write(",Min:");
    LCD.WriteLine(SERVO_LEVER_MIN);
    LCD.Write(",Max:");
    LCD.Write(SERVO_LEVER_MAX);
    LCD.WriteLine("}");

    LCD.Write("Coin Servo Init-{");
    LCD.Write("Port:");
    LCD.Write(SERVO_PORT_COIN);
    LCD.Write(",Min:");
    LCD.WriteLine(SERVO_COIN_MIN);
    LCD.Write(",Max:");
    LCD.Write(SERVO_COIN_MAX);
    LCD.WriteLine("}");

    LCD.Write("Claw Servo Init-{");
    LCD.Write("Port:");
    LCD.Write(SERVO_PORT_CLAW);
    LCD.Write(",Min:");
    LCD.WriteLine(SERVO_CLAW_MIN);
    LCD.Write(",Max:");
    LCD.Write(SERVO_CLAW_MAX);
    LCD.WriteLine("}");

    Sleep(1.0);

    // Print info for sensors
    LCD.Write("CdS Cell Init-{");
    LCD.Write("Port:");
    LCD.Write(CDS_CELL_PORT);
    LCD.Write(",Thresh:");
    LCD.Write(CDS_CELL_START_THRESH);
    LCD.WriteLine("}");

    LCD.Write("Encoder left port: ");
    LCD.WriteLine(ENCODER_LEFT_PORT);
    LCD.Write("Encoder right port: ");
    LCD.WriteLine(ENCODER_RIGHT_PORT);
    LCD.Write("Encoder counts/inch: ");
    LCD.WriteLine(ENCODER_CTS_PER_INCH);

    LCD.WriteLine("Init complete.");
    return;
}

////////////////////////////////////////////////////////////
// Test functions //////////////////////////////////////////

void testDrive() {
    motorLeft.SetPercent(100);
    motorRight.SetPercent(-100);
    Sleep(3.0);
    motorLeft.SetPercent(-100);
    motorRight.SetPercent(100);
    Sleep(3.0);
    motorLeft.Stop();
    motorRight.Stop();
    return;
}

void testSensors() {
    encoderLeft.ResetCounts();
    encoderRight.ResetCounts();
    while(true) {
        LCD.Write("CdS: ");
        LCD.WriteLine(cdsCell.Value());
        LCD.Write("Left encoder: ");
        LCD.WriteLine(encoderLeft.Counts());
        LCD.Write("Right encoder: ");
        LCD.WriteLine(encoderRight.Counts());
        Sleep(0.3);
    }
}

void testRPS() {
    float touch_x, touch_y;
    RPS.InitializeTouchMenu();

    LCD.WriteLine("Press Screen to Start");
    while(!LCD.Touch(&touch_x, &touch_y));

    LCD.Clear();

    LCD.WriteRC("RPS Test Program", 0, 0);
    LCD.WriteRC("X Position: ", 2, 0);
    LCD.WriteRC("Y Position: ", 3, 0);
    LCD.WriteRC("   Heading: ", 4, 0);

    while(true) {
        LCD.WriteRC(RPS.X(), 2, 13);
        LCD.WriteRC(RPS.Y(), 3, 13);
        LCD.WriteRC(RPS.Heading(), 4, 13);

        Sleep(10); // 10ms
    }
    // Will never exit infinite loop to reach here
    return;
}

void testDistance() {
    driveForDistance(50.0, MotorPercentMedium, DirectionForward);
    LCD.Write("left: ");
    LCD.WriteLine(encoderLeft.Counts());
    LCD.Write("right: ");
    LCD.WriteLine(encoderRight.Counts());
}

void testDirections() {
    LCD.WriteLine(MotorPercentMedium * MOTOR_SIDE_DIR_CORRECTOR);
    LCD.WriteLine("turn right");
    turnForAngle(30, MotorPercentMedium, DirectionClockwise);
    Sleep(2.0);
    LCD.WriteLine("turn left");
    turnForAngle(30, MotorPercentMedium, DirectionCounterClockwise);
    Sleep(2.0);
    LCD.WriteLine("forwards");
    driveForDistance(2.0, MotorPercentMedium, DirectionForward);
    Sleep(2.0);
    LCD.WriteLine("backwards");
    driveForDistance(2.0, MotorPercentMedium, DirectionBackward);
    Sleep(4.0);
}

void testFunctions() {
    driveForDistance(4.0, MotorPercentMedium, DirectionForward);
    driveForTime(4.0, MotorPercentMedium, DirectionBackward);
    turnForAngle(90, MotorPercentMedium, DirectionClockwise);
    turnForTime(2.0, MotorPercentMedium, DirectionCounterClockwise);
    turnToCourseAngle(90, 180, MotorPercentMedium);
    turnToCourseAngle(90, 0, MotorPercentMedium);
    LCD.WriteLine("Done");
}

void testTreadTurns() {
   while(true) {
       turnForAngle(180, MotorPercentMedium, DirectionClockwise);
       Sleep(1.0);
       turnForAngle(180, MotorPercentMedium, DirectionCounterClockwise);
       Sleep(1.0);
   }
}

void testServos() {
    LCD.WriteLine("servo time");
    servoLever.SetDegree(180);
    LCD.WriteLine(180);
    Sleep(2.0);
    servoLever.SetDegree(135);
    LCD.WriteLine(135);
    Sleep(2.0);
    servoLever.SetDegree(90);
    LCD.WriteLine(90);
    Sleep(2.0);
    servoLever.SetDegree(45);
    LCD.WriteLine(45);
    Sleep(2.0);
}

////////////////////////////////////////////////////////////
// Mechanism functions /////////////////////////////////////

void flipLever() {
    servoLever.SetDegree(SERVO_LEVER_POS_ACTIVE);
    return;
}

void flipLeverReset() {
    servoLever.SetDegree(SERVO_LEVER_POS_NEUTRAL);
    return;
}

void rpsResetPress() {
    int currAngle = SERVO_LEVER_POS_NEUTRAL;
    // Slow down the servo motor's movement so that it has more torque
    // 90degrees difference * 0.02seconds per degree = 1.8 secons 
    while(currAngle > SERVO_LEVER_POS_ACTIVE) {
        servoLever.SetDegree(currAngle);
        currAngle--;
        Sleep(SERVO_LEVER_ITER_PAUSE);
    }
    Sleep(SERVO_LEVER_RESET_PAUSE);
    while(currAngle < SERVO_LEVER_POS_NEUTRAL) {
        servoLever.SetDegree(currAngle);
        currAngle++;
        Sleep(SERVO_LEVER_ITER_PAUSE);
    }
    return;
}

////////////////////////////////////////////////////////////
// Drive functions /////////////////////////////////////////

void driveForDistance(double inches, MotorPower motorPercent, DriveDirection direction) {
    encoderLeft.ResetCounts();
    encoderRight.ResetCounts();
    double expectedEncoderCounts = inches * ENCODER_CTS_PER_INCH;
    LCD.Write("Exp enc counts: ");
    LCD.WriteLine(expectedEncoderCounts);
    if(direction == DirectionForward) {
        LCD.WriteLine("Going FW");
        motorLeft.SetPercent(motorPercent);
        motorRight.SetPercent(motorPercent * MOTOR_SIDE_DIR_CORRECTOR * MOTOR_SIDE_STR_CORRECTOR);
    } else {
        LCD.WriteLine("Going BW");
        motorLeft.SetPercent(motorPercent * MOTOR_SIDE_DIR_CORRECTOR);
        motorRight.SetPercent(motorPercent * MOTOR_SIDE_STR_CORRECTOR);
    }
    while( ( encoderLeft.Counts() + encoderRight.Counts() ) / 2.0 < expectedEncoderCounts);
    motorLeft.Stop();
    motorRight.Stop();
    LCD.WriteLine("--- Drive Done ---");
    return;
}

void driveForTime(double seconds, MotorPower motorPercent, DriveDirection direction) {
    if(direction == DirectionForward) {
        LCD.WriteLine("Going FW");
        motorLeft.SetPercent(motorPercent);
        motorRight.SetPercent(motorPercent * MOTOR_SIDE_DIR_CORRECTOR * MOTOR_SIDE_STR_CORRECTOR);
    } else {
        LCD.WriteLine("Going BW");
        motorLeft.SetPercent(motorPercent * MOTOR_SIDE_DIR_CORRECTOR);
        motorRight.SetPercent(motorPercent * MOTOR_SIDE_STR_CORRECTOR);
    }
    LCD.Write("Drive time: ");
    LCD.WriteLine(seconds);
    Sleep(seconds);
    motorLeft.Stop();
    motorRight.Stop();
    LCD.WriteLine("--- Drive Done ---");
    return;
}

void turnForTime(double seconds, MotorPower motorPercent, TurnDirection direction) {
    if(direction == DirectionClockwise) {
        LCD.WriteLine("Going CW");
        motorLeft.SetPercent(motorPercent);
        motorRight.SetPercent(motorPercent * MOTOR_SIDE_STR_CORRECTOR);
    } else {
        LCD.WriteLine("Going CNTCW");
        motorLeft.SetPercent(motorPercent * MOTOR_SIDE_DIR_CORRECTOR);
        motorRight.SetPercent(motorPercent * MOTOR_SIDE_DIR_CORRECTOR * MOTOR_SIDE_STR_CORRECTOR);
    }
    LCD.Write("Turn time: ");
    LCD.WriteLine(seconds);
    Sleep(seconds);
    motorLeft.Stop();
    motorRight.Stop();
    LCD.WriteLine("--- Turn Done ---");
    return;
}

void turnForRatioTime(double seconds, MotorPower motorPercent, TurnDirection direction, double motorRatio) {
    if(direction == DirectionClockwise) {
        LCD.Write("Going CW, ratio ");
        LCD.WriteLine(motorRatio);
        motorLeft.SetPercent(motorPercent);
        motorRight.SetPercent(motorPercent * motorRatio * MOTOR_SIDE_DIR_CORRECTOR * MOTOR_SIDE_STR_CORRECTOR);
    } else {
        LCD.Write("Going CNTCW, ratio ");
        LCD.WriteLine(motorRatio);
        motorLeft.SetPercent(motorPercent * motorRatio);
        motorRight.SetPercent(motorPercent * MOTOR_SIDE_DIR_CORRECTOR * MOTOR_SIDE_STR_CORRECTOR);
    }
    LCD.Write("Turn time: ");
    LCD.WriteLine(seconds);
    Sleep(seconds);
    motorLeft.Stop();
    motorRight.Stop();
    LCD.WriteLine("--- Turn Done ---");
    return;
}

void turnForAngle(int targetAngle, MotorPower motorPercent, TurnDirection direction) {
    encoderLeft.ResetCounts();
    encoderRight.ResetCounts();
    double arcLength = (targetAngle / 360.0) * ROBOT_TURN_CIRC;
    LCD.Write("Turn arc length: ");
    LCD.WriteLine(arcLength);   
    double expectedEncoderCounts = arcLength * ENCODER_CTS_PER_INCH;
    LCD.Write("Exp enc counts: ");
    LCD.WriteLine(expectedEncoderCounts);
    if(direction == DirectionClockwise) {
        LCD.WriteLine("Going CW");
        motorLeft.SetPercent(motorPercent);
        motorRight.SetPercent(motorPercent * MOTOR_SIDE_STR_CORRECTOR);
    } else {
        LCD.WriteLine("Going CNTCW");
        motorLeft.SetPercent(motorPercent * MOTOR_SIDE_DIR_CORRECTOR);
        motorRight.SetPercent(motorPercent * MOTOR_SIDE_DIR_CORRECTOR * MOTOR_SIDE_STR_CORRECTOR);
    }
    while( ( encoderLeft.Counts() + encoderRight.Counts() ) / 2.0 < expectedEncoderCounts);
    motorLeft.Stop();
    motorRight.Stop();
    LCD.WriteLine("--- Turn Done ---");
    return;
}

void turnToCourseAngle(int currentAngle, int targetAngle, MotorPower motorPercent) {
    if(currentAngle > targetAngle) {
        if( (currentAngle - targetAngle) < 180) {
            LCD.Write("Turn deg: ");
            LCD.WriteLine( (currentAngle - targetAngle) );
            turnForAngle( (currentAngle - targetAngle) , motorPercent, DirectionClockwise );
        } else {
            LCD.Write("Turn deg: ");
            LCD.WriteLine( 360 - (currentAngle - targetAngle) );
            turnForAngle( 360 - (currentAngle - targetAngle) , motorPercent, DirectionCounterClockwise );
        }
    } else {
        if( (targetAngle - currentAngle) < 180) {
            LCD.Write("Turn deg: ");
            LCD.WriteLine( (targetAngle - currentAngle) );
            turnForAngle( (targetAngle - currentAngle) , motorPercent, DirectionCounterClockwise );
        } else {
            LCD.Write("Turn deg: ");
            LCD.WriteLine( 360 - (targetAngle - currentAngle) );
            turnForAngle( 360 - (targetAngle - currentAngle) , motorPercent, DirectionClockwise );
        }
    }
    return;
}

//void driveUntil(int motorPower, special type for function pointer CALLBACKFUNC) {}

// Use RPS to get current heading, then calculate appropriate turn to reach target
void turnToCourseAngle(int targetAngle, MotorPower motorPercent) {
    float firstHeading = RPS.Heading();
    Sleep(0.5);
    float secondHeading = RPS.Heading();
    float currentHeading = (firstHeading + secondHeading) / 2.0;
    int currentAngle = static_cast<int>(currentHeading);
    turnToCourseAngle(currentAngle, targetAngle, motorPercent);
    return;
}

////////////////////////////////////////////////////////////
// RPS functions ///////////////////////////////////////////

void rpsCheckHeading(float targetHeading) {
    while( std::abs(RPS.Heading() - targetHeading) > 5.0) {
        float headingDifference = RPS.Heading() - targetHeading;
        LCD.Write("Target angle diff: ");
        LCD.WriteLine(headingDifference);
        if(headingDifference > 0 && headingDifference < 180) {
            turnForAngle(2, MotorPercentWeak, DirectionClockwise);
        } else if(headingDifference < 0 && headingDifference > -180) {
            turnForAngle(2, MotorPercentWeak, DirectionCounterClockwise);
        } else if(headingDifference > 180) {
            turnForAngle(2, MotorPercentWeak, DirectionCounterClockwise);
        } else if(headingDifference < -180) {
            turnForAngle(2, MotorPercentWeak, DirectionClockwise);
        }
    }
    return;
}

void rpsCheckXCoord(float targetX) {
    float currentHeading = RPS.Heading();
    bool facingPlus;
    if(currentHeading > 90 && currentHeading < 270) {
        facingPlus = true;
    } else {
        facingPlus = false;
    }
    while( std::abs(RPS.X() - targetX) > 1.0 ) {
        if(RPS.X() < targetX && facingPlus) {
            driveForDistance(0.5, MotorPercentWeak, DirectionForward);
        } else if(RPS.X() > targetX && facingPlus) {
            driveForDistance(0.5, MotorPercentWeak, DirectionBackward);
        } else if(RPS.X() < targetX && !facingPlus) {
            driveForDistance(0.5, MotorPercentWeak, DirectionBackward);
        } else if(RPS.X() > targetX && !facingPlus) {
            driveForDistance(0.5, MotorPercentWeak, DirectionForward);
        }
    }
    return;
}

void rpsCheckYCoord(float targetY) {
    float currentHeading = RPS.Heading();
    bool facingPlus;
    if(currentHeading > 0 && currentHeading < 180) {
        facingPlus = true;
    } else {
        facingPlus = false;
    }
    while( std::abs(RPS.Y() - targetY) > 1.0 ) {
        if(RPS.Y() < targetY && facingPlus) {
            driveForDistance(0.5, MotorPercentWeak, DirectionForward);
        } else if(RPS.Y() > targetY && facingPlus) {
            driveForDistance(0.5, MotorPercentWeak, DirectionBackward);
        } else if(RPS.Y() < targetY && !facingPlus) {
            driveForDistance(0.5, MotorPercentWeak, DirectionBackward);
        } else if(RPS.Y() > targetY && !facingPlus) {
            driveForDistance(0.5, MotorPercentWeak, DirectionForward);
        }
    }
    return;
}

// Wrap RPS.Heading() for some automatic error detection
float rpsSampleHeading() {
    // Keep track of how many times we resample to avoid an incorrect value
    int extraAttempts = 0;
    float sampleOne, sampleTwo, sampleThree, sampleFinal;
    sampleOne = RPS.Heading();
    // If sample outside of range and we haven't exceeded the max number of
    //   incorrect values, try again
    while( (sampleOne < 0.0 || sampleOne > 360.0) && extraAttempts < 3 ) {
        extraAttempts++;
        sampleOne = RPS.Heading();
    }
    // At this point, either the sample is good or we've exceeded the max number
    //   of incorrect values. If the sample is bad, quit trying and return an error value
    if(sampleOne < 0.0 || sampleOne > 360.0) {
        return -3.0;
    }
    sampleTwo = RPS.Heading();
    while((sampleTwo < 0.0 || sampleTwo > 360.0) && extraAttempts < 3 ) {
        extraAttempts++;
        sampleTwo = RPS.Heading();
    }
    if(sampleTwo < 0.0 || sampleTwo > 360.0) {
        return -3.0;
    }
    sampleThree = RPS.Heading();
    while((sampleThree < 0.0 || sampleThree > 360.0) && extraAttempts < 3 ) {
        extraAttempts++;
        sampleThree = RPS.Heading();
    }
    if(sampleThree < 0.0 || sampleThree > 360.0) {
        return -3.0;
    }
    // If RPS is returning values that are within range but vary wildly, return an error value
    if(std::abs(sampleOne - sampleTwo) > 5.0 || std::abs(sampleOne - sampleThree) > 5.0) {
        return -3.0;
    }
    // Otherwise, use valid samples to calculate an averaged value and return it
    sampleFinal = (sampleOne + sampleTwo + sampleThree) / 3.0;
    return sampleFinal;
}

// Wrap RPS.X() for some automatic error detection
float rpsSampleXCoord() {
    // Keep track of how many times we resample to avoid an incorrect value
    int extraAttempts = 0;
    float sampleOne, sampleTwo, sampleThree, sampleFinal;
    sampleOne = RPS.X();
    // If sample outside of range and we haven't exceeded the max number of
    //   incorrect values, try again
    while( (sampleOne < 0.0 || sampleOne > 36.0) && extraAttempts < 3 ) {
        extraAttempts++;
        sampleOne = RPS.X();
    }
    // At this point, either the sample is good or we've exceeded the max number
    //   of incorrect values. If the sample is bad, quit trying and return an error value
    if(sampleOne < 0.0 || sampleOne > 36.0) {
        return sampleOne;
    }
    sampleTwo = RPS.X();
    while((sampleTwo < 0.0 || sampleTwo > 36.0) && extraAttempts < 3 ) {
        extraAttempts++;
        sampleTwo = RPS.X();
    }
    if(sampleTwo < 0.0 || sampleTwo > 36.0) {
        return sampleTwo;
    }
    sampleThree = RPS.X();
    while((sampleThree < 0.0 || sampleThree > 36.0) && extraAttempts < 3 ) {
        extraAttempts++;
        sampleThree = RPS.X();
    }
    if(sampleThree < 0.0 || sampleThree > 36.0) {
        return sampleThree;
    }
    // If RPS is returning values that are within range but vary wildly, return an error value
    if(std::abs(sampleOne - sampleTwo) > 5.0 || std::abs(sampleOne - sampleThree) > 5.0) {
        return -3.0;
    }
    // Otherwise, use valid samples to calculate an averaged value and return it
    sampleFinal = (sampleOne + sampleTwo + sampleThree) / 3.0;
    return sampleFinal;
}

// Wrap RPS.Y() for some automatic error detection
float rpsSampleYCoord() {
    // Keep track of how many times we resample to avoid an incorrect value
    int extraAttempts = 0;
    float sampleOne, sampleTwo, sampleThree, sampleFinal;
    sampleOne = RPS.Y();
    // If sample outside of range and we haven't exceeded the max number of
    //   incorrect values, try again
    while( (sampleOne < 0.0 || sampleOne > 72.0) && extraAttempts < 3 ) {
        extraAttempts++;
        sampleOne = RPS.Y();
    }
    // At this point, either the sample is good or we've exceeded the max number
    //   of incorrect values. If the sample is bad, quit trying and return an error value
    if(sampleOne < 0.0 || sampleOne > 72.0) {
        return sampleOne;
    }
    sampleTwo = RPS.Y();
    while((sampleTwo < 0.0 || sampleTwo > 72.0) && extraAttempts < 3 ) {
        extraAttempts++;
        sampleTwo = RPS.Y();
    }
    if(sampleTwo < 0.0 || sampleTwo > 72.0) {
        return sampleTwo;
    }
    sampleThree = RPS.Y();
    while((sampleThree < 0.0 || sampleThree > 72.0) && extraAttempts < 3 ) {
        extraAttempts++;
        sampleThree = RPS.Y();
    }
    if(sampleThree < 0.0 || sampleThree > 72.0) {
        return sampleThree;
    }
    // If RPS is returning values that are within range but vary wildly, return an error value
    if(std::abs(sampleOne - sampleTwo) > 5.0 || std::abs(sampleOne - sampleThree) > 5.0) {
        return -3.0;
    }
    // Otherwise, use valid samples to calculate an averaged value and return it
    sampleFinal = (sampleOne + sampleTwo + sampleThree) / 3.0;
    return sampleFinal;
}

////////////////////////////////////////////////////////////
