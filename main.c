#include <stdio.h>
#include <string.h>
#include "rle.h"

void print_usage(const char *prog_name) {
    printf("Uso del compresor RLE:\n");
    printf("  Comprimir:    %s -c <archivo_origen> <archivo_destino>\n", prog_name);
    printf("  Descomprimir: %s -d <archivo_origen> <archivo_destino>\n", prog_name);
}

int main(int argc, char *argv[]) {
    // Verificar que se hayan pasado 3 parametros (-opcion entrada salida)
    if (argc != 4) {
        print_usage(argv[0]);
        return 1;
    }

    const char *flag = argv[1];
    const char *input_path = argv[2];
    const char *output_path = argv[3];

    // Abrir archivos obligatoriamente en modo binario ("rb" y "wb")
    FILE *in = fopen(input_path, "rb");
    if (!in) {
        perror("Error al abrir el archivo de entrada");
        return 1;
    }

    FILE *out = fopen(output_path, "wb");
    if (!out) {
        perror("Error al crear el archivo de salida");
        fclose(in);
        return 1;
    }

    rle_status_t status;

    if (strcmp(flag, "-c") == 0) {
        printf("Comprimiendo %s -> %s...\n", input_path, output_path);
        status = rle_compress(in, out);
    } else if (strcmp(flag, "-d") == 0) {
        printf("Descomprimiendo %s -> %s...\n", input_path, output_path);
        status = rle_decompress(in, out);
    } else {
        printf("Opcion invalida: %s\n", flag);
        print_usage(argv[0]);
        fclose(in);
        fclose(out);
        return 1;
    }

    // Siempre cerrar flujos abiertos
    fclose(in);
    fclose(out);

    if (status != RLE_OK) {
        printf("Error procesando el archivo: %s\n", rle_strerror(status));
        return 1;
    }

    printf("Operacion completada con exito.\n");
    return 0;
}
