#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "list.h"

typedef struct {
  char id[20];
  char description[100];
  char priority[10];
  time_t timestamp;
} Ticket;

typedef struct {
  List *high;
  List *medium;
  List *low;
} ticket_system;

void waitForKeyPress() {
  printf("Presione Enter para continuar...");
  while (getchar() != '\n');
}

void clearScreen() {
  printf("\033[H\033[J");
}

void showMainMenu() {
  clearScreen();
  puts("========================================");
  puts("    Sistema de Gestión de Tickets");
  puts("========================================");

  puts("1) Registrar ticket");
  puts("2) Asignar prioridad a ticket");
  puts("3) Mostrar lista de tickets");
  puts("4) Procesar siguiente ticket");
  puts("5) Buscar ticket por ID y mostrar detalles");
  puts("6) Salir");
}

void toLowerCase(char *str) {
  for (int i = 0; str[i]; i++) {
    str[i] = tolower(str[i]);
  }
}

void register_ticket(ticket_system *system) {
  Ticket *new_ticket = malloc(sizeof(Ticket));

  printf("Ingrese ID del ticket: ");
  scanf("%s", new_ticket->id);
  getchar();

  printf("Ingrese descripción: ");
  fgets(new_ticket->description, 100, stdin);

  new_ticket->description[strcspn(new_ticket->description, "\n")] = '\0';

  strcpy(new_ticket->priority, "Bajo");
  new_ticket->timestamp = time(NULL);
  list_pushBack(system->low, new_ticket);

  printf("Ticket registrado con prioridad 'Bajo'.\n");
}

void assign_priority(ticket_system *system) {
  char id[20], inputPriority[20];

  printf("Ingrese ID del ticket: ");
  scanf("%s", id);
  getchar();
  printf("Ingrese nueva prioridad (Alto, Medio, Bajo): ");

  scanf("%s", inputPriority);
  getchar(); 

  // Permitir ingresar alto, medio o bajo como 1, 2 o 3
  if (strcmp(inputPriority, "1") == 0) strcpy(inputPriority, "alto");
  else if (strcmp(inputPriority, "2") == 0) strcpy(inputPriority, "medio");
  else if (strcmp(inputPriority, "3") == 0) strcpy(inputPriority, "bajo");
  else toLowerCase(inputPriority); // Convertir a minúsculas en todo otro caso
  
  // Convertir a formato correcto "Alto", "Medio", "Bajo" para simplificar frontend
  char newPriority[10];
  if (strcmp(inputPriority, "alto") == 0) strcpy(newPriority, "Alto");
  else if (strcmp(inputPriority, "medio") == 0) strcpy(newPriority, "Medio");
  else if (strcmp(inputPriority, "bajo") == 0) strcpy(newPriority, "Bajo");
  else {
    printf("Prioridad no válida.\n");
    return;
  }

  List *lists[] = {system->high, system->medium, system->low};
  for (int i = 0; i < 3; i++) {
    for (Ticket *t = list_first(lists[i]); t != NULL; t = list_next(lists[i])) {
      if (strcmp(t->id, id) == 0) {
        list_popCurrent(lists[i]);
        strcpy(t->priority, newPriority);

        if (strcmp(newPriority, "Alto") == 0) list_pushBack(system->high, t);
        else if (strcmp(newPriority, "Medio") == 0) list_pushBack(system->medium, t);
        else list_pushBack(system->low, t);

        printf("Prioridad actualizada exitosamente a '%s'.\n", newPriority);
        return;
      }
    }
  }
  printf("Ticket no encontrado.\n");
}

void show_list(List *list) {
  for (Ticket *t = list_first(list); t != NULL; t = list_next(list)) {
    printf("ID: %s | Descripción: %s | Prioridad: %s | Hora: %s",
           t->id, t->description, t->priority, ctime(&(t->timestamp)));
  }
}

void show_ticket_list(ticket_system *system) {
  puts("\n--- Tickets Prioridad Alta ---");
  show_list(system->high);
  puts("\n--- Tickets Prioridad Media ---");
  show_list(system->medium);
  puts("\n--- Tickets Prioridad Baja ---");
  show_list(system->low);
}

void process_next_from_list(List *list) {
  Ticket *t = list_first(list);
  if (t == NULL) return;

  printf("Procesando ticket:\nID: %s\nDescripción: %s\nPrioridad: %s\nHora: %s",
         t->id, t->description, t->priority, ctime(&(t->timestamp)));
  list_popCurrent(list);
}

void process_next_ticket(ticket_system *system) {
  if (list_size(system->high) > 0) {
    process_next_from_list(system->high);
  } else if (list_size(system->medium) > 0) {
    process_next_from_list(system->medium);
  } else if (list_size(system->low) > 0) {
    process_next_from_list(system->low);
  } else {
    printf("No hay tickets pendientes.\n");
  }
}

void search_ticket_by_id(ticket_system *system) {
  char id[20];
  printf("Ingrese ID del ticket: ");
  scanf("%s", id);
  getchar(); 

  List *lists[] = {system->high, system->medium, system->low};
  for (int i = 0; i < 3; i++) {
    for (Ticket *t = list_first(lists[i]); t != NULL; t = list_next(lists[i])) {
      if (strcmp(t->id, id) == 0) {
        printf("ID: %s\nDescripción: %s\nPrioridad: %s\nHora: %s",
               t->id, t->description, t->priority, ctime(&(t->timestamp)));
        return;
      }
    }
  }
  printf("Ticket no encontrado.\n");
}


int main() {
  char option;
  ticket_system system;
  system.high = list_create();
  system.medium = list_create();
  system.low = list_create();


  do {
    showMainMenu();
    printf("Ingrese una opción: ");
    scanf(" %c", &option);
    getchar(); 

    switch (option) {
    case '1':
      register_ticket(&system);
      break;
    case '2':
      assign_priority(&system);
      break;
    case '3':
      show_ticket_list(&system);
      break;
    case '4':
      process_next_ticket(&system);
      break;
    case '5':
      search_ticket_by_id(&system);
      break;
    case '6':
      puts("Saliendo del sistema de gestión de tickets...");
      break;
    default:
      puts("Opción inválida. Intente nuevamente.");
    }
    
    waitForKeyPress(); 

  } while (option != '6');

  list_clean(system.high);
  list_clean(system.medium);
  list_clean(system.low);
  return 0;
}
