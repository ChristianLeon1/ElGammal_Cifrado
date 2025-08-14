# Algoritmo de Cifrado ElGamal

Este repositorio contiene la implementación en lenguaje C del **algoritmo de cifrado de clave pública ElGamal**. ElGamal es un pilar de la criptografía asimétrica, desarrollado por Taher ElGamal en 1985.

## 📖 Descripción General

El **algoritmo de ElGamal** se basa en la dificultad computacional del **problema del logaritmo discreto**. A diferencia de los algoritmos de cifrado simétrico que usan una sola clave para cifrar y descifrar, ElGamal utiliza un par de claves: una **clave pública** para cifrar mensajes y una **clave privada** para descifrarlos.

El proceso de cifrado de un mensaje se realiza utilizando la clave pública, mientras que el descifrado solo es posible con la clave privada correspondiente. Esto permite que dos partes, como Alicia y Bob, puedan intercambiar mensajes de forma segura a través de un canal no seguro.

El algoritmo también se relaciona estrechamente con el **intercambio de clave Diffie-Hellman** y puede ser utilizado para generar firmas digitales seguras.

## ⚙️ Funcionamiento del Algoritmo

El documento adjunto describe el proceso en detalle, pero a grandes rasgos el algoritmo de ElGamal funciona así:

1.  **Selección de parámetros públicos**: Alicia elige un número primo grande $p$ y un elemento primitivo $g$ de $\mathbb{Z}_{p}$. Ambos números serán públicos.
2.  **Generación de claves**:
    * Alicia escoge un número $a$ en el rango $[[1, p-2]]$, el cual funcionará como clave privada.
    * La clave pública de Alicia, $A$, se calcula como $A \equiv g^a \pmod{p}$.
3.  **Cifrado del mensaje**:
    * Bob, que quiere enviar un mensaje $m$ a Alicia, escoge un número aleatorio $k$ que se utiliza para cifrar el mensaje.
    * Bob calcula dos valores, $c_1$ y $c_2$:
        * $c_1 = g^k \pmod{p}$ 
        * $c_2 = m \cdot A^k \pmod{p}$
    * Bob le envía el par ordenado $(c_1, c_2)$ a Alicia.
4.  **Descifrado del mensaje**:
    * Alicia recibe el par $(c_1, c_2)$ y usa su clave privada $a$ para descifrar el mensaje.
    * Primero, calcula un valor auxiliar $x \equiv (c_1^a)^{-1} \pmod{p}$. Esto se hace con el algoritmo 2.4.2 para calcular $c^{p-1-a}(mod~p)$, ya que $(c^{a})^{-1}\equiv c^{p-1-a}(mod~p)$.
    * Finalmente, recupera el mensaje original $m$ calculando $x \cdot c_2 \pmod{p}$.

## 💻 Implementación en C

El código fuente implementa las funciones clave del algoritmo:

* `ClavePublica`: Genera la clave pública a partir de la clave privada.
* `cifradoGammal`: Cifra un mensaje utilizando la clave pública y un valor aleatorio $k$.
* `DescifradoGammal`: Descifra el par de valores cifrados para recuperar el mensaje original.
* `FastPot`: Es una función auxiliar que implementa el **algoritmo rápido para la potenciación modular**, esencial para calcular las potencias de forma eficiente.

Este código está estructurado para cifrar y descifrar un mensaje carácter por carácter, utilizando las funciones `charToInt` e `IntToChar` para la codificación y decodificación[cite: 185, 186].
