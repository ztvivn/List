#include <iostream>

template<class Type>
class Node
{
private:
    Type data;
public:
    Node(Type data) { this->data = data; }
    Type &getData() { return data; }
    Node<Type> *ptr_next = nullptr;
};

template<class Type>
class List
{
private:
    Node<Type> *ptr_first = nullptr;
    void sort_merge_copy(Type *arr, int size_arr);//метод для упращения работы с сортировкой слиянием, но потерям по памяти
public:
    void push_back(Type data);//добавление элемента в конец списка
    void push_front(Type data);//добавление в начало
    int size_list();//вывод общего числа элементов
    void out_all();//вывод всех элементов
    void delet(int index);//удаление элемента по индексу
    void delet_front();//удаление первого элемента
    void delet_back();//удаление последнего элемента

    Type &operator[](int index);//Перегруженный оператор для объекта

    void sort_bubble();//сортировка по возрастанию (Пузырьковая)
    void sort_insert();//сортировка по возрастанию (Вставками)
    void sort_select();//сортировка по возрастанию (Выбором)
    void sort_merge();//сортировка по возрастанию  (Слиянием)
};

template<class Type>
void List<Type>::push_back(Type data)
{
    if(ptr_first == nullptr)
    {
        ptr_first = new Node<Type>(data);

        return;
    }

    Node<Type> *ptr_first_cope = ptr_first;

    while(ptr_first_cope->ptr_next)
    {
        ptr_first_cope = ptr_first_cope->ptr_next; 
    }

    ptr_first_cope->ptr_next = new Node<Type>(data);

}

template<class Type>
void List<Type>::out_all()
{
    if(ptr_first == nullptr)
    {
        std::cout << "Элементов нет!\n";

        return;
    }

    Node<Type> *ptr_first_cope = ptr_first;

    while(ptr_first_cope->ptr_next)
    {
        std::cout << ptr_first_cope->getData() << " ";

        ptr_first_cope = ptr_first_cope->ptr_next;
    }

    std::cout << ptr_first_cope->getData() << " ";
    std::cout << std::endl;
}

template<class Type>
void List<Type>::delet(int index)
{
    if(ptr_first == nullptr)
    {
        std::cout << "Элементов нет!\n";
        return;
    }

    Node<Type> *ptr_first_cope = ptr_first;
    Node<Type> *ptr_prev = nullptr;

    if(index == 0)//удаление первого элемента
    {
        ptr_first = ptr_first->ptr_next;
        delete ptr_first_cope;
        return;
    }

    for (int i = 0; i < index; ++i)
    {
        if(ptr_first_cope->ptr_next == nullptr)
        {
            std::cout << "Вы вышли за границы списка!\n";
            return;
        }
        ptr_prev = ptr_first_cope;
        ptr_first_cope = ptr_first_cope->ptr_next;
    }

    if(ptr_first_cope->ptr_next == nullptr)//удаление последнего элемента
    {
        delete ptr_first_cope;
        ptr_prev->ptr_next = nullptr;
        return;
    }

    ptr_prev->ptr_next = ptr_first_cope->ptr_next;
    ptr_first_cope->ptr_next = nullptr;
    delete ptr_first_cope;

}

template<class Type>
void List<Type>::push_front(Type data)
{
    Node<Type> *ptr_first_cope = ptr_first;
    ptr_first_cope = new Node<Type>(data);
    ptr_first_cope->ptr_next = ptr_first;
    ptr_first = ptr_first_cope;
    ptr_first_cope = nullptr;
}

template<class Type>
void List<Type>::delet_front()
{
    if(ptr_first == nullptr)
    {
        std::cout << "Элементов нет!\n";
        return;
    }

    Node<Type> *ptr_first_cope = ptr_first;
    ptr_first = ptr_first->ptr_next;
    ptr_first_cope->ptr_next = nullptr;
    delete ptr_first_cope;
}

template<class Type>
void List<Type>::delet_back()
{
    if(ptr_first == nullptr)
    {
        std::cout << "Элементов нет!\n";
        return;
    }

    if(ptr_first->ptr_next == nullptr)
    {
        delet_front();
        return;
    }

    Node<Type> *ptr_first_cope = ptr_first;
    Node<Type> *ptr_prev = nullptr;

    while(ptr_first_cope->ptr_next)
    {
        ptr_prev = ptr_first_cope;
        ptr_first_cope = ptr_first_cope->ptr_next;
    }

    ptr_prev->ptr_next = nullptr;
    delete ptr_first_cope;
}

template<class Type>
int List<Type>::size_list()
{
    int size = 0;
    if(ptr_first == nullptr)
    {
        return size;
    }

    ++size;

    Node<Type> *ptr_first_cope = ptr_first;

    while(ptr_first_cope->ptr_next)
    {
        ++size;
        ptr_first_cope = ptr_first_cope->ptr_next;
    }

    return size;
}

