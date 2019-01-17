#include "mindless_machine.h"
#include <stdio.h>

 /**
 * Функции для работы с конечным автоматом
 * и реализации цепей Маркова для генерации осмысленного текста,
 * исходя из данного.
 */

#ifndef MARKOV_CHAIN_CHAIN_H
#define MARKOV_CHAIN_CHAIN_H

/**
 * Функция создания нового конечного автомата из файла filename
 * @param file - файл
 * @return указатель на новый граф
 */
struct graph* create_new_machine(FILE *file);

/**
 * Функция создания автомата из сохраненного графа
 * @param file - файл
 * @return указатель на граф
 */
struct graph* create_new_machine_graph_file(FILE *file);

/**
 * Функция генерации предложения
 * @param graph - указатель на граф состояний (автомат)
 * @return - указатель на строку
 */
char* generate(struct graph const *graph);

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
#endif //MARKOV_CHAIN_CHAIN_H
