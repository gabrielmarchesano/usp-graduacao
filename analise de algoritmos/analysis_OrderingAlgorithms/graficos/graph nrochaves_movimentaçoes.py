import matplotlib.pyplot as plt

# Dados atualizados com número de movimentações
aleatorias_movimentacoes = {
    "Algoritmo": ["Insertion Sort", "Selection Sort", "Bubble Sort", "Merge Sort",
                  "Shell Sort", "Heap Sort", "Quick Sort"],
    100: [2373, 291, 6525, 1344, 1307, 1785, 1449],
    1000: [250298, 2970, 744980, 19952, 21952, 27216, 21381],
    10000: [25024270, 29684, 1245268, 267232, 327858, 372552, 246540]
}

crescente_movimentacoes = {
    "Algoritmo": ["Insertion Sort", "Selection Sort", "Bubble Sort", "Merge Sort",
                  "Shell Sort", "Heap Sort", "Quick Sort"],
    100: [198, 0, 0, 1344, 884, 1620, 1005],
    1000: [1998, 0, 0, 19952, 12914, 23294, 17172],
    10000: [19998, 0, 0, 267232, 170486, 395868, 258255]
}

decrescente_movimentacoes = {
    "Algoritmo": ["Insertion Sort", "Selection Sort", "Bubble Sort", "Merge Sort",
                  "Shell Sort", "Heap Sort", "Quick Sort"],
    100: [5148, 150, 14850, 1344, 1206, 1546, 1470],
    1000: [501498, 1500, 1498500, 19952, 16531, 29848, 20415],
    10000: [50014998, 15000, 14995000, 267232, 224190, 350088, 261447]
}

def gerar_grafico(dados, titulo):
    categorias = [100, 1000, 10000]
    algoritmos = dados["Algoritmo"]

    x = range(len(categorias))
    width = 0.1  # Largura das barras

    fig, ax = plt.subplots(figsize=(12, 6))
    for i, algoritmo in enumerate(algoritmos):
        valores = [dados[categoria][i] for categoria in categorias]
        ax.bar([xi + i * width for xi in x], valores, width, label=algoritmo)

    ax.set_title(titulo, fontsize=14)
    ax.set_xticks([xi + width * (len(algoritmos) - 1) / 2 for xi in x])
    ax.set_xticklabels(categorias, fontsize=12)
    ax.set_ylabel("Número de Movimentações", fontsize=12)  # Eixo y atualizado
    ax.set_xlabel("Número de Chaves", fontsize=12)
    ax.legend(title="Algoritmos", bbox_to_anchor=(1.05, 1), loc='upper left', fontsize=10)
    plt.tight_layout()
    plt.show()

# Gerando e exibindo os gráficos
gerar_grafico(aleatorias_movimentacoes, "Chaves em ordem aleatória")
gerar_grafico(crescente_movimentacoes, "Chaves em ordem Crescente")
gerar_grafico(decrescente_movimentacoes, "Chaves em ordem Decrescente")
