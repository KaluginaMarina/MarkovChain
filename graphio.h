#include <stdbool.h>
#include <stdio.h>

 /**
 * Функции для вывода информации в консоль и получении данных из аргументов командной строки
 */
#ifndef MARKOV_CHAIN_GRAPHIO_H
#define MARKOV_CHAIN_GRAPHIO_H
#define FLAG_LOAD_FILE 1
#define FLAG_SAVE_GRAPH 2
#define FLAG_AMOUNT 4

/**
 * Функция проверки размера файла
 * При неподустимом размере файла предлагает пользователю завершить программу
 * @param f - исходный файл
 * @return
 */
bool check_fsize(FILE *f);

/**
 * Функция подсчета количества символов в файле
 * @param f - исходный файл
 * @return количество символов
 */
size_t get_file_size(FILE *f);

/**
 * Функция для получения флагов из командной строки
 * и вываоде пользовательских ошибок при вводе команды
 * @param argc - аргументы командной строки
 * @param argv - аргументы командной строки
 * @return маску флагов типа int
 */
int parse_flags(int argc, char *argv[]);

/**
 * Функция для создания или загрузки графа
 * @param flags - маска флагов
 * @param filename - имя файла с текстом
 * @return указатель на созданный граф
 */
struct graph* create_graph(int flags, char* filename);

/**
 * Функция для вывода сгенерированного текста
 * @param graph указатель но граф
 */
void generate_text(struct graph* graph);

/**
 * Функция для сохранения графа
 * @param flags - маска флагов
 * @param filename - имя файла
 * @param graph - граф
 */
void graph_save(int flags, char *filename, struct graph* graph);
#endif //MARKOV_CHAIN_GRAPHIO_H
