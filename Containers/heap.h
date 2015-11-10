#include <vector>
#include <ostream>
#include <algorithm>

template<typename T>
class BinaryHeap{
      static const unsigned top = 0;
   public:
      BinaryHeap() : heap() {}

      int size() const {return heap.size() - 1;}
      void push(const T& data) {
         heap.push_back(data);
         siftUp(size());
      }
      void pop(){
         std::swap(heap[top], heap[size()]);
         heap.pop_back();
         siftDown(top);
      }
      T peek() const {return heap[top];}
      bool isEmpty() const {return heap.empty();}

      void heapify(const std::vector<T> elements){
         heap.assign(elements.begin(), elements.end());
         int current = getParent(heap.size());
         while (current >= 0){
            siftDown(current);
            --current;
         }
      }

      void heapsort(std::vector<T>& elements){
         heapify(elements);
         elements.clear();
         while (!heap.empty()){
            T first = peek(); pop();
            elements.push_back(first);
         }
      }
      typename std::vector<T>::iterator begin() {return heap.begin();}
      typename std::vector<T>::iterator end() {return heap.end();}
   private:
      std::vector<T> heap;

      void siftUp(int index);
      void siftDown(int index);
      static int getParent(int index) {return (index - 1) / 2;}
      static int leftChild(int index) {return 2 * index + 1;}
      static int rightChild(int index) {return 2 *(index + 1);}
};

template<typename T>
std::ostream& operator<<(std::ostream& out, BinaryHeap<T> binheap){
   if (binheap.isEmpty()){
      out << "[]";
      return out;
   }
   typename std::vector<T>::const_iterator iter = binheap.begin();
   out << "[";
   for (;iter != binheap.end() - 1; ++iter){
      out << *iter << ", ";
   }
   out << *(binheap.end() - 1) << "]";
}

template<typename T>
void BinaryHeap<T>::siftUp(int index){
   int current = index;
   int parent = getParent(current);
   while (current >= top && heap[current] > heap[parent]){
      std::swap(heap[current], heap[parent]);
      current = parent;
      parent = getParent(current);
   }

}

template<typename T>
void BinaryHeap<T>::siftDown(int index){
   int current = index;
   int left = leftChild(current), right = rightChild(current);

   while ((left <= size() && heap[current] < heap[left]) ||
          (right <= size() && heap[current] < heap[right])){
      if (left <= size() && right <= size()){
         if (heap[left] < heap[right]){
            std::swap(heap[current], heap[right]);
            current = right;
            left = leftChild(current); right = rightChild(current);
         }
         else {
            std::swap(heap[current], heap[left]);
            current = left;
            left = leftChild(current); right = rightChild(current);
         }
      }
      else if (left <= size()){
         std::swap(heap[current], heap[left]);
         current = left;
         left = leftChild(current); right = rightChild(current);
      }
      else if (right <= size()){
         std::swap(heap[current], heap[right]);
         current = right;
         left = leftChild(current); right = rightChild(current);
      }
   }
}
