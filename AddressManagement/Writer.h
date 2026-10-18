#ifndef WRITER_H
#define WRITER_H
#include <string>

class AddressManager;

class Writer {
public:
    void Write(std::string path,  AddressManager& man);
};

#endif
