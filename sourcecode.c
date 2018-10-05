#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "boolean.h"

/***KAMUS TYPE***/

typedef struct {
	char chara[100];
  int Neff;
} string; /* MEMBENTUK TIPE DATA STRING */
typedef struct {
	int Elmt[100];
  int Neff;
} Tabel; /* MEMBENTUK TIPE DATA ARRAY/TABEL */

/***HEADER PROSEDUR***/

void Pembukaan();	/* PEMBUKAAN DAN PETUNJUK PERMAINAN */
void BuangSampah(FILE *file);	/* MEMBUANG BARIS YANG TIDAK DIPAKAI */
void SkipLine(FILE *file, int *input, int *Q, string *XO, string *status);	/* SKIP BARIS KE BARIS STATES BARU (Q1, Q2, Q3, DST...) */
void getTujuan(FILE *file, int *N, int *Qtujuan);	/* MENGETAHUI STATES TUJUAN (MISAL P = 2 MENUJU KE Q2, DST...) */
void TulisXO(string XO);	/* MENULIS RENTETAN XOXOXO DALAM BENTUK  SEPERTI GAME TICTACTOE PADA UMUMNYA */

/***MAIN PROGRAM***/

int main() {
	/* kamus main */
	  int q,input,N,mode,d; /* variabel utk nyimpen nomor states dan mode permainan */
		int i = 1; /* sbg penanda elemen array utk nyimpen states */
		char x; /* karakter untuk mark */
	  string XO,status; /* string yang dipakai (XO utk XOXOXO dst, status utk WIN/DRAW/belum selesai) */
		string sampah; /* string sampah ga guna yang ga dipakai, selain utk buang baris */
		boolean done, masukanValid; /* boolean utk mark looping */
		Tabel states; /* array utk nyimpen states */
	  FILE *file = fopen("file1.txt", "r"); /* file utk player first */
		FILE *file2 = fopen("file2.txt", "r"); /* file utk computer first */

	/* Main Algoritma */

		Pembukaan();

		BuangSampah(file);
		BuangSampah(file2);


		while ((mode != 1) && (mode != 2)) {
			printf("Pilih mode permainan (1 = Computer First, 2 = Player First) : ");
			scanf("%d", &mode); /* baca input pemain */
			if (mode == 1) {
				/* COMPUTER FIRST */
				printf("\nKOMPUTER BERGERAK PERTAMA!\n");
				fscanf(file2, "  q%d - %s %s", &q, &XO, &status);
				TulisXO(XO);
				printf("\n");
				while (!done) { /* Looping sampai permainan selesai (WIN atau DRAW)*/
					printf("\nMASUKAN NOMOR KOTAK : ");
					scanf("%d", &N); /*Memasukkan nomor kotak yang mau diisi*/
					getTujuan(file2,&N,&input);
					SkipLine(file2,&input,&q,&XO,&status);
					TulisXO(XO);
					printf("\n");

					(states).Elmt[(i)] = q; /*Menyimpan daftar states yang terpakai ke array/tabel*/

					if ((strcmp(status.chara, "WIN")) == 0) { /*Komputer menang*/
						printf("\nKOMPUTER MENANG\n");
						done = true;
					}
					else if ((strcmp(status.chara, "DRAW")) == 0) { /*Seri*/
						printf("\nSERI\n");
						done = true;
					}
					else /*Permainan belum selesai*/
						i++;
				}
				printf("\nStates yang telah dilewati : q0 ");
				for (int j = 1; j <= i; j++) { /*Menampilkan daftar states yang dilewati*/
					d = (states).Elmt[(j)];
					printf("q%d ", d);
				}
			}
			else if (mode == 2) {
				/* PLAYER FIRST */
				printf("\nKAMU BERGERAK PERTAMA!\n");
				while (!masukanValid) { /*Menerima masukkan nomor kotak pertama sampai valid (kotak yang diisi kotak nomor 5)*/
					printf("MASUKAN NOMOR KOTAK : ");
					scanf("%d", &N); /*Memasukkan nomor kotak yang mau diisi*/
					if (N == 5) { /* Masukkan valid (kotak 5 diisi pertama)*/
						masukanValid = true;
						strcpy(XO.chara,"O000X0000");
						TulisXO(XO);
						printf("\n");
						while (!done) { /* Looping sampai permainan selesai (WIN atau DRAW)*/
							printf("\nMASUKAN NOMOR KOTAK : ");
							scanf("%d", &N);

							fscanf(file, "  q%d - %s %s", &q, &XO, &status);
							getTujuan(file,&N,&input);
							SkipLine(file,&input,&q,&XO,&status);
							TulisXO(XO);
							printf("\n");

							(states).Elmt[(i)] = q; /*Menyimpan daftar states yang terpakai ke array/tabel*/

							if ((strcmp(status.chara, "WIN")) == 0) { /*Komputer menang*/
								printf("\nKOMPUTER MENANG\n");
								done = true;
							}
							else if ((strcmp(status.chara, "DRAW")) == 0) { /*Seri*/
								printf("\nSERI\n");
								done = true;
							}
							else /* Permainan belum selesai*/
								i++;
						}

						printf("\nStates yang telah dilewati : q1 ");
						for (int j = 1; j <= i; j++) { /*Menampilkan daftar states yang dilewati*/
							d = (states).Elmt[(j)];
							printf("q%d ", d);
						}
					}
					else /* Masukkan tidak valid (kotak 5 tidak diisi pertama)*/
						printf("ULANGI! Baca aturan bermain\n");
				}
			}
			else {
				/* MASUKKAN PILIHAN MODE BUKAN 1 ATAU 2 */
				printf("ERROR : Masukkan tidak valid\n");
			}
		}

		printf("\n");
		printf("\nSELAMAT TINGGAL (ketik pesan perpisahan + enter untuk Exit) \n");
		scanf("\n"); /*Supaya pas program selesai, pemain bisa melihat tulisan hasilnya dulu, ngga langsung keluar dari program*/


	  return 0;
}

