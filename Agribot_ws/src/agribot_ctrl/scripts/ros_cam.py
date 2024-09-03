#!/usr/bin/env python3

import rospy
import requests
import cv2
import numpy as np
import imutils
from cv_bridge import CvBridge
from sensor_msgs.msg import Image
import subprocess

def fetch_and_publish_image():
    rospy.init_node('android_cam_publisher', anonymous=True)
    image_pub = rospy.Publisher('/newir_cam', Image, queue_size=10)
    rate = rospy.Rate(10)  # 10 Hz
    bridge = CvBridge()
    subprocess.Popen(['rqt_image_view', '/newir_cam'])
    url = "http://192.168.170.137:8080/shot.jpg"

    while not rospy.is_shutdown():
        try:
            img_resp = requests.get(url)
            img_arr = np.array(bytearray(img_resp.content), dtype=np.uint8)
            img = cv2.imdecode(img_arr, -1)
            img = imutils.resize(img, width=1000, height=1800)
            
            # Convert OpenCV image to ROS Image message and publish
            image_msg = bridge.cv2_to_imgmsg(img, encoding="bgr8")
            image_pub.publish(image_msg)
            
            # Display image using OpenCV
            # cv2.imshow("Android_cam", img)
            # # Check for exit key (Esc)
            # if cv2.waitKey(1) == 27:
            #     break
        except Exception as e:
            rospy.logerr("Error fetching image: %s", e)

        rate.sleep()
    
    # cv2.destroyAllWindows()

if __name__ == '__main__':
    try:
        fetch_and_publish_image()
    except rospy.ROSInterruptException:
        pass
