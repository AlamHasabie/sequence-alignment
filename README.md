# sequence-alignment
<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/7/79/RPLP0_90_ClustalW_aln.gif/640px-RPLP0_90_ClustalW_aln.gif" width="50%" height="50%" align="top"><img src="https://upload.wikimedia.org/wikipedia/commons/2/25/An_excerpt_of_a_multiple_sequence_alignment_of_TMEM66_proteins.png" width="50%" height="50%" align="top">

## Tujuan Tugas
1. Review materi *Divide and Conquer* dan *Dynamic Programming*.
2. Mengenal bidang bioinformatika
3. Mengenal pensejajaran sekuens sebagai salah satu aplikasi DnC dan DP dalam bidang bioinformatika

## Deskripsi Masalah
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;*Sequence alignment* (pensejajaran sekuens) merupakan sebuah teknik dalam bioinformatika untuk melakukan pensejajaran antara dua buah string sekuens, misalkan sekuens asam amino atau nukleotid. Teknik ini banyak dipakai, misalkan dalam melakukan pencarian dalam sebuah basis data genom ataupun mengetahui keterkaitan organisme dalam studi filogeni.<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Dua buah sekuens DNA bisa memiliki susunan basa nukleotida yang berbeda, namun keduanya bisa memiliki sub-sekuens yang mirip. Misalkan, dua buah sekuens ACTGGTA dan TGTGGTC memiliki sub-sekuens yang sama (TGGT). Sub-sekuens ini disebut *conserved sequence*. Salah satu tujuan pensejajaran adalah mengidentifikasi bagian yang mirip. Dengan mengetahui pensejajaran DNA antar dua organisme, kita dapat mengetahui hubungan dan perubahan evolusioner yang terjadi antar dua organisme.<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;*Global alignment* merujuk pada pensejajaran global (seluruh panjang kedua sekuens), sedangkan pensejajaran lokal merujuk pada pensejajaran suatu daerah yang diduga memuat kesamaan. Pada tugas ini, anda akan diminta untuk melakukan implementasi algoritma pensejajaran global sederhana dengan prinsip pemrograman dinamis dan *DnC* (Divide and Conquer) yang sudah anda pelajari di kelas. Selain itu, anda akan diminta untuk melakukan MSA berdasarkan algoritma pensejajaran dua sekuens yang telah anda buat. Sebagai tantangan, anda akan menggunakan data sekuens DNA dari beberapa *strain* Coronavirus sebagai data uji coba.

## Milestone
Terdapat dua titik capai dalam tugas ini :
1. Implementasi algoritma Needleman-Wunsch , algoritma pemrograman dinamis untuk pensejajaran global.
2. Implementasi algoritma MSA

## Global Alignment
Algoritma pensejajaran global yang digunakan adalah algoritma Needleman-Wunsch (N-W) dengan menggunakan dynamic programming. Pendekatan algoritma ini saya bagi menjadi dua, yaitu utnuk pensejajaran antar nukleotida (ACTGU) dan pensejajaran antar protein (20 jenis asam amino).
Awalnya akan dibuat sebuah matrix n x m di mana n adalah panjang sekuens pertama dan m adalah panjang sekuens kedua. Matrix lalu diisi oleh nilaiantar basa nukelotida dengan aturan match(1) mismatch(-1) indel/gap(-1). Deangkan untuk pensejajaran protein, diambil data dari scoring matrix (matrix PAM250) terlebih dahulu lalu dihitung nilai tiap sel pada matrix. Setelah matrix terisi penuh, dilakukan proses traceback untuk menelusuri jalan sehingga diperoleh skor akhir pada sel matrix ujung kanan bawah.<br/>

untuk mengoptimalkan algoritma N-W ini, digunakan pendekatan divide and conquer (DnC). Algoritma ini menggunakan fungsi rekursif. Basis dari fungsi ini adalah ketika ukuran salah satu sisi matrix (baris atau kolomnya) sudah mencapai angka 1. Dilakukan pemrosesan matrix basis tersebut dengan algoritma N-W biasa. Sedangkan rekuresnnya adalah membagi-bagi matrix berukuran n x m tadi ke beberapa bagian.

## Getting Started
### How to compile
Pdaa folder src terdapat kode sumber program. Untuk melakukan kompilasi, lakukan langkah-langkah berikut:
1. Buka cmd (windows) untuk direktori src
2. ketikan perintah berikut di cmd
```
g++ main.cpp -o main
```
3. Kompilasi telah selesai, jika ingin menjalankan program dari hasil kompilasi tersebut, ketikkan perintah berikut di cmd
```
main.exe
```

### How to run
Pada folder bin, terdapat executable file yang dapat langsung dijalankan.
1. Buka cmd (windows) di direktori bin
2. ketikkan perintah berikut
```
main.exe
```
3. Program berhasil dijalankan.

### How to test
Untuk memasukkan test case, lakukan langkah berikut pada progam yang sudah dijalankan
1. pilih option 1 atau 2 (1 untuk pensejajaran nukelotida dan 2 untuk pensejajaran antar protein)
2. Masukkan file eksternal untuk sekuens pertama dan kedua
3. Algoritma akan memproses kedua sekuens
4. Hasil akan ditampilkan di layar cmd dan disimpan pada file eksternal pada folder result.


## Referensi
Silahkan gunakan referensi berikut sebagai awal pengerjaan tugas:<br>
[1] Pengenalan sequence alignment : https://www.bioinformaticsalgorithms.org/<br>
[2] Beragam kode sumber : https://github.com/topics/needleman-wunsch-algorithm<br>
[3] Data sekuens DNA : https://www.ncbi.nlm.nih.gov/nuccore<br>
[4] MSA dengan profile : https://www.ncbi.nlm.nih.gov/CBBresearch/Przytycka/download/lectures/PCB_Lect05_Multip_Align.pdf [pdf]<br>
[5] https://github.com/farhanma/PySeq<br>
[6] https://github.com/jtloong/needleman-wunsch-py

