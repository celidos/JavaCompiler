[![Build Status](https://travis-ci.org/celidos/JavaCompiler.svg?branch=master)](https://travis-ci.org/celidos/JavaCompiler) 
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/c3a2927bff314215b3f04867965570b2)](https://www.codacy.com/manual/celidos/JavaCompiler?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=celidos/JavaCompiler&amp;utm_campaign=Badge_Grade)

## Компилятор языка MiniJava

Репозиторий с кодом проекта для курса "Теория компиляторов" ФИВТ МФТИ, кафедра ABBYY

Участник | telegram | e-mail
--- | --- | ---
Лунин Дмитрий Владимирович | @dimon2016 |
Поконечный Эдуард Павлович | @celidos | pokonechnyy.ep@phystech.edu
Ожерельева София Сергеевна | @Sofya_Ozherelieva |
Алексеев Никита Анатольевич | @Saynocommon |

[Грамматика языка](https://docs.google.com/document/d/1xCaMk7tq-WJN1Y59yW3w17DDs7QFwLpovbJ_ZrJp9NM/edit "Google Docs")

## Зависимости

`bison --version`

bison (GNU Bison) 3.4

`flex --version`

flex 2.6.4

`dot -V`

dot - graphviz version 2.40.1 (20161225.0304)

## Пример запуска:

Сборка всего:

`./make_all.sh`

Запуск программы на примере с кодом:

`./run_sample.sh ./tests/samples/two_plus_two.java ./two_plus_two_ast ./two_plus_two_irt`
