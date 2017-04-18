
#include <opencv2/opencv.hpp>

// img1, img2 : type CV_8UC1
double cross_correlation(Mat img1, Mat img2)
{
	double corr;

	Mat img_1(img1);
	Mat img_2(img2);

	// in the case with gray image
	//Scalar img1_avg = mean(img1);
	//Scalar img2_avg = mean(img2);

	// in the case with binary image
	Scalar img1_avg = Scalar(128, 0, 0);
	Scalar img2_avg = Scalar(128, 0, 0);

	double sum_img1_img2 = 0;
	double sum_img1_2 = 0;
	double sum_img2_2 = 0;

	for (int m = 0; m<img1.rows; ++m)
	{
		for (int n = 0; n<img1.cols; ++n)
		{
			sum_img1_img2 += (img1.at<uchar>(m, n) - img1_avg.val[0])*(img_2.at<uchar>(m, n) - img2_avg.val[0]);
			sum_img1_2 += (img1.at<uchar>(m, n) - img1_avg.val[0])*(img1.at<uchar>(m, n) - img1_avg.val[0]);
			sum_img2_2 += (img2.at<uchar>(m, n) - img2_avg.val[0])*(img2.at<uchar>(m, n) - img2_avg.val[0]);
		}
	}

	if (sum_img1_2 == 0 || sum_img2_2 == 0) return -1;

	corr = sum_img1_img2 / sqrt(sum_img1_2*sum_img2_2);

	return corr;
}
