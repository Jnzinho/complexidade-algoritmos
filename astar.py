# Trabalho: Algoritmo A*
# Objetivo
# Implementar o algoritmo A* para resolver um problema de pathfinding em um ambiente 2D
# com obstáculos, utilizando uma heurística específica.

# Problema Customizado: Navegação Robótica

# Descrição do Problema: Um robô deve navegar de um ponto inicial (A) até um ponto
# destino (B) em um ambiente 2D retangular. O ambiente contém obstáculos retangulares que
# o robô não pode atravessar. O robô pode se mover em 8 direções (incluindo diagonais) e cada
# movimento tem um custo específico.

from warnings import warn
import heapq

class Node:
    def __init__(self, parent=None, position=None):
        self.parent = parent
        self.position = position

        self.g = 0
        self.h = 0
        self.f = 0

    def __eq__(self, other):
        return self.position == other.position
    
    def __repr__(self):
      return f"{self.position} - g: {self.g} h: {self.h} f: {self.f}"

    # para fins de heap queue
    def __lt__(self, other):
      return self.f < other.f
    
    # para fins de heap queue
    def __gt__(self, other):
      return self.f > other.f

def return_path(current_node):
    path = []
    current = current_node
    while current is not None:
        path.append(current.position)
        current = current.parent
    return path[::-1]  # inverter o caminho para o começo


def astar(maze, start, end, allow_diagonal_movement = True):
    """
    Retorna uma lista de tuplas como um caminho do ponto inicial até o ponto final no labirinto
    :param maze:
    :param start:
    :param end:
    """

    # Criar o nó inicial e o nó final
    start_node = Node(None, start)
    start_node.g = start_node.h = start_node.f = 0
    end_node = Node(None, end)
    end_node.g = end_node.h = end_node.f = 0

    open_list = [] # todos os nós que ele pode visitar em seguida
    closed_list = [] # todos os nós que ele já visitou, ou obstáculos

    # Transformar a lista em um heap
    heapq.heapify(open_list) 
    heapq.heappush(open_list, start_node)

    # Adicionar uma condição de parada
    outer_iterations = 0
    max_iterations = (len(maze[0]) * len(maze) // 2)

    # quais quadrados ele pode visitar em seguida
    adjacent_squares = ((0, -1), (0, 1), (-1, 0), (1, 0),)
    if allow_diagonal_movement:
        adjacent_squares = ((0, -1), (0, 1), (-1, 0), (1, 0), (-1, -1), (-1, 1), (1, -1), (1, 1),)

    # Loop até encontrar o destino
    while len(open_list) > 0:
        outer_iterations += 1

        if outer_iterations > max_iterations:
          # se chegarmos aqui, significa que o algoritmo está travado
          warn("Não foi possível encontrar um caminho até o destino, muitas iterações")
          return return_path(current_node)       
        
        # Pegar o nó atual
        current_node = heapq.heappop(open_list)
        closed_list.append(current_node)

        # Encontrou o destino
        if current_node == end_node:
            return return_path(current_node)

        # Gerar os filhos
        children = []
        
        for new_position in adjacent_squares: # Quadrados adjacentes

            # Pegar a posição do nó
            node_position = (current_node.position[0] + new_position[0], current_node.position[1] + new_position[1])

            # Verificar se a posição está dentro do labirinto
            if node_position[0] > (len(maze) - 1) or node_position[0] < 0 or node_position[1] > (len(maze[len(maze)-1]) -1) or node_position[1] < 0:
                continue

            # Verificar se o terreno é passável
            if maze[node_position[0]][node_position[1]] != 0:
                continue

            # Criar um novo nó
            new_node = Node(current_node, node_position)

            # Adicionar o novo nó aos filhos
            children.append(new_node)

        # Loop pelos filhos
        for child in children:
            # Verificar se o filho está na lista de visitados
            if len([closed_child for closed_child in closed_list if closed_child == child]) > 0:
                continue

            # Criar os valores de f, g e h
            child.g = current_node.g + 1
            child.h = ((child.position[0] - end_node.position[0]) ** 2) + ((child.position[1] - end_node.position[1]) ** 2)
            child.f = child.g + child.h

            # Verificar se o filho já está na open_list
            if len([open_node for open_node in open_list if child.position == open_node.position and child.g > open_node.g]) > 0:
                continue

            # Adicionar o filho à open_list
            heapq.heappush(open_list, child)

    warn("Não foi possível encontrar um caminho até o destino")
    return None

def example(print_maze = True):

    maze = [[0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,] * 2,
            [0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,] * 2,
            [0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,] * 2,
            [0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,] * 2,
            [0,0,0,1,1,0,0,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,] * 2,
            [0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,] * 2,
            [0,0,0,1,0,1,1,1,1,0,1,1,0,0,1,1,1,0,0,0,1,1,1,1,1,1,1,0,0,0,] * 2,
            [0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,1,1,0,1,0,0,0,0,0,0,1,1,1,0,] * 2,
            [0,0,0,1,0,1,1,0,1,1,0,1,1,1,0,0,0,0,0,1,0,0,1,1,1,1,1,0,0,0,] * 2,
            [0,0,0,1,0,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,1,0,1,0,1,1,] * 2,
            [0,0,0,1,0,1,0,1,1,0,1,1,1,1,0,0,1,1,1,1,1,1,1,0,1,0,1,0,0,0,] * 2,
            [0,0,0,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,1,1,0,] * 2,
            [0,0,0,1,0,1,1,1,1,0,1,0,0,1,1,1,0,1,1,1,1,0,1,1,1,0,1,0,0,0,] * 2,
            [0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1,1,] * 2,
            [0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,] * 2,
            [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,] * 2,]
    
    start = (0, 0)
    end = (len(maze)-1, len(maze[0])-1)

    path = astar(maze, start, end)

    if print_maze:
      for step in path:
        maze[step[0]][step[1]] = 2
      
      for row in maze:
        line = []
        for col in row:
          if col == 1:
            line.append("\u2588")
          elif col == 0:
            line.append(" ")
          elif col == 2:
            line.append(".")
        print("".join(line))

    print(path)

if __name__ == "__main__":
    example(print_maze=True)