#include <QtCore>
#include <diff_match_patch.h>

int main(int argc, char **argv)
{
    QString foo = "10111213";
    {
        QRegExp rx("^..*$");
        printf("%d\n", rx.exactMatch(foo));
        printf("%s,%s\n", rx.cap(0).constData(), rx.cap(1).constData());
    }
    printf("%s\n", foo.constData());
    QStringList list = foo.split("1"); //, QString::SkipEmptyParts);

    for (QStringList::const_iterator it = list.begin(); it != list.end(); ++it) {
        if (it != list.begin())
            printf(", ");
        printf("\"%s\"", it->constData());
    }
    printf("\n");
    return 0;
}

int QRegExp::indexIn(const QString &string) const
{
    regex_t regex;
    if (regcomp(&regex, pattern.constData(), 0))
        return -1;

    int ret = -1;
    regmatch_t captures[10];
    if (!regexec(&regex, string.constData(), sizeof(captures) / sizeof(regmatch_t), captures, 0)) {
        for (int i=0; i<10 && captures[i].rm_so != -1; ++i) {
            printf("%d: %lld %lld\n", i, captures[i].rm_so, captures[i].rm_eo);
            caps.append(string.mid(captures[i].rm_so, captures[i].rm_eo - captures[i].rm_so));
        }

        ret = captures[0].rm_so;
    }

    regfree(&regex);

    return ret;
}

bool QRegExp::exactMatch(const QString &string) const
{
    regex_t regex;
    if (regcomp(&regex, pattern.constData(), 0))
        return -1;

    bool ret = false;
    regmatch_t captures[1];
    if (!regexec(&regex, string.constData(), sizeof(captures) / sizeof(regmatch_t), captures, 0)) {
        ret = captures[0].rm_so == 0 && captures[0].rm_eo == string.size();
        for (int i=0; i<10 && captures[i].rm_so != -1; ++i) {
            printf("%d: %lld %lld\n", i, captures[i].rm_so, captures[i].rm_eo);
            caps.append(string.mid(captures[i].rm_so, captures[i].rm_eo - captures[i].rm_so));
        }
    }

    regfree(&regex);

    return ret;
}
