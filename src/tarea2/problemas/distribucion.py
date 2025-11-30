# -*- coding: utf-8 -*-
"""
Problema de Distribución de un Recurso
Compatible con la interfaz ProblemaBusqueda
"""

class ProblemaDistribucion:

    def __init__(self, tabla, R):
        """
        tabla[i][j]  = ganancia asignando i unidades al elemento j
        R            = recurso total disponible
        """
        self.tabla = tabla
        self.R = R
        self.N = len(tabla) - 1  # i = 0..N unidades posibles
        self.M = len(tabla[0])   # j = elementos a los que asignar

    def solucion_inicial(self):
        """Solución = lista de asignaciones por elemento."""
        return []

    def completo(self, sol):
        """Se completó cuando ya asignamos todos los M elementos."""
        return len(sol) == self.M

    def recursos_usados(self, sol):
        """Retorna cuántas unidades del recurso ya se usaron."""
        return sum(sol)

    def candidatos(self, sol):
        """Posibles asignaciones para el siguiente elemento."""
        usados = self.recursos_usados(sol)
        restantes = self.R - usados

        # Se puede asignar entre 0 y restantes unidades
        max_asignable = min(self.N, restantes)
        return list(range(0, max_asignable + 1))

    def factible(self, sol, candidato):
        """Factible si no excede el recurso total."""
        return self.recursos_usados(sol) + candidato <= self.R

    def agregar(self, sol, candidato):
        """Devuelve una nueva lista agregando unidades para el siguiente elemento."""
        return sol + [candidato]

    def evaluar(self, sol):
        """Suma de ganancias parciales."""
        total = 0
        for j, unidades in enumerate(sol):
            total += self.tabla[unidades][j]
        return total

    def cota_superior(self, sol):
        """
        Cota optimista:
        - Ganancia actual
        - + mejor ganancia posible para los elementos restantes,
          suponiendo que se pueden asignar unidades de manera ideal.
        """

        valor = self.evaluar(sol)
        usados = self.recursos_usados(sol)
        restantes = self.M - len(sol)
        recurso_restante = self.R - usados

        # Estimar optimista:
        # Para cada elemento faltante, elegir la mejor ganancia posible
        # respetando NO exceder todo el recurso restante.

        for j in range(len(sol), self.M):
            mejor = 0
            for unidades in range(min(self.N, recurso_restante) + 1):
                mejor = max(mejor, self.tabla[unidades][j])
            valor += mejor

        return valor
