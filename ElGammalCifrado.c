#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int Modulo(int a, int p);

int FastPot(int potencia, int base, int p);

int ClavePublica(int clave_privada, int g, int p); 

void cifradoGammal(int *c1, int *c2, int clave_pub, int g, int p, int m);
int DescifradoGammal(int *c1, int *c2, int clave_privada, int p); 

int charToInt(char c);
char IntToChar(int n); 

int main() {
  int *c1 = (int *)malloc(sizeof(int));
  int *c2 = (int *)malloc(sizeof(int));
  int g = 5, p = 503;
  int clave_privada = rand() % (p - 3) + 2;
  int clave_pub = ClavePublica(clave_privada, g, p);
  int i;
  int m;

  char *mensaje, *mensaje_descifrado;
  int *mensaje_c1, *mensaje_c2;

  mensaje = (char *)malloc(100 * sizeof(char));
  printf("Ingrese algo a cifrar: ");
  scanf("%*c%[^\n]", mensaje);

  int mensaje_len = strlen(mensaje);
  mensaje_c1 = (int *)malloc(mensaje_len * sizeof(int));
  mensaje_c2 = (int *)malloc(mensaje_len * sizeof(int));
  mensaje_descifrado = (char *)malloc((mensaje_len + 1) * sizeof(char));

  srand(time(NULL));

  // Cifrado
  for (i = 0; i < mensaje_len; i++) {
    m = charToInt(mensaje[i]); 
    cifradoGammal(c1, c2, clave_pub, g, p, m);
    mensaje_c1[i] = *c1;
    mensaje_c2[i] = *c2;
  }

  // Descifrado
  for (i = 0; i < mensaje_len; i++) {
    *c1 = mensaje_c1[i];
    *c2 = mensaje_c2[i];
    m = DescifradoGammal(c1, c2, clave_privada, p);
    mensaje_descifrado[i] = IntToChar(m);
  }

  mensaje_descifrado[mensaje_len] = '\0';

  printf("Mensaje original: %s\n", mensaje); 
  printf("Mensaje descifrado: %s\n", mensaje_descifrado);

  free(c1);
  free(c2);
  free(mensaje);
  free(mensaje_c1);
  free(mensaje_c2);
  free(mensaje_descifrado);

  return 0;
}

int Modulo(int a, int p) {
  return ((a % p) + p) % p;
}

int FastPot(int potencia, int base, int p) {
  int resultado = 1, b;
  b = Modulo(base, p);
  resultado = potencia % 2 ? b : 1;
  potencia = potencia / 2;

  while (potencia != 0) {
    b = Modulo(b * b, p);
    if (potencia % 2) {
      resultado = Modulo(resultado * b, p);
    }
    potencia = potencia / 2;
  }
  return resultado;
}

int ClavePublica(int clave_privada, int g, int p) {
  return FastPot(clave_privada, g, p);
}

void cifradoGammal(int *c1, int *c2, int clave_pub, int g, int p, int m) {
  int k = (rand() % (p - 3)) + 2; // Generar k entre 2 y p-2
  *c1 = FastPot(k, g, p);
  *c2 = Modulo(m * FastPot(k, clave_pub, p), p);
}

int DescifradoGammal(int *c1, int *c2, int clave_privada, int p) {
  int x = FastPot(p - 1 - clave_privada, *c1, p);
  return Modulo(x * (*c2), p);
}

int charToInt(char c) {
  return (int)c;
}

char IntToChar(int n) {
  return (char)n;
}
