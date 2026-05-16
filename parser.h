#ifndef PARSER_H
#define PARSER_H

// bağlı liste düğüm yapısı
typedef struct KomutDugumu
{
    char komut_adi[20];
    long long argumanlar[4];
    int arg_sayisi;
    char cikti_mesaji[100];
    int hata_var_mi;
    struct KomutDugumu *sonraki;
} KomutDugumu;

void dosya_islemlerini_yurut(const char *giris_dosyasi, const char *cikis_dosyasi);

#endif
