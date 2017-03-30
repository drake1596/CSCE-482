#include <stdlib.h>
#include <stdio.h>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <string>
#include <iostream>
#include <dirent.h>
#include <vector>

using namespace cv;

/// Global variables

Mat src, src_gray;
Mat dst, detected_edges;

int edgeThresh = 1;
int lowThreshold;
int const max_lowThreshold = 100;
int ratio;// = 2;
int kernel_size = 3;
char* window_name = "Edge Map";

/**
* @function CannyThreshold
* @brief Trackbar callback - Canny thresholds input with a ratio 1:3
*/
void CannyThreshold(int, void*, Mat s , Mat d)
{
	/// Reduce noise with a kernel 3x3
	blur(s, detected_edges, Size(3, 3));
	
	/// Canny detector
	Canny(detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size);

	/// Using Canny's output as a mask, we display our result
	d = Scalar::all(0);

	//dst becomes the final image. Saves it here
	src.copyTo(d, detected_edges);
	imshow(window_name, d);
	std::cout << "Finished sketching image \n";
}


/** @function main */
int main(int argc, char** argv)
{
	

	//std::cout << argv[1];
	//DIR *dir = opendir("..\\data");
	//if (dir == NULL) {
		//std::wcout << argv[1] + '\n';
		//std::wcout << "Error \n";
	//}
	//else {
	//std::cout << "No Error \n";
	//}

		
		//std::wcout << "Yes" << "\n";

		/// Create a matrix of the same type and size as src (for dst)
		
		

	//while there exists an image in the directory

	/// Load an image (as a grayscale image)
	String folderpath = "C:\\Users\\izaya\\Source\\Repos\\CSCE-482\\CECE-482\\data\\*.jpg";
	std::vector<String> filenames;
	cv::glob(folderpath, filenames);

	for (size_t i = 0; i < filenames.size(); i++)
	{
		Mat src = imread(filenames[i], CV_LOAD_IMAGE_GRAYSCALE);
		//src = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);

		if (!src.data)
		{
			return -1;
		}

		/// Create a matrix of the same type and size as src (for dst)
		dst.create(src.size(), src.type());

		blur(src, detected_edges, Size(3, 3));

		/// Canny detector
		Canny(detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size);

		/// Using Canny's output as a mask, we display our result
		dst = Scalar::all(0);

		//dst becomes the final image. Saves it here
		src.copyTo(dst, detected_edges);
		imshow(window_name, dst);
		String fn = filenames[i].substr(50, filenames[i].size() - 4);
	std::cout << fn << "\n";
		imwrite("C:\\Users\\izaya\\Source\\Repos\\CSCE-482\\CECE-482\\sketches\\"+fn+"_sketch.jpg", dst);
		//std::cout << "C:\\Users\\izaya\\Source\\Repos\\CSCE-482\\CECE-482\\sketches\\" + filenames[i] + "_sketch.jpg" << "\n";
		
		std::cout << "Finished sketching image C:\\Users\\izaya\\Source\\Repos\\CSCE-482\\CECE-482\\sketches\\" << filenames[i] << "_sketch.jpg" << "\n";



		/// Convert the image to grayscale

		//cvtColor(src, src_gray, CV_BGR2GRAY);

		/// Create a window
		//namedWindow(window_name, CV_WINDOW_KEEPRATIO);

		/// Create a Trackbar for user to enter threshold
		//createTrackbar("Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold);

		//createTrackbar("Ratio:", window_name, &ratio, 10, CannyThreshold);

		//createTrackbar("Kernel Size", window_name, &kernel_size, 20, CannyThreshold);

		/// Show the image
		//CannyThreshold(0, 0, src,dst);

		/// Wait until user exit program by pressing a key

	}
	
	
	waitKey(0);
	return 0;
}