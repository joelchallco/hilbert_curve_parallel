#include <bits/stdc++.h>
#include <vector>
#include <omp.h>

using namespace std;

#define STEP_SZ 10
#define H_WINDOWS 800
#define W_WINDOWS 800
#define SPEED 3  // check https://docs.python.org/3/library/turtle.html#turtle.speed

int angles[4] = { 90,-90,-90,90 };


FILE *out;

void print_python_head(){
    fprintf(out,"import turtle\n");
    fprintf(out,"turtle.setup(%d, %d)\n", H_WINDOWS, W_WINDOWS);
    fprintf(out, "turtle.speed(%d)\n", SPEED);
	fprintf(out, "turtle.tracer(0)\n");
	
}

void print_python_end(){
	fprintf(out, "turtle.update()\n"); 
    fprintf(out, "screen = turtle.Screen()\n"); // EXIT ON CLICK
    fprintf(out, "screen.exitonclick()\n"); // EXIT ON CLICK
}

void hilbert_curve_Parallel(int order, int angle);

void hilbert_curve(int n, int angle) {
    if( n==0 ) return;
    
    
    fprintf(out,"turtle.right(%d)\n", angle);
    
    hilbert_curve(n-1, -angle);
    //hilbert_curve_Parallel(n - 1, -angle);
    
    fprintf(out,"turtle.forward(%d)\n", STEP_SZ);
    fprintf(out,"turtle.left(%d)\n", angle);
    
    hilbert_curve(n-1, angle);
    //hilbert_curve_Parallel(n - 1, angle);

    fprintf(out,"turtle.forward(%d)\n", STEP_SZ);
    
    hilbert_curve(n-1, angle);
    //hilbert_curve_Parallel(n - 1, angle);

    fprintf(out,"turtle.left(%d)\n", angle);
    fprintf(out,"turtle.forward(%d)\n", STEP_SZ);

    hilbert_curve(n-1, -angle);
    //hilbert_curve_Parallel(n - 1, -angle);

    fprintf(out,"turtle.right(%d)\n", angle);
}



void hilbert_curve_Parallel(int order, int angle) {
    // Dividir el trabajo en secciones más pequeñas
    vector<int> angles;

    // Crear las secciones para cada hilo
    angles.push_back(angle);
    angles.push_back(-angle);
    angles.push_back(-angle);
    angles.push_back(angle);

    // Iniciar hilos paralelos angulo de inicio de cada seccion.
    #pragma omp parallel for
    fprintf(out, "turtle.left(%d)\n", angle);

    fprintf(out, "turtle.pencolor('#04B431')\n");
    hilbert_curve(order, angle);
    fprintf(out, "turtle.forward(%d)\n", STEP_SZ);
    fprintf(out, "turtle.left(%d)\n", -angle);
    
    fprintf(out, "turtle.pencolor('#210B61')\n");
    hilbert_curve(order, -angle);

    fprintf(out, "turtle.forward(%d)\n", STEP_SZ);

    //mitad
    fprintf(out, "turtle.pencolor('#FA58D0')\n");
    hilbert_curve(order, -angle);
    
    fprintf(out, "turtle.left(%d)\n", -angle);
    fprintf(out, "turtle.forward(%d)\n", STEP_SZ);
    fprintf(out, "turtle.pencolor('#DF0101')\n");
    hilbert_curve(order, angle);

    fprintf(out, "turtle.left(%d)\n", angle);

    //for (int i = 0; i < 4; ++i) {
    //    //constructHilbertCurveParallel(level - 1, order, sectionStarts[i], sectionEnds[i]);
    //    //construct_hilbertcurve_Parallel(order - 1, -angle);
    //    hilbert_curve(order-1, angles[i]);

    //}
}

int main(int argc, char const *argv[]) {
    out = fopen("hilbert_turtle.py", "w+");
    print_python_head();

    int order = 3;
    int angle = -90;

    //hilbert_curve(order, angle);
    hilbert_curve_Parallel(order, angle);
    print_python_end();
    fclose(out);
    return 0;
}
