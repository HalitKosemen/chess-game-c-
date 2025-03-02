#include <iostream>
#include <string>
#include <utility>
using namespace std;

bool game_continous = true;
char santrac_tahtasi[64]; //santra� tahtasindaki kareleri dizi elemanlar�na �evirdigim yer
bool tas_rengi[64]; // eger tas_rengi mesela 9 karedeki beyaz ise true yap�caz

std::string oynancak_tas_konumu;
std::string oynancak_hamle_konumu;
int oynancak_hamle_konum_index;
int oynancak_tas_konum_index;

int girilen_hamlenin_index_hesaplamasi(std::string& girilen_deger) {

	if (girilen_deger.length() != 2) {
		return -1;
	}
	char birinci_eleman = girilen_deger[1]; //sat�r sutun harf ve say� atamas� yap�labiliyor
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


/*mant�k �u �ekilde santra� tahtas�n� karelerini her birini dizi �eklinde ay�rd�m
  ve dizi elemanlar�na ta�lar�n ba�lang�c konumlar�n� verdim ve tas_rengi de hangi
  renkte olduklar�n� g�steriyor mesela dizideki b2 konumu piyon ve rengi beyaz
  burdaki ayarlama ile siyah ta�lar� harflerini k���k yazars�n ve ay�rt edilebilir
  olur...*/
void tahta_baslangic_dizilimi() {
	for (int i = 0;i < 64;i++) {
		santrac_tahtasi[i] = ' '; //oncelik ile her kareyi bo� ayarl�yorum ' ' aras�nda space var
		tas_rengi[i] = false; // ve her kareyi beyaz olmad���n� g�steriyorum
	}

	//beyaz taslar i�in tan�mlama
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

	//siyah ta�lar i�in tan�mlama
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

/* burdada beyaz taslar b�y�k harf olarak siyahlar ise k�c�k harfe d�n��t�r�l�p
   yaz�l�yor... santra� tahtas�nda bir de�i�iklik oldu�unda yani santrac_tahtasi
   dizisinde bir de�i�iklik oldugunda bu fonksiyonu cagir tekrardan hepsini
   g�ncelleyip versin yani her tahtada degi�iklikte bu fonksiyonu cagirmak sart*/
void tahta_yazdirma() {
	for (int i = 0;i < 64;i++) {
		if (santrac_tahtasi[i] == ' ') {
			cout << ". ";
		}
		else {
			if (tas_rengi[i]) {
				cout << santrac_tahtasi[i] << " "; //beyaz tas ise direkt b�y�k yaz
			}
			else {
				cout << (char)tolower(santrac_tahtasi[i]) << " "; //siyah ise k���k harf ile yaz
			}
		}
		if ((i + 1) % 8 == 0) {
			cout << endl;
		}
	}
}


bool piyon_hareket_kontrol(int baslangic_index, int hedef_index, bool renk) {

	int fark = hedef_index - baslangic_index; // beyazlar i�in pozirif ikin ��nk� yukardan a�a gidiyo siyahlar i�in negatif
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
//burada baslangic_index kullan�c�n�n oynamak i�in se�ti�i ta� index de�i�keni hedef index ise oynicagi ta��n gidicegi konumun index degeri 
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

	//yukardan a�a��ya a-b-c-d... sa�dan sola 1-2-3 diye tan�mlama
	while (game_continous) {

		cout << "oynancak_tas_konumu: ";
		cin >> oynancak_tas_konumu;
		cout << "oynancak_tasin_bilgisi :" << (char)tahta_kutu_tas_kontrol(oynancak_tas_konumu) << endl << "tas rengi :" << (int)tahta_kutu_renk_kontrol(oynancak_tas_konumu) << endl;
		oynancak_tas_konum_index = girilen_hamlenin_index_hesaplamasi(oynancak_tas_konumu);
		cout << "sectiginiz tas gitmesini istediginiz konum :";
		cin >> oynancak_hamle_konumu;
		oynancak_hamle_konum_index = girilen_hamlenin_index_hesaplamasi(oynancak_hamle_konumu);

		/*�NEML� UPDATE
		  �imdi bir�ok �ey do�ru fakat piyonlar�n hareket etmesi gereken kuralda hareket etmedikleri g�r�n�yor burda buna bi d�zenleme yap�lmas� gerek 
		  a�ag�da bir ta� hareket edince yeni gidice�i konuma update etme kodu var bunu piyon_hareket_kural� adl� bir fonksiyon i�inde e�er hareket
		  do�ru ise belirtilen konuma hareket et gibisinden bir fonksiyon yazman laz�m...*/
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