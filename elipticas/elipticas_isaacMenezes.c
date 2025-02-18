/*
 * C program to implement the elliptic curve cryptography
 * Isaac Menezes Pereira, 190088885 - feb, 2025
 *
 * Compile: $ gcc -Wall elipticas_isaacMenezes.c -lgmp -o elipticas_isaacMenezes.x 
 * Run: $ ./elipticas_isaacMenezes.x a b p
 * Downloading the GNU Multi Precision Library (GMP): 
 *  $ sudo apt update
 *  $ sudo apt install libgmp-dev
 *
 * Interesting observation:
 * Using the curve y^2 = 4x^3 + 4 (mod 103) and the point (94, 28), generated by this curve, it's order is
 * 268.435.455
 * */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <gmp.h>

typedef struct{
  char xr[100], yr[100], s[100]; 

} PointDoubling;

//Assignments for all the functions
void generatingPoints(char* a, char* b, char* p);
void choosingPoints();
void findOrder(char *a, char *p);
PointDoubling pointDoubling(char *xp, char *yp, char *a, char *p);
void modInverse(char *a, char *p, char *dest);
char gcdExtended(char *a, char *b, char *x, char *y);
//int gcd(char *a, char *b); //Não precisa??

int main(int argc, char *argv[4]){
  if(argc != 4){
    printf("Error! Run: $ ./elipticas_isaacMenezes.x a b p\n");
    printf("These arguments satisfy: y^2 = x^3 + ax + b (mod p)\n");
    exit(1);
  }

  char *a = argv[1], 
       *b = argv[2],
       *p = argv[3];

  generatingPoints(a, b, p);

  system("open pointsElliptics.dat");
  system("open choosedPoints_ellipticCurve.dat"); //Vai se tornar: system("rm choosedPoints_ellipticCurve.dat");
  //system("open 2choosedPoints_ellipticCurve.dat"); //Descomentar no final 

  return 0;
}

