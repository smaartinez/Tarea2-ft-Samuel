#include "tdas/extra.h"
#include "tdas/list.h"
#include "tdas/map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
  int tempo;
  char id[100];
  char title[100];
  char gender[100];
  List *artists;
  char album[100];
} cancion;

typedef struct
{
  char nombreLista[100];
  List* canciones;
}tipoPlayList;

// Menú principal
void mostrarMenuPrincipal() 
{
  limpiarPantalla();
  puts("========================================");
  puts("     Spotifind     ");
  puts("========================================");

  puts("1) Cargar canciones");
  puts("2) Buscar por Genero");
  puts("3) Buscar por Artista");
  puts("4) Buscar por Tempo");
  puts("5) Crear Lista de Reproduccion");
  puts("6) Agregar Cancion a la Lista de Reproduccion");
  puts("7) Mostrar Canciones de una Lista de Reproduccion");
  puts("8) Salir");
}

/**
 * @param key1 Primer puntero a la clave string.
 * @param key2 Segundo puntero a la clave string.
 * @return Retorna 1 si las claves son iguales, 0 de lo contrario.
 */

 int is_equal_str(void *key1, void *key2) {
  return strcmp((char *)key1, (char *)key2) == 0;
}

/**
 * Compara dos claves de tipo entero para determinar si son iguales.
 * Esta función se utiliza para inicializar mapas con claves de tipo entero.
 *
 * @param key1 Primer puntero a la clave entera.
 * @param key2 Segundo puntero a la clave entera.
 * @return Retorna 1 si las claves son iguales, 0 de lo contrario.
 */

 int is_equal_int(void *key1, void *key2) {
  return *(int *)key1 == *(int *)key2; 
}

/* Lo que hace esta funcion es abrir y leer el dataset de las canciones para luego cargar el maximo de canciones solicitado por la persona, se ingresan los mapas del id de las canciones, de
su genero y de los artistas. Ademas se crea una lista genero y artista ya que esto nos ayudara en futuras funciones. */ 
void leer_y_cargar_canciones(Map *canciones_id, Map *canciones_genero, Map *canciones_artista) 
{
  long totalCanciones = 0; 

  puts("==========================================================");
  puts("          CARGAR CANCIONES          ");
  puts("==========================================================");

  printf("Ingrese canciones desea cargar (MAXIMO SOPORTADO 113998): ");
  scanf("%lu", &totalCanciones); 

  FILE *archivo = fopen("song_dataset_.csv", "r");
  if (archivo == NULL) 
  {
    perror("Error no se logro abrir el archivo"); 
    return;
  }

  char **campos;
  campos = leer_linea_csv(archivo, ','); // Lee los encabezados del CSV
  long contador = 0; // Contador de canciones cargadas
  while((campos = leer_linea_csv(archivo, ',')) != NULL)
  {
    if (contador >= totalCanciones) break;
    cancion *nuevaCancion = (cancion *)malloc(sizeof(cancion)); 
    if (nuevaCancion == NULL) 
    {
      perror("Error al asignar memoria para la nueva canción");
      fclose(archivo);
      return;
    }

    strncpy(nuevaCancion->id, campos[0], sizeof(nuevaCancion->id)); 
    nuevaCancion->artists = split_string(campos[2], ";"); 
    strncpy(nuevaCancion->album, campos[3], sizeof(nuevaCancion->album));
    strncpy(nuevaCancion->title, campos[4], sizeof(nuevaCancion->title));
    nuevaCancion->tempo = atoi(campos[18]); 
    strncpy(nuevaCancion->gender, campos[20], sizeof(nuevaCancion->gender));
    
    map_insert(canciones_id, nuevaCancion->id, nuevaCancion); // Inserta en el mapa por ID
    MapPair *pairGeneros = map_search(canciones_genero, nuevaCancion->gender);
    if (pairGeneros == NULL) 
    {
      List *nuevaListaGenero = list_create(); // Crea una nueva lista para el género
      list_pushBack(nuevaListaGenero, nuevaCancion); // Agrega la canción a la lista
      map_insert(canciones_genero, nuevaCancion->gender, nuevaListaGenero); 
    }
    else
    {
      List *listaGenero = (List *)pairGeneros->value; 
      list_pushBack(listaGenero, nuevaCancion); 
    }

    char *artista = list_first(nuevaCancion->artists); 
    while (artista != NULL)
    {
      MapPair *pairDeArtista = map_search(canciones_artista, artista);
      if (pairDeArtista == NULL)
      {
        List *nuevaListaArtista = list_create();
        list_pushBack(nuevaListaArtista, nuevaCancion); 
        map_insert(canciones_artista, artista, nuevaListaArtista); 
      }
      else
      {
        List *listaArtista = (List *)pairDeArtista->value; 
        list_pushBack(listaArtista, nuevaCancion); 
      }
      artista = list_next(nuevaCancion->artists); 
    }
    contador++; 

    if (contador == 1) printf("Ingresando Canciones...");
  }
  printf("Se han cargado exitosamente %ld canciones\n", contador); 
  puts("==========================================================");
  fclose(archivo); 
}

