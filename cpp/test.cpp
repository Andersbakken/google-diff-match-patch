#include <QtCore>
#include <diff_match_patch.h>

void foo()
{

    regex_t regex;
    int state = regcomp(&regex, ".\\(.\\).", 0);
    printf("regcomp state %d\n", state);
    regmatch_t captures[10];
    state = regexec(&regex, "abc", sizeof(captures) / sizeof(regmatch_t), captures, 0);
    for (unsigned i=0; i<sizeof(captures) / sizeof(regmatch_t); ++i) {
        if (captures[i].rm_so != -1) {
            printf("Got capped %d %lld %lld\n", i, captures[i].rm_so, captures[i].rm_eo);
        } else {
            break;
        }
    }
    regfree(&regex);

}

int main(int argc, char **argv)
{
    // foo();
    // return 0;
    QRegExp rx(".\\(.\\).");
    QString foo = "abc";
    // QString foo = "10111213";
    {
        // QRegExp rx("^\\(.\\).*$");
        printf("%d\n", rx.indexIn(foo));

        // printf("%d\n", rx.exactMatch(foo));
         printf("%s,%s\n", rx.cap(0).constData(), rx.cap(1).constData());
    }
    return 0;
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

