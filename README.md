# Shared ptr

Реализация класса SharedPtr на языке программирования c++

Тип shared_ptr — это смарт-указатель в стандартной библиотеке C++, который предназначен для ситуаций, когда управлять
временем существования объекта в памяти требуется нескольким владельцам. После инициализации указателя shared_ptr его
можно копировать, передавать по значению в аргументах функций и присваивать другим экземплярам shared_ptr. Все
экземпляры указывают на один и тот же объект и имеют общий доступ к одному "блоку управления", который увеличивает и
уменьшает счетчик ссылок, когда указатель shared_ptr добавляется, выходит из области действия или сбрасывается. Когда
счетчик ссылок достигает нуля, блок управления удаляет ресурс в памяти и самого себя.

На схеме ниже показано несколько экземпляров shared_ptr, указывающих на одно расположение в памяти.

![](https://docs.microsoft.com/ru-ru/cpp/cpp/media/shared_ptr.png?view=msvc-170)

### Links

https://en.cppreference.com/w/cpp/memory/shared_ptr

https://docs.microsoft.com/ru-ru/cpp/cpp/how-to-create-and-use-shared-ptr-instances?view=msvc-170