

#include <opencv2/opencv.hpp>

using namespace cv;

/** @brief adaptive thresholding using the integral image				

@param src input image: 8-bit unsignd CV_8UC1
@param des output binary image: 8-bit unsignd CV_8UC1 
@param T threshold value at 0 ~ 1 for binarizing
@param blkSize block size for blockwise thresholding
*/
void adaptThreshByIntegral(Mat src, Mat& des, double T, int blkSize)
{
	unsigned long* integralImg = 0;
	int i, j;
	long sum = 0;
	int count = 0;
	int index;
	int x1, y1, x2, y2;
	int s2 = src.cols / blkSize / 2;

	des = Mat::zeros(src.size(), CV_8UC1);

	// create the integral image
	integralImg = (unsigned long*)malloc(src.cols*src.rows * sizeof(unsigned long*));

	for (i = 0; i<src.cols; i++) {
		// reset this column sum
		sum = 0;

		for (j = 0; j<src.rows; j++) {
			index = j*src.cols + i;

			sum += src.at<uchar>(j, i);
			//sum += input[index];
			if (i == 0)
				integralImg[index] = sum;
			else
				integralImg[index] = integralImg[index - 1] + sum;
		}
	}

	// perform thresholding
	for (i = 0; i<src.cols; i++) {
		for (j = 0; j<src.rows; j++) {
			index = j*src.cols + i;

			// set the SxS region
			x1 = i - s2; x2 = i + s2;
			y1 = j - s2; y2 = j + s2;

			// check the border
			if (x1 < 0) x1 = 0;
			if (x2 >= src.cols) x2 = src.cols - 1;
			if (y1 < 0) y1 = 0;
			if (y2 >= src.rows) y2 = src.rows - 1;

			count = (x2 - x1)*(y2 - y1);

			// I(x,y)=s(x2,y2)-s(x1,y2)-s(x2,y1)+s(x1,x1)
			sum = integralImg[y2*src.cols + x2] -
				integralImg[y1*src.cols + x2] -
				integralImg[y2*src.cols + x1] +
				integralImg[y1*src.cols + x1];

			if ((long)(src.at<uchar>(j, i) * count) < (long)(sum*(1.0 - T)))
				des.at<uchar>(j, i) = 0;
			else
				des.at<uchar>(j, i) = 255;
		}
	}

	free(integralImg);
}

// example
Mat image, binImg;
adaptThreshByIntegral(image, binImg, 0.1, 8);

