#ifndef QtCore_h
#define QtCore_h

#include <string>
#include <vector>
#include <sstream>
#include <regex.h>
#include <sys/time.h>
#include <map>

typedef unsigned short ushort;


class QChar
{
public:
    QChar(char val = 0)
        : value(val)
    {}

    operator char() const
    {
        return static_cast<char>(value);
    }

    ushort unicode() const
    {
        return value;
    }
    bool isLetterOrNumber() const
    {
        return isalnum(value);
    }

    char toAscii() const
    {
        return value;
    }

    bool isSpace() const
    {
        return isspace(value);
    }

    enum Category {
        NoCategory,
        Other_Control
    };

    Category category() const
    {
        return NoCategory;
    }

    char value;
};

class QStringList;
class QString : public std::string
{
public:
    QString(const char *str)
        : std::string(str)
    {}
    QString(const char *str, int len)
        : std::string(str, len)
    {}

    QString()
    {}
    explicit QString(char ch)
        : std::string(&ch, 1)
    {}

    QString(const std::string &str)
        : std::string(str)
    {}
    bool isNull() const
    {
        return empty();
    }

    int toInt() const
    {
        return atoi(constData());
    }


    const char *constData() const
    {
        return c_str();
    }

    QString arg(const QString &str) const
    {
        QString ret = *this;
        ret.replace("%1", str);
        return ret;
    }

    QString arg(const QChar &str) const
    {
        QString ret = *this;
        ret.replace("%1", QString(str));
        return ret;
    }

    int size() const
    {
        return std::string::size();
    }

    int length() const
    {
        return size();
    }

    int indexOf(char ch, int start = 0) const
    {
        const size_t ret = find(ch, start);
        return ret == std::string::npos ? -1 : ret;
    }

    int indexOf(const QString &str, int start = 0) const
    {
        const size_t ret = find(str, start);
        return ret == std::string::npos ? -1 : ret;
    }

    int lastIndexOf(char ch, size_t start = npos) const
    {
        const size_t ret = rfind(ch, start);
        return ret == std::string::npos ? -1 : ret;
    }

    int lastIndexOf(const QString &str, size_t start = npos) const
    {
        const size_t ret = rfind(str, start);
        return ret == std::string::npos ? -1 : ret;
    }


    bool endsWith(const QString &string) const
    {
        return string.size() <= size() && !strncmp(string.constData(), constData() + (size() - string.size()), string.size());
    }

    bool startsWith(const QString &string) const
    {
        return string.size() <= size() && !strncmp(string.constData(), constData(), string.size());
    }

    QChar operator[](int val) const
    {
        return std::string::operator[](val);
    }

    bool isEmpty() const
    {
        return empty();
    }
    std::string toUtf8() const
    {
        return *this;
    }

    QString mid(int from, int len = -1) const
    {
        return substr(from, len);
    }

    QString left(int count) const
    {
        return substr(0, count);
    }

    QString right(int count) const
    {
        return substr(size() - count, count);
    }

    QString &replace(char from, char to)
    {
        size_t idx = 0;
        while ((idx = find(from, idx)) != npos) {
            operator[](idx) = to;
        }
        return *this;
    }

    QString &replace(const QString &from, const QString &to)
    {
        size_t last = 0;
        size_t idx = 0;
        std::ostringstream stream;
        bool changes = false;
        while ((idx = find(from, idx)) != npos) {
            changes = true;
            if (last < idx)
                stream.write(constData() + last, idx - last);
            stream << to;
            idx += from.size();
            last = idx;
        }
        if (changes)
            operator=(stream.str());
        return *this;
    }

    enum SplitBehavior {
        KeepEmptyParts,
        SkipEmptyParts
    };
    QStringList split(const QString &delimiter, SplitBehavior behavior = KeepEmptyParts) const;

    static QString number(int num)
    {
        char buf[1024];
        snprintf(buf, sizeof(buf), "%d", num);
        return buf;
    }

    QString operator+(const QChar &other) const
    {
        QString ret = *this;
        ret.push_back(other);
        return ret;
    }

};

inline void qDebug(const char *format, ...)
{
    va_list ap;
    va_start(ap, format); // use variable arg list
    vfprintf(stderr, format, ap);
    va_end(ap);
}

template <typename T>
class QList : public std::vector<T>
{
public:
    void setSharable(bool) {}
    void append(const T &t)
    {
        std::vector<T>::push_back(t);
    }

    QList<T> &operator<<(const T &t)
    {
        append(t);
        return *this;
    }

    void prepend(const T &t)
    {
        std::vector<T>::insert(std::vector<T>::begin(), t);
    }

