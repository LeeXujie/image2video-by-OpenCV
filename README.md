### image2video-by-OpenCV
This project converts image sequence into video using OpenCV.

#### build
```bash
$ mkdir build
$ cd build/
$ cmake ..
$ make
```

#### usage
You can download a dataset named 4_video_office_large.zip from this website(https://sourceforge.net/projects/markermapper/files/test_data/) to test the program.
Example of usage：./img2video 4_video_office_large/image-%04d0.jpg video.avi 25.0