/* Esta funcion se encarga de buscar las canciones por genero, primero verifica si hay generos registrados, 
si no los hay se avisa al usuario. Luego se pide el genero a buscar y se busca en la lista de generos. 
Para luego mostrar todas las canciones encontradas con ese genero*/
  
void buscar_por_genero(Map *canciones_genero) 
  {
  char generoCancion[100];
  
  puts("==========================================================");
  puts("                      BUSCAR POR GENERO");
  puts("==========================================================");

  if (canciones_genero == NULL || map_first(canciones_genero) == 0) 
  {
    puts("\n\n==========================================================");
    puts("ERROR: No hay generos registrados.");
    puts("==========================================================");
    return;
  }
  
  printf("Ingrese el genero que desea buscar: ");
  scanf(" %[^\n]%*c", generoCancion);
 
  
  MapPair *pairGender = map_search(canciones_genero, generoCancion);

  if (pairGender == NULL) 
  {
    puts("==========================================================");
    puts("ERROR: No se encontraron canciones con ese tipo de genero.");
    puts("==========================================================");
    return;
  }
  else
  {
    List *cancionesEncontradas = (List *)pairGender->value; 
    puts("\n==========================================================");
    printf("Canciones encontradas con el genero \"%s\":\n", generoCancion);
    puts("==========================================================");

    cancion *cancionActual = (cancion *)list_first(cancionesEncontradas); 
    while (cancionActual != NULL)
    {
      printf("ID: %s\n", cancionActual->id);
      printf("Nombre Cancion: %s\n", cancionActual->title);
      char *artista = list_first(cancionActual->artists); 
      printf("Artista: ");
      while (artista != NULL) 
      {
        printf("%s ", artista); 
        artista = list_next(cancionActual->artists); 
      }
      printf("\n");
      printf("Album: %s\n", cancionActual->album);
      printf("Tempo: %d\n", cancionActual->tempo);
      printf("===========================================================\n");
      cancionActual = (cancion *)list_next(cancionesEncontradas); 
    }
  }
}


/* Esta funcion se encarga de buscar las canciones por artista, primero verifica si hay artistas registrados,
si no los hay se avisa al usuario. Luego se pide el artista a buscar y se busca en la lista de artistas. 
Para luego mostrar todas las canciones encontradas con ese artista*/
void buscar_por_artista(Map *canciones_artista)
{
  char artista[100];
  puts("==========================================================");
  puts("                      BUSCAR POR ARTISTA");
  puts("==========================================================");
  if (canciones_artista == NULL || map_first(canciones_artista) == 0)
  {
    puts("\n\n==========================================================");
    puts("ERROR: No hay artistas registrados.");
    puts("==========================================================");
    return;
  }
  printf("Ingrese el nombre del artista: ");
  scanf(" %[^\n]%*c", artista);
  limpiarPantalla();
  puts("==========================================================");
  printf("CANCIONES DEL ARTISTA \"%s\":\n", artista);
  puts("==========================================================");

  MapPair *pairArtista = map_search(canciones_artista, artista);
  if (pairArtista == NULL)
  {
    puts("==========================================================");
    puts("ERROR: No se encontraron canciones para el artista.");
    puts("==========================================================");
    return;
  }
  else
  {
    List *canciones = (List *)pairArtista->value;
    cancion *cancionActual = list_first(canciones);
    while (cancionActual != NULL)
    {
      printf("ID: %s\n", cancionActual->id);
      printf("Nombre Cancion: %s\n", cancionActual->title);
      printf("Album: %s\n", cancionActual->album);
      printf("Tempo: %d\n", cancionActual->tempo);
      printf("===========================================================\n");
      cancionActual = (cancion *)list_next(canciones); 
    }
  }
  List *canciones = (List *)pairArtista->value;
  printf("==========================================================\n");
  printf("Se han encontrado %d canciones para el artista %s\n", list_size(canciones), artista);
}


