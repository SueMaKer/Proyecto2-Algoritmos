# -*- coding: utf-8 -*-
"""
Menú principal 
"""

from __future__ import annotations
from rich.console import Console
from typing import List
import math

from .interfaz import panel_contenido, leer_tecla, pausa
from .problemas.asignacion import ProblemaAsignacion
from .problemas.distribucion import ProblemaDistribucion
from .problemas.vendedor import ProblemaVendedor
from .problemas.mochila import ProblemaMochila

from .algoritmos import (
    busqueda_greedy,
    busqueda_exhaustiva,
    busqueda_branch_and_bound,
)

console = Console()


def render_menu_problema() -> None:
    cuerpo = (
        "\n"
        "       Proyecto 2 - Técnicas de Búsqueda\n\n"
        "[1] Problema de Asignación 1 a 1\n"
        "[2] Problema de Distribución de un recurso\n"
        "[3] Problema de la Mochila\n"
        "[4] Problema del Vendedor\n"
        "[5] Salir\n\n"
        "Digite una opción [_]"
    )
    panel_contenido(cuerpo)


def render_menu_tecnica() -> None:
    cuerpo = (
        "\n"
        "       Selección de técnica de búsqueda\n\n"
        "[1] Búsqueda Greedy\n"
        "[2] Búsqueda Exhaustiva Pura\n"
        "[3] Búsqueda con Ramificación y Acotamiento\n\n"
        "Digite una opción [_]"
    )
    panel_contenido(cuerpo)


def seleccionar_tecnica():
    while True:
        render_menu_tecnica()
        op = leer_tecla("123")
        console.print()
        match op:
            case "1":
                return "greedy"
            case "2":
                return "exhaustiva"
            case "3":
                return "branchbound"


def main() -> None:
    while True:
        render_menu_problema()
        op = leer_tecla("12345")
        console.print()

        if op == "5":
            console.print("[green]Saliendo del programa...[/]")
            console.clear()
            return 

        tecnica = seleccionar_tecnica()

        if op == "1":
            console.print("[cyan]Ingrese tamaño N de la matriz:[/]")
            N = int(input("N = "))
            matriz = []
            console.print("[cyan]Ingrese la matriz fila por fila:[/]")
            for i in range(N):
                fila = list(map(int, input(f"Fila {i+1}: ").split()))
                matriz.append(fila)
            problema = ProblemaAsignacion(matriz)

        elif op == "2":
            console.print("[cyan]Ingrese número máximo de unidades asignables (N):[/]")
            N = int(input("N = "))
            console.print("[cyan]Ingrese número de elementos (M):[/]")
            M = int(input("M = "))

            tabla = []
            console.print("[cyan]Ingrese la tabla (N+1) x M:[/]")
            for i in range(N + 1):
                fila = list(map(int, input(f"Unidades {i}: ").split()))
                tabla.append(fila)

            R = int(input("Recurso total disponible R = "))
            problema = ProblemaDistribucion(tabla, R)

        elif op == "3":
            console.print("[cyan]Ingrese número de elementos N:[/]")
            N = int(input("N = "))
            beneficios = []
            for i in range(N):
                beneficios.append(int(input(f"beneficio[{i}] = ")))
            C = int(input("Capacidad = "))
            problema = ProblemaMochila(beneficios, C)

        elif op == "4":
            console.print("[cyan]Ingrese número de ciudades N:[/]")
            N = int(input("N = "))

            dist = []
            console.print("[cyan]Ingrese la matriz de distancias N x N (use 99999 para 'no hay camino'):[/]")

            for i in range(N):
                while True:
                    fila_str = input(f"Fila {i+1}: ").strip().split()

                    if len(fila_str) != N:
                        console.print(f"[red]La fila debe contener exactamente {N} valores.[/]")
                        continue

                    try:
                        fila = [float(x) for x in fila_str]
                    except ValueError:
                        console.print("[red]Error: Debe ingresar números válidos.[/]")
                        continue

                    if any(x < 0 for x in fila if x != 99999):
                        console.print("[red]No se permiten distancias negativas.[/]")
                        continue

                    if fila[i] != 0:
                        console.print("[red]Error: dist[i][i] debe ser 0.[/]")
                        continue

                    fila = [math.inf if x == 99999 else x for x in fila]

                    sim = True
                    for j in range(i):
                        if dist[j][i] != fila[j]:
                            sim = False
                            break

                    if not sim:
                        console.print(
                            f"[red]La matriz debe ser simétrica: dist[{i+1}][{j+1}] != dist[{j+1}][{i+1}].[/]"
                        )
                        continue

                    dist.append(fila)
                    break

            problema = ProblemaVendedor(dist)

        console.print("[yellow]Ejecutando búsqueda...[/]")

        if tecnica == "greedy":
            sol, valor, t = busqueda_greedy(problema)
            console.print(f"[green]Solución greedy:[/] {sol}")
            console.print(f"Valor: {valor}")
            console.print(f"Tiempo: {t:.6f} s")

        elif tecnica == "exhaustiva":
            sol, valor, t, evaluadas = busqueda_exhaustiva(problema)
            console.print(f"[green]Mejor solución (exhaustiva):[/] {sol}")
            console.print(f"Valor: {valor}")
            console.print(f"Evaluadas: {evaluadas}")
            console.print(f"Tiempo: {t:.6f} s")

        elif tecnica == "branchbound":
            sol, valor, t, evaluadas = busqueda_branch_and_bound(problema)
            console.print(f"[green]Mejor solución (B&B):[/] {sol}")
            console.print(f"Valor: {valor}")
            console.print(f"Evaluadas: {evaluadas}")
            console.print(f"Tiempo: {t:.6f} s")

        pausa()


if __name__ == "__main__":
    main()
