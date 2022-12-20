//
// Created by NelosG.
//

#include <OpenXLSX.hpp>
#include <logger.h>

using namespace OpenXLSX;

logger::logger(const std::string &path, bool add) {
    try {
        if (add) {
            doc.open(path);
            return;
        }
    } catch (...) {
    }
    doc.create(path);
}

XLWorksheet get_sheet(const XLDocument &doc, const std::string &name) {
    return doc.workbook( ).sheet(name);
}

bool logger::set_page(const std::string &name) {
    check_state();
    bool ret = false;
    if (sheet_init && sheet.name( ) == name) {
        return ret;
    }
    if (!doc.workbook( ).worksheetExists(name)) {
        doc.workbook( ).addWorksheet(name);
        ret = true;
    }
    sheet = get_sheet(doc, name);
    row = 1;
    column = 1;
    sheet_init = true;
    if(just_created) {
        if (doc.workbook( ).sheetExists("Sheet1")) {
            doc.workbook( ).deleteSheet("Sheet1");
        }
        just_created = false;
    }
    return ret;
}

logger &logger::next_line() {
    check_state();
    ++row;
    column = 1;
    return *this;
}

void logger::set_heading(const std::vector<std::string> &heading) {
    check_state();
    int row_temp = row;
    int column_temp = column;
    row = 1;
    column = 1;

    for (const auto &i : heading) {
        write(i);
    }

    row = row_temp == 1 ? 2 : row_temp;
    column = column_temp;
}

void logger::set_page(const std::string &name,
                      const std::vector<std::string> &heading) {
    set_page(name);
    set_heading(heading);
}

void logger::flush() {
    check_state();
    doc.save( );
}

void logger::close() {
    if(!closed) {
        doc.save( );
        doc.close( );
        closed = true;
    }
}

logger &logger::operator<<(const char &s) {
    check_state();
    if (s == '\n') {
        return next_line( );
    }
    return write(s);
}

void logger::check_state() const {
    if(closed) {
        throw std::runtime_error("Illegal state.");
    }
}
