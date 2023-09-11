#ifndef _VIDEO_TEXT_H_
#define _VIDEO_TEXT_H_

#include "utypes.h"
#include <stdio.h>

/* inicio da defincao da memoria video-texto*/
#define VIDEO_TEXT 0xB8000              ///< Endereco de memoria em modo texto
#define WIDTH 80                                ///< Numero de linhas do ecra
#define HEIGHT 25                               ///< Numero de colunas do ecra
/*final das dimensoes e definicao da memoria de video no modo texto */

/*name Definicao dos bytes para os atributos
* (definicao das cores estao no ficheiro conio.h)
*/

#define BLUE_FOREG  (1 << 0)  ///< Primeiro plano a azul
#define GREEN_FOREG (1 << 1)  ///< Primeiro plano a verde
#define RED_FOREG   (1 << 2)  ///< Primeiro plano a vermelho

#define STRONG      (1 << 3)  ///< Intensidade do primeiro plano

#define BLUE_BACK   (1 << 4)  ///< Fundo azul
#define GREEN_BACK  (1 << 5)  ///< Fundo verde
#define RED_BACK    (1 << 6)  ///< Fundo vermelho

#define CANTO_SESQUERDO 0xC9
#define CANTO_SDIREITO 0xBB
#define CANTO_IESQUERDO 0xC8
#define CANTO_IDIREITO 0XBC
#define VERTICAL 0xBA
#define HORIZONTAL 0xCD
#define BLINK       (1 << 7)  ///< ja esta definido no conio.h

#define NORMAL (RED_FOREG | GREEN_FOREG | BLUE_FOREG) ///< definicao de caracteristicas normais, juncao das tres cores
#define TAM_COLORS 3
/* final da definicao dos bytes para os atributos */

/* name Funcoes uteis */
/**
 * Imprimir um caracter na posicao x,y com atributos
 *
 * @param str caracter que se prentende imprimir
 * @param x coordenada x onde sera impresso o numero
 * @param y coordenada y onde sera impresso o numero
 * @param attributes caracteristica que tera o numero impresso (Cor letra, cor background, ...)
 */
 /* @return true se a funcao obteve sucesso */
Bool printCharAt(char ch, int x, int y, char attributes);

/**
 * Imprimir uma cadeia de caracteres na posição x,y com atributos
 *
 * @param str caracter que se prentende imprimir
 * @param x coordenada x onde será impresso o número
 * @param y coordenada y onde será impresso o número
 * @param attributes característica que terá o número impresso (Cor letra, cor background, ...)
 *
 * @return true se a função obteve sucesso
 */
Bool printStringAt(char *str, int x, int y, char attributes);

/**
 * Imprimir um inteiro na posição x,y com atributos
 *
 * @param num é o número que se prentende imprimir
 * @param x coordenada x onde será impresso o número
 * @param y coordenada y onde será impresso o número
 * @param attributes característica que terá o número impresso (Cor letra, cor background, ...)
 *
 * @return true se a função obteve sucesso
 */
Bool printIntAt(int num, int x, int y, char attributes);

/**
 * Desenha um rectângulo com o canto esquerdo na posição x,y e com comprimento e largura de dimensões, decorado com título e seus atributos
 *
 * @param title título da janela a desenhar
 * @param attributes característica que terá a janela
 * @param x coordenada x onde será impresso o número
 * @param y coordenada y onde será impresso o número
 * @param width largura da janela
 * @param height comprimento da janela
 *
 * @return true se a função obteve sucesso
 */
Bool drawFrame(char *title, char attributes, int x, int y, int width, int height);

/**
 * Preenche o ecrã com uma cor de fundo, é como se o ecrã fosse limpo
 *
 * @param background Cor de fundo
 */
void fillScreen(char background);

/*@} final das funções úteis */

/**@} final do VideoTexto */
#endif

