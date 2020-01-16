CONFIG += ordered

TEMPLATE = subdirs

GIT_TIMESTAMP    = $$system($$quote(git --git-dir $$PWD/.git log -n 1 --format=format:"%at"))
GIT_VERSION      = $$system($$quote(git --git-dir $$PWD/.git --work-tree $$PWD describe --always --tags))
GIT_COMMIT_COUNT = $$system($$quote(git --git-dir $$PWD/.git rev-list HEAD --count))

QMAKE_SUBSTITUTES += $$PWD/app_version.h.in

SUBDIRS += \
    microsha \
    tests/tst_i8080 \
    tests/tst_i8255



