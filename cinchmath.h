int xOriginAdjust(int x)	//WRT Origin at center
{
	return ((dispX / 2) + x);
}

int yOriginAdjust(int y)	//WRT Origin at center
{
	return ((dispY / 2) - y);
}

struct vec2
{
	float x;
	float y;
};
struct vec3
{
	float x;
	float y;
	float z;
};