#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

int saglik = 100;    
int enerji = 100;    
int yemek = 0;       
int siginak_var = 0; 
char komut;

int envanter_goster();
int avlan();
int siginak_ara();
int dinlen();
int tehlike_serisi();
int sifreli_ilerleme();

// --- Ana Fonksiyon (main) ---
int main() {
    // Global deðiþkenler zaten yukarýda tanýmlý. Burada sadece rastgelelik baþlatýlýyor.
    srand(time(NULL));

    printf("--- Hayatta Kalma Simulatorune Hos Geldiniz ---\n");
    printf("Amaciniz hayatta kalmak! Komutlar: A, S, R, E, F, P, X\n");

    // Ana Komut Dinleme Dongusu (DO-WHILE Zorunlu)
    do {
        // Oyun Bitti Kontrolu (Global deðiþkenlere doðrudan eriþim)
        if (saglik <= 0 || enerji <= 0) {
            printf("\n!!! Hayatta Kalma Basarisiz! Saglik veya Enerji bitti. !!!\n");
            komut = 'X'; 
            continue;
        }

        // Envanteri Goster
        envanter_goster(); 
        printf("\nBir komut giriniz (X: Cikis): ");
        scanf(" %c", &komut); 

        // Komutu buyuk harfe cevir
        if (komut >= 'a' && komut <= 'z') {
            komut = komut - 32;
        }

        // Komut Yonetimi (SWITCH-CASE Zorunlu)
        switch (komut) {
            case 'A': 
                avlan(); 
                break;
            case 'S': 
                siginak_ara();
                break;
            case 'R': 
                dinlen(); 
                break;
            case 'E': 
                printf("Envanter durumu goruntulendi.\n");
                break;
            case 'F': 
                tehlike_serisi(); 
                break;
            case 'P': 
                sifreli_ilerleme(); 
            case 'X': 
                printf("Simulasyon Sonlandiriliyor...\n");
                break;
            default:
                printf("Gecersiz komut. Lutfen A, S, R, E, F, P veya X girin.\n");
        }
    } while (komut != 'X'); 

    printf("\n--- Simulator Bitti. Iyi Gunler. ---\n");
    return 0;
}

// --- Fonksiyon Tanimlamalari ---

// E Komutu: Global deðiþkenleri doðrudan okur.
int envanter_goster() {
    printf("\n--- Mevcut Durum ---\n");
    printf("Saglik: %d/100\n", saglik);
    printf("Enerji: %d/100\n", enerji);
    printf("Yemek: %d Adet\n", yemek);
    printf("Siginak Durumu: %s\n", siginak_var ? "BULUNDU" : "YOK");
    printf("--------------------\n");
    return 0; // Ýnt döndürmek zorunlu olduðu için
}

// A Komutu: Global deðiþkenleri doðrudan deðiþtirir.
int avlan() {
    int sans = rand() % 100; 
    
    enerji -= 20; // Global enerji doðrudan azaltýlýyor

    printf("Avlanmaya ciktiniz ve 20 enerji kaybettiniz. (Kalan Enerji: %d)\n", enerji);
    
    // Yemek Bulma Ýhtimali
    if ((enerji >= 50) && (sans >= 40)) { 
        int kazanilan_yemek = (rand() % 3) + 1; 
        yemek += kazanilan_yemek;
        printf("Basarili avlanma! %d adet yemek buldunuz. (Toplam Yemek: %d)\n", kazanilan_yemek, yemek);
    } 
    // Yaralanma Ýhtimali
    else if ((enerji < 50) || (sans < 20)) { 
        int kaybedilen_saglik = (rand() % 10) + 5; 
        saglik -= kaybedilen_saglik; // Global saðlýk doðrudan azaltýlýyor
        printf("Av sirasinda yaralandiniz! %d saglik kaybettiniz. (Kalan Saglik: %d)\n", kaybedilen_saglik, saglik);
    } 
    else { 
        printf("Basarisiz avlanma. Bir sey bulamadiniz.\n");
    }
    return 0;
}

