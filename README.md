### COMPILAR
```sh
gcc -Wall -pedantic -std=c99 -O2 -g lector.c
```

### EJECUTAR

```sh
rm stats.csv #para remover estadisticas
./a.out
```

Se ejecutaran los tests, se crearán los archivos para probar el codigo y para calcular estadisticas.

En un AMD A9-9425 se demoró 17 minutos con debian 11 64 bits y gcc de 64 bits version 10.2.1

Las estadisticas están sin header, así que
se cargan desde el script show_stats.py

### VER ESTADISTICAS
```sh
python3 -m venv venv
source venv/bin/activate
pip install -r requirements.txt
python show_stats.py
```