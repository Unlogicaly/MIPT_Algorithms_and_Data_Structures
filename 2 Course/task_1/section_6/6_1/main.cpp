#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

template <typename T, class Cmp = std::less<T>>
class Heap {
  private:
    Cmp cmp;

    std::vector<T> heap;

    void ShiftUp(size_t index) {

        if (index > heap.size())
            return;

        while (index != 0 && cmp(heap[index], heap[Parent(index)])) {
            std::swap(heap[index], heap[Parent(index)]);
            index = Parent(index);
        }
    }

    size_t GetSwapIndex(size_t childIndex, size_t swapIndex) {

        if (childIndex < heap.size() && cmp(heap[childIndex], heap[swapIndex])) {
            swapIndex = childIndex;
        }
        return swapIndex;
    }

    void ShiftDown(size_t index) {

        while (index < heap.size()) {
            size_t swapIndex = index;
            swapIndex = GetSwapIndex(Left(index), swapIndex);
            swapIndex = GetSwapIndex(Right(index), swapIndex);
            if (swapIndex != index) {
                std::swap(heap[index], heap[swapIndex]);
                index = swapIndex;
            }
            else {
                break;
            }
        }
    }

  public:
    Heap() = default;

    explicit Heap(const std::vector<T> &arr) : heap(arr) {

        for (size_t i = (heap.size() >> 1); i > 0; --i) {
            ShiftDown(i - 1);
        }
    }

    explicit Heap(const Heap<T> &rhs) : heap(rhs.heap) {}

    Heap(Heap &&rhs) noexcept : heap(std::move(rhs.heap)) {}

    Heap &operator=(const Heap<T> &rhs) {

        if (this != &rhs) {
            heap = rhs.heap;
        }
        return *this;
    }

    Heap &operator=(Heap<T> &&rhs) {

        if (this != &rhs) {
            heap = std::move(rhs.heap);
        }
    }

    bool operator==(const Heap &rhs) const {

        return heap == rhs.heap;
    }

    size_t Parent(size_t index) const {

        return (index - 1) >> 1;
    }

    size_t Left(size_t index) const {

        return (index << 1) + 1;
    }

    size_t Right(size_t index) const {

        return (index + 1) << 1;
    }

    bool empty() const {

        return heap.empty();
    }

    const T &top() const {

        return heap[0];
    }

    void pop() {

        if (!heap.empty()) {
            std::swap(heap.front(), heap.back());
            heap.resize(heap.size() - 1);
            ShiftDown(0);
        }
    }

    void add(const T &element) {

        heap.push_back(element);
        ShiftUp(heap.size() - 1);
    }

    size_t size() {

        return heap.size();
    }
};

int main() {

    std::ios::sync_with_stdio(false);

    uint_fast64_t n;
    std::cin >> n;

    Heap<int_fast32_t, std::greater<>> heap;

    for (auto i = 0; i < n; ++i) {
        int tmp;
        std::cin>>tmp;
        heap.add(tmp);
    }

    int k;
    std::cin >> k;

    int res = 0;

    while(!heap.empty()) {
        int cur_sum = 0;
        std::vector<int_fast32_t >buffer;
        while (!heap.empty() and cur_sum + heap.top() <= k) {
            cur_sum += heap.top();
            if (heap.top() != 1)
                buffer.push_back(heap.top() / 2);
            heap.pop();
        }

        for (auto i: buffer) {
            heap.add(i);
        }

        ++res;
    }

    std::cout << res;

    return 0;
}
