#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gmp.h>
#include <string.h>

typedef struct {
  mpz_t e;
  mpz_t d;
  mpz_t n;
  long c;
}
Result;

void generateBigCousins(mpz_t p, mpz_t q, int bit_size) {
  gmp_randstate_t gmp_randstate;
  gmp_randinit_mt(gmp_randstate);
  gmp_randseed_ui(gmp_randstate, time(NULL));

  do {
    mpz_urandomb(p, gmp_randstate, bit_size);
    mpz_nextprime(p, p);

    mpz_set(q, p);
    mpz_add_ui(q, q, 2); // Busca un primo cercano a p
    mpz_nextprime(q, q);

  } while (mpz_cmp(p, q) == 0); // Asegúrate de que p y q no sean iguales, esto es muy importante por temas de seguridad

  gmp_randclear(gmp_randstate);
}

void calculateModularInverse(mpz_t d, mpz_t e, mpz_t phi) {
  if (!mpz_invert(d, e, phi)) {
    gmp_printf("Error: No se puede calcular el inverso modular\n");

  }
}

Result encryptor(int message) {
  Result r;
  int bit_size = 10;
  mpz_inits(r.e, r.d, r.n, NULL);
  mpz_t p, q, n, phi, e, d, message_mpz, c, m;
  mpz_inits(p, q, n, phi, e, d, message_mpz, c, m, NULL);

  // Genera primos grandes y cercanos
  generateBigCousins(p, q, bit_size);

  gmp_printf("Número primo 1 (p): %Zd\n", p);
  gmp_printf("Número primo 2 (q): %Zd\n", q);

  // Calcula n = p * q
  mpz_mul(n, p, q);

  // Calcula phi = (p-1) * (q-1)
  mpz_t temp1, temp2;
  mpz_inits(temp1, temp2, NULL);
  mpz_sub_ui(temp1, p, 1);
  mpz_sub_ui(temp2, q, 1);
  mpz_mul(phi, temp1, temp2);

  mpz_set_ui(e, 65537); // Valor común para e, este e vi que se usa en RSA productivos.

  mpz_gcd(temp1, e, phi); // Calcula gcd(e, phi) y almacena el resultado en temp1
  if (mpz_cmp_ui(temp1, 1) != 0) { // Verifica que gcd(e, phi) != 1
    gmp_printf("Error: 'e' no es coprimo con phi\n");
    exit(1);
  }

  // Calculamos el inverso modular asi nos otorga buena presicion
  calculateModularInverse(d, e, phi);

  // seteamos el mensaje a mpz asi ambos son structss
  mpz_set_ui(message_mpz, message);

  mpz_powm(c, message_mpz, e, n);

  long floatC = mpz_get_si(c);
  r.c = floatC;
  mpz_init_set(r.e, e);
  mpz_init_set(r.d, d);
  mpz_init_set(r.n, n);
  mpz_clears(p, q, n, phi, e, d, message_mpz, c, temp1, temp2, NULL);
  return r;
}
long decryptor(long c, mpz_t d, mpz_t n) {
  mpz_t m, cGMP;
  mpz_init(m);
  mpz_init(cGMP);

  mpz_set_si(cGMP, c);

  mpz_powm(m, cGMP, d, n); // m = (c ^ d) % n

  long floatM = mpz_get_si(m);

  mpz_clear(m);
  mpz_clear(cGMP);

  return floatM;
}

int main() {
  mpz_t e, d, n;
  mpz_init(e);
  mpz_init(d);
  mpz_init(n);

  Result result;

  char * MessageToEncript = "quieroSerIngenieroEnInformatica";

  int messageLength = strlen(MessageToEncript);
  long AsciiMessageEncripted[messageLength];

  for (int i = 0; MessageToEncript[i] != '\0'; i++) {
    result = encryptor((int) MessageToEncript[i]);
    AsciiMessageEncripted[i] = result.c;
    mpz_set(e, result.e);
    mpz_set(d, result.d);
    mpz_set(n, result.n);
  }

  gmp_printf("Clave Publica: (%Zd, %Zd)\n", e, n);
  gmp_printf("Clave Privada (No la compartas !!): (%Zd, %Zd)\n", d, n);

  printf("Mensaje Desencriptado:\n");
  for (int i = 0; i < messageLength; i++) {
    long decryptedChar = decryptor(AsciiMessageEncripted[i], d, n);
    printf("%c", (char) decryptedChar);
  }
  printf("\n");

  return 0;
}