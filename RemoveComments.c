#include <stdio.h>

int main(void) {
    int c;

    goto ESTADO_CODIGO;

    // ESTADO_CODIGO:
    // - Emite chars normales
    // - Detecta '/', '"' o '\''
    ESTADO_CODIGO:
        c = getchar();
        if (c == EOF) goto FIN;
        if (c == '/') goto ESTADO_BARRA; 
        if (c == '"') {
            putchar(c);
            goto ESTADO_STRING;
        }
        if (c == '/') {
            putchar(c);
            goto ESTADO_CARACTER;
        }
        putchar(c);
        goto ESTADO_CODIGO;
        
    // ESTADO_BARRA:
    // - Tras leer '/'
    // - Determina inicio de comentario
    ESTADO_BARRA:
        c = getchar();
        if (c == EOF) {
            putchar('/');
            goto FIN;
        };
        if (c == '/') goto ESTADO_COM_LINEA;
        if (c == '*') goto ESTADO_COM_BLOQUE;
        putchar('/');
        putchar(c);
        goto ESTADO_CODIGO;
    
    // ESTADO_COM_LINEA:
    // - Descarta hasta encontrar '\n'
    // - Emite '\n' y vuelve a ESTADO_CODIGO
    ESTADO_COM_LINEA:
        c = getchar();
        if (c == EOF) goto FIN;
        if (c == '\n') {
            putchar(c);
            goto ESTADO_CODIGO;
        }
        goto ESTADO_COM_LINEA;

    // ESTADO_COM_BLOQUE:
    // - Descarta hasta encontrar '*'
    ESTADO_COM_BLOQUE:
        c = getchar();
        if (c == EOF) goto FIN;
        if (c == '*') goto ESTADO_ASTERISCO;
        goto ESTADO_COM_BLOQUE;

    // ESTADO_ASTERISCO:
    // - Tras ver '*'
    // - Si aparece '/' entonces se cierra el bloque
    // - Si aparece '*' entonces se sigue en asterisco
    // - Otro, vuelve a bloque
    ESTADO_ASTERISCO:
        c = getchar();
        if (c == EOF) goto FIN;
        if (c == '/') goto ESTADO_CODIGO;
        if (c == '*') goto ESTADO_ASTERISCO;
        goto ESTADO_COM_BLOQUE;

    // ESTADO_STRING:
    // - Literal entre ""
    // - Maneja '\\' para escapes
    ESTADO_STRING:
        c = getchar();
        if (c == EOF) goto FIN;
        putchar(c);
        if (c == '\\') goto ESTADO_ESCAPE;
        if (c == '"') goto ESTADO_CODIGO;
        goto ESTADO_STRING;

    // ESTADO_CARACTER:
    // - Literal entre ''
    // - Igual que CADENA
    ESTADO_CARACTER:
        c = getchar();
        if (c == EOF) goto FIN;
        putchar(c);
        if (c == '\\') goto ESTADO_ESCAPE;
        if (c == '\'') goto ESTADO_CODIGO;
        goto ESTADO_CARACTER;

    // ESTADO_ESCAPE:
    // - Emite el caracter escapado
    // - Vuelve a STRING o CARACTER
    ESTADO_ESCAPE:
        c = getchar();
        if (c == EOF) goto FIN;
        putchar(c);
        goto ESTADO_STRING;
    
    FIN:
        return 0;
}
