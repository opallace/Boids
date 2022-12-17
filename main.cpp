#include <GL/glut.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>

using namespace std;




#include "Param.hpp"
#include "Vector.hpp"
#include "Boid.hpp"
#include "QuadTree.hpp"

Boid boid[n_boids];


void MyInit(){
	srand(time(NULL));
	
	for(int i = 0; i < n_boids; i++){
		boid[i] = Boid();	
	}

	glViewport(0, 0, window_width, window_height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, window_width, window_height, 0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(1, 1, 1, 1);
}

void RenderScene(){
	glClear(GL_COLOR_BUFFER_BIT);
	
	QuadTree *qt = new QuadTree(Rectangle(window_width / 2, window_height / 2, window_width, window_height), 5);
	
	for(int i = 0; i < n_boids; i++){
		qt->insert(&boid[i]);	
	}

	qt->show();
	
	for(int i = 0; i < n_boids; i++){

	 	if(boid[i].position.x < 0){
	 		boid[i].position.x = window_width;	
	 	}

	 	if(boid[i].position.x > window_width){
	 		boid[i].position.x = 0;	
	 	}

	 	if(boid[i].position.y < 0){
	 		boid[i].position.y = window_height;	
	 	}

	 	if(boid[i].position.y > window_height){
	 		boid[i].position.y = 0;	
	 	}
	
		Rectangle rc(boid[i].position.x, boid[i].position.y, p_perception / 2, p_perception / 2);
		vector<Boid*> neightboids = qt->query(&rc);
	 	boid[i].flock(neightboids);
	 	boid[i].update();
	 	boid[i].show();
	 }



	free(qt);

	glFlush();
}

int main(int argc, char **argv){
	

	glutInit(&argc, argv);  
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  
    glutInitWindowSize(window_width, window_height);  
    glutCreateWindow("Boids");
    glutFullScreen();	

	glutIdleFunc(RenderScene);
   	glutDisplayFunc(RenderScene);  

    MyInit();  
    glutMainLoop(); 

	return 0;
}
