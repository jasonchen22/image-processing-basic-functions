

#include <opencv2/opencv.hpp>

using namespace cv;


/** @brief contrast enhancement of image
@param src input image: 8-bit unsigned CV_8UC1
@param dst output image: 8-bit unsigned CV_8UC1
@param a enhancement rate: double value > 0
@param b criterion value between 0 and 255
@param c desired mean value between 0 and 255
*/
void contrast_image(Mat src, Mat& dst, double a, int b, int c)
{
	// a > 0
	// b = 0 ~ 255. if b < 0, b = mean(src)
	// c = 0 ~ 255

	Mat dst_ = Mat::zeros(src.size(), src.type());

	if (b < 0) b = mean(src, src > 20)[0];

	for (int y = 0; y < src.rows; y++) {
		for (int x = 0; x < src.cols; x++) {
			dst_.at<uchar>(y, x) =
				saturate_cast<uchar>(a*(src.at<uchar>(y, x) - b) + c);
		}
	}

	dst = dst_;
}

/** @brief blockwise contrast enhancement of image
@param src input image: 8-bit unsigned CV_8UC1
@param dst output image: 8-bit unsigned CV_8UC1
@param blksz block size
@param a enhancement rate: double value > 0
@param c desired mean value between 0 and 255
*/
void contrast_blockwise(Mat src, Mat& dst, int blksz, double a, int c)
{
	int i, j;
	int w = src.cols;
	int h = src.rows;
	int blk2 = blksz / 2;
	Mat ima;

	Mat dst_ = Mat(src.size(), src.type());

	for (j = 0; j < h; j++) {
		for (i = 0; i < w; i++) {
			Rect rt(i - blk2, j - blk2, blksz, blksz);
			if (rt.x < 0) rt.x = 0; if (rt.x + rt.width > w) rt.width = w - rt.x;
			if (rt.y < 0) rt.y = 0; if (rt.y + rt.height > w) rt.height = h - rt.y;

			ima = src(rt);
			double b = mean(ima)[0];
			dst_.at<uchar>(j, i) =
				saturate_cast<uchar>(a*(src.at<uchar>(j, i) - b) + c);
		}
	}

	dst = dst_;
}

