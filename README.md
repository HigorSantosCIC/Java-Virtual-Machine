# About

This repository contains an implementation of a Java Virtual Machine (JVM) that supports Java SE 8.

The entire code is based on a JVM specification by Tim Lindholm, Frank Yellin, Gilad Bracha and Alex Buckley, available in the official Oracle's documentation.

# Usage

In order to compile, link and build this project on Linux, paste the following command on a command line:

> $ make clean && make

Then, to execute the JVM, use:

> $ ./bin/jvm \<PATH\>

## Flags:

- **\<PATH\>**: Path to .class file that will be read by the JVM.


Avaliação ----

Defesa (100)

   - Componente 1  
   - Componente 2 
   - Componente 3 
   - Componente 4  
   - Componente 5

-------------------------
 Corretude do interpretador 

Resumo: 100

1. () array simples
2. () arrays.length
3. () arrays multidimensionais
4. () arrays de referencia
5. () doubles
6. () floats
7. () longs
8. () inteiros
9. () shorts
10. () strings
11. () desvios com cat 1 
12. () operacoes logicas com cat 1
13. () operacoes de deslocamento com cat 1 
14. () operacoes aritmeticas de cat 2 
15. () operacoes de deslocamento de longs
16. () system.out.println (int, float, string e booleano)
17. () conversao de e para cat 2
18. () iteracao
19. () switches
20. () fields
21. () interfaces
22. () recursao
23. () metodos estaticos
24. () metodos nao estaticos
25. () objetos 
26. () operacoes de retorno
27. () operacoes de manipulacao de pilha
28. () consistencia
29. () exceptions
30. () invokes
31. () polimorfismo
32. () reescrita
33. () herança
-------------------------

Resumo: 100

-- leitura do formato ponto class:
- Trata versões superiores? 
- Despreza silenciosamente atributos não tratados?
- Consistência?
- Corretude?
- Exibe mnemônicos?
- Apresenta reindireção das entradas no Constant Pool?


Bonus: 10% (bonus sobre a corretude do interpretador)

--  opcionais 
Todas as demais instruções.

( ) threads
( ) debug
( ) checagem dinâmica de tipos
( ) coletor de lixo.

-------------------------


Atribuição de nota para a JVM
0,3leitor_exibidor + 0,5corretude + 0,1defesa do interpretador + 0,1site

Site: 100 

- Apresenta o Diagrama de Comunicação entre os Módulos e a descrição de cada função?
- Contem a relação das estruturas de dados e os arquivos?
- Está atualizado?
- Corretude?


