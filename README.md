# Spotifind

Spotifind es una aplicación de consola en C que permite gestionar y explorar un conjunto de canciones desde un archivo .csv. Los usuarios pueden buscar canciones por género, artista o tempo, además de crear listas de reproducción personalizadas.


🚀 Funcionalidades
Cargar canciones desde un archivo CSV (song_dataset_.csv).
Buscar canciones por género.
Buscar canciones por artista.
Buscar canciones por tempo.
Crear listas de reproducción personalizadas.
Agregar canciones a listas existentes.
Mostrar canciones de una lista de reproducción.

🧠 Estructuras de Datos Usadas
Map: para almacenar canciones por ID, género y artista.
List: para listas de reproducción y artistas por canción.
Estructuras personalizadas:
cancion: representa una canción con título, ID, género, artistas, álbum y tempo.
tipoPlayList: representa una lista de reproducción con un nombre y una lista de canciones.

⚙️ Cómo Compilar
Asegúrate de tener un compilador de C (como gcc) instalado y compila con:

gcc tarea2.c tdas/*.c -o tarea2.exe


▶️ Cómo Usar
Ejecuta el archivo.exe
Se te mostrara un menu como este:
========================================
            Spotifind
========================================
1) Cargar canciones
2) Buscar por Genero
3) Buscar por Artista
4) Buscar por Tempo
5) Crear Lista de Reproduccion
6) Agregar Cancion a la Lista de Reproduccion
7) Mostrar Canciones de una Lista de Reproduccion
8) Salir

📜 Funcionalidades del Menú Spotifind
Importar canciones desde un archivo CSV
Carga un archivo CSV con datos de canciones a la base de datos del programa. Cada canción incluye información como título, artistas, álbum, género y tempo. Es el paso inicial obligatorio para usar el resto de las funciones.

Buscar canciones por artista
Permite ingresar el nombre de un artista y muestra una lista de todas las canciones en las que participa, junto con su título y álbum. Si no se encuentra el artista, se notifica al usuario.

Buscar canciones por género
Muestra todas las canciones que pertenecen a un género musical específico ingresado por el usuario (por ejemplo: pop, rock, reggaetón). Se muestra el título de cada canción junto con su artista principal.

Buscar canciones por nombre
Busca una canción por su título. Si se encuentra, se muestran todos sus detalles: título, artistas, álbum, género y tempo. La búsqueda no distingue entre mayúsculas y minúsculas.

Crear una playlist personalizada
Permite crear una nueva lista de reproducción asignándole un nombre. Luego, se pueden agregar canciones una por una escribiendo su nombre exacto. Solo se pueden agregar canciones ya cargadas en la base de datos.

Ver canciones de una playlist
Muestra todas las canciones que contiene una playlist previamente creada, listando su título y artista principal. Si no existen playlists, se avisa al usuario.

Salir del programa
Finaliza la ejecución del programa.
