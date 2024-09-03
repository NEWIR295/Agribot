#!/usr/bin/env python3

import rospy
from geometry_msgs.msg import Twist

class MoveSquare:
    def __init__(self):
        # Initialize the ROS node
        rospy.init_node('move_square', anonymous=True)
        
        # Create a publisher to publish on the /turtle1/cmd_vel topic
        self.pub = rospy.Publisher('/cmd_vel', Twist, queue_size=10)
        
        # Define the Twist messages
        self.move_cmd_straight = Twist()
        self.move_cmd_straight.linear.x = 1.5
        self.move_cmd_straight.angular.z = 0.0
        
        self.move_cmd_turn = Twist()
        self.move_cmd_turn.linear.x = 0.0
        self.move_cmd_turn.angular.z = 1.57  # 90 degrees turn
        
        self.move_cmd_turn2 = Twist()
        self.move_cmd_turn2.linear.x = 0.0
        self.move_cmd_turn2.angular.z = -1.57  # -90 degrees turn
        
        self.stop_cmd = Twist()
        self.stop_cmd.linear.x = 0.0
        self.stop_cmd.angular.z = 0.0
        
        # Define the time intervals
        self.duration_straight1 = 12# seconds
        self.duration_straight2 = 2 # seconds

        self.duration_turn = 4  # seconds
        self.duration_stop = 2  # seconds
        
        # Set the rate for the loop
        self.rate = rospy.Rate(1)

    def move_square(self):
        while not rospy.is_shutdown():
            self.perform_motion_sequence()

    def perform_motion_sequence(self):
        # Stop
        self.pub.publish(self.stop_cmd)
        rospy.loginfo("Stopping")
        rospy.sleep(self.duration_stop)

        # Move straight1
        self.pub.publish(self.move_cmd_straight)
        rospy.loginfo("Moving straight")
        rospy.sleep(self.duration_straight1)
        
        # Stop
        self.pub.publish(self.stop_cmd)
        rospy.loginfo("Stopping")
        rospy.sleep(self.duration_stop)
        
        # Turn
        self.pub.publish(self.move_cmd_turn)
        rospy.loginfo("Turning")
        rospy.sleep(self.duration_turn)
        
        # Stop
        self.pub.publish(self.stop_cmd)
        rospy.loginfo("Stopping")
        rospy.sleep(self.duration_stop)
        
        # Move straight2
        self.pub.publish(self.move_cmd_straight)
        rospy.loginfo("Moving straight")
        rospy.sleep(self.duration_straight2)
        
        # Turn
        self.pub.publish(self.move_cmd_turn)
        rospy.loginfo("Turning")
        rospy.sleep(self.duration_turn)
        
        # Stop
        self.pub.publish(self.stop_cmd)
        rospy.loginfo("Stopping")
        rospy.sleep(self.duration_stop)
        
        # Move straight1
        self.pub.publish(self.move_cmd_straight)
        rospy.loginfo("Moving straight")
        rospy.sleep(self.duration_straight1)
        
        # Turn
        self.pub.publish(self.move_cmd_turn2)
        rospy.loginfo("Turning")
        rospy.sleep(self.duration_turn)
        
        # Stop
        self.pub.publish(self.stop_cmd)
        rospy.loginfo("Stopping")
        rospy.sleep(self.duration_stop)
        
        # Move straight
        self.pub.publish(self.move_cmd_straight)
        rospy.loginfo("Moving straight")
        rospy.sleep(self.duration_straight2)
        
        # Stop
        self.pub.publish(self.stop_cmd)
        rospy.loginfo("Stopping")
        rospy.sleep(self.duration_stop)
        
        # Turn
        self.pub.publish(self.move_cmd_turn2)
        rospy.loginfo("Turning")
        rospy.sleep(self.duration_turn)
        
        # Stop
        self.pub.publish(self.stop_cmd)
        rospy.loginfo("Stopping")
        rospy.sleep(self.duration_stop)
        
        self.rate.sleep()

if __name__ == '__main__':
    try:
        mover = MoveSquare()
        mover.move_square()
    except rospy.ROSInterruptException:
        pass
