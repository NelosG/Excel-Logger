//
// Created by NelosG.
//

#include <OpenXLSX.hpp>
#include <logger.h>

using namespace OpenXLSX;

logger::logger(const std::string &path) : logger(path, false) {}

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
    XLSheet shet = doc.workbook( ).sheet(name);
    return XLWorksheet(shet.get_Data( ));
}

bool logger::set_page(const std::string &name) {
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
    return ret;
}

logger &logger::next_line() {
    ++row;
    column = 1;
    return *this;
}

void logger::set_heading(const std::vector<std::string> &heading) {
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

void logger::flush() { doc.save( ); }

void logger::close() {
    if (doc.workbook( ).sheetExists("Sheet1")) {
        doc.workbook( ).deleteSheet("Sheet1");
    }
    doc.save( );
    doc.close( );
}

logger &logger::operator<<(const char &s) {
    if (s == '\n') {
        return next_line( );
    }
    return write(s);
}