/* Esta funcion se encarga de agregar una cancion a una lista de reproduccion, primero verifica si hay listas de reproduccion registradas,
si no las hay se avisa al usuario. Luego se pide el nombre de la lista a la que se quiere agregar la cancion y se busca en la lista de listas de reproduccion.
Para luego pedir el id de la cancion a agregar y se busca en el mapa de canciones.
Si se encuentra la cancion, se agrega a la lista de reproduccion. */
void addSongPlaylist(Map *canciones_id, Map *lista_reproduccion) 
{
  char idCancion[100];
  char nombreLista[100];
  puts("==========================================================");
  puts("          AGREGAR CANCION A LISTA DE REPRODUCCION");
  puts("==========================================================");
  puts("");
  if(lista_reproduccion == NULL)
  {
    
    puts("\nADVERTENCIA: No hay Listas de Reproduccion guardadas.");
    puts("==========================================================");
    return;
  }

  printf("Lista de Reproducciones disponibles:\n");
  MapPair *listasRep_disponible = map_first(lista_reproduccion);
  
  while (listasRep_disponible) 
  {
    printf(" - %s\n", (char *)listasRep_disponible->key);
    listasRep_disponible = map_next(lista_reproduccion);
  }
  puts("==========================================================");
  
  puts("Ingrese el nombre de la lista de reproduccion:");
  scanf(" %[^\n]", nombreLista);
  MapPair *pairList = map_search(lista_reproduccion, nombreLista);

  if(pairList == NULL){
    puts("\n==========================================================");
    puts("ERROR: No existe una lista de reproduccion con ese nombre.");
    puts("==========================================================");
    return;
  }
  tipoPlayList* listaCanciones = (tipoPlayList *)pairList->value;

  puts("Ingrese el ID de la cancion:");
  scanf(" %s", idCancion);

  MapPair *pairCancion = map_search(canciones_id, idCancion);
  if(pairCancion == NULL){
    puts("\n==========================================================");
    puts("ERROR: No se encontro una cancion con ese ID");
    puts("==========================================================");
  }

  cancion* song = (cancion*)pairCancion->value;

  list_pushBack(listaCanciones->canciones, song);
  
  printf("La cancion \"%s\" se agrego a la lista de reproduccion \"%s\" correctamente :).\n", song->title, listaCanciones->nombreLista);
}


/* Esta funcion se encarga de mostrar las canciones de una lista de reproduccion, primero verifica si hay listas de reproduccion registradas,
si no las hay se avisa al usuario. Luego se pide el nombre de la lista a la que se quiere mostrar las canciones y se busca en la lista de listas de reproduccion.
Para luego mostrar todas las canciones encontradas en la lista de reproduccion. */
void showSongsPlaylist(Map *lista_reproduccion)
{
  char nombreLista[100];
  puts("==========================================================");
  puts("          MOSTRAR CANCIONES DE UNA LISTA DE REPRODUCCION");
  puts("==========================================================");
  puts("");
  if(lista_reproduccion == NULL || map_first(lista_reproduccion) == 0){
    puts("\nADVERTENCIA: No hay Listas de Reproduccion guardadas.");
    puts("==========================================================");
    return;
  }

  printf("Lista de Reproducciones disponibles:\n");
  MapPair *listasRep_disponible = map_first(lista_reproduccion);
  
  while (listasRep_disponible) {
    printf(" - %s\n", (char *)listasRep_disponible->key);
    listasRep_disponible = map_next(lista_reproduccion);
  }
  puts("==========================================================");
  
  puts("Ingrese el nombre de la lista de reproduccion:");
  scanf(" %[^\n]", nombreLista);
  MapPair *pairList = map_search(lista_reproduccion, nombreLista);

  if(pairList == NULL){
    puts("\n==========================================================");
    puts("ERROR: No existe una lista con ese nombre.");
    puts("==========================================================");
    return;
  }
  
  tipoPlayList* listaCanciones = (tipoPlayList *)pairList->value;

  cancion* song = (cancion*)list_first(listaCanciones->canciones);
  
  if(song == NULL){
    printf("La lista de reproduccion \"%s\" está vacía.\n", nombreLista);
    return;
  }

  while(song != NULL){
      printf("==========================================================\n");
      printf("ID: %s\n", song->id);
      printf("Nombre Cancion: %s\n", song->title);
      printf("Artista: ");
      char *artista = list_first(song->artists);
      while (artista) {
        printf("%s ", artista);
        artista = list_next(song->artists);
      }
      printf("\n");
      printf("Album: %s\n", song->album);
      printf("Tempo: %d\n", song->tempo);
      printf("Genero: %s\n", song->gender);
      printf("==========================================================\n");
      song = (cancion*)list_next(listaCanciones->canciones);
  }
}



