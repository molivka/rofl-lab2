# Лабораторная работа №2, lerner для варианта brainfuck-лисп

Выполнил Краев Степан, ИУ9-51Б.

## Запуск
1. Склонировать данный репозиторий:
    ```
    git clone git@github.com:molivka/rofl-lab2.git
    ```
2. Запустить код угадывателя:
    ```
    py Lerner.py
    ```
3. Запустить угадыватель. Работает в паре с поднятым локально МАТом (запускает МАТ автоматически при указании пути):
   ```
   def main():
    guesser = LispGuesser("filepath_to_MATmain_HERE", "parameters.txt")
   ```
4. Сгенерить параметры (пока что так):
   ```
   import json

  def generate_params():
      params = {
          "max_bracket_depth": 5,
          "max_automaton_size": 100
      }
      with open("parameters.txt", "w") as f:
          json.dump(params, f, indent=4)
  ...
  main()
    generate_params()
   ```

## Реализация
1. Основными функциями при общении с МАТом являются: проверка слова на принадлежность языку и проверка полученного автомата на эквивалентность
    ```
    def membership_query 
    ```
2. Основными функциями при построении описания автомата являются: проверка таблицы на полноту и на непротиворечивость (остальные функции вспомогательные для этих двух)
    ```
    def equivalence_query
    ```
3. Сделаны функции для вывода в консоль состояний угадывателя и обработчики ошибок
    ```
    print
    ```
4. Функции для взаимодествия с МАТом сделаны через входящий поток
    ```
    process.stdin
    ```

## Тестирование
Данный код был протестирован на:
   1. Примере автомата с консультации по данной лабораторной работе.
   3. На МАТе людей из моей другой группы
   4. Ручками на локальных тестах.

## Замечания
Описал их в Pull Request, их много, но все касаются данных, передаваемых в stdin