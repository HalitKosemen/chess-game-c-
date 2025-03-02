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


/*mantýk þu þekilde santraç tahtasýný karelerini her birini dizi þeklinde ayýrdým
  ve dizi elemanlarýna taþlarýn baþlangýc konumlarýný verdim ve tas_rengi de hangi
  renkte olduklarýný gösteriyor mesela dizideki b2 konumu piyon ve rengi beyaz
  burdaki ayarlama ile siyah taþlarý harflerini küçük yazarsýn ve ayýrt edilebilir
  olur...*/
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

/* burdada beyaz taslar büyük harf olarak siyahlar ise kücük harfe dönüþtürülüp
   yazýlýyor... santraç tahtasýnda bir deðiþiklik olduðunda yani santrac_tahtasi
   dizisinde bir deðiþiklik oldugunda bu fonksiyonu cagir tekrardan hepsini
   güncelleyip versin yani her tahtada degiþiklikte bu fonksiyonu cagirmak sart*/
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


bool piyon_hareket_kontrol(int baslangic_index, int hedef_index, bool renk) {

	int fark = hedef_index - baslangic_index; // beyazlar için pozirif ikin çünkü yukardan aþa gidiyo siyahlar için negatif
	if (renk == true) { //ki bu beyaz ise 
		if (baslangic_index >= 8 && baslangic_index <= 15 && fark == 16 && santrac_tahtasi[baslangic_index + 8] == '. ' && santrac_tahtasi[hedef_index] == '. ') {
			return true;
		}
		if (fark == 8 && santrac_tahtasi[hedef_index] == '. ') {
			return true;
		}
		if ((fark == 7 || fark == 9) && santrac_tahtasi[hedef_index] != '. ' && tas_rengi[hedef_index] != renk) {
			return true;
		}
	}
	else {
		if (baslangic_index >= 48 && baslangic_index <= 55 && fark == -16 && santrac_tahtasi[baslangic_index - 8] == '. ' && santrac_tahtasi[hedef_index] == '. ') {
			return true;
		}
		if (fark == -8 && santrac_tahtasi[hedef_index] == '. ') {
			return true;
		}
		if ((fark == -7 || fark == -9) && santrac_tahtasi[hedef_index] != '. ' && tas_rengi[hedef_index] == renk) {
			return true;
		}
	}
	return false;
}
//burada baslangic_index kullanýcýnýn oynamak için seçtiði taþ index deðiþkeni hedef index ise oynicagi taþýn gidicegi konumun index degeri 
int piyon_hareket_dogru_mu(int baslangic_index, int hedef_index , bool renk) {
	int fark = hedef_index - baslangic_index;
	if (renk == true) {
		if (fark == 8 && santrac_tahtasi[hedef_index] == '. ') {
			santrac_tahtasi[oynancak_hamle_konum_index] = santrac_tahtasi[oynancak_tas_konum_index];
			tas_rengi[oynancak_hamle_konum_index] = tas_rengi[oynancak_tas_konum_index];
			santrac_tahtasi[oynancak_tas_konum_index] = '. ';
			tas_rengi[oynancak_tas_konum_index] = true;
			tahta_yazdirma();
		}
	}

	return 0;
}

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

	//yukardan aþaðýya a-b-c-d... saðdan sola 1-2-3 diye tanýmlama
	while (game_continous) {

		cout << "oynancak_tas_konumu: ";
		cin >> oynancak_tas_konumu;
		cout << "oynancak_tasin_bilgisi :" << (char)tahta_kutu_tas_kontrol(oynancak_tas_konumu) << endl << "tas rengi :" << (int)tahta_kutu_renk_kontrol(oynancak_tas_konumu) << endl;
		oynancak_tas_konum_index = girilen_hamlenin_index_hesaplamasi(oynancak_tas_konumu);
		cout << "sectiginiz tas gitmesini istediginiz konum :";
		cin >> oynancak_hamle_konumu;
		oynancak_hamle_konum_index = girilen_hamlenin_index_hesaplamasi(oynancak_hamle_konumu);

		/*ÖNEMLÝ UPDATE
		  þimdi birçok þey doðru fakat piyonlarýn hareket etmesi gereken kuralda hareket etmedikleri görünüyor burda buna bi düzenleme yapýlmasý gerek 
		  aþagýda bir taþ hareket edince yeni gidiceði konuma update etme kodu var bunu piyon_hareket_kuralý adlý bir fonksiyon içinde eðer hareket
		  doðru ise belirtilen konuma hareket et gibisinden bir fonksiyon yazman lazým...*/
		//if (piyon_hareket_kontrol(oynancak_tas_konum_index, oynancak_hamle_konum_index, true)) {
		// 
		//	santrac_tahtasi[oynancak_hamle_konum_index] = santrac_tahtasi[oynancak_tas_konum_index];
		//	tas_rengi[oynancak_hamle_konum_index] = tas_rengi[oynancak_tas_konum_index];
		//	santrac_tahtasi[oynancak_tas_konum_index] = '. ';
		//	tas_rengi[oynancak_tas_konum_index] = true;
		// 
		//	tahta_yazdirma();
		//}
		piyon_hareket_dogru_mu(oynancak_tas_konum_index, oynancak_hamle_konum_index, tahta_kutu_renk_kontrol(oynancak_tas_konumu));
		tahta_yazdirma();
	}
	return 0;
}