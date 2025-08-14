# Algoritmo de Cifrado ElGamal

Este repositorio contiene la implementación en lenguaje C del **algoritmo de cifrado de clave pública ElGamal**. [cite_start]ElGamal es un pilar de la criptografía asimétrica, desarrollado por Taher ElGamal en 1985[cite: 23].

## 📖 Descripción General

[cite_start]El **algoritmo de ElGamal** se basa en la dificultad computacional del **problema del logaritmo discreto**[cite: 24, 143]. [cite_start]A diferencia de los algoritmos de cifrado simétrico que usan una sola clave para cifrar y descifrar, ElGamal utiliza un par de claves: una **clave pública** para cifrar mensajes y una **clave privada** para descifrarlos[cite: 22].

[cite_start]El proceso de cifrado de un mensaje se realiza utilizando la clave pública, mientras que el descifrado solo es posible con la clave privada correspondiente[cite: 22]. [cite_start]Esto permite que dos partes, como Alicia y Bob, puedan intercambiar mensajes de forma segura a través de un canal no seguro[cite: 92].

[cite_start]El algoritmo también se relaciona estrechamente con el **intercambio de clave Diffie-Hellman** [cite: 143] [cite_start]y puede ser utilizado para generar firmas digitales seguras[cite: 25].

## ⚙️ Funcionamiento del Algoritmo

El documento adjunto describe el proceso en detalle, pero a grandes rasgos el algoritmo de ElGamal funciona así:

1.  [cite_start]**Selección de parámetros públicos**: Alicia elige un número primo grande $p$ y un elemento primitivo $g$ de $\mathbb{Z}_{p}$[cite: 146]. [cite_start]Ambos números serán públicos[cite: 146].
2.  **Generación de claves**:
    * [cite_start]Alicia escoge un número $a$ en el rango $[[1, p-2]]$, el cual funcionará como clave privada[cite: 146].
    * [cite_start]La clave pública de Alicia, $A$, se calcula como $A \equiv g^a \pmod{p}$[cite: 147, 148].
3.  **Cifrado del mensaje**:
    * [cite_start]Bob, que quiere enviar un mensaje $m$ a Alicia, escoge un número aleatorio $k$ que se utiliza para cifrar el mensaje[cite: 150, 154].
    * Bob calcula dos valores, $c_1$ y $c_2$:
        * [cite_start]$c_1 = g^k \pmod{p}$ [cite: 155]
        * [cite_start]$c_2 = m \cdot A^k \pmod{p}$ [cite: 156]
    * [cite_start]Bob le envía el par ordenado $(c_1, c_2)$ a Alicia[cite: 158].
4.  **Descifrado del mensaje**:
    * [cite_start]Alicia recibe el par $(c_1, c_2)$ y usa su clave privada $a$ para descifrar el mensaje[cite: 158].
    * [cite_start]Primero, calcula un valor auxiliar $x \equiv (c_1^a)^{-1} \pmod{p}$[cite: 159]. [cite_start]Esto se hace con el algoritmo 2.4.2 para calcular $c^{p-1-a}(mod~p)$, ya que $(c^{a})^{-1}\equiv c^{p-1-a}(mod~p)$[cite: 161, 162].
    * [cite_start]Finalmente, recupera el mensaje original $m$ calculando $x \cdot c_2 \pmod{p}$[cite: 164].

## 💻 Implementación en C

El código fuente implementa las funciones clave del algoritmo:

* [cite_start]`ClavePublica`: Genera la clave pública a partir de la clave privada[cite: 180, 332].
* [cite_start]`cifradoGammal`: Cifra un mensaje utilizando la clave pública y un valor aleatorio $k$[cite: 182, 338].
* [cite_start]`DescifradoGammal`: Descifra el par de valores cifrados para recuperar el mensaje original[cite: 183, 349].
* [cite_start]`FastPot`: Es una función auxiliar que implementa el **algoritmo rápido para la potenciación modular**, esencial para calcular las potencias de forma eficiente[cite: 108, 179, 295].

[cite_start]Este código está estructurado para cifrar y descifrar un mensaje carácter por carácter, utilizando las funciones `charToInt` e `IntToChar` para la codificación y decodificación[cite: 185, 186].
