# Шаблоны проектирования

## Holder (держатель, хранитель)

Проблема:

```cpp
{
    A* ptr = new A;
    ptr->f(); // создаёт исключения
    delete a; // в исключительной ситуации не удаляется
}
```

Решение:

```cpp
template <typename T>
class Holder {
    T *ptr;
public:
    Holder() { ptr = new T; }
    ~Holder() { if (ptr) delete ptr; }
    T* operator->() { return ptr; }
    T& operator*() { return *ptr; }
    operator bool() { return ptr != nullptr; }
    Holder(const Holder<T> &) = delete;
    Holder<T> &operator=(const Holder<T> &) = delete;
};
```

Теперь можно:

```cpp
{
    Holder<A> h(new A);
    h->f();
}
```

Память будет освобождаться автоматически. Возникает проблема при множественном владении указателем. Решается небольшими модификациями исходного класса, догадаться до которых несложно. В C++ реализованы следующим образом:

- `unique_ptr<Type>` - указатель существует в единственном экземпляре

- `shared_ptr<Type>` - указатель удаляется последним освободившим

- `weak_ptr<Type>` - использует уже существующий указатель, не владеет им. Создаётся от уже существующего указателя

| memory      | unique_ptr                  | shared_ptr                      | weak_ptr                          |
|:-----------:|:---------------------------:|:-------------------------------:|:---------------------------------:|
| владение    | строгое                     | совместное                      | слабое                            |
| операторы   | `*, ->, bool, []`           | `*, ->, bool, []`               | -                                 |
| копирование | нельзя                      | можно                           | можно                             |
| методы      | `get, release, reset, swap` | `get, reset, use_count, unique` | `use_count, expired, reset, lock` |

## Iterator

Итератор - специальная структура данных, привязанная к другой, "перечисляемой" структуре данных. Итератор, по своей сути, является указателем на текущий элемент. Необходим для того, чтобы не привязываться к данным, и унифицировать интерфейс взаимодействия с ними.

# Порождающие паттерны

## Factory

![](C:\Users\Jora\repo\oop\doc\Factory.jpg)

## Creator

```cpp
class Creator {
public:
    shared_ptr<Product> get() {
        if (!product) {
            product = create();
        }

        return product;
    }
}
protected:
    virtual shared_ptr<Product> create() = 0;
private:
    shared_ptr<Product> product;
}
```

## Abstract Factory

![](C:\Users\Jora\repo\oop\doc\AbstractFactory.jpg)

## Prototype

![](C:\Users\Jora\repo\oop\doc\Prototype.jpg)

## Builder

![](C:\Users\Jora\repo\oop\doc\Builder.jpg)

Агрегация может быть и на уровне конкретных объектов, если построение объекта отличается для каждого производного строителя

## Singleton

```cpp
template<typename Type>
class Singleton {
public:
    static Type& instance(); {
        static unique_ptr<Type> myInstance = make_unique<Type>();
        return *myInstance;
    }
private:
    Singleton() = delete;
    Singleton(const Singleton& other) = delete;
}
```

## Pool

![](C:\Users\Jora\repo\oop\doc\Pool.jpg)

## Singleton Pool

Говорить мы про него не будем

# Структурные паттерны

## Adapter

Выделить простой класс, для которого посредники будут представлять интерфейс работы.

![](C:\Users\Jora\repo\oop\doc\Adapter.jpg)
