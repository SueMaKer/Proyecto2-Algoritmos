# Tarea programada 2, Segundo Semestre 2025 
### CI-0116 Análisis de Algoritmos y Estructuras de Datos

## Estudiantes:
- **Paula Sofía Grell – C22977**  
- **Melissa Garita – C23186**

---

# Descripción general

Este proyecto implementa tres técnicas fundamentales de búsqueda para resolver problemas de optimización combinatoria:

- **Búsqueda Greedy (Voraz)**
- **Búsqueda Exhaustiva Pura (Backtracking total)**
- **Ramificación y Acotamiento (Branch and Bound)**

Se aplican a **cuatro tipos clásicos de problemas**:

1. Problema de **Asignación 1 a 1**  
2. Problema de **Distribución de un recurso**  
3. Problema de **la Mochila (Knapsack)**  
4. Problema del **Vendedor viajero (TSP)**  

El proyecto incluye un **menú interactivo en consola**, con interface visual basada en `rich`, que permite al usuario:
- seleccionar el problema
- elegir la técnica de búsqueda
- ingresar los datos
- visualizar la solución, tiempo de ejecución y estadísticas

---

# Técnicas de búsqueda implementadas

| Técnica | Descripción |
|--------|-------------|
| **Greedy** | Construye una solución seleccionando en cada paso el mejor candidato local según una heurística. |
| **Exhaustiva** | Genera todas las soluciones posibles mediante backtracking. Siempre encuentra la solución óptima. |
| **Branch and Bound (B&B)** | Variante optimizada que calcula cotas superiores para descartar ramas completas del árbol de búsqueda. |

Cada técnica retorna:
- **solución encontrada**
- **valor** asociado
- **tiempo** de ejecución
- **cantidad de soluciones evaluadas** (solo exhaustiva y B&B)

---

# Problemas implementados

## 1️-Problema de Asignación 1 a 1
Se recibe una matriz **N × N** donde cada entrada `[i][j]` indica la ganancia por asignar *i → j*.  
El objetivo es **maximizar** la ganancia total.

## 2️-Problema de Distribución de un Recurso
Se recibe una tabla **(N+1) × M**, donde `[i][j]` indica la ganancia al asignar *i* unidades del recurso al elemento *j*.  
El recurso total disponible es **R**.  
El objetivo es distribuir R para **maximizar la ganancia**.

## 3️-Problema de la Mochila
Cada elemento tiene un **beneficio**.  
El costo de incluir cualquier elemento es **1 unidad**, y la mochila tiene una capacidad **C**.  
El objetivo es **maximizar los beneficios** sin exceder la capacidad.

## 4️-Problema del Vendedor (TSP)
Se recibe una matriz **N × N** de distancias simétricas.  
El objetivo es encontrar un ciclo que visite todas las ciudades minimizando la distancia.  
La evaluación se devuelve como **negativo del costo total**, para utilizar las técnicas de maximización.

Incluye validaciones:
- `dist[i][i] = 0`
- Matriz simétrica
- `99999` se interpreta como ausencia de camino

---

# Ejecución
### 1. Instalar dependencias
```bash
uv sync
## uv run tarea2
