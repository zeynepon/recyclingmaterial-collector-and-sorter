
import os
import cv2
import numpy as np
from picamera.array import PiRGBArray
from picamera import PiCamera
import tensorflow as tf
import argparse
import sys
import serial
import time
import warnings

warnings.filterwarnings("ignore", category=RuntimeWarning)

IM_WIDTH = 1280
IM_HEIGHT = 720

 
camera_type = 'picamera'

sys.path.append('..')

from utils import label_map_util
from utils import visualization_utils as vis_util

# Name of the directory containing the object detection module we're using
MODEL_NAME = 'ssdlite_mobilenet_v2_coco_2018_05_09-8'

CWD_PATH = os.getcwd()

# Path to frozen detection graph .pb file, which contains the model that is used
# for object detection.
PATH_TO_CKPT = os.path.join(CWD_PATH,MODEL_NAME,'frozen_inference_graph.pb')

# Path to label map file
PATH_TO_LABELS = os.path.join(CWD_PATH,'data','mscoco_label_map.pbtxt')

# Number of classes the object detector can identify
NUM_CLASSES = 90

## Load the label map.

label_map = label_map_util.load_labelmap(PATH_TO_LABELS)
categories = label_map_util.convert_label_map_to_categories(label_map, max_num_classes=NUM_CLASSES, use_display_name=True)
category_index = label_map_util.create_category_index(categories)

# Load the Tensorflow model into memory.
detection_graph = tf.Graph()
with detection_graph.as_default():
    od_graph_def = tf.GraphDef()
    with tf.gfile.GFile(PATH_TO_CKPT, 'rb') as fid:
        serialized_graph = fid.read()
        od_graph_def.ParseFromString(serialized_graph)
        tf.import_graph_def(od_graph_def, name='')

    sess = tf.Session(graph=detection_graph)

# Input tensor is the image
image_tensor = detection_graph.get_tensor_by_name('image_tensor:0')

# Output tensors are the detection boxes, scores, and classes
detection_boxes = detection_graph.get_tensor_by_name('detection_boxes:0')

# Each score represents level of confidence for each of the objects.
detection_scores = detection_graph.get_tensor_by_name('detection_scores:0')
detection_classes = detection_graph.get_tensor_by_name('detection_classes:0')

# Number of objects detected
num_detections = detection_graph.get_tensor_by_name('num_detections:0')

# Initialize frame rate calculation
frame_rate_calc = 1
freq = cv2.getTickFrequency()
font = cv2.FONT_HERSHEY_SIMPLEX


pause = 0
pause_counter = 0

#### Trash detection function ####
def tell_ardunio(material):
    s1=serial.Serial('/dev/ttyUSB0',9600)
    s1.flushInput()
    print("i am connected")

    done=1
    cond_1=0
    cond_2=0
    cond_3=0
    cond_4=0
    print("su an 0 hepsi")
    if material ==1:
        cond_1=1
        print("materyal 1")
    if material==2:
        cond_2=1
        print("materyal 2")
    if material==3:
        cond_3=1
        print("materyal 3")
    if material==4:
        cond_4=1
        print("materyal 4")
    stop=0
    comp_list=["Done Moving"]
    print("loopa giriyom")
    iter_num = 0
    while True:
        iter_num += 1
        # print("s1 0dan buyuk degil")
        if stop == 1 in comp_list:
                print('break ettim')
                break
        if s1.inWaiting()>0:
            inputValue=s1.readline()
            print("seriala girdim", iter_num)
            print(inputValue.decode('utf-8'))
            """if stop == 1 in comp_list:
                print('break ettim')
                break"""
                # arduino tell done moving
                # if inputValue.decode('utf-8') in comp_list:
            if cond_1==1:
                s1.write(bytes('1','utf-8'))
                print(1, "iter:", iter_num)
                stop=1
                done=0
                break
            if cond_2==1:
                print(2)
                s1.write(bytes('2','utf-8'))
                stop=1
                done=0
                break
            if cond_3==1:
                print(3)
                s1.write(bytes('3','utf-8'))
                stop=1
                done=0
                break
            if cond_4==1:
                print(4)
                s1.write(bytes('4','utf-8'))
                stop=1
                done=0
                break
     

                        
cup_count=0
bottle_count=0
bowl_count=0 
cat_count=0

