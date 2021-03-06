# MarkovChain
Генерация текста с использованием цепей Маркова

# Синтаксис

``` ./MarkovChain  [-s] [-l] [-n NUM] FILE ```

# Описание 

Генератор осмысленного текста с использованием цепей Маркова на основе пользовательского текста. 

`FILE` - файл `.txt`, с текстом на __английском__ языке, на основе которого будет работать генератор. Рекомендуемый размер текста: __не более 25.000 символов.__

`-s` - после генерации текста сохраняет полученный граф состояний для последующего использования.

`-l` - загружает _ранее сохраненный_ граф.

`-n NUM` - указывает количество предложений для генерации. Значение по умолчанию: 1.

# Краткое описание алгоритма

__Цепь Маркова__ - автомат без предусловия: последовательность случайных событий, в которой вероятность каждого зависит только от состояния, в котором процесс находится в текущий момент и не зависит от более ранних состояний.

Алгоритм генерации текста условно можно разбить на 2 этапа: 
1. Создание конечного автомата (в виде графа состояний).
2. Генерация текста, используя полученный автомат.

### Создание конечного автомата

Автомат представлен в виде графа, в котором вершины (состояния) - это слова в тексте, а ребра - вероятность перехода из текущего состояния в другое. 

Для создания автомата текст разбивается на токены по пробелам и далее рассматривается каждая пара слов. Если слова из пары уже присутствуют в автомате,
то увеличивается вероятность перехода из состояния первого слова в паре в состояние второго. Если в автомате нет хотя бы одного слова, то сначала создаются недостающие вершины графа, а потом добавляется отношение между ними.

### Генерация текста

Генерация текста начинается со слова, которое раньше стояло в начале предложения (после точки). После генерации начального слова ищется 
следующее на основании комбинации вероятности и случайности. Этот цикл продолжается до тех пор, пока не встретится конец предложения. 
