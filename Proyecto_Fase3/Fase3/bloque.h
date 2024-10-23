#ifndef BLOQUE_H
#define BLOQUE_H

#include <QString>

using namespace std;

class Bloque{

public:

    int INDEX;
    QString TIMESTAMP;
    QString NONCE;
    QString PREVIOUSHASH;
    QString HASH;
    QString DATA;

    Bloque(int INDEX_, QString TIMESTAMP_, QString NONCE_, QString PREVIOUSHASH_, QString HASH_, QString DATA_)
        : INDEX(INDEX_), TIMESTAMP(TIMESTAMP_), NONCE(NONCE_), PREVIOUSHASH(PREVIOUSHASH_), HASH(HASH_), DATA(DATA_) {};

};

#endif // BLOQUE_H
