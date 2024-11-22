#include <stdio.h>
#define HEADER_SIZE 54

void decript(const char * cadena) {

    for (int i = 1; cadena[i] != '\0'; i += 3) {
        printf("%c", cadena[i]);
    }
    printf("\n");
}

int main() {
    FILE * archivo;
    char nombreArchivo[100];
    unsigned char encabezado[HEADER_SIZE];
    unsigned char byteActual;
    char mensaje[256];
    int contador = 0;

    printf("Ingrese el nombre del archivo BMP: ");
    scanf("%s", nombreArchivo);

    // Abrir el archivo BMP en modo binario
    archivo = fopen(nombreArchivo, "rb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return 1;
    }

    // Leer el encabezado BMP
    fread(encabezado, 1, HEADER_SIZE, archivo);

    // Leer los bytes de la imagen para encontrar el texto encriptado
    while (fread( & byteActual, 1, 1, archivo) == 1) {
        if (byteActual == 'B') {

            fread(mensaje, 1, sizeof(mensaje), archivo);
            contador = sizeof(mensaje);
            break;
        }
    }

    fclose(archivo);

    if (contador > 0) {
        printf("Mensaje encriptado encontrado: %s\n", mensaje);

        printf("El Mensaje Desencriptado Es:");
        decript(mensaje);

    } else {
        printf("No se encontró texto encriptado en el archivo BMP.\n");
    }

    return 0;
}
