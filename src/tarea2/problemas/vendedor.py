# -*- coding: utf-8 -*-
"""
Problema del Vendedor
"""

from __future__ import annotations
from typing import List
import math

class ProblemaVendedor:

    def __init__(self, distancias: List[List[float]]):
        self.dist = distancias
        self.N = len(distancias)

    def solucion_inicial(self):
        return [0]

    def completo(self, sol):
        return len(sol) == self.N

    def candidatos(self, sol):
        return [c for c in range(self.N) if c not in sol]

    def factible(self, sol, c):
        return True

    def agregar(self, sol, c):
        return sol + [c]

    def evaluar(self, sol):
        if len(sol) != self.N:
            return float("-inf") 
        costo = 0
        for i in range(self.N - 1):
            costo += self.dist[sol[i]][sol[i+1]]

        costo += self.dist[sol[-1]][sol[0]]
        return -costo 

    def cota_superior(self, sol):
        if len(sol) == 1:
            return 0  

        costo = 0
        for i in range(len(sol) - 1):
            costo += self.dist[sol[i]][sol[i+1]]

        restante = [c for c in range(self.N) if c not in sol]

        if not restante:
            costo += self.dist[sol[-1]][sol[0]]
            return -costo

        min_edge = math.inf
        for i in range(self.N):
            for j in range(self.N):
                if i != j:
                    min_edge = min(min_edge, self.dist[i][j])

        costo += min_edge * (len(restante) + 1)

        return -costo
