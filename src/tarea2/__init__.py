# -*- coding: utf-8 -*-
"""
Menú principal 
"""

from __future__ import annotations

from rich.console import Console


from .interfaz import panel_contenido, leer_tecla, pausa
from .problemas.asignacion import ProblemaAsignacion
from .problemas.distribucion import ProblemaDistribucion

from .algoritmos import (
    busqueda_greedy,
    busqueda_exhaustiva,
    busqueda_branch_and_bound,
)

# Aquí luego importaremos:
# from tarea2.problemas.asignacion import ProblemaAsignacion
# from tarea2.problemas.distribucion import ProblemaDistribucion
# from tarea2.problemas.mochila import ProblemaMochila
# from tarea2.problemas.vendedor import ProblemaVendedor

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
            console.clear()
            break

        tecnica = seleccionar_tecnica()

    # Aquí, según op, instanciamos el problema correspondiente
    # (por ahora dejamos placeholders)
    if op == "1":
        console.print("[cyan]Ingrese tamaño N de la matriz:[/]")
        N = int(input("N = "))
        matriz = []
        console.print("[cyan]Ingrese la matriz fila por fila (separada por espacios):[/]")

        for i in range(N):
            fila = list(map(int, input(f"Fila {i+1}: ").split()))
            matriz.append(fila)

        problema = ProblemaAsignacion(matriz)
        # problema = ProblemaAsignacion(...)

    elif op == "2":
        console.print("[cyan]Ingrese número máximo de unidades asignables (N):[/]")
        N = int(input("N = "))

        console.print("[cyan]Ingrese número de elementos (M):[/]")
        M = int(input("M = "))

        tabla = []
        console.print("[cyan]Ingrese la tabla de ganancias de tamaño (N+1) x M:[/]")

        for i in range(N + 1):
            fila = list(map(int, input(f"Unidades {i}: ").split()))
            tabla.append(fila)

        R = int(input("Recurso total disponible R = "))

        problema = ProblemaDistribucion(tabla, R)
    elif op == "3":
        console.print("[yellow]TODO: Instanciar Problema de Mochila[/]")
    elif op == "4":
        console.print("[yellow]TODO: Instanciar Problema del Vendedor[/]")

        # En cuanto tengamos la instancia `problema`, haríamos algo como:
        # if tecnica == "greedy":
        #     sol, valor, t = busqueda_greedy(problema)
        # elif tecnica == "exhaustiva":
        #     sol, valor, t, evaluadas = busqueda_exhaustiva(problema)
        # elif tecnica == "branchbound":
        #     sol, valor, t, evaluadas = busqueda_branch_and_bound(problema)
        #
        # Y luego imprimiríamos resultados bonitos.

        pausa()


if __name__ == "__main__":
    main()