# This function contains the code to detect a trash 
def trash_detector(frame):

    global pause, pause_counter
    global cup_count
    global bottle_count
    global bowl_count
    global cat_count

    frame_expanded = np.expand_dims(frame, axis=0)

    # Perform the actual detection by running the model with the image as input
    (boxes, scores, classes, num) = sess.run(
        [detection_boxes, detection_scores, detection_classes, num_detections],
        feed_dict={image_tensor: frame_expanded})

    # visulaize the results
    vis_util.visualize_boxes_and_labels_on_image_array(
        frame,
        np.squeeze(boxes),
        np.squeeze(classes).astype(np.int32),
        np.squeeze(scores),
        category_index,
        use_normalized_coordinates=True,
        line_thickness=8,
        min_score_thresh=0.40)

    # 44= bottle in coco label map
    if ((int(classes[0][0]) == 44) or (int(classes[0][0]) == 46) or (int(classes[0][0]) == 41) or (int(classes[0][0]) == 33) or (int(classes[0][0]) == 77) and (pause == 0)):
        x = int(((boxes[0][0][1]+boxes[0][0][3])/2)*IM_WIDTH)
        y = int(((boxes[0][0][0]+boxes[0][0][2])/2)*IM_HEIGHT)
    
        # Draw a circle at center of object
        cv2.circle(frame,(x,y), 5, (75,13,180), -1)
        bottle_count=bottle_count+1
    if bottle_count>10:
        tell_ardunio(1)
        print("bottle to be collected")
        bottle_count=0

        
    if ((int(classes[0][0]) == 47) or (int(classes[0][0]) == 75) or (int(classes[0][0]) == 51) or (int(classes[0][0]) == 86) and (pause == 0)):
        x = int(((boxes[0][0][1]+boxes[0][0][3])/2)*IM_WIDTH)
        y = int(((boxes[0][0][0]+boxes[0][0][2])/2)*IM_HEIGHT)
    
        # Draw a circle at center of object
        cv2.circle(frame,(x,y), 5, (75,13,180), -1)
        cup_count=cup_count+1
        print("cup")
        print(cup_count)
    if cup_count>3:
        print("cup to be collected")
        tell_ardunio(2)
        cup_count=0

        
    if ((int(classes[0][0]) == 50) or (int(classes[0][0]) == 48) or (int(classes[0][0]) == 49) or (int(classes[0][0]) == 87) or (int(classes[0][0]) == 90) and (pause == 0)):
        x = int(((boxes[0][0][1]+boxes[0][0][3])/2)*IM_WIDTH)
        y = int(((boxes[0][0][0]+boxes[0][0][2])/2)*IM_HEIGHT)
    
        # Draw a circle at center of object
        cv2.circle(frame,(x,y), 5, (75,13,180), -1)
        bowl_count=bowl_count+1
    if bowl_count>3:
        tell_ardunio(3)
        print("bowl to be collected")
        bowl_count=0

    if ((int(classes[0][0]) == 17) or (int(classes[0][0]) == 23) or (int(classes[0][0]) == 18) or (int(classes[0][0]) == 88) and (pause == 0)):
        x = int(((boxes[0][0][1]+boxes[0][0][3])/2)*IM_WIDTH)
        y = int(((boxes[0][0][0]+boxes[0][0][2])/2)*IM_HEIGHT)
    
        # Draw a circle at center of object
        cv2.circle(frame,(x,y), 5, (75,13,180), -1)
        cat_count=cat_count+1
    if cat_count>3:
        tell_ardunio(4)
        print("cat to be collected")
        cat_count=0


    return frame

#### Initialize camera and perform object detection ####.
camera = PiCamera()
camera.resolution = (IM_WIDTH,IM_HEIGHT)
camera.framerate = 10
rawCapture = PiRGBArray(camera, size=(IM_WIDTH,IM_HEIGHT))
rawCapture.truncate(0)

# Continuously capture frames and perform object detection on them
for frame1 in camera.capture_continuous(rawCapture, format="bgr",use_video_port=True):

    t1 = cv2.getTickCount()
                    
    frame = np.copy(frame1.array)
    frame.setflags(write=1)

    # Pass frame into trash detection function
    frame = trash_detector(frame)

    cv2.putText(frame,"FPS: {0:.2f}".format(frame_rate_calc),(30,50),font,1,(255,255,0),2,cv2.LINE_AA)
            
    cv2.imshow('Object detector', frame)

    # FpS calculation
    t2 = cv2.getTickCount()
    time1 = (t2-t1)/freq
    frame_rate_calc = 1/time1

    #'q' to quit
    if cv2.waitKey(1) == ord('q'):
        break

    rawCapture.truncate(0)

camera.close()
            
cv2.destroyAllWindows()
  
