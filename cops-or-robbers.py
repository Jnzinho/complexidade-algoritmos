# -*- coding: utf-8 -*-
'''
Escreva a sua solução aqui
Code your solution here
Escriba su solución aquí
'''

from collections import deque

def can_reach_end(maze):
    # Se a posição inicial ou final estão bloqueadas, não há caminho
    if maze[0][0] == 1 or maze[4][4] == 1:
        return False
    
    # BFS
    queue = deque([(0, 0)])
    visited = [[False] * 5 for _ in range(5)]
    visited[0][0] = True
    
    # Movimentos possíveis: cima, baixo, esquerda, direita
    directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]
    
    while queue:
        row, col = queue.popleft()
        
        if row == 4 and col == 4:
            return True
        
        for dr, dc in directions:
            new_row, new_col = row + dr, col + dc
            
            if 0 <= new_row < 5 and 0 <= new_col < 5:
                if not visited[new_row][new_col] and maze[new_row][new_col] == 0:
                    visited[new_row][new_col] = True
                    queue.append((new_row, new_col))
    
    return False

# Ler número de casos de teste
t = int(input())

for _ in range(t):
    numbers = []
    while len(numbers) < 25:
        line = input().split()
        numbers.extend([int(x) for x in line])
    
    # Converter para matriz 5x5
    maze = []
    for i in range(5):
        row = numbers[i*5:(i+1)*5]
        maze.append(row)
    
    if can_reach_end(maze):
        print("COPS")
    else:
        print("ROBBERS")