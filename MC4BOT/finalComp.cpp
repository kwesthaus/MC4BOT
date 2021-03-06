// Required proteus firmware libraries
#include <FEHUtility.h>
#include <FEHLCD.h>
#include <FEHSD.h>
#include <FEHIO.h>
#include <FEHServo.h>
#include <FEHMotor.h>

// Required personal libraries
#include "include/constants.h"
#include "include/globals.h"
#include "include/functions.h"

// Try not to print anything to LCD in this file.
//   functions.cpp should be the single point-of-change
//   for data logging

void finalComp() {

    // Init sequence
    // If testing without RPS, remember to change in initRobot() function
    initRobot();
    printInit();
    competitionStart();

    // Moving from start box to DDR light
    {

        // Robot starts at (9.5, 12.5)
        rpsCheckHeadingDynamic(312.0);
        rpsCheckYCoordDynamic(12.5);

        // Move forward/northeast
        driveForDistanceProportion(2.4, MotorPercentStrong, DirectionForward);
        Sleep(ACTION_SEP_PAUSE);
        rpsCheckHeadingDynamic(312.0);
        rpsCheckYCoordDynamic(14.2);

        // Robot should now be at (11.2, 14.2)

        // Rotate CW
        turnForAngleProportion(45.0, MotorPercentMedium, DirectionClockwise);
        Sleep(ACTION_SEP_PAUSE);
        rpsCheckHeadingDynamic(270.0);
        rpsCheckXCoordDynamic(11.5 + g_adjustX);

        // Robot should now be at (11.5, 12.8)

        // Move forward/east
        driveForDistanceProportion(12.8, MotorPercentStrong, DirectionForward);
        Sleep(ACTION_SEP_PAUSE);
        rpsCheckHeadingDynamic(267.0);
        rpsCheckXCoordDynamic(24.3 + g_adjustX);

    }

    // Completing DDR machine interactions
    // Robot before this split is at (24.3, 12.8)

    if( g_cdsCell.Value() < CDS_CELL_DIV_BLUE_RED ) {

        SD.Printf("MECH-DDR-LIGHT:{CdS Value: %f}\n", g_cdsCell.Value());
        
        // Red light
        LCD.SetBackgroundColor(RED);

        driveForDistanceProportion(2.7, MotorPercentStrong, DirectionForward);
        Sleep(ACTION_SEP_PAUSE);
        rpsCheckHeadingDynamic(267.0);
        rpsCheckXCoordDynamic(27.0 + g_adjustX);

        // Robot should now be at (27.0, 12.8)

        // Rotate CW
        turnForAngleProportion(90.0, MotorPercentMedium, DirectionClockwise);
        Sleep(ACTION_SEP_PAUSE);
        rpsCheckHeadingDynamic(177.0);
        rpsCheckYCoordDynamic(11.8 + g_adjustY);

        // Robot should now be at (25.0, 11.8)

        // Move forward/south
        //   Note that proportional driving is not used so that the
        //   motors will be strong enough to keep moving forward until
        //   the encoder counts are reached even if the robot runs up
        //   against the DDR machine
        driveForDistance(3.7, MotorPercentMedium, DirectionForward);
        Sleep(ACTION_SEP_PAUSE);
        rpsCheckHeadingDynamic(177.0);

        // Mechanism
        rpsResetPress(SERVO_LEVER_RED_ACTIVE);

        // Robot should now be at (25.0, 9.1)

        // Move backward/north
        driveForDistanceProportion(3.9, MotorPercentStrong, DirectionBackward);
        Sleep(ACTION_SEP_PAUSE);
        rpsCheckHeadingDynamic(177.0);
        rpsCheckYCoordDynamic(13.0 + g_adjustY);

        // Robot should now be at (25.0, 13.0)

        // Rotate CCW
        turnForAngleProportion(90.0, MotorPercentMedium, DirectionCounterClockwise);
        Sleep(ACTION_SEP_PAUSE);
        rpsCheckHeadingDynamic(267.0);
        rpsCheckXCoordDynamic(27.4 + g_adjustX);

        // Robot should now be at (27.4, 14.2)

        // Move forward/east
        driveForDistanceProportion(3.6, MotorPercentStrong, DirectionForward);
        Sleep(ACTION_SEP_PAUSE);
        rpsCheckHeadingDynamic(267.0);
        rpsCheckXCoordDynamic(30.9 + g_adjustX);

        // Robot should now be at (30.9, 14.2)

        // Rotate CCW
        turnForAngleProportion(90.0, MotorPercentMedium, DirectionCounterClockwise);
        Sleep(ACTION_SEP_PAUSE);
        rpsCheckHeadingDynamic(357.0);
        rpsCheckYCoordDynamic(16.6 + g_adjustY);

        // Robot is now facing ramp at (29.7, 16.6)

    } else {

        SD.Printf("MECH-DDR-LIGHT:{CdS Value: %f}\n", g_cdsCell.Value());

        // Blue light
        LCD.SetBackgroundColor(BLUE);

        // Move forward/east
        driveForDistanceProportion(6.6, MotorPercentStrong, DirectionForward);
        Sleep(ACTION_SEP_PAUSE);
        rpsCheckHeadingDynamic(267.0);
        rpsCheckXCoordDynamic(30.9 + g_adjustX);

        // Robot should now be at (30.9, 12.8)

        // Rotate CW
        turnForAngleProportion(90.0, MotorPercentMedium, DirectionClockwise);
        Sleep(ACTION_SEP_PAUSE);
        rpsCheckHeadingDynamic(177.0);
        rpsCheckYCoordDynamic(11.8 + g_adjustY);

        // Robot should now be at (28.9, 11.8)

        // Move forward/south
        driveForDistance(3.6, MotorPercentMedium, DirectionForward);
        Sleep(ACTION_SEP_PAUSE);
        rpsCheckHeadingDynamic(177.0);

        // Mechanism
        rpsResetPress(SERVO_LEVER_BLUE_ACTIVE);

        // Robot should now be at (28.9, 9.2)

        // Move backward/north
        driveForDistanceProportion(3.8, MotorPercentStrong, DirectionBackward);
        Sleep(ACTION_SEP_PAUSE);
        rpsCheckHeadingDynamic(177.0);
        rpsCheckYCoordDynamic(13.0 + g_adjustY);

        // Robot should now be at (28.9, 13.0)

        // Rotate CCW
        turnForAngleProportion(90.0, MotorPercentMedium, DirectionCounterClockwise);
        Sleep(ACTION_SEP_PAUSE);
        rpsCheckHeadingDynamic(267.0);
        rpsCheckXCoordDynamic(31.2 + g_adjustX);

        // Robot should now be at (31.2, 14.2)

        driveForDistanceProportion(0.3, MotorPercentStrong, DirectionBackward);
        Sleep(ACTION_SEP_PAUSE);
        rpsCheckHeadingDynamic(267.0);
        rpsCheckXCoordDynamic(30.9);

        // Rotate CCW
        turnForAngleProportion(90.0, MotorPercentMedium, DirectionCounterClockwise);
        Sleep(ACTION_SEP_PAUSE);
        rpsCheckHeadingDynamic(357.0);
        rpsCheckYCoordDynamic(16.6 + g_adjustY);

        // Robot is now facing ramp at (29.7, 16.6)

    }

    // Moving from DDR machine to foosball counter
    {

        // Move forward/north, up ramp
        //   Maintain check here - last spot before upper-level RPS!
        driveForDistanceProportion(36.4, MotorPercentStrong, DirectionForward);
        Sleep(ACTION_SEP_PAUSE);
        rpsCheckHeadingDynamic(0.0);
        rpsCheckYCoordDynamic(53.0 + g_adjustY);

        // Move forward/north, across upper level
        driveForDistanceProportion(14.1, MotorPercentStrong, DirectionForward);
        Sleep(ACTION_SEP_PAUSE);
        rpsCheckHeadingDynamic(357.0);
        rpsCheckYCoordDynamic(67.1 + g_adjustY);

        // Rotate CCW
        turnForAngleProportion(90.0, MotorPercentMedium, DirectionCounterClockwise);
        Sleep(ACTION_SEP_PAUSE);
        rpsCheckHeadingDynamic(87.0);
        rpsCheckXCoordDynamic(27.7 + g_adjustX);

    }

    // Completing foosball counter interactions
    {

        // Mechanism
        foosballDeploy();
        Sleep(ACTION_SEP_PAUSE);

        // Move counter slider
        //   Note that the right side is 22% stronger to account for friction from the arm
        turnForRatioTime(3.3, MotorPercentMedium, DirectionCounterClockwise, 0.78);
        
        // Mechanism and re-align, because sliding might mess up driving
        foosballRetract();

        turnForAngleProportion(15.0, MotorPercentMedium, DirectionCounterClockwise);
        Sleep(ACTION_SEP_PAUSE);
        rpsCheckHeadingDynamic(98.0);
        rpsCheckXCoordDynamic(17.6 + g_adjustX);

    }

    // Moving to and completing claw game joystick interactions
    {

        // Move forward/west
        driveForDistanceProportion(11.2, MotorPercentStrong, DirectionForward);
        Sleep(ACTION_SEP_PAUSE);
        rpsCheckHeadingDynamic(98.0);
        rpsCheckXCoordDynamic(6.5 + g_adjustX);

        // Rotate CW
        turnForAngleProportion(55.0, MotorPercentMedium, DirectionClockwise);
        Sleep(ACTION_SEP_PAUSE);
        rpsCheckHeadingDynamic(42.0);

        // Move forward to lever
        driveForDistance(2.0, MotorPercentStrong, DirectionForward);
        Sleep(ACTION_SEP_PAUSE);

        // Mechanism
        flipLever();
        Sleep(ACTION_SEP_PAUSE);

        // Move backward/southeast to knock claw joystick down
        driveForDistance(1.0, MotorPercentStrong, DirectionBackward);
        Sleep(ACTION_SEP_PAUSE);
        rpsCheckHeadingDynamic(42.0);

        // Mechanism
        flipLeverReset();

        // Move backward/southeast
        //   Fine if we knock the icosahedron down, because WE HAVE TREADS
        driveForDistanceProportion(1.0, MotorPercentStrong, DirectionBackward);
        Sleep(ACTION_SEP_PAUSE);
        rpsCheckHeadingDynamic(42.0);

        // Rotate CCW
        turnForAngleProportion(90.0, MotorPercentMedium, DirectionCounterClockwise);
        Sleep(ACTION_SEP_PAUSE);
        rpsCheckHeadingDynamic(132.0);

    }

    // Moving to and completing coin machine interactions
    {

        // Move forward/southwest
        driveForDistanceProportion(6.0, MotorPercentStrong, DirectionForward);
        Sleep(ACTION_SEP_PAUSE);
        rpsCheckHeadingDynamic(132.0);

        // Rotate CCW
        turnForAngleProportion(45.0, MotorPercentMedium, DirectionCounterClockwise);
        Sleep(ACTION_SEP_PAUSE);
        rpsCheckHeadingDynamic(177.0);
        // Can throw an rpsCheckYCoordDynamic() check in here once we know proper distance value

        // Move forward/south
        driveForDistanceProportion(10.0, MotorPercentStrong, DirectionForward);
        Sleep(ACTION_SEP_PAUSE);
        rpsCheckHeadingDynamic(177.0);
        rpsCheckYCoordDynamic(46.3 + g_adjustY);

        // Robot is now at (5.0, 46.3)

        // Rotate CW
        turnForAngleProportion(90.0, MotorPercentMedium, DirectionClockwise);
        Sleep(ACTION_SEP_PAUSE);
        rpsCheckHeadingDynamic(87.0);
        rpsCheckXCoordDynamic(4.0 + g_adjustX);

        // Robot is now at (4.0, 48.3)

        // Move backward/east
        driveForDistanceProportion(9.0, MotorPercentStrong, DirectionBackward);
        Sleep(ACTION_SEP_PAUSE);
        rpsCheckHeadingDynamic(87.0);
        rpsCheckXCoordDynamic(13.0 + g_adjustX);

        // Robot is now at (13.0, 48.3)

        // Rotate CW
        turnForAngleProportion(90.0, MotorPercentMedium, DirectionClockwise);
        Sleep(ACTION_SEP_PAUSE);
        rpsCheckHeadingDynamic(357.0);
        rpsCheckYCoordDynamic(49.3 + g_adjustY);

        // Robot is now at (15.0, 49.3)

        // Move backward/south
        //   Note that proportional driving is not used so that the
        //   motors will be strong enough to keep moving backward until
        //   the encoder counts are reached even if the robot runs up
        //   against the coin machine
        driveForDistance(6.0, MotorPercentMedium, DirectionBackward);
        Sleep(ACTION_SEP_PAUSE);
        rpsCheckHeadingDynamic(357.0);

        // Mechanism
        coinRelease();
        Sleep(ACTION_SEP_PAUSE);

        // Robot is now at (15.0, 44.3)

        // Move forward/north
        driveForDistanceProportion(4.0, MotorPercentStrong, DirectionForward);
        Sleep(ACTION_SEP_PAUSE);
        rpsCheckHeadingDynamic(357.0);
        rpsCheckYCoordDynamic(48.3 + g_adjustY);

        // Robot is now at (15.0, 48.3)

    }

    // Moving to and pushing final button
    {
        
        // Rotate CCW
        turnForAngleProportion(90.0, MotorPercentMedium, DirectionCounterClockwise);
        Sleep(ACTION_SEP_PAUSE);
        rpsCheckHeadingDynamic(87.0);
        rpsCheckXCoordDynamic(12.6 + g_adjustX);

        // Robot is now at (12.6, 47.1)

        // Move forward/west
        driveForDistanceProportion(9.7, MotorPercentStrong, DirectionForward);
        Sleep(ACTION_SEP_PAUSE);
        rpsCheckHeadingDynamic(87.0);
        rpsCheckXCoordConstant(2.9 + g_adjustX);

        // Robot is now at (2.9, 47.1)

        // Rotate CCW
        turnForAngleProportion(90.0, MotorPercentMedium, DirectionCounterClockwise);
        Sleep(ACTION_SEP_PAUSE);
        // Note this angle is slightly different, to angle towards button
        rpsCheckHeadingDynamic(180.0);
        rpsCheckYCoordDynamic(44.7 + g_adjustY);

        // Robot is now at (4.1, 44.7)

        // Move forward/south
        driveForDistanceProportion(20.0, MotorPercentStrong, DirectionForward);
        rpsCheckHeadingDynamic(180.0);
        driveForDistanceProportion(25.0, MotorPercentStrong, DirectionForward);
        // Turn towards final button if not there already
        turnForAngleProportion(45.0, MotorPercentStrong, DirectionClockwise);

    }

    // By this point the robot should have hit the final button and turned itself off

    SD.CloseLog();

    return;
}
