#include "common.h"

 /** INTERFACE SEGREGATION PRINCIPLE
 *
 * Do not create interfaces that are too large and implement too much.
 */

struct Document;

/**
 * Separate interfaces for everything.
 */
struct IPrinter {
    virtual void print(Document &doc) = 0;
};

struct IScanner {
    virtual void scan(Document &doc) = 0;
};

struct IFaxer {
    virtual void fax(Document &doc) = 0;
};

/**
 * Full implementation: OK.
 */
struct MFP : IPrinter, IScanner, IFaxer {
    void print(Document &doc) override {

    }

    void scan(Document &doc) override {

    }

    void fax(Document &doc) override {

    }
};

/**
 * Now you can implement just a scanner.
 */
struct Scanner : public IScanner {
    /**
     * This is the only function that will give something meaningful to the client.
     */
    void scan(Document &doc) override {

    }
};

/**
 * You can have an IMachine interface for printer / scanners.
 */
struct IMachine : IPrinter, IScanner {};


/**
 * You can actually make a decorator - which we will learn later one.
 */
struct Machine : IMachine {
    // We already have references to implementations of the printing and scanning, say, so this is a decorator for them.
    IPrinter &printer;
    IScanner &scanner;

    Machine(IPrinter &printer, IScanner &scanner) : printer(printer), scanner(scanner) {}

    void print(Document &doc) override {
        printer.print(doc);
    }

    void scan(Document &doc) override {
        scanner.scan(doc);
    }
};

int main() {

}