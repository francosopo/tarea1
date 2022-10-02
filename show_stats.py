import pandas as pd
import matplotlib.pyplot as plt

header = [
    "nalg",
    "cant_palabras",
    "tamano_string",
    "tiempo_promedio_por_par"
]
filename = "stats.csv"

df = pd.read_csv(filename, sep=',', names=header)

df_alg_1 = df[df['nalg'] == 1]
df_alg_2 = df[df['nalg'] == 2]
df_alg_3 = df[df['nalg'] == 3]

fig, axes = plt.subplots(nrows=1, ncols=3, sharex=True, sharey=True)


df_alg_1.plot(ax=axes[0],x='tamano_string',y='tiempo_promedio_por_par',
xlabel='Cantidad de palabras', ylabel="Tiempo promedio [s]",
title="Programación Dinámica", legend="Tiempo promedio por par")

df_alg_2.plot(ax=axes[1], x='tamano_string',y='tiempo_promedio_por_par',
xlabel='Cantidad de palabras', ylabel="Tiempo promedio [s]",
title="Algoritmo en caché", legend="Tiempo promedio por par")

df_alg_3.plot(ax=axes[2], x='tamano_string',y='tiempo_promedio_por_par',
xlabel='Cantidad de palabras', ylabel="Tiempo promedio [s]",
title="Memoria secundaria", legend="Tiempo promedio por par")

plt.show()
