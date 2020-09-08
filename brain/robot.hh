#ifndef ROBOT_HH
#define ROBOT_HH

#include <gazebo/gazebo_config.h>
#include <gazebo/transport/transport.hh>
#include <gazebo/msgs/msgs.hh>
#include <gazebo/gazebo_client.hh>

class Robot {
  public:
    void (*on_update)(Robot*);

    std::vector<float> ranges;
    float pos_x;
    float pos_y;

    gazebo::transport::NodePtr node;
    gazebo::transport::PublisherPtr turn_pub;
    gazebo::transport::PublisherPtr vel_pub;
    gazebo::transport::SubscriberPtr scan_sub;

    Robot(int argc, char* argv[], void (*cb)(Robot*));
    ~Robot();

    void wait();
    void set_vel(double vel);
    void set_turn(double turn);
    void on_scan(ConstLaserScanStampedPtr &msg);
};

#endif