import matplotlib.pyplot as plt

# Dados atualizados com tempos em microsegundos
aleatorias_tempo = {
    "Algoritmo": ["Insertion Sort", "Selection Sort", "Bubble Sort", "Merge Sort",
                  "Shell Sort", "Heap Sort", "Quick Sort"],
    100: [6.84, 14.13, 248.09, 911.60, 7.02, 9.98, 50.34],
    1000: [622.49, 1051.22, 2074.25, 114.74, 118.66, 1417.84, 581.87],
    10000: [63644.76, 101149.41, 260086.95, 1586.28, 1694.87, 1989.49, 5872.02]
}

crescente_tempo = {
    "Algoritmo": ["Insertion Sort", "Selection Sort", "Bubble Sort", "Merge Sort",
                  "Shell Sort", "Heap Sort", "Quick Sort"],
    100: [0.58, 10.82, 0.37, 6.05, 2.52, 33.01, 45.83],
    1000: [5.06, 997.94, 2.86, 70.87, 35.49, 129.94, 478.69],
    10000: [50.86, 99256.07, 28.12, 886.58, 471.40, 1617.65, 5144.67]
}

decrescente_tempo = {
    "Algoritmo": ["Insertion Sort", "Selection Sort", "Bubble Sort", "Merge Sort",
                  "Shell Sort", "Heap Sort", "Quick Sort"],
    100: [13.30, 11.74, 25.31, 6.18, 3.96, 8.10, 48.41],
    1000: [1230.04, 1021.55, 2497.99, 71.18, 51.74, 119.53, 513.35],
    10000: [129127.96, 100264.82, 250941.91, 894.28, 672.63, 1585.21, 5278.98]
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
    ax.set_ylabel("Tempo de Execução (µs)", fontsize=12)  # Eixo y atualizado
    ax.set_xlabel("Número de Chaves", fontsize=12)
    ax.legend(title="Algoritmos", bbox_to_anchor=(1.05, 1), loc='upper left', fontsize=10)
    plt.tight_layout()
    plt.show()

# Gerando e exibindo os gráficos
gerar_grafico(aleatorias_tempo, "Chaves em ordem aleatória")
gerar_grafico(crescente_tempo, "Chaves em ordem Crescente")
gerar_grafico(decrescente_tempo, "Chaves em ordem Decrescente")
