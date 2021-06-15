//
// Created by NelosG.
//

#ifndef LOGGER_H
#define LOGGER_H
#include <OpenXLSX.hpp>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace OpenXLSX;

class logger {
    XLDocument doc;
    XLWorksheet sheet;
    bool sheet_init = false;
    int row = 1, column = 1;

public:
    explicit logger(const std::string &path);

    bool set_page(const std::string &name);// true if already exists, if false you must can set_heading
    void set_heading(const std::vector<std::string> &heading);
    void set_page(const std::string &name, const std::vector<std::string> &heading);

    logger &next_line();

    void close();

    void flush();

    template<typename T>
    logger &write(const T &s) {
        sheet.cell(XLCellReference(row, column++)).value() = s;
        return *this;
    }

    template<typename T, typename... Args>
    logger &write(const T &s, Args... ss) {
        return write(s), write(ss...);
    }
    template<typename T>
    logger &writeln(const T &s) {
        logger &ret = write(s);
        next_line();
        return ret;
    }
    template<typename T, typename... Args>
    logger &writeln(const T &s, Args... ss) {
        logger &ret = (write(s), write(ss...));
        next_line();
        return ret;
    }

    template<typename T>
    logger &operator<<(T s) {
        return write(s);
    }
};


#endif//LOGGER_H
