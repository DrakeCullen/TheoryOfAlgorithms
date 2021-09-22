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

        T* getElement(int index);

        void calculateSize();

        void swap(int firstIndex, int secondIndex);

        void insert(T newItem);

        T pop();

        ~ResizableArray();
};

#endif