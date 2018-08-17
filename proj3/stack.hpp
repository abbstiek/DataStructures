using namespace std;

template <typename T>
Stack<T>::Stack() {
   v.reserve(30);
    }

template <typename T>
Stack<T>::~Stack () {
    v.clear();
   }

template <typename T>
Stack<T>::Stack(const Stack<T>& rhs) {
    v = rhs.v;
    }

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack <T>& rhs) {
    v = rhs.v;
    }

template <typename T>
bool Stack<T>::empty() const {
    if(v.size() < 1)
        return true;
    else
        return false;
    }

template <typename T>
void Stack<T>::clear() { v.clear(); }

template <typename T>
void Stack<T>::push(const T& x) { v.push_back(x); }

template <typename T>
void Stack<T>::pop() { v.pop_back(); }

template <typename T>
T& Stack<T>::top() {
    if(v.size() > 0 )
        return  v.at(v.size() - 1);
        }

template <typename T>
const T& Stack<T>::top() const {
    if(v.size() > 0 )
        return v.at(v.size() - 1);
        }

template <typename T>
int Stack<T>::size() const { return v.size(); }

template <typename T>
void Stack<T>::print(std::ostream& os, char ofc) const {

    if(!this->empty()) {
        typename std::vector<T>::const_iterator it = v.begin();
        for ( it = v.begin() ; it != v.end(); it++ ) {
            os << *it << ofc;
        }
    }
}

template <typename T>
std::ostream& operator<< (std::ostream& os, const Stack<T>& a){
    a.print(os);
    return os;
    }

template <typename T>
bool operator== (const Stack<T>& lhs, const Stack <T>& rhs) {
    if(lhs.size() != rhs.size())
        return false;

    Stack<T> a = lhs;
    Stack<T> b = rhs;
    while(a.size() > 0){
        if(a.top() != b.top())
            return false;
        a.pop(); b.pop();
        }
    return true;
}

template <typename T>
bool operator!= (const Stack<T>& lhs, const Stack <T>& rhs){ return !(lhs == rhs); }

template <typename T>
bool operator< (const Stack<T>& lhs, const Stack <T>& rhs){
    Stack<T> a = lhs;
    Stack<T> b = rhs;
    while(a.size() > 0 && b.size() > 0){
        if(a.top() >= b.top())
            return false;
        a.pop(); b.pop();
        }
    return true;
}