//Generating the points
void generatingPoints(char* a, char* b, char* p){
  FILE *file1 = fopen("pointsElliptics.dat", "w");
  if(!file1){
    printf("Error on openning pointsElliptics.dat in 'w' mode in generatingPoints()\n");
    exit(1);
  }
  
  /*
   * -> Generating a specif quantitie of points witch is controlled with the 'n' variable
   * 
   * The prefixe 'r_*' means 'result_*'. The result of an operation.
   * */
  mpz_t x, 					y,  					n,							limit, 						a_gmp,
		b_gmp,				p_gmp,					one,						r_y_pow_2, 					r_y2_mod_pGMP,  
		r_x_pow_3,			r_aGMP_mul_x,			r_aGMPx_sum_bGMP, 			r_aGMPxbGMP_mod_pGMP,
		r_x3_sum_aGMPx,		r_x3aGMPx_sum_bGMP, 	r_x3aGMPxbGMP_mod_pGMP; 
  //Initializing:
  mpz_init_set_ui(x, 0); 
  mpz_init_set_ui(y, 0);
  mpz_init_set_ui(n, 0);
  mpz_init_set_ui(limit, 1000); //Limit for n_gmp
  mpz_set_str(a_gmp, a, 10);
  mpz_set_str(b_gmp, b, 10);
  mpz_set_str(p_gmp, p, 10);
  mpz_init_set_ui(one, 1); //Incrementing (const) variable
  mpz_init(r_y_pow_2);
  mpz_init(r_y2_mod_pGMP);
  mpz_init(r_x_pow_3);
  mpz_init(r_aGMP_mul_x); 
  mpz_init(r_aGMPx_sum_bGMP);
  mpz_init(r_aGMPxbGMP_mod_pGMP);
  mpz_init(r_x3_sum_aGMPx);
  mpz_init(r_x3aGMPx_sum_bGMP);
  mpz_init(r_x3aGMPxbGMP_mod_pGMP);
  /*
   * -> Operations:
   * 
   * Those satisfies the follwing:
   * (y*y) % p == (x*x*x + a*x + b) % p 
   * Witch is the condition for a point on the elliptic curve:
   * y^2 = x^3 + ax + b (mod p)
   * All operations required are executed in order of the above equation.
   * */
  mpz_pow_ui(r_y_pow_2, y, 2);									//y^2
  mpz_mod(r_y2_mod_pGMP, r_y_pow_2, p_gmp); 					//(y^2) % p
  mpz_pow_ui(r_x_pow_3, x, 3); 									//x^3
  mpz_mul(r_aGMP_mul_x, a_gmp, x); 								//a*x
  mpz_add(r_x3_sum_aGMPx, r_x_pow_3, r_aGMP_mul_x); 			//x^3 + a*x
  mpz_add(r_x3aGMPx_sum_bGMP, r_x3_sum_aGMPx, b_gmp); 			//(x^3 + a*x) + b
  mpz_mod(r_x3aGMPxbGMP_mod_pGMP, r_x3aGMPx_sum_bGMP, p_gmp); 	//(x^3 + a*x + b) % p
  //Finding all points:
  for(; mpz_cmp(x, p_gmp) < 0; mpz_add(x, x, one)){
    for(; mpz_cmp(y, p_gmp) < 0; mpz_add(y, y, one)){
      if(mpz_cmp(r_y2_mod_pGMP, r_x3aGMPxbGMP_mod_pGMP) == 0){ // (y*y) % p == (x*x*x + a*x + b) % p
        mpz_add(n, n, one); //n++
        
        char buffer_x[100], buffer_y[100]; //Creating buffers for printing the correct converted gmp variables in file1
        mpz_get_str(buffer_x, 10, r_x3aGMPxbGMP_mod_pGMP);
        mpz_get_str(buffer_y, 10, r_y2_mod_pGMP);
        fprintf(file1, "%s\t%s\n", buffer_x, buffer_y); 
        
        if(mpz_cmp(n, limit) > 0){ //n > 1000
          break;
        }
      }
    }
  }

  fclose(file1);
  printf("All points created!\n");
  
  choosingPoints(); 
  
  //Using the Finding Order Algorithm to find the order of all points choosed:
  char buffer_aGMP[100], buffer_pGMP[100];
  mpz_get_str(buffer_aGMP, 10, a_gmp);
  mpz_get_str(buffer_pGMP, 10, p_gmp);
  findOrder(buffer_aGMP, buffer_pGMP);
  
  //Cleaning all the GMP variables created:
  mpz_clear(x);
  mpz_clear(y);
  mpz_clear(n);
  mpz_clear(limit);
  mpz_clear(one);
  mpz_clear(r_y_pow_2);
  mpz_clear(r_y2_mod_pGMP);
  mpz_clear(r_x_pow_3);
  mpz_clear(r_aGMP_mul_x);
  mpz_clear(r_aGMPx_sum_bGMP);
  mpz_clear(r_aGMPxbGMP_mod_pGMP);
  mpz_clear(r_x3_sum_aGMPx);
  mpz_clear(r_x3aGMPx_sum_bGMP);
  mpz_clear(r_x3aGMPxbGMP_mod_pGMP);
} 

//Choosing the points for the Finding Order Algorithm
void choosingPoints(){
  srand(time(NULL));  
  int totalLines = 0;
  char buffer[100];

  FILE *file2 = fopen("pointsElliptics.dat", "r");
  if(!file2){
    printf("Error on openning pointsElliptics.dat in 'r' mode in choosingPoints()\n");
    exit(1);
  }
  FILE *file3 = fopen("choosedPoints_ellipticCurve.dat", "w");
  if(!file3){
    printf("Error on openning choosedPoints_ellipticCurve.dat in 'w' mode in choosingPoints()\n");
    exit(1);
  }

  //Checking the number of lines in file2:
  while(fgets(buffer, sizeof(buffer), file2)){
    totalLines++;
  }
  printf("Total of points: %d\n", totalLines);
  rewind(file2);

  //Creating the vector with a specific size depending on the number of lines in file2:
  int tamVetor;
  if(totalLines > 100){
    tamVetor = 100;
  }else{
    tamVetor = totalLines;
  }
  int v_random[tamVetor];

  //Assigning random values to the vector depending on it's size and the number of lines in file2:
  for(int i=0; i<tamVetor; i++){
    int aux = rand() % totalLines;
    v_random[i] = aux;
  }  

  //Printing the specific line in file2 depending on the index of the vector:
  for(int i=0; i<tamVetor; i++){
    int desiredLine = v_random[i];
    rewind(file2); //Comes back to tho first line of the file
    int currentLine = 1;
    while(fgets(buffer, sizeof(buffer), file2)){
      if(currentLine == desiredLine){
        fprintf(file3, "%s", buffer);
        break;
      }
      currentLine++;
    }
  } 

  fclose(file2);
  fclose(file3);
  
  FILE *file4 = fopen("choosedPoints_ellipticCurve.dat", "r");
  if(!file4){
    printf("Error on openning choosedPoints_ellipticCurve.dat in 'r' mode in choosingPoints()\n");
    exit(1);  
  }

  //Checking the number of lines in file4:
  totalLines = 0;
  while(fgets(buffer, sizeof(buffer), file4)){
    totalLines++;
  }
  printf("Total of points choosed: %d\n", totalLines);

  fclose(file4);
}

