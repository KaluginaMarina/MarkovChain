#ifndef MARKOV_CHAIN_CHAIN_H
#define MARKOV_CHAIN_CHAIN_H

#include "mindless_machine.h"
#include <stdio.h>
/**
 * Функция создания нового конечного автомата из файла filename
 * @param file - файл
 * @return указатель на новый граф
 */
graph* create_new_machine(FILE *file);

/**
 * Функция создания автомата из сохраненного графа
 * @param file - файл
 * @return указатель на граф
 */
graph* create_new_machine_graph_file(FILE *file);

/**
 * Функция генерации предложения
 * @param graph - указатель на граф состояний (автомат)
 * @return - указатель на строку
 */
char* generate(graph* graph);

/**
 * функция считывает строку с файла
 * @param file - файл, с которого производится считывание
 * @return  указатель на начало строки, в которую производится запись с файла
 */
char* read_file(FILE *file);

/**
 * Функция приводит строку к читаемому виду (без лишних пробелов между знаками препинания)
 * @param str - указатель на начало строки
 * @return - новую строку-результат
 */
char* do_res_string(char* str);

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
#endif //MARKOV_CHAIN_CHAIN_H
