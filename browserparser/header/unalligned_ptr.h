/**
\file
\bref Заголовочный файл с описанием класса unalligned_ptr.
*/

#ifndef UNALLIGNED_PTR_H 
#define UNALLIGNED_PTR_H

#include <cstring>

/**
\bref Шаблон класса unalligned_ptr.
\details Служит для чтения объекта класса T расположенного по невыровненному адресу.
*/
template<typename T>
class unalligned_ptr final {
public:
    /**
    \bref Коструктор.
    \details Инициализация указателя. 
    */
    explicit unalligned_ptr(const uint8_t *pointer) : ptr(pointer) { };
    /**
    \bref Оператор непрямого обращения. 
    \details .    
    */
    T operator*() const {
        T value;
        std::memcpy(&value, ptr, sizeof(T));
        return value; 
    }
    /**
    \bref Деструктор.
    \details .
    */
    ~unalligned_ptr() noexcept = default;    
private:
    /**
    \bref Коструктор копирования.
    \details удален.
    */
    unalligned_ptr(const unalligned_ptr &) = delete;
    /**
    \bref Коструктор перемещения.
    \details удален.
    */
    unalligned_ptr(unalligned_ptr &&) = delete;
    /**
    \bref Оператор присваивания копированием.
    \details удален.
    */
    unalligned_ptr& operator=(const unalligned_ptr &) = delete;
    /**
    \bref Оператор присваивания перемещением.
    \details удален.
    */
    unalligned_ptr& operator=(unalligned_ptr &&) = delete;
    /**
    \bref Указатель объекта класса T.
    \details .
    */
    const uint8_t *ptr = nullptr;    
};

#endif  /* UNALLIGNED_PTR_H */

