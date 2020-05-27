#ifndef SNITCH_H
#define SNITCH_H

class Snitch {
private:
    int _id;
protected:
    static bool _logging_enabled;
    void log(const char *msg);
public:
    Snitch(int id = 0);
    Snitch(const Snitch& src) noexcept;
    Snitch(Snitch&& src) noexcept;
    ~Snitch();
    Snitch& operator=(const Snitch& src);
    Snitch& operator=(Snitch&& src);
    int get_id() const;
    static void disable_log();
    static void enable_log();
};

#endif
