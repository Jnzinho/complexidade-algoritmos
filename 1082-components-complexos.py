# -*- coding: utf-8 -*-
'''
Escreva a sua solução aqui
Code your solution here
Escriba su solución aquí
'''

def dfs(node, graph, visited, component):
    visited[node] = True
    component.append(node)
    
    if node in graph:
        for neighbor in graph[node]:
            if not visited[neighbor]:
                dfs(neighbor, graph, visited, component)

def find_connected_components(vertices, edges):
    # Criar o grafo como lista de adjacências
    graph = {}
    
    # Adicionar todas as arestas ao grafo
    for u, v in edges:
        if u not in graph:
            graph[u] = []
        if v not in graph:
            graph[v] = []
        graph[u].append(v)
        graph[v].append(u)
    
    # Dicionário para marcar vértices visitados
    visited = {v: False for v in vertices}
    
    # Lista para armazenar os componentes conexos
    components = []
    
    # Para cada vértice, se não foi visitado, fazer DFS
    for vertex in sorted(vertices):
        if not visited[vertex]:
            component = []
            dfs(vertex, graph, visited, component)
            component.sort()
            components.append(component)
    
    return components

# Ler número de casos de teste
n = int(input())

for case in range(1, n + 1):
    # Ler número de vértices e arestas
    v, e = map(int, input().split())
    
    # Gerar lista de vértices (a, b, c, ...)
    vertices = [chr(ord('a') + i) for i in range(v)]
    
    # Ler as arestas
    edges = []
    for _ in range(e):
        line = input().split()
        u, v_node = line[0], line[1]
        edges.append((u, v_node))
    
    components = find_connected_components(vertices, edges)
    
    print(f"Case #{case}:")
    for component in components:
        print(','.join(component) + ',')
    
    print(f"{len(components)} connected components")
    print()