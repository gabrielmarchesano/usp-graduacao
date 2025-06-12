import matplotlib.pyplot as plt

# Dados para os gráficos
aleatorias_tamanho = {
    "Algoritmo": ["Insertion Sort", "Selection Sort", "Bubble Sort", "Merge Sort",
                  "Shell Sort", "Heap Sort", "Quick Sort"],
    1: [63644.76, 101149.41, 260086.95, 1586.28, 1694.87, 1989.49, 5872.02],
    1000: [10617721.96, 203689.27, 15786694.53, 122105.50, 43027.93, 47014.68, 47987.68],
}

crescente_tamanho = {
    "Algoritmo": ["Insertion Sort", "Selection Sort", "Bubble Sort", "Merge Sort",
                  "Shell Sort", "Heap Sort", "Quick Sort"],
    1: [50.86, 99256.07, 28.12, 886.58, 471.40, 1617.65, 5144.67],
    1000: [2844.13, 193622.29, 240.61, 92939.82, 1119.66, 41594.14, 34980.18],
}

decrescente_tamanho = {
    "Algoritmo": ["Insertion Sort", "Selection Sort", "Bubble Sort", "Merge Sort",
                  "Shell Sort", "Heap Sort", "Quick Sort"],
    1: [129127.96, 100264.82, 250941.91, 894.28, 672.63, 1585.21, 5278.98],
    1000: [23868565.44, 209986.17, 22966948.04, 92096.65, 31043.50, 35958.34, 42501.08],
}

# Função para gerar e exibir o gráfico
def gerar_grafico(dados, titulo):
    categorias = [1, 1000]
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
    ax.set_ylabel("Tempo de Execução (µs)", fontsize=12)
    ax.set_xlabel("Tamanho do Campo", fontsize=12)
    ax.legend(title="Algoritmos", bbox_to_anchor=(1.05, 1), loc='upper left', fontsize=10)
    plt.tight_layout()
    plt.show()

# Gerando e exibindo os gráficos
gerar_grafico(aleatorias_tamanho, "Chaves em ordem aleatória")
gerar_grafico(crescente_tamanho, "Chaves em ordem Crescente")
gerar_grafico(decrescente_tamanho, "Chave em ordem Decrescente")
