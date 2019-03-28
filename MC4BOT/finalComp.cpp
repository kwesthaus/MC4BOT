// Required proteus firmware libraries
#include <FEHUtility.h>
#include <FEHSD.h>

// Required personal libraries
#include "include/constants.h"
#include "include/functions.h"

void finalComp() {
    initRobot();
    //printInit();
    //competitionStart();

    turnForAngleProportion(180.0, MotorPercentMedium, DirectionClockwise);
    Sleep(2.0);

    turnForAngleProportion(180.0, MotorPercentMedium, DirectionCounterClockwise);
    Sleep(2.0);
    return;

    driveForDistanceProportion(30.0, MotorPercentMedium, DirectionForward);
    Sleep(ACTION_SEP_PAUSE);

    turnForAngle(45.0, MotorPercentMedium, DirectionClockwise);
    Sleep(ACTION_SEP_PAUSE);

    rpsCheckHeadingDynamic(270.0);
    Sleep(ACTION_SEP_PAUSE);

    rpsCheckXCoordDynamic(13.0);
    Sleep(ACTION_SEP_PAUSE);

    driveForDistanceProportion(10.0, MotorPercentMedium, DirectionForward);
    Sleep(ACTION_SEP_PAUSE);

    rpsCheckXCoordDynamic(27.0);
    Sleep(ACTION_SEP_PAUSE);

    /*
    | PSEUDOCODE
    |
    | - Wait until cds cell reading is below threshold OR 30 seconds passes, whichever comes first
    | - Drive forward for ~6 inches
    | - Rotate 45degrees clockwise
    | - Drive forward ~8 inches
    | - Rotate 90 degrees clockwise
    | - Detect light color in front of DDR machine using cds cell
    | - Turn to appropriate DDR button
    | - Drive forwards until microswitch is pushed, indicating that DDR button has been pushed
    | - Drop lever servo in order to push RPS reset button, then pick back up
    | - Drive backwards two inches
    | - Rotate 90 degrees counterclockwise
    | - Drive forward 2 inches
    | - Rotate 90 degrees counterclockwise
    | - Drive with motors on high up ramp
    | - Drive across top section until microswitch hits foosball section
    | - Rotate 90 degrees counterclockwise
    | - Extend/grip claw
    | - Drive forwards until front-right microswitch hits far side of foosball section
    | - Release/retract claw
    | - Rotate 20 degrees counterclockwise
    | - Drive fowards 6 inches
    | - Rotate 40 degrees clockwise
    | - Drop lever servo
    | - Drive backwards 2 inches (to pull down lever)
    | - Turn 65 degrees counterclockwise
    | - Drive forward until front-right microswitch hits wall
    | - Rotate 45degrees counterclockwise
    | - Drive 1 foot forward
    | - Turn 90degrees clockwise
    | - Drive 8 inches backwards
    | - Release coin into slot from top level
    | - Drive forward 8 inches
    | - Rotate 90 degrees counterclockwise
    | - Drive forward 1 foot down ramp
    | - Rotate 45 degrees clockwise
    | - Drive forward until we push the finish button
    */

    SD.CloseLog();

    return;
}
