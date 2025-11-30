# -*- coding: utf-8 -*-
"""
Implementaciones genéricas de técnicas de búsqueda:
- Greedy
- Exhaustiva Pura
- Ramificación y Acotamiento
"""

from __future__ import annotations
import time
from typing import Any, Protocol


class ProblemaBusqueda(Protocol):
    """Interfaz que deben implementar todos los problemas."""

    def solucion_inicial(self) -> Any: ...
    def completo(self, solucion: Any) -> bool: ...
    def candidatos(self, solucion: Any) -> list[Any]: ...
    def factible(self, solucion: Any, candidato: Any) -> bool: ...
    def agregar(self, solucion: Any, candidato: Any) -> Any: ...
    def evaluar(self, solucion: Any) -> float: ...
    def cota_superior(self, solucion: Any) -> float: ...


def busqueda_greedy(problema: ProblemaBusqueda):
    """Estrategia voraz (greedy). Retorna (solucion, valor, tiempo)."""
    inicio = time.perf_counter()

    sol = problema.solucion_inicial()

    while not problema.completo(sol):
        cands = [c for c in problema.candidatos(sol) if problema.factible(sol, c)]

        if not cands:
            break  #No hay forma de continuar

        mejor = max(cands, key=lambda c: problema.evaluar(problema.agregar(sol, c)))
        sol = problema.agregar(sol, mejor)

    valor = problema.evaluar(sol)
    tiempo = time.perf_counter() - inicio
    return sol, valor, tiempo


def busqueda_exhaustiva(problema: ProblemaBusqueda):
    """Exhaustiva pura por backtracking. Retorna (mejor_sol, mejor_valor, tiempo, evaluadas)."""
    inicio = time.perf_counter()
    mejor_valor = float("-inf")
    mejor_sol = None
    evaluadas = 0

    def backtrack(sol):
        nonlocal mejor_valor, mejor_sol, evaluadas
        if problema.completo(sol):
            evaluadas += 1
            valor = problema.evaluar(sol)
            if valor > mejor_valor:
                mejor_valor = valor
                mejor_sol = sol.copy()
            return

        for c in problema.candidatos(sol):
            if problema.factible(sol, c):  # solo soluciones factibles
                sol.append(c)
                backtrack(sol)
                sol.pop()

    backtrack([])
    tiempo = time.perf_counter() - inicio
    return mejor_sol, mejor_valor, tiempo, evaluadas


def busqueda_branch_and_bound(problema: ProblemaBusqueda):
    """Exhaustiva con Ramificación y Acotamiento. Retorna (mejor_sol, mejor_valor, tiempo, evaluadas)."""
    inicio = time.perf_counter()
    mejor_valor = float("-inf")
    mejor_sol = None
    evaluadas = 0

    def backtrack(sol):
        nonlocal mejor_valor, mejor_sol, evaluadas

        if problema.cota_superior(sol) < mejor_valor:
            return

        if problema.completo(sol):
            evaluadas += 1
            valor = problema.evaluar(sol)
            if valor > mejor_valor:
                mejor_valor = valor
                mejor_sol = sol.copy()
            return

        for c in problema.candidatos(sol):
            if problema.factible(sol, c):
                sol.append(c)
                backtrack(sol)
                sol.pop()

    backtrack([])
    tiempo = time.perf_counter() - inicio
    return mejor_sol, mejor_valor, tiempo, evaluadas
