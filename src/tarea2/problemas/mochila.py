# -*- coding: utf-8 -*-
class ProblemaMochila:
    def __init__(self, beneficios, capacidad):
        self.beneficios = beneficios
        self.N = len(beneficios)
        self.capacidad = capacidad 

    def solucion_inicial(self):
        return []   

    def completo(self, sol):
        return len(sol) == self.capacidad or len(sol) == self.N

    def candidatos(self, sol):
        return [i for i in range(self.N) if i not in sol]

    def factible(self, sol, c):
        return len(sol) + 1 <= self.capacidad

    def agregar(self, sol, c):
        return sol + [c]

    def evaluar(self, sol):
        return sum(self.beneficios[i] for i in sol)

    def cota_superior(self, sol):
        restantes = [i for i in range(self.N) if i not in sol]
        restantes_ben = sorted(
            (self.beneficios[i] for i in restantes),
            reverse=True
        )

        capacidad_restante = self.capacidad - len(sol)

        mejor_suma = sum(restantes_ben[:capacidad_restante])

        return self.evaluar(sol) + mejor_suma
