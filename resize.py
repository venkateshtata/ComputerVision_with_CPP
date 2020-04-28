import cv2
import sys

print(sys.argv[0])
print(sys.argv[1])

 
img = cv2.imread(str(sys.argv[1]), cv2.IMREAD_UNCHANGED)
 
print('Original Dimensions : ',img.shape)
 
scale_percent = 20 # percent of original size
width = int(img.shape[1] * scale_percent / 100)
height = int(img.shape[0] * scale_percent / 100)
dim = (width, height)
# resize image
resized = cv2.resize(img, dim, interpolation = cv2.INTER_AREA)


cv2.imwrite(str(sys.argv[2]),resized)
 
print('Resized Dimensions : ',resized.shape)
 
# cv2.imshow("Resized image", resized)
# cv2.waitKey(0)
# cv2.destroyAllWindows()
