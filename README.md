# ¿Cómo compilar y ejecutar?

Para ejecutar el codigo, primero debemos compilar:
   1. Asegúrate de tener gcc y git instalados.
   2. Coloca todos los archivos (`tarea1.c`, `list.c`, `list.h`) en la misma carpeta.
   3. Compila con:
````
gcc tarea1.c list.c -o tarea1.exe
````
Y ejecuta el programa:

```
./tarea1.exe
```
---
### Funcionalidades para la aplicación:

1. **Registrar ticket** (ID, descripción):
   - El usuario ingresa el ID y la descripción del problema.
   - La aplicación registra el ticket con la hora de registro actual y asigna automáticamente prioridad "Bajo". 

2. **Asignar prioridad a ticket** (ID, nivel de prioridad):
   - El usuario ingresa el ID del ticket y el nuevo nivel de prioridad ("Alto", "Medio", "Bajo"). Esto no es dependiente de mayusculas.
   - La aplicación actualiza la prioridad del ticket. Si el ID no existe, se muestra un aviso.

3. **Mostrar lista de tickets pendientes** ():
   - Muestra todos los tickets ordenados por prioridad (de "Alto" a "Bajo") y, dentro de la misma prioridad, por hora de registro (orden de llegada).

4. **Procesar siguiente ticket** ():
   - Selecciona el ticket con mayor prioridad (y más antiguo dentro de su nivel) para ser atendido.
   - Elimina el ticket de la lista y muestra sus datos (ID, descripción, prioridad y hora de registro).
   - Si no hay tickets pendientes, muestra un aviso.

5. **Buscar ticket por ID y mostrar detalles** (ID):
   - El usuario ingresa un ID, y la aplicación busca el ticket correspondiente en la lista.
   - Si existe, muestra todos sus datos (descripción, prioridad, hora de registro).
   - Si no existe, muestra un mensaje de error.

