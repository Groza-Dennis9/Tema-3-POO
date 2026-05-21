#ifndef TEMA_3_POO_RESOURCELOADEXCEPTION_H
#define TEMA_3_POO_RESOURCELOADEXCEPTION_H

#include <exception>
#include <string>

using namespace std;

class ResourceLoadException : public exception {
private:
    string message;
public:
    explicit ResourceLoadException(const string& file)
        : message("Critical Error: Nu s-a putut incarca resursa din fisierul: " + file) {}

    [[nodiscard]] const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif //TEMA_3_POO_RESOURCELOADEXCEPTION_H