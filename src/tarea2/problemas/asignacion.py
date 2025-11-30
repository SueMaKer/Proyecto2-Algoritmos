# -*- coding: utf-8 -*-
"""
Problema de Asignación 1 a 1
Compatible con la interfaz ProblemaBusqueda
"""

class ProblemaAsignacion:

    def __init__(self, matriz):
        self.matriz = matriz
        self.N = len(matriz)
    #  Métodos requeridos por la interfaz
    def solucion_inicial(self):
        return []

    def completo(self, solucion):
        return len(solucion) == self.N

    def candidatos(self, solucion):
        usados = set(solucion)
        return [j for j in range(self.N) if j not in usados]

    def factible(self, solucion, candidato):
        return candidato not in solucion

    def agregar(self, solucion, candidato):
        return solucion + [candidato]

    def evaluar(self, solucion):
        total = 0
        for i, j in enumerate(solucion):
            total += self.matriz[i][j]
        return total

    def cota_superior(self, solucion):
        usados = set(solucion)
        valor = self.evaluar(solucion)

        fila_actual = len(solucion)

        for i in range(fila_actual, self.N):
            mejores_no_usados = [
                self.matriz[i][j]
                for j in range(self.N)
                if j not in usados
            ]
            valor += max(mejores_no_usados)

        return valor
