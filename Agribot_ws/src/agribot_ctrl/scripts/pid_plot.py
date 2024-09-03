#!/usr/bin/env python3

import rospy
from std_msgs.msg import Float32
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

class PlotNode:
    def __init__(self):
        # Initialize ROS node
        rospy.init_node('pid_plot', anonymous=True)

        # Initialize Matplotlib plot
        self.fig, self.ax = plt.subplots()
        self.ax.set_xlabel('Time')
        self.ax.set_ylabel('velocity in rpm')
        self.ax.set_title('set point - output graph')

        # Initialize lists to store received values
        self.values1 = []
        self.values2 = []
        self.times = []

        # Subscribe to topic1
        rospy.Subscriber("/encoder", Float32, self.callback1)

        # Set up a Timer to periodically update the plot
        self.timer = rospy.Timer(rospy.Duration(0.1), self.timer_callback)

        # Start the animation
        self.ani = FuncAnimation(self.fig, self.update_plot, interval=100)

        plt.show()

    def callback1(self, data):
        # Append received value to the list
        self.values1.append(data.data)
        # Append current time to the times list
        self.times.append(rospy.Time.now().to_sec())
        # Retrieve the updated value of the parameter
        self.set_point = rospy.get_param('/motor_reconfigure/motor_speed', 10.0)
        # Append constant value to the values2 list
        self.values2.append(self.set_point)

    def timer_callback(self, event):
        self.fig.canvas.draw_idle()

    def update_plot(self, frame):
        # Clear previous plot
        self.ax.clear()
        # Plot values from topic1
        self.ax.plot(self.times, self.values1, label='Output')
        # Plot constant value for topic2
        self.ax.plot(self.times, self.values2, label='Set point')
        # Add legend
        self.ax.legend()

if __name__ == '__main__':
    try:
        plot_node = PlotNode()
    except rospy.ROSInterruptException:
        pass
