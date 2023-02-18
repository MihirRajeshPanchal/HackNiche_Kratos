import cv2
import numpy as np
import time
import glob
import os
global cnt
cnt=0

def load_yolo():

    net=cv2.dnn.readNetFromDarknet("./public/python/yolov3_testing.cfg","./public/python/yolov3.weights")

    with open("./public/python/coco.names", "r") as f:
      classes = [line.strip() for line in f.readlines()]

    output_layers = [layer_name for layer_name in net.getUnconnectedOutLayersNames()]
    colors = np.random.uniform(0, 255, size=(len(classes), 3))
    return net, classes, colors, output_layers


def start_video(video_path):
   model, classes, colors, output_layers = load_yolo()
   cap = cv2.VideoCapture(0)
   cnte=0
   ret=True
   # out = cv2.VideoWriter('videos/proc.mp4', cv2.VideoWriter_fourcc(*'mp4v'), 20.0, (416,416))
   while ret:
      ret, frame = cap.read()
      #print(ret,cnte)
      if not ret:
         break
      # cv2.imshow('Win',frame)
      # cv2.waitKey(1500)
      try:
         height, width, channels = frame.shape
         blob, outputs = detect_objects(frame, model, output_layers)
      except:
         pass

      boxes, confs, class_ids = get_box_dimensions(outputs, height, width)
      draw_labels(boxes, confs, colors, class_ids, classes, frame)
      cnte+=1
      # out.write(img) #--- out----FUNC
      key = cv2.waitKey(1)
      if key == 27:
         break
   cap.release()




def get_box_dimensions(outputs, height, width):
   boxes = []
   confs = []
   class_ids = []
   prev_frame_time=0
   new_prev_frame_time=0


   for output in outputs:
      for detect in output:
         scores = detect[5:]
         class_id = np.argmax(scores)
         conf = scores[class_id]
         if conf > 0.4:   #Try .6
            center_x = int(detect[0] * width)
            center_y = int(detect[1] * height)
            w = int(detect[2] * width)
            h = int(detect[3] * height)
            x = int(center_x - w/2)
            y = int(center_y - h / 2)
            boxes.append([x, y, w, h])
            confs.append(float(conf))
            class_ids.append(class_id)
   # codec = cv2.VideoWriter_fourcc(*"MJPG")
   # new_frame_time = time.time()
   # fps = 1 / (new_frame_time - prev_frame_time)
   # prev_frame_time = new_frame_time
   # fps_n = int(fps)

   return boxes, confs, class_ids

def detect_objects(img, net, outputLayers):
    blob = cv2.dnn.blobFromImage(img, scalefactor=0.00392, size=(320, 320), mean=(0, 0, 0), swapRB=True, crop=False)
    net.setInput(blob)
    outputs = net.forward(outputLayers)
    return blob, outputs

def save_vdo():
   img_array = []
   file_list=[]
   for file_n in glob.glob('./public/python/frames/*jpg'):
       file_n=file_n.replace('./public/python/frames/','')#TODO save the first and last part in variables
       file_n = file_n.replace('.jpg', '')
       file_list.append(file_n)
       # print(file_n)


   file_list.sort(key=int)
   #print(file_list)
   for filename in file_list:
       img = cv2.imread('./public/python/frames/'+filename+'.jpg')
       height, width, layers = img.shape
       size = (width, height)
       img_array.append(img)
       #print('appending',filename)

   out = cv2.VideoWriter('./public/python/videos/project.mp4', cv2.VideoWriter_fourcc(*'H264'), 15, size)

   for i in range(len(img_array)):
       out.write(img_array[i])
       #print('Frame:',i)
   out.release()

   #print('Appended and framed')


def draw_labels(boxes, confs, colors, class_ids, classes, img):
   global cnt
   indexes = cv2.dnn.NMSBoxes(boxes, confs, 0.5, 0.4) #(0.2,0.2) // (0.7,0.6)
   font = cv2.FONT_HERSHEY_DUPLEX
   # image_folder = 'data-set-race-01'
   video_file = './public/python/videos/proc.mp4'
   image_size = (416, 416)
   fps = 24
   # out = cv2.VideoWriter(video_file, cv2.VideoWriter_fourcc('M','P','E','G'), fps, image_size)

   for i in range(len(boxes)):
      if i in indexes:
         x, y, w, h = boxes[i]
         label = str(classes[class_ids[i]])
         # color = colors[i]

         if confs[i] > 0.85:
            color=(0,255,0)#GREEN
         elif confs[i] > 0.6:
            color = (255,0,0)#ORange
         elif confs[i] >0.4:
            color=(255,0,255)#RED


         cv2.rectangle(img, (x,y), (x+w, y+h), color, 2)
         cv2.putText(img, label + str(round(confs[i]*100,2)), (x, y - 5), font, 1, color, 1)
         # out.write(img)

   cv2.imshow("Image", img)
   cv2.imwrite('./public/python/frames/'+str(cnt)+'.jpg',img)
   #print('\t',cnt)
   cnt += 1


#----------------------------------MAIN -------------------
# if name == 'main':
if os.path.exists("./public/python/videos/project.mp4"):
  os.remove("./public/python/videos/project.mp4")

dir = './public/python/frames/'
for f in os.listdir(dir):
    os.remove(os.path.join(dir, f))

if os.path.exists("./public/python/videos/raw1.mp4"):
   video_path = './public/python/videos/raw1.mp4'
   #print('Opening ' + video_path + " .... ")
   start_video(video_path)
   # save_vdo()
   print('Video computed')
else: 
   print("Video doesn't exists")