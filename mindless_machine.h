#include <stdlib.h>
#include <stdbool.h>

/*
* Функции для работы со строками
*/

#ifndef MARKOV_CHAIN_FOR_STRING_H
#define MARKOV_CHAIN_FOR_STRING_H

#include <stdio.h>

/**
 * Структура для хранения графа состояний конечного автомата.
 * v_graph - вершины графа - массив слов, встречающихся в тексте
 * e_graph - ребра графа - двумерный массив int'ов, в котом сохраняется отношения между словами
 * size_graph - количество вершин графа
 */
struct graph;

/**
 * функция считывает строку с консоли до переноса строки.
 * @param *str - указатель на начало строки, в которую записсывается результат
 * @return  количество считынных символов
 *          -1 - количество считанных символов больше буфера
 */
int read_string (char *str);

/**
 * функция выводит строку в консоль
 * @param *str - указатель на начало строки
 * @return  0 - успешное выполнении функции,
 *          -1 - ошибка: указатель не инициаллизирован
 */
int write_console(char const *str);

/**
 * функция записывает строку в файл
 * создает новый файл, если файла с именем fname не существует
 * @param fname имя файла в который записывается строка
 * @param *str - указатель на начало строки, с которой производится запись с файла
 * @return  0 - успешное выполнении функции,
 *          -1 - ошибка: указатель не инициаллизирован
 */
int write_file(char const *fname, char const *str);

/**
 * функция парсит строку по токенам и создает конечный автомат
 * @param str - исходная строка
 * @param graph - указатель на граф состояний
 * @return количество считанных символов
 *          -1 - ошибка: передан NULL
 */
int create_machine(char *str, struct graph *graph);

/**
 *  функция переводит слово в нижний регистр (english)
 *  @param str - указатель на строку
 *  @return true  - успешное выполнение функции
 *          false - ошибка: указатель на инициализирван
 */
bool str_to_down(char* str);

/**
 * Функция ставит перед каждым знаком препинания пробел
 * Необходима для дальнейшего разбиения строки на токенв по пробелам (чтобы каждый знак препинания был тоже токеном)
 * @attention - убивает после себя @param str
 *
 * @param str - указатель на начальную строку
 * @return указатель на строку-результат
 */
char* str_replace_punct(char* str);

/**
 * Функция поиска строки str в двумерном массиве строк
 * @param v_graph - указатель на двумерный массив строк, в котором происходит поиск элементов
 * @param str - указатель на искомую строку
 * @return  индекс найденной строки
 *          -1 - совпадений не найдено
 *          -2 - переден NULL
 */
int graph_search_elem(char const *str, struct graph const* graph);

/**
 * Функция добавления вершины в граф состояний
 * Если элемент существует, возвращает его порядковый номер
 * @param str - указатель на значение добавляемой вершины
 * @param graph - указатль на граф состояний
 * @return  индекс по которому находится элемент
 *          -1 - Ошибка: указатель на NULL
 */
int graph_add_v_graph(char const *str, struct graph* graph);

/**
 * Функция добавления элемента в граф состояний
 * @param str_prev указатель на значение "откуда" строится отношение в графе
 * @param str_cur - указатель на значение "куда" строится отношение
 * @param graph - указатель на граф состояний
 * @return  номер полученного элемента
 *          -1 - Ошибка: указатель на неинициаллизированную строку
 */
int graph_add_e_graph(char const *str_prev, char const *str_cur, struct graph* graph);

/**
 * Функция для создания графа состояний
 * @param sz - размер выделяемой памяти
 * @return указатель на graph
 */
struct graph* graph_create(size_t sz);

/**
 * Функция сохраняет граф в файл
 * Структура хранения графа:
 * size_graph\n
 * v_graph[0]\n
 * ...
 * v_graph[size_graph - 1]
 * v_graph[0][0] v_graph[0][1] ... v_graph[0][size_graph - 1]
 * ...
 * v_graph[size_graph - 1][0] v_graph[size_graph - 1][1] ... v_graph[size_graph - 1][size_graph - 1]
 * @param output_file - файл для хранения графа
 * @param graph - указатель на граф
 */
bool save_graph(FILE *output_file, struct graph const *graph);

/**
 * Функция выгружает граф
 * @param input_file - файл для хранения графа
 * @return - указатель на созданный граф
 */
struct graph* load_graph(FILE *input_file);

/**
 * Функция создания графа вероятностей
 * @param graph - указатель на граф
 * @return - результат проверки
 */
bool graph_to_probability(struct graph *graph);

/**
 * Функция, которая проверяет, присутствует ли буква с в строке-шаблоне
 * @param c - символ для проверки
 * @param template - шаблон для сравнения
 * @return - результат проверки
 */
bool find_char_in_template(char c, char const *template);

/**
 * Функция, которая проверяет, принадлежит ли символ с интервалу [start, end]
 * @param c - символ для проверки
 * @param start - начало интервала
 * @param end - конец интервала
 * @return - результат проверки
 */
bool char_in_interval(char c, char start, char end);
#endif //MARKOV_CHAIN_FOR_STRING_H
