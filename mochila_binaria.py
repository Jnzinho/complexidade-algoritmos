def mochila_binaria(weights, values, W):
    n = len(weights)
    dp = [[0] * (W + 1) for _ in range(n + 1)]

    for i in range(1, n + 1):
        wi = weights[i - 1]
        vi = values[i - 1]
        for w in range(0, W + 1):
            if wi > w:
                dp[i][w] = dp[i - 1][w]
            else:
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - wi] + vi)

    return dp


def print_dp_table(dp, W):
    n = len(dp) - 1
    max_val = 0
    for row in dp:
        for val in row:
            if val > max_val:
                max_val = val

    cell_width = max(len(str(max_val)), len(str(W))) + 2

    header = " " * cell_width + "".join(f"{w:>{cell_width}}" for w in range(W + 1))
    print(header)

    for i in range(n + 1):
        row_str = f"{i:>{cell_width}}" + "".join(f"{dp[i][w]:>{cell_width}}" for w in range(W + 1))
        print(row_str)


def reconstruir_itens(dp, weights, values, W):
    itens = []
    i = len(weights)
    w = W
    while i > 0 and w >= 0:
        if dp[i][w] != dp[i - 1][w]:
            idx = i - 1
            itens.append(idx)
            w -= weights[idx]
        i -= 1
    itens.reverse()
    return itens

weights = [4, 3, 5, 2]
values  = [40, 30, 50, 20]
W = 10

dp = mochila_binaria(weights, values, W)
print_dp_table(dp, W)
print("Valor máximo:", dp[len(weights)][W])
itens = reconstruir_itens(dp, weights, values, W)
print("Itens na mochila (índice, peso, valor):")
for idx in itens:
    print(f"- {idx}, {weights[idx]}, {values[idx]}")