template<class Type>
Type &List<Type>::operator[](int index)
{
    if(ptr_first == nullptr || index < 0)
    {
        std::cout << "Вы вышли за границы списка!\n";
        exit(0);
    }

    Node<Type> *ptr_first_cope = ptr_first;

    for (int i = 0; i < index; ++i)
    {
        if(ptr_first_cope->ptr_next == nullptr)
        {
            std::cout << "Вы вышли за границы списка!\n";
            exit(0);
        }
        ptr_first_cope = ptr_first_cope->ptr_next;
    }

    return ptr_first_cope->getData();
}

template<class Type>
void List<Type>::sort_bubble()
{
    if(typeid(Type) != typeid(int) && typeid(Type) != typeid(double))
    {
        std::cout << "Данный тип нельзя отсортировать.Возможный тип(int, double)!\n";
        return;
    }

    Type swap = 0;

    for(int size = size_list() - 1; size > 0; --size)
    {
        for(int number = 0; number < size; ++number)
        {
            if((*this)[number] > (*this)[number + 1])
            {
                swap = (*this)[number];
                (*this)[number] = (*this)[number + 1];
                (*this)[number + 1] = swap;
            }
        }
    }
}

template<class Type>
void List<Type>::sort_insert()
{
    if(typeid(Type) != typeid(int) && typeid(Type) != typeid(double))
    {
        std::cout << "Данный тип нельзя отсортировать.Возможный тип(int, double)!\n";
        return;
    }

    Type swap = 0;

    for (int size = 0; size < size_list(); ++size)
    {
        for (int index = size; index != 0; --index)
        {
            if((*this)[index] < (*this)[index - 1])
            {
                swap = (*this)[index];
                (*this)[index] = (*this)[index - 1];
                (*this)[index - 1] = swap;
            }
        }
    }
}

template<class Type>
void List<Type>::sort_select()
{
    if(typeid(Type) != typeid(int) && typeid(Type) != typeid(double))
    {
        std::cout << "Данный тип нельзя отсортировать.Возможный тип(int, double)!\n";
        return;
    }

    Type swap_index = 0;
    Type swap_copy = 0;

    for (int size = size_list() - 1; size > 0; --size)
    {
        swap_index = 0;
        for (int index = 0; index < size; ++index)
        {
            if((*this)[swap_index] < (*this)[index + 1])
            {
                swap_index = index + 1;
            }
        }

        swap_copy = (*this)[size];
        (*this)[size] = (*this)[swap_index];
        (*this)[swap_index] = swap_copy;
    }
}

template<class Type>
void List<Type>::sort_merge_copy(Type *arr, int size_arr)
{
    if(size_arr <= 1)
    {
        return;
    }

    int size_left = size_arr / 2;
    int size_right = size_arr - size_left;

    Type arr_left[size_left];
    Type arr_right[size_arr - size_left];

    int index_arr = 0;
    for ( ; index_arr < size_left; ++index_arr)
    {
        arr_left[index_arr] = arr[index_arr];
    }

    for (int index = 0 ; index_arr < size_arr; ++index_arr, ++index)
    {
        arr_right[index] = arr[index_arr];
    }

    sort_merge_copy(arr_left, size_left);
    sort_merge_copy(arr_right, size_right);

    int index_left = 0, index_right = 0;

    for (int counter = 0; counter < size_arr; ++counter)
    {
        if((arr_left[index_left] <= arr_right[index_right] && size_left > index_left) || index_right == size_right)
        {
            arr[counter] = arr_left[index_left];
            ++index_left;
        }else if((arr_right[index_right] < arr_left[index_left] && size_right > index_right) || index_left == size_left)
        {
            arr[counter] = arr_right[index_right];
            ++index_right;
        }
    }
}

template<class Type>
void List<Type>::sort_merge()
{
    if(typeid(Type) != typeid(int) && typeid(Type) != typeid(double))
    {
        std::cout << "Данный тип нельзя отсортировать.Возможный тип(int, double)!\n";
        return;
    }

    Type arr[size_list()];
    for(int i = 0; i < size_list(); i++)
    {
        arr[i] = (*this)[i];
    }

    sort_merge_copy(arr, size_list());

    for (int i = 0; i < size_list(); ++i)
    {
        (*this)[i] = arr[i];
    }
}



int main() 
{
    List<std::string> list;

    list.push_back("dsfg");
    list.push_back("s");
    list.push_back("ggg");
    list.push_back("h");

    list.out_all();
    list.sort_merge();
    list.out_all();

    return 0;
}
