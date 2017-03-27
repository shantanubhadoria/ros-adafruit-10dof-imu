#include "ros/ros.h"
#include "sensor_msgs/Imu.h"

#include <LSM303DLHC_Magnetometer.h>
#include <LSM303DLHC_Accelerometer.h>
#include <L3GD20H_Gyroscope.h>
#include <LSM303DLHC_Magnetometer.cpp>
#include <LSM303DLHC_Accelerometer.cpp>
#include <L3GD20H_Gyroscope.cpp>
#include <I2CBus.cpp>
#include <unistd.h>

/**
 * This tutorial demonstrates simple sending of messages over the ROS system.
 */
int main(int argc, char **argv)
{
  const char* i2cDevice = "/dev/i2c-1";
  LSM303DLHC_Magnetometer mag(i2cDevice);
  LSM303DLHC_Accelerometer acc(i2cDevice);
  L3GD20H_Gyroscope gyr(i2cDevice);

  gyr.begin();
  mag.begin();
  acc.begin();

  /**
   * The ros::init() function needs to see argc and argv so that it can perform
   * any ROS arguments and name remapping that were provided at the command line.
   * For programmatic remappings you can use a different version of init() which takes
   * remappings directly, but for most command-line programs, passing argc and argv is
   * the easiest way to do it.  The third argument to init() is the name of the node.
   *
   * You must call one of the versions of ros::init() before using any other
   * part of the ROS system.
   */
  ros::init(argc, argv, "talker");

  /**
   * NodeHandle is the main access point to communications with the ROS system.
   * The first NodeHandle constructed will fully initialize this node, and the last
   * NodeHandle destructed will close down the node.
   */
  ros::NodeHandle n;

  /**
   * The advertise() function is how you tell ROS that you want to
   * publish on a given topic name. This invokes a call to the ROS
   * master node, which keeps a registry of who is publishing and who
   * is subscribing. After this advertise() call is made, the master
   * node will notify anyone who is trying to subscribe to this topic name,
   * and they will in turn negotiate a peer-to-peer connection with this
   * node.  advertise() returns a Publisher object which allows you to
   * publish messages on that topic through a call to publish().  Once
   * all copies of the returned Publisher object are destroyed, the topic
   * will be automatically unadvertised.
   *
   * The second parameter to advertise() is the size of the message queue
   * used for publishing messages.  If messages are published more quickly
   * than we can send them, the number here specifies how many messages to
   * buffer up before throwing some away.
   */
  ros::Publisher chatter_pub = n.advertise<sensor_msgs::Imu>("chatter", 100);

  ros::Rate loop_rate(10);

  /**
   * A count of how many messages we have sent. This is used to create
   * a unique string for each message.
   */
  int count = 0;
  while (ros::ok())
  {
    /**
     * This is a message object. You stuff it with data, and then publish it.
     */
    sensor_msgs::Imu imu;

    mag.read();
    acc.read();
    gyr.read();

    imu.header.stamp = ros::Time::now();
    imu.header.frame_id = "base_imu_link";
    imu.orientation_covariance = {0.0025, 0, 0, 0, 0.0025, 0, 0, 0, 0.0025};
    imu.angular_velocity_covariance = {0.0025, 0, 0, 0, 0.0025, 0, 0, 0, 0.0025};
    imu.linear_acceleration_covariance = {0.0025, 0, 0, 0, 0.0025, 0, 0, 0, 0.0025};
    imu.orientation.x = mag.raw.x;
    imu.orientation.y = mag.raw.y;
    imu.orientation.z = mag.raw.z;
    imu.orientation.w = 1;
    imu.angular_velocity.x = gyr.raw.x;
    imu.angular_velocity.y = gyr.raw.y;
    imu.angular_velocity.z = gyr.raw.z;
    imu.linear_acceleration.x = 1.0;
    imu.linear_acceleration.y = 1.0;
    imu.linear_acceleration.z = 1.0;
    /**
     * The publish() function is how you send messages. The parameter
     * is the message object. The type of this object must agree with the type
     * given as a template parameter to the advertise<>() call, as was done
     * in the constructor above.
     */
    chatter_pub.publish(imu);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }


  return 0;
}
