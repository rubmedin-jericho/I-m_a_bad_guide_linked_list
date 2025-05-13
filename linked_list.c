/*                                Vamos a ver esta es la guia paso por paso.                              */

/*<------------------------------------------------------------------------------------------------------------>*/

/*1-Lo primero seria plantearse la struct este es un ejemplo la struct puede ser como tu necesites esta es muy basica
 * , lo llamo nodo porque la entiedad/elemento se llama nodo.*/

typedef struct stack{
  int numero;
  struct stack *next;
}node;

/*<------------------------------------------------------------------------------------------------------------>*/

/*2-Las librerias, vamos a hacer muchos mallocs asi que stdlib.h obligatorio la de stdio.h es para en este
ver el resultado en pantalla.*/

#include <stdio.h>
#include <stdlib.h>

/*<------------------------------------------------------------------------------------------------------------->*/

/*3-Ahora vendria el codigo ya propiamente dicho, empieza a leerlo desdel main para enterarte paso por paso gil.*/

/*3.6- Esta funcion es para una vez terminada todo el programa ir haciendo frees recursivos
 * para borrar toda la lista uno a uno, funciona asi: pasa de un nodo a otro mientras guardas el nodo anterior
 * y lo borra simple sencillo.*/

void free_list(node *stack){
  node *tmp;
  while (stack != NULL) {
    tmp = stack;
    stack = stack->next;
    free(tmp);
  }
}

/*3.5- Esta esta funcion va antes que la anterior basicamente para ver que la lista tiene contenido
 *te printa toda la lista, va recorriendo, como funciona el recorrer una lista? pues con un bucle que mientras
 el nodo en el que estas no sea la direccion de memoria de 0x0 osea NULL se va repitiendo entonces voy printando el numero
 del nodo, lo cuiroso de esta funcion es que no  tenemos contador ni indice solo "actualizamos" la direccion de memoria
 del nodo en el que estamos por la direccion de memoria siguiente.
 Para la 3.6 anda*/

void print_list(node *stack){
  while (stack != NULL) {
    printf("node_num: %d\n", stack->numero);
    stack = stack->next;
  }
}

/*3.4- Esta funcion una vez vas creando nodos los vas uniendo en la lista pues el echo de unir nodos se hace en esta funcion
 * Vale como te dije antes ten cuidado con la direccion de memoria original por eso hago un node temporal y lo incializo
 * con que sea *stack, porque *stack? pues porque representa al primer nodo de la lista, entonces dentro del while
 * la condicion es un poco rara que significa? pues que vaya haciendo el while mientras la direccion de memoria siguiente 
 * no sea 0x0 osea NULL, una vez este en un nodo y el next de este nodo sea 0x0 osea NULL significa que es el final de la lista,
 * o deberia serlo siguiendo es guia pocha, pues como estamos en el ultimo nodo vamos a decirle que en vez de apuntar a 0x0
 * ahora apunte al nodo que queremos introducir.
 * sube al 3.5 .*/

void  add_node_to_list(node **stack, node *new_node){
  node *stack_tmp; 

  stack_tmp = *stack;
  while(stack_tmp->next != NULL)
    stack_tmp = stack_tmp->next;
  stack_tmp->next = new_node;
}

/*3.3- Esta es la funcion para crearte el nodo.
 * Como se crea un nodo modificado para una lista, si te fijas esta funcion no es ni una funcion int, ni void, ni char,
 * es una funcion tipo node puntero, no te asustes, ni digas "hay dios mio" poniendote la mano en la frente y mirando al suelo,
 * empezamos creando un puntero de node que es el que returnaremos al final de esta funcion, y justo despues reservamos memoria
 * allocando con malloc, ojo sizeof(node), node porque es una variable que va a contener direeciones de memoria de tipo node,
 * y siempre el if de proteccion por si falla algo, luego le metes el contenido dentro de la structura, si en vez de un int 
 * fuera un char* recuerda hacer malloc para la string*, en este caso no hace falta, y despues de meter el numero next apunta a
 * 0x0 que es la direccion de memoria de NULL, y returnamos el node que hemos creado.
 * Estas tardando en subir arriba al 3.4 .*/

node *create_node(int valor){
  node *node_tmp;

  node_tmp = malloc(sizeof(node));
  if(!node_tmp)
    return (NULL);
  node_tmp->numero = (valor + 1);
  node_tmp->next = NULL;
  return (node_tmp);
}

/*3.2- La funcion para crearte la lista: 
 * que hago creo otra structura porque cuando manejas listas tienes que tener mucho
 * cuidado con la primera direccion de memoria del nodo, porque como la pierdas cagamos, lo mas normal es ir pasando
 * "copias" de la direccion de memoria del primer nodo de la lista, cuando tu haces &variable le estas pasando
 * la direccion de memoria pero cuando lo pasas a palo seco sin & es como si fuera una copia que no tendria porque repercutir
 * en la lista original, pero hay maneras de que si la cambie, entonces lo de j ni caso es para que el bucle se repita las veces,
 * que le indiques fuera, dentro del bucle incializo la variable struct que creamos antes con un nuevo nodo, si es la primera
 * vez que entramos en esta funcion el primer elemento deberia estar en NULL por eso entra en el primer if, lo que ara que
 * stack que es: stack == NULL ahora pase a ser el mismo nodo que new_node y ya termina el bucle, en la siguiente vuelta
 * ya no entrara mas en el if y solo entrara en el else lo que ara que entremos en la funcion de add el node a la lista,
 * le pasas la lista/stack y el nuevo nodo que le vamos a introducir.
 * sube al punto 3.3 .
 * */
void  create_list(node **stack, char **valor){
  node *new_node;
  int i;
  int j;

  j = atoi(valor[1]);
  i = 0;
  while(i < j)
  {
    new_node = create_node(i);
    if(*stack == NULL)
      *stack = new_node;
    else
      add_node_to_list(stack, new_node);
    i++;
  }
}

/*3.1- Este es el main vale, si no lo conoces vuelvete a ver lo mas basico de la programacion, el primer if ni case
 esta porque no me fio del "usuario/tu", declaras/creas el "tipo" de variable que has creado con struct y lo inicializas
 en NULL porque luego con la funcion de crear nodo se rellanara de momento lo dejas en NULL, y luego sencillo vas pasando
 la direccion de memoria del primer nodo en este caso el stack, lo de que le paso argv ni caso es para meterle contenido.
 en create_list() le paso la direccion de memoria porque para editar las direcciones de memoria se vienen doble punteros.
 sube al punto 3.2 0(^.^)0  <-- cara feliz.
*/
int main(int argc, char **argv){
  node *stack;

  if(argc != 2)
  {
    printf("Ostias que no es muy dificil tia que es solo poner ./a.out y el numero de nodos de la lista\n");
    return (1);
  }
  stack = NULL;
  create_list(&stack, argv);
  print_list(stack);
  free_list(stack);
  return (0);
}
