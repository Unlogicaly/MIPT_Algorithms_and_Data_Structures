#include <iostream>
#include <vector>
#include <algorithm>

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

    std::vector<std::pair<int_fast32_t , int_fast32_t >> a(n);

    std::sort(a.data(), a.data() + a.size(), [](std::pair<int, int> lhs, std::pair<int, int> rhs) {
        return lhs.first < rhs.first;
    });

    for (auto i = 0; i < n; ++i) {
        std::cin >> a[i].first >> a[i].second;
    }

    Heap<int_fast32_t> src;

    uint_fast64_t max_load = 0;

    for (auto i = 0; i < n; ++i) {

        auto arr = a[i].first, dep = a[i].second;

        if (src.empty()) {
            src.add(dep);
        }

        else if (arr <= src.top()) {
            src.add(dep);
        }
        else {
            max_load = std::max(max_load, src.size());
            while (!src.empty() and arr > src.top()) {
                src.pop();
            }
            src.add(dep);
        }
    }

    max_load = std::max(max_load, src.size());

    std::cout << max_load;

    return 0;
}