//Finding the order of all points choosed
void findOrder(char *a, char *p){
  mpz_t order, two, pdxr_gmp, pdyr_gmp, r_order_mul_2, one;
  
  mpz_init_set_ui(order, 2);
  mpz_init_set_ui(two, 2); //Const
  mpz_init(pdxr_gmp);
  mpz_init(pdyr_gmp);
  mpz_init(r_order_mul_2);
  mpz_init_set_ui(one, 1);

  FILE *file5 = fopen("choosedPoints_ellipticCurve.dat", "r") ;
  if(!file5){
    printf("Error on openning choosedPoints_ellipticCurve.dat in 'r' mode in findOrder()\n");
    exit(1);
  }

  FILE *file6 = fopen("2choosedPoints_ellipticCurve.dat", "w");
  if(!file6){
    printf("Error on openning 2choosedPoints_ellipticCurve.dat in 'w' mode in findOrder()\n");
    exit(1);
  }

  //Applying PointDoubling in every single point until find it's order
  PointDoubling pd;
  char line[100], str1[100], str2[100];
  
  while(fgets(line, sizeof(line), file5)){
	if(sscanf(line, "%s %s", str1, str2) == 2){
		int flag = 0; //This is for controlling the recurrence
		printf("\n\nP = (%s, %s)\n", str1, str2);
		while(1){
		  if(flag == 0){
			pd = pointDoubling(str1, str2, a , p);
			char buffer_order[500]; //Talvez essas linhas só sirvam para printar no console (3)
			mpz_get_str(buffer_order, 10, order);
			printf("%sP = (%s, %s)\n", buffer_order, pd.xr, pd.yr);
		  }else{
			char *aux1 = pd.xr;
			char *aux2 = pd.yr;

			pd = pointDoubling(aux1, aux2, a, p);
			char buffer2_order[500]; //Talveze essas linhas só sirvam para printar no console (3)
			mpz_get_str(buffer2_order, 10, order);
			printf("%sP = (%s, %s)\n", buffer2_order, pd.xr, pd.yr);
			
			mpz_t str1_gmp, str2_gmp;
			mpz_set_str(str1_gmp, str1, 10);
			mpz_set_str(str2_gmp, str2, 10);
			
			mpz_set_str(pdxr_gmp, pd.xr, 10);
			mpz_set_str(pdyr_gmp, pd.yr, 10);
			if((mpz_cmp(pdxr_gmp, str1_gmp) == 0) && (mpz_cmp(pdyr_gmp, str2_gmp) == 0)) //Point in the infinit found!
			  break;

			mpz_clear(str1_gmp);
			mpz_clear(str2_gmp);
		  }
		  //order *= 2; //gmp aqui
		  mpz_mul(r_order_mul_2, order, two);
		  flag++;
		};
		//printf("Order: %d\n", order-1);
		mpz_sub(order, order, one); //order -= 1
		gmp_printf("Order: %Zd\n", order);//
		char aux[500];
		mpz_get_str(aux, 10, order); 
		fprintf(file6, "%s\t%s\t%s\n", str1, str2, aux); 
		//order = 2;
		mpz_set_ui(order, 2);
		flag = 0;
	}
  }

  //Cleaning all the variables:
  mpz_clear(order);
  mpz_clear(two);
  mpz_clear(pdxr_gmp);
  mpz_clear(pdyr_gmp);
  mpz_clear(r_order_mul_2);
  mpz_clear(one);

  fclose(file5);
  fclose(file6);

  system("open 2choosedPoints_ellipticCurve.dat"); //Apagar depois
  //system("rm choosedPoints_ellipticCurve.dat"); //Descomentar depois
}