/***IMPLEMENTATION PROSEDUR***/

void Pembukaan() {
	printf("\n");
  printf("SELAMAT DATANG DI 'THE AMAZING TICTACTOE'\n");
	printf(" ---------- \n");
	printf("CARA BERMAIN :\n");
	printf(" - Pilih mode permainan (player first / computer first)\n");
	printf(" - Masukkan nomor kotak yang ingin diisi\n");
	printf(" - Pemain akan memainkan huruf 'X', sementara komputer akan memainkan huruf 'O'\n");
	printf(" - Berusahalah untuk mengalahkan komputer yang amazing ini!\n");
	printf(" ---------- \n");
	printf("PETUNJUK NOMOR KOTAK :\n");
	printf("1 | 2 | 3\n");
	printf("4 | 5 | 6\n");
	printf("7 | 8 | 9\n");
	printf(" ---------- \n");
	printf("ATURAN BERMAIN :\n");
	printf(" - Jika memilih mode player first, wajib mengisi kotak nomor 5 pertama\n");
	printf(" - Dilarang untuk curang atau mengehack game ini!\n");
	printf(" - Hanya isi kotak yang belum diisi\n");
	printf(" - Jika mengisi kotak yang telah terisi, maka akan ada konsekuensi\n");
	printf(" - Konsekuensi berupa kotak akan diisi oleh komputer yang amazing ini secara otomatis\n");
	printf(" ---------- \n");
}

void BuangSampah(FILE *file) {
	string sampah;

	fscanf(file,"%s -%s %s-", &sampah, &sampah, &sampah);
	fscanf(file,"%s %s :", &sampah, &sampah);
}

void SkipLine(FILE *file, int *input, int *Q, string *XO, string *status) {
	char x = 'A';

	*Q = 99;
	while (*Q != *input) {
		while (x != 'X') {
				fscanf(file,"%c\n",&x);
			}
		fscanf(file, "  q%d - %s %s", Q, XO, status);
		x = 'A';
	}

}

void getTujuan(FILE *file, int *N, int *Qtujuan) {
  int input = 99;

	while ((input != *N) && (input != 0)) {
    fscanf(file, "    p = %d : q%d", &input, Qtujuan);
  }
}

void TulisXO(string XO) {
   int i = 0;
	 char x;

	 while (i <= 8) {
 		x = XO.chara[i];
 		if (x == '0') {
 			printf("-");
 		}
 		else
 		 	printf("%c", x);

 		if (i == 2 | i == 5) {
 			printf("\n");
 		}
 		i++;
 	}
}
