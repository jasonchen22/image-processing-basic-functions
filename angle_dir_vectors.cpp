
#include <opencv2/opencv.hpp>

using namespace cv;

/** @brief returns angle between two vectors that has value at 0 ~ 180
@param vec1, vec2 two vectors representing by data type Point2f
*/
double angle_2vectors(Point2f vec1, Point2f vec2)
{
	double al1 = (atan2(vec1.y, vec1.x) * 180 / 3.141592);
	double al2 = (atan2(vec2.y, vec2.x) * 180 / 3.141592);

	double al = abs(al1 - al2);
	al = al < 180 ? al : 360 - al;

	return al;
}

/** @brief returns unsigned direction from vec1 to vec2 that has value at 0 ~ 180
	return value is the same for the 2nd vectors symmetric by origin when the first vector is x-axis
@param vec1 the first vector representing by data type Point2f
@param vec2 the second vector representing by data type Point2f
*/
double dir_vector12(Point2f vec1, Point2f vec2)
{
	double al1 = (atan2(-vec1.y, vec1.x) * 180 / 3.141592);
	double al2 = (atan2(-vec2.y, vec2.x) * 180 / 3.141592);

	double al = al2 - al1;
	if (al < 0) al += 360;
	if (al >= 360) al -= 360;
	if (al > 180) al -= 180;

	return al;
}

/** @brief returns signed direction from vec1 to vec2 that has value at -180 ~ 180
@param vec1 the first vector representing by data type Point2f
@param vec2 the second vector representing by data type Point2f
*/
double signdir_vector12(Point2f vec1, Point2f vec2)
{
	double al1 = (atan2(-vec1.y, vec1.x) * 180 / 3.141592);
	double al2 = (atan2(-vec2.y, vec2.x) * 180 / 3.141592);

	double al = al2 - al1;
	if (al < 0) al += 360;
	if (al >= 360) al -= 360;
	if (al > 180) al -= 360;

	return al;
}
