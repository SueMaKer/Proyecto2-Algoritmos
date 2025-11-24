# -*- coding: utf-8 -*-
"""
Problema de Distribución de un Recurso
Compatible con Greedy, Exhaustiva y Branch & Bound
"""

from __future__ import annotations


class ProblemaDistribucion:
    def __init__(self, tabla, recurso_total):
        """
        tabla[i][j] = ganancia por asignar i unidades al elemento j
        i = unidades asignadas (0..N)
        j = elemento (0..M-1)

        recurso_total = cantidad total disponible para distribuir
        """
        self.tabla = tabla
        self.R = recurso_total
        self.N = len(tabla) - 1          # máximo recurso asignable por elemento
        self.M = len(tabla[0])           # número de elementos

  
    def solucion_inicial(self):
        return []  

    def completo(self, sol):
        return len(sol) == self.M

    def candidatos(self, sol):
        """Candidatos = cantidades posibles de recurso para el siguiente elemento."""
        usado = sum(sol)
        restantes = self.R - usado

      
        return list(range(0, min(self.N, restantes) + 1))

 
    def factible(self, sol, cand):
        return (sum(sol) + cand) <= self.R

 
    def agregar(self, sol, cand):
        return sol + [cand]

    def evaluar(self, sol):
        total = 0
        for j, unidades in enumerate(sol):
            total += self.tabla[unidades][j]
        return total


    def cota_superior(self, sol):
        """
        Suma:
        - ganancia real de lo asignado
        - + máximo posible para cada elemento faltante
        respetando el recurso restante
        """
        valor = self.evaluar(sol)

        usado = sum(sol)
        restantes = self.R - usado

        k = len(sol)

        # Para cada elemento restante, asumimos asignar la mejor cantidad posible
        for j in range(k, self.M):
            mejor = 0
            for i in range(0, min(self.N, restantes) + 1):
                mejor = max(mejor, self.tabla[i][j])
            valor += mejor

        return valor
