#include "KeyBoard.h"

char KeyBoard::key[256];

int KeyBoard::updateKey() {
    char tmpKey[256]; // ���݂̃L�[�̓��͏�Ԃ��i�[����
    GetHitKeyStateAll( tmpKey ); // �S�ẴL�[�̓��͏�Ԃ𓾂�
    for ( int i = 0; i < 256; i++ ) {
        if ( tmpKey[i] != 0 ) { // i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
            key[i]++;     // ���Z
        } else { // ������Ă��Ȃ����
            key[i] = 0;
        }
        if ( key[i] >= CHAR_MAX ) key[i] = CHAR_MAX - 1;
    }
    return 0;
}