//Point doubling 
PointDoubling pointDoubling(char *px, char *py, char *a, char *p){
  PointDoubling result;

  //char s[100], xr[100], yr[100];
  
  /*
   * Creating GMP variables for finding slope (s)
   * */
  mpz_t s,  					yr, 					xr,					a_gmp, 					p_gmp, 				px_gmp, 	
		py_gmp,					r_px_pow_2,				r_3_times_px2,		r_3px2_sum_aGMP, 		r_2_times_pyGMP, 
		r_modInverseF_mod_pGMP,	r_3px2aGMP_mod_pGMP,	rt_modInverse,		zero,					two,				three;
  //Initializing:
  mpz_init(s);
  mpz_init(yr);
  mpz_set_str(a_gmp, a, 10);
  mpz_set_str(p_gmp, p, 10);
  mpz_set_str(px_gmp, px, 10);
  mpz_set_str(py_gmp, py, 10);
  mpz_init(r_px_pow_2);
  mpz_init(r_3_times_px2);
  mpz_init(r_3px2_sum_aGMP);
  mpz_init(r_2_times_pyGMP);
  mpz_init(r_3px2aGMP_mod_pGMP);
  //mpz_init(rt_modInverse);
  mpz_init_set_ui(zero, 0); //Const
  mpz_init_set_ui(three, 3); //Const
  mpz_init_set_ui(two, 2); //Const
  //Operations:
  mpz_pow_ui(r_px_pow_2, px_gmp, 2);
  mpz_mul(r_3_times_px2, r_px_pow_2, three);
  mpz_add(r_3px2_sum_aGMP, r_3_times_px2, a_gmp);
  mpz_mod(r_3px2aGMP_mod_pGMP, r_3px2_sum_aGMP, p_gmp);
  mpz_mul(r_2_times_pyGMP, py_gmp, two);
  
  char buffer_r_2_times_pyGMP[100], buffer_p_gmp[100];
  mpz_get_str(buffer_r_2_times_pyGMP, 10, r_2_times_pyGMP); 
  mpz_get_str(buffer_p_gmp, 10, p_gmp);
  
  char aux_rt[100]; 
  modInverse(buffer_r_2_times_pyGMP, buffer_p_gmp, aux_rt);
  mpz_set_str(rt_modInverse, aux_rt, 10); //return (rt) of modInverse(2*py, p)
  mpz_mod(r_modInverseF_mod_pGMP, rt_modInverse, p_gmp); //modInverse(2*py, p) % p
  //Finding slope (s):
  mpz_mul(s, r_3px2aGMP_mod_pGMP, r_modInverseF_mod_pGMP); //s = ((3 * px*px + a) % p) * (modInverse(2*py, p)) % p;
  if(mpz_cmp(s, zero) < 0){ //Just for ensurrement: s < 0
    do{
      mpz_add(s, s, p_gmp);
    }while(mpz_cmp(s, zero) < 0);
  }

  /*
   * Creating GMP variables for finding xr
   * */
  mpz_t xr_gmp, r_s_mul_s, r_2_times_pxGMP, r_ss_dif_2pxGMP, r_ss2pxGMP_mod_pGMP;
  //Initializing:
  mpz_init(xr_gmp);
  mpz_init(r_s_mul_s);
  mpz_init(r_2_times_pxGMP);
  mpz_init(r_ss_dif_2pxGMP);
  mpz_init(r_ss2pxGMP_mod_pGMP);
  //Operations:
  mpz_mul(r_s_mul_s, s, s);
  mpz_mul(r_2_times_pxGMP, px_gmp, two);
  mpz_sub(r_ss_dif_2pxGMP, r_s_mul_s, r_2_times_pxGMP);
  //Finding xr:
  mpz_mod(xr_gmp, r_ss_dif_2pxGMP, p_gmp); //xr = (s*s - 2*px) % p;
  if(mpz_cmp(xr_gmp, zero) < 0){ //xr < 0
    do{
      //xr += p;
      mpz_add(xr_gmp, xr_gmp, p_gmp);
    }while(mpz_cmp(xr_gmp, zero) < 0);
  }
  
  /*
   * Creating GMP variables for finding yr
   * */
  mpz_t yr_gmp, r_pxGMP_dif_xr, r_s_times_pxGMPxr, r_spxGMPxr_dif_pyGMP, r_spxGMPpyGMP_mod_pGMP; 
  //Initializing:
  mpz_init(r_pxGMP_dif_xr);
  mpz_init(r_s_times_pxGMPxr);
  mpz_init(r_spxGMPxr_dif_pyGMP);
  mpz_init(r_spxGMPpyGMP_mod_pGMP);
  //Operations:
  mpz_sub(r_pxGMP_dif_xr, px_gmp, xr);
  mpz_mul(r_s_times_pxGMPxr, s, r_pxGMP_dif_xr);
  mpz_sub(r_spxGMPxr_dif_pyGMP, r_s_times_pxGMPxr, py_gmp);
  //Finding yr:
  mpz_mod(r_spxGMPpyGMP_mod_pGMP, r_spxGMPxr_dif_pyGMP, p_gmp); //yr = (s*(px - xr) - py) % p;
  if(mpz_cmp(yr_gmp, zero) < 0){ //yr < 0
    do{
      //yr += p;
      mpz_add(yr_gmp, yr_gmp, p_gmp);
    }while(mpz_cmp(yr_gmp, zero) < 0);
  }

  //Converting for the struct:
  char buffer_xr[100], buffer_yr[100], buffer_s[100];
  mpz_get_str(buffer_xr, 10, xr_gmp);
  mpz_get_str(buffer_yr, 10, yr_gmp);
  mpz_get_str(buffer_s, 10, s);
  //Comming back to the struct:
  strcpy(result.xr, buffer_xr);
  strcpy(result.yr, buffer_yr);
  strcpy(result.s, buffer_s);

  /*
   * Cleaning all GMP variables created
   * */
  //Variables used for finding slope (s):
  mpz_clear(s);
  mpz_clear(a_gmp);
  mpz_clear(p_gmp);
  mpz_clear(px_gmp);
  mpz_clear(py_gmp);
  mpz_clear(r_px_pow_2);
  mpz_clear(r_3_times_px2);
  mpz_clear(r_3px2_sum_aGMP);
  mpz_clear(r_2_times_pyGMP);
  mpz_clear(r_modInverseF_mod_pGMP);
  mpz_clear(r_3px2aGMP_mod_pGMP);
  mpz_clear(rt_modInverse);
  mpz_clear(zero);
  mpz_clear(three);
  mpz_clear(two);
  //Variables used for finding xr:
  mpz_clear(xr_gmp);
  mpz_clear(r_s_mul_s);
  mpz_clear(r_2_times_pxGMP);
  mpz_clear(r_ss_dif_2pxGMP);
  mpz_clear(r_ss2pxGMP_mod_pGMP);
  //Variables used for finding yr:
  mpz_clear(yr_gmp);
  mpz_clear(r_pxGMP_dif_xr);
  mpz_clear(r_s_times_pxGMPxr);
  mpz_clear(r_spxGMPxr_dif_pyGMP);
  mpz_clear(r_spxGMPpyGMP_mod_pGMP);

  return result;
}

