/**
  @file videowriter_basic.cpp
  @brief A very basic sample for using VideoWriter and VideoCapture
  @author PkLab.net
  @date Aug 24, 2016
*/

#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h> 

using namespace cv;
using namespace std;

static void help(char** argv)
{
    cout << "This sample shows you how to read a sequence of images using the VideoCapture interface.\n"
         << "Usage: " << argv[0] << " <image_mask> (example mask: example_%02d.jpg) <video_name> (example: video.avi) <video_fps> (example: 25.0)\n"
         << "Image mask defines the name variation for the input images that have to be read as a sequence. \n"
         << "Using the mask example_%02d.jpg will read in images labeled as 'example_00.jpg', 'example_01.jpg', etc."
         << endl;
}

int main(int argc, char** argv)
{
    if(argc<4){ help(argv); return false; }

    cv::CommandLineParser parser(argc, argv, "{@image| ../data/image-%02d.jpg |}");
    string first_file = parser.get<string>("@image");

    VideoCapture sequence;

    if(first_file.size() < 3)
    {
        cout << "The input may not be a image sequence, try open a camera device!\n" << endl;
        sequence.open(atoi(argv[1]));
    }

    else sequence.open(first_file);

    if (!sequence.isOpened())
    {
        cerr << "Failed to open the image sequence or a camera device of " << argv[1] << endl;
        return false;
    }

    Mat src;

    // get one frame from camera to know frame size and type
    sequence >> src;
    // check if we succeeded
    if (src.empty()) {
        cerr << "ERROR! blank frame grabbed\n";
        return false;
    }
    bool isColor = (src.type() == CV_8UC3);

    //--- INITIALIZE VIDEOWRITER
    VideoWriter writer;
    int codec = CV_FOURCC('M', 'J', 'P', 'G');  // select desired codec (must be available at runtime)
    double fps = atof(argv[3]);                 // framerate of the created video stream
    string filename = "./";
    filename += argv[2];                        // name of the output video file
    writer.open(filename, codec, fps, src.size(), isColor);
    // check if we succeeded
    if (!writer.isOpened()) {
        cerr << "Could not open the output video file for write!" << endl;
        return false;
    }

    //--- GRAB AND WRITE LOOP
    char cvKey;
    cout << "Writing videofile: " << filename << endl;
    while (cvKey != 27)
    {
        // check if we succeeded
        if (!sequence.read(src)) {
            cerr << "End of Sequence!" << endl;
            break;
        }
        // encode the frame into the videofile stream
        writer.write(src);
        // show live and wait for a key with timeout long enough to show images
        imshow("Image sequence | press ESC to close", src);
        cvKey = waitKey(10);
    }
    cout << "The video has been saved as " << filename << endl;
    // the videofile will be closed and released automatically in VideoWriter destructor
    return 0;
}