    int count() const
    {
        return std::vector<T>::size();
    }

    typename std::vector<T>::const_iterator constEnd() const { return std::vector<T>::end(); }
    typename std::vector<T>::const_iterator constBegin() const { return std::vector<T>::begin(); }


    bool isEmpty() const
    {
        return std::vector<T>::empty();
    }

    QList<T> &operator+=(const QList<T> &other)
    {
        std::vector<T>::insert(std::vector<T>::end(), other.begin(), other.end());
        return *this;
    }

    QList<T> operator+(const QList<T> &other) const
    {
        QList<T> ret = *this;
        ret.insert(ret.std::vector<T>::end(), other.begin(), other.end());
        return ret;
    }

    void removeLast()
    {
        std::vector<T>::pop_back();
    }

    void removeFirst()
    {
        std::vector<T>::erase(std::vector<T>::begin());
    }

    T value(int idx, const T &def = T()) const
    {
        if (idx < std::vector<T>::size())
            return std::vector<T>::at(idx);
        return def;
    }
    T &first()
    {
        return std::vector<T>::operator[](0);
    }

    const T &first() const
    {
        return std::vector<T>::operator[](0);
    }

    T &last()
    {
        return std::vector<T>::operator[](std::vector<T>::size() - 1);
    }


    const T &last() const
    {
        return std::vector<T>::operator[](std::vector<T>::size() - 1);
    }

};

template <typename T>
class QVector : public QList<T>
{
public:
    QVector(int size = 0)
        : QList<T>()
    {
        if (size)
            QList<T>::resize(size);
    }

};

template <typename T>
class QStack : public QVector<T>
{
public:
    void push(const T &t)
    {
        QVector<T>::append(t);
    }

    T& top()
    {
        return QVector<T>::at(QVector<T>::size() - 1);
    }

    void pop()
    {
        QVector<T>::pop_back();
    }
};


class QStringList : public QList<QString>
{
public:

};

class QRegExp
{
public:
    QRegExp(const QString &p)
        : pattern(p)
    {}

    int indexIn(const QString &string) const;
    // {
    //     regex_t regex;
    //     if (regcomp(&regex, pattern.constData(), 0))
    //         return -1;

    //     int ret = -1;
    //     regmatch_t captures[10];
    //     if (!regexec(&regex, string.constData(), sizeof(captures) / sizeof(regmatch_t), captures, 0)) {
    //         for (int i=0; i<10 && captures[i].rm_so != -1; ++i) {
    //             printf("%d: %lld %lld\n", i, captures[i].rm_so, captures[i].rm_eo);
    //             caps.append(string.mid(captures[i].rm_so, captures[i].rm_eo - captures[i].rm_so));
    //         }

    //         ret = captures[0].rm_so;
    //     }

    //     regfree(&regex);

    //     return ret;
    // }

    bool exactMatch(const QString &string) const;
    // {
    //     regex_t regex;
    //     if (regcomp(&regex, pattern.constData(), 0))
    //         return -1;

    //     bool ret = false;
    //     regmatch_t captures[1];
    //     if (!regexec(&regex, string.constData(), sizeof(captures) / sizeof(regmatch_t), captures, 0)) {
    //         ret = captures[0].rm_so == 0 && captures[0].rm_eo == string.size();
    //         for (int i=0; i<10 && captures[i].rm_so != -1; ++i) {
    //             printf("%d: %lld %lld\n", i, captures[i].rm_so, captures[i].rm_eo);
    //             caps.append(string.mid(captures[i].rm_so, captures[i].rm_eo - captures[i].rm_so));
    //         }
    //     }

    //     regfree(&regex);

    //     return ret;
    // }

    QString cap(int idx) const
    {
        return caps.value(idx);

    }

    QString pattern;
    mutable QStringList caps;
};

inline QStringList QString::split(const QString &delimiter, SplitBehavior behavior) const
{
    QStringList ret;
    size_t idx = 0;
    size_t last = 0;
    while ((idx = find(delimiter, last)) != npos) {
        if (behavior == KeepEmptyParts || last != idx)
            ret << mid(last, idx - last);
        last = ++idx;
    }
    if (last < size())
        ret << mid(last);
    return ret;
}

class QVariant
{
public:
    QString toString() const
    {
        return string;
    }
    QStringList toStringList() const
    {
        return stringList;
    }

    static QVariant fromValue(const QString &string)
    {
        QVariant ret;
        ret.string = string;
        return ret;
    }

    static QVariant fromValue(const QStringList &stringList)
    {
        QVariant ret;
        ret.stringList = stringList;
        return ret;
    }

    QString string;
    QStringList stringList;
};

