#include "common.h"

 /** INTERFACE SEGREGATION PRINCIPLE
 *
 * Do not create interfaces that are too large and implement too much.
 */

struct Document;

/**
 * This is the interface for a machine that scans, faxes, prints, etc.
 */
struct IMachine {
    virtual void print(Document &doc) = 0;
    virtual void scan(Document &doc) = 0;
    virtual void fax(Document &doc) = 0;
};

/**
 * Full implementation: OK.
 */
struct MFP : IMachine {
    void print(Document &doc) override {

    }

    void scan(Document &doc) override {

    }

    void fax(Document &doc) override {

    }
};

/**
 * Problem: what if you only need to implement just a scanner?
 * You are sending the client the idea that you have a machine that can do all these things, which is false.
 * Interfaces should be segregated.
 */
struct Scanner : IMachine {
    void print(Document &doc) override {
        throw "Not implemented.";
    }

    /**
     * This is the only function that will give something meaningful to the client.
     */
    void scan(Document &doc) override {

    }

    void fax(Document &doc) override {
        // ...or just leave empty.
    }
};

int main() {

}