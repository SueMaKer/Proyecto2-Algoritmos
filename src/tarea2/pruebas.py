# -*- coding: utf-8 -*-
"""
Script definitivo de experimentos para el Proyecto 2.
Genera resultados para:
- Problema de Asignación
- Problema de Distribución
- Problema de Mochila
- Problema del Vendedor

Usa SOLO tamaños seguros para garantizar que
Greedy, Exhaustiva y Branch&Bound terminen.
"""

from tarea2.algoritmos import (
    busqueda_greedy,
    busqueda_exhaustiva,
    busqueda_branch_and_bound,
)

from tarea2.problemas.asignacion import ProblemaAsignacion
from tarea2.problemas.distribucion import ProblemaDistribucion
from tarea2.problemas.mochila import ProblemaMochila
from tarea2.problemas.vendedor import ProblemaVendedor

import random
import time
import math


# ===============================================================
# Utilidades
# ===============================================================

def medir(func, *args):
    """Mide tiempo y ejecuta función"""
    inicio = time.perf_counter()
    res = func(*args)
    fin = time.perf_counter()
    return res, (fin - inicio)


def print_header(titulo):
    print("\n" + "-"*55)
    print(f"----- {titulo} -----")
    print("-"*55)


def print_resultado(nombre, sol, valor, tiempo, extra=None):
    print(f"   Técnica: {nombre}")
    print(f"   ✔ Solución: {sol}")
    print(f"   Valor obtenido: {valor}")
    print(f"   Tiempo: {tiempo:.6f} s")
    if extra is not None:
        print(f"   Extra: {extra}")
    print()


# ===============================================================
# EXPERIMENTOS — Problema de Asignación
# ===============================================================

def correr_asignacion(N):
    matriz = [[random.randint(1, 10) for _ in range(N)] for _ in range(N)]
    problema = ProblemaAsignacion(matriz)

    print(f"\n>>> Asignación — Tamaño: {N}")

    # Greedy
    (sol, valor, t), tiempo = medir(busqueda_greedy, problema)
    print_resultado("Greedy", sol, valor, tiempo)

    # Exhaustiva
    (sol, valor, t_exh, evaluadas), tiempo = medir(busqueda_exhaustiva, problema)
    print_resultado("Exhaustiva", sol, valor, tiempo, extra=f"Evaluadas: {evaluadas}")

    # B&B
    (sol, valor, t_bb, evaluadas), tiempo = medir(busqueda_branch_and_bound, problema)
    print_resultado("Branch & Bound", sol, valor, tiempo, extra=f"Evaluadas: {evaluadas}")


# ===============================================================
# EXPERIMENTOS — Problema de Distribución
# ===============================================================

def correr_distribucion(N, M):
    tabla = [[random.randint(0, 20) for _ in range(M)] for _ in range(N+1)]
    R = random.randint(N//2, N)

    problema = ProblemaDistribucion(tabla, R)

    print(f"\n>>> Distribución — Tamaño: N={N}, M={M}")

    # Greedy
    (sol, valor, t), tiempo = medir(busqueda_greedy, problema)
    print_resultado("Greedy", sol, valor, tiempo)

    # Exhaustiva
    (sol, valor, t_exh, evaluadas), tiempo = medir(busqueda_exhaustiva, problema)
    print_resultado("Exhaustiva", sol, valor, tiempo, extra=f"Evaluadas: {evaluadas}")

    # B&B
    (sol, valor, t_bb, evaluadas), tiempo = medir(busqueda_branch_and_bound, problema)
    print_resultado("Branch & Bound", sol, valor, tiempo, extra=f"Evaluadas: {evaluadas}")


# ===============================================================
# EXPERIMENTOS — Problema de Mochila
# ===============================================================

def correr_mochila(N):
    beneficios = [random.randint(5, 20) for _ in range(N)]
    capacidad = N // 2

    problema = ProblemaMochila(beneficios, capacidad)

    print(f"\n>>> Mochila — Tamaño: {N}")

    # Greedy
    (sol, valor, t), tiempo = medir(busqueda_greedy, problema)
    print_resultado("Greedy", sol, valor, tiempo)

    # Exhaustiva
    (sol, valor, t_exh, evaluadas), tiempo = medir(busqueda_exhaustiva, problema)
    print_resultado("Exhaustiva", sol, valor, tiempo, extra=f"Evaluadas: {evaluadas}")

    # B&B
    (sol, valor, t_bb, evaluadas), tiempo = medir(busqueda_branch_and_bound, problema)
    print_resultado("Branch & Bound", sol, valor, tiempo, extra=f"Evaluadas: {evaluadas}")


# ===============================================================
# EXPERIMENTOS — Problema del Vendedor (TSP)
# ===============================================================

def correr_vendedor(N):
    dist = [[0 if i == j else random.randint(5, 30) for j in range(N)] for i in range(N)]
    problema = ProblemaVendedor(dist)

    print(f"\n>>> Vendedor — Tamaño: {N}")

    # Greedy
    (sol, valor, t), tiempo = medir(busqueda_greedy, problema)
    print_resultado("Greedy", sol, valor, tiempo)

    # Exhaustiva
    (sol, valor, t_exh, evaluadas), tiempo = medir(busqueda_exhaustiva, problema)
    print_resultado("Exhaustiva", sol, valor, tiempo, extra=f"Evaluadas: {evaluadas}")

    # B&B
    (sol, valor, t_bb, evaluadas), tiempo = medir(busqueda_branch_and_bound, problema)
    print_resultado("Branch & Bound", sol, valor, tiempo, extra=f"Evaluadas: {evaluadas}")


# ===============================================================
# MAIN — tamaños seguros
# ===============================================================

def main():
    print("\n==================== INICIANDO EXPERIMENTOS ====================\n")

    print_header("PROBLEMA DE ASIGNACIÓN")
    for N in [3, 5, 7]:
        correr_asignacion(N)

    print_header("PROBLEMA DE DISTRIBUCIÓN")
    correr_distribucion(4, 3)
    correr_distribucion(6, 4)
    correr_distribucion(8, 6)

    print_header("PROBLEMA DE MOCHILA")
    correr_mochila(6)
    correr_mochila(10)
    correr_mochila(12)

    print_header("PROBLEMA DEL VENDEDOR")
    correr_vendedor(4)
    correr_vendedor(6)
    correr_vendedor(7)

    print("\n==================== EXPERIMENTOS FINALIZADOS ====================\n")


if __name__ == "__main__":
    main()
