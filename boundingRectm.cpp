
void boundingRectm(Mat src, Rect& boundingRect)
{
	int i, j, x, y;

	x = -1;
	for (i = 0; i < src.cols; i++) {
		for (j = 0; j < src.rows; j++) {
			if (src.at<uchar>(j, i) == 0) continue;
			x = i;
		}
		if (x > -1) break;
	}
	boundingRect.x = x;
	if (x == -1) boundingRect.x = 0;

	x = -1;
	for (i = src.cols - 1; i >= 0; i--) {
		for (j = 0; j < src.rows; j++) {
			if (src.at<uchar>(j, i) == 0) continue;
			x = i;
		}
		if (x > -1) break;
	}
	if (x == -1) boundingRect.width = 0;
	else boundingRect.width = x - boundingRect.x + 1;

	y = -1;
	for (j = 0; j < src.rows; j++) {
		for (i = 0; i < src.cols; i++) {
			if (src.at<uchar>(j, i) == 0) continue;
			y = j;
		}
		if (y > -1) break;
	}
	boundingRect.y = y;
	if (y == -1) boundingRect.y = 0;

	y = -1;
	for (j = src.rows - 1; j >= 0; j--) {
		for (i = 0; i < src.cols; i++) {
			if (src.at<uchar>(j, i) == 0) continue;
			y = j;
		}
		if (y > -1) break;
	}
	if (y == -1) boundingRect.height = 0;
	else boundingRect.height = y - boundingRect.y + 1;
}

