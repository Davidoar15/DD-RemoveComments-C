# Remover Comentarios en C

## Consigna:

Escribir un programa que remueva todos los comentarios de un programa C.

## Especificaciones de Máquina de Estados planteada

El flujo general de la máquina de estados para eliminar comentarios en C empieza siempre en el estado CODIGO y procesa el programa carácter a carácter.

### 1. Estado Inicial: CODIGO

* Descripción: Copia cada carácter a la salida salvo que detecte el posible inicio de un comentario.

* Transiciones:
    - Si ve una `/`, cambia a BARRA (aún no sabe si es comentario).

    - Si ve `"` o `'`, emite ese carácter y pasa a CADENA o CARACTER para no confundir literales con comentarios.

    - Cualquier otro carácter lo emite directamente y permanece en CODIGO.

### 2. Detección del `/`: BARRA

* Cuando se entra en BARRA, se sabe que acaba de ver un `/`:

* Se lee el siguiente carácter `c`:
    - Si `c` = `/` vuelve a Barra -> COM_LINEA: empieza un comentario de línea `//`.

    - Si `c` = `***` cambia a COM_BLOQUE: empieza un comentario de bloque `/*`.

    - En cualquier otro caso: no era comentario. Entonces se emite primero el `/` que estaba "pendiente", luego se emite `c`, y se regresa a CODIGO.

### 3. Comentario de Línea: COM_LINEA

* Descripción: Descarta todo hasta encontrar el salto de línea. Se leen los caracteres uno a uno y no se emite nada mientras se está en este estado.

* Cuando se lee `\n`:
    1. Emite `\n`.

    2. Se vuelve a CODIGO.

### 4. Comentario de Bloque: COM_BLOQUE

* Descripción: Descarta todo hasta encontrar la secuencia `*/`. Se leen los caracteres y permanece en COM_BLOQUE mientras no se vea el `*`.

* Si se lee un `*`, se pasa a ASTERISCO, un subestado de cierre potencial de bloque.

### 5. Subestado de Cierre: ASTERISCO

* Se lee un carácter `c`:
    - Si `c` = `/` -> FIN de bloque: se vuelve a CODIGO.

    - Si `c` = `***` -> Se queda en ASTERISCO.

    - Si `c` = `otro` -> No era el cierre `*/`, se vuelve a COM_BLOQUE y se sigue descartando.

### 6. Literales: STRING Y CHAR

* Para no eliminar "comentarios" que aparezcan dentro de literales, cada vez que desde CODIGO se ve `"` o `'`:
    1. Emitir la comilla y pasar a STRING (caso de `"`) o CHAR (caso de `'`).

    2. En STRING / CHAR:
        - Lee y emite todo carácter normal.

        - Si ve `\` se pasa a ESCAPE, para emitir también la siguiente letra sin acabar el string.

        - Si ve la comilla de cierre (`"` en STRING, `'` en CHAR), se emite y regresa a CODIGO.

### 7. Escape dentro de Literales: ESCAPE

* Se lee un carácter `c`, se emite directamente (por ejemplo `\"` o `\'`) y se regresa al estado STRING o CHAR según donde se estaba.

### Diagrama de la Máquina de Estados

![Maquina-Estados](https://i.postimg.cc/QxdgHBhT/Maquina-Estado.png)

