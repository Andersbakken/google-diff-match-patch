#include <QtCore>
#include <diff_match_patch.h>

int main(int argc, char **argv)
{
//     QString balls = "1";
//     balls.replace("1", "1234");
//     printf("%s\n", balls.constData());
//     balls.replace("23", "aa");
//     printf("%s\n", balls.constData());
//     // return 0;



//     printf("%s\n", QString("%2:%1").arg('0').arg("99").constData());
//     return 0;
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

