#include "phone.h"

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    PhoneDaemon phoneDaemon(&app);
    app.exec();
}
