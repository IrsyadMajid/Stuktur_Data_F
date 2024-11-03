#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DATA 20

typedef struct Node {
    char nama[50];
    char gender;
    struct Node* next;
} Node;

Node* head = NULL;
int count = 0;

Node* createNode(char* nama, char gender) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->nama, nama);
    newNode->gender = gender;
    newNode->next = NULL;
    return newNode;
}

void tambahData(char* nama, char gender) {
    if (count >= MAX_DATA) {
        printf("Sudah memenuhi kapasitas\n", MAX_DATA);
        return;
    }

    Node* newNode = createNode(nama, gender);

    if (head == NULL) {
        head = newNode;
        head->next = head;
    } else {
        Node* temp = head;
        while (temp->next != head) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = head;
    }
    count++;
    printf("Atas nama %s (%c) berhasil ditambahkan\n", nama, gender);
}

void tambahDataTengah(char* nama, char gender, char* namaPos) {
	if (count >= MAX_DATA) {
		printf("Sudah memenuhi kapasitas\n");
		return;
	}
	
	Node* pCur = head;
	while (pCur != NULL && strcmp(pCur->nama, namaPos) != 0) {
		pCur = pCur->next;
	}
	
	if (pCur == NULL) {
		printf("Nama %s tidak ditemukan didalam list\n", namaPos);
		return;
	}
	
	Node* newNode = createNode(nama, gender);
	newNode->next = pCur->next;
	pCur->next = newNode;
	count++;
	printf("Atas nama %s (%c) berhasil disisipkan setelah %s (%c)", nama, gender, namaPos, gender);
}

void hapusData(char* nama) {
    if (head == NULL) {
        printf("Belum ada nama di dalam urutan\n");
        return;
    }

    Node *temp = head, *prev = NULL;
    if (strcmp(temp->nama, nama) == 0) {
    	char delGender = temp->gender;
        if (temp->next == head) {
            free(temp);
            head = NULL;
        } else {
            while (temp->next != head) {
                temp = temp->next;
            }
            Node* delNode = head;
            temp->next = head->next;
            head = head->next;
            free(delNode);
        }
        count--;
        printf("Atas nama %s (%c) berhasil dihapus\n", nama, delGender);
        return;
    }
	
	temp = head;
    do {
        prev = temp;
        temp = temp->next;
    } while (temp != head && strcmp(temp->nama, nama) != 0);

    if (strcmp(temp->nama, nama) == 0) {
        prev->next = temp->next;
        char delGender = temp->gender;
        free(temp);
        count--;
        printf("Atas nama %s (%c) berhasil dihapus\n", nama, delGender);
    } else {
        printf("Atas nama %s tidak ditemukan\n", nama);
    }
}

void tranverse(Node *head) {
    if (head == NULL) {
        printf("Belum ada nama di dalam urutan\n");
        return;
    }

    Node *pWalker = head;

    do {
        printf("%s (%c) -> ", pWalker->nama, pWalker->gender);
        pWalker = pWalker->next;
    } while (pWalker != head);
    printf("%s (%c)\n", head->nama, head->gender);
}

void tampilkanBerdasarkanGender(char gender) {
    if (head == NULL) {
        printf("Belum ada nama di dalam urutan\n");
        return;
    }

    Node* temp = head;
    int found = 0;
    do {
        if (temp->gender == gender) {
            printf("%s (%c) -> ", temp->nama, temp->gender);
            found = 1;
        }
        temp = temp->next;
    } while (temp != head);

    if (found) {
        printf("%s (%c)\n", head->nama, head->gender);
    } else {
        printf("Tidak ada data dengan jenis kelamin %c\n", gender);
    }
}

int main() {
    int opsi;
    char nama[50], gender, delName[50];

    do {
        printf("\nOpsi untuk camping bersama teman-teman\n");
        printf("1. Masukkan Nama\n");        
		printf("2. Hapus Nama\n");
        printf("3. Tampilkan Urutan\n");
        printf("4. Tampilkan Urutan Berdasarkan Jenis Kelamin\n");
        printf("5. Keluar\n");
        printf("Masukkan pilihan: ");
        scanf("%d", &opsi);

        switch (opsi) {
            case 1:
                if (count < MAX_DATA) {
                	int opsiTambah;
                	printf("1. Menambahkan nama di awal\n");
                	printf("2. Menambahkan menu di tengah\n");
                	printf("Masukkan opsi untuk menambahkan pilihanmu: ");
                	scanf("%d", &opsiTambah);
                	
                    printf("Masukkan nama: ");
                    scanf("%s", nama);
                    printf("Masukkan jenis kelamin (L/P): ");
                    scanf(" %c", &gender);
                    
                    if (opsiTambah == 1) {
                    	tambahData(nama, gender);
					} else if (opsiTambah == 2) {
						char namaPos[50];
						printf("Masukkan nama setelah data akan disisipkan: ");
						scanf("%s", &namaPos);
						tambahDataTengah (nama, gender, namaPos);
					} else {
                    	printf("Sudah memenuhi kapasitas\n");
                	}
            } else {
            	printf("Sudah memenuhi kapasitas\n");
			}
                break;
            case 2:
                printf("Masukkan nama yang ingin dihapus: ");
                scanf("%s", delName);
                hapusData(delName);
                break;
            case 3:
                tranverse(head);
                break;
            case 4:
                printf("Masukkan jenis kelamin yang ingin ditampilkan (L/P): ");
                scanf(" %c", &gender);
                tampilkanBerdasarkanGender(gender);
                break;
            case 5:
                printf("Keluar");
                break;
            default:
                printf("ERROR. Ulangi program");
        }
    } while (opsi != 5);
    system("cls");
    return 0;
}