template <typename Key, typename Value>
class QMap : public std::map<Key, Value>
{
public:
    bool contains(const Key &key) const
    {
        return std::map<Key, Value>::find(key) != std::map<Key, Value>::end();
    }

    Value value(const Key &key, const Value &def = Value()) const
    {
        typename std::map<Key, Value>::const_iterator it = std::map<Key, Value>::find(key);
        if (it == std::map<Key, Value>::end())
            return def;
        return it->second;
    }

    void insert(const Key &key, const Value &val)
    {
        std::map<Key, Value>::operator[](key) = val;
    }
};
template <typename P1, typename P2>
class QPair : public std::pair<P1, P2>
{
public:
    QPair(const P1 &p1 = P1(), const P2 &p2 = P2())
        : std::pair<P1, P2>(p1, p2)
    {}
};

class QUrl
{
public:
    static inline char toHexHelper(char c)
    {
        static const char hexnumbers[] = "0123456789ABCDEF";
        return hexnumbers[c & 0xf];
    }

    static std::string toPercentEncodingHelper(const QString &s, const char *exclude, const char *include = 0)
    {
        if (s.isNull())
            return std::string();    // null
        std::string ba = s.toUtf8();
        q_toPercentEncoding(&ba, exclude, include);
        return ba;
    }


    static void q_fromPercentEncoding(std::string *ba, char percent)
    {
        if (ba->empty())
            return;

        char *data = &(*ba)[0];
        const char *inputPtr = data;

        int i = 0;
        int len = ba->size();
        int outlen = 0;
        int a, b;
        char c;
        while (i < len) {
            c = inputPtr[i];
            if (c == percent && i + 2 < len) {
                a = inputPtr[++i];
                b = inputPtr[++i];

                if (a >= '0' && a <= '9') a -= '0';
                else if (a >= 'a' && a <= 'f') a = a - 'a' + 10;
                else if (a >= 'A' && a <= 'F') a = a - 'A' + 10;

                if (b >= '0' && b <= '9') b -= '0';
                else if (b >= 'a' && b <= 'f') b  = b - 'a' + 10;
                else if (b >= 'A' && b <= 'F') b  = b - 'A' + 10;

                *data++ = (char)((a << 4) | b);
            } else {
                *data++ = c;
            }

            ++i;
            ++outlen;
        }

        if (outlen != len)
            ba->resize(outlen);
    }


    static QString fromPercentEncoding(const std::string &ba)
    {
        if (ba.empty())
            return QString();       // null
        std::string copy = ba;
        q_fromPercentEncoding(&copy, '%');
        return QString(copy.c_str(), copy.size());
    }


    static void q_toPercentEncoding(std::string *ba, const char *dontEncode, const char *alsoEncode, char percent = '%')
    {
        if (ba->empty())
            return;

        std::string input = *ba;
        int len = input.size();
        const char *inputData = input.c_str();
        char *output = 0;
        int length = 0;

        for (int i = 0; i < len; ++i) {
            unsigned char c = *inputData++;
            if (((c >= 0x61 && c <= 0x7A) // ALPHA
                 || (c >= 0x41 && c <= 0x5A) // ALPHA
                 || (c >= 0x30 && c <= 0x39) // DIGIT
                 || c == 0x2D // -
                 || c == 0x2E // .
                 || c == 0x5F // _
                 || c == 0x7E // ~
                 || strchr(dontEncode, c))
                && !strchr(alsoEncode, c)) {
                if (output)
                    output[length] = c;
                ++length;
            } else {
                if (!output) {
                    // detach now
                    ba->resize(len*3); // worst case
                    output = &(*ba)[0];
                }
                output[length++] = percent;
                output[length++] = toHexHelper((c & 0xf0) >> 4);
                output[length++] = toHexHelper(c & 0xf);
            }
        }
        if (output && ba->size() > length)
            ba->resize(length);
    }

    static QString toPercentEncoding(const QString &input, const std::string &exclude, const std::string &include = std::string())
    {
        return toPercentEncodingHelper(input, exclude.c_str(), include.c_str());
    }

};

class QTime
{
public:
    void start()
    {
        gettimeofday(&tv, 0);
    }
    int elapsed() const
    {
        timeval tv2;
        gettimeofday(&tv2, 0);
        return ((tv2.tv_sec - tv.tv_sec) * 1000) + ((tv2.tv_usec - tv.tv_usec) / 1000);
    }
    timeval tv;
};

/* make use of typeof-extension */
template <typename T>
class QForeachContainer {
public:
    inline QForeachContainer(const T& t) : c(t), brk(0), i(c.begin()), e(c.end()) { }
    const T c;
    int brk;
    typename T::const_iterator i, e;
};

