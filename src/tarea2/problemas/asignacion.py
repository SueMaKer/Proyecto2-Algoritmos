# -*- coding: utf-8 -*-
"""
Problema de Asignación 1 a 1
Compatible con: Greedy, Exhaustiva, Branch & Bound
"""

from __future__ import annotations


class ProblemaAsignacion:
    def __init__(self, matriz):
        """
        matriz[i][j] = ganancia si se asigna i -> j
        i = trabajador, j = tarea
        """
        self.matriz = matriz
        self.n = len(matriz)

    # -----------------------
    # Solución inicial
    # -----------------------
    def solucion_inicial(self):
        return []  # lista vacía de asignaciones

    # -----------------------
    # ¿Solución completa?
    # -----------------------
    def completo(self, sol):
        return len(sol) == self.n

    # -----------------------
    # Candidatos
    # -----------------------
    def candidatos(self, sol):
        """
        candidatos = tareas no asignadas aún
        """
        usados = set(sol)
        return [j for j in range(self.n) if j not in usados]

    # -----------------------
    # Factible
    # -----------------------
    def factible(self, sol, candidato):
        return candidato not in sol

    # -----------------------
    # Agregar candidato
    # sol es una lista donde sol[i] = tarea asignada al trabajador i
    # -----------------------
    def agregar(self, sol, candidato):
        return sol + [candidato]

    # -----------------------
    # Evaluación de solución
    # -----------------------
    def evaluar(self, sol):
        total = 0
        for i, j in enumerate(sol):
            total += self.matriz[i][j]
        return total

    # -----------------------
    # Cota superior (Branch & Bound)
    # -----------------------
    def cota_superior(self, sol):
        """
        Cálculo simple:
        - suma real de lo asignado
        - + máximo valor posible para cada trabajador pendiente
        """
        suma = self.evaluar(sol)
        k = len(sol)

        for trabajador in range(k, self.n):
            max_para_trabajador = max(self.matriz[trabajador])
            suma += max_para_trabajador

        return suma
