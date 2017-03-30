#include <stdlib.h>
#include <stdio.h>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <string>
#include <iostream>
#include <dirent.h>
#include <vector>

using namespace cv;

/// Global variables + Canny variables

Mat src, src_gray;
Mat dst, detected_edges;

int edgeThresh = 1;
int lowThreshold = 100;
int const max_lowThreshold = 100;
int ratio;// = 2;
int kernel_size = 3;
char* window_name = "Edge Map";

//Contouring Variables
int thresh = 100;
int max_thresh = 255;
RNG rng(12345);

/// Function header
void thresh_callback(int, void*);

/**
* @function CannyThreshold
* @brief Trackbar callback - Canny thresholds input with a ratio 1:3
*/



/** @function main */
int main(int argc, char** argv)
{
	/* Single Sketch implementation
	//Image passed as a command line argument
	//arguments can be changed for the debug version (probably the version you;re using by doing the following:
	//Right Click CECE-482 (NOT SOlution CECE-482) in the solution explorer -> properties -> Debugging ->command arguments
	//the argument should be an image file. currently stored in the data file 1 directory up from where the arguments are accepted
	//so, argument looks like ..\\data\Fig04.jpg or similar

	//sets image to the file that was a command line argument
	src = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);

	//return failure if image cannot be loaded
	if (!src.data)
	{
		std::cout << "Image" << argv[1] << " not found! \n";
	return -1;
	}

	/// Convert the image to grayscale -> no longer necessary as image should be loaded as a grayscale image
	//cvtColor(src, src_gray, CV_BGR2GRAY);

	/// Create a window
	window_name = argv[1];
	namedWindow(window_name, CV_WINDOW_KEEPRATIO);

	/// Create a Trackbar for user to enter threshold
	createTrackbar("Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold);

	createTrackbar("Ratio:", window_name, &ratio, 10, CannyThreshold);

	//createTrackbar("Kernel Size", window_name, &kernel_size, 20, CannyThreshold);

	/// Show the image
	CannyThreshold(0, 0);

	/// Wait until user exit program by pressing a key*/

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/*Single Contour Implementation
	//WARNING: Works very slowly. 

	/// Load source image and convert it to gray
	src = imread(argv[1], 1);
	if (!src.data)
	{
		std::cout << "Image" << argv[1] << " not found! \n";
		return -1;
	}

	/// Convert image to gray and blur it
	cvtColor(src, src_gray, CV_BGR2GRAY);
	blur(src_gray, src_gray, Size(3, 3));

	/// Create Window
	char* source_window = "Source";
	namedWindow(source_window, CV_WINDOW_AUTOSIZE);
	imshow(source_window, src);

	createTrackbar(" Canny thresh:", "Source", &thresh, max_thresh, thresh_callback);
	thresh_callback(0, 0);

	waitKey(0);
	return(0);*/
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	//Multi(directory) sketch implementation
	//Directory pointed at by folderpath. Currently hardcoded. should be changed 
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////

	/// Load an image (as a grayscale image)
	String folderpath = "C:\\Users\\izaya\\Source\\Repos\\CSCE-482\\CECE-482\\data\\*.jpg";
	std::vector<String> filenames;
	cv::glob(folderpath, filenames);

	for (size_t i = 0; i < filenames.size(); i++)
	{
		//Mat src = imread(filenames[i], CV_LOAD_IMAGE_GRAYSCALE);
		

		if (!src.data)
		{
			return -1;
		}

		/// Create a matrix of the same type and size as src (for dst)
		dst.create(src.size(), src.type());

		//blur(src, detected_edges, Size(3, 3));

		/// Canny detector
		//Canny(detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size);

		/// Using Canny's output as a mask, we display our result
		//dst = Scalar::all(0);

		//dst becomes the final image. Saves it here
		src.copyTo(dst, detected_edges);
		
		imshow(window_name, dst);
		//provides part of the name of the original image so that the output iamge can be identified
		String fn = filenames[i].substr(50, filenames[i].size() - 4);
		//window_name = (char*)i;
		//std::cout << fn << "\n";
		//saves image to specified path. should be made relative, not absolute
		imwrite("C:\\Users\\izaya\\Source\\Repos\\CSCE-482\\CECE-482\\sketches\\"+fn+"_sketch.jpg", dst);
		//std::cout << "C:\\Users\\izaya\\Source\\Repos\\CSCE-482\\CECE-482\\sketches\\" + filenames[i] + "_sketch.jpg" << "\n";
		
		std::cout << "Finished sketching image C:\\Users\\izaya\\Source\\Repos\\CSCE-482\\CECE-482\\sketches\\" << filenames[i] << "_sketch.jpg" << "\n";

	}/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	
	waitKey(0);
	return 0;
}

/*Canny edge detection for a single image file. 
*/
void CannyThreshold(int, void*)
{
	/// Reduce noise with a kernel 3x3
	blur(src, detected_edges, Size(3, 3));

	/// Canny detector
	Canny(detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size);

	/// Using Canny's output as a mask, we display our result
	dst = Scalar::all(0);

	//dst becomes the final image. Saves it here
	src.copyTo(dst, detected_edges);
	imshow(window_name, dst);
	std::cout << "Finished sketching image \n";
}

/** @function thresh_callback
Used for the contouring scrollbar*/
void thresh_callback(int, void*)
{
	Mat canny_output;
	std::vector<std::vector<Point> > contours;
	std::vector<Vec4i> hierarchy;

	/// Detect edges using canny
	Canny(src_gray, canny_output, thresh, thresh * 2, 3);
	/// Find contours
	findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	/// Draw contours
	Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
	for (int i = 0; i< contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
	}

	/// Show in a window
	namedWindow("Contours", CV_WINDOW_AUTOSIZE);
	imshow("Contours", drawing);
}