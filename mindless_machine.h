#include <stdlib.h>
#include <stdbool.h>

/*
* Функции для работы со строками
*/

#ifndef MARKOV_CHAIN_FOR_STRING_H
#define MARKOV_CHAIN_FOR_STRING_H
#define N 1000000 // глобальный буфер для максимальной строки


/**
 * Структура для хранения графа состояний конечного автомата.
 * v_graph - вершины графа - массив слов, встречающихся в тексте
 * e_graph - ребра графа - двумерный массив int'ов, в котом сохраняется отношения между словами
 * size_graph - количество вершин графа
 */
typedef struct graph {
    size_t size_graph;
    char** v_graph;
    int** e_graph;
} graph;

/**
 * функция считывает строку с консоли до переноса строки.
 * строка не должна превышать глобальный буфер N
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
int write_console(char *str);

/**
 * функция считывает строку с файла
 * количество символов в файле не должно превышать заданный глобальный буфер N
 * @param fname - имя файла, с которого производится считывание
 * @param *str - указатель на начало строки, в которую производится запись с файла
 * @return  количество считанных символов
 *          -1 - количество считанных символов больше буфера
 *          -2 - ошибка при открытии файла
 */
int read_file(char *fname, char *str);

/**
 * функция записывает строку в файл
 * создает новый файл, если файла с именем fname не существует
 * @param fname имя файла в который записывается строка
 * @param *str - указатель на начало строки, с которой производится запись с файла
 * @return  0 - успешное выполнении функции,
 *          -1 - ошибка: указатель не инициаллизирован
 */
int write_file(char *fname, char *str);

/**
 * функция парсит строку по токенам
 * возвращает граф, со строками-веринами и массив, в котором храняться отношения между вершинами
 * @param str - исходная строка
 * @param graph - указатель на граф состояний
 * @return количество считанных символов
 */
int str_parse(char* str, graph graph);

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
int graph_search_elem(char *str, graph const* graph);

/**
 * Функция добавления вершины в граф состояний
 * Если элемент существует, возвращает его порядковый номер
 * @param str - указатель на значение добавляемой вершины
 * @param graph - указатль на граф состояний
 * @return  индекс по которому находится элемент
 *          -1 - Ошибка: указатель на NULL
 */
int graph_add_v_graph(char *str, graph* graph);

/**
 * Функция добавления элемента в граф состояний
 * @param str_prev указатель на значение "откуда" строится отношение в графе
 * @param str_cur - указатель на значение "куда" строится отношение
 * @param graph - указатель на граф состояний
 * @return  номер полученного элемента
 *          -1 - Ошибка: указатель на неинициаллизированную строку
 */
int graph_add_e_graph(char *str_prev, char *str_cur, graph* graph);

/**
 * Функция для создания графа состояний
 * @param sz - размер выделяемой памяти
 * @return указатель на graph
 */
graph* graph_create(size_t sz);

/**
 * Функция выводит граф в консоль
 * @param graph
 */
void graph_print(graph* graph);

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
 * @param filename - имя файла для хранения графа
 * @param graph - указатель на граф
 */
bool save_graph(char* filename, graph* graph);

/**
 * Функция выгружает граф
 * @param filename_v_graph - имя файла для хранения графа
 * @return - указатель на созданный граф
 */
graph* load_graph(char* filename);
#endif //MARKOV_CHAIN_FOR_STRING_H
