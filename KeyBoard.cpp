#include "KeyBoard.h"

char KeyBoard::key[256];

int KeyBoard::updateKey() {
    char tmpKey[256]; // ���݂̃L�[�̓��͏�Ԃ��i�[����
    GetHitKeyStateAll( tmpKey ); // �S�ẴL�[�̓��͏�Ԃ𓾂�
    for ( int i = 0; i < 256; i++ ) {
        if ( key[i] >= CHAR_MAX ) key[i] = 1;
        if ( tmpKey[i] != 0 ) { // i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
            key[i]++;     // ���Z
        } else { // ������Ă��Ȃ����
            key[i] = 0;
        }
    }
    return 0;
}