import matplotlib.pyplot as plt

# Dados atualizados com número de chaves e comparações
aleatorias_comparacoes = {
    "Algoritmo": ["Insertion Sort", "Selection Sort", "Bubble Sort", "Merge Sort",
                  "Shell Sort", "Heap Sort", "Quick Sort"],
    100: [2373, 4950, 12035, 344, 1764, 2086, 1803],
    1000: [250298, 499500, 1245268, 8718, 29395, 30217, 29395],
    10000: [25024270, 4999500, 124992516, 120403, 143131, 402553, 400600]
}

crescente_comparacoes = {
    "Algoritmo": ["Insertion Sort", "Selection Sort", "Bubble Sort", "Merge Sort",
                  "Shell Sort", "Heap Sort", "Quick Sort"],
    100: [198, 4950, 200, 356, 1341, 2221, 1520],
    1000: [1998, 499500, 2000, 5044, 19392, 32125, 26674],
    10000: [19998, 4999500, 20000, 69008, 255729, 425869, 377043]
}

decrescente_comparacoes = {
    "Algoritmo": ["Insertion Sort", "Selection Sort", "Bubble Sort", "Merge Sort",
                  "Shell Sort", "Heap Sort", "Quick Sort"],
    100: [5148, 4950, 15048, 316, 1571, 1849, 1753],
    1000: [501498, 499500, 1500498, 4932, 23312, 27949, 84608],
    10000: [50014998, 4999500, 150004998, 69008, 309463, 380089, 384435]
}

def gerar_grafico(dados, titulo):
    categorias = [100, 1000, 10000]  # Novos valores do eixo x
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
    ax.set_ylabel("Número de Comparações", fontsize=12)  # Eixo y atualizado
    ax.set_xlabel("Número de Chaves", fontsize=12)  # Eixo x atualizado
    ax.legend(title="Algoritmos", bbox_to_anchor=(1.05, 1), loc='upper left', fontsize=10)
    plt.tight_layout()
    plt.show()

# Gerando e exibindo os gráficos
gerar_grafico(aleatorias_comparacoes, "Chaves em ordem aleatória")
gerar_grafico(crescente_comparacoes, "Chaves em ordem Crescente")
gerar_grafico(decrescente_comparacoes, "Chaves em ordem Decrescente")
