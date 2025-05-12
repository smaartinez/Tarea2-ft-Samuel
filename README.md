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
# Requisitos Previos
1. Tener instalado Visual Studio Code
2. Tener la extención C/C++
3. Tener instalado un compilador de C, como por ejemplo *MinGW*


# Pasos para ejecutar

1. Descarga el archivo .zip y descomprime este en un directorio a elección
2. Abre el código en Visual Studio Code
Para esto:
- Abre la aplicacion
- Archivo -> Abrir Carpeta
- Y seleccionamos la carpeta donde descomprimimos el programa

3. Para compilar el codigo
- Crea una nueva terminal, en Terminal -> Nueva Terminal
- En la terminal coloca este comando: gcc tarea2.c tdas/*.c -o tarea2.exe


▶️ Cómo Usar
Ejecuta el archivo.exe
Se te mostrara un menu como este:

![image](https://github.com/user-attachments/assets/0747a810-b517-4074-a58d-28cbe86c68bd)


**📜 Funcionalidades del Menú Spotifind**

1. Importar canciones desde un archivo CSV
Carga un archivo CSV con datos de canciones a la base de datos del programa. Cada canción incluye información como título, artistas, álbum, género y tempo. Es el paso inicial obligatorio para usar el resto de las funciones.

2. Buscar canciones por género
Muestra todas las canciones que pertenecen a un género musical específico ingresado por el usuario (por ejemplo: pop, rock, reggaetón). Se muestra el título de cada canción junto con su artista principal.

3. Buscar canciones por artista
Permite ingresar el nombre de un artista y muestra una lista de todas las canciones en las que participa, junto con su título y álbum. Si no se encuentra el artista, se notifica al usuario.

4. Buscar canciones por tempo
Busca una canción por su tempo. Si se encuentra, se muestran todas las canciones que tengan ese numero de tempo.

5. Crear una playlist personalizada
Permite crear una nueva lista de reproducción asignándole un nombre. Luego, se pueden agregar canciones una por una escribiendo su nombre exacto. Solo se pueden agregar canciones ya cargadas en la base de datos.

6. Agregar Cancion a la Lista de Reproduccion
Esta funcion permite agregar una cancion a cualquiera de la listas de reproducciones que tenemos creada. El programa nos preguntara que ingresemos el nombre de la lista de reproduccion para luego ingresar el id de la cancion y agregarla a esta.

8. Ver canciones de una playlist
Muestra todas las canciones que contiene una playlist previamente creada, listando su título y artista principal. Si no existen playlists, se avisa al usuario.

9. Salir del programa
Finaliza la ejecución del programa.
