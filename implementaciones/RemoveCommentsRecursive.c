#include <stdio.h>

void processCodigo(void);
void processBarra(void);
void processComLinea(void);
void processComBloque(void);
void processAsterisco(void);
void processString(void);
void processCaracter(void);
void processEscapeString(void);
void processEscapeCaracter(void);

// ESTADO CODIGO: copia todo salvo '/', '"', '\''
void processCodigo(void) {
    int c = getchar();
    if (c == EOF) return;
    if (c == '/') {
        processBarra();
    } else if (c == '"') {
        putchar(c);
        processString();
    } else if (c == '\'') {
        putchar(c);
        processCaracter();
    } else {
        putchar(c);
        processCodigo();
    }
}

// ESTADO BARRA: decide si es //, /* o solo '/'
void processBarra(void) {
    int c = getchar();
    if (c == EOF) {
        putchar('/');
        return;
    }
    if (c == '/') {
        processComLinea();
    } else if (c == '*') {
        processComBloque();
    } else {
        putchar('/');
        putchar(c);
        processCodigo();
    }
}

// ESTADO COM_LINEA: descarta todo hasta '\n'
void processComLinea(void) {
    int c = getchar();
    if (c == EOF) return;
    if (c == '\n') {
        putchar(c);
        processCodigo();
    } else {
        processComLinea();
    }
}

// ESTADO COM_BLOQUE: descarta todo hasta ver '*'
void processComBloque(void) {
    int c = getchar();
    if (c == EOF) return;
    if (c == '*') {
        processAsterisco();
    } else {
        processComBloque();
    }
}

// ESTADO ASTERISCO: confirma si se cierra con '/'
void processAsterisco(void) {
    int c = getchar();
    if (c == EOF) return;
    if (c == '/') {
        processCodigo();
    } else if (c == '*') {
        processAsterisco();
    } else {
        processComBloque();
    }
}

// ESTADO STRING: copia todo hasta que termine el literal
void processString(void) {
    int c = getchar();
    if (c == EOF) return;
    putchar(c);
    if (c == '\\') {
        processEscapeString();
    } else if (c == '"') {
        processCodigo();
    } else {
        processString();
    }
}

// ESTADO CARACTER: similar a STRING pero para comillas simples
void processCaracter(void) {
    int c = getchar();
    if (c == EOF) return;
    putchar(c);
    if (c == '\\') {
        processEscapeCaracter();
    } else if (c == '\'') {
        processCodigo();
    } else {
        processCaracter();
    }
}

// ESTADO ESCAPE: emite carácter y vuelve al literal correspondiente
void processEscapeString(void) {
    int c = getchar();
    if (c == EOF) return;
    putchar(c);
    processString();
}
void processEscapeCaracter(void) {
    int c = getchar();
    if (c == EOF) return;
    putchar(c);
    processCaracter();
}

// Llamar a processCodigo
int main(void) {
    processCodigo();
    return 0;
}
