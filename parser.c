/*
 * Ad Soyad: Batuhan Ceyhan , Yunus Emre Karaslan
 * Numara: 434368 , 434391
 * Açıklama: Dosya okuma, komutları ayrıştırma ve belleği yönetme işlemleri.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parser.h"
#include "math_utils.h"

void bosluklari_al(char *str) {
    char *son;
    while (isspace((unsigned char)*str)) str++;
    if (*str == 0) return;
    son = str + strlen(str) - 1;
    while (son > str && isspace((unsigned char)*son)) son--;
    son[1] = '\0';
}

void dosya_islemlerini_yurut(const char *giris_dosyasi, const char *cikis_dosyasi) {
    FILE *giris = fopen(giris_dosyasi, "r");
    if (giris == NULL) {
        printf("Hata: %s dosyasi okuma icin acilamadi.\n", giris_dosyasi);
        return;
    }

    FILE *cikis = fopen(cikis_dosyasi, "w");
    if (cikis == NULL) {
        printf("Hata: %s dosyasi yazma icin acilamadi.\n", cikis_dosyasi);
        fclose(giris);
        return;
    }

    KomutDugumu *liste_basi = NULL;
    KomutDugumu *liste_sonu = NULL;

    char satir[1024];

    while (fgets(satir, sizeof(satir), giris)) {
        bosluklari_al(satir);

        if (strlen(satir) == 0 || satir[0] == '#') continue;

        char *token = strtok(satir, ";");
        while (token != NULL) {
            char komut_gecici[256];
            strcpy(komut_gecici, token);
            bosluklari_al(komut_gecici);

            if (strlen(komut_gecici) > 0) {
                KomutDugumu *yeni_dugum = (KomutDugumu *)malloc(sizeof(KomutDugumu));
                yeni_dugum->hata_var_mi = 0;
                yeni_dugum->arg_sayisi = 0;
                yeni_dugum->sonraki = NULL;
                memset(yeni_dugum->komut_adi, 0, sizeof(yeni_dugum->komut_adi));
                memset(yeni_dugum->cikti_mesaji, 0, sizeof(yeni_dugum->cikti_mesaji));

                char kmt[20];
                long long args[4];
                
                int okunan_parametre = sscanf(komut_gecici, "%s %lld %lld %lld %lld", kmt, &args[0], &args[1], &args[2], &args[3]);
                
                if (okunan_parametre >= 1) {
                    strcpy(yeni_dugum->komut_adi, kmt);
                    yeni_dugum->arg_sayisi = okunan_parametre - 1;
                    for (int i = 0; i < yeni_dugum->arg_sayisi; i++) {
                        yeni_dugum->argumanlar[i] = args[i];
                    }

                    // KOMUT KONTROLLERİ
                    if (strcmp(kmt, "GCD") == 0 && yeni_dugum->arg_sayisi == 2) {
                        if (args[0] <= 0 || args[1] <= 0) {
                            strcpy(yeni_dugum->cikti_mesaji, "ERROR_INVALID_INPUT");
                            yeni_dugum->hata_var_mi = 1;
                        } else {
                            sprintf(yeni_dugum->cikti_mesaji, "%lld", gcd_hesapla(args[0], args[1]));
                        }
                    } 
                    else if (strcmp(kmt, "POW") == 0 && yeni_dugum->arg_sayisi == 3) {
                        if (args[1] < 0 || args[2] <= 0) {
                            strcpy(yeni_dugum->cikti_mesaji, "ERROR_INVALID_INPUT");
                            yeni_dugum->hata_var_mi = 1;
                        } else {
                            sprintf(yeni_dugum->cikti_mesaji, "%lld", power_mod_hesapla(args[0], args[1], args[2]));
                        }
                    } 
                    else if (strcmp(kmt, "PRIME") == 0 && yeni_dugum->arg_sayisi == 1) {
                        if (args[0] < 2) {
                            strcpy(yeni_dugum->cikti_mesaji, "ERROR_INVALID_INPUT");
                            yeni_dugum->hata_var_mi = 1;
                        } else {
                            strcpy(yeni_dugum->cikti_mesaji, is_prime_kontrol(args[0]) ? "YES" : "NO");
                        }
                    } 
                    else if (strcmp(kmt, "INV") == 0 && yeni_dugum->arg_sayisi == 2) {
                        int hata = 0;
                        long long ters = moduler_ters(args[0], args[1], &hata);
                        if (hata) {
                            strcpy(yeni_dugum->cikti_mesaji, "ERROR_NO_INVERSE");
                            yeni_dugum->hata_var_mi = 1;
                        } else {
                            sprintf(yeni_dugum->cikti_mesaji, "%lld", ters);
                        }
                    } 
                    else if (strcmp(kmt, "PHI") == 0 && yeni_dugum->arg_sayisi == 1) {
                        if (args[0] < 1) {
                            strcpy(yeni_dugum->cikti_mesaji, "ERROR_INVALID_INPUT");
                            yeni_dugum->hata_var_mi = 1;
                        } else {
                            sprintf(yeni_dugum->cikti_mesaji, "%lld", euler_phi_hesapla(args[0]));
                        }
                    } 
                    else if (strcmp(kmt, "CHECK") == 0 && yeni_dugum->arg_sayisi == 2) {
                        int hata = 0;
                        long long ters = moduler_ters(args[0], args[1], &hata);
                        if (hata) {
                            strcpy(yeni_dugum->cikti_mesaji, "ERROR_NO_INVERSE");
                            yeni_dugum->hata_var_mi = 1;
                        } else {
                            if ((args[0] % args[1] * ters % args[1]) % args[1] == 1) {
                                strcpy(yeni_dugum->cikti_mesaji, "CORRECT");
                            } else {
                                strcpy(yeni_dugum->cikti_mesaji, "FAILED");
                                yeni_dugum->hata_var_mi = 1;
                            }
                        }
                    } 
                    else {
                        strcpy(yeni_dugum->cikti_mesaji, "ERROR_UNKNOWN_COMMAND");
                        yeni_dugum->hata_var_mi = 1;
                    }

                    if (liste_basi == NULL) {
                        liste_basi = yeni_dugum;
                        liste_sonu = yeni_dugum;
                    } else {
                        liste_sonu->sonraki = yeni_dugum;
                        liste_sonu = yeni_dugum;
                    }
                } else {
                    free(yeni_dugum); 
                }
            }
            token = strtok(NULL, ";");
        }
    }

    // listeyi dolaşıp sonuçları dosyaya yazdırıyoruz
    KomutDugumu *aktif = liste_basi;
    while (aktif != NULL) {
        fprintf(cikis, "%s ", aktif->komut_adi);
        for(int i = 0; i < aktif->arg_sayisi; i++) {
            fprintf(cikis, "%lld%s", aktif->argumanlar[i], (i == aktif->arg_sayisi - 1) ? "" : " ");
        }
        fprintf(cikis, " -> %s\n", aktif->cikti_mesaji);
        aktif = aktif->sonraki;
    }

    fclose(giris);
    fclose(cikis);

    // Memory Leak oluşmaması için ayrılan tüm bellek alanlarını temizliyoruz
    aktif = liste_basi;
    while (aktif != NULL) {
        KomutDugumu *silinecek = aktif;
        aktif = aktif->sonraki;
        free(silinecek); 
    }
}