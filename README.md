# SubstitutionsCalculator
Calculator for multiplying substitutions from right to left, pow them and find the reverse substitution

## Как с ним работать?
Представлен класс Substitution, имеющий конструктор, принимающий в себя std::map (можно воспользоваться синтаксисом вида `{ {1, i}, {2, j}, {3, k} }`
Их можно перемножать (перегружена *), возводить в степень (метод PowIn), переворачивать (Reverse).
