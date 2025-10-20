def activity_selection(activities):
    # atividades: lista de tuplas (start, finish, name)
    # ordenar por finish crescente
    activities_sorted = sorted(activities, key=lambda x: x[1])
    chosen = []
    last_finish = -float('inf')
    for s, f, name in activities_sorted:
        if s >= last_finish:
            chosen.append((name, s, f))
            last_finish = f
    return chosen

acts = [(1,3,'A'), (2,5,'B'), (3,6,'C'), (5,7,'D'), (6,8,'E'), (8,10,'F')]
print(activity_selection(acts))
