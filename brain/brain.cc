
#include <iostream>
#include <math.h>

#include "robot.hh"

using std::cout;
using std::endl;

const double goal_x = 20.0;
const double goal_y = 0.0;
bool done = false;
double phi = 0;

void
callback(Robot* robot)
{
    /*
    cout << endl;
    cout << "robot x =" << robot->pos_x << endl;
    cout << "robot y =" << robot->pos_y << endl;
    */
    double dx = goal_x - robot->pos_x;
    double dy = goal_y - robot->pos_y;
    if (abs(dx) < 0.75 && abs(dy) < 0.75) {
        cout << "we win!" << endl;
        robot->set_vel(0.0);
        robot->set_turn(0.0);
        robot->done();
        return;
    }

    bool turn = false;

    for (LaserHit hit : robot->hits) {
        if (hit.range < 1.55) {
            if (hit.angle < 0.55 || hit.angle > (6.2 - 0.5)) {
                turn = true;
            }
        }
    }

    if (turn) {
        robot->set_vel(3.0);
        robot->set_turn(0.5);
    }
    /**
     * Solution for HW01:
     * If the robot is not in range of an obstacle, the arctan between
     * dx and dy will be calculated and subtracted from 90 degrees (radians).
     * This angle is defined as the phi angle.
     * This will then be used in logic to determine if the robot must turn.
     * It will only turn if it is not within a certain range of the phi angle.
     */
    else {
	phi = (3.14159/2) - atan2(dx, dy);	// phi angle calculation

	// logic used to determine if the robot is on the right track within a
	// certain range of precision
	if ((phi - robot->pos_t) >= 0.1 || (phi - robot->pos_t) < -0.1) {
	    // if the target is to the left of the robot's heading, turn left
	    if (phi > robot->pos_t) {
                robot->set_turn(-0.15);
                robot->set_vel(3.0);
	    }
	    // if the target is to the right of the robot's heading, turn right
	    else {
                robot->set_turn(0.15);
                robot->set_vel(3.0);
	    }
	}
	// if the robot is within the range needed to get to the target,
	// continue at full speed
	else {
            robot->set_vel(10.0);
	    robot->set_turn(0.0);
	}
    }
}

// end of solution for HW01

int
main(int argc, char* argv[])
{
    cout << "making robot" << endl;
    Robot robot(argc, argv, callback);
    robot.do_stuff();

    return 0;
}
