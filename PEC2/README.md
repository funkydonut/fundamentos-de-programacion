# Fundamentos-de-Programacion

PEC2 - 20252
Enunciado

Un sistema de gestión agrícola inteligente debe decidir si activa el sistema de riego de
una parcela. Para optimizar el agua, se definen diferentes criterios según el tipo de cultivo
y las condiciones meteorológicas:

1. Riego de emergencia: El nivel de humedad del suelo es inferior al 10%,
independientemente del cultivo.

2. Riego por tipo de planta (según la especie):
- Suculenta: La humedad es inferior al 20%.
- Arbusto: La humedad es inferior al 40%.
- Planta Tropical: La humedad es inferior al 60%.

3. Riego preventivo por calor: La temperatura exterior supera los 35 grados y la
humedad es inferior al 50%, independiente del cultivo.
Se pide implementar un programa en C que indique, mediante una expresión, si el
sistema de riego debe activarse.
No se permite el uso de condicionales.
Siempre que sea posible, se debe evitar el uso de valores numéricos directos y utilizar en
su lugar constantes previamente definidas.

Entrada de datos
Se introducirán desde el teclado los valores:
1. Nivel de humedad actual (0-100).
2. Tipo de planta (0-Suculenta, 1-Arbusto, 2-Tropical).
3. Temperatura exterior (en grados Celsius).
Salida de datos
Se mostrará por pantalla si el riego debe activarse (1) o no (0).

Anexo
INPUT
HUMIDITY PERCENTAGE?
5.0
PLANT TYPE (0-SUCCULENT, 1-SHRUB, 2-TROPICAL)?
0
OUTDOOR TEMPERATURE?
25.0
OUTPUT
ACTIVATING IRRIGATION (0-FALSE, 1-TRUE): 1