[![Build Status](https://travis-ci.org/celidos/JavaCompiler.svg?branch=master)](https://travis-ci.org/celidos/JavaCompiler) 
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/c3a2927bff314215b3f04867965570b2)](https://www.codacy.com/manual/celidos/JavaCompiler?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=celidos/JavaCompiler&amp;utm_campaign=Badge_Grade)

Зависимости:

`bison --version`

bison (GNU Bison) 3.4

`flex --version`

flex 2.6.4

`dot -V`

dot - graphviz version 2.40.1 (20161225.0304)

Сборка всего:

`./make_all.sh`

Запуск программы на примере с кодом (результаты записываются в подпапки `output`):

`./run_sample.sh ./tests/samples/two_plus_two.java two_plus_two`
