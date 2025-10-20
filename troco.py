def troco_guloso(V, moedas=[50, 25, 10, 5, 1]):
    resultado = {}
    for m in moedas:
        if V >= m:
            qtd = V // m
            resultado[m] = qtd
            V -= qtd * m
    return resultado

print(troco_guloso(67))
