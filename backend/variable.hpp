#ifndef __VARIABLE_HPP__
#define __VARIABLE_HPP__

using namespace std;

template<typename T>
class variable {
    private:
        T value;
    public:
        T get_value();
        void update_value(T value);
}

#endif
