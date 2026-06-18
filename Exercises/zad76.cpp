#include <iostream>
#include <utility>
#include <vector>
#include <stdexcept>
using namespace std;

template <typename T>
class MoveStack
{
private:
    vector<T> data;
public:
    MoveStack() noexcept {}

    MoveStack(const MoveStack& other) = delete;
    MoveStack& operator=(const MoveStack& other) = delete;

    MoveStack(MoveStack&& other) noexcept {
        data = move(other.data);
    }

    MoveStack& operator=(MoveStack&& other) noexcept {
        if(this != &other) {
            data = move(other.data);
        }

        return *this;
    }

    void push(T&& element) {
        data.push_back(move(element));
    }

    T pop() {
        if(empty()) {
            throw runtime_error("Stack is empty");
        }

        T result = move(data.back());
        data.pop_back();
        return result;
    }

    bool empty() const {
        return data.empty();
    }
};

int main()
{
    try
    {
        MoveStack<int> st;
        cout << st.pop() << endl;
    }
    catch (const runtime_error& e)
    {
        cerr << e.what() << endl;
    }

    return 0;
}