/* Esta funcion se encarga de crear una lista de reproduccion, primero verifica si ya existe una lista con ese nombre,
si ya existe se avisa al usuario. Luego se pide el nombre de la lista a crear y se busca en la lista de listas de reproduccion.
Para luego crear la lista de reproduccion y agregarla al mapa de listas de reproduccion. */
void createPlaylist(Map *lista_reproduccion)
{
  char NombrePlaylist[100];

  puts("==========================================================");
  puts("          CREAR LISTA DE REPRODUCCION");
  puts("==========================================================");
  puts("");
  printf("Ingrese el nombre de la nueva lista de reproduccion: ");
  scanf(" %[^\n]", NombrePlaylist);


  if (map_search(lista_reproduccion, NombrePlaylist) != NULL) {
      puts("\n==========================================================");
      puts("ERROR: Ya existe una lista de reproduccion con ese nombre.");
      puts("==========================================================");
      return;
  }


  tipoPlayList *Nuevaplaylist = malloc(sizeof(tipoPlayList));
  if (Nuevaplaylist == NULL) {
      puts("ERROR: No se pudo asignar memoria para la nueva lista.");
      return;
  }

  strcpy(Nuevaplaylist->nombreLista, NombrePlaylist);
  Nuevaplaylist->canciones = list_create();

  
  map_insert(lista_reproduccion, Nuevaplaylist->nombreLista, Nuevaplaylist);

  puts("\n==========================================================");
  printf("La lista de reproduccion \"%s\" ha sido creada exitosamente.\n", Nuevaplaylist->nombreLista);
  puts("==========================================================");
}


/* Esta funcion se encarga de buscar las canciones por tempo, primero verifica si hay canciones registradas,
si no las hay se avisa al usuario. Luego se pide el tempo a buscar y se busca en la lista de canciones.
Para luego mostrar todas las canciones encontradas con ese tempo*/
void search_for_tempo(Map*canciones_id)
{
  int tempo;
  puts("==========================================================");
  puts("                      BUSCAR POR TEMPO");
  puts("==========================================================");
  puts("Ingrese el tempo que desea buscar: ");
  scanf("%d", &tempo);
  limpiarPantalla();
  puts("==========================================================");
  printf("CANCIONES CON TEMPO \"%d\":\n", tempo);
  puts("==========================================================");
  MapPair *pair = map_first(canciones_id);
  while(pair != NULL)
  {
    cancion *cancionActual = (cancion *)pair->value;
    if(cancionActual->tempo == tempo)
    {
      printf("ID: %s\n", cancionActual->id);
      printf("Nombre Cancion: %s\n", cancionActual->title);
      printf("Album: %s\n", cancionActual->album);
      printf("Artista: ");
      char *artista = list_first(cancionActual->artists); 
      while (artista != NULL) 
      {
        printf("%s ", artista); 
        artista = list_next(cancionActual->artists); 
      }
      printf("\n");
      printf("===========================================================\n");
    }
    pair = map_next(canciones_id);
  
  }
  return;
}

int main() 
{
  char opcion;
               
  Map *canciones_id = map_create(is_equal_str);
  Map *canciones_genero = map_create(is_equal_str);
  Map *lista_reproduccion = map_create(is_equal_str);
  Map *canciones_artista = map_create(is_equal_str);
  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opcion: ");
    scanf(" %c", &opcion);

    switch (opcion) 
    {
    case '1':
      limpiarPantalla();
      leer_y_cargar_canciones(canciones_id, canciones_genero, canciones_artista);
      break;
    case '2':
      limpiarPantalla();
      buscar_por_genero(canciones_genero);
      break;
    case '3':
      limpiarPantalla();
      buscar_por_artista(canciones_artista);
      break;
    case '4':
      limpiarPantalla();
      search_for_tempo(canciones_id);
      break;
    case '5':
      limpiarPantalla();
      createPlaylist(lista_reproduccion);
      break;
    case '6':
      addSongPlaylist(canciones_id, lista_reproduccion);
      break;
    case '7':
      limpiarPantalla();
      showSongsPlaylist(lista_reproduccion);
      break;
    
    case '8':
      limpiarPantalla();
      puts("Saliendo del programa...");
      break;
    }
    presioneTeclaParaContinuar();

  } while (opcion != '8');

  return 0;
}
