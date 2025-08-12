Из любви к прекрасному, и желанию написать что-то условно масштабное на плюсах, было принято решение написать очередную реализацию клеточных автоматов
Вдохновение для различных правил черпал из статьи на хабре: https://habr.com/ru/articles/719324/

![alt text](https://github.com/GlebVas1/RaylibUI_ConwayCPP/blob/devel/images/4.png)

# Из реализованного почти все, что нужно для счастья:
  1 Все вычисления проводятся многопоточно с надлежащей синхронизацией. При наличии большого числа ядер, даже на относительно сложных правилах и крупных полях, обсчет проходит сравнительно быстро
  2 Реализован UI методами raylib, на который все и упирается. Следует учесть, что по умолчанию raylib дает из коробки, по крайней мере по моей субъективной оценке, довольно пресные элементы интерфейса, вследствие чего было решено написать свою библиотеку для отрисовки и взаимодействия всеъ элементов последнего
  3 Присутствует достаточно гибкая настройка правил игры, включая возможность создавать случайно генерируемые правила
  4 Все настраевымые параметры, такие как темы оформления, палитры, объекты и правила задаются текстовым конфигом, что исключает потребность пересобирать код при желании добавить разнообразия

Изначально доступно базовое окно, со стандартными правилами и палитрой

![alt text](https://github.com/GlebVas1/RaylibUI_ConwayCPP/blob/devel/images/1.png)

Однако при манипуляции с настройками можно получать различные эффекты на холсте:
 
![alt text](https://github.com/GlebVas1/RaylibUI_ConwayCPP/blob/devel/images/2.png)
![alt text](https://github.com/GlebVas1/RaylibUI_ConwayCPP/blob/devel/images/6.png)


Помимо возможности смен темы оформления, можно заставить интерфейс синхронизоваться с цветами отображенными на холсте:
![alt text](https://github.com/GlebVas1/RaylibUI_ConwayCPP/blob/devel/images/6.png)
![alt text](https://github.com/GlebVas1/RaylibUI_ConwayCPP/blob/devel/images/5.png)

И, дополнительно пару достаточно приятных визуальных эффектов, которыые получаются методом тыка:

![alt text](https://github.com/GlebVas1/RaylibUI_ConwayCPP/blob/devel/images/e1.png)
![alt text](https://github.com/GlebVas1/RaylibUI_ConwayCPP/blob/devel/images/e2.png)
![alt text](https://github.com/GlebVas1/RaylibUI_ConwayCPP/blob/devel/images/e3.png)
![alt text](https://github.com/GlebVas1/RaylibUI_ConwayCPP/blob/devel/images/e4.png)
![alt text](https://github.com/GlebVas1/RaylibUI_ConwayCPP/blob/devel/images/e5.png)
![alt text](https://github.com/GlebVas1/RaylibUI_ConwayCPP/blob/devel/images/e6.png)

# TODO:
  1 Внести по возможности еще новые правила, так же сделать механику более гибкой
  2 Сделать более адекватные варианты загрузок конфигурации, нежели сейчас

# Known issues:
  1 Direct/Indirect memory leaks, читая обсуждения raylib на хабе, а также будучи в поисках информации по этой проблеме в интернете, было установленно, что с огромной долей вероятности проблема вызвана непосредственно низкоуровневым взаимодействием с драйверами и opengl в целом со стороны raylib, как и на уровне, вероятно, кривых драйверов
