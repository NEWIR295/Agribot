#!/usr/bin/env python3

import rospy
from geometry_msgs.msg import Twist
import sys, select, termios, tty

msg = """
Control Your Robot!
---------------------------
Moving around:
        w
   a    s    d
        x

w/x : increase/decrease linear velocity
a/d : increase/decrease angular velocity

CTRL-C to quit
"""

moveBindings = {
        'w': (0.1, 0),
        'x': (-0.1, 0),
        'a': (0, -0.1),
        'd': (0, 0.1),
}

def getKey():
    tty.setraw(sys.stdin.fileno())
    select.select([sys.stdin], [], [], 0)
    key = sys.stdin.read(1)
    termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)
    return key

speed = 1
turn = 1

def vels(speed, turn):
    return "currently:\tspeed %s\tturn %s " % (speed, turn)

if __name__=="__main__":
    settings = termios.tcgetattr(sys.stdin)

    rospy.init_node('teleop_twist_keyboard')
    pub = rospy.Publisher('/Agribot_cmd_vel', Twist, queue_size=1)

    x = 0
    th = 0
    status = 0

    try:
        print(msg)
        print(vels(speed,turn))
        while True:
            key = getKey()
            if key in moveBindings.keys():
                x += moveBindings[key][0]
                th += moveBindings[key][1]
            elif key in ['w', 'x']:
                speed = max(0.1, speed + (0.1 if key == 'w' else -0.1))
                print(vels(speed, turn))
            elif key in ['a', 'd']:
                turn = max(0.1, turn + (0.1 if key == 'a' else -0.1))
                print(vels(speed, turn))
            else:
                x = 0
                th = 0
                if (key == '\x03'):
                    break

            twist = Twist()
            twist.linear.x = x * speed
            twist.angular.z = th * turn
            pub.publish(twist)

    except Exception as e:
        print(e)

    finally:
        twist = Twist()
        twist.linear.x = 0
        twist.angular.z = 0
        pub.publish(twist)

        termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)

