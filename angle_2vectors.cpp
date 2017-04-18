
int angle_2vectors(Point2f vec1, Point2f vec2)
{
	int al1 = (int)(atan2(vec1.y, vec1.x) * 180 / 3.141592);
	int al2 = (int)(atan2(vec2.y, vec2.x) * 180 / 3.141592);

	int al = abs(al1 - al2);
	al = al < 180 ? al : 360 - al;

	return al;
}
