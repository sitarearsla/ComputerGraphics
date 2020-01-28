#pragma once
#include "Angel.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

using namespace std;

namespace models {
	enum { CUBE = 0, SPHERE = 1, BUNNY = 2, NUM_MODELS = 3 };

	////// CUBE //////
	const int cubeNumVertices = 36; //(6 faces)(2 triangles/face)(3 vertices/triangle)

	point4 cubePoints[cubeNumVertices];

	// Vertices of a cube of side length 2 centered at origin, sides aligned with axes
	point4 vertices[8] = {
		point4(-1.0, -1.0,  1.0, 1.0),
		point4(-1.0,  1.0,  1.0, 1.0),
		point4(1.0,  1.0,  1.0, 1.0),
		point4(1.0, -1.0,  1.0, 1.0),
		point4(-1.0, -1.0, -1.0, 1.0),
		point4(-1.0,  1.0, -1.0, 1.0),
		point4(1.0,  1.0, -1.0, 1.0),
		point4(1.0, -1.0, -1.0, 1.0)
	};

	// quad generates two triangles for each face 
	int Index = 0;
	void
		quad(int a, int b, int c, int d)
	{
		cubePoints[Index] = vertices[a]; Index++;
		cubePoints[Index] = vertices[b]; Index++;
		cubePoints[Index] = vertices[c]; Index++;
		cubePoints[Index] = vertices[a]; Index++;
		cubePoints[Index] = vertices[c]; Index++;
		cubePoints[Index] = vertices[d]; Index++;
	}

	//----------------------------------------------------------------------------

	// generate 12 triangles: 36 vertices and 36 colors
	void
		cube()
	{
		quad(1, 0, 3, 2);
		quad(2, 3, 7, 6);
		quad(3, 0, 4, 7);
		quad(6, 5, 1, 2);
		quad(4, 5, 6, 7);
		quad(5, 4, 0, 1);
	}
	
	// ----------------------------------------------------------------------------

	////// SPHERE //////

	const int NumTimesToSubdivide = 3;
	const int NumTriangles = 4096; // (4 faces)^(NumTimesToSubdivide + 1)
	const int sphereNumVertices = 3 * NumTriangles;
	point4 spherePoints[sphereNumVertices];

	int sphereIndex = 0;
	void
	triangle(const point4& a, const point4& b, const point4& c)
	{
		spherePoints[sphereIndex] = a; sphereIndex++;
		spherePoints[sphereIndex] = b; sphereIndex++;
		spherePoints[sphereIndex] = c; sphereIndex++;
	}

	point4
	unit(const point4& p)
	{
		float len = p.x*p.x + p.y*p.y + p.z*p.z;
		point4 t;
		if (len > DivideByZeroTolerance) {
			t = p / sqrt(len);
			t.w = 1.0;
		}
		return t;
	}
	void
	divide_triangle(const point4& a, const point4& b,
			const point4& c, int count)
	{
		if (count > 0) {
			point4 v1 = unit(a + b);
			point4 v2 = unit(a + c);
			point4 v3 = unit(b + c);
			divide_triangle(a, v1, v2, count - 1);
			divide_triangle(c, v2, v3, count - 1);
			divide_triangle(b, v3, v1, count - 1);
			divide_triangle(v1, v3, v2, count - 1);
		}
		else {
			triangle(a, b, c);
		}
	}

	void
	tetrahedron(int count)
	{
		point4 v[4] = {
			vec4(0.0, 0.0, 1.0, 1.0),
			vec4(0.0, 0.942809, -0.333333, 1.0),
			vec4(-0.816497, -0.471405, -0.333333, 1.0),
			vec4(0.816497, -0.471405, -0.333333, 1.0)
		};
		divide_triangle(v[0], v[1], v[2], count);
		divide_triangle(v[3], v[2], v[1], count);
		divide_triangle(v[0], v[3], v[1], count);
		divide_triangle(v[0], v[2], v[3], count);
	}

	void
	sphere() {
		tetrahedron(NumTimesToSubdivide);
	}

	// ----------------------------------------------------------------------------

	//// BUNNY ////
	const int bunnyNumVertices = 9840 * 3; // (number of triangles in bunny.off) * 3 
	point4 bunnyPoints[bunnyNumVertices]; 
	GLfloat bunnyScale;

	void bunny() {
		ifstream bunnyFile("bunny.off");
		GLuint numTris = 0, numVerts = 0;
		point4 vertices[4922];

		string dump = "";		// dummy string to dump unneeded data

		bunnyFile >> dump;		// OFF
		bunnyFile 
			>> numVerts			// 4922
			>> numTris			// 9840
			>> dump;			// don't need number of edges 

		GLfloat maxDim = -10000;
		GLfloat x = 0, y = 0, z = 0;
		for (int i = 0; i < numVerts; i++) {
			bunnyFile >> x >> y >> z;
			vertices[i] = point4(x, y, z, 1.0);

			// finding the maximum dimension for scaling
			maxDim = max(abs(x), maxDim);
			maxDim = max(abs(y), maxDim);
			maxDim = max(abs(z), maxDim);
		}
		bunnyScale = 1.0 / maxDim;	// to "normalize" bunny while viewing
		bunnyScale *= 4;

		int v1 = 0, v2 = 0, v3 = 0;
		for (int i = 0; i < numTris; i++) {
			// we know there are only triangles in the model
			bunnyFile >> dump >> v1 >> v2 >> v3;
			bunnyPoints[3*i] = vertices[v1];
			bunnyPoints[3*i + 1] = vertices[v2];
			bunnyPoints[3*i + 2] = vertices[v3];
		}
	}

	// array of pointers to models points
	point4 *model_pts[NUM_MODELS]
		= { cubePoints , spherePoints, bunnyPoints };

	// sizes of point arrays (needed due to non-uniform array size in the above array)
	size_t model_pts_sizes[NUM_MODELS] 
		= { sizeof(cubePoints), sizeof(spherePoints), sizeof(bunnyPoints) };
	
	// number of vertices for each model
	int NumVertices[NUM_MODELS] 
		= { cubeNumVertices, sphereNumVertices, bunnyNumVertices };
}