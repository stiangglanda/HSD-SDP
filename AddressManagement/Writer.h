#ifndef WRITER_H
#define WRITER_H
#include <fstream>
#include <string>

class AddressManager;

class Writer {
public:
    virtual ~Writer() = default;
    virtual void WriteHeader(std::ofstream & out) = 0;
    virtual void WriteFooter(std::ofstream & out) = 0;

    void Write(const std::string& path, AddressManager& man);
};

#endif