#define Q_FOREACH(variable, container)                                  \
    for (QForeachContainer<__typeof__(container)> _container_(container); \
         !_container_.brk && _container_.i != _container_.e;            \
         __extension__  ({ ++_container_.brk; ++_container_.i; }))      \
        for (variable = *_container_.i;; __extension__ ({--_container_.brk; break;}))

#define foreach Q_FOREACH
#define Q_UNUSED(val) (void)val;

#define qPrintable(string) QString(string).c_str()

#define Q_DECLARE_SEQUENTIAL_ITERATOR(C)                                \
                                                                        \
    template <class T>                                                  \
    class Q##C##Iterator                                                \
    {                                                                   \
        typedef typename Q##C<T>::const_iterator const_iterator;        \
            Q##C<T> c;                                                  \
                const_iterator i;                                       \
  public:                                                               \
                inline Q##C##Iterator(const Q##C<T> &container)         \
                    : c(container), i(c.constBegin()) {}                \
                    inline Q##C##Iterator &operator=(const Q##C<T> &container) \
                        { c = container; i = c.constBegin(); return *this; } \
                        inline void toFront() { i = c.constBegin(); }   \
                        inline void toBack() { i = c.constEnd(); }      \
                        inline bool hasNext() const { return i != c.constEnd(); } \
                        inline const T &next() { return *i++; }         \
                        inline const T &peekNext() const { return *i; } \
                        inline bool hasPrevious() const { return i != c.constBegin(); } \
                        inline const T &previous() { return *--i; }     \
                        inline const T &peekPrevious() const { const_iterator p = i; return *--p; } \
                        inline bool findNext(const T &t)                \
                        { while (i != c.constEnd()) if (*i++ == t) return true; return false; } \
                        inline bool findPrevious(const T &t)            \
                        { while (i != c.constBegin()) if (*(--i) == t) return true; \
                            return false;  }                            \
    };

#define Q_DECLARE_MUTABLE_SEQUENTIAL_ITERATOR(C)                        \
                                                                        \
    template <class T>                                                  \
    class QMutable##C##Iterator                                         \
    {                                                                   \
        typedef typename Q##C<T>::iterator iterator;                    \
            typedef typename Q##C<T>::const_iterator const_iterator;    \
                Q##C<T> *c;                                             \
                    iterator i, n;                                      \
                    inline bool item_exists() const { return const_iterator(n) != c->constEnd(); } \
  public:                                                               \
                    inline QMutable##C##Iterator(Q##C<T> &container)    \
                        : c(&container)                                 \
                    { c->setSharable(false); i = c->begin(); n = c->end(); } \
                        inline ~QMutable##C##Iterator()                 \
                        { c->setSharable(true); }                       \
                            inline QMutable##C##Iterator &operator=(Q##C<T> &container) \
                                { c->setSharable(true); c = &container; c->setSharable(false); \
                                    i = c->begin(); n = c->end(); return *this; } \
                                inline void toFront() { i = c->begin(); n = c->end(); } \
                                inline void toBack() { i = c->end(); n = i; } \
                                inline bool hasNext() const { return c->constEnd() != const_iterator(i); } \
                                inline T &next() { n = i++; return *n; } \
                                inline T &peekNext() const { return *i; } \
                                inline bool hasPrevious() const { return c->constBegin() != const_iterator(i); } \
                                inline T &previous() { n = --i; return *n; } \
                                inline T &peekPrevious() const { iterator p = i; return *--p; } \
                                inline void remove()                    \
                                { if (c->constEnd() != const_iterator(n)) { i = c->erase(n); n = c->end(); } } \
                                inline void setValue(const T &t) const { if (c->constEnd() != const_iterator(n)) *n = t; } \
                                inline T &value() { Q_ASSERT(item_exists()); return *n; } \
                                inline const T &value() const { Q_ASSERT(item_exists()); return *n; } \
                                inline void insert(const T &t) { n = i = c->insert(i, t); ++i; } \
                                inline bool findNext(const T &t)        \
                                { while (c->constEnd() != const_iterator(n = i)) if (*i++ == t) return true; return false; } \
                                inline bool findPrevious(const T &t)    \
                                { while (c->constBegin() != const_iterator(i)) if (*(n = --i) == t) return true; \
                                    n = c->end(); return false;  }      \
    };

Q_DECLARE_SEQUENTIAL_ITERATOR(List)
Q_DECLARE_MUTABLE_SEQUENTIAL_ITERATOR(List)

template <typename T>
T qAbs(T t)
{
    return std::abs(t);
}



#endif