//Modular inverse of a number mod p
void modInverse(char *a, char *p, char *dest){
  //int gcd = gcdExtended(a, p, &x, &y);
  
  //aqui (ultimo log guardado)
  
  if(gcd != 1){
    printf("Modular inverse does not exists!\n"); //In this case, it always exist if p is prime
    exit(1);
  }
  
  //Creating all GMP variables:
  mpz_t x, y, a_gmp, p_gmp, r_x_mod_p, r_xmodp_sum_p, inverse;
  //Initializing:
  mpz_init(x);
  mpz_init(y);
  mpz_set_str(a_gmp, a, 10);
  mpz_set_str(p_gmp, p, 10);
  mpz_init(r_x_mod_p);
  mpz_init(r_xmodp_sum_p);
  mpz_init(inverse);
  //Operations:
  mpz_mod(r_x_mod_p, x, p_gmp);
  mpz_add(r_xmodp_sum_p, r_x_mod_p, p_gmp); 
  //Finding the inverse:
  mpz_mod(inverse, r_xmodp_sum_p, p_gmp); //inverse = (x % p + p) % p;
  
  char buffer_inverse[100];
  mpz_get_str(buffer_inverse, 10, inverse);
  
  //Cleaning all the variables used:
  mpz_clear(x);
  mpz_clear(y);
  mpz_clear(a_gmp);
  mpz_clear(p_gmp);
  mpz_clear(r_x_mod_p);
  mpz_clear(r_xmodp_sum_p);
  mpz_clear(inverse);
  
  strcat(dest, buffer_inverse);
}

