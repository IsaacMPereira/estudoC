#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Assingments for all the functions
void plotting(double a, double b);
void generating(double a, double b);

int main(){
	double a, b;

	printf("The equation is: {a*cos(t), a*sin(t)}\nSet a: ");
	scanf("%lf", &a);
	printf("\nThe equation is: {b*cos(t), b*sin(t)}\nSet b: ");
	scanf("%lf", &b);

	generating(a, b);
	plotting(a, b);

	printf("\n");
	return 0;
}

void generating(double a, double b){
	FILE *file1 = fopen("dados_cryptos.dat", "w");
	if(!file1){
		printf("Error in file1 in generating() in 'w' mode\n");
		exit(1);
	}
	
	for(double x=0; x<a+b; x++){
		for(double y=0; y<a+b; y++){
			if((a*cos(x) + b*cos(y)) % (a+b) == (a*sin(x) + b*sin(y) % (a+b))){
				fprintf(file1, "%lf\t%lf\n", x, y);
			}
		}
	}
	
	system("open dados_cryptos.dat");
	
	fclose(file1);
}

void plotting(double a, double b){
	FILE *gnuplot = popen("gnuplot -persist", "w");
	if(!gnuplot){
		printf("Error on gnuplot pipe in 'w' mode\n");
		exit(1);
	}

	double aux1;
	if(a > b){
		aux1 = a + 2;
	}else{
		aux1 = b + 2;
	}

	fprintf(gnuplot, "set xlabel 'x' offset 20.5, 9.2\n");
	fprintf(gnuplot, "set ylabel 'y' offset 22.3, 8.7 rotate by 360\n");
	fprintf(gnuplot, "set xrange [-%lf:%lf]\n", aux1, aux1);
	fprintf(gnuplot, "set yrange [-%lf:%lf]\n", aux1, aux1);

	fprintf(gnuplot, "unset xtics\n");
	fprintf(gnuplot, "unset ytics\n");
	fprintf(gnuplot, "set title 'r_{1} = %lf, r_{2} = %lf' offset 0, 0.5\n", a, b);
	//fprintf(gnuplot, "set object 1 rectangle from 30, -42 to 50, -48 fillstyle solid border lc 'black'\n");

	fprintf(gnuplot, "set zeroaxis\n");
	fprintf(gnuplot, "set parametric\n");
	fprintf(gnuplot, "set trange [0:2*pi]\n"); //The angle delta is called 't'
	fprintf(gnuplot, "set size square\n");

	fprintf(gnuplot, "plot %lf*cos(t), %lf*sin(t) lw 2 notitle, %lf*cos(t), %lf*sin(t) lw 2 notitle\n", a, a, b, b);

	pclose(gnuplot);
}
