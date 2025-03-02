#include <iostream>
#include <string>
#include <utility>
using namespace std;

bool game_continous = true;
char santrac_tahtasi[64]; //santraç tahtasindaki kareleri dizi elemanlarýna çevirdigim yer
bool tas_rengi[64]; // eger tas_rengi mesela 9 karedeki beyaz ise true yapýcaz

std::string oynancak_tas_konumu;
std::string oynancak_hamle_konumu;
int oynancak_hamle_konum_index;
int oynancak_tas_konum_index;


int girilen_hamlenin_index_hesaplamasi(std::string& girilen_deger) {

	if (girilen_deger.length() != 2) {
		return -1;
	}
	char birinci_eleman = girilen_deger[1]; //satýr sutun harf ve sayý atamasý yapýlabiliyor
	char ikinci_eleman = girilen_deger[0];
	if (birinci_eleman < '1' || birinci_eleman > '8') {
		return -1;
	}
	if (ikinci_eleman < 'a' || ikinci_eleman >'h') {
		return -1;
	}
	int birinci_eleman_indx = birinci_eleman - '1';
	int ikinci_eleman_indx = ikinci_eleman - 'a';

	return birinci_eleman_indx * 8 + ikinci_eleman_indx;
}

void tahta_baslangic_dizilimi() {
	for (int i = 0;i < 64;i++) {
		santrac_tahtasi[i] = ' '; //oncelik ile her kareyi boþ ayarlýyorum ' ' arasýnda space var
		tas_rengi[i] = false; // ve her kareyi beyaz olmadýðýný gösteriyorum
	}

	//beyaz taslar için tanýmlama
	santrac_tahtasi[0] = 'K'; tas_rengi[0] = true;
	santrac_tahtasi[1] = 'A'; tas_rengi[1] = true;
	santrac_tahtasi[2] = 'F'; tas_rengi[2] = true;
	santrac_tahtasi[3] = 'V'; tas_rengi[3] = true;
	santrac_tahtasi[4] = 'S'; tas_rengi[4] = true;
	santrac_tahtasi[5] = 'F'; tas_rengi[5] = true;
	santrac_tahtasi[6] = 'A'; tas_rengi[6] = true;
	santrac_tahtasi[7] = 'K'; tas_rengi[7] = true;
	for (int i = 8;i < 16;i++) {
		santrac_tahtasi[i] = 'P'; tas_rengi[i] = true;
	}

	//siyah taþlar için tanýmlama
	santrac_tahtasi[56] = 'K'; tas_rengi[56] = false;
	santrac_tahtasi[57] = 'A'; tas_rengi[57] = false;
	santrac_tahtasi[58] = 'F'; tas_rengi[58] = false;
	santrac_tahtasi[59] = 'V'; tas_rengi[59] = false;
	santrac_tahtasi[60] = 'S'; tas_rengi[60] = false;
	santrac_tahtasi[61] = 'F'; tas_rengi[61] = false;
	santrac_tahtasi[62] = 'A'; tas_rengi[62] = false;
	santrac_tahtasi[63] = 'K'; tas_rengi[63] = false;
	for (int i = 48;i < 56;i++) {
		santrac_tahtasi[i] = 'P'; tas_rengi[i] = false;
	}
}

void tahta_yazdirma() {
	for (int i = 0;i < 64;i++) {
		if (santrac_tahtasi[i] == ' ') {
			cout << ". ";
		}
		else {
			if (tas_rengi[i]) {
				cout << santrac_tahtasi[i] << " "; //beyaz tas ise direkt büyük yaz
			}
			else {
				cout << (char)tolower(santrac_tahtasi[i]) << " "; //siyah ise küçük harf ile yaz
			}
		}
		if ((i + 1) % 8 == 0) {
			cout << endl;
		}
	}
}
//oynancak hamlelerin indexlerini gir ama
void hamle_oynadiginda_dizi_guncelleme() {

	santrac_tahtasi[oynancak_hamle_konum_index] = santrac_tahtasi[oynancak_tas_konum_index];
	tas_rengi[oynancak_hamle_konum_index] = tas_rengi[oynancak_tas_konum_index];
	santrac_tahtasi[oynancak_tas_konum_index] = '. ';
	tas_rengi[oynancak_tas_konum_index] = true;
	tahta_yazdirma();

}

//coutta cagirirken (char) fonksiyon yap
int tahta_kutu_tas_kontrol(std::string& girilen_hamle) {
	int index_hesap = girilen_hamlenin_index_hesaplamasi(girilen_hamle);
	char hangi_tas = santrac_tahtasi[index_hesap];
	return hangi_tas;
}
int tahta_kutu_renk_kontrol(std::string girilen_hamle) {
	int index_hesap = girilen_hamlenin_index_hesaplamasi(girilen_hamle);
	bool tas_rengi_ne = tas_rengi[index_hesap];
	return tas_rengi_ne;
}



int main() {

	tahta_baslangic_dizilimi();
	tahta_yazdirma();

	while (game_continous) {

		cout << "oynancak_tas_konumu: ";
		cin >> oynancak_tas_konumu;
		oynancak_tas_konum_index = girilen_hamlenin_index_hesaplamasi(oynancak_tas_konumu);
		cout << "sectiginiz tas gitmesini istediginiz konum :";
		cin >> oynancak_hamle_konumu;
		oynancak_hamle_konum_index = girilen_hamlenin_index_hesaplamasi(oynancak_hamle_konumu);

		cout << "oynancak tas tipi :" << (char)tahta_kutu_tas_kontrol(oynancak_tas_konumu) << " " << (bool)tahta_kutu_renk_kontrol(oynancak_tas_konumu) << endl;
		cout << "hamleyi oynicagin kutu bilgi:" << (char)tahta_kutu_tas_kontrol(oynancak_hamle_konumu) << " " << (bool)tahta_kutu_renk_kontrol(oynancak_hamle_konumu) << endl;
		hamle_oynadiginda_dizi_guncelleme();
	}
	return 0;
} 