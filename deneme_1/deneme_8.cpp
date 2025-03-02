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
	santrac_tahtasi[56] = 'k'; tas_rengi[56] = false;
	santrac_tahtasi[57] = 'a'; tas_rengi[57] = false;
	santrac_tahtasi[58] = 'f'; tas_rengi[58] = false;
	santrac_tahtasi[59] = 'v'; tas_rengi[59] = false;
	santrac_tahtasi[60] = 's'; tas_rengi[60] = false;
	santrac_tahtasi[61] = 'f'; tas_rengi[61] = false;
	santrac_tahtasi[62] = 'a'; tas_rengi[62] = false;
	santrac_tahtasi[63] = 'k'; tas_rengi[63] = false;
	for (int i = 48;i < 56;i++) {
		santrac_tahtasi[i] = 'p'; tas_rengi[i] = false;
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

// bu piyon hareket_kontrol fonksiyonu çalýþýyor bþ kutuya hareket için ' ' arada bi boþluk býraktan yeterli  
bool piyon_hareket_okey_mi() {

	int renk_kontrol = (bool)tahta_kutu_renk_kontrol(oynancak_tas_konumu);
	int fark = oynancak_hamle_konum_index - oynancak_tas_konum_index;
	char tas_harf = (char)tahta_kutu_tas_kontrol(oynancak_tas_konumu);
	if (renk_kontrol == 1 && tas_harf == 'P') {
		if (fark == 8 && santrac_tahtasi[oynancak_hamle_konum_index] == ' ') {
			return true;
		}
		if (oynancak_tas_konum_index >= 8 && oynancak_tas_konum_index <= 15 && fark == 16 && santrac_tahtasi[oynancak_hamle_konum_index] == ' ' && santrac_tahtasi[oynancak_tas_konum_index + 8] == ' ') {
			return true;
		}
		if ((fark == 7 || fark == 9) && santrac_tahtasi[oynancak_hamle_konum_index] != ' ' && tas_rengi[oynancak_hamle_konum_index] != 1) {
			return true;
		}
	}
	else if (renk_kontrol == 0 && tas_harf == 'p') {
		if (oynancak_tas_konum_index >= 48 && oynancak_tas_konum_index <= 55 && fark == -16 && santrac_tahtasi[oynancak_tas_konum_index - 8] == ' ' && santrac_tahtasi[oynancak_hamle_konum_index] == ' ') {
			return true;
		}
		if (fark == -8 && santrac_tahtasi[oynancak_hamle_konum_index] == ' ') {
			return true;
		}
		if ((fark == -7 || fark == -9) && santrac_tahtasi[oynancak_hamle_konum_index] != ' ' && tas_rengi[oynancak_hamle_konum_index] == 1) {
			return true;
		}
	}
	return false;
}

bool kale_hareket_okey_mi() {

	int renk_kontrol = (bool)tahta_kutu_renk_kontrol(oynancak_tas_konumu);
	int fark = oynancak_hamle_konum_index - oynancak_tas_konum_index;
	char tas_harf = (char)tahta_kutu_tas_kontrol(oynancak_tas_konumu);
	int adim = 0;

	if (renk_kontrol == 1 && tas_harf == 'K') { //beyaz kale için hareket sýnýrlamalarý 
		if (fark % 8 == 0) {
			adim = (fark > 0) ? 8 : -8;
			for (int i = oynancak_tas_konum_index + adim; i != oynancak_hamle_konum_index; i += adim) {
				if (santrac_tahtasi[i] != ' ') {
					return false;
				}
			}
			if (santrac_tahtasi[oynancak_hamle_konum_index] == ' ' || tas_rengi[oynancak_hamle_konum_index] != renk_kontrol) {
				return true;
			}
		}
		if (oynancak_tas_konum_index / 8 == oynancak_hamle_konum_index / 8) {
			adim = (fark > 0) ? 1 : -1;
			for (int i = oynancak_tas_konum_index + adim; i != oynancak_hamle_konum_index; i += adim) {
				if (santrac_tahtasi[i] != ' ') {
					return false;
				}
			}
			if (santrac_tahtasi[oynancak_hamle_konum_index] == ' ' || tas_rengi[oynancak_hamle_konum_index] != renk_kontrol) {
				return true;
			}
		}
	}
	if (renk_kontrol == 0 && tas_harf == 'k') {
		if (fark % 8 == 0) {
			adim = (fark > 0) ? 8 : -8;
			for (int i = oynancak_tas_konum_index + adim; i != oynancak_hamle_konum_index; i += adim) {
				if (santrac_tahtasi[i] != ' ') {
					return false;
				}
			}
			if (santrac_tahtasi[oynancak_hamle_konum_index] == ' ' || tas_rengi[oynancak_hamle_konum_index] != renk_kontrol) {
				return true;
			}
		}
		if (oynancak_tas_konum_index / 8 == oynancak_hamle_konum_index / 8) {
			adim = (fark > 0) ? 1 : -1;
			for (int i = oynancak_tas_konum_index + adim; i != oynancak_hamle_konum_index; i += adim) {
				if (santrac_tahtasi[i] != ' ') {
					return false;
				}
			}
			if (santrac_tahtasi[oynancak_hamle_konum_index] == ' ' || tas_rengi[oynancak_hamle_konum_index] != renk_kontrol) {
				return true;
			}
		}
	}
	return false;
}

bool kullanicinin_girdigi_hamleler_okey_mi(std::string kullanici_ilk_girilen, std::string kullanici_ikinci_girilen) {

	if (kullanici_ilk_girilen.length() != 2 || kullanici_ikinci_girilen.length() != 2) {
		return false;
	}
	char ilk_harf = kullanici_ilk_girilen[0];
	char ilk_sayi = kullanici_ilk_girilen[1];
	if (ilk_harf < 'a' || ilk_harf > 'h' || ilk_sayi < '1' || ilk_sayi > '8') {
		return false;
	}

	char ikinci_harf = kullanici_ikinci_girilen[0];
	char ikinci_sayi = kullanici_ikinci_girilen[1];
	if (ikinci_harf < 'a' || ikinci_harf > 'h' || ikinci_sayi < '1' || ikinci_sayi > '8') {
		return false;
	}
	return true;
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
		if (kullanicinin_girdigi_hamleler_okey_mi(oynancak_tas_konumu, oynancak_hamle_konumu)) {
			if (piyon_hareket_okey_mi()) {
				hamle_oynadiginda_dizi_guncelleme();
			}
			if (kale_hareket_okey_mi()) {
				hamle_oynadiginda_dizi_guncelleme();
			}
		}
	}
	return 0;
}
