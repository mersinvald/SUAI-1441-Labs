#ifndef INTERNATIONALID_H
#define INTERNATIONALID_H
#include "document.hpp"

enum {
    DocType_InternetionalID = 2
};

class InternationalID : public AbstractDatedDocument {
public:
    explicit InternationalID(int type)
        : AbstractDatedDocument(type), startDate(0), endDate(0) {}

    virtual void          promt();
    virtual std::ostream& write (std::ostream& os) const;
    virtual std::istream& read (std::istream& is);

protected:
    time_t startDate;
    time_t endDate;
};

struct InternationalIDCreator : public AbstractDocumentCreator {
    using AbstractDocumentCreator::AbstractDocumentCreator;
    static struct Initializer {
        Initializer();
    } initializer;
    virtual DocumentPointer operator()();
};

#endif // INTERNATIONALID_H
