#include <QtCore>
#include <diff_match_patch.h>

int main(int argc, char **argv)
{
    QString foo = "1\n2\3\n";
    foo.replace('\n', 'a');
    printf("Foo [%s]\n", foo.constData());
    return 0;
    QString a, b;
    bool string = false;
    for (int i=1; i<argc; ++i) {
        if (!strcmp(argv[i], "--string") || !strcmp(argv[i], "-s")) {
            string = true;
        } else if (a.isEmpty()) {
            a = argv[i];
        } else if (b.isEmpty()) {
            b = argv[i];
        } else {
            fprintf(stderr, "No use for this argument %s\n", argv[i]);
            return 1;
        }
    }
    if (a.isEmpty() || b.isEmpty()) {
        fprintf(stderr, "Not enough data\n");
        return 1;
    }

    if (!string) {
        QString *files[] = { &a, &b, 0 };
        for (int i=0; files[i]; ++i) {
            FILE *f = fopen(files[i]->constData(), "r");
            if (!f) {
                fprintf(stderr, "Can't open %s for reading\n", files[i]->constData());
                return 1;
            }
            files[i]->clear();
            char buf[1024];
            while (true) {
                const int r = fread(buf, sizeof(char), sizeof(buf), f);
                if (r <= 0)
                    break;
                files[i]->append(QString(buf, r));
            }
            fclose(f);
        }
    }

    diff_match_patch patch;
    QList<Diff> diffs = patch.diff_main(a, b);
    for (int i=0; i<diffs.size(); ++i) {
        printf("%s\n", diffs.at(i).toString().constData());
    }

    return 0;
}

