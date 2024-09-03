#!/usr/bin/env python3

import rospy
from sensor_msgs.msg import JointState
class VelocitySetter:
    def __init__(self):
        rospy.init_node('velocity_setter_node', anonymous=True)
        # Initialize publishers for each wheel velocity
        self.pub = rospy.Publisher('joint_states', JointState, queue_size=10)   
     
    def set_vel(self):
        joint_state = JointState()
        joint_state.header.stamp = rospy.Time.now()
        joint_state.name = ['agribot_left_front_joint', 'agribot_right_front_joint', 'agribot_left_rear_joint', 'agribot_right_rear_joint']
        joint_state.position = [3.14, 3.14, 3.14, 3.14]
        joint_state.velocity = [1, 1, 1, 1]
        joint_state.effort = [0.0, 0.0, 0.0, 0.0]
        self.pub.publish(joint_state)
    def run(self):
        rate = rospy.Rate(10)  # 10 Hz
        while not rospy.is_shutdown():
            try:
                # Example: Set both wheels to the same velocity (1500 rad/s)
                self.set_vel()
            except rospy.ROSException as e:
                rospy.logerr("Error setting wheel velocities: {}".format(e))
            rate.sleep()

if __name__ == '__main__':
    try:
        vs = VelocitySetter()
        vs.run()
    except rospy.ROSInterruptException as e:
        rospy.logerr(e)
