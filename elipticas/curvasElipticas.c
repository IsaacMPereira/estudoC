/*
 * Programa para calcular os pontos de uma curva elíptica. Curva em questão: E: y² = x³ + 2x + 2 (mod 17)
 * Isaac Menezes Pereira, 190088885
 * */
 
 #include <stdio.h>
 //#include <math.h> //Não sei porquê a função pow() não funciona
 
 //Assinatura
 int gcdExtended();
 int modInverse();
 int gcd();
 
 int main(){
		int gx=5, gy=1, countPoint=2, s, xr, yr/*, auxX, auxY*/;
		
		for(int i=0; i<1; i++){
			if(countPoint%2 == 0){ //Point doubling
				s = (gcd((3 * gx*gx + 2),17) * (modInverse(2*gy, 17)))%17;
				
				xr = (s*s - 2*gx)%17;
				yr = ((s*(gx - xr) - gy)%17 + 17)%17; //Garante (em C) que o módulo seja feito, mesmo com um número negativo
				//auxX = xr;
				//auxY = yr;
				printf("(%d, %d)\n", xr, yr);
			}else{ //Adition 
				//s = auxY - 
			}
		}
	 
	 return 0;
}

//Calcular o inverso multiplicativo
int gcdExtended(int a, int b, int *x, int *y) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }

    int x1, y1; // Coeficientes para as chamadas recursivas
    int gcd = gcdExtended(b % a, a, &x1, &y1);

    // Atualiza os valores de x e y
    *x = y1 - (b / a) * x1;
    *y = x1;

    return gcd;
}
int modInverse(int a, int m) { //Nesse caso, o inverso sempre existe
    int x, y; // Coeficientes que satisfazem a identidade de Bézout
    int gcd = gcdExtended(a, m, &x, &y);

    // O inverso modular existe apenas se o MDC(a, m) = 1
    if (gcd != 1) {
        printf("Inverso modular não existe.\n");
        return -1; // Retorna -1 para indicar que não há inverso
    }

    // Ajusta x para ser positivo (caso necessário)
    int inverse = (x % m + m) % m;
    
    return inverse;
}

//gcd
int gcd(int a, int b){
		int rest, count=1, aux;
		
		if(a < b){
			aux = a;
			a = b;
			b = aux;
			
			while(b != 0){
				rest = a % b;
				a = b;
				b = rest;
				count++;
			}
		}
	return a;
}
