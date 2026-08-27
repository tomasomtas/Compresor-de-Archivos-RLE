Markdown
# RLE File Compressor (CLI)

Compresor y descompresor de archivos en línea de comandos desarrollado en **C puro**, utilizando el algoritmo de compresión sin pérdida **Run-Length Encoding (RLE)**. 

Diseñado con un enfoque modular, bajo consumo de memoria RAM mediante flujos de datos (*streams*) y manejo riguroso de I/O binario.

## 🚀 Características
* **Compresión sin pérdida:** Algoritmo RLE optimizado para archivos con secuencias de bytes repetidos.
* **Procesamiento eficiente:** Uso de *streams* (`FILE*`) para un consumo de memoria RAM prácticamente nulo, sin importar el tamaño del archivo.
* **Arquitectura modular:** Separación limpia entre interfaz CLI (`main.c`), motor del algoritmo (`rle.c`) y contrato de API (`rle.h`).
* **Robustez:** Gestión explícita de errores mediante enumeraciones (`rle_status_t`) y control de desbordamiento de búfer.

## 🛠️ Compilación
Puedes abrir el proyecto y compilarlo con **Code::Blocks** (tecla F9), o compilarlo desde la terminal con `gcc`:

```bash
gcc -Wall -Wextra -std=c11 main.c rle.c -o rle
💻 Uso
Comprimir un archivo:

Bash
./rle -c archivo_origen.txt comprimido.rle
Descomprimir un archivo:

Bash
./rle -d comprimido.rle archivo_destino.txt
🔮 Futuras Mejoras
[ ] Desarrollo de una interfaz gráfica (GUI) en Python integrada mediante subprocess.

[ ] Detección automática del porcentaje de compresión logrado en consola.