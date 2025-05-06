#include<string>
#include<iostream>
#include<unordered_map>

template<typename KEY, typename VALUE, typename HashFunction = std::hash<KEY>>
class MyHashMap{
    private:
        std::unordered_map<KEY, VALUE, HashFunction> _hash;

    public:
    VALUE& operator[](KEY key){
        return _hash[key];
    }
};

class MyIntHashFunction {
    public:
        size_t operator()(int i) const
        {
            return i % 10;
        }
};

class MyStringHashFunction {
    public:
        size_t operator()(const std::string& str) const
        {
            if (str == "")
                return 'a' % 10;
            else 
                return str[0] % 10;
        }
};

int main()
{
    MyHashMap<int, int, MyIntHashFunction> intHash;
    MyHashMap<std::string, std::string, MyStringHashFunction> strHash;
    intHash[1] = 11;
    intHash[2] = 12;
    intHash[3] = 13;

    // Add one case to demonstrate hash collision
    intHash[13] = 100; // key=13 collides with key=3 as for both the custom hash returns 3 (mod 10).

    strHash["abc"] = "cde";
    strHash["bcd"] = "fgh";
    strHash["cde"] = "ijk";

    // Add one case to demonstrate hash collision
    strHash["cxx"] = "some_string";   // collides with key=cde as 
                                      // for both the custom hash returns ('c' % 10) (mod 10). 

    return 0;
}