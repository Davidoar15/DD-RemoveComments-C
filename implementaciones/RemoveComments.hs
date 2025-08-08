import System.IO (isEOF)

data Estado = 
    Codigo      -- Estado principal. Copia caracteres normales
  | Barra       -- Detecta '/' y espera ver si es comentario
  | ComLinea    -- Comentario de línea "//". Descarta hasta encontrar '\n'
  | ComBloque   -- Comentario de bloque "/* ... */". Descarta contenido
  | Asterisco   -- Subestado dentro de comentario de bloque, mira '*', posible cierre
  | String      -- Dentro de un literal de texto "", se copia todo
  | Caracter    -- Dentro de un literal de carácter ''
  | Escape      -- Secuencia de escape en literal (\n, \", etc.)
  deriving (Eq)

main :: IO ()
main = process Codigo

-- process: procesa caracter a caracter segun el estado
process :: Estado -> IO ()
process estado = do
  eof <- isEOF
  if eof then return () else do
    c <- getChar
    case (estado, c) of

      -- ESTADO CODIGO: copia todo salvo '/', '"', '\''
      (Codigo, '/') -> process Barra -- Posible inicio de comentario
      (Codigo, '"') -> putChar '"' >> process String -- Literal de string
      (Codigo, '\'') -> putChar '\'' >> process Caracter -- Literal de carácter
      (Codigo, char) -> putChar char >> process Codigo -- Otro: emite y sigue

      -- ESTADO BARRA: decide si es //, /* o solo '/'
      (Barra, '/') -> process ComLinea -- Comentario de línea
      (Barra, '*') -> process ComBloque -- Comentario de bloque
      (Barra, char) -> putChar '/' >> putChar char >> process Codigo -- No era comentario: emite '/' y el carácter

      -- ESTADO COM_LINEA: descarta todo hasta '\n'
      (ComLinea, '\n') -> putChar '\n' >> process Codigo
      (ComLinea, _) -> process ComLinea -- Sigue descartando

      -- ESTADO COM_BLOQUE: descarta todo hasta ver '*'
      (ComBloque, '*') -> process Asterisco -- Observa '*', posible cierre
      (ComBloque, _) -> process ComBloque

      -- ESTADO ASTERISCO: confirma si se cierra con '/'
      (Asterisco, '/') -> process Codigo -- Fin del comentario de bloque
      (Asterisco, '*') -> process Asterisco -- Sigue en posible cierre
      (Asterisco, _)   -> process ComBloque -- No era cierre, vuelve a ComBloque

      -- ESTADO STRING: copia todo hasta que termine el literal
      (String, '\\') -> putChar '\\' >> process Escape -- Secuencia de escape
      (String, '"') -> putChar '"' >> process Codigo -- Cierra literal
      (String, char) -> putChar char >> process String -- Copia carácter

      -- ESTADO CARACTER: similar a STRING pero para comillas simples
      (Caracter, '\\') -> putChar '\\' >> process Escape
      (Caracter, '\'') -> putChar '\'' >> process Codigo
      (Caracter, char) -> putChar char >> process Caracter

      -- ESTADO ESCAPE: emite carácter y vuelve al literal correspondiente
      (Escape, char) -> putChar char >> process String