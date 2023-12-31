# SDL2 Sidescroller game project

---

### Цель проекта:
Реализация простого sidescroller-a, с графикой на SDL2.

Цель понять, как работать с графическими библиотеками, в частности с SDL2, строить игровую логику и физику, а также создавать интерфейс и обрабатывать пользовательский ввод.

Поставлена цель реализовать: 
- простую игровую логику (перемещение камеры, пользовательский интерфейс, изменение состояния игрового мира)
- игровую физику (гравитацию, коллизии, взаимодействия с объектами и противниками, и т.д.)
- обработку пользовательского ввода и передачу его в игру
- искуственный интеллект противника

---

### Установка:

1. Скачать репозиторий
2. Установить vcpkg. Для этого перейти в директорию **vcpkg_install** и запустить скрипт:
   - для windows install.cmd
   - для unix install.sh
3. Установить необходимые библиотеки. Для этого:
   - Либо из директории **vcpkg_install** запустить скрипт:
     - для windows pkg_install.cmd
     - для unix pkg_install.sh
   - (Предпочтительный вариант) Либо открыть соответствующий файл в текстовом редакторе и установить библиотеки вручную, с учетом используемой операционной системы
      - как пример:
      ```bash
      ./vcpkg/vcpkg.exe install sdl2:x64-linux
      ``` 
5. Запустить сборку через cmake в корневой директории проекта:
      ```powershell
      cmake -B build
      cmake --build build
      ```

---

### Примерная структура проекта:

- [X] Файл main.cpp, где создаются все необходимые объекты и запускается бесконечный игровой цикл
- [X] Класс самой игры
- [X] Класс управляемого игроком персонажа
- [X] Класс для работы с текстурами
- [ ] Класс для работы с окружением (миром)
- [X] Классы для работы с противниками
- [X] Класс для работы с камерой
- [ ] Класс для работы с пользовательским вводом
- [X] Класс для работы с пользовательским интерфейсом
- [X] Класс для работы с меню
- [ ] Класс для работы с аудио (второстепенная задача)

--- 

### Структура репозитория:

- Директория **assets**: содержит спрайты для отображения игровых объектов.
- Директория **headers**: содержит header-файлы.
- Директория **src**: содержит исходный код проекта. 
- Директория **vcpkg_install**: содержит скрипты для установки vcpkg, а также необходимых библиотек для windows и unix-подобрыйх систем
- Файл **CMakeLists.txt** для установки программы.

---

### Реализованные цели:
1. Сборка самого проекта, подключение необходимых библиотек
2. README. Описание проекта, список поставленных и реализованных целей
3. Основной игровой цикл
4. Обработка пользовательского ввода, передача его в игровой цикл
5. Класс персонажа. Изменение состояния персонажа в соответствии с вводом (перемещение в пространстве, прыжки, стрельба)
6. Менеджер текстур, "натягивание" спрайтов на персонажа, противников, тайлы окружения
7. Коллизии (игрока с окружением, с противниками, противников с окружением и игроком, и т.д.)
8. Гравитация (Воздействует на игрока)
9. Анимация спрайтов
10. Менеджер для работы с камерой
11. Бесконечный повторяющийся бэкграунд с эффектом параллакса
12. Выстрелы прожектайлами (без анимации взрыва)
13. Пользовательский интерфейс (частично)
14. Противники, которые наносят урон, получают урон и погибают (без анимации и эффектов)
15. Главное меню (Без сохранения и старта новой игры)

---

### Поставленные цели:
1. Искуственный интеллект противников
2. Менеджер для работы с окружением (контроль состояния, сохранение состояния)
3. Сохранение и загрузка с помощью файлов
4. Аудио (Второстепенная задача)
5. Сделать тайлы более простым классом (Второстепенная задача)
6. Рефакторинг кода

---

P.S. Все ассеты для тестирования проекта взяты из выдачи гугла.
