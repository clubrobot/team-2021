import numpy as np
import cv2 as cv
import glob
def initiate():
    # termination criteria
    criteria = (cv.TERM_CRITERIA_EPS + cv.TERM_CRITERIA_MAX_ITER, 30, 0.001)
    # prepare object points, like (0,0,0), (1,0,0), (2,0,0) ....,(6,5,0)
    objp = np.zeros((6*6,3), np.float32)
    objp[:,:2] = np.mgrid[0:6,0:6].T.reshape(-1,2)
    # Arrays to store object points and image points from all the images.
    objpoints = [] # 3d point in real world space
    imgpoints = [] # 2d points in image plane.
    images = glob.glob('*.jpg')
    camera= cv.VideoCapture(0)
    for i in range(0,50):
        sucess,img = camera.read()
        gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)
        # Find the chess board corners
        ret, corners = cv.findChessboardCorners(gray, (6,6), None)
        # If found, add object points, image points (after refining them)
        if ret == True:
            objpoints.append(objp)
            corners2 = cv.cornerSubPix(gray,corners, (11,11), (-1,-1), criteria)
            imgpoints.append(corners)
            # Draw and display the corners
            #cv.drawChessboardCorners(img, (6,6), corners2, ret)
            print("pass")

        #cv.imshow('img', img)
        #cv.waitKey(500)
        print(i)
    ret, mtx, dist, rvecs, tvecs = cv.calibrateCamera(objpoints, imgpoints, gray.shape[::-1], None, None)
    f=open("cameraValues.txt","w")
    f.write(str(mtx[0,0]))
    f.write(" ")
    f.write(str(mtx[1, 1]))
    f.write(" ")
    f.write(str(mtx[0, 2]))
    f.write(" ")
    f.write(str(mtx[1, 2]))
    f.close()
    print(mtx)
    cv.destroyAllWindows()