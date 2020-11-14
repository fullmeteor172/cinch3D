#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include<iostream>
#include<vector>
#include<fstream>
#include<math.h>

#define objfile ".\\obj_files\\face.obj"

const int dispX = 800;	//Output window X Length px
const int dispY = 800;	//Output window Y Length px
const int pixelRatio = 1;	//1px of outPutWindow -> pixelRatio px's on screen
float rotAngle = 45.f;

olc::Pixel DULLGREY = olc::Pixel(28, 28, 28, 255);
olc::Pixel GREY = olc::Pixel(92, 92, 92, 255);
olc::Pixel ORANGE = olc::Pixel(255, 119, 0, 255);
olc::Pixel CYAN = olc::Pixel(0, 230, 207, 255);
olc::Pixel DULLCYAN = olc::Pixel(3, 97, 87, 255);


#include"cinchmath.h"
std::vector<vec3> vertData;		//Contains all the vertices
std::vector<vec3> fVertData;	//Contains the vertices that make up each face
#include"misc.h"

class Cinch : public olc::PixelGameEngine
{
public:
	Cinch()
	{
		sAppName = "Cinch3D";
	}

	void Line(int x0, int y0, int x1, int y1, olc::Pixel color);	//Draws Lines
	void Dot(int x0, int y0, olc::Pixel color);	//Draws Dots
	void DrawAxis(olc::Pixel color);	//Draws Axes
	void DrawGrid(int scale, olc::Pixel color);
	vec2 VertPos(int no, int scale);
	void DotVerts(int scale, olc::Pixel color);	//Puts a dot at each vert from vertData
	void DrawEdges(int scale, olc::Pixel color);	//Draws Edges
	void DrawUI();	//Draws all the ui Elements (Grid + Filename)

	
	bool OnUserCreate() override
	{
		//Once at startup
		loadObjModel(objfile);
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		FillRect(0, 0, dispX, dispY, olc::BLACK);
		DrawUI();
		DrawEdges(150, CYAN);
		DotVerts(150, ORANGE);
		rotAngle += 1.f * fElapsedTime/2;
		return true;										
	}														
};

void Cinch::Line(int x0, int y0, int x1, int y1, olc::Pixel color)
{
	//Correcting Origin to center
	x0 = xOriginAdjust(x0);
	y0 = yOriginAdjust(y0);
	x1 = xOriginAdjust(x1);
	y1 = yOriginAdjust(y1);
	DrawLine(x0, y0, x1, y1, color);
}
void Cinch::Dot(int x0, int y0, olc::Pixel color)
{
	//Correcting origin to center
	x0 = xOriginAdjust(x0);
	y0 = yOriginAdjust(y0);
	int dotRad = dispY/300;	//Will change depending on window size
	FillCircle(x0, y0, dotRad, color);
}
void Cinch::DrawAxis(olc::Pixel color)
{
	//Not using origin correction here
	DrawLine(dispX / 2, 0, dispX / 2, dispY, color);	//Y axis
	DrawLine(0, dispY / 2, dispX, dispY / 2, color);	//X axis
	Dot(0, 0, color);
}
void Cinch::DrawGrid(int scale, olc::Pixel color)
{
	//DOES NOT USE ORIGIN CORRECTION
	//Vert lines
	for (int i = 1; i <= (dispX / scale); i++)
	{
		DrawLine(i * scale, 0, i * scale, dispY, color);
	}
	
	//Hor lines
	for (int i = 1; i <= (dispY / scale); i++)
	{
		DrawLine(0, i * scale, dispX, i * scale, color);
	}
}
vec2 Cinch::VertPos(int i, int scale)
{
	vec2 pos;
	float xPos = vertData[i].x * scale;
	if (vertData[i].x == 0 && vertData[i].y == 0)
	{
		pos.x = 0; pos.y = 0;
		return pos;
	}
	float oDist = DistBetw(0, 0, vertData[i].x * scale, vertData[i].y * scale);
	float theta;
	if (vertData[i].y >= 0)
		theta = acos(xPos / oDist) * 1;
	else
		theta = acos(xPos / oDist) * -1;
	xPos = oDist * cos(theta + rotAngle);
	float zPos = vertData[i].z * scale;
	pos.x = xPos;
	pos.y = zPos;
	return pos;
}
void Cinch::DotVerts(int scale, olc::Pixel color)
{
	for (int i = 0; i < vertData.size(); i++)
	{
		vec2 pos = VertPos(i, scale);
		if(pos.x!=0&&pos.y!=0)
			Dot(pos.x, pos.y, color);	
	}
}
void Cinch::DrawEdges(int scale, olc::Pixel color)
{
	for (int i = 0; i < fVertData.size(); i++)
	{
		vec2 pos1 = VertPos(fVertData[i].x-1, scale);
		vec2 pos2 = VertPos(fVertData[i].y-1, scale);
		vec2 pos3 = VertPos(fVertData[i].z-1, scale);
		Line(pos1.x, pos1.y, pos2.x, pos2.y, color);
		Line(pos2.x, pos2.y, pos3.x, pos3.y, color);
		Line(pos3.x, pos3.y, pos1.x, pos1.y, color);
	}
}
void Cinch::DrawUI()
{
	DrawGrid(10, DULLGREY);
	DrawAxis(DULLCYAN);
	DrawString(dispX / 100, dispX / 100, objfile, GREY, 1);
	DrawString(dispX / 100, 3 * dispX / 100,"Orthographic View", GREY, 1.2);
	DrawString(dispX / 100, 5 * dispX / 100, "Author: Dhruv Jha", GREY, 1.2);
}

int main()
{
	Cinch renderer;
	if (renderer.Construct(dispX, dispY, pixelRatio, pixelRatio))
		renderer.Start();
	return 0;
}