// S Komutu
int siginak_ara() {
    if (siginak_var == 1) {
        printf("Zaten bir siginaginiz var. Tekrar aramaniza gerek yok.\n");
        return 0;
    }

    int arama_sans = rand() % 100;
    
    if (arama_sans > 70 && enerji >= 70) { 
        siginak_var = 1; // Global siginak_var doðrudan deðiþtiriliyor
        printf("Tebrikler! Guvenli bir siginak buldunuz.\n");
    } 
    else if (arama_sans > 30) { 
        printf("Siginak aradiniz ama bulamadiniz. Tekrar denemeniz gerekebilir.\n");
    } 
    else {
        printf("Arama sirasinda kotu hava sartlari ile karsilastiniz. Arama basarisiz oldu.\n");
    }
    return 0;
}

// R Komutu
int dinlen() {
    int enerji_artisi = 25;
    int saglik_artisi = 10;

    enerji += enerji_artisi; 
    saglik += saglik_artisi;

    if (enerji > 100) { 
        enerji = 100;
    }
    if (saglik > 100) {
        saglik = 100;
    }

    printf("Dinlendiniz. %d Enerji ve %d Saglik kazandiniz.\n", enerji_artisi, saglik_artisi);
    printf("Yeni Durum: Saglik: %d, Enerji: %d\n", saglik, enerji);
    return 0;
}

// F Komutu
int tehlike_serisi() {
    int tehlike_sayisi = (rand() % 4) + 2; 
    int i; 

    printf("!!! Tehlike Dalgasi Basliyor (%d tur) !!!\n", tehlike_sayisi);

    for (i = 1; i <= tehlike_sayisi; i++) {
        printf("--- Tur %d ---\n", i);
        
        if (saglik > 50) {
            enerji -= 5;
            printf("Tehlikeden basarili bir sekilde kacindiniz, 5 enerji kaybettiniz.\n");
        } else if (saglik <= 50 && enerji > 20) {
            saglik -= 10;
            enerji -= 10;
            printf("Zorlu bir mucadele! 10 saglik ve 10 enerji kaybettiniz.\n");
        } else {
            saglik -= 20;
            printf("Kacmakta zorlandiniz! 20 saglik kaybettiniz.\n");
        }
    }
    printf("Tehlike dalgasi sona erdi. Guncel Durum: Saglik: %d, Enerji: %d\n", saglik, enerji);
    return 0;
}

// P Komutu
int sifreli_ilerleme() {
    char sifre_karakteri = 'K'; 
    char girilen_karakter;
    int deneme_sayisi = 0;

    printf("Onunuzde sifreli bir engel var. Dogru karakteri bulmalisiniz.\n");

    // DO-WHILE Dongusu (Zorunlu) - Dogrulama Mekanizmasi
    do {
        printf("\nBir karakter giriniz: ");
        scanf(" %c", &girilen_karakter);
        deneme_sayisi++;

        if (girilen_karakter >= 'a' && girilen_karakter <= 'z') {
            girilen_karakter = girilen_karakter - 32;
        }

        if (girilen_karakter == sifre_karakteri) {
            printf("\n*** Tebrikler! Dogru sifre! Engeli %d denemede astiniz. ***\n", deneme_sayisi);
        } else {
            printf("Yanlis karakter. Lutfen tekrar deneyin.\n");
            
            // --- 1. IPUCU (ALFABE KONUMU) ---
            if (girilen_karakter < sifre_karakteri) {
                printf("1. IPUCU: Girdiginiz karakter, DOGRU KARAKTERDEN alfabede ONCE geliyor.\n");
            } else {
                printf("1. IPUCU: Girdiginiz karakter, DOGRU KARAKTERDEN alfabede SONRA geliyor.\n");
            }

            // --- 2. IPUCU (OYUN ÝÇÝ ÝLÝÞKÝ) ---
            printf("2. IPUCU: DOGRU KARAKTER, 'Dinlen' (R) ve 'Avlan' (A) komutlarinin alfabedeki arasinda yer alir.\n");
        }
    } while (girilen_karakter != sifre_karakteri); 
    return 0;
}
