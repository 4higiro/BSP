// Protection from repeat including
#pragma once

// Including
#include "buffer_objects.h"

// Side enum type
enum side {
	LEFT, RIGHT,NS
};

// Scene class
class scene {
private:	
	// Wall class
	class poligon {
	public:
		vbo* coords, *colors;
		vao data;
		ebo* primitive;

		float A, B, C, D;
		float a[3], b[3], c[3], d[3];

		poligon* left;
		poligon* right;

		void floor();
		bool cross(poligon p);
		side chekSide(poligon g);
		void clear();
	};

	void addNode(poligon g);
	int account(int number);

	float* coords, * colors;
	int n;

	poligon* head;
	poligon* poligons;
public:
	scene();
	void load(const char* path);
	void init();
	void drawing();
	void build();
	void clear();
};

