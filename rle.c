#include "rle.h"

rle_status_t rle_compress(FILE *in_stream, FILE *out_stream) {
    if (!in_stream || !out_stream) return RLE_ERR_NULL_ARG;

    int current = fgetc(in_stream);
    if (current == EOF) return RLE_OK; // Archivo vacío

    uint8_t count = 1;
    int next;

    while ((next = fgetc(in_stream)) != EOF) {
        if (next == current && count < RLE_MAX_RUN) {
            count++;
        } else {
            // Escribe la cantidad de repeticiones y luego el byte procesado
            if (fputc(count, out_stream) == EOF || fputc(current, out_stream) == EOF) {
                return RLE_ERR_WRITE;
            }
            current = next;
            count = 1;
        }
    }

    // Escribir el último bloque restante
    if (fputc(count, out_stream) == EOF || fputc(current, out_stream) == EOF) {
        return RLE_ERR_WRITE;
    }

    return RLE_OK;
}

rle_status_t rle_decompress(FILE *in_stream, FILE *out_stream) {
    if (!in_stream || !out_stream) return RLE_ERR_NULL_ARG;

    int count, byte;

    while ((count = fgetc(in_stream)) != EOF) {
        byte = fgetc(in_stream);
        if (byte == EOF) return RLE_ERR_INVALID_DATA; // Archivo incompleto o corrupto

        for (int i = 0; i < count; i++) {
            if (fputc(byte, out_stream) == EOF) return RLE_ERR_WRITE;
        }
    }

    return RLE_OK;
}

const char *rle_strerror(rle_status_t status) {
    switch (status) {
        case RLE_OK: return "Operacion exitosa";
        case RLE_ERR_NULL_ARG: return "Puntero nulo en los argumentos";
        case RLE_ERR_READ: return "Error al leer el archivo";
        case RLE_ERR_WRITE: return "Error al escribir en el archivo";
        case RLE_ERR_INVALID_DATA: return "Formato de archivo comprimido invalido";
        default: return "Error desconocido";
    }
}
