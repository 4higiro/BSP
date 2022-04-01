// Including
#include <glad/glad.h>
#include <iostream>
#include <fstream>

#include "poligons.h"
#include "buffer_objects.h"

// Using names
using namespace std;

// Add node in BSP-tree
void scene::addNode(poligon key)
{
	if (head == nullptr) 
	{
		head = &key;
	}
	else
	{
		poligon* current = head;

		while (true) 
		{
			if (current->chekSide(key) == LEFT ) 
			{
				current = current->left;
			}
			if (current->chekSide(key) == RIGHT ) 
			{
				current = current->right;	
			}
			if (current == nullptr) 
			{
				current = &key;
				break;
			}
		}
	}
}

// Account left-right poligons differents
int scene::account(int number)
{
	return 0;
}

// Scene construct
scene::scene()
{
	coords = nullptr;
	colors = nullptr;
	n = 0;
}

// Load all walls
void scene::load(const char* path)
{
	ifstream file;
	file.open(path);

	if (!file.is_open()) 
	{
		cout << "Cant open file" << endl;
		return;
	}
	
	file >> n;

	coords = new float[n * 12];
	colors = new float[n * 12];

	for (int i = 0; i < n * 12; i++) 
	{
		file >> coords[i];
	}

	for (int i = 0; i < n * 12; i++) 
	{
		file >> colors[i];
	}
	file.close();	
}

// All poligons init
void scene::init()
{
	poligons = new poligon[n];
	unsigned int indexes[6] = {
		0, 1, 2, 1, 2, 3
	};

	for (int i = 0; i < n; i++) 
	{
		poligons[i].coords = new vbo(coords + i * 12, 12, 3);
		poligons[i].colors = new vbo(colors + i * 12, 12, 3);
		poligons[i].data.addVBO(*poligons[i].coords);
		poligons[i].data.addVBO(*poligons[i].colors);
		poligons[i].primitive = new ebo(poligons[i].data, indexes, 6);
		poligons[i].a[0] = coords[0 + i * 12];
		poligons[i].a[1] = coords[1 + i * 12];
		poligons[i].a[2] = coords[2 + i * 12];
		poligons[i].b[0] = coords[3 + i * 12];
		poligons[i].b[1] = coords[4 + i * 12];
		poligons[i].b[2] = coords[5 + i * 12];
		poligons[i].c[0] = coords[6 + i * 12];
		poligons[i].c[1] = coords[7 + i * 12];
		poligons[i].c[2] = coords[8 + i * 12];
		poligons[i].d[0] = coords[9 + i * 12];
		poligons[i].d[1] = coords[10 + i * 12];
		poligons[i].d[2] = coords[11 + i * 12];
	}
}

// Drawing scene
void scene::drawing()
{
	for (int i = 0; i < n; i++) 
	{
		poligons[i].primitive->draw(GL_TRIANGLES);
	}
}

// Build BSP-tree
void scene::build()
{
	int* scores = new int[n];
	for (int i = 0; i < n; i++) 
	{
		for (int k = 0; k < n; k++) 
		{
			scores[k] = account(k);
			for (int j = 0; j < n;j++) 
			{
				if (j!=k && poligons[k].cross(poligons[j])) 
				{
					scores[k]--;
				}
				if(j!=k && !poligons[k].cross(poligons[j])) 
				{
					scores[k]++;
				}
			}
		}
		int max = 0;
		for (int k = 0; k < n; k++) 
		{
			if (scores[max] < scores[k]) 
			{
				max = k;
			}
		}
	}
}

// Account equantity's scalars
void scene::poligon::floor()
{
	A = (b[1] - a[1]) * (c[2] - a[2]) - (b[2] - a[2]) * (c[1] - a[1]);
	B = (b[0] - a[0]) * (b[1]- a[1]) - (b[1] - a[1]) * (b[0] - a[0]);
	C = (b[0] - a[0]) * (b[1] - a[1]) - (b[1] - a[1]) * (b[0] - a[0]);
	D = -a[0] * A - a[1] * B - a[2] * C;
}

// Check of floors crossing
bool scene::poligon::cross(poligon p)
{
	return false;
}

// Check of splitter's side
side scene::poligon::chekSide(poligon g)
{
	return side();
}

// Claer scene
void scene::clear()
{
	for (int i = 0; i < n; i++)
	{
		poligons[i].clear();
	}

	delete[] poligons;
	delete[] coords;
	delete[] colors;

	n = 0;
}

// Poligon clear
void scene::poligon::clear()
{
	delete coords;
	delete colors;
	delete primitive;
}
