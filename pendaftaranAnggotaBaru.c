#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LENGTH 100
#define FILE_NAME "anggota.txt"

struct Anggota
{
    long long id;
    char nama[MAX_LENGTH];
    char email[MAX_LENGTH];
    char no_telepon[MAX_LENGTH];
    char password[MAX_LENGTH];
};

void clear_input_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void get_input(char *prompt, char *buffer)
{
    printf("%s", prompt);
    fgets(buffer, MAX_LENGTH, stdin);
    buffer[strcspn(buffer, "\n")] = 0;
}

long long generate_id()
{
    return (long long)time(NULL);
}

int validate_password(const char *password, const char *confirm_password)
{
    if (strcmp(password, confirm_password) != 0)
    {
        printf("Error: Password dan konfirmasi password tidak cocok.\n");
        return 0;
    }
    if (strlen(password) < 8)
    {
        printf("Error: Password harus minimal 8 karakter.\n");
        return 0;
    }
    return 1;
}

void daftar_anggota()
{
    struct Anggota anggota;
    char confirm_password[MAX_LENGTH];
    FILE *file = fopen(FILE_NAME, "a");

    if (file == NULL)
    {
        printf("Error: Tidak dapat membuka file.\n");
        return;
    }

    anggota.id = generate_id();

    get_input("Masukkan nama: ", anggota.nama);
    get_input("Masukkan email: ", anggota.email);
    get_input("Masukkan no telepon: ", anggota.no_telepon);

    do
    {
        get_input("Masukkan password: ", anggota.password);
        get_input("Konfirmasi password: ", confirm_password);
    } while (!validate_password(anggota.password, confirm_password));

    fprintf(file, "%lld|%s|%s|%s|%s\n", anggota.id, anggota.nama, anggota.email, anggota.no_telepon, anggota.password);

    fclose(file);

    printf("Pendaftaran berhasil! ID Anggota Anda: %lld\n", anggota.id);
}

int main()
{
    char pilihan;

    do
    {
        printf("\nPendaftaran Anggota Baru Perpustakaan\n");
        printf("1. Daftar anggota baru\n");
        printf("0. Keluar\n");
        printf("Pilihan Anda: ");
        scanf(" %c", &pilihan);
        clear_input_buffer();

        switch (pilihan)
        {
        case '1':
            daftar_anggota();
            break;
        case '0':
            printf("Terima kasih telah menggunakan program ini.\n");
            break;
        default:
            printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }
    } while (pilihan != '0');

    return 0;
}
