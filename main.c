/*
 * Ad Soyad: Batuhan Ceyhan , Yunus Emre Karaslan
 * Numara: 434368 , 434391
 * Açıklama: Programın ana giriş noktası ve argüman kontrolleri.
 */

#include <stdio.h>
#include "parser.h"

int main(int argc, char *argv[])
{
    // argüman kontrolü
    if (argc != 3)
    {
        printf("Hatalı kullanım yaptınız\n");
        printf("Örnek format: ./numtool <giris_dosyasi> <cikis_dosyasi>\n");
        return 1;
    }

    dosya_islemlerini_yurut(argv[1], argv[2]);

    return 0;
}
