// From https://en.cppreference.com/w/cpp/language/template_specialization
#include <iostream>
#include <string>
#include <vector>

namespace {

  template <typename T>
  struct is_void : std::false_type  {
    //nothing
  };

  template<>  // explicit specialization for T = void
  struct is_void<void> : std::true_type {
    // also nothing
  };


  template <typename T>
  void show_stuff(std::string_view tag, const std::vector<T>& v) {
    std::cout << tag << " size = " << v.size() << std::endl;
    for (int i = 0; i < v.size(); ++i) {
      std::cout << tag << "[" << i << "] = " << v.at(i) << std::endl;
    }
  }

  template <typename T>
  std::vector<T> make_stuff(int n) {
    std::vector<T> empty;
    return empty;
  }

  template <>
  std::vector<std::string> make_stuff<std::string>(int n) {
    std::vector<std::string> result;
    result.push_back("make_stuff()");
    result.push_back("was called");
    result.push_back("with");
    result.push_back(std::to_string(n));
    return result;
  }

  template <>
  std::vector<int> make_stuff<int>(int n) {
    std::vector<int> result;
    for (int k = 0; k < n; ++k) {
      result.push_back(k*k);
    }
    return result;
  }

  
}  // namespace

int main(int argc, char* argv[]) {
  // for any type T other than void, the 
  // class is derived from false_type
  std::cout << "is_void<char>::value = " << is_void<char>::value << std::endl; 
  // but when T is void, the class is derived
  // from true_type
  std::cout << "is_void<void>::value = " << is_void<void>::value << std::endl;
  // Explicit specialisation of functions.
  std::vector<bool> bv = make_stuff<bool>(10);
  std::vector<std::string> sv = make_stuff<std::string>(10);
  std::vector<int> iv = make_stuff<int>(10);
  show_stuff("bv", bv);
  show_stuff("sv", sv);
  show_stuff("iv", iv);
  return 0;
}
