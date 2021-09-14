#ifndef RESIZABLEARRAY_H
#define RESIZABLEARRAY_H

template <typename T>
class ResizableArray
{
    private:
        int maxSize;
        int currentSize;
        T* array;

        void enlargeArray();

    public:
        ResizableArray(int newSize = 128);

        void push(T newItem);

        T operator[](T index);

        void swap(int firstIndex, int secondIndex);

        void moveToTop(int lastEntry);

        ~ResizableArray();
};

#endif