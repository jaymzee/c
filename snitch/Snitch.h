#ifndef SNITCH_H
#define SNITCH_H

class Snitch {
private:
    int _id;
protected:
    static bool _logging_enabled;
    void log(const char *msg);
public:
    Snitch() : Snitch(0) {}
    Snitch(int id) : _id(id) { log("S::ctor"); }
    Snitch(const Snitch& src) : _id(src._id) { log("S::ctor [copy]"); }
    Snitch(Snitch&& src) : _id(src._id) { log("S::ctor [move]"); }
    ~Snitch() { log("S::dtor"); }
    Snitch& operator=(const Snitch& src);
    Snitch& operator=(Snitch&& src);
    int get_id() { return _id; }
    static void disable_log();
    static void enable_log();
};

#endif
