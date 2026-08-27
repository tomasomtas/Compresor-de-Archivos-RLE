#ifndef RLE_H
#define RLE_H

#include <stdio.h>
#include <stdint.h>

// Límite máximo de repeticiones almacenables en un byte sin signo (uint8_t)
#define RLE_MAX_RUN 255

// Códigos de retorno para manejo explícito de errores
typedef enum {
    RLE_OK = 0,
    RLE_ERR_NULL_ARG,
    RLE_ERR_READ,
    RLE_ERR_WRITE,
    RLE_ERR_INVALID_DATA
} rle_status_t;

/**
 * Comprime un flujo de datos de entrada en uno de salida usando RLE.
 * @param in_stream Flujo de origen abierto en modo binario ("rb").
 * @param out_stream Flujo de destino abierto en modo binario ("wb").
 * @return RLE_OK si fue exitoso, o un código de error de rle_status_t.
 */
rle_status_t rle_compress(FILE *in_stream, FILE *out_stream);

/**
 * Descomprime un flujo RLE a su estado original.
 * @param in_stream Flujo comprimido abierto en modo binario ("rb").
 * @param out_stream Flujo de destino abierto en modo binario ("wb").
 * @return RLE_OK si fue exitoso, o un código de error de rle_status_t.
 */
rle_status_t rle_decompress(FILE *in_stream, FILE *out_stream);

/**
 * Devuelve una cadena de texto descriptiva según el código de error.
 */
const char *rle_strerror(rle_status_t status);

#endif // RLE_H
