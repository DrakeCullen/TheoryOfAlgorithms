#include <iostream>
#include <climits>

using namespace std;

template <typename T>
class DynamicArray
{
    private:
        int maxSize;
        int currentSize;
        T* array;

        void enlargeArray() 
        {
            maxSize *= 2;
            T* newArray = new T[maxSize];

            for (int i = 0; i < currentSize; i++)
                newArray[i] = array[i];
            
            
            delete[] array;
            array = newArray;
        }

    public:
        DynamicArray(int newSize = 2)
        {
            maxSize = newSize;
            currentSize = 0;
            array = new T[newSize];
        }

        void push(T newItem)
        {
            if (currentSize + 1 == maxSize)
                enlargeArray();
            
            array[currentSize++] = newItem;
        }

        T operator[](T index)
        {
            if (index >= 0 && index < maxSize)
                return array[index];
            return -1;
        }

        void swap(int firstIndex, int secondIndex)
        {
            T temp = array[firstIndex];
            array[firstIndex] = array[secondIndex];
            array[secondIndex] = temp;
        }

        void moveToTop(int firstIndex, int secondIndex)
        {
            array[firstIndex] = array[secondIndex];
            array[secondIndex] = INT_MAX;
        }

        ~DynamicArray()
        {
            delete[] array;
            array = nullptr;
        }
};

template <typename T> 
class PriorityQueue 
{
    private:
        DynamicArray<T> array;
        int currentIndex = 0;


        void moveUp()
        {
            int i = currentIndex;
            
            while (array[i] < array[(i - 1) / 2] && i >= 0) 
            {
                array.swap(i, (i - 1) / 2);
                i = (i - 1) / 2;
            }
        }

        T getLeftChild(int index)
        {
            if (2 * index + 1 < currentIndex)
                return array[2 * index + 1];
            else 
                return array[index];
        }

        T getRightChild(int index)
        {
            if (2 * index + 1 < currentIndex)
                return array[2 * index + 2];
            else 
                return array[index];
        }

        void moveDown()
        {
            int index = 0;
            T current, leftChild, rightChild;

            do
            {
                T current = array[index];
                T leftChild = getLeftChild(index);
                T rightChild = getRightChild(index);

                if (leftChild <= rightChild && leftChild < current)
                {
                    array.swap(index, 2 * index + 1);
                    index = 2 * index + 1;
                }

                else if (rightChild < current)
                {
                    array.swap(index, 2 * index + 2);
                    index = 2 * index + 2;
                }
            }
            while (index * 2 + 1 < currentIndex && (array[index] > getLeftChild(index) || array[index] > getRightChild(index)));
        }

    public:
        PriorityQueue() 
        {

        }

        void push(T newItem)
        {
            array.push(newItem);
            moveUp();
            currentIndex++;
        }

        T pop()
        {
            T topValue = array[0];
            currentIndex--;
            array.moveToTop(0, currentIndex);
            moveDown();
            return topValue;
        }

        int getSize()
        {
            return currentIndex;
        }

        void print()
        {
            for (int i = 0; i < currentIndex; i++)
                cout<<array[i]<<' ';
            cout<<endl;
        }
};

int main() 
{
    PriorityQueue<int> da;

    da.push(45);
    da.push(20);
    da.push(14);
    da.push(12);
    da.push(31);
    da.push(7);
    da.push(11);
    da.push(13);
    da.push(7);

    while(da.getSize())
        cout<<da.pop()<<' ';
}