//Extended Euclidian Algorithm
char gcdExtended(char *a, char *b, char *x, char *y){
  //Creating GMP variables:
  mpz_t a_gmp, b_gmp, x_gmp, y_gmp, zero;
  //Initializing:
  mpz_set_str(a_gmp, a, 10);
  mpz_set_str(b_gmp, b, 10);
  mpz_set_str(x_gmp, x, 10);
  mpz_set_str(y_gmp, y, 10);
  mpz_init_set_ui(zero, 0); //Const
  //Operations:
  if(mpz_cmp(a_gmp, zero) == 0){
	mpz_set_ui(x_gmp, 0);
	mpz_set_ui(y_gmp, 1);
	
	char buffer_bGMP[100];
	mpz_get_str(buffer_bGMP, b_gmp, 10);
	return buffer_bGMP;
  }
	
  mpz_t x1, y1, tco_gcdExtended, r_bGMP_mod_aGMP;
  mpz_init(x1);
  mpz_init(y1);
  mpz_init(r_bGMP_mod_aGMP);
  
  //mpz_mod(r_bGMP_mod_aGMP, b_gmp, a_gmp);
  
  char buffer_r_bGMP_mod_aGMP[100];
  mpz_get_str(buffer_r_bGMP_mod_aGMP, mpz_mod(r_bGMP_mod_aGMP, b_gmp, a_gmp), 10); //Funciona ou tenho que converter r_bGMP_mod_aGMP para char?
  char buffer_aGMP[100];
  mpz_get_str(buffer_aGMP, a_gmp, 10);
  char buffer_x1[100];
  mpz_get_str(buffer_x1, x1, 10);
  char buffer_y1[100];
  mpz_get_str(buffer_y1, y1, 10);
  
  mpz_init_set_str(tco_gcdExtended, gcdExtended(buffer_r_bGMP_mod_aGMP, buffer_aGMP, buffer_x1, buffer_y1)); //gcdExtended(b % a, a, &x1, &y1);
  
  char gcd[100];
  mpz_get_str(gdc, 10, tco_gcdExtended);

  //Creating
  mpz_t r_b_div_a, r_bDiva_mul_x1, r_y1_dif_bax1;
  //Initializing
  mpz_init(r_b_div_a);
  mpz_init(r_bDiva_mul_x1);
  mpz_init(r_y1_dif_bax1);
  //Operations
  mpz_div(r_b_div_a, b_gmp, a_gmp);
  mpz_mul(r_bDiva_mul_x1, r_b_div_a, x1);
  mpz_sub(r_y1_dif_bax1, y1, r_bDiva_mul_x1);
  
  mpz_set_ui(x_gmp, r_y1_dif_bax1); //*x = y1 - (b / a) * x1;
  mpz_set_ui(y_gmp, x1); //*y = x1;

  //*x = y1 - (b / a) * x1;
  //*y = x1;

  return gcd;
}

/*
//Greatest common divisor
int gcd(char *a, char *b){
  int rest, count=1, aux;

  if(a < b){
    aux = a;
    a = b;
    b = aux;
  }

  while(b != 0){
    rest = a % b;
    a = b;
    b = rest;
    count++;
  }

  return a